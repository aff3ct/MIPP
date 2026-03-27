from headers_def import mipp_funcs
from .templates import GENERIC_FOR_LOOP
from .common import (
    TemplateParts,
    build_layer_gen_test_dict,
    SHAPE_RET_REG_2ARGS_REG,
    SHAPE_RET_MSK_2ARGS_REG,
    SHAPE_RET_REG_1ARG_PTR,
    SHAPE_RET_VOID_2ARGS_PTR_REG,
    #those are only backed by 1 function ;(
    SHAPE_RET_REG_1ARG_NELE,#set only
    SHAPE_RET_MSK_1ARG_NELE,#setk 
    SHAPE_RET_REG_1ARG_VAL, #only set1 :o
    SHAPE_RET_MSK_1ARG_I32,#set1_k
    SHAPE_RET_REG_0ARG,#set0
    SHAPE_RET_MSK_0ARG,#set0_k
)

# --------------------------
# C fragments
# --------------------------


# --------------------------------------------
# FN decl 
# --------------------------------------------
FUNC_DECL = """void test_cmipp_{{func}}_{{dt_ext}}(){"""


# --------------------------------------------
# SCALAR VEC DECL
# --------------------------------------------
DECL_0ARGS = "\tconst int vectorSize = {{size}};"
DECL_1ARG = """\tconst int vectorSize = {{size}}; {{dt_ext}}_t inputs1[vectorSize];"""
DECL_1ARG_INT32 = """\tconst int vectorSize = {{size}}; int32_t inputs1[vectorSize];"""
DECL_1ARG_SCALAR = """\tconst int vectorSize = {{size}}; \t{{dt_ext}}_t input1 = 12;"""
DECL_1ARG_SCALAR_INT32 = """\tconst int vectorSize = {{size}}; \tint32_t input1 = 12;"""

DECL_2ARGS_FOR_STORE = """\tconst int vectorSize = {{size}};\n\t{{dt_ext}}_t inputs1[vectorSize],inputs2[vectorSize];"""
DECL_2ARGS = """\tconst int vectorSize = {{size}};\n\t{{dt_ext}}_t inputs1[vectorSize],inputs2[vectorSize];"""

# --------------------------------------------
# SCALAR VEC INIT
# --------------------------------------------
INIT_2ARGS = """\tstd::iota(inputs1, inputs1 + vectorSize, 1);
\tstd::iota(inputs2, inputs2 + vectorSize, 1);

\tstd::mt19937 g;
\tstd::shuffle(inputs1, inputs1 + vectorSize, g);
\tstd::shuffle(inputs2, inputs2 + vectorSize, g);
"""

INIT_1ARG = """\tstd::iota(inputs1, inputs1 + vectorSize, 1);
\tstd::mt19937 g;
\tstd::shuffle(inputs1, inputs1 + vectorSize, g);
"""

INIT_2ARGS_NOUFLOW = INIT_2ARGS + """\tfor(int i = 0; i < vectorSize; i++)
\t{
\t\tinputs1[i] += inputs2[i];
\t}
"""

# --------------------------------------------
# LOADS
# --------------------------------------------

LOAD_2ARGS_REG = """\t{{reg_type}} r1 = mipp_load_{{dt_ext}}(inputs1);
\t{{reg_type}} r2 = mipp_load_{{dt_ext}}(inputs2);"""

LOAD_1ARG_REG = """\t{{reg_type}} r1 = mipp_load_{{dt_ext}}(inputs1);"""
LOAD_1SCALAR_REG = """\t{{reg_type}} r1 = mipp_set1_{{dt_ext}}(input1);"""
LOAD_SET0_REG = """\t{{reg_type}} r1 = mipp_set0_{{dt_ext}}();"""

LOAD_2ARGS_MASK = """\t{{msk_type}} m1 = mipp_set_k_{{dt_ext}}(inputs1); 
\t{{msk_type}} m2 = mipp_set_k_{{dt_ext}}(inputs2);"""

LOAD_1ARG_MASK = """\t{{msk_type}} m1 = mipp_set_k_{{dt_ext}}(inputs1);"""
LOAD_1SCALAR_MASK = """\t{{msk_type}} m1 = mipp_set1_k_{{dt_ext}}(input1);"""
LOAD_SET0_MASK = """\t{{msk_type}} m1 = mipp_set0_k_{{dt_ext}}();"""

# --------------------------------------------
# OPERATIONS
# --------------------------------------------

OP_REG_NOOP = """\t{{reg_type}} r3 = r1;"""
OP_REG_UNOP = """\t{{reg_type}} r3 = mipp_{{func}}_{{dt_ext}}(r1);"""
OP_REG_BINOP = """\t{{reg_type}} r3 = mipp_{{func}}_{{dt_ext}}(r1, r2);"""

OP_CMP_2REG = """\t{{msk_type}} m3 = mipp_{{func}}_{{dt_ext}}(r1, r2); {{reg_type}} r3 = mipp_toreg_{{dt_ext}}(m3);"""

OP_STORE = """\tmipp_store_{{dt_ext}}(inputs2, r1);"""

OP_TOREG = """\t{{reg_type}} r3 = mipp_toreg_{{dt_ext}}(m1);"""

# --------------------------------------------
# OPERATION IN LOOP BODY
# ------------------------------------------

