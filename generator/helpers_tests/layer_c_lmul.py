import copy
from registry import mipp_funcs
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


    SHAPE_RET_REG_2ARGS_PTR_REG, #gather only
    SHAPE_RET_VOID_3ARGS_PTR_REG_REG, #scatter only

    SHAPE_RET_REG_2ARGS_REG_VAL # lshift, rshift


)

# --------------------------
# C fragments (suffix + coeff generic)
# --------------------------

# --------------------------------------------
# FN decl
# --------------------------------------------
FUNC_DECL = """void test_cmipp_{{func}}_{{dt_ext}}_{{lmul_suffix}}(){"""

FUNC_DECL_GATHER = """void test_cmipp_{{func}}_{{dt_ext}}_{{dt_ext}}_{{lmul_suffix}}(){"""
FUNC_DECL_SCATTER = """void test_cmipp_{{func}}_{{dt_ext}}_{{dt_ext}}_{{lmul_suffix}}(){"""

# --------------------------------------------
# SCALAR VEC DECL
# --------------------------------------------

DECL_CATCH_SEED = DECL_GET_CATCH_SEED = "\n\tstd::mt19937 seed(Catch::getSeed()+n);\n"
DECL_G_SNIPPET = """\tstd::mt19937 g;\n\tstd::uniform_int_distribution<uint16_t> dis(0, 1);"""


DECL_0ARGS = DECL_GET_CATCH_SEED + ""
DECL_1ARG = DECL_GET_CATCH_SEED + """ {{dt_ext}}_t inputs1[{{size}} * {{lmul_coeff}}];"""
DECL_1ARG_INT32 = DECL_GET_CATCH_SEED + """ int32_t inputs1[{{size}} * {{lmul_coeff}}];"""
DECL_1ARG_SCALAR = DECL_GET_CATCH_SEED + """ \t{{dt_ext}}_t input1 = 12;"""
DECL_1ARG_SCALAR_INT32 = DECL_GET_CATCH_SEED + """ \tint32_t input1 = 12;"""

DECL_2ARGS_FOR_STORE = DECL_GET_CATCH_SEED + """\n\t{{dt_ext}}_t inputs1[{{size}} * {{lmul_coeff}}],inputs2[{{size}} * {{lmul_coeff}}];"""
DECL_2ARGS = DECL_GET_CATCH_SEED + """{{dt_ext}}_t inputs1[{{size}} * {{lmul_coeff}}],inputs2[{{size}} * {{lmul_coeff}}];"""
DECL_2ARGS_INT32 = DECL_GET_CATCH_SEED + """int32_t inputs1[{{size}} * {{lmul_coeff}}],inputs2[{{size}} * {{lmul_coeff}}];"""
DECL_3ARGS = DECL_GET_CATCH_SEED + """{{dt_ext}}_t inputs1[{{size}} * {{lmul_coeff}}],inputs2[{{size}} * {{lmul_coeff}}],inputs3[{{size}} * {{lmul_coeff}}];"""


# cast: allocate inputs1 scaled by coeff; inputs2 size is computed from bytes (correctly scales)
DECL_CAST_2ARGS = DECL_GET_CATCH_SEED + """{{dt1_ext}}_t inputs1[{{size}} * {{lmul_coeff}}];\n\tconstexpr size_t bytes = sizeof(inputs1);\n\t{{dt2_ext}}_t inputs2[bytes / sizeof({{dt2_ext}}_t)];"""
DECL_CAST_2ARGS_MSK = DECL_GET_CATCH_SEED + """int32_t inputs1[{{size}} * {{lmul_coeff}}];\n\tconstexpr size_t bytes = sizeof(inputs1);\n\t{{dt2_ext}}_t inputs2[bytes / sizeof({{dt2_ext}}_t)];"""


# declare 1 dt array of dt type, another array of uint of the same size.
DECL_GATHER = DECL_GET_CATCH_SEED + """
{{dt_ext}}_t inputs1[{{size}} * {{lmul_coeff}}];
uint{{type_size}}_t indexes[{{size}} * {{lmul_coeff}}];
"""

DECL_SCATTER = DECL_GET_CATCH_SEED + """
{{dt_ext}}_t inputs1[{{size}} * {{lmul_coeff}}];
uint{{type_size}}_t indexes[{{size}} * {{lmul_coeff}}];
{{dt_ext}}_t outputs[{{size}} * {{lmul_coeff}}];
{{dt_ext}}_t outputs_scal[{{size}} * {{lmul_coeff}}];
"""

# --------------------------------------------
# SCALAR VEC INIT (unchanged)
# --------------------------------------------
INIT_2ARGS = """
\tfor(size_t i = 0; i < {{size}}* {{lmul_coeff}}; i++)
\t{
\t\tinputs1[i] = rnd::uniform<{{dt_ext}}_t>(seed);
\t\tinputs2[i] = rnd::uniform<{{dt_ext}}_t>(seed);
\t}
"""

INIT_1ARG = """
\tfor(size_t i = 0; i < {{size}} * {{lmul_coeff}}; i++)
\t{
\t\tinputs1[i] = rnd::uniform<{{dt_ext}}_t>(seed);
\t}
"""

INIT_2ARGS_NOUFLOW = INIT_2ARGS + """\tfor(size_t i = 0; i < {{size}} * {{lmul_coeff}}; i++)
\t{
\t\tinputs1[i] += inputs2[i];
\t}
"""


INIT_1ARG_DIS = """\tstd::iota(inputs1, inputs1 + {{size}} * {{lmul_coeff}}, 1);
\tfor(size_t i = 0; i < {{size}} * {{lmul_coeff}}; i++)
\t{
\t\tinputs1[i] = dis(g) ? -1 : 0;
\t}"""

INIT_2ARGS_DIS = """\tfor(size_t i = 0; i < {{size}} * {{lmul_coeff}}; i++)
\t{
\t\tinputs1[i] = dis(g) ? -1 : 0;
\t\tinputs2[i] = dis(g) ? -1 : 0;
\t}"""


