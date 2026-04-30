import copy
from headers_def import mipp_funcs
from .templates import GENERIC_FOR_LOOP, GENERIC_NO_LOOP
from .common import (
    TemplateParts,
    build_layer_gen_test_dict,
    SHAPE_RET_REG_2ARGS_REG,
    SHAPE_RET_MSK_2ARGS_REG,
    SHAPE_RET_REG_1ARG_PTR,
    SHAPE_RET_VOID_2ARGS_PTR_REG,
    SHAPE_RET_REG_1ARG_NELE,      # set only
    SHAPE_RET_MSK_1ARG_NELE,      # set_k only
    SHAPE_RET_REG_1ARG_VAL,       # set1 only
    SHAPE_RET_MSK_1ARG_I32,       # set1_k only
    SHAPE_RET_REG_0ARG,           # set0
    SHAPE_RET_MSK_0ARG,           # set0_k
    SHAPE_RET_VAL_2ARGS_REG_VAL,  # get
    SHAPE_RET_VAL_2ARGS_MSK_VAL,  # get_k
    SHAPE_RET_VAL_1ARG_REG,
    SHAPE_RET_REG_3ARGS_2REG_1MSK,    # blend
    SHAPE_RET_MSK_2ARGS_MSK,          # andb_k/orb_k/xorb_k/andnb_k
    SHAPE_RET_REG_1ARG_REG,           # notb, sqrt, cast, reductions...
    SHAPE_RET_MSK_1ARG_MSK,           # notb_k, cast_k
    SHAPE_RET_REG_1ARG_MSK,           # toreg
    SHAPE_RET_REG_3ARGS_REG,          # fmadd, fmsub, fnmadd, fnmsub
    SHAPE_RET_I32_2ARGS_MSK,          # testz
    SHAPE_RET_I32_1ARG_MSK,           # testz_2
    SHAPE_RET_REG_3ARGS_1MSK_2REG,    # maskz_add
    SHAPE_RET_MSK_1ARG_REG,           # tomsk
    SHAPE_RET_REG_2ARGS_MASK_PTR,     # maskz load
    SHAPE_RET_VOID_3ARGS_PTR_MSK_REG, # mask store (maskst)
)

# --------------------------
# C fragments (suffix + coeff generic)
# --------------------------

# --------------------------------------------
# FN decl
# --------------------------------------------
FUNC_DECL = """void test_cmipp_{{func}}_{{dt_ext}}_{{lmul_suffix}}(){"""

# --------------------------------------------
# SCALAR VEC DECL
# --------------------------------------------
DECL_0ARGS = "\tconst int vectorSize = {{size}} * {{lmul_coeff}};"
DECL_1ARG = """\tconst int vectorSize = {{size}} * {{lmul_coeff}}; {{dt_ext}}_t inputs1[vectorSize];"""
DECL_1ARG_INT32 = """\tconst int vectorSize = {{size}} * {{lmul_coeff}}; int32_t inputs1[vectorSize];"""
DECL_1ARG_SCALAR = """\tconst int vectorSize = {{size}} * {{lmul_coeff}}; \t{{dt_ext}}_t input1 = 12;"""
DECL_1ARG_SCALAR_INT32 = """\tconst int vectorSize = {{size}} * {{lmul_coeff}}; \tint32_t input1 = 12;"""

DECL_2ARGS_FOR_STORE = """\tconst int vectorSize = {{size}} * {{lmul_coeff}};\n\t{{dt_ext}}_t inputs1[vectorSize],inputs2[vectorSize];"""
DECL_2ARGS = """\tconst int vectorSize = {{size}} * {{lmul_coeff}};\n\t{{dt_ext}}_t inputs1[vectorSize],inputs2[vectorSize];"""
DECL_2ARGS_INT32 = """\tconst int vectorSize = {{size}} * {{lmul_coeff}};\n\tint32_t inputs1[vectorSize],inputs2[vectorSize];"""
DECL_3ARGS = """\tconst int vectorSize = {{size}} * {{lmul_coeff}};\n\t{{dt_ext}}_t inputs1[vectorSize],inputs2[vectorSize],inputs3[vectorSize];"""

DECL_G_SNIPPET = """\tstd::mt19937 g;\n\tstd::uniform_int_distribution<uint16_t> dis(0, 1);"""