LB_SET_OP = """\t\t{{dt_ext}}_t res = inputs1[i];"""
LB_SET_SCALAR_OP = """\t\t{{dt_ext}}_t res = input1;"""

LB_REG_BINOP = """\t\t{{dt_ext}}_t res = inputs1[i] {{op}} inputs2[i];"""
AS_REG_BINOP = """\t\tREQUIRE(mipp_get_{{dt_ext}}(r3, i) == res);"""

LB_CMP_2REG = """\t\tbool res = inputs1[i] {{op}} inputs2[i];"""
AS_CMP_2REG = """\t\tif(res) REQUIRE(mipp_get_{{dt_ext}}(r3, i) != 0); else REQUIRE(mipp_get_{{dt_ext}}(r3, i) == 0);"""

LB_LOAD = """\t\t{{dt_ext}}_t res = inputs1[i];"""
AS_LOAD = """\t\tREQUIRE(mipp_get_{{dt_ext}}(r1, i) == res);"""

LB_STORE = """\t\t{{dt_ext}}_t res = inputs1[i];"""
AS_STORE = """\t\tREQUIRE(inputs2[i] == res);"""

shape_templates = {
    SHAPE_RET_REG_2ARGS_REG: TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_2ARGS,
        init=INIT_2ARGS,
        load=LOAD_2ARGS_REG,
        operation=OP_REG_BINOP,
        loop_body=LB_REG_BINOP,
        loop_assert=AS_REG_BINOP,
    ),
    SHAPE_RET_MSK_2ARGS_REG: TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_2ARGS,
        init=INIT_2ARGS,
        load=LOAD_2ARGS_REG,
        operation=OP_CMP_2REG,
        loop_body=LB_CMP_2REG,
        loop_assert=AS_CMP_2REG,
    ),
    SHAPE_RET_REG_1ARG_PTR: TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_1ARG,
        init=INIT_1ARG,
        load=LOAD_1ARG_REG,
        operation="",  # load is in LOAD_1ARG_REG line already
        loop_body=LB_LOAD,
        loop_assert=AS_LOAD,
    ),
    SHAPE_RET_VOID_2ARGS_PTR_REG: TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_2ARGS_FOR_STORE,
        init=INIT_1ARG,     # only inputs1 needs init; inputs2 is output
        load=LOAD_1ARG_REG,     # store uses r1 loaded from inputs1
        operation=OP_STORE,
        loop_body=LB_STORE,
        loop_assert=AS_STORE,
    ),

    SHAPE_RET_REG_1ARG_NELE: TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_1ARG,
        init=INIT_1ARG,
        load="""\t{{reg_type}} r1 = mipp_{{func}}_{{dt_ext}}(inputs1);""",
        operation=OP_REG_NOOP,
        loop_body=LB_SET_OP,
        loop_assert=AS_REG_BINOP,
    ),
    
    SHAPE_RET_MSK_1ARG_NELE: TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_1ARG_INT32,
        init=INIT_1ARG,
        load=LOAD_1ARG_MASK,
        operation=OP_TOREG,
        loop_body=LB_SET_OP,
        loop_assert=AS_CMP_2REG,
    ),
    
    SHAPE_RET_REG_1ARG_VAL: TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_1ARG_SCALAR,
        init="",
        load=LOAD_1SCALAR_REG,
        operation=OP_REG_NOOP,
        loop_body=LB_SET_SCALAR_OP,
        loop_assert=AS_REG_BINOP,
    ),
    
    SHAPE_RET_MSK_1ARG_I32: TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_1ARG_SCALAR_INT32,
        init="",
        load=LOAD_1SCALAR_MASK,
        operation=OP_TOREG,
        loop_body=LB_SET_SCALAR_OP,
        loop_assert=AS_CMP_2REG,
    ),
    
    SHAPE_RET_REG_0ARG: TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_0ARGS,
        init="",
        load=LOAD_SET0_REG,
        operation=OP_REG_NOOP,
        loop_body="\t\t{{dt_ext}}_t res = 0;",
        loop_assert=AS_REG_BINOP,
    ),
    
    SHAPE_RET_MSK_0ARG: TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_0ARGS,
        init="",
        load=LOAD_SET0_MASK,
        operation=OP_TOREG,
        loop_body="\t\t{{dt_ext}}_t res = 0;",
        loop_assert=AS_CMP_2REG,
    ),
}

deny = {
    # casts / masks / gather / reductions etc (for now)
    "cast", "cast_k", "toreg", "tomsk",
    "maskzld", "maskst",
    "gather", "scatter",
    "blend", "getfirst", "get_k",
    "testz", "testz_2",
    "sqrt", "rsqrt",
    "hadd", "hmul", "hmin", "hmax", "hadd_to_scal",
    "notb", "notb_k",
    "andb_k", "orb_k", "xorb_k", "andnb_k", 
    "max", "min"
}


LAYER_OVERRIDES = {
    # Non-operator function: expected scalar expression override
    "andnb": {
        "loop_body": """\t\t{{dt_ext}}_t res = ~(inputs1[i]) & (inputs2[i]);"""
    },

    "sub": {
        "init": INIT_2ARGS_NOUFLOW
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
    layer_name="c",
    template=GENERIC_FOR_LOOP,
    mipp_funcs=mipp_funcs,
    shape_templates=shape_templates,
    deny_funcs=deny,
)

gen_test_dict = apply_overrides(gen_test_dict)