INIT_3ARGS = """\tfor(size_t i = 0; i < {{size}} * {{lmul_coeff}}; i++)
\t{
\t\tinputs1[i] = rnd::uniform<{{dt_ext}}_t>(seed);
\t\tinputs2[i] = rnd::uniform<{{dt_ext}}_t>(seed);
\t\tinputs3[i] = rnd::uniform<{{dt_ext}}_t>(seed);
\t}
"""

INIT_CAST_2ARGS = """\tstd::iota(inputs1, inputs1 + {{size}} * {{lmul_coeff}}, 1);\n\tmemcpy(inputs2, inputs1, sizeof(inputs1));"""

# 1 array is random values, 1 is indexes that don't cross array boundaries
INIT_GATHER = """
\tfor(size_t i = 0; i < {{size}} * {{lmul_coeff}}; i++)
{
\t\tinputs1[i] = rnd::uniform<{{dt_ext}}_t>(seed);
\t\tindexes[i] = (i * rnd::uniform<uint{{type_size}}_t>(seed)) % ({{size}} * {{lmul_coeff}}); // ensure indexes are within bounds and not all the same
}
"""

INIT_SCATTER = """
\tfor(size_t i = 0; i < {{size}} * {{lmul_coeff}}; i++)
{
\t\tinputs1[i] = rnd::uniform<{{dt_ext}}_t>(seed);
\t\tindexes[i] = (i * rnd::uniform<uint{{type_size}}_t>(seed)) % ({{size}} * {{lmul_coeff}}); // ensure indexes are within bounds and not all the same
\t\toutputs[i] = 0;
\t\toutputs_scal[i] = 0;
}
"""

# --------------------------------------------
# LOADS (suffix)
# --------------------------------------------

LOAD_2ARGS_REG = """\t{{reg_type}} r1 = mipp_load_{{dt_ext}}_{{lmul_suffix}}(inputs1);
\t{{reg_type}} r2 = mipp_load_{{dt_ext}}_{{lmul_suffix}}(inputs2);
\t{{reg_type_scalar}} s1 = mipp_scalar_load_{{dt_ext}}_{{lmul_suffix}}(inputs1);
\t{{reg_type_scalar}} s2 = mipp_scalar_load_{{dt_ext}}_{{lmul_suffix}}(inputs2);
"""


LOAD_1ARG_REG = """\t{{reg_type}} r1 = mipp_load_{{dt_ext}}_{{lmul_suffix}}(inputs1);
\t{{reg_type_scalar}} s1 = mipp_scalar_load_{{dt_ext}}_{{lmul_suffix}}(inputs1);"""

LOAD_1SCALAR_REG = """\t{{reg_type}} r1 = mipp_set1_{{dt_ext}}_{{lmul_suffix}}(input1);
\t{{reg_type_scalar}} s1 = mipp_scalar_set1_{{dt_ext}}_{{lmul_suffix}}(input1);"""

LOAD_SET0_REG = """\t{{reg_type}} r1 = mipp_set0_{{dt_ext}}_{{lmul_suffix}}();
\t{{reg_type_scalar}} s1 = mipp_scalar_set0_{{dt_ext}}_{{lmul_suffix}}();"""

LOAD_2ARGS_MASK = """\t{{msk_type}} m1 = mipp_set_k_{{dt_ext}}_{{lmul_suffix}}(inputs1);
\t{{msk_type}} m2 = mipp_set_k_{{dt_ext}}_{{lmul_suffix}}(inputs2);
\t{{msk_type_scalar}} ms1 = mipp_scalar_set_k_{{dt_ext}}_{{lmul_suffix}}(inputs1);
\t{{msk_type_scalar}} ms2 = mipp_scalar_set_k_{{dt_ext}}_{{lmul_suffix}}(inputs2);"""

LOAD_1ARG_MASK = """\t{{msk_type}} m1 = mipp_set_k_{{dt_ext}}_{{lmul_suffix}}(inputs1);
\t{{msk_type_scalar}} ms1 = mipp_scalar_set_k_{{dt_ext}}_{{lmul_suffix}}(inputs1);"""

LOAD_1SCALAR_MASK = """\t{{msk_type}} m1 = mipp_set1_k_{{dt_ext}}_{{lmul_suffix}}(input1);
\t{{msk_type_scalar}} ms1 = mipp_scalar_set1_k_{{dt_ext}}_{{lmul_suffix}}(input1);"""

LOAD_SET0_MASK = """\t{{msk_type}} m1 = mipp_set0_k_{{dt_ext}}_{{lmul_suffix}}();
\t{{msk_type_scalar}} ms1 = mipp_scalar_set0_k_{{dt_ext}}_{{lmul_suffix}}();"""

LOAD_SET1_2ARGS_REG = """\t{{reg_type}} r1 = mipp_set1_{{dt_ext}}_{{lmul_suffix}}(1); \n\t{{reg_type}} r2 = mipp_set1_{{dt_ext}}_{{lmul_suffix}}(2);
\t{{reg_type_scalar}} s1 = mipp_scalar_set1_{{dt_ext}}_{{lmul_suffix}}(1); \n\t{{reg_type_scalar}} s2 = mipp_scalar_set1_{{dt_ext}}_{{lmul_suffix}}(2);"""

LOAD_3ARGS_REG = """\t{{reg_type}} r1 = mipp_load_{{dt_ext}}_{{lmul_suffix}}(inputs1);
\t{{reg_type}} r2 = mipp_load_{{dt_ext}}_{{lmul_suffix}}(inputs2);
\t{{reg_type}} r3 = mipp_load_{{dt_ext}}_{{lmul_suffix}}(inputs3);
\t{{reg_type_scalar}} s1 = mipp_scalar_load_{{dt_ext}}_{{lmul_suffix}}(inputs1);
\t{{reg_type_scalar}} s2 = mipp_scalar_load_{{dt_ext}}_{{lmul_suffix}}(inputs2);
\t{{reg_type_scalar}} s3 = mipp_scalar_load_{{dt_ext}}_{{lmul_suffix}}(inputs3);"""

LOAD_CAST_2ARGS = """\t{{reg1_type}} r1 = mipp_load_{{dt1_ext}}_{{lmul_suffix}}(inputs1);
\n\t{{reg1_scalar_type}} s1 = mipp_scalar_load_{{dt1_ext}}_{{lmul_suffix}}(inputs1);"""