# cast: allocate inputs1 scaled by coeff; inputs2 size is computed from bytes (correctly scales)
DECL_CAST_2ARGS = """\tconst int vectorSize = {{size}} * {{lmul_coeff}};\n\t{{dt1_ext}}_t inputs1[vectorSize];\n\tconstexpr size_t bytes = sizeof(inputs1);\n\t{{dt2_ext}}_t inputs2[bytes / sizeof({{dt2_ext}}_t)];"""
DECL_CAST_2ARGS_MSK = """\tconst int vectorSize = {{size}} * {{lmul_coeff}};\n\tint32_t inputs1[vectorSize];\n\tconstexpr size_t bytes = sizeof(inputs1);\n\t{{dt2_ext}}_t inputs2[bytes / sizeof({{dt2_ext}}_t)];"""

# --------------------------------------------
# SCALAR VEC INIT (unchanged)
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

INIT_1ARG_DIS = """\tstd::iota(inputs1, inputs1 + vectorSize, 1);
\tfor(int i = 0; i < vectorSize; i++)
\t{
\t\tinputs1[i] = dis(g) ? -1 : 0;
\t}"""

INIT_2ARGS_DIS = """\tfor(int i = 0; i < vectorSize; i++)
\t{
\t\tinputs1[i] = dis(g) ? -1 : 0;
\t\tinputs2[i] = dis(g) ? -1 : 0;
\t}"""

INIT_3ARGS = """\tstd::iota(inputs1, inputs1 + vectorSize, 1);
\tstd::iota(inputs2, inputs2 + vectorSize, 1);
\tstd::iota(inputs3, inputs3 + vectorSize, 1);"""

INIT_CAST_2ARGS = """\tstd::iota(inputs1, inputs1 + vectorSize, 1);\n\tmemcpy(inputs2, inputs1, sizeof(inputs1));"""

# --------------------------------------------
# LOADS (suffix)
# --------------------------------------------
LOAD_2ARGS_REG = """\t{{reg_type}} r1 = mipp_load_{{dt_ext}}_{{lmul_suffix}}(inputs1);
\t{{reg_type}} r2 = mipp_load_{{dt_ext}}_{{lmul_suffix}}(inputs2);"""

LOAD_1ARG_REG = """\t{{reg_type}} r1 = mipp_load_{{dt_ext}}_{{lmul_suffix}}(inputs1);"""
LOAD_1SCALAR_REG = """\t{{reg_type}} r1 = mipp_set1_{{dt_ext}}_{{lmul_suffix}}(input1);"""
LOAD_SET0_REG = """\t{{reg_type}} r1 = mipp_set0_{{dt_ext}}_{{lmul_suffix}}();"""

LOAD_2ARGS_MASK = """\t{{msk_type}} m1 = mipp_set_k_{{dt_ext}}_{{lmul_suffix}}(inputs1);
\t{{msk_type}} m2 = mipp_set_k_{{dt_ext}}_{{lmul_suffix}}(inputs2);"""

LOAD_1ARG_MASK = """\t{{msk_type}} m1 = mipp_set_k_{{dt_ext}}_{{lmul_suffix}}(inputs1);"""
LOAD_1SCALAR_MASK = """\t{{msk_type}} m1 = mipp_set1_k_{{dt_ext}}_{{lmul_suffix}}(input1);"""
LOAD_SET0_MASK = """\t{{msk_type}} m1 = mipp_set0_k_{{dt_ext}}_{{lmul_suffix}}();"""

LOAD_SET1_2ARGS_REG = """\t{{reg_type}} r1 = mipp_set1_{{dt_ext}}_{{lmul_suffix}}(1); \n\t{{reg_type}} r2 = mipp_set1_{{dt_ext}}_{{lmul_suffix}}(2);"""

LOAD_3ARGS_REG = """\t{{reg_type}} r1 = mipp_load_{{dt_ext}}_{{lmul_suffix}}(inputs1);
\t{{reg_type}} r2 = mipp_load_{{dt_ext}}_{{lmul_suffix}}(inputs2);
\t{{reg_type}} r3 = mipp_load_{{dt_ext}}_{{lmul_suffix}}(inputs3);"""

LOAD_CAST_2ARGS = """\t{{reg1_type}} r1 = mipp_load_{{dt1_ext}}_{{lmul_suffix}}(inputs1);"""
LOAD_CAST_2ARGS_MASK = """\t{{msk1_type}} m1 = mipp_set_k_{{dt1_ext}}_{{lmul_suffix}}(inputs1);"""

# --------------------------------------------
# OPERATIONS (suffix)
# --------------------------------------------
OP_REG_NOOP = """\t{{reg_type}} r3 = r1;"""
OP_REG_UNOP = """\t{{reg_type}} r3 = mipp_{{func}}_{{dt_ext}}_{{lmul_suffix}}(r1);"""
OP_REG_BINOP = """\t{{reg_type}} r3 = mipp_{{func}}_{{dt_ext}}_{{lmul_suffix}}(r1, r2);"""

