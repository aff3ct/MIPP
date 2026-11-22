"""
Scalar forms of the functions (`"forms"` key of `registry_interfaces.json`).

A function whose arguments are data registers can also be called with a scalar in place of some of them: `add(r, s)`
adds the scalar `s` to every lane of `r`. Each form is a string with one letter per data register argument of the
base prototype, in order: `v` keeps the register, `s` takes a scalar of the element type instead. The base function
is the all-`v` form; the registry lists the other ones:

    "sub": { "proto_ref": "ret_reg_2args_reg", ..., "forms": ["vs", "sv"] }

gives `sub_vs(r, s)` and `sub_sv(s, r)`. Every form is expanded here, when the registry is loaded, into a function of
its own (`<base>_<form>`): a prototype where the `s` registers became `val` arguments of the type of the function,
the datatypes, variants and category of the base, and a scalar reference derived from the one of the base (`r1.r[i]`
becomes `s0`). The rest of the generator handles them as any other function. Their names follow the RVV style:
`mipp_sub_vs_float32_maskz_m2` in C (the form right after the name of the function), and `mipp::sub(r, s)` /
`mipp::sub(s, r)` in C++ (overloads of the base name, `cpp_name`).

Implementations:
- every form gets a generic Level 2 body (`generic_implems`): the base function with the scalar broadcast,
  `sub(r0, set1(s0))`, for every mask variant. Its level is the level of the base function (decision 9.4: the
  broadcast is free, as a cast): see `codegen/candidate_resolver.py` (`derived_form`);
- an ISA can give a native body under the name of the form (`"sub_vs": [...]` in `<isa>_native_implems.json`), with
  `s0`, `s1`... for the scalars: SVE `_n` intrinsics, RVV `.vx` / `.vf`, NEON `_n`.

The all-`v` form keeps the name of the base function; `mipp_<base>_vv_<...>` is an alias of it in C (`c_vv_aliases`).
"""
import copy
import re

# key of the interfaces that lists the forms of a function
FORMS_KEY = "forms"
# key added to the expanded interfaces: name of the base function and form
FORM_OF_KEY = "form_of"
FORM_KEY = "form"


def form_name(base, form):
    """Name of the function of a form: `sub` + `vs` -> `sub_vs`."""
    return f"{base}_{form}"


def form_proto_ref(proto_ref, form):
    """Name of the prototype of a form. It keeps the name of the base prototype (the tests builder reads the number
    of arguments in it, `2args`, `3args`) and appends the form."""
    return f"{proto_ref}_form_{form}"


def _data_reg_positions(proto):
    """Indices, in `proto["args"]`, of the data register arguments (type `reg` of the type of the function)."""
    return [i for i, a in enumerate(proto["args"]) if a["type"] == "reg" and a.get("fixeddatatype", False) is False]


def check_form(func, proto, form):
    """Raises ValueError if `form` does not match the data registers of the prototype of `func`."""
    n_regs = len(_data_reg_positions(proto))
    if not re.fullmatch(r"[vs]+", form):
        raise ValueError(f"'{func}': form '{form}' must only contain 'v' (register) and 's' (scalar)")
    if len(form) != n_regs:
        raise ValueError(f"'{func}': form '{form}' has {len(form)} letters, the prototype has {n_regs} data registers")
    if "s" not in form:
        raise ValueError(f"'{func}': form '{form}' is the base function (no scalar)")
    if "v" not in form:
        raise ValueError(f"'{func}': form '{form}' has no register (the result would not depend on a register)")


def derive_proto(proto, form):
    """Prototype of a form: the data registers marked `s` become read-only scalars of the type of the function."""
    p = copy.deepcopy(proto)
    for letter, pos in zip(form, _data_reg_positions(proto)):
        if letter == "s":
            p["args"][pos] = {"type": "val", "fixeddatatype": False, "charac": "RO"}
    return p


def arg_renaming(form):
    """
    Names of the arguments of the base (`r0`, `r1`...) in a form: the generator names the registers `r<i>` and the
    scalars `s<i>`, each with its own counter. `vs` -> {0: "r0", 1: "s0"}, `sv` -> {0: "s0", 1: "r0"}.
    """
    names = {}
    n_r = n_s = 0
    for i, letter in enumerate(form):
        if letter == "v":
            names[i] = f"r{n_r}"
            n_r += 1
        else:
            names[i] = f"s{n_s}"
            n_s += 1
    return names