LOAD_CAST_2ARGS_MASK = """\t{{msk1_type}} m1 = mipp_set_k_{{dt1_ext}}_{{lmul_suffix}}(inputs1);
\n\t{{msk1_scalar_type}} ms1 = mipp_scalar_set_k_{{dt1_ext}}_{{lmul_suffix}}(inputs1);"""

LOAD_GATHER = """
rvd_uint{{type_size}}_{{lmul_suffix}}_t ri1 = mipp_load_uint{{type_size}}_{{lmul_suffix}}(indexes);

rvd_scalar_uint{{type_size}}_{{lmul_suffix}}_t ris1 = mipp_scalar_load_uint{{type_size}}_{{lmul_suffix}}(indexes);
"""

LOAD_SCATTER = """
{{reg_type}} r1 = mipp_load_{{dt_ext}}_{{lmul_suffix}}(inputs1);
rvd_uint{{type_size}}_{{lmul_suffix}}_t ri1 = mipp_load_uint{{type_size}}_{{lmul_suffix}}(indexes);

{{reg_type_scalar}} rs1 = mipp_scalar_load_{{dt_ext}}_{{lmul_suffix}}(inputs1);
rvd_scalar_uint{{type_size}}_{{lmul_suffix}}_t ris1 = mipp_scalar_load_uint{{type_size}}_{{lmul_suffix}}(indexes);
"""

# --------------------------------------------
# OPERATIONS (suffix)
# --------------------------------------------

OP_REG_NOOP = """\t{{reg_type}} r3 = r1;\n\t{{reg_type_scalar}} s3 = s1;"""
OP_REG_UNOP = """\t{{reg_type}} r3 = mipp_{{func}}_{{dt_ext}}_{{lmul_suffix}}(r1);\n\t{{reg_type_scalar}} s3 = mipp_scalar_{{func}}_{{dt_ext}}_{{lmul_suffix}}(s1);"""

OP_REG_BINOP = """\t{{reg_type}} r3 = mipp_{{func}}_{{dt_ext}}_{{lmul_suffix}}(r1, r2);
\t{{reg_type_scalar}} s3 = mipp_scalar_{{func}}_{{dt_ext}}_{{lmul_suffix}}(s1, s2);
"""

OP_CMP_2REG = """\t{{msk_type}} m3 = mipp_{{func}}_{{dt_ext}}_{{lmul_suffix}}(r1, r2); {{reg_type}} r3 = mipp_toreg_{{dt_ext}}_{{lmul_suffix}}(m3);
{{msk_type_scalar}} ms3 = mipp_scalar_{{func}}_{{dt_ext}}_{{lmul_suffix}}(s1, s2); {{reg_type_scalar}} s3 = mipp_scalar_toreg_{{dt_ext}}_{{lmul_suffix}}(ms3);"""

# WRONG
OP_STORE = """\tmipp_store_{{dt_ext}}_{{lmul_suffix}}(inputs2, r1);\n\t//mipp_scalar_store_{{dt_ext}}_{{lmul_suffix}}(inputs2, s1);"""

OP_TOREG = """\t{{reg_type}} r3 = mipp_toreg_{{dt_ext}}_{{lmul_suffix}}(m1);\n\t{{reg_type_scalar}} s3 = mipp_scalar_toreg_{{dt_ext}}_{{lmul_suffix}}(ms1);"""

## Unused ?
OP_SCAL_UNOP = """\t{{dt_ext}}_t res = mipp_{{func}}_{{dt_ext}}_{{lmul_suffix}}(r1);\n\t{{dt_ext}}_t sres = mipp_scalar_{{func}}_{{dt_ext}}_{{lmul_suffix}}(s1);"""

OP_3ARGS_2REG_1MSK = """\t{{reg_type}} r3 = mipp_{{func}}_{{dt_ext}}_{{lmul_suffix}}(r1, r2, m1);
\t{{reg_type_scalar}} s3 = mipp_scalar_{{func}}_{{dt_ext}}_{{lmul_suffix}}(s1, s2, ms1);"""
OP_3ARGS_1MSK_2REG = """\t{{reg_type}} r3 = mipp_{{func}}_{{dt_ext}}_{{lmul_suffix}}(m1, r1, r2);
\t{{reg_type_scalar}} s3 = mipp_scalar_{{func}}_{{dt_ext}}_{{lmul_suffix}}(ms1, s1, s2);"""

OP_1ARG_1MASK = """\t{{msk_type}} m3 = mipp_{{func}}_{{dt_ext}}_{{lmul_suffix}}(m1); {{reg_type}} r3 = mipp_toreg_{{dt_ext}}_{{lmul_suffix}}(m3);
\t{{msk_type_scalar}} ms3 = mipp_scalar_{{func}}_{{dt_ext}}_{{lmul_suffix}}(ms1); {{reg_type_scalar}} s3 = mipp_scalar_toreg_{{dt_ext}}_{{lmul_suffix}}(ms3);"""

OP_2ARGS_2MASK = """\t{{msk_type}} m3 = mipp_{{func}}_{{dt_ext}}_{{lmul_suffix}}(m1, m2);\n\t{{reg_type}} r3 = mipp_toreg_{{dt_ext}}_{{lmul_suffix}}(m3);
\t{{msk_type_scalar}} ms3 = mipp_scalar_{{func}}_{{dt_ext}}_{{lmul_suffix}}(ms1, ms2);\n\t{{reg_type_scalar}} s3 = mipp_scalar_toreg_{{dt_ext}}_{{lmul_suffix}}(ms3);"""

OP_3ARGS_REG = """\t{{reg_type}} r4 = mipp_{{func}}_{{dt_ext}}_{{lmul_suffix}}(r1, r2, r3);
\t{{reg_type_scalar}} s4 = mipp_scalar_{{func}}_{{dt_ext}}_{{lmul_suffix}}(s1, s2, s3);"""

