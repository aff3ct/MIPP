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
    SHAPE_RET_MSK_1ARG_NELE,      # set_k
    SHAPE_RET_REG_1ARG_VAL,       # set1 only
    SHAPE_RET_MSK_1ARG_I32,       # set1_k
    SHAPE_RET_REG_0ARG,           # set0
    SHAPE_RET_MSK_0ARG,           # set0_k
    SHAPE_RET_VAL_2ARGS_REG_VAL,  # get only
    SHAPE_RET_VAL_2ARGS_MSK_VAL,  # get_k only
    SHAPE_RET_VAL_1ARG_REG,
    SHAPE_RET_REG_3ARGS_2REG_1MSK,    # blend only
    SHAPE_RET_MSK_2ARGS_MSK,          # andb_k orb_k xorb_k andnb_k
    SHAPE_RET_REG_1ARG_REG,           # notb, sqrt, cast
    SHAPE_RET_MSK_1ARG_MSK,           # notb_k, cast_k
    SHAPE_RET_REG_1ARG_MSK,           # toreg only
    SHAPE_RET_REG_3ARGS_REG,          # fmadd, fmsub
    SHAPE_RET_I32_2ARGS_MSK,          # testz
    SHAPE_RET_I32_1ARG_MSK,           # testz2
    SHAPE_RET_REG_3ARGS_1MSK_2REG,    # maskz_add only
    SHAPE_RET_MSK_1ARG_REG,           # tomsk only
    SHAPE_RET_REG_2ARGS_MASK_PTR,     # maskz load only
    SHAPE_RET_VOID_3ARGS_PTR_MSK_REG, # mask store (maskst) only
)

# --------------------------
# C fragments (mask variants)
# --------------------------

# Mask kind: "mask", "maskz", or "masks"
# Note: we keep the suffix naming consistent with the existing generator conventions:
#   mipp_<func>_<dt>_mask / _maskz / _masks

# --------------------------------------------
# FN decl
# --------------------------------------------
FUNC_DECL = """void test_cmipp_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}(){"""

# --------------------------------------------
# SCALAR VEC DECL
# --------------------------------------------
DECL_VECTOR_SIZE = "\tconst int vectorSize = {{size}} * {{lmul_coeff}};"

DECL_0ARGS = DECL_VECTOR_SIZE
DECL_1ARG = DECL_VECTOR_SIZE + """ {{dt_ext}}_t inputs1[vectorSize];"""
DECL_1ARG_INT32 = DECL_VECTOR_SIZE + """ int32_t inputs1[vectorSize];"""
DECL_1ARG_SCALAR = DECL_VECTOR_SIZE + """ \t{{dt_ext}}_t input1 = 12;"""
DECL_1ARG_SCALAR_INT32 = DECL_VECTOR_SIZE + """ \tint32_t input1 = 12;"""

DECL_2ARGS_FOR_STORE = DECL_VECTOR_SIZE + """\n\t{{dt_ext}}_t inputs1[vectorSize],inputs2[vectorSize];"""
DECL_2ARGS = DECL_VECTOR_SIZE + """\n\t{{dt_ext}}_t inputs1[vectorSize],inputs2[vectorSize];"""
DECL_2ARGS_INT32 = DECL_VECTOR_SIZE + """\n\tint32_t inputs1[vectorSize],inputs2[vectorSize];"""

DECL_3ARGS = DECL_VECTOR_SIZE + """\n\t{{dt_ext}}_t inputs1[vectorSize],inputs2[vectorSize],inputs3[vectorSize];"""

DECL_G_SNIPPET = """\tstd::mt19937 g;\n\tstd::uniform_int_distribution<uint16_t> dis(0, 1);"""

DECL_CAST_2ARGS = (
    DECL_VECTOR_SIZE
    + """\n\t{{dt1_ext}}_t inputs1[vectorSize];\n\tconstexpr size_t bytes = sizeof(inputs1);\n\t{{dt2_ext}}_t inputs2[bytes / sizeof({{dt2_ext}}_t)];"""
)
DECL_CAST_2ARGS_MSK = (
    DECL_VECTOR_SIZE
    + """\n\tint32_t inputs1[vectorSize];\n\tconstexpr size_t bytes = sizeof(inputs1);\n\t{{dt2_ext}}_t inputs2[bytes / sizeof({{dt2_ext}}_t)];"""
)

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
# LOADS (masked: create m0 + optionally rsrc)
# --------------------------------------------
LOAD_2ARGS_REG = """\t{{reg_type}} r1 = mipp_load_{{dt_ext}}{{lmul_suffix}}(inputs1);
\t{{reg_type}} r2 = mipp_load_{{dt_ext}}{{lmul_suffix}}(inputs2);"""