def derive_scalar_code(code, form):
    """
    Scalar reference of a form from the one of the base: the lane `r<i>.r[i]` of a register that became a scalar
    is the scalar itself (`s<j>`), and the other registers are renumbered. Applied to the `implem` strings of
    `registry_scalar_implems.json`, which only read the registers lane by lane (`r<i>.r[i]`).
    """
    names = arg_renaming(form)

    def repl(m):
        new = names[int(m.group(1))]
        return new if new.startswith("s") else f"{new}.r[i]"

    out = re.sub(r"\br(\d+)\.r\[i\]", repl, code)
    # any other use of a register would not be renamed: the scalar reference must be written lane by lane
    left = [int(x) for x in re.findall(r"\br(\d+)\b", re.sub(r"\br\d+\.r\[i\]", "", code))]
    if any(names.get(i, "").startswith("s") for i in left):
        raise ValueError(f"scalar reference '{code}' uses a register other than lane by lane (r<i>.r[i])")
    return out


def expand_interfaces(raw_protos, raw_interfaces):
    """
    Adds to `raw_protos` and `raw_interfaces` (the JSON of the registry, modified in place) the prototype and the
    interface of every form, and removes the `forms` key of the base interfaces. Returns {form function: base}.
    """
    derived = {}
    for func in list(raw_interfaces):
        iface = raw_interfaces[func]
        forms = iface.pop(FORMS_KEY, [])
        for form in forms:
            base_proto = raw_protos[iface["proto_ref"]]
            check_form(func, base_proto, form)
            pref = form_proto_ref(iface["proto_ref"], form)
            if pref not in raw_protos:
                raw_protos[pref] = derive_proto(base_proto, form)
            name = form_name(func, form)
            if name in raw_interfaces:
                raise ValueError(f"form '{form}' of '{func}': '{name}' already exists in the registry")
            f_iface = copy.deepcopy(iface)
            f_iface["proto_ref"] = pref
            f_iface["cpp_name"] = iface.get("cpp_name", func)
            f_iface[FORM_OF_KEY] = func
            f_iface[FORM_KEY] = form
            raw_interfaces[name] = f_iface
            derived[name] = func
    return derived


def expand_categories(categories, derived):
    """Adds the functions of the forms to the category of their base (in place), right after it."""
    for name, base in derived.items():
        for funcs in categories.values():
            if base in funcs and name not in funcs:
                funcs.insert(funcs.index(base) + 1 + sum(1 for f in funcs if f.startswith(base + "_")
                                                           and derived.get(f) == base), name)
                break


def expand_scalar_implems(raw_scalar_implems, raw_interfaces, derived):
    """Adds the scalar reference of every form (in place), derived from the one of its base."""
    for name, base in derived.items():
        if name in raw_scalar_implems or base not in raw_scalar_implems:
            continue
        form = raw_interfaces[name][FORM_KEY]
        items = copy.deepcopy(raw_scalar_implems[base])
        for item in items:
            code = item["implem"]
            if isinstance(code, list):
                item["implem"] = [derive_scalar_code(line, form) for line in code]
            else:
                item["implem"] = derive_scalar_code(code, form)
        raw_scalar_implems[name] = items


def expand_docs(funcs_docs, raw_interfaces, derived):
    """
    Documentation of the forms without an entry in `funcs_docs.json`: the description of the base and the operand
    that is a scalar, and the formula of the base with the scalar operands (`r1_i` -> `s0`).
    """
    for name, base in derived.items():
        if name in funcs_docs or base not in funcs_docs:
            continue
        form = raw_interfaces[name][FORM_KEY]
        names = arg_renaming(form)
        base_doc = funcs_docs[base]
        ops = [f"operand {i + 1}" for i, letter in enumerate(form) if letter == "s"]
        desc = base_doc.get("description", "").rstrip(".")
        entry = dict(base_doc)
        entry["description"] = (f"{desc}, with a scalar as {' and '.join(ops)} (broadcast to every lane). "
                                f"Scalar form `{form}` of `{base}`.")
        if "latex" in base_doc:
            def repl(m):
                new = names.get(int(m.group(1)))
                if new is None:
                    return m.group(0)
                return new if new.startswith("s") else f"{new}_i"
            entry["latex"] = re.sub(r"\br(\d+)_i\b", repl, base_doc["latex"])
        funcs_docs[name] = entry