OP_CAST = """\t{{reg2_type}} r2 = mipp_cast_{{dt1_ext}}_{{dt2_ext}}_{{lmul_suffix}}(r1);
\t{{reg2_scalar_type}} s2 = mipp_scalar_cast_{{dt1_ext}}_{{dt2_ext}}_{{lmul_suffix}}(s1);"""
OP_CAST_MSK = """\t{{msk2_type}} m2 = mipp_cast_k_{{dt1_ext}}_{{dt2_ext}}_{{lmul_suffix}}(m1);
\t{{msk2_scalar_type}} ms2 = mipp_scalar_cast_k_{{dt1_ext}}_{{dt2_ext}}_{{lmul_suffix}}(ms1);"""

OP_GATHER = """\t{{reg_type}} r2 = mipp_gather_{{dt_ext}}_{{dt_ext}}_{{lmul_suffix}}(inputs1, ri1);\n\t{{reg_type_scalar}} s2 = mipp_scalar_gather_{{dt_ext}}_{{dt_ext}}_{{lmul_suffix}}(inputs1, ris1);"""

OP_SCATTER = """\tmipp_scatter_{{dt_ext}}_{{dt_ext}}_{{lmul_suffix}}(outputs, ri1, r1);\n\tmipp_scalar_scatter_{{dt_ext}}_{{dt_ext}}_{{lmul_suffix}}(outputs_scal, ris1, rs1);"""

OP_REG_VAL = """\t{{reg_type}} r3 = mipp_{{func}}_{{dt_ext}}_{{lmul_suffix}}(r1, input1);\n\t{{reg_type_scalar}} s3 = mipp_scalar_{{func}}_{{dt_ext}}_{{lmul_suffix}}(s1, input1);"""


# --------------------------------------------
# ASSERTS IN LOOP BODY (unchanged)
# ------------------------------------------

AS_REG_BINOP = """\t\tREQUIRE(mipp_get_{{dt_ext}}_{{lmul_suffix}}(r3, i) == mipp_scalar_get_{{dt_ext}}_{{lmul_suffix}}(s3, i));"""
AS_CMP_2REG = AS_REG_BINOP

AS_LOAD = """\t\tREQUIRE(mipp_get_{{dt_ext}}_{{lmul_suffix}}(r1, i) == mipp_scalar_get_{{dt_ext}}_{{lmul_suffix}}(s1,i));"""
AS_STORE = """\t\tREQUIRE(inputs2[i] == mipp_scalar_get_{{dt_ext}}_{{lmul_suffix}}(s1,i));"""

AS_3ARGS = """\t\tREQUIRE(mipp_get_{{dt_ext}}_{{lmul_suffix}}(r4, i) == mipp_scalar_get_{{dt_ext}}_{{lmul_suffix}}(s4,i) );"""

AS_CAST_2ARGS = """\t\tREQUIRE(mipp_get_{{dt2_ext}}_{{lmul_suffix}}(r2, i) == mipp_scalar_get_{{dt2_ext}}_{{lmul_suffix}}(s2,i) );"""
AS_CAST_2ARGS_MSK = """\t\tif(res) REQUIRE(mipp_get_k_{{dt2_ext}}_{{lmul_suffix}}(m2, i) != 0); else REQUIRE(mipp_get_k_{{dt2_ext}}_{{lmul_suffix}}(m2, i) == 0);"""

AS_REG_BINOP_FLOAT_WORKAROUND = """{% if is_int %}""" + AS_REG_BINOP + """{% else %}
\n\t\tREQUIRE(std::bit_cast<uint{{type_size}}_t,{{dt_ext}}_t>(mipp_get_{{dt_ext}}_{{lmul_suffix}}(r3, i))\
\n\t\t\t==
\t\t\tstd::bit_cast<uint{{type_size}}_t,{{dt_ext}}_t>(mipp_scalar_get_{{dt_ext}}_{{lmul_suffix}}(s3,i)) );
{% endif %}"""

AS_CMP_BINOP_LOGI_FLOAT_WORKAROUND = """{% if is_int %}""" + AS_CMP_2REG + """{% else %} 
\n\t\tREQUIRE( (!!mipp_get_{{dt_ext}}_{{lmul_suffix}}(r3, i)) == (!!mipp_scalar_get_{{dt_ext}}_{{lmul_suffix}}(s3,i)) );
{% endif %}"""

AS_TOMSK = """\t\tREQUIRE(!!mipp_get_{{dt_ext}}_{{lmul_suffix}}(r3, i) == !!mipp_scalar_get_{{dt_ext}}_{{lmul_suffix}}(s3,i));"""

AS_3ARGS_TOL = """\t\t{{dt_ext}}_t res1 = mipp_get_{{dt_ext}}_{{lmul_suffix}}(r4, i);
\t\t{{dt_ext}}_t res2 = mipp_scalar_get_{{dt_ext}}_{{lmul_suffix}}(s4, i);
\t\t{{dt_ext}}_t tol  = 1e-5f * abs_diff::abs_diff(res2) + 1.0f;
\t\t{{dt_ext}}_t diff = abs_diff::abs_diff(res1, res2);
\t\tREQUIRE(diff <= tol);"""

AS_GATHER = """\t\tREQUIRE(mipp_get_{{dt_ext}}_{{lmul_suffix}}(r2, i) == inputs1[indexes[i]]);\n\t\tREQUIRE(mipp_scalar_get_{{dt_ext}}_{{lmul_suffix}}(s2, i) == inputs1[indexes[i]]);"""
AS_SCATTER = """
\t\tREQUIRE(outputs[i] == outputs_scal[i]);
"""


AS_CMP_BINOP_FLOAT_WORKAROUND = AS_REG_BINOP_FLOAT_WORKAROUND

