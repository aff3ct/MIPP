"""Symbol tables of the generated C headers, for the "Algorithm" modal of the API Explorer.

For each ISA, the C headers of include/mipp/internal/simd_ext/<isa>/c/ are split into top-level
symbols (macros, types, functions, other declarations). Each symbol keeps its exact code, the
preprocessor conditions under which it is defined, and the names of the other symbols it uses.
The Explorer rebuilds from these tables the self-contained code of any function (the transitive
closure of its dependencies), for the compiler flags selected by the user.

Output: docs/assets/data/algo/<isa>.json and docs/assets/data/algo/index.json.
"""
import json
import os
import re

IDENT = re.compile(r"[A-Za-z_][A-Za-z0-9_]*")
GUARD_RE = re.compile(r"^#ifndef\s+(\w+_H_?)\s*$")
INCLUDE_SIMD_RE = re.compile(r"#include\s+[<\"]mipp/internal/simd_ext/(\w+)/")
DIRECTIVE_RE = re.compile(r"^\s*#\s*(\w+)\s*(.*)$")


def _strip_comments(code):
    """Code without comments and string literals (for the dependency scan only)."""
    code = re.sub(r"/\*.*?\*/", " ", code, flags=re.S)
    code = re.sub(r"//[^\n]*", " ", code)
    return re.sub(r"\"(?:\\.|[^\"\\])*\"", "\"\"", code)


def _brace_delta(line):
    s = _strip_comments(line)
    return s.count("{") - s.count("}")


def _decl_name(text):
    """Name declared by a top-level statement (typedef, function, variable)."""
    s = _strip_comments(text)
    s = re.sub(r"__attribute__\s*\(\(.*?\)\)", " ", s, flags=re.S)
    head = s.split("{", 1)[0] if "(" not in s.split("{", 1)[0] or s.lstrip().startswith("typedef") else s
    if s.lstrip().startswith("typedef"):
        body = re.sub(r"\{.*\}", " ", s, flags=re.S)  # struct / union body
        names = IDENT.findall(body.rsplit(";", 1)[0])
        return names[-1] if names else None
    m = re.match(r"[^(=;{]*?\b([A-Za-z_]\w*)\s*\(", head, flags=re.S)
    if m:
        return m.group(1)
    names = IDENT.findall(re.split(r"[=;\[]", s, maxsplit=1)[0])
    return names[-1] if names else None


def parse_header(path, isa, symbols, imports, system_includes=None):
    """Adds the symbols of one header to `symbols` ({name: [variant, ...]})."""
    with open(path, encoding="utf-8") as f:
        lines = f.read().split("\n")
    conds = []  # stack of lists: the conditions of the branches of each open #if
    stmt, stmt_conds, depth = [], None, 0
    i = 0
    guard = None
    while i < len(lines):
        line = lines[i]
        i += 1
        if stmt:  # inside a multi-line statement (function body, struct typedef): keep everything
            stmt.append(line)
            depth += _brace_delta(line)
            if depth <= 0 and (_strip_comments(line).rstrip().endswith("}") or _strip_comments(line).rstrip().endswith(";")):
                if depth == 0 and _strip_comments(line).rstrip().endswith("}") and stmt[0].lstrip().startswith("typedef"):
                    continue  # typedef struct {...} name; may end on a later line
                _add(symbols, "\n".join(stmt), stmt_conds, isa)
                stmt = []
            continue
        d = DIRECTIVE_RE.match(line)
        if d:
            kw, rest = d.group(1), d.group(2).strip()
            if kw == "pragma" or kw == "error" or kw == "warning":
                continue
            if kw == "include":
                m = INCLUDE_SIMD_RE.search(line)
                if m and m.group(1) != isa:
                    imports.add(m.group(1))
                sm = re.match(r"\s*#\s*include\s*(<[^>]+>)", line)
                if sm and system_includes is not None and sm.group(1) not in system_includes:
                    system_includes.append(sm.group(1))
                continue
            if kw == "ifndef" and guard is None and GUARD_RE.match(line.strip()) and i < len(lines) and lines[i].strip().startswith("#define " + rest.split()[0]):
                guard = rest.split()[0]
                i += 1  # skip the #define of the guard
                conds.append(None)  # marks the guard level
                continue
            if kw in ("if", "ifdef", "ifndef"):
                expr = {"if": rest, "ifdef": f"defined({rest})", "ifndef": f"!defined({rest})"}[kw]
                conds.append([expr])
                continue
            if kw == "elif":
                prev = conds[-1]
                conds[-1] = prev + [rest]
                continue
            if kw == "else":
                if conds[-1] is not None:
                    conds[-1] = conds[-1] + ["1"]
                continue
            if kw == "endif":
                conds.pop()
                continue
            if kw == "define":
                text = line
                while text.endswith("\\") and i < len(lines):
                    text += "\n" + lines[i]
                    i += 1
                name = IDENT.match(rest).group(0)
                if name.startswith("MIPP_FLOAT_TYPEDEFS"):
                    continue
                _add(symbols, text, _active(conds), isa, name=name, kind="macro")
                continue
            if kw == "undef":
                continue
            continue
        s = _strip_comments(line).strip()
        if not s:
            continue
        # forward declarations of functions: skipped (the definitions are kept)
        if re.match(r"static\s+inline\b", s) and s.endswith(");") and "{" not in s:
            continue
        stmt, stmt_conds = [line], _active(conds)
        depth = _brace_delta(line)
        ends = s.endswith(";") and depth == 0
        if ends or (depth == 0 and s.endswith("}")):
            _add(symbols, line, stmt_conds, isa)
            stmt = []