def base_call_args(base_proto, form):
    """
    Arguments of the call of the base function in the generic body of a form, in the order of the base prototype,
    with the names of the arguments of the form (the generator numbers each kind on its own: `r`, `m`, `s`, `p`):
    `select` (m, r, r) in form `vs` -> ["m0", "r0", "%set1<tp>%(s0)"].
    """
    form_proto = derive_proto(base_proto, form)
    prefix = {"reg": "r", "msk": "m", "val": "s", "ptr": "p"}
    counters = {}
    args = []
    for base_arg, arg in zip(base_proto["args"], form_proto["args"]):
        kind = prefix[arg["type"]]
        name = f"{kind}{counters.get(kind, 0)}"
        counters[kind] = counters.get(kind, 0) + 1
        # a data register of the base that became a scalar: broadcast
        args.append(f"%set1<tp>%({name})" if base_arg["type"] == "reg" and arg["type"] == "val" else name)
    return args


def generic_implems(raw_protos, raw_interfaces, derived):
    """
    Generic Level 2 bodies of the forms: the base function with the scalars broadcast by `set1`, for the unmasked
    function and its mask variants. Returns (unmasked table, mask table) in the format of `generic_emu_implems.json`
    and `generic_emu_implems_mask.json`, with inline templates. The entries are marked `derived_form` (name of the
    base): their level is the one of the base (see candidate_resolver.resolve_candidates).
    """
    std, mask = {}, {}
    for name, base in derived.items():
        iface = raw_interfaces[name]
        base_proto = raw_protos[raw_interfaces[base]["proto_ref"]]
        args = ", ".join(base_call_args(base_proto, iface[FORM_KEY]))
        datatypes = iface["datatypes"]
        std[name] = [{
            "datatypes": datatypes,
            "derived_form": base,
            "template": {"format": "long", "code": [f"return %{base}<tp>%({args});"]},
        }]
        # the mask (and the source of the masks variant) come first, before the arguments of the function. Merge
        # masking keeps the first register of the form in the inactive lanes (`sub_sv` M: `m ? s - r : r`, as SVE
        # `svsubr_n_m`): the merge variant of the base would keep the broadcast scalar when the base operand 0 became
        # a scalar, the inactive lanes are then taken back from the register by a select.
        if iface[FORM_KEY][0] == "s":
            m_call = f"return %select<tp>%(m0, %{base}<tp>%({args}), r0);"
        else:
            m_call = f"return %{base}<tp|v:M>%(m0, {args});"
        calls = {
            "m": m_call,
            "z": f"return %{base}<tp|v:Z>%(m0, {args});",
            "s": f"return %{base}<tp|v:S>%(m0, rsrc, {args});",
        }
        mask[name] = [{
            "datatypes": datatypes,
            "variant": v,
            "derived_form": base,
            "template": {"format": "long", "code": [calls[v]]},
        } for v in ("m", "z", "s") if v in iface["variants"]]
    return std, mask


def c_vv_aliases(func, variants, datatypes, lmul_suffixes):
    """
    C aliases of the base form `vv` (decision 9.5): `#define mipp_<func>_vv_<dt>[_<variant>]<lmul> mipp_<func>_...`,
    for every datatype, mask variant (`u`, `m`, `z`, `s`) and LMUL suffix (`""` for the LMUL 1 names without
    suffix, `_m1`, `_m2`, ..., `_d2`).
    """
    sfx = {"u": "", "m": "_mask", "z": "_maskz", "s": "_masks"}
    lines = []
    for dt in datatypes:
        for v in variants:
            for l in lmul_suffixes:
                tail = f"{dt}{sfx[v]}{l}"
                lines.append(f"#define mipp_{func}_vv_{tail} mipp_{func}_{tail}")
    return lines