shape_templates = {
    SHAPE_RET_REG_2ARGS_REG: TemplateParts( # add, mul, sub, div, min, max, andb, orb, xorb
        func_decl=FUNC_DECL,
        decl=DECL_2ARGS,
        init=INIT_2ARGS,
        load=LOAD_2ARGS_REG,
        operation=OP_REG_BINOP,
        loop_body="",
        loop_assert=AS_REG_BINOP,
    ),
    SHAPE_RET_MSK_2ARGS_REG: TemplateParts( # cmpeq, cmpneq, cmpgt, cmpge, cmplt, cmple
        func_decl=FUNC_DECL,
        decl=DECL_2ARGS,
        init=INIT_2ARGS,
        load=LOAD_2ARGS_REG,
        operation=OP_CMP_2REG,
        loop_body="",
        loop_assert=AS_CMP_BINOP_LOGI_FLOAT_WORKAROUND,
    ),
    SHAPE_RET_REG_1ARG_PTR: TemplateParts( # load, loadu
        func_decl=FUNC_DECL,
        decl=DECL_1ARG,
        init=INIT_1ARG,
        load=LOAD_1ARG_REG,
        operation="",
        loop_body="",
        loop_assert=AS_LOAD,
    ),
    SHAPE_RET_VOID_2ARGS_PTR_REG: TemplateParts( # store, storeu
        func_decl=FUNC_DECL,
        decl=DECL_2ARGS_FOR_STORE,
        init=INIT_1ARG,
        load=LOAD_1ARG_REG,
        operation=OP_STORE,
        loop_body="",
        loop_assert=AS_STORE,
    ),
    SHAPE_RET_REG_1ARG_NELE: TemplateParts( # set
        func_decl=FUNC_DECL,
        decl=DECL_1ARG,
        init=INIT_1ARG,
        load="""\t{{reg_type}} r1 = mipp_{{func}}_{{dt_ext}}_{{lmul_suffix}}(inputs1);\n\t{{reg_type_scalar}} s1 = mipp_scalar_{{func}}_{{dt_ext}}_{{lmul_suffix}}(inputs1);""",
        operation=OP_REG_NOOP,
        loop_body="",
        loop_assert=AS_REG_BINOP,
    ),
    SHAPE_RET_MSK_1ARG_NELE: TemplateParts( # set_k
        func_decl=FUNC_DECL,
        decl=DECL_1ARG_INT32,
        init=INIT_1ARG,
        load=LOAD_1ARG_MASK,
        operation=OP_TOREG,
        loop_body="",
        loop_assert=AS_CMP_BINOP_LOGI_FLOAT_WORKAROUND,
    ),
    SHAPE_RET_REG_1ARG_VAL: TemplateParts( # set1
        func_decl=FUNC_DECL,
        decl=DECL_1ARG_SCALAR,
        init="",
        load=LOAD_1SCALAR_REG,
        operation=OP_REG_NOOP,
        loop_body="",
        loop_assert=AS_REG_BINOP,
    ),
    SHAPE_RET_MSK_1ARG_I32: TemplateParts( # set1_k
        func_decl=FUNC_DECL,
        decl=DECL_1ARG_SCALAR_INT32,
        init="",
        load=LOAD_1SCALAR_MASK,
        operation=OP_TOREG,
        loop_body="",
        loop_assert=AS_CMP_BINOP_LOGI_FLOAT_WORKAROUND,
    ),
    SHAPE_RET_REG_0ARG: TemplateParts( # set0
        func_decl=FUNC_DECL,
        decl=DECL_0ARGS,
        init="",
        load=LOAD_SET0_REG,
        operation=OP_REG_NOOP,
        loop_body="",
        loop_assert=AS_REG_BINOP,
    ),
    SHAPE_RET_MSK_0ARG: TemplateParts( # set0_k
        func_decl=FUNC_DECL,
        decl=DECL_0ARGS,
        init="",
        load=LOAD_SET0_MASK,
        operation=OP_TOREG,
        loop_body="",
        loop_assert=AS_CMP_BINOP_LOGI_FLOAT_WORKAROUND
    ),
    
    
    SHAPE_RET_VAL_2ARGS_REG_VAL: TemplateParts( # get
        func_decl=FUNC_DECL,
        decl=DECL_1ARG,
        init=INIT_1ARG,
        load=LOAD_1ARG_REG,
        operation=OP_REG_NOOP,
        loop_body="",
        loop_assert=AS_REG_BINOP,
    ),
    SHAPE_RET_VAL_2ARGS_MSK_VAL: TemplateParts( # get_k
        func_decl=FUNC_DECL,
        decl=DECL_1ARG_INT32,
        init=INIT_1ARG,
        load=LOAD_1ARG_MASK,
        operation=OP_TOREG,
        loop_body="",
        loop_assert=AS_CMP_BINOP_LOGI_FLOAT_WORKAROUND,
    ),
    SHAPE_RET_VAL_1ARG_REG: TemplateParts( # getfirst, hadd_to_scal
        func_decl=FUNC_DECL,
        decl=DECL_1ARG,
        init=INIT_1ARG,
        load=LOAD_1ARG_REG,
        operation="",
        loop_body="",
        loop_assert="\t\tREQUIRE(mipp_{{func}}_{{dt_ext}}_{{lmul_suffix}}(r1) == mipp_scalar_{{func}}_{{dt_ext}}_{{lmul_suffix}}(s1));",
    ),
    SHAPE_RET_REG_3ARGS_2REG_1MSK: TemplateParts( # blend
        func_decl=FUNC_DECL,
        decl=DECL_1ARG_INT32,
        init=INIT_1ARG,
        load=LOAD_1ARG_MASK + "\n" + LOAD_SET1_2ARGS_REG,
        operation=OP_3ARGS_2REG_1MSK,
        loop_body="",
        loop_assert=AS_REG_BINOP,
    ),
    SHAPE_RET_MSK_2ARGS_MSK: TemplateParts( # andb_k, orb_k, xorb_k, andnb_k
        func_decl=FUNC_DECL,
        decl=DECL_2ARGS_INT32 + DECL_G_SNIPPET,
        init=INIT_2ARGS_DIS,
        load=LOAD_2ARGS_MASK,
        operation=OP_2ARGS_2MASK,
        loop_body="",
        loop_assert=AS_CMP_BINOP_LOGI_FLOAT_WORKAROUND,
    ),
    SHAPE_RET_REG_1ARG_REG: TemplateParts( # hadd, hmul, hmin, hmax, round
        func_decl=FUNC_DECL,
        decl=DECL_1ARG,
        init=INIT_1ARG,
        load=LOAD_1ARG_REG,
        operation=OP_REG_UNOP,
        loop_body="",
        loop_assert=AS_REG_BINOP,
    ),
    
    # SHAPE_RET_MSK_1ARG_MSK: TemplateParts( # notb_k, cast_k
    #     func_decl=FUNC_DECL,
    #     decl=DECL_1ARG_INT32 + DECL_G_SNIPPET,
    #     init=INIT_1ARG_DIS,
    #     load=LOAD_1ARG_MASK,
    #     operation=OP_1ARG_1MASK,
    #     loop_body="",
    #     loop_assert=AS_CMP_BINOP_FLOAT_WORKAROUND,
    # ),
    SHAPE_RET_REG_1ARG_MSK: TemplateParts( # toreg
        func_decl=FUNC_DECL,
        decl=DECL_1ARG_INT32 + DECL_G_SNIPPET,
        init=INIT_1ARG_DIS,
        load=LOAD_1ARG_MASK,
        operation=OP_TOREG,
        loop_body="",
        loop_assert=AS_CMP_BINOP_FLOAT_WORKAROUND,
    ),
    SHAPE_RET_REG_3ARGS_REG: TemplateParts( # fmadd, fmsub, fnmadd, fnmsub
        func_decl=FUNC_DECL,
        decl=DECL_3ARGS,
        init=INIT_3ARGS,
        load=LOAD_3ARGS_REG,
        operation=OP_3ARGS_REG,
        loop_body="",
        loop_assert=AS_3ARGS_TOL,
    ),
    
    SHAPE_RET_I32_2ARGS_MSK: TemplateParts( # testz
        func_decl=FUNC_DECL,
        decl="",
        init="",
        load="\t{{msk_type}} m1 = mipp_set1_k_{{dt_ext}}_{{lmul_suffix}}(1); \n\t{{msk_type}} m2 = mipp_set1_k_{{dt_ext}}_{{lmul_suffix}}(0);",
        operation="",
        loop_body="",
        loop_assert="\tREQUIRE(mipp_testz_{{dt_ext}}_{{lmul_suffix}}(m1, m1) == 0);\n\tREQUIRE(mipp_testz_{{dt_ext}}_{{lmul_suffix}}(m2, m2) != 0);",
    ),
    SHAPE_RET_I32_1ARG_MSK: TemplateParts( #testz2
        func_decl=FUNC_DECL,
        decl="",
        init="",
        load="\t{{msk_type}} m1 = mipp_set1_k_{{dt_ext}}_{{lmul_suffix}}(1); \n\t{{msk_type}} m2 = mipp_set1_k_{{dt_ext}}_{{lmul_suffix}}(0);",
        operation="",
        loop_body="",
        loop_assert="\tREQUIRE(mipp_testz_2_{{dt_ext}}_{{lmul_suffix}}(m1) == 0);\n\tREQUIRE(mipp_testz_2_{{dt_ext}}_{{lmul_suffix}}(m2) != 0);",
    ),
    

    SHAPE_RET_MSK_1ARG_REG: TemplateParts( # tomsk
        func_decl=FUNC_DECL,
        decl=DECL_1ARG,
        init=INIT_1ARG,
        load=LOAD_1ARG_REG,
        operation="""\t{{msk_type}} m1 = mipp_tomsk_{{dt_ext}}_{{lmul_suffix}}(r1);\n{{reg_type}} r3 = mipp_toreg_{{dt_ext}}_{{lmul_suffix}}(m1);
{{msk_type_scalar}} ms1 = mipp_scalar_tomsk_{{dt_ext}}_{{lmul_suffix}}(s1);\n\t{{reg_type_scalar}} s3 = mipp_scalar_toreg_{{dt_ext}}_{{lmul_suffix}}(ms1);""",
        loop_body="",
        loop_assert=AS_TOMSK,
    ),
    
    SHAPE_RET_REG_2ARGS_PTR_REG : TemplateParts( # gather
        func_decl=FUNC_DECL_GATHER,
        decl=DECL_GATHER,
        init=INIT_GATHER,
        load=LOAD_GATHER,
        operation=OP_GATHER,
        loop_body="",
        loop_assert=AS_GATHER,
    ),

    SHAPE_RET_VOID_3ARGS_PTR_REG_REG : TemplateParts( # scatter
        func_decl=FUNC_DECL_SCATTER,
        decl=DECL_SCATTER,
        init=INIT_SCATTER,
        load=LOAD_SCATTER,
        operation=OP_SCATTER,
        loop_body="",
        loop_assert=AS_SCATTER,
    ),

    SHAPE_RET_REG_2ARGS_REG_VAL: TemplateParts( # lshift, rshift
        func_decl=FUNC_DECL,
        decl=DECL_1ARG+ """ \tint32_t input1 = rnd::uniform<int32_t>(seed); input1 = input1 < 0 ? -input1 : input1; input1 = input1 % ((sizeof({{dt_ext}}_t) * 8) - 2);""",
        init=INIT_1ARG,
        load=LOAD_1ARG_REG,
        operation=OP_REG_VAL,
        loop_body="",
        loop_assert=AS_CMP_BINOP_FLOAT_WORKAROUND,
    ),

}

