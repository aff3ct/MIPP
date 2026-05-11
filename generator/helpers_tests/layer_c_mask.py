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

DECL_GET_CATCH_SEED = "\n\tstd::mt19937 seed(Catch::getSeed()+n);\n"
DECL_PRED_ARG = """int32_t inpred[{{size}}*{{lmul_coeff}}];\n"""

DECL_0ARGS = DECL_GET_CATCH_SEED + DECL_PRED_ARG
DECL_1ARG = DECL_GET_CATCH_SEED + DECL_PRED_ARG + """ {{dt_ext}}_t inputs1[{{size}}*{{lmul_coeff}}];"""
DECL_1ARG_INT32 = DECL_GET_CATCH_SEED + DECL_PRED_ARG + """ int32_t inputs1[{{size}}*{{lmul_coeff}}];"""
DECL_1ARG_SCALAR = DECL_GET_CATCH_SEED + DECL_PRED_ARG + """ \t{{dt_ext}}_t input1 = 12;\n\t {{dt_ext}}_t inputs1[{{size}}*{{lmul_coeff}}];"""
DECL_1ARG_SCALAR_INT32 = DECL_GET_CATCH_SEED + DECL_PRED_ARG + """ \tint32_t input1 = 12;"""

DECL_2ARGS_FOR_STORE = DECL_GET_CATCH_SEED + DECL_PRED_ARG + """\n\t{{dt_ext}}_t inputs1[{{size}}*{{lmul_coeff}}],inputs2[{{size}}*{{lmul_coeff}}];"""
DECL_2ARGS = DECL_GET_CATCH_SEED + DECL_PRED_ARG + """\n\t{{dt_ext}}_t inputs1[{{size}}*{{lmul_coeff}}],inputs2[{{size}}*{{lmul_coeff}}];"""
DECL_2ARGS_INT32 = DECL_GET_CATCH_SEED + DECL_PRED_ARG + """\n\tint32_t inputs1[{{size}}*{{lmul_coeff}}],inputs2[{{size}}*{{lmul_coeff}}];"""

DECL_3ARGS = DECL_GET_CATCH_SEED + DECL_PRED_ARG + """\n\t{{dt_ext}}_t inputs1[{{size}}*{{lmul_coeff}}],inputs2[{{size}}*{{lmul_coeff}}],inputs3[{{size}}*{{lmul_coeff}}];"""

DECL_G_SNIPPET = """\tstd::mt19937 g;\n\tstd::uniform_int_distribution<uint16_t> dis(0, 1);"""

# DECL_CAST_2ARGS = (
#     DECL_GET_CATCH_SEED
#     + """\n\t{{dt1_ext}}_t inputs1[{{size}}*{{lmul_coeff}}];\n\tconstexpr size_t bytes = sizeof(inputs1);\n\t{{dt2_ext}}_t inputs2[bytes / sizeof({{dt2_ext}}_t)];"""
# )
# DECL_CAST_2ARGS_MSK = (
#     DECL_GET_CATCH_SEED
#     + """\n\tint32_t inputs1[{{size}}*{{lmul_coeff}}];\n\tconstexpr size_t bytes = sizeof(inputs1);\n\t{{dt2_ext}}_t inputs2[bytes / sizeof({{dt2_ext}}_t)];"""
# )

# --------------------------------------------
# SCALAR VEC INIT
# --------------------------------------------
INIT_PRED ="""
\tfor(size_t i = 0; i < {{size}} * {{lmul_coeff}}; i++)
\t{
\t\tinpred[i] = std::bit_cast<uint{{type_size}}_t,{{dt_ext}}_t>( rnd::uniform<{{dt_ext}}_t>(seed)) % 2 ? -1 : 0;
\t}"""


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

# --------------------------------------------
# LOADS (masked: create m0 + optionally rsrc)
# --------------------------------------------
LOAD_2ARGS_REG = """\t{{reg_type}} r1 = mipp_load_{{dt_ext}}{{lmul_suffix}}(inputs1);
\t{{reg_type}} r2 = mipp_load_{{dt_ext}}{{lmul_suffix}}(inputs2);
\t{{reg_type_scalar}} s1 = mipp_scalar_load_{{dt_ext}}{{lmul_suffix}}(inputs1);
\t{{reg_type_scalar}} s2 = mipp_scalar_load_{{dt_ext}}{{lmul_suffix}}(inputs2);
"""

