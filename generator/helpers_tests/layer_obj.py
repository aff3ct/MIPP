from headers_def import mipp_funcs
from .templates import GENERIC_FOR_LOOP
from .common import (
    TemplateParts,
    build_layer_gen_test_dict,
    SHAPE_RET_REG_2ARGS_REG,
    SHAPE_RET_MSK_2ARGS_REG,
    SHAPE_RET_REG_1ARG_PTR,
    SHAPE_RET_VOID_2ARGS_PTR_REG,
)


FUNC_DECL = """template <typename T>\nvoid test_objmipp_{{func}}(){"""

DECL_2ARGS = """\tconst int vectorSize = mipp::N<T>(); T inputs1[vectorSize],inputs2[vectorSize];"""
DECL_1ARG = """\tconst int vectorSize = mipp::N<T>(); T inputs1[vectorSize];"""
DECL_2ARGS_FOR_STORE = """\tconst int vectorSize = mipp::N<T>(); T inputs1[vectorSize],inputs2[vectorSize];"""

INIT_2ARGS = """\tstd::iota(inputs1, inputs1 + vectorSize, 1);
\tstd::iota(inputs2, inputs2 + vectorSize, 1);

\tstd::mt19937 g;
\tstd::shuffle(inputs1, inputs1 + vectorSize, g);
\tstd::shuffle(inputs2, inputs2 + vectorSize, g);
"""

INIT_2ARGS_NOUFLOW = INIT_2ARGS + """\tfor(int i = 0; i < vectorSize; i++)
\t{
\t\tinputs1[i] += inputs2[i];
\t}
"""

INIT_1ARG = """\tstd::iota(inputs1, inputs1 + vectorSize, 1);
\tstd::mt19937 g;
\tstd::shuffle(inputs1, inputs1 + vectorSize, g);
"""

LOAD_2ARGS = """\t//{{reg_type}} r1(inputs1), r2(inputs2); // waiting for load to be fixed in obj layer
\t{{reg_type}} r1, r2; r1.r = mipp::load<T>(inputs1); r2.r = mipp::load<T>(inputs2);"""
LOAD_1ARG = """\t//{{reg_type}} r1(inputs1); // waiting for load to be fixed in obj layer
\t{{reg_type}} r1; r1.r = mipp::load<T>(inputs1);"""

# For maintainability: use operator overload for binops (like you did).
OP_REG_BINOP = """\t{{reg_type}} r3 = r1 {{op}} r2;"""
OP_STORE = """\tmipp::store(inputs2, r1.r);"""

LB_REG_BINOP = """\t\tT res = inputs1[i] {{op}} inputs2[i];"""
AS_REG_BINOP = """\t\tREQUIRE(r3[i] == res);"""

LB_LOAD = """\t\tT res = inputs1[i];"""
AS_LOAD = """\t\tREQUIRE(r1[i] == res);"""

LB_STORE = """\t\tT res = inputs1[i];"""
AS_STORE = """\t\tREQUIRE(inputs2[i] == res);"""

shape_templates = {
    SHAPE_RET_REG_2ARGS_REG: TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_2ARGS,
        init=INIT_2ARGS,
        load=LOAD_2ARGS,
        operation=OP_REG_BINOP,
        loop_body=LB_REG_BINOP,
        loop_assert=AS_REG_BINOP,
    ),

    SHAPE_RET_REG_1ARG_PTR: TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_1ARG,
        init=INIT_1ARG,
        load=LOAD_1ARG,
        operation="",  # load is in LOAD_1ARG line already
        loop_body=LB_LOAD,
        loop_assert=AS_LOAD,
    ),
    SHAPE_RET_VOID_2ARGS_PTR_REG: TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_2ARGS_FOR_STORE,
        init=INIT_1ARG,     # only inputs1 needs init; inputs2 is output
        load=LOAD_1ARG,     # store uses r1 loaded from inputs1
        operation=OP_STORE,
        loop_body=LB_STORE,
        loop_assert=AS_STORE,
    ),
}


deny = {
    "cast", "cast_k", "toreg", "tomsk",
    "maskzld", "maskst",
    "blend", "getfirst", "get_k", "set_k", "set0_k", "set1_k",
    "testz", "testz_2",
    "sqrt", "rsqrt",
    "hadd", "hmul", "hmin", "hmax", "hadd_to_scal",
    "notb", "notb_k",
    "andb_k", "orb_k", "xorb_k", "andnb_k",
    "cmpeq", "cmpneq", "cmplt", "cmple", "cmpgt", "cmpge",
    "max", "min", 
    "orb", "xorb", "andb",
    "andnb", #andnb broken in object layer.
    "pow",
}

LAYER_OVERRIDES = {
    # Non-operator function: expected scalar expression override
    "andnb": {
        "operation": "mipp::Rvd<T> r3 = ~(r1) & (r2);",
        "loop_body": """\t\tT res = ~(inputs1[i]) & (inputs2[i]);"""
    },

    "sub": {
        "init": INIT_2ARGS_NOUFLOW
    },

    "div" : {
        "loop_assert": """\tREQUIRE(
#if defined(MIPP_NEON) && !defined(__aarch64__)
            std::abs(r3[i] - res) < 1e-2
#else
            r3[i] == res
#endif
        );""",
    },
}

def apply_overrides(gen_dict):
    for func, entry in gen_dict.items():
        ovr = LAYER_OVERRIDES.get(func)
        if not ovr:
            continue

        if "func_decl" in ovr:
            decl = ovr["func_decl"]
            entry["proto"]["func_decl"] = decl
        if "decl" in ovr:
            decl = ovr["decl"]
            entry["proto"]["decl"] = decl
        if "init" in ovr:
            strat = ovr["init"]
            entry["proto"]["init"] = strat
        if "load" in ovr:
            load = ovr["load"]
            entry["proto"]["load"] = load
        if "operation" in ovr:
            op = ovr["operation"]
            entry["proto"]["operation"] = op
        if "loop_assert" in ovr:
            assert_ = ovr["loop_assert"]
            entry["proto"]["loop_assert"] = assert_
        if "loop_body" in ovr:
            body = ovr["loop_body"]
            entry["proto"]["loop_body"] = body
    return gen_dict

gen_test_dict = build_layer_gen_test_dict(
    layer_name="obj",
    template=GENERIC_FOR_LOOP,
    mipp_funcs=mipp_funcs,
    shape_templates=shape_templates,
    deny_funcs=deny,
)

gen_test_dict = apply_overrides(gen_test_dict)