OP_CMP_2REG = """\t{{msk_type}} m3 = mipp_{{func}}_{{dt_ext}}_{{lmul_suffix}}(r1, r2); {{reg_type}} r3 = mipp_toreg_{{dt_ext}}_{{lmul_suffix}}(m3);"""

OP_STORE = """\tmipp_store_{{dt_ext}}_{{lmul_suffix}}(inputs2, r1);"""

OP_TOREG = """\t{{reg_type}} r3 = mipp_toreg_{{dt_ext}}_{{lmul_suffix}}(m1);"""

OP_SCAL_UNOP = """\t{{dt_ext}}_t res = mipp_{{func}}_{{dt_ext}}_{{lmul_suffix}}(r1);"""

OP_3ARGS_2REG_1MSK = """\t{{reg_type}} r3 = mipp_{{func}}_{{dt_ext}}_{{lmul_suffix}}(r1, r2, m1);"""
OP_3ARGS_1MSK_2REG = """\t{{reg_type}} r3 = mipp_{{func}}_{{dt_ext}}_{{lmul_suffix}}(m1, r1, r2);"""

OP_1ARG_1MASK = """\t{{msk_type}} m3 = mipp_{{func}}_{{dt_ext}}_{{lmul_suffix}}(m1); {{reg_type}} r3 = mipp_toreg_{{dt_ext}}_{{lmul_suffix}}(m3);"""
OP_2ARGS_2MASK = """\t{{msk_type}} m3 = mipp_{{func}}_{{dt_ext}}_{{lmul_suffix}}(m1, m2);\n\t{{reg_type}} r3 = mipp_toreg_{{dt_ext}}_{{lmul_suffix}}(m3);"""

OP_3ARGS_REG = """\t{{reg_type}} r4 = mipp_{{func}}_{{dt_ext}}_{{lmul_suffix}}(r1, r2, r3);"""

OP_CAST = """\t{{reg2_type}} r2 = mipp_cast_{{dt1_ext}}_{{dt2_ext}}_{{lmul_suffix}}(r1);"""
OP_CAST_MSK = """\t{{msk2_type}} m2 = mipp_cast_k_{{dt1_ext}}_{{dt2_ext}}_{{lmul_suffix}}(m1);"""

# --------------------------------------------
# OPERATION IN LOOP BODY (unchanged)
# ------------------------------------------
LB_SET_OP = """\t\t{{dt_ext}}_t res = inputs1[i];"""
LB_SET_SCALAR_OP = """\t\t{{dt_ext}}_t res = input1;"""
LB_REG_BINOP = """\t\t{{dt_ext}}_t res = inputs1[i] {{op}} inputs2[i];"""
LB_CMP_2REG = """\t\tbool res = inputs1[i] {{op}} inputs2[i];"""
LB_CAST_2ARGS = """\t\t{{dt2_ext}}_t res = inputs2[i];"""

LB_REG_BINOP_FLOAT_WORKAROUND = """{% if is_int %}""" + LB_REG_BINOP + """{% else %}
        \t{{dt_ext}}_t res = std::bit_cast<{{dt_ext}}_t,uint{{type_size}}_t>(
\t\t\t\tstd::bit_cast<uint{{type_size}}_t,{{dt_ext}}_t>(inputs1[i]) 
\t\t\t\t{{op}} 
\t\t\t\tstd::bit_cast<uint{{type_size}}_t,{{dt_ext}}_t>(inputs2[i]));{% endif %}"""

# --------------------------------------------
# ASSERTS IN LOOP BODY (unchanged)
# ------------------------------------------
AS_REG_BINOP = """\t\tREQUIRE(mipp_get_{{dt_ext}}_{{lmul_suffix}}(r3, i) == res);"""
AS_CMP_2REG = """\t\tif(res) REQUIRE(mipp_get_{{dt_ext}}_{{lmul_suffix}}(r3, i) !=  ({{dt_ext}}_t)0); else REQUIRE(mipp_get_{{dt_ext}}_{{lmul_suffix}}(r3, i) == 0);"""
AS_LOAD = """\t\tREQUIRE(mipp_get_{{dt_ext}}_{{lmul_suffix}}(r1, i) == res);"""
AS_STORE = """\t\tREQUIRE(inputs2[i] == res);"""
AS_3ARGS = """\t\tREQUIRE(mipp_get_{{dt_ext}}_{{lmul_suffix}}(r4, i) == res);"""

AS_CAST_2ARGS = """\t\tREQUIRE(mipp_get_{{dt2_ext}}(r2, i) == res);"""
AS_CAST_2ARGS_MSK = """\t\tif(res) REQUIRE(mipp_get_k_{{dt2_ext}}(m2, i) != 0); else REQUIRE(mipp_get_k_{{dt2_ext}}(m2, i) == 0);"""