LOAD_1ARG_REG = """\t{{reg_type}} r1 = mipp_load_{{dt_ext}}{{lmul_suffix}}(inputs1);
\t{{reg_type_scalar}} s1 = mipp_scalar_load_{{dt_ext}}{{lmul_suffix}}(inputs1);"""

LOAD_1SCALAR_REG = """\t{{reg_type}} r1 = mipp_set1_{{dt_ext}}{{lmul_suffix}}(input1);
\t{{reg_type_scalar}} s1 = mipp_scalar_set1_{{dt_ext}}{{lmul_suffix}}(input1);"""

LOAD_SET0_REG = """\t{{reg_type}} r1 = mipp_set0_{{dt_ext}}{{lmul_suffix}}();
\t{{reg_type_scalar}} s1 = mipp_scalar_set0_{{dt_ext}}{{lmul_suffix}}();"""

LOAD_2ARGS_MASK = """\t{{msk_type}} m1 = mipp_set_k_{{dt_ext}}{{lmul_suffix}}(inputs1);
\t{{msk_type}} m2 = mipp_set_k_{{dt_ext}}{{lmul_suffix}}(inputs2);
\t{{msk_type_scalar}} ms1 = mipp_scalar_set_k_{{dt_ext}}{{lmul_suffix}}(inputs1);
\t{{msk_type_scalar}} ms2 = mipp_scalar_set_k_{{dt_ext}}{{lmul_suffix}}(inputs2);"""

LOAD_1ARG_MASK = """\t{{msk_type}} m1 = mipp_set_k_{{dt_ext}}{{lmul_suffix}}(inputs1);
\t{{msk_type_scalar}} ms1 = mipp_scalar_set_k_{{dt_ext}}{{lmul_suffix}}(inputs1);"""

LOAD_1SCALAR_MASK = """\t{{msk_type}} m1 = mipp_set1_k_{{dt_ext}}{{lmul_suffix}}(input1);
\t{{msk_type_scalar}} ms1 = mipp_scalar_set1_k_{{dt_ext}}{{lmul_suffix}}(input1);"""

LOAD_SET0_MASK = """\t{{msk_type}} m1 = mipp_set0_k_{{dt_ext}}{{lmul_suffix}}();
\t{{msk_type_scalar}} ms1 = mipp_scalar_set0_k_{{dt_ext}}{{lmul_suffix}}();"""

LOAD_SET1_2ARGS_REG = """\t{{reg_type}} r1 = mipp_set1_{{dt_ext}}_{{lmul_suffix}}(1); \n\t{{reg_type}} r2 = mipp_set1_{{dt_ext}}{{lmul_suffix}}(2);
\t{{reg_type_scalar}} s1 = mipp_scalar_set1_{{dt_ext}}{{lmul_suffix}}(1); \n\t{{reg_type_scalar}} s2 = mipp_scalar_set1_{{dt_ext}}{{lmul_suffix}}(2);"""

LOAD_3ARGS_REG = """\t{{reg_type}} r1 = mipp_load_{{dt_ext}}{{lmul_suffix}}(inputs1);
\t{{reg_type}} r2 = mipp_load_{{dt_ext}}{{lmul_suffix}}(inputs2);
\t{{reg_type}} r3 = mipp_load_{{dt_ext}}{{lmul_suffix}}(inputs3);
\t{{reg_type_scalar}} s1 = mipp_scalar_load_{{dt_ext}}{{lmul_suffix}}(inputs1);
\t{{reg_type_scalar}} s2 = mipp_scalar_load_{{dt_ext}}{{lmul_suffix}}(inputs2);
\t{{reg_type_scalar}} s3 = mipp_scalar_load_{{dt_ext}}{{lmul_suffix}}(inputs3);"""