LOAD_1ARG_REG = """\t{{reg_type}} r1 = mipp_load_{{dt_ext}}{{lmul_suffix}}(inputs1);"""
LOAD_1SCALAR_REG = """\t{{reg_type}} r1 = mipp_set1_{{dt_ext}}{{lmul_suffix}}(input1);"""
LOAD_SET0_REG = """\t{{reg_type}} r1 = mipp_set0_{{dt_ext}}{{lmul_suffix}}();"""

LOAD_2ARGS_MASK = """\t{{msk_type}} m1 = mipp_set_k_{{dt_ext}}{{lmul_suffix}}(inputs1);
\t{{msk_type}} m2 = mipp_set_k_{{dt_ext}}{{lmul_suffix}}(inputs2);"""

LOAD_1ARG_MASK = """\t{{msk_type}} m1 = mipp_set_k_{{dt_ext}}{{lmul_suffix}}(inputs1);"""
LOAD_1SCALAR_MASK = """\t{{msk_type}} m1 = mipp_set1_k_{{dt_ext}}{{lmul_suffix}}(input1);"""
LOAD_SET0_MASK = """\t{{msk_type}} m1 = mipp_set0_k_{{dt_ext}}{{lmul_suffix}}();"""

# Used for blend
LOAD_SET1_2ARGS_REG = """\t{{reg_type}} r1 = mipp_set1_{{dt_ext}}{{lmul_suffix}}(1);\n\t{{reg_type}} r2 = mipp_set1_{{dt_ext}}{{lmul_suffix}}(2);"""

LOAD_3ARGS_REG = """\t{{reg_type}} r1 = mipp_load_{{dt_ext}}{{lmul_suffix}}(inputs1);
\t{{reg_type}} r2 = mipp_load_{{dt_ext}}{{lmul_suffix}}(inputs2);
\t{{reg_type}} r3 = mipp_load_{{dt_ext}}{{lmul_suffix}}(inputs3);"""

LOAD_CAST_2ARGS = """\t{{reg1_type}} r1 = mipp_load_{{dt1_ext}}(inputs1);"""
LOAD_CAST_2ARGS_MASK = """\t{{msk1_type}} m1 = mipp_set_k_{{dt1_ext}}(inputs1);"""

# Mask inputs for masked wrappers:
# - choose mask m0 (we'll base it on inputs1 for convenience)
# - rsrc for "masks" kind (use r1 where available, otherwise set0)
LOAD_MASK_AND_RSRC_FROM_INPUTS = """\t{{msk_type}} mpred = mipp_set_k_{{dt_ext}}{{lmul_suffix}}(inputs1);
\t{{reg_type}} rsrc = mipp_set0_{{dt_ext}}{{lmul_suffix}}();"""

LOAD_MASK_AND_RSRC_FROM_REG1 = """\t{{msk_type}} mpred = mipp_set_k_{{dt_ext}}{{lmul_suffix}}(inputs1);
\t{{reg_type}} rsrc = r1;"""

# --------------------------------------------
# OPERATIONS (masked)
# --------------------------------------------
OP_REG_NOOP = """\t{{reg_type}} r3 = r1;"""
OP_REG_UNOP = """\t{{reg_type}} r3 = mipp_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}({{mask_args}} r1);"""
OP_REG_BINOP = """\t{{reg_type}} r3 = mipp_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}({{mask_args}} r1, r2);"""

OP_CMP_2REG = """\t{{msk_type}} m3 = mipp_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}({{mask_args}} r1, r2); {{reg_type}} r3 = mipp_toreg_{{dt_ext}}(m3);"""

OP_STORE = """\tmipp_store_{{dt_ext}}(inputs2, r1);"""