AS_REG_BINOP_FLOAT_WORKAROUND = """{% if is_int %}""" + AS_REG_BINOP + """{% else %}
\n\t\tREQUIRE(std::bit_cast<uint{{type_size}}_t,{{dt_ext}}_t>(mipp_get_{{dt_ext}}_{{lmul_suffix}}(r3, i))\
\n\t\t\t==
\t\t\tstd::bit_cast<uint{{type_size}}_t,{{dt_ext}}_t>(res) );
{% endif %}"""

AS_CMP_BINOP_FLOAT_WORKAROUND = """{% if is_int %}""" + AS_CMP_2REG + """{% else %}
\n\t\tif(res) REQUIRE(std::bit_cast<uint{{type_size}}_t,{{dt_ext}}_t>(mipp_get_{{dt_ext}}_{{lmul_suffix}}(r3, i))\n\t\t\t!= 0);
else REQUIRE(std::bit_cast<uint{{type_size}}_t,{{dt_ext}}_t>(mipp_get_{{dt_ext}}_{{lmul_suffix}}(r3, i)) == 0);
{% endif %}"""

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
    # SHAPE_RET_MSK_2ARGS_REG: TemplateParts(
    #     func_decl=FUNC_DECL,
    #     decl=DECL_2ARGS,
    #     init=INIT_2ARGS,
    #     load=LOAD_2ARGS_REG,
    #     operation=OP_CMP_2REG,
    #     loop_body=LB_CMP_2REG,
    #     loop_assert=AS_CMP_2REG,
    # ),
    # SHAPE_RET_REG_1ARG_PTR: TemplateParts(
    #     func_decl=FUNC_DECL,
    #     decl=DECL_1ARG,
    #     init=INIT_1ARG,
    #     load=LOAD_1ARG_REG,
    #     operation="",
    #     loop_body=LB_SET_OP,
    #     loop_assert=AS_LOAD,
    # ),
    # SHAPE_RET_VOID_2ARGS_PTR_REG: TemplateParts(
    #     func_decl=FUNC_DECL,
    #     decl=DECL_2ARGS_FOR_STORE,
    #     init=INIT_1ARG,
    #     load=LOAD_1ARG_REG,
    #     operation=OP_STORE,
    #     loop_body=LB_SET_OP,
    #     loop_assert=AS_STORE,
    # ),
    # SHAPE_RET_REG_1ARG_NELE: TemplateParts(
    #     func_decl=FUNC_DECL,
    #     decl=DECL_1ARG,
    #     init=INIT_1ARG,
    #     load="""\t{{reg_type}} r1 = mipp_{{func}}_{{dt_ext}}_{{lmul_suffix}}(inputs1);""",
    #     operation=OP_REG_NOOP,
    #     loop_body=LB_SET_OP,
    #     loop_assert=AS_REG_BINOP,
    # ),
    # SHAPE_RET_MSK_1ARG_NELE: TemplateParts(
    #     func_decl=FUNC_DECL,
    #     decl=DECL_1ARG_INT32,
    #     init=INIT_1ARG,
    #     load=LOAD_1ARG_MASK,
    #     operation=OP_TOREG,
    #     loop_body=LB_SET_OP,
    #     loop_assert=AS_CMP_2REG,
    # ),
    # SHAPE_RET_REG_1ARG_VAL: TemplateParts(
    #     func_decl=FUNC_DECL,
    #     decl=DECL_1ARG_SCALAR,
    #     init="",
    #     load=LOAD_1SCALAR_REG,
    #     operation=OP_REG_NOOP,
    #     loop_body=LB_SET_SCALAR_OP,
    #     loop_assert=AS_REG_BINOP,
    # ),
    # SHAPE_RET_MSK_1ARG_I32: TemplateParts(
    #     func_decl=FUNC_DECL,
    #     decl=DECL_1ARG_SCALAR_INT32,
    #     init="",
    #     load=LOAD_1SCALAR_MASK,
    #     operation=OP_TOREG,
    #     loop_body=LB_SET_SCALAR_OP,
    #     loop_assert=AS_CMP_2REG,
    # ),
    # SHAPE_RET_REG_0ARG: TemplateParts(
    #     func_decl=FUNC_DECL,
    #     decl=DECL_0ARGS,
    #     init="",
    #     load=LOAD_SET0_REG,
    #     operation=OP_REG_NOOP,
    #     loop_body="\t\t{{dt_ext}}_t res = 0;",
    #     loop_assert=AS_REG_BINOP,
    # ),
    # SHAPE_RET_MSK_0ARG: TemplateParts(
    #     func_decl=FUNC_DECL,
    #     decl=DECL_0ARGS,
    #     init="",
    #     load=LOAD_SET0_MASK,
    #     operation=OP_TOREG,
    #     loop_body="\t\t{{dt_ext}}_t res = 0;",
    #     loop_assert=AS_CMP_2REG,
    # ),
    # SHAPE_RET_VAL_2ARGS_REG_VAL: TemplateParts(
    #     func_decl=FUNC_DECL,
    #     decl=DECL_1ARG,
    #     init=INIT_1ARG,
    #     load=LOAD_1ARG_REG,
    #     operation=OP_REG_NOOP,
    #     loop_body=LB_SET_OP,
    #     loop_assert=AS_REG_BINOP,
    # ),
    # SHAPE_RET_VAL_2ARGS_MSK_VAL: TemplateParts(
    #     func_decl=FUNC_DECL,
    #     decl=DECL_1ARG_INT32,
    #     init=INIT_1ARG,
    #     load=LOAD_1ARG_MASK,
    #     operation=OP_TOREG,
    #     loop_body=LB_SET_OP,
    #     loop_assert=AS_CMP_2REG,
    # ),
    # SHAPE_RET_VAL_1ARG_REG: TemplateParts(
    #     func_decl=FUNC_DECL,
    #     decl=DECL_1ARG,
    #     init=INIT_1ARG,
    #     load=LOAD_1ARG_REG,
    #     operation=OP_SCAL_UNOP,
    #     loop_body="",
    #     loop_assert="\t\tREQUIRE(res == inputs1[0]);",
    # ),
    # SHAPE_RET_REG_3ARGS_2REG_1MSK: TemplateParts(
    #     func_decl=FUNC_DECL,
    #     decl=DECL_1ARG_INT32,
    #     init=INIT_1ARG,
    #     load=LOAD_1ARG_MASK + "\n" + LOAD_SET1_2ARGS_REG,
    #     operation=OP_3ARGS_2REG_1MSK,
    #     loop_body="\t\t{{dt_ext}}_t res = mipp_get_k_{{dt_ext}}(m1, i) ? mipp_get_{{dt_ext}}_{{lmul_suffix}}(r1, i) : mipp_get_{{dt_ext}}_{{lmul_suffix}}(r2, i);",
    #     loop_assert=AS_REG_BINOP,
    # ),
    # SHAPE_RET_MSK_2ARGS_MSK: TemplateParts(
    #     func_decl=FUNC_DECL,
    #     decl=DECL_2ARGS_INT32 + DECL_G_SNIPPET,
    #     init=INIT_2ARGS_DIS,
    #     load=LOAD_2ARGS_MASK,
    #     operation=OP_2ARGS_2MASK,
    #     loop_body=LB_REG_BINOP,
    #     loop_assert=AS_CMP_2REG,
    # ),
    # SHAPE_RET_REG_1ARG_REG: TemplateParts(
    #     func_decl=FUNC_DECL,
    #     decl=DECL_1ARG,
    #     init=INIT_1ARG,
    #     load=LOAD_1ARG_REG,
    #     operation=OP_REG_UNOP,
    #     loop_body=LB_SET_OP,
    #     loop_assert=AS_REG_BINOP,
    # ),
    # SHAPE_RET_MSK_1ARG_MSK: TemplateParts(
    #     func_decl=FUNC_DECL,
    #     decl=DECL_1ARG_INT32 + DECL_G_SNIPPET,
    #     init=INIT_1ARG_DIS,
    #     load=LOAD_1ARG_MASK,
    #     operation=OP_1ARG_1MASK,
    #     loop_body=LB_SET_OP,
    #     loop_assert=AS_CMP_2REG,
    # ),
    # SHAPE_RET_REG_1ARG_MSK: TemplateParts(
    #     func_decl=FUNC_DECL,
    #     decl=DECL_1ARG_INT32 + DECL_G_SNIPPET,
    #     init=INIT_1ARG_DIS,
    #     load=LOAD_1ARG_MASK,
    #     operation=OP_TOREG,
    #     loop_body=LB_SET_OP,
    #     loop_assert=AS_CMP_2REG,
    # ),
    # SHAPE_RET_REG_3ARGS_REG: TemplateParts(
    #     func_decl=FUNC_DECL,
    #     decl=DECL_3ARGS,
    #     init=INIT_3ARGS,
    #     load=LOAD_3ARGS_REG,
    #     operation=OP_3ARGS_REG,
    #     loop_body="",
    #     loop_assert=AS_3ARGS,
    # ),
    # SHAPE_RET_I32_2ARGS_MSK: TemplateParts(
    #     func_decl=FUNC_DECL,
    #     decl="",
    #     init="",
    #     load="\t{{msk_type}} m1 = mipp_set1_k_{{dt_ext}}_{{lmul_suffix}}(1); \n\t{{msk_type}} m2 = mipp_set1_k_{{dt_ext}}_{{lmul_suffix}}(0);",
    #     operation="",
    #     loop_body="",
    #     loop_assert="\tREQUIRE(mipp_testz_{{dt_ext}}_{{lmul_suffix}}(m1, m1) == 0);\n\tREQUIRE(mipp_testz_{{dt_ext}}_{{lmul_suffix}}(m2, m2) != 0);",
    # ),
    # SHAPE_RET_I32_1ARG_MSK: TemplateParts(
    #     func_decl=FUNC_DECL,
    #     decl="",
    #     init="",
    #     load="\t{{msk_type}} m1 = mipp_set1_k_{{dt_ext}}_{{lmul_suffix}}(1); \n\t{{msk_type}} m2 = mipp_set1_k_{{dt_ext}}_{{lmul_suffix}}(0);",
    #     operation="",
    #     loop_body="",
    #     loop_assert="\tREQUIRE(mipp_testz_2_{{dt_ext}}_{{lmul_suffix}}(m1) == 0);\n\tREQUIRE(mipp_testz_2_{{dt_ext}}_{{lmul_suffix}}(m2) != 0);",
    # ),
    # SHAPE_RET_REG_3ARGS_1MSK_2REG: TemplateParts(
    #     func_decl=FUNC_DECL,
    #     decl=DECL_1ARG_INT32,
    #     init=INIT_1ARG,
    #     load=LOAD_1ARG_MASK + "\n" + LOAD_SET1_2ARGS_REG,
    #     operation=OP_3ARGS_1MSK_2REG,
    #     loop_body="\t\t{{dt_ext}}_t res = mipp_get_k_{{dt_ext}}(m1, i) ? 3 : 0;",
    #     loop_assert=AS_REG_BINOP,
    # ),
    # SHAPE_RET_MSK_1ARG_REG: TemplateParts(
    #     func_decl=FUNC_DECL,
    #     decl=DECL_1ARG,
    #     init=INIT_1ARG,
    #     load=LOAD_1ARG_REG,
    #     operation="\t{{msk_type}} m1 = mipp_tomsk_{{dt_ext}}_{{lmul_suffix}}(r1);\n{{reg_type}} r3 = mipp_toreg_{{dt_ext}}_{{lmul_suffix}}(m1);",
    #     loop_body="\t\t{{dt_ext}}_t res = inputs1[i] ? 1 : 0;",
    #     loop_assert=AS_CMP_2REG,
    # ),
    
    # #maskzld
    # SHAPE_RET_REG_2ARGS_MASK_PTR : TemplateParts(
    #     func_decl="",
    #     decl="",
    #     init="",
    #     load="",
    #     operation="",
    #     loop_body="",
    #     loop_assert="",
    # ),
    
    # #maskst
    # SHAPE_RET_VOID_3ARGS_PTR_MSK_REG : TemplateParts(
    #     func_decl="",
    #     decl="",
    #     init="",
    #     load="",
    #     operation="",
    #     loop_body="",
    #     loop_assert="",
    # ),

}