LOAD_CAST_2ARGS = """\t{{reg1_type}} r1 = mipp_load_{{dt1_ext}}{{lmul_suffix}}(inputs1);
\n\t{{reg1_scalar_type}} s1 = mipp_scalar_load_{{dt1_ext}}{{lmul_suffix}}(inputs1);"""

LOAD_CAST_2ARGS_MASK = """\t{{msk1_type}} m1 = mipp_set_k_{{dt1_ext}}{{lmul_suffix}}(inputs1);
\n\t{{msk1_scalar_type}} ms1 = mipp_scalar_set_k_{{dt1_ext}}{{lmul_suffix}}(inputs1);"""

# Mask inputs for masked wrappers:
# - choose mask m0 (we'll base it on inputs1 for convenience)
# - rsrc for "masks" kind (use r1 where available, otherwise set0)
LOAD_MASK_AND_RSRC_FROM_INPUTS = """\t{{msk_type}} mpred = mipp_set_k_{{dt_ext}}{{lmul_suffix}}(inpred);
\t{{reg_type}} rsrc = mipp_set0_{{dt_ext}}{{lmul_suffix}}();
\t{{msk_type_scalar}} smpred = mipp_scalar_set_k_{{dt_ext}}{{lmul_suffix}}(inpred);
\t{{reg_type_scalar}} srsrc = mipp_scalar_set0_{{dt_ext}}{{lmul_suffix}}();"""


LOAD_MASK_AND_RSRC_FROM_REG1 = """\t{{msk_type}} mpred = mipp_set_k_{{dt_ext}}{{lmul_suffix}}(inpred);
\t{{msk_type_scalar}} smpred = mipp_scalar_set_k_{{dt_ext}}{{lmul_suffix}}(inpred);
{% if mkind == "masks" %}
\t{{reg_type}} rsrc = mipp_load_{{dt_ext}}{{lmul_suffix}}(inputs1);
\t{{reg_type_scalar}} srsrc = mipp_scalar_load_{{dt_ext}}{{lmul_suffix}}(inputs1);
{% endif %}
"""


# --------------------------------------------
# OPERATIONS (masked)
# --------------------------------------------
OP_REG_NOOP = """\t{{reg_type}} r3 = r1;\t{{reg_type_scalar}} s3 = s1;"""
OP_REG_UNOP = """\t{{reg_type}} r3 = mipp_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}({{mask_args}} r1);
\t{{reg_type_scalar}} s3 = mipp_scalar_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}({{mask_args_scalar}} s1);"""

OP_REG_BINOP = """\t{{reg_type}} r3 = mipp_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}({{mask_args}} r1, r2);
\t{{reg_type_scalar}} s3 = mipp_scalar_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}({{mask_args_scalar}} s1, s2);"""

OP_CMP_2REG = """\t{{msk_type}} m3 = mipp_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}({{mask_args}} r1, r2); {{reg_type}} r3 = mipp_toreg_{{dt_ext}}(m3);
\t{{msk_type_scalar}} sm3 = mipp_scalar_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}({{mask_args_scalar}} s1, s2); {{reg_type_scalar}} s3 = mipp_scalar_toreg_{{dt_ext}}(sm3);"""

OP_STORE = """
\t{{dt_ext}}_t output[{{size}}*{{lmul_coeff}}];
\t{{dt_ext}}_t output_scalar[{{size}}*{{lmul_coeff}}];
\tfor(size_t i = 0; i < {{size}}*{{lmul_coeff}}; i++){
    //dummy init to compare 
    output[i] = i;
    output_scalar[i] = i;
}
\tmipp_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}({{mask_args}} output, r1);
\tmipp_scalar_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}({{mask_args_scalar}} output_scalar, s1);"""


OP_TOREG = """\t{{reg_type}} r3 = mipp_toreg_{{dt_ext}}(m1);\n\t{{reg_type_scalar}} s3 = mipp_scalar_toreg_{{dt_ext}}(ms1);"""

OP_SCAL_UNOP = """\t{{dt_ext}}_t res = mipp_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}({{mask_args}} r1);
\t{{dt_ext}}_t sres = mipp_scalar_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}({{mask_args_scalar}} s1);"""