def _active(conds):
    """Condition of the current position: each open #if contributes its last branch, the
    previous branches of an #elif / #else chain are negated."""
    out = []
    for branch in conds:
        if branch is None:
            continue
        for prev in branch[:-1]:
            out.append(f"!({prev})")
        if branch[-1] != "1":
            out.append(branch[-1])
    return out


def _add(symbols, code, cond, isa, name=None, kind=None):
    first = _strip_comments(code).strip()
    if kind is None:
        if first.startswith("typedef"):
            kind = "type"
        elif re.match(r"(static\s+)?(inline\s+)?[^;{]*\([^;]*\)\s*\{", first, flags=re.S):
            kind = "func"
        else:
            kind = "decl"
    if name is None:
        name = _decl_name(code)
    if not name:
        return
    variants = symbols.setdefault(name, [])
    for v in variants:
        if v["code"] == code and v["cond"] == cond:
            return
    variants.append({"kind": kind, "code": code.rstrip(), "cond": cond})


def parse_isa(include_dir, isa):
    root = os.path.join(include_dir, "mipp", "internal", "simd_ext", isa, "c")
    symbols, imports = {}, set()
    paths = []
    for dirpath, _, files in os.walk(root):
        for fn in files:
            if fn.endswith(".h"):
                paths.append(os.path.join(dirpath, fn))
    # common.h first: macros and types before the functions
    paths.sort(key=lambda p: (not p.endswith(os.sep + "common.h"), p))
    includes = []
    for p in paths:
        parse_header(p, isa, symbols, imports, includes if p.endswith(os.sep + "common.h") else None)
    # Prototypes of the functions defined in these headers (RVV declares its functions first,
    # as they call each other in any order): the definitions are the symbols. A prototype
    # listed first would be resolved in their place, and it has no body to show.
    for variants in symbols.values():
        if any(v["kind"] == "func" for v in variants):
            variants[:] = [v for v in variants if v["kind"] != "decl"]
    return symbols, sorted(imports), includes


CPP_WRAPPER_RE = re.compile(
    r"inline\s+[^\n]*?\b(\w+)\s*(<[^>()]*>)?\s*\([^)]*\)\s*\{\s*return\s+(mipp_\w+)\s*\(", re.S)


def parse_cpp_wrappers(include_dir, isa):
    """C function -> C++ Functional API call head ('add', 'add<M, float32_t, 1>', 'set0<float32_t, 1>')."""
    root = os.path.join(include_dir, "mipp", "internal", "simd_ext", isa, "cpp")
    out = {}
    for dirpath, _, files in os.walk(root):
        for fn in files:
            if not fn.endswith(".hpp"):
                continue
            with open(os.path.join(dirpath, fn), encoding="utf-8") as f:
                text = f.read()
            for m in CPP_WRAPPER_RE.finditer(text):
                name, targs, cfunc = m.group(1), m.group(2), m.group(3)
                if targs:
                    args = [a.strip() for a in targs[1:-1].split(",")]
                    args = [a for a in args if a and a not in (isa.upper(), "ISA::" + isa.upper())]
                    targs = "<" + ", ".join(args) + ">" if args else ""
                out.setdefault(cfunc, name + (targs or ""))
    return out