deny = { "cvt", "wcvt" }
LAYER_OVERRIDES = {

        # Define CUSTOM overflow workarounds
    "add" : {
        "loop_assert" :
"""
\t\tbool ov = ovf::will_add_overflow<{{dt_ext}}_t>(mipp_get_{{dt_ext}}_{{lmul_suffix}}(r1, i), mipp_get_{{dt_ext}}_{{lmul_suffix}}(r2, i));
\t\tif(ov) {
\t\t\tINFO("Overflow occurred, skipping assert");
\t\t}else{\n\t"""+ AS_REG_BINOP + """\n\t\t}"""},
    
    "sub" : {
        "loop_assert" :"""
\tbool ov = ovf::will_sub_overflow<{{dt_ext}}_t>(mipp_get_{{dt_ext}}_{{lmul_suffix}}(r1, i), mipp_get_{{dt_ext}}_{{lmul_suffix}}(r2, i));
\t\tif(ov) {
\t\t\tINFO("Overflow occurred, skipping assert");
\t\t}else{\n\t"""+ AS_REG_BINOP + """\n\t\t}"""},
    
    "mul" : {
        "loop_assert" :"""
\t\tbool ov = ovf::will_mul_overflow<{{dt_ext}}_t>(mipp_get_{{dt_ext}}_{{lmul_suffix}}(r1, i), mipp_get_{{dt_ext}}_{{lmul_suffix}}(r2, i));
\t\tif(ov) {
\t\t\tINFO("Overflow occurred, skipping assert");
\t\t}else{\n\t"""+ AS_REG_BINOP + """\n\t\t}"""},
    
    # division by zero is skipped + add some 
    # tolerance for float division to avoid precision issues.
    "div" : {
        "loop_assert" :"""
\t\tif(mipp_get_{{dt_ext}}_{{lmul_suffix}}(r2, i) == 0) {
\t\t\tINFO("Division by zero, skipping assert");
\t\t}else{\n\t"""+ "\t\t {{dt_ext}}_t res1 = mipp_get_{{dt_ext}}_{{lmul_suffix}}(r3, i);\n \t\t{{dt_ext}}_t res2 = mipp_scalar_get_{{dt_ext}}_{{lmul_suffix}}(s3, i);\n"
+ "{% if is_int%}"
+ "\t\tREQUIRE(abs_diff::abs_diff(res1,res2) == 0);"
+ "{% else %}"
+ "\n\t\t{{dt_ext}}_t tol  = 1e-5f * abs_diff::abs_diff(res2) + 1.0f;"
+ "\n\t\t{{dt_ext}}_t diff = abs_diff::abs_diff(res1, res2);"
+ "\n\t\tREQUIRE(diff <= tol);"
+ "{% endif %}"
+ """\n\t\t}""",
    },

    # alwyas divide by 2 so no 0 check needed, but add some tolerance for float division to avoid precision issues.
    "div2" : {
        "loop_assert" :"""\t\t {{dt_ext}}_t res1 = mipp_get_{{dt_ext}}_{{lmul_suffix}}(r3, i);\n \t\t{{dt_ext}}_t res2 = mipp_scalar_get_{{dt_ext}}_{{lmul_suffix}}(s3, i);\n"""
+ "{% if is_int%}"
+ "\t\tREQUIRE(abs_diff::abs_diff(res1,res2) == 0);"
+ "{% else %}"
+ "\n\t\t{{dt_ext}}_t tol  = 1e-5f * abs_diff::abs_diff(res2) + 1.0f;"
+ "\n\t\t{{dt_ext}}_t diff = abs_diff::abs_diff(res1, res2);"
+ "\n\t\tREQUIRE(diff <= tol);"
+ "{% endif %}"
    },

    "div4" : {
        "loop_assert" :"""\t\t {{dt_ext}}_t res1 = mipp_get_{{dt_ext}}_{{lmul_suffix}}(r3, i);\n \t\t{{dt_ext}}_t res2 = mipp_scalar_get_{{dt_ext}}_{{lmul_suffix}}(s3, i);\n"""
+ "{% if is_int%}"
+ "\t\tREQUIRE(abs_diff::abs_diff(res1,res2) == 0);"
+ "{% else %}"
+ "\n\t\t{{dt_ext}}_t tol  = 1e-5f * abs_diff::abs_diff(res2) + 1.0f;"
+ "\n\t\t{{dt_ext}}_t diff = abs_diff::abs_diff(res1, res2);"
+ "\n\t\tREQUIRE(diff <= tol);"
+ "{% endif %}"
    },
    
    "andb": {
        "loop_assert" : AS_REG_BINOP_FLOAT_WORKAROUND
    },
    "orb": {
        "loop_assert" : AS_REG_BINOP_FLOAT_WORKAROUND
    },
    "xorb": {
        "loop_assert" : AS_REG_BINOP_FLOAT_WORKAROUND
    },
    
    # more tolerance than 1e-5 for hadd since on floats since it sums more stuff w lmul
    "hadd_to_scal" : {
        "loop_assert" :"""\t\tbool ov = false; {{dt_ext}}_t res = 0;
\t\tfor(int j = 0; j < {{size}} * {{lmul_coeff}}; j++){
\t\t\tov |= ovf::will_add_overflow<{{dt_ext}}_t>(res, inputs1[j]);
\t\t\tif(ov) break;
\t\t\tres += inputs1[j];
\t\t}
\t\tif(ov) {
\t\t\tINFO("Overflow occurred, skipping assert");
\t\t}else{\n\t"""
+ "\t\t {{dt_ext}}_t res1 = mipp_{{func}}_{{dt_ext}}_{{lmul_suffix}}(r1);\n \t\t{{dt_ext}}_t res2 = mipp_scalar_{{func}}_{{dt_ext}}_{{lmul_suffix}}(s1);\n"
+ "{% if is_int%}"
+ "\t\tREQUIRE(abs_diff::abs_diff(res1,res2) == 0);"
+ "{% else %}"
+ "\n\t\t{{dt_ext}}_t tol  = 1e-3f * abs_diff::abs_diff(res2) + 1.0f;"
+ "\n\t\t{{dt_ext}}_t diff = abs_diff::abs_diff(res1, res2);"
+ "\n\t\tREQUIRE(diff <= tol);"
+ "{% endif %}"
+ """\n\t\t}""",
    },

    "hadd" : {
        "loop_assert" :"""\t\tbool ov = false; {{dt_ext}}_t res = 0;
\t\tfor(int j = 0; j < {{size}} * {{lmul_coeff}}; j++){
\t\t\tov |= ovf::will_add_overflow<{{dt_ext}}_t>(res, inputs1[j]);
\t\t\tif(ov) break;
\t\t\tres += inputs1[j];
\t\t}
\t\tif(ov) {
\t\t\tINFO("Overflow occurred, skipping assert");
\t\t}else{\n\t"""
+ "\t\t {{dt_ext}}_t res1 = mipp_{{func}}_{{dt_ext}}_{{lmul_suffix}}(r1);\n \t\t{{dt_ext}}_t res2 = mipp_scalar_{{func}}_{{dt_ext}}_{{lmul_suffix}}(s1);\n"
+ "{% if is_int%}"
+ "\t\tREQUIRE(abs_diff::abs_diff(res1,res2) == 0);"
+ "{% else %}"
+ "\n\t\t{{dt_ext}}_t tol  = 1e-3f * abs_diff::abs_diff(res2) + 1.0f;"
+ "\n\t\t{{dt_ext}}_t diff = abs_diff::abs_diff(res1, res2);"
+ "\n\t\tREQUIRE(diff <= tol);"
+ "{% endif %}"
+ """\n\t\t}""",
    },

    
    "hmul": {
        "loop_assert": """\t\tbool ov = false; {{dt_ext}}_t res = 1;
\t\tfor(int j = 0; j < {{size}} * {{lmul_coeff}}; j++){
\t\t\tov |= ovf::will_mul_overflow<{{dt_ext}}_t>(res, inputs1[j]);
\t\t\tif(ov) break;
\t\t\tres *= inputs1[j];
\t\t}
\t\tif(ov) {
\t\t\tINFO("Overflow occurred, skipping assert");
\t\t}else{\n\t"""+ "\t\t {{dt_ext}}_t res1= mipp_{{func}}_{{dt_ext}}_{{lmul_suffix}}(r1);\n \t\t{{dt_ext}}_t res2 = mipp_scalar_{{func}}_{{dt_ext}}_{{lmul_suffix}}(s1);\n"
+ "{% if is_int%}"
+ "\t\tREQUIRE(abs_diff::abs_diff(res1,res2) == 0);"
+ "{% else %}"
+ "\n\t\t{{dt_ext}}_t tol  = 1e-5f * abs_diff::abs_diff(res2) + 1.0f;"
+ "\n\t\t{{dt_ext}}_t diff = abs_diff::abs_diff(res1, res2);"
+ "\n\t\tREQUIRE(diff <= tol);;"
+ "{% endif %}"
+ """\n\t\t}""",
    },
    
    "hmin": {
        "loop_assert": """\tREQUIRE(mipp_{{func}}_{{dt_ext}}_{{lmul_suffix}}(r1) == mipp_scalar_{{func}}_{{dt_ext}}_{{lmul_suffix}}(s1));""",
    },
    
    
    "hmax": {
        "loop_assert": """\tREQUIRE(mipp_{{func}}_{{dt_ext}}_{{lmul_suffix}}(r1) == mipp_scalar_{{func}}_{{dt_ext}}_{{lmul_suffix}}(s1));""",
    },
    
    "rsqrt" : {
# if inputs1[i] < 0 the result is a NaN and the assert will fail bc of how nan comparison works. 
# so skip in that case
        "loop_assert": """\t\tif(inputs1[i] < 0) {
\t\t\tINFO("Input is negative, result is NaN, skipping assert");
\t\t}else{\n\t"""+ "\t\t {{dt_ext}}_t res1 = mipp_get_{{dt_ext}}_{{lmul_suffix}}(r3,i);\n \t\t{{dt_ext}}_t res2 = mipp_scalar_get_{{dt_ext}}_{{lmul_suffix}}(s3,i);\n"
+ "\n\t\t{{dt_ext}}_t tol  = 1e-5f * abs_diff::abs_diff(res2) + 1.0f;"
+ "\n\t\t{{dt_ext}}_t diff = abs_diff::abs_diff(res1, res2);"
+ "\n\t\tREQUIRE(diff <= tol);;"
+ """\n\t\t}""",
    },
    
    # let's try 0 tolerance on sqrt
    "sqrt" : {
        "loop_assert": """\t\tif(inputs1[i] < 0) {
\t\t\tINFO("Input is negative, result is NaN, skipping assert");
\t\t}else{\n\t"""+ "\t\t {{dt_ext}}_t res1 = mipp_get_{{dt_ext}}_{{lmul_suffix}}(r3,i);\n \t\t{{dt_ext}}_t res2 = mipp_scalar_get_{{dt_ext}}_{{lmul_suffix}}(s3,i);\n"
+ "\t\tREQUIRE(res1 == res2);"
+ """\n\t\t}""",
    },
    
    # sometimes produces different bitwise results that both represent the same float value. So just compare w == instead of bitwise asssertion.
    # when fractional part is exactly 0.5 round and roundf from math.h round to upper int 
    # while some round intrinsics round to lower int. So we skip assert in that case.
    "round": {
        "loop_assert": "\t\t{{dt_ext}}_t fractional_part = inputs1[i] - std::floor(inputs1[i]);\n" +
        "\t\tif(fractional_part == 0.5f) {\n" +
        "\t\t\tINFO(\"Fractional part is exactly 0.5, different rounding methods may round differently, skipping assert\");\n" +
        "\t\t}else{\n\t\t\tREQUIRE(mipp_get_{{dt_ext}}_{{lmul_suffix}}(r3, i) == mipp_scalar_get_{{dt_ext}}_{{lmul_suffix}}(s3, i));\n\t\t}",
        },
    
    
    "cast": {
        "func_decl": """void test_cmipp_cast_{{dt1_ext}}_{{dt2_ext}}_{{lmul_suffix}}(){""",
        "decl": DECL_CAST_2ARGS,
        "init": INIT_CAST_2ARGS,
        "load": LOAD_CAST_2ARGS,
        "operation": OP_CAST,
        "loop_body": "",
        "loop_assert": 
"""for(size_t i = 0; i < {{size}} * sizeof({{dt1_ext}}_t) / sizeof({{dt2_ext}}_t); i++){\n""" +
AS_CAST_2ARGS+ "\n\t}",
    },
    
    "cast_k": {
        "func_decl": """void test_cmipp_cast_k_{{dt1_ext}}_{{dt2_ext}}_{{lmul_suffix}}(){""",
        "decl": DECL_CAST_2ARGS_MSK,
        "init": INIT_CAST_2ARGS,
        "load": LOAD_CAST_2ARGS_MASK,
        "operation": OP_CAST_MSK,
        "loop_body": "",
        "loop_assert": """for(size_t i = 0; i < {{size}} * sizeof({{dt1_ext}}_t) / sizeof({{dt2_ext}}_t); i++){\n""" +AS_CAST_2ARGS_MSK + "\n\t}",
    },
    
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