OP_TOREG = """\t{{reg_type}} r3 = mipp_toreg_{{dt_ext}}(m1);"""

OP_SCAL_UNOP = """\t{{dt_ext}}_t res = mipp_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}({{mask_args}} r1);"""

OP_3ARGS_2REG_1MSK = """\t{{reg_type}} r3 = mipp_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}({{mask_args}} r1, r2, m1);"""
OP_3ARGS_1MSK_2REG = """\t{{reg_type}} r3 = mipp_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}({{mask_args}} m1, r1, r2);"""

OP_1ARG_1MASK = """\t{{msk_type}} m3 = mipp_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}({{mask_args}} m1); {{reg_type}} r3 = mipp_toreg_{{dt_ext}}(m3);"""
OP_2ARGS_2MASK = """\t{{msk_type}} m3 = mipp_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}({{mask_args}} m1, m2);\n\t{{reg_type}} r3 = mipp_toreg_{{dt_ext}}(m3);"""

OP_3ARGS_REG = """\t{{reg_type}} r4 = mipp_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}({{mask_args}} r1, r2, r3);"""

OP_CAST = """\t{{reg2_type}} r2 = mipp_cast_{{dt1_ext}}_{{dt2_ext}}(r1);"""
OP_CAST_MSK = """\t{{msk2_type}} m2 = mipp_cast_k_{{dt1_ext}}_{{dt2_ext}}(m1);"""

# --------------------------------------------
# OPERATION IN LOOP BODY
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
# ASSERTS IN LOOP BODY
# ------------------------------------------
AS_REG_BINOP = """\t\tREQUIRE(mipp_get_{{dt_ext}}{{lmul_suffix}}(r3, i) == res);"""
AS_CMP_2REG = """\t\tif(res) REQUIRE(mipp_get_{{dt_ext}}{{lmul_suffix}}(r3, i) !=  ({{dt_ext}}_t)0); else REQUIRE(mipp_get_{{dt_ext}}{{lmul_suffix}}(r3, i) == 0);"""
AS_LOAD = """\t\tREQUIRE(mipp_get_{{dt_ext}}{{lmul_suffix}}(r1, i) == res);"""
AS_STORE = """\t\tREQUIRE(inputs2[i] == res);"""
AS_3ARGS = """\t\tREQUIRE(mipp_get_{{dt_ext}}{{lmul_suffix}}(r4, i) == res);"""

AS_CAST_2ARGS = """\t\tREQUIRE(mipp_get_{{dt2_ext}}(r2, i) == res);"""
AS_CAST_2ARGS_MSK = """\t\tif(res) REQUIRE(mipp_get_k_{{dt2_ext}}(m2, i) != 0); else REQUIRE(mipp_get_k_{{dt2_ext}}(m2, i) == 0);"""

AS_REG_BINOP_FLOAT_WORKAROUND = """{% if is_int %}""" + AS_REG_BINOP + """{% else %}
\n\t\tREQUIRE(std::bit_cast<uint{{type_size}}_t,{{dt_ext}}_t>(mipp_get_{{dt_ext}}{{lmul_suffix}}(r3, i))\
\n\t\t\t==
\t\t\tstd::bit_cast<uint{{type_size}}_t,{{dt_ext}}_t>(res) );
{% endif %}"""

AS_CMP_BINOP_FLOAT_WORKAROUND = """{% if is_int %}""" + AS_CMP_2REG + """{% else %}
\n\t\tif(res) REQUIRE(std::bit_cast<uint{{type_size}}_t,{{dt_ext}}_t>(mipp_get_{{dt_ext}}{{lmul_suffix}}(r3, i))\n\t\t\t!= 0);
else REQUIRE(std::bit_cast<uint{{type_size}}_t,{{dt_ext}}_t>(mipp_get_{{dt_ext}}{{lmul_suffix}}(r3, i)) == 0);
{% endif %}"""