OP_3ARGS_2REG_1MSK = """\t{{reg_type}} r3 = mipp_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}({{mask_args}} r1, r2, m1);
\t{{reg_type_scalar}} s3 = mipp_scalar_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}({{mask_args_scalar}} s1, s2, sm1);"""

OP_3ARGS_1MSK_2REG = """\t{{reg_type}} r3 = mipp_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}({{mask_args}} m1, r1, r2);
\t{{reg_type_scalar}} s3 = mipp_scalar_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}({{mask_args_scalar}} sm1, s1, s2);"""

OP_1ARG_1MASK = """\t{{msk_type}} m3 = mipp_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}({{mask_args}} m1); {{reg_type}} r3 = mipp_toreg_{{dt_ext}}(m3);
\t{{msk_type_scalar}} sm3 = mipp_scalar_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}({{mask_args_scalar}} sm1); {{reg_type_scalar}} s3 = mipp_scalar_toreg_{{dt_ext}}(sm3);"""

OP_2ARGS_2MASK = """\t{{msk_type}} m3 = mipp_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}({{mask_args}} m1, m2);\n\t{{reg_type}} r3 = mipp_toreg_{{dt_ext}}(m3);
\t{{msk_type_scalar}} sm3 = mipp_scalar_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}({{mask_args_scalar}} sm1, sm2); {{reg_type_scalar}} s3 = mipp_scalar_toreg_{{dt_ext}}(sm3);"""

OP_3ARGS_REG = """\t{{reg_type}} r4 = mipp_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}({{mask_args}} r1, r2, r3);
\t{{reg_type_scalar}} s4 = mipp_scalar_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}({{mask_args_scalar}} s1, s2, s3);"""


# --------------------------------------------
# ASSERTS IN LOOP BODY
# ------------------------------------------
AS_REG_BINOP = """\t\tREQUIRE(mipp_get_{{dt_ext}}{{lmul_suffix}}(r3, i) == mipp_scalar_get_{{dt_ext}}{{lmul_suffix}}(s3, i));"""
AS_CMP_2REG = AS_REG_BINOP

AS_LOAD = """\t\tREQUIRE(mipp_get_{{dt_ext}}{{lmul_suffix}}(r1, i) == mipp_scalar_get_{{dt_ext}}{{lmul_suffix}}(s1,i));"""
AS_STORE = """\t\tREQUIRE(output[i] == output_scalar[i]);"""

AS_3ARGS = """\t\tREQUIRE(mipp_get_{{dt_ext}}{{lmul_suffix}}(r4, i) == mipp_scalar_get_{{dt_ext}}{{lmul_suffix}}(s4, i));"""

AS_REG_BINOP_FLOAT_WORKAROUND = """{% if is_int %}""" + AS_REG_BINOP + """{% else %}
\n\t\tREQUIRE(std::bit_cast<uint{{type_size}}_t,{{dt_ext}}_t>(mipp_get_{{dt_ext}}{{lmul_suffix}}(r3, i))\
\n\t\t\t==
\t\t\tstd::bit_cast<uint{{type_size}}_t,{{dt_ext}}_t>(mipp_scalar_get_{{dt_ext}}{{lmul_suffix}}(s3, i)) );
{% endif %}"""

AS_CMP_BINOP_LOGI_FLOAT_WORKAROUND = """{% if is_int %}""" + AS_CMP_2REG + """{% else %} 
\n\t\tREQUIRE( (!!mipp_get_{{dt_ext}}{{lmul_suffix}}(r3, i)) == (!!mipp_scalar_get_{{dt_ext}}{{lmul_suffix}}(s3,i)) );
{% endif %}"""

AS_3ARGS_TOL = """\t\t{{dt_ext}}_t res1 = mipp_get_{{dt_ext}}{{lmul_suffix}}(r4, i);
\t\t{{dt_ext}}_t res2 = mipp_scalar_get_{{dt_ext}}{{lmul_suffix}}(s4, i);
\t\t{{dt_ext}}_t tol  = 1e-5f * abs_diff::abs_diff(res2) + 1.0f;
\t\t{{dt_ext}}_t diff = abs_diff::abs_diff(res1, res2);
\t\tREQUIRE(diff <= tol);"""