def _deps(code, known, self_name):
    names = set(IDENT.findall(_strip_comments(code)))
    names.discard(self_name)
    return sorted(n for n in names if n in known)


def export_algo_sources(project_root, isas):
    include_dir = os.path.join(project_root, "include")
    out_dir = os.path.join(project_root, "docs", "assets", "data", "algo")
    if not os.path.isdir(os.path.join(include_dir, "mipp", "internal", "simd_ext")):
        print("[algo_sources] include/ not generated: run gen_mipp_headers.py first (skipped)")
        return None
    os.makedirs(out_dir, exist_ok=True)

    tables, imports, includes, cpp = {}, {}, {}, {}
    for isa in isas:
        if os.path.isdir(os.path.join(include_dir, "mipp", "internal", "simd_ext", isa, "c")):
            tables[isa], imports[isa], includes[isa] = parse_isa(include_dir, isa)
            cpp[isa] = parse_cpp_wrappers(include_dir, isa)
    # macros shared by all the ISAs (MIPP_RVD_SIZE_BYTE, MIPP_LMUL_STRIDE, ...): public C interface
    iface_symbols, iface_imports = {}, set()
    parse_header(os.path.join(include_dir, "mipp", "internal", "interfaces", "c", "common.h"),
                 "interface", iface_symbols, iface_imports)
    tables["interface"], imports["interface"], includes["interface"], cpp["interface"] = iface_symbols, [], [], {}
    for isa in isas:
        if isa in imports:
            imports[isa] = imports[isa] + ["interface"]

    # every name an ISA can see: its own symbols and those of the ISAs it imports (transitively)
    def visible(isa, seen=None):
        seen = seen if seen is not None else set()
        if isa in seen or isa not in tables:
            return set()
        seen.add(isa)
        names = set(tables[isa])
        for imp in imports[isa]:
            names |= visible(imp, seen)
        return names

    index = {"isas": {}}
    all_names = set().union(*[set(t) for t in tables.values()])
    for isa, symbols in tables.items():
        # the shared interface refers to the macros of every ISA (MIPP_RVD_SIZE_BYTE -> MIPP_AVX_RVD_SIZE_BYTE)
        known = all_names if isa == "interface" else visible(isa)
        for name, variants in symbols.items():
            for v in variants:
                v["deps"] = _deps(v["code"], known, name)
        payload = {"isa": isa, "imports": imports[isa], "includes": includes[isa], "cpp": cpp[isa], "symbols": symbols}
        path = os.path.join(out_dir, f"{isa}.json")
        with open(path, "w", encoding="utf-8") as f:
            json.dump(payload, f, separators=(",", ":"), ensure_ascii=False)
        if isa == "interface":
            index["interface"] = {"symbols": len(symbols), "bytes": os.path.getsize(path)}
            continue
        index["isas"][isa] = {"imports": imports[isa], "symbols": len(symbols), "bytes": os.path.getsize(path)}

    # the ISA selection logic of the public C interface (MIPP_AVX, MIPP_BW, ...), evaluated by the
    # Explorer with the predefined macros of the selected compiler flags
    common = os.path.join(include_dir, "mipp", "internal", "interfaces", "c", "common.h")
    with open(common, encoding="utf-8") as f:
        text = f.read()
    start = text.find("#if defined(MIPP_SCALAR)")
    end = text.find("#ifndef MIPP_FLOAT_TYPEDEFS_")
    index["selection"] = text[start:end].strip() if start >= 0 and end > start else ""
    with open(os.path.join(out_dir, "index.json"), "w", encoding="utf-8") as f:
        json.dump(index, f, indent=1)
    return index


if __name__ == "__main__":
    import sys
    root = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
    idx = export_algo_sources(root, sys.argv[1:] or ["sse", "avx", "avx512", "neon", "sve", "rvv", "scalar"])
    print(json.dumps({k: v for k, v in idx["isas"].items()}, indent=1))