# --------------------------------------------
# Shapes
# --------------------------------------------
shape_templates = {
    SHAPE_RET_REG_2ARGS_REG: TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_2ARGS,
        init=INIT_2ARGS,
        load=LOAD_2ARGS_REG + "\n" + LOAD_MASK_AND_RSRC_FROM_REG1,
        operation=OP_REG_BINOP,
        loop_body=LB_REG_BINOP,
        loop_assert=AS_REG_BINOP,
    ),
    SHAPE_RET_MSK_2ARGS_REG: TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_2ARGS,
        init=INIT_2ARGS,
        load=LOAD_2ARGS_REG + "\n" + LOAD_MASK_AND_RSRC_FROM_REG1,
        operation=OP_CMP_2REG,
        loop_body=LB_CMP_2REG,
        loop_assert=AS_CMP_2REG,
    ),
    SHAPE_RET_REG_1ARG_PTR: TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_1ARG,
        init=INIT_1ARG,
        load=LOAD_1ARG_REG + "\n" + LOAD_MASK_AND_RSRC_FROM_REG1,
        operation="",
        loop_body=LB_SET_OP,
        loop_assert=AS_LOAD,
    ),
    SHAPE_RET_VOID_2ARGS_PTR_REG: TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_2ARGS_FOR_STORE,
        init=INIT_1ARG,
        load=LOAD_1ARG_REG + "\n" + LOAD_MASK_AND_RSRC_FROM_REG1,
        operation=OP_STORE,
        loop_body=LB_SET_OP,
        loop_assert=AS_STORE,
    ),
    SHAPE_RET_REG_1ARG_NELE: TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_1ARG,
        init=INIT_1ARG,
        load="""\t{{reg_type}} r1 = mipp_{{func}}_{{dt_ext}}{{lmul_suffix}}(inputs1);\n""" + LOAD_MASK_AND_RSRC_FROM_REG1,
        operation=OP_REG_NOOP,
        loop_body=LB_SET_OP,
        loop_assert=AS_REG_BINOP,
    ),
    SHAPE_RET_MSK_1ARG_NELE: TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_1ARG_INT32,
        init=INIT_1ARG,
        load=LOAD_1ARG_MASK + "\n" + LOAD_MASK_AND_RSRC_FROM_INPUTS,
        operation=OP_TOREG,
        loop_body=LB_SET_OP,
        loop_assert=AS_CMP_2REG,
    ),
    SHAPE_RET_REG_1ARG_VAL: TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_1ARG_SCALAR,
        init="",
        load=LOAD_1SCALAR_REG + "\n" + LOAD_MASK_AND_RSRC_FROM_REG1,
        operation=OP_REG_NOOP,
        loop_body=LB_SET_SCALAR_OP,
        loop_assert=AS_REG_BINOP,
    ),
    SHAPE_RET_MSK_1ARG_I32: TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_1ARG_SCALAR_INT32,
        init="",
        load=LOAD_1SCALAR_MASK + "\n" + LOAD_MASK_AND_RSRC_FROM_INPUTS,
        operation=OP_TOREG,
        loop_body=LB_SET_SCALAR_OP,
        loop_assert=AS_CMP_2REG,
    ),
    SHAPE_RET_REG_0ARG: TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_0ARGS,
        init="",
        load=LOAD_SET0_REG + "\n" + LOAD_MASK_AND_RSRC_FROM_INPUTS,
        operation=OP_REG_NOOP,
        loop_body="\t\t{{dt_ext}}_t res = 0;",
        loop_assert=AS_REG_BINOP,
    ),
    SHAPE_RET_MSK_0ARG: TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_0ARGS,
        init="",
        load=LOAD_SET0_MASK + "\n" + LOAD_MASK_AND_RSRC_FROM_INPUTS,
        operation=OP_TOREG,
        loop_body="\t\t{{dt_ext}}_t res = 0;",
        loop_assert=AS_CMP_2REG,
    ),
    SHAPE_RET_VAL_2ARGS_REG_VAL: TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_1ARG,
        init=INIT_1ARG,
        load=LOAD_1ARG_REG + "\n" + LOAD_MASK_AND_RSRC_FROM_REG1,
        operation=OP_REG_NOOP,
        loop_body=LB_SET_OP,
        loop_assert=AS_REG_BINOP,
    ),
    SHAPE_RET_VAL_2ARGS_MSK_VAL: TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_1ARG_INT32,
        init=INIT_1ARG,
        load=LOAD_1ARG_MASK + "\n" + LOAD_MASK_AND_RSRC_FROM_INPUTS,
        operation=OP_TOREG,
        loop_body=LB_SET_OP,
        loop_assert=AS_CMP_2REG,
    ),
    SHAPE_RET_VAL_1ARG_REG: TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_1ARG,
        init=INIT_1ARG,
        load=LOAD_1ARG_REG + "\n" + LOAD_MASK_AND_RSRC_FROM_REG1,
        operation=OP_SCAL_UNOP,
        loop_body="",
        loop_assert="\t\tREQUIRE(res == inputs1[0]);",
    ),
    SHAPE_RET_REG_3ARGS_2REG_1MSK: TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_1ARG_INT32,
        init=INIT_1ARG,
        load=LOAD_1ARG_MASK + "\n" + LOAD_SET1_2ARGS_REG + "\n" + LOAD_MASK_AND_RSRC_FROM_INPUTS,
        operation=OP_3ARGS_2REG_1MSK,
        loop_body="\t\t{{dt_ext}}_t res = mipp_get_k_{{dt_ext}}{{lmul_suffix}}(m1, i) ? mipp_get_{{dt_ext}}{{lmul_suffix}}(r1, i) : mipp_get_{{dt_ext}}{{lmul_suffix}}(r2, i);",
        loop_assert=AS_REG_BINOP,
    ),
    SHAPE_RET_MSK_2ARGS_MSK: TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_2ARGS_INT32 + DECL_G_SNIPPET,
        init=INIT_2ARGS_DIS,
        load=LOAD_2ARGS_MASK + "\n" + LOAD_MASK_AND_RSRC_FROM_INPUTS,
        operation=OP_2ARGS_2MASK,
        loop_body=LB_REG_BINOP,
        loop_assert=AS_CMP_2REG,
    ),
    SHAPE_RET_REG_1ARG_REG: TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_1ARG,
        init=INIT_1ARG,
        load=LOAD_1ARG_REG + "\n" + LOAD_MASK_AND_RSRC_FROM_REG1,
        operation=OP_REG_UNOP,
        loop_body=LB_SET_OP,
        loop_assert=AS_REG_BINOP,
    ),
    SHAPE_RET_MSK_1ARG_MSK: TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_1ARG_INT32 + DECL_G_SNIPPET,
        init=INIT_1ARG_DIS,
        load=LOAD_1ARG_MASK + "\n" + LOAD_MASK_AND_RSRC_FROM_INPUTS,
        operation=OP_1ARG_1MASK,
        loop_body=LB_SET_OP,
        loop_assert=AS_CMP_2REG,
    ),
    SHAPE_RET_REG_1ARG_MSK: TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_1ARG_INT32 + DECL_G_SNIPPET,
        init=INIT_1ARG_DIS,
        load=LOAD_1ARG_MASK + "\n" + LOAD_MASK_AND_RSRC_FROM_INPUTS,
        operation=OP_TOREG,
        loop_body=LB_SET_OP,
        loop_assert=AS_CMP_2REG,
    ),
    SHAPE_RET_REG_3ARGS_REG: TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_3ARGS,
        init=INIT_3ARGS,
        load=LOAD_3ARGS_REG + "\n" + LOAD_MASK_AND_RSRC_FROM_REG1,
        operation=OP_3ARGS_REG,
        loop_body="",
        loop_assert=AS_3ARGS,
    ),
    SHAPE_RET_I32_2ARGS_MSK: TemplateParts(
        func_decl=FUNC_DECL,
        decl="",
        init="",
        load="\t{{msk_type}} m1 = mipp_set1_k_{{dt_ext}}{{lmul_suffix}}(1); \n\t{{msk_type}} m2 = mipp_set1_k_{{dt_ext}}{{lmul_suffix}}(0);\n"
        + LOAD_MASK_AND_RSRC_FROM_INPUTS,
        operation="",
        loop_body="",
        loop_assert="\tREQUIRE(mipp_testz_{{dt_ext}}{{lmul_suffix}}(m1, m1) == 0);\n\tREQUIRE(mipp_testz_{{dt_ext}}{{lmul_suffix}}(m2, m2) != 0);",
    ),
    SHAPE_RET_I32_1ARG_MSK: TemplateParts(
        func_decl=FUNC_DECL,
        decl="",
        init="",
        load="\t{{msk_type}} m1 = mipp_set1_k_{{dt_ext}}{{lmul_suffix}}(1); \n\t{{msk_type}} m2 = mipp_set1_k_{{dt_ext}}{{lmul_suffix}}(0);\n"
        + LOAD_MASK_AND_RSRC_FROM_INPUTS,
        operation="",
        loop_body="",
        loop_assert="\tREQUIRE(mipp_testz_2_{{dt_ext}}{{lmul_suffix}}(m1) == 0);\n\tREQUIRE(mipp_testz_2_{{dt_ext}}{{lmul_suffix}}(m2) != 0);",
    ),
    SHAPE_RET_REG_3ARGS_1MSK_2REG: TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_1ARG_INT32,
        init=INIT_1ARG,
        load=LOAD_1ARG_MASK + "\n" + LOAD_SET1_2ARGS_REG + "\n" + LOAD_MASK_AND_RSRC_FROM_INPUTS,
        operation=OP_3ARGS_1MSK_2REG,
        loop_body="\t\t{{dt_ext}}_t res = mipp_get_k_{{dt_ext}}{{lmul_suffix}}(m1, i) ? 3 : 0;",
        loop_assert=AS_REG_BINOP,
    ),
    SHAPE_RET_MSK_1ARG_REG: TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_1ARG,
        init=INIT_1ARG,
        load=LOAD_1ARG_REG + "\n" + LOAD_MASK_AND_RSRC_FROM_REG1,
        operation="\t{{msk_type}} m1 = mipp_tomsk_{{dt_ext}}{{lmul_suffix}}(r1);\n{{reg_type}} r3 = mipp_toreg_{{dt_ext}}{{lmul_suffix}}(m1);",
        loop_body="\t\t{{dt_ext}}_t res = inputs1[i] ? 1 : 0;",
        loop_assert=AS_CMP_2REG,
    ),
    # maskz load
    SHAPE_RET_REG_2ARGS_MASK_PTR: TemplateParts(
        func_decl="",
        decl="",
        init="",
        load="",
        operation="",
        loop_body="",
        loop_assert="",
    ),
    # mask store (maskst)
    SHAPE_RET_VOID_3ARGS_PTR_MSK_REG: TemplateParts(
        func_decl="",
        decl="",
        init="",
        load="",
        operation="",
        loop_body="",
        loop_assert="",
    ),
}