# --------------------------------------------
# Shapes
# --------------------------------------------
shape_templates = {
    SHAPE_RET_REG_2ARGS_REG: TemplateParts( # add, mul, sub, div, min, max, andb, orb, xorb
        func_decl=FUNC_DECL,
        decl=DECL_2ARGS,
        init=INIT_PRED+INIT_2ARGS,
        load=LOAD_2ARGS_REG + "\n" + LOAD_MASK_AND_RSRC_FROM_REG1,
        operation=OP_REG_BINOP,
        loop_body="",
        loop_assert=AS_REG_BINOP,
    ),
    SHAPE_RET_MSK_2ARGS_REG: TemplateParts( # cmpeq, cmpneq, cmpgt, cmpge, cmplt, cmple
        func_decl=FUNC_DECL,
        decl=DECL_2ARGS,
        init=INIT_PRED+INIT_2ARGS,
        load=LOAD_2ARGS_REG + "\n" + LOAD_MASK_AND_RSRC_FROM_REG1,
        operation=OP_CMP_2REG,
        loop_body="",
        loop_assert=AS_CMP_BINOP_LOGI_FLOAT_WORKAROUND,
    ),

    SHAPE_RET_REG_1ARG_PTR: TemplateParts(  # load, loadu
        func_decl=FUNC_DECL,
        decl=DECL_1ARG,
        init=INIT_PRED+INIT_1ARG,
        load=LOAD_MASK_AND_RSRC_FROM_REG1,
        #delegate "load" to operation
        operation="""{{reg_type}} r1 = mipp_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}({{mask_args}} inputs1); 
\t{{reg_type_scalar}} s1 = mipp_scalar_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}({{mask_args_scalar}} inputs1);""",
        loop_body="",
        loop_assert=AS_LOAD,
    ),
    SHAPE_RET_VOID_2ARGS_PTR_REG: TemplateParts( # store, storeu
        func_decl=FUNC_DECL,
        decl=DECL_1ARG,
        init=INIT_PRED + INIT_1ARG,
        load=LOAD_1ARG_REG + "\n" + LOAD_MASK_AND_RSRC_FROM_REG1,
        operation=OP_STORE,
        loop_body="",
        loop_assert=AS_STORE,
    ),
    SHAPE_RET_REG_1ARG_NELE: TemplateParts( # set
        func_decl=FUNC_DECL,
        decl=DECL_1ARG,
        init=INIT_PRED+INIT_1ARG,
        load=LOAD_MASK_AND_RSRC_FROM_REG1,
        operation="""\t{{reg_type}} r1 = mipp_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}({{mask_args}} inputs1);
\t{{reg_type_scalar}} s1 = mipp_scalar_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}({{mask_args_scalar}} inputs1);\n""" + OP_REG_NOOP,
        loop_body="",
        loop_assert=AS_REG_BINOP_FLOAT_WORKAROUND
    ),
    SHAPE_RET_REG_1ARG_VAL: TemplateParts( # set1
        func_decl=FUNC_DECL,
        decl=DECL_1ARG_SCALAR,
        init=INIT_PRED+INIT_1ARG,
        load=LOAD_MASK_AND_RSRC_FROM_REG1,
        operation="""{{reg_type}} r1 = mipp_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}({{mask_args}} input1);
\t{{reg_type_scalar}} s1 = mipp_scalar_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}({{mask_args_scalar}} input1);\n""" + OP_REG_NOOP,
        loop_body="",
        loop_assert=AS_REG_BINOP_FLOAT_WORKAROUND,
    ),
    SHAPE_RET_REG_0ARG: TemplateParts( # set0
        func_decl=FUNC_DECL,
        decl=DECL_1ARG, # used for rsrc initialization
        init=INIT_PRED+INIT_1ARG,
        load=LOAD_MASK_AND_RSRC_FROM_REG1,
        # args hardcoded by hand bc templates end them w a comma ....
        # fine bc there is only 1 type of mask support for set0 ...
        operation="""\t{{reg_type}} r1 = mipp_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}(mpred,rsrc);
\t{{reg_type_scalar}} s1 = mipp_scalar_{{func}}_{{dt_ext}}{{mask_kind}}{{lmul_suffix}}(smpred,srsrc);\n""" + OP_REG_NOOP,
        loop_body="",
        loop_assert=AS_REG_BINOP_FLOAT_WORKAROUND,
    ),

    # SHAPE_RET_REG_1ARG_REG: TemplateParts( # hadd, hmul, hmax, hmin, round, cast, sqrt, rsqrt, notb
    #     func_decl=FUNC_DECL,
    #     decl=DECL_1ARG,
    #     init=INIT_1ARG,
    #     load=LOAD_1ARG_REG + "\n" + LOAD_MASK_AND_RSRC_FROM_REG1,
    #     operation=OP_REG_UNOP,
    #     loop_body="" #LB_SET_OP,
    #     loop_assert=AS_REG_BINOP,
    # ),

    SHAPE_RET_REG_3ARGS_REG: TemplateParts( # fmadd, fmsub, fnmadd, fnmsub
        func_decl=FUNC_DECL,
        decl=DECL_3ARGS,
        init=INIT_PRED+INIT_3ARGS,
        load=LOAD_3ARGS_REG + "\n" + LOAD_MASK_AND_RSRC_FROM_REG1,
        operation=OP_3ARGS_REG,
        loop_body="",
        loop_assert=AS_3ARGS_TOL
    ),
}