deny = set()
LAYER_OVERRIDES = {
    "andnb": {
        "loop_body": "{% if is_int %}" + "\t\t{{dt_ext}}_t res = ~(inputs1[i]) & (inputs2[i]);" +
"{% else %}" + """\t{{dt_ext}}_t res = std::bit_cast<{{dt_ext}}_t,uint{{type_size}}_t>(
\t\t\t~std::bit_cast<uint{{type_size}}_t,{{dt_ext}}_t>(inputs1[i]) 
\t\t\t&
\t\t\tstd::bit_cast<uint{{type_size}}_t,{{dt_ext}}_t>(inputs2[i]) );\n""" + """{% endif %}""",
        "loop_assert": AS_REG_BINOP_FLOAT_WORKAROUND,
    },
    
#     "andnb_k": {
#         "loop_body": """\t\t{{dt_ext}}_t res = ~(inputs1[i]) & (inputs2[i]);"""
#     },

#     "sub": {
#         "init": INIT_2ARGS_NOUFLOW
#     },

#     "div" : {
#         "loop_assert": """\tREQUIRE(
# #if defined(MIPP_NEON) && !defined(__aarch64__)
# 			std::abs(mipp_get_{{dt_ext}}_{{lmul_suffix}}(r3, i) - res) < 1e-2
# #else
# 			mipp_get_{{dt_ext}}_{{lmul_suffix}}(r3, i) == res
# #endif
# 		);""",
# 	},
    
#     "notb": {
#         "loop_body": "{%if is_int %}"+"""\t\t{{dt_ext}}_t res = ~(inputs1[i]);"""+
# """{% else %}""" + """\t{{dt_ext}}_t res = std::bit_cast<{{dt_ext}}_t,uint{{type_size}}_t>(
# \t\t\t~std::bit_cast<uint{{type_size}}_t,{{dt_ext}}_t>(inputs1[i]));\n""" + """{% endif %}""",
#         "loop_assert": AS_REG_BINOP_FLOAT_WORKAROUND,
#     },
    
#     "notb_k": {
#         "loop_body": """{%if is_int %}""" + """\t\t{{dt_ext}}_t res = ~(inputs1[i]);""" 
# + """{% else %} 
# uint{{type_size}}_t expected_bits = (inputs1[i] != 0)
#   ? 0
#   : -1;

# uint{{type_size}}_t got_bits = std::bit_cast<uint{{type_size}}_t>(mipp_get_float{{type_size}}(r3, i));
# {%endif%}""",
#         "loop_assert": "{% if is_int %}" + AS_REG_BINOP + "{% else %}REQUIRE( (!(!(got_bits))) == (!(!(expected_bits))) ); {% endif %}",
#     },
    
#     "hadd": {
#         "loop_body": """\t{{dt_ext}}_t res = 0; uint64_t ures = 0;
# \tfor(int j = 0; j < vectorSize; j++){
# \t\tres {{op}} inputs1[j];
# \t\tures{{op}} inputs1[j];
# \t}""",
#         "loop_assert": """\tif(ures == (uint64_t)res) REQUIRE(mipp_get_{{dt_ext}}_{{lmul_suffix}}(r3, 0) == res);""",
#     },
    
#     "hmul": {
#         "loop_body":"""\t{{dt_ext}}_t res = 1;
# \tfor(int j = 0; j < vectorSize; j++)
# \t\tres {{op}} inputs1[j];""",
#         "loop_assert": """\tREQUIRE(mipp_get_{{dt_ext}}_{{lmul_suffix}}(r3, 0) == res);""",
#     },
    
#     "hmin": {
#         "loop_body": """\t{{dt_ext}}_t res = inputs1[0];
# \tfor(int j = 1; j < vectorSize; j++)
# \t\tres = std::min(res, inputs1[j]);""",
#         "loop_assert": """\tREQUIRE(mipp_get_{{dt_ext}}_{{lmul_suffix}}(r3, 0) == res);""",
#     },
    
    
#     "hmax": {
#         "loop_body": """\t{{dt_ext}}_t res = inputs1[0];
# \tfor(int j = 1; j < vectorSize; j++)
# \t\tres = std::max(res, inputs1[j]);""",
#         "loop_assert": """\tREQUIRE(mipp_get_{{dt_ext}}_{{lmul_suffix}}(r3, 0) == res);""",
#     },
    
#     "fmadd": {
#         "loop_body": """\t\t{{dt_ext}}_t res = inputs1[i] * inputs2[i] + inputs3[i];""",
#     },
    
#     "fnmadd": {
#         "loop_body": """\t\t{{dt_ext}}_t res = -(inputs1[i] * inputs2[i]) + inputs3[i];""",
#     },
    
#     "fmsub": {
#         "loop_body": """\t\t{{dt_ext}}_t res = inputs1[i] * inputs2[i] - inputs3[i];""",
#     },
    
#     "fnmsub": {
#         "loop_body": """\t\t{{dt_ext}}_t res = -(inputs1[i] * inputs2[i]) - inputs3[i];""",
#     },
    
    "max" : {
        "loop_body": """\t\t{{dt_ext}}_t res = std::max(inputs1[i], inputs2[i]);""",
    },
    "min" : {
        "loop_body": """\t\t{{dt_ext}}_t res = std::min(inputs1[i], inputs2[i]);""",
    },
    
#     "sqrt" : {
#         "loop_body": """\t\t{{dt_ext}}_t res = std::sqrt(inputs1[i]);""",
#     },
    
#     "rsqrt" : {
#         "loop_body": """\t\t{{dt_ext}}_t res = 1.0 / std::sqrt(inputs1[i]);""",
#         "loop_assert": """\tREQUIRE(std::abs(mipp_get_{{dt_ext}}_{{lmul_suffix}}(r3, i) - res) < 1e-2);""",
#     },
    
#     #msb is most significant BIT not byte.
#     #the function returns msb of a lane & 0x8 etc
#     "msb" : {
#         "loop_body": "{% if is_int %}" + "\t{{dt_ext}}_t res = inputs1[i] & (({{dt_ext}}_t)1 << (sizeof({{dt_ext}}_t)*8 - 1));"
#         + "{% else %}" + """\t{{dt_ext}}_t res = 
#         std::bit_cast<{{dt_ext}}_t,uint{{type_size}}_t>(
# \t\t\tstd::bit_cast<uint{{type_size}}_t, {{dt_ext}}_t>(inputs1[i])
# \t\t\t&((uint{{type_size}}_t)1 << (sizeof({{dt_ext}}_t)*8 - 1))
# \t\t);\n""" + """{% endif %}""",
#         "loop_assert": AS_REG_BINOP_FLOAT_WORKAROUND,
#     },
    
#     "hadd_to_scal": {
#         "loop_body": """\t{{dt_ext}}_t res1 = 0; uint64_t ures1 = 0;
# \tfor(int j = 0; j < vectorSize; j++){
# \t\tres1 += inputs1[j];
# \t\tures1 += inputs1[j];
# \t}""",
#         "loop_assert": """\tif((uint64_t)res1 == ures1) REQUIRE(res == res1);""",
#     },
    
#     "cast": {
#         "func_decl": """void test_cmipp_cast_{{dt1_ext}}_{{dt2_ext}}(){""",
#         "decl": DECL_CAST_2ARGS,
#         "init": INIT_CAST_2ARGS,
#         "load": LOAD_CAST_2ARGS,
#         "operation": OP_CAST,
#         "loop_body": """\tfor(size_t i = 0; i < vectorSize * sizeof({{dt1_ext}}_t) / sizeof({{dt2_ext}}_t); i++){\n"""+ LB_CAST_2ARGS,
#         "loop_assert": AS_CAST_2ARGS+ "\n\t}",
#     },
    
#     "cast_k": {
#         "func_decl": """void test_cmipp_cast_k_{{dt1_ext}}_{{dt2_ext}}(){""",
#         "decl": DECL_CAST_2ARGS_MSK,
#         "init": INIT_CAST_2ARGS,
#         "load": LOAD_CAST_2ARGS_MASK,
#         "operation": OP_CAST_MSK,
#         "loop_body": """\tfor(size_t i = 0; i < vectorSize * sizeof({{dt1_ext}}_t) / sizeof({{dt2_ext}}_t); i++){\n"""+ LB_CAST_2ARGS,
#         "loop_assert": AS_CAST_2ARGS_MSK + "\n\t}",
#     },
    
    #add support for float via {% is_float %}
    "andb": {
        "loop_body" : LB_REG_BINOP_FLOAT_WORKAROUND,
        "loop_assert" : AS_REG_BINOP_FLOAT_WORKAROUND
    },
    "orb": {
        "loop_body" : LB_REG_BINOP_FLOAT_WORKAROUND,
        "loop_assert" : AS_REG_BINOP_FLOAT_WORKAROUND
    },
    "xorb": {
        "loop_body" : LB_REG_BINOP_FLOAT_WORKAROUND,
        "loop_assert" : AS_REG_BINOP_FLOAT_WORKAROUND
    },
    
#     "round": {
#         "init" : """\tstd::iota(inputs1, inputs1 + vectorSize, 1);
# \tstd::mt19937 g;
# std::uniform_real_distribution<float> dis(0.0, 1.0);
# \tfor(int i = 0; i < vectorSize; i++)
# \t{
# \t\tinputs1[i] += dis(g);
# \t}""",
#         "loop_body": """\t\t{{dt_ext}}_t res = std::round(inputs1[i]);""",
#     },
#     "div2": {
#         "loop_body": """\t\t{{dt_ext}}_t res = inputs1[i] / 2;""",
#     },
    
#     "div4": {
#         "loop_body": """\t\t{{dt_ext}}_t res = inputs1[i] / 4;""",
#     },
}

NO_LOOP_FUNCS = {"hadd", "hmul", "hmin", "hmax",
                 "hadd_to_scal", "getfirst", "testz",
                 "testz_2", "cast", "cast_k"}

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
    for f in NO_LOOP_FUNCS:
        if f in gen_dict:
            gen_dict[f]["template"] = GENERIC_NO_LOOP
    return gen_dict

gen_test_dict_lmul = build_layer_gen_test_dict(
    layer_name="c_lmul",
    template=GENERIC_FOR_LOOP,
    mipp_funcs=copy.deepcopy(mipp_funcs),
    shape_templates=shape_templates,
    deny_funcs=deny,
)

gen_test_dict_lmul = apply_overrides(gen_test_dict_lmul)