deny = set()

# Keep overrides structure (empty by default for mask layer; users can add later)
LAYER_OVERRIDES = {}

NO_LOOP_FUNCS = {"hadd", "hmul", "hmin", "hmax",
                 "hadd_to_scal", "getfirst", "testz",
                 "testz_2", "cast", "cast_k"}

def apply_overrides(gen_dict):
    for func, entry in gen_dict.items():
        ovr = LAYER_OVERRIDES.get(func)
        if not ovr:
            continue

        if "func_decl" in ovr:
            entry["proto"]["func_decl"] = ovr["func_decl"]
        if "decl" in ovr:
            entry["proto"]["decl"] = ovr["decl"]
        if "init" in ovr:
            entry["proto"]["init"] = ovr["init"]
        if "load" in ovr:
            entry["proto"]["load"] = ovr["load"]
        if "operation" in ovr:
            entry["proto"]["operation"] = ovr["operation"]
        if "loop_assert" in ovr:
            entry["proto"]["loop_assert"] = ovr["loop_assert"]
        if "loop_body" in ovr:
            entry["proto"]["loop_body"] = ovr["loop_body"]

    for f in NO_LOOP_FUNCS:
        if f in gen_dict:
            gen_dict[f]["template"] = GENERIC_NO_LOOP
    return gen_dict


gen_test_dict_mask = build_layer_gen_test_dict(
    layer_name="c_mask",
    template=GENERIC_FOR_LOOP,
    mipp_funcs=mipp_funcs,
    shape_templates=shape_templates,
    deny_funcs=deny,
)

# Note: this layer expects the caller (gen_mipp_tests.py) to render with:
#   mask_kind in {"mask","maskz","masks"}
#   mask_args in {"m0, ", "m0, ", "m0, rsrc, "} depending on mask_kind
gen_test_dict_mask = apply_overrides(gen_test_dict_mask)