deny = {
    "andb", # circular dependency w blend for generic emu.
    "xorb", # I think avx2 causes issues w these two bc of how blend is implemented ?
    "andnb",
    "storeu",
    "hadd", 
    "hmul",
    "hmin",
    "hmax",
}

LAYER_OVERRIDES = {
    "add" : {
        "loop_assert" :
    """
    \t\tbool ov = ovf::will_add_overflow<{{dt_ext}}_t>(mipp_get_{{dt_ext}}(r1, i), mipp_get_{{dt_ext}}(r2, i));
    \t\tif(ov){
    \t\t\tINFO("Overflow occurred, skipping assert");
    \t\t}else{\n\t"""+ AS_REG_BINOP + """\n\t\t}"""},
    
    "sub" : {
        "loop_assert" :"""
\tbool ov = ovf::will_sub_overflow<{{dt_ext}}_t>(mipp_get_{{dt_ext}}(r1, i), mipp_get_{{dt_ext}}(r2, i));
\t\tif(ov) {
\t\t\tINFO("Overflow occurred, skipping assert");
\t\t}else{\n\t"""+ AS_REG_BINOP + """\n\t\t}"""},
    
    "mul" : {
        "loop_assert" :"""
\t\tbool ov = ovf::will_mul_overflow<{{dt_ext}}_t>(mipp_get_{{dt_ext}}(r1, i), mipp_get_{{dt_ext}}(r2, i));
\t\tif(ov) {
\t\t\tINFO("Overflow occurred, skipping assert");
\t\t}else{\n\t"""+ AS_REG_BINOP + """\n\t\t}"""},
    
    # division by zero is skipped + add some 
    # tolerance for float division to avoid precision issues.
    "div" : {
        "loop_assert" :"""
\t\tif(mipp_get_{{dt_ext}}(r2, i) == 0) {
\t\t\tINFO("Division by zero, skipping assert");
\t\t}else{\n\t"""+ "\t\t {{dt_ext}}_t res1 = mipp_get_{{dt_ext}}(r3, i);\n \t\t{{dt_ext}}_t res2 = mipp_scalar_get_{{dt_ext}}(s3, i);\n"
+ "{% if is_int%}"
+ "\t\tREQUIRE(abs_diff::abs_diff(res1,res2) == 0);"
+ "{% else %}"
+ "\n\t\t{{dt_ext}}_t tol  = 1e-5f * abs_diff::abs_diff(res2) + 1.0f;"
+ "\n\t\t{{dt_ext}}_t diff = abs_diff::abs_diff(res1, res2);"
+ "\n\t\tREQUIRE(diff <= tol);"
+ "{% endif %}"
+ """\n\t\t}""",
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