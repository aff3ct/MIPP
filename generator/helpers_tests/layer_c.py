from headers_def import mipp_funcs
from .templates import GENERIC_FOR_LOOP, GENERIC_NO_LOOP
from .common import (
    TemplateParts,
    build_layer_gen_test_dict,
    SHAPE_RET_REG_2ARGS_REG,
    SHAPE_RET_MSK_2ARGS_REG,
    SHAPE_RET_REG_1ARG_PTR,
    SHAPE_RET_VOID_2ARGS_PTR_REG,
    SHAPE_RET_REG_1ARG_NELE,#set only
    SHAPE_RET_MSK_1ARG_NELE,#setk 
    SHAPE_RET_REG_1ARG_VAL, #only set1 :o
    SHAPE_RET_MSK_1ARG_I32,#set1_k
    SHAPE_RET_REG_0ARG,#set0
    SHAPE_RET_MSK_0ARG,#set0_k
    SHAPE_RET_VAL_2ARGS_REG_VAL, #get only
    SHAPE_RET_VAL_2ARGS_MSK_VAL, #get_k only
    SHAPE_RET_VAL_1ARG_REG,
    SHAPE_RET_REG_3ARGS_2REG_1MSK, #blend only
    SHAPE_RET_MSK_2ARGS_MSK, #andb_k orb_k xorb_k andnb_k
    SHAPE_RET_REG_1ARG_REG, #notb, sqrt, cast
    SHAPE_RET_MSK_1ARG_MSK, #notb_k, and cast_k
    SHAPE_RET_REG_1ARG_MSK, #toreg only
    
    SHAPE_RET_REG_3ARGS_REG, #fmadd, fmsub
    SHAPE_RET_I32_2ARGS_MSK,# testz
    SHAPE_RET_I32_1ARG_MSK, #testz2
    
    SHAPE_RET_REG_3ARGS_1MSK_2REG, #maskz_add only
    SHAPE_RET_MSK_1ARG_REG, #tomsk only
    SHAPE_RET_REG_2ARGS_MASK_PTR, #maskz load only
    SHAPE_RET_VOID_3ARGS_PTR_MSK_REG, #mask store (maskst) only

)

# --------------------------
# C fragments
# --------------------------


# --------------------------------------------
# FN decl 
# --------------------------------------------
FUNC_DECL = """void test_cmipp_{{func}}_{{dt_ext}}(){"""
FUNC_DECL_LMUL = """void test_cmipp_{{func}}_{{dt_ext}}_{{lmul}}(){"""


# --------------------------------------------
# SCALAR VEC DECL
# --------------------------------------------


DECL_GET_CATCH_SEED = "\n\tstd::mt19937 seed(Catch::getSeed()+n);\n"

DECL_1ARG = DECL_GET_CATCH_SEED + """ {{dt_ext}}_t inputs1[{{size}}];"""
DECL_1ARG_INT32 = DECL_GET_CATCH_SEED + """ int32_t inputs1[{{size}}];"""
DECL_1ARG_SCALAR = DECL_GET_CATCH_SEED + """ \t{{dt_ext}}_t input1 = rnd::uniform<{{dt_ext}}_t>(seed);"""
DECL_1ARG_SCALAR_INT32 = DECL_GET_CATCH_SEED + """ \tint32_t input1 = rnd::uniform<int32_t>(seed);"""

DECL_2ARGS_FOR_STORE = """\n\t{{dt_ext}}_t inputs1[{{size}}],inputs2[{{size}}];"""
DECL_2ARGS = DECL_GET_CATCH_SEED + """\n\t{{dt_ext}}_t inputs1[{{size}}],inputs2[{{size}}];"""

DECL_2ARGS_INT32 = """\n\tint32_t inputs1[{{size}}],inputs2[{{size}}];"""

DECL_3ARGS = DECL_GET_CATCH_SEED + """\n\t{{dt_ext}}_t inputs1[{{size}}],inputs2[{{size}}],inputs3[{{size}}];"""

#never used on it's own, but used alongisde other snippets :)
DECL_G_SNIPPET = """\tstd::mt19937 g;\n\tstd::uniform_int_distribution<uint16_t> dis(0, 1);"""

#we want inputs2 to store the same amount of bytes as inputs1 since we'll be memcpying from inputs1 to inputs2 for the cast tests, so if dt2 is smaller than dt1 we need more lanes in inputs2
DECL_CAST_2ARGS = """\n\t{{dt1_ext}}_t inputs1[{{size}}];\n\tconstexpr size_t bytes = sizeof(inputs1);\n\t{{dt2_ext}}_t inputs2[bytes / sizeof({{dt2_ext}}_t)];"""
DECL_CAST_2ARGS_MSK = """\n\tint32_t inputs1[{{size}}];\n\tconstexpr size_t bytes = sizeof(inputs1);\n\t{{dt2_ext}}_t inputs2[bytes / sizeof({{dt2_ext}}_t)];"""

# --------------------------------------------
# SCALAR VEC INIT
# --------------------------------------------

# init using values generated with the seed taken from Catch::getSeed()
INIT_2ARGS = """
\tfor(size_t i = 0; i < {{size}}; i++)
\t{
\t\tinputs1[i] = rnd::uniform<{{dt_ext}}_t>(seed);
\t\tinputs2[i] = rnd::uniform<{{dt_ext}}_t>(seed);
\t}
"""

INIT_1ARG = """
\tfor(size_t i = 0; i < {{size}}; i++)
\t{
\t\tinputs1[i] = rnd::uniform<{{dt_ext}}_t>(seed);
\t}
"""

INIT_2ARGS_NOUFLOW = INIT_2ARGS + """\tfor(size_t i = 0; i < {{size}}; i++)
\t{
\t\tinputs1[i] += inputs2[i];
\t}
"""


INIT_1ARG_DIS = """\tstd::iota(inputs1, inputs1 + {{size}}, 1);
\tfor(size_t i = 0; i < {{size}}; i++)
\t{
\t\tinputs1[i] = dis(g) ? -1 : 0;
\t}"""

INIT_2ARGS_DIS = """\tfor(size_t i = 0; i < {{size}}; i++)
\t{
\t\tinputs1[i] = dis(g) ? -1 : 0;
\t\tinputs2[i] = dis(g) ? -1 : 0;
\t}"""


INIT_3ARGS = """\tfor(size_t i = 0; i < {{size}}; i++)
\t{
\t\tinputs1[i] = rnd::uniform<{{dt_ext}}_t>(seed);
\t\tinputs2[i] = rnd::uniform<{{dt_ext}}_t>(seed);
\t\tinputs3[i] = rnd::uniform<{{dt_ext}}_t>(seed);
\t}
"""

#to cast we want to memcpy from inputs1 to inputs2 
#to compare inputs2 to what we got after casting in the loop body.
INIT_CAST_2ARGS = """\tstd::iota(inputs1, inputs1 + {{size}}, 1);\n\tmemcpy(inputs2, inputs1, sizeof(inputs1));"""

# --------------------------------------------
# LOADS
# --------------------------------------------


LOAD_2ARGS_REG = """\t{{reg_type}} r1 = mipp_load_{{dt_ext}}(inputs1);
\t{{reg_type}} r2 = mipp_load_{{dt_ext}}(inputs2);
\t{{reg_type_scalar}} s1 = mipp_scalar_load_{{dt_ext}}(inputs1);
\t{{reg_type_scalar}} s2 = mipp_scalar_load_{{dt_ext}}(inputs2);
"""

LOAD_1ARG_REG = """\t{{reg_type}} r1 = mipp_load_{{dt_ext}}(inputs1);
\t{{reg_type_scalar}} s1 = mipp_scalar_load_{{dt_ext}}(inputs1);"""

LOAD_1SCALAR_REG = """\t{{reg_type}} r1 = mipp_set1_{{dt_ext}}(input1);\n\t{{reg_type_scalar}} s1 = mipp_scalar_set1_{{dt_ext}}(input1);"""
LOAD_SET0_REG = """\t{{reg_type}} r1 = mipp_set0_{{dt_ext}}(); {{reg_type_scalar}} s1 = mipp_scalar_set0_{{dt_ext}}();"""

LOAD_2ARGS_MASK = """\t{{msk_type}} m1 = mipp_set_k_{{dt_ext}}(inputs1); 
\t{{msk_type}} m2 = mipp_set_k_{{dt_ext}}(inputs2);
\t{{msk_type_scalar}} ms1 = mipp_scalar_set_k_{{dt_ext}}(inputs1);
\t{{msk_type_scalar}} ms2 = mipp_scalar_set_k_{{dt_ext}}(inputs2);
"""

LOAD_1ARG_MASK = """\t{{msk_type}} m1 = mipp_set_k_{{dt_ext}}(inputs1);\n\t{{msk_type_scalar}} ms1 = mipp_scalar_set_k_{{dt_ext}}(inputs1);"""
LOAD_1SCALAR_MASK = """\t{{msk_type}} m1 = mipp_set1_k_{{dt_ext}}(input1);\n\t{{msk_type_scalar}} ms1 = mipp_scalar_set1_k_{{dt_ext}}(input1);"""
LOAD_SET0_MASK = """\t{{msk_type}} m1 = mipp_set0_k_{{dt_ext}}();\n\t{{msk_type_scalar}} ms1 = mipp_scalar_set0_k_{{dt_ext}}();"""

#used for blend
LOAD_SET1_2ARGS_REG = """\t{{reg_type}} r1 = mipp_set1_{{dt_ext}}(1); \n\t{{reg_type}} r2 = mipp_set1_{{dt_ext}}(2);
\t{{reg_type_scalar}} s1 = mipp_scalar_set1_{{dt_ext}}(1); \n\t{{reg_type_scalar}} s2 = mipp_scalar_set1_{{dt_ext}}(2);"""

LOAD_3ARGS_REG = """\t{{reg_type}} r1 = mipp_load_{{dt_ext}}(inputs1);
\t{{reg_type}} r2 = mipp_load_{{dt_ext}}(inputs2);
\t{{reg_type}} r3 = mipp_load_{{dt_ext}}(inputs3);
\t{{reg_type_scalar}} s1 = mipp_scalar_load_{{dt_ext}}(inputs1);
\t{{reg_type_scalar}} s2 = mipp_scalar_load_{{dt_ext}}(inputs2);
\t{{reg_type_scalar}} s3 = mipp_scalar_load_{{dt_ext}}(inputs3);
"""

LOAD_CAST_2ARGS = """\t{{reg1_type}} r1 = mipp_load_{{dt1_ext}}(inputs1); {{reg1_scalar_type}} s1 = mipp_scalar_load_{{dt1_ext}}(inputs1);"""
LOAD_CAST_2ARGS_MASK = """\t{{msk1_type}} m1 = mipp_set_k_{{dt1_ext}}(inputs1); {{msk1_scalar_type}} ms1 = mipp_scalar_set_k_{{dt1_ext}}(inputs1);"""

# --------------------------------------------
# OPERATIONS
# --------------------------------------------

OP_REG_NOOP = """\t{{reg_type}} r3 = r1;\n\t{{reg_type_scalar}} s3 = s1;"""
OP_REG_UNOP = """\t{{reg_type}} r3 = mipp_{{func}}_{{dt_ext}}(r1);\n\t{{reg_type_scalar}} s3 = mipp_scalar_{{func}}_{{dt_ext}}(s1);"""
OP_REG_BINOP = """\t{{reg_type}} r3 = mipp_{{func}}_{{dt_ext}}(r1, r2);
\t{{reg_type_scalar}} s3 = mipp_scalar_{{func}}_{{dt_ext}}(s1, s2);
"""

OP_CMP_2REG = """\t{{msk_type}} m3 = mipp_{{func}}_{{dt_ext}}(r1, r2); {{reg_type}} r3 = mipp_toreg_{{dt_ext}}(m3);
{{msk_type_scalar}} ms3 = mipp_scalar_{{func}}_{{dt_ext}}(s1, s2); {{reg_type_scalar}} s3 = mipp_scalar_toreg_{{dt_ext}}(ms3);
"""

OP_STORE = """\tmipp_store_{{dt_ext}}(inputs2, r1);"""

OP_TOREG = """\t{{reg_type}} r3 = mipp_toreg_{{dt_ext}}(m1);\n\t{{reg_type_scalar}} s3 = mipp_scalar_toreg_{{dt_ext}}(ms1);"""

OP_SCAL_UNOP = """\t{{dt_ext}}_t res = mipp_{{func}}_{{dt_ext}}(r1);"""

OP_3ARGS_2REG_1MSK = """\t{{reg_type}} r3 = mipp_{{func}}_{{dt_ext}}(r1, r2, m1);\n\t{{reg_type_scalar}} s3 = mipp_scalar_{{func}}_{{dt_ext}}(s1, s2, ms1);"""
OP_3ARGS_1MSK_2REG = """\t{{reg_type}} r3 = mipp_{{func}}_{{dt_ext}}(m1, r1, r2);\n\t{{reg_type_scalar}} s3 = mipp_scalar_{{func}}_{{dt_ext}}(ms1, s1, s2);"""


OP_1ARG_1MASK = """\t{{msk_type}} m3 = mipp_{{func}}_{{dt_ext}}(m1); {{reg_type}} r3 = mipp_toreg_{{dt_ext}}(m3);
\t{{msk_type_scalar}} ms3 = mipp_scalar_{{func}}_{{dt_ext}}(ms1); {{reg_type_scalar}} s3 = mipp_scalar_toreg_{{dt_ext}}(ms3);"""

OP_2ARGS_2MASK = """\t{{msk_type}} m3 = mipp_{{func}}_{{dt_ext}}(m1, m2);\n\t{{reg_type}} r3 = mipp_toreg_{{dt_ext}}(m3);
\t{{msk_type_scalar}} ms3 = mipp_scalar_{{func}}_{{dt_ext}}(ms1, ms2); {{reg_type_scalar}} s3 = mipp_scalar_toreg_{{dt_ext}}(ms3);"""

OP_3ARGS_REG = """\t{{reg_type}} r4 = mipp_{{func}}_{{dt_ext}}(r1, r2, r3);
\t{{reg_type_scalar}} s4 = mipp_scalar_{{func}}_{{dt_ext}}(s1, s2, s3);
"""


OP_CAST = """\t{{reg2_type}} r2 = mipp_cast_{{dt1_ext}}_{{dt2_ext}}(r1);\n\t{{reg2_scalar_type}} s2 = mipp_scalar_cast_{{dt1_ext}}_{{dt2_ext}}(s1);"""
OP_CAST_MSK = """\t{{msk2_type}} m2 = mipp_cast_k_{{dt1_ext}}_{{dt2_ext}}(m1);\n\t{{msk2_scalar_type}} ms2 = mipp_scalar_cast_k_{{dt1_ext}}_{{dt2_ext}}(ms1);"""
# --------------------------------------------
# OPERATION IN LOOP BODY
# ------------------------------------------

# LB_SET_OP = """\t\t{{dt_ext}}_t res = inputs1[i];"""
# LB_SET_SCALAR_OP = """\t\t{{dt_ext}}_t res = input1;"""

# LB_REG_BINOP = """"""

# LB_CMP_2REG = """\t\tbool res = inputs1[i] {{op}} inputs2[i];"""

# LB_CAST_2ARGS = """\t\t{{dt2_ext}}_t res = inputs2[i];"""

# LB_REG_BINOP_FLOAT_WORKAROUND = """{% if is_int %}""" + LB_REG_BINOP + """{% else %}
#         \t{{dt_ext}}_t res = std::bit_cast<{{dt_ext}}_t,uint{{type_size}}_t>(
# \t\t\t\tstd::bit_cast<uint{{type_size}}_t,{{dt_ext}}_t>(inputs1[i]) 
# \t\t\t\t{{op}} 
# \t\t\t\tstd::bit_cast<uint{{type_size}}_t,{{dt_ext}}_t>(inputs2[i]));{% endif %}"""

# --------------------------------------------
# ASSERTS IN LOOP BODY
# ------------------------------------------

AS_REG_BINOP = """\t\tREQUIRE(mipp_get_{{dt_ext}}(r3, i) == mipp_scalar_get_{{dt_ext}}(s3, i));"""
AS_CMP_2REG = """REQUIRE(mipp_get_{{dt_ext}}(r3, i) == mipp_scalar_get_{{dt_ext}}(s3, i));"""
AS_LOAD = """\t\tREQUIRE(mipp_get_{{dt_ext}}(r1, i) == mipp_scalar_get_{{dt_ext}}(s1,i));"""

AS_STORE = """\t\tREQUIRE(inputs2[i] == mipp_scalar_get_{{dt_ext}}(s1,i));"""

AS_3ARGS = """\t\tREQUIRE(mipp_get_{{dt_ext}}(r4, i) == mipp_scalar_get_{{dt_ext}}(s4, i));"""
AS_3ARGS_TOL = """\t\t{{dt_ext}}_t res1 = mipp_get_{{dt_ext}}(r4, i);
\t\t{{dt_ext}}_t res2 = mipp_scalar_get_{{dt_ext}}(s4, i);
\t\t{{dt_ext}}_t tol  = 1e-5f * abs_diff::abs_diff(res2) + 1.0f;
\t\t{{dt_ext}}_t diff = abs_diff::abs_diff(res1, res2);
\t\tREQUIRE(diff <= tol);"""


AS_CAST_2ARGS = """\t\tREQUIRE(mipp_get_{{dt2_ext}}(r2, i) == mipp_scalar_get_{{dt2_ext}}(s2, i));"""
AS_CAST_2ARGS_MSK = """\t\tif(res) REQUIRE( (!!mipp_get_k_{{dt2_ext}}(m2, i)) == (!!mipp_scalar_get_k_{{dt2_ext}}(s2, i)) );"""

AS_REG_BINOP_FLOAT_WORKAROUND = """{% if is_int %}""" + AS_REG_BINOP + """{% else %}
\n\t\tREQUIRE(std::bit_cast<uint{{type_size}}_t,{{dt_ext}}_t>(mipp_get_{{dt_ext}}(r3, i))\
\n\t\t\t==
\t\t\tstd::bit_cast<uint{{type_size}}_t,{{dt_ext}}_t>(res) );
{% endif %}"""

AS_CMP_BINOP_FLOAT_WORKAROUND = """{% if is_int %}""" + AS_CMP_2REG + """{% else %}
\n\t\tREQUIRE(std::bit_cast<uint{{type_size}}_t,{{dt_ext}}_t>(mipp_get_{{dt_ext}}(r3, i))\
    \n\t\t\t==
    \t\tstd::bit_cast<uint{{type_size}}_t,{{dt_ext}}_t>(mipp_scalar_get_{{dt_ext}}(s3,i)) );
{% endif %}"""

# both value must be either 0 or non-zero. 
AS_CMP_2REG_LOGI = """REQUIRE( (!!mipp_get_{{dt_ext}}(r3, i)) == (!!mipp_scalar_get_{{dt_ext}}(s3, i)) );"""
AS_CMP_BINOP_LOGI_FLOAT_WORKAROUND = """{% if is_int %}""" + AS_CMP_2REG + """{% else %} 
\n\t\tREQUIRE( (!!mipp_get_{{dt_ext}}(r3, i)) == (!!mipp_scalar_get_{{dt_ext}}(s3,i)) );
{% endif %}"""

AS_CMP_TOMSK="""\t\tREQUIRE( (!!mipp_get_{{dt_ext}}(r3, i)) == (!!mipp_scalar_get_{{dt_ext}}(s3,i)) );"""

shape_templates = {
    SHAPE_RET_REG_2ARGS_REG: TemplateParts( # add, sub, div, mul
        func_decl=FUNC_DECL,
        decl=DECL_2ARGS,
        init=INIT_2ARGS,
        load=LOAD_2ARGS_REG,
        operation=OP_REG_BINOP,
        loop_body="",
        loop_assert=AS_REG_BINOP,
    ),
    SHAPE_RET_MSK_2ARGS_REG: TemplateParts( # cmpeq, cmpneq, cmpgt, ...
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
        operation="",  # load is in LOAD_1ARG_REG line already
        loop_body="",
        loop_assert=AS_LOAD,
    ),
    SHAPE_RET_VOID_2ARGS_PTR_REG: TemplateParts( # store, storeu
        func_decl=FUNC_DECL,
        decl=DECL_2ARGS,
        init=INIT_1ARG,     # only inputs1 needs init; inputs2 is output
        load=LOAD_1ARG_REG,     # store uses r1 loaded from inputs1
        operation=OP_STORE,
        loop_body="",
        loop_assert=AS_STORE,
    ),

    SHAPE_RET_REG_1ARG_NELE: TemplateParts( # set
        func_decl=FUNC_DECL,
        decl=DECL_1ARG,
        init=INIT_1ARG,
        load="""\t{{reg_type}} r1 = mipp_{{func}}_{{dt_ext}}(inputs1);\n\t{{reg_type_scalar}} s1 = mipp_scalar_{{func}}_{{dt_ext}}(inputs1);""",
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
        decl=DECL_GET_CATCH_SEED,
        init="",
        load=LOAD_SET0_REG,
        operation=OP_REG_NOOP,
        loop_body="",
        loop_assert=AS_REG_BINOP + """\t\tREQUIRE(mipp_get_{{dt_ext}}(r3, i) == 0);"""
    ),
    
    SHAPE_RET_MSK_0ARG: TemplateParts( # set0_k
        func_decl=FUNC_DECL,
        decl=DECL_GET_CATCH_SEED,
        init="",
        load=LOAD_SET0_MASK,
        operation=OP_TOREG,
        loop_body="",
        loop_assert= AS_CMP_BINOP_LOGI_FLOAT_WORKAROUND
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
        loop_assert= AS_CMP_BINOP_LOGI_FLOAT_WORKAROUND,
    ),
    
    SHAPE_RET_VAL_1ARG_REG: TemplateParts( # getfirst, hadd_to_scal
        func_decl=FUNC_DECL,
        decl=DECL_1ARG,
        init=INIT_1ARG,
        load=LOAD_1ARG_REG,
        operation="",
        loop_body="",
        loop_assert="\t\tREQUIRE(mipp_{{func}}_{{dt_ext}}(r1) == mipp_scalar_{{func}}_{{dt_ext}}(s1));",
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
    
    SHAPE_RET_MSK_2ARGS_MSK: TemplateParts( # andb_k orb_k xorb_k andnb_k
        func_decl=FUNC_DECL,
        decl=DECL_2ARGS_INT32+DECL_G_SNIPPET,
        init=INIT_2ARGS_DIS,
        load=LOAD_2ARGS_MASK,
        operation=OP_2ARGS_2MASK,
        loop_body="",
        loop_assert=AS_CMP_BINOP_LOGI_FLOAT_WORKAROUND,
    ),
    
    # #this shape covers 
    # #various functions 
    # #i.e : notb, sqrt, cast, hadd, hmul, hmin, hmax, round
    # #since the asserts for these function will vary
    # #each func will override some parts of the template 
    SHAPE_RET_REG_1ARG_REG: TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_1ARG,
        init=INIT_1ARG,
        load=LOAD_1ARG_REG,
        operation=OP_REG_UNOP,
        loop_body="",
        loop_assert=AS_CMP_BINOP_FLOAT_WORKAROUND,
    ),
    
    SHAPE_RET_MSK_1ARG_MSK: TemplateParts( # notb_k, and cast_k
        func_decl=FUNC_DECL,
        decl=DECL_1ARG_INT32+DECL_G_SNIPPET,
        init=INIT_1ARG_DIS,
        load=LOAD_1ARG_MASK,
        operation=OP_1ARG_1MASK,
        loop_body="",
        loop_assert=AS_CMP_BINOP_FLOAT_WORKAROUND,
    ),
    
    SHAPE_RET_REG_1ARG_MSK: TemplateParts( # toreg
        func_decl=FUNC_DECL,
        decl=DECL_1ARG_INT32+DECL_G_SNIPPET,
        init=INIT_1ARG_DIS,
        load=LOAD_1ARG_MASK,
        operation=OP_TOREG,
        loop_body="",
        loop_assert=AS_CMP_BINOP_FLOAT_WORKAROUND,
    ),
    
    # #loop body will be overridden 
    # #by each func using this shape
    SHAPE_RET_REG_3ARGS_REG: TemplateParts( # fmadd, fmsub, fnmadd, fnmsub
        func_decl=FUNC_DECL,
        decl=DECL_3ARGS,
        init=INIT_3ARGS,
        load=LOAD_3ARGS_REG,
        operation=OP_3ARGS_REG,
        loop_body="",
        loop_assert=AS_3ARGS_TOL,
    ),
    
    # #testz, ugly template but only used for testz so ig it's fine
    SHAPE_RET_I32_2ARGS_MSK : TemplateParts(
        func_decl=FUNC_DECL,
        decl="",
        init="",
        load="\t{{msk_type}} m1 = mipp_set1_k_{{dt_ext}}(1); \n\t{{msk_type}} m2 = mipp_set1_k_{{dt_ext}}(0);",
        operation="",
        loop_body="",
        loop_assert="\tREQUIRE(mipp_testz_{{dt_ext}}(m1, m1) == 0);\n\tREQUIRE(mipp_testz_{{dt_ext}}(m2, m2) != 0);",
    ),
   
    # testz_2 
    SHAPE_RET_I32_1ARG_MSK : TemplateParts(
        func_decl=FUNC_DECL,
        decl="",
        init="",
        load="\t{{msk_type}} m1 = mipp_set1_k_{{dt_ext}}(1); \n\t{{msk_type}} m2 = mipp_set1_k_{{dt_ext}}(0);",
        operation="",
        loop_body="",
        loop_assert="\tREQUIRE(mipp_testz_2_{{dt_ext}}(m1) == 0);\n\tREQUIRE(mipp_testz_2_{{dt_ext}}(m2) != 0);",
    ),
    
    SHAPE_RET_REG_3ARGS_1MSK_2REG : TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_1ARG_INT32,
        init=INIT_1ARG,
        load=LOAD_1ARG_MASK + "\n" + LOAD_SET1_2ARGS_REG,
        operation=OP_3ARGS_1MSK_2REG,
        loop_body="",
        loop_assert=AS_REG_BINOP,
    ),
    
    # tomsk
    SHAPE_RET_MSK_1ARG_REG : TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_1ARG,
        init=INIT_1ARG,
        load=LOAD_1ARG_REG,
        operation="""\t{{msk_type}} m1 = mipp_tomsk_{{dt_ext}}(r1);\n{{reg_type}} r3 = mipp_toreg_{{dt_ext}}(m1);
{{msk_type_scalar}} ms1 = mipp_scalar_tomsk_{{dt_ext}}(s1);\n\t{{reg_type_scalar}} s3 = mipp_scalar_toreg_{{dt_ext}}(ms1);""",
        loop_body="",
        loop_assert=AS_CMP_TOMSK,
    ),
    
    
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

deny = {
    #"hadd_to_scal", # hadd is wrong on avx2 for int16.
}


LAYER_OVERRIDES = {
    

    
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
    

#         "loop_body": """\t\t{{dt_ext}}_t res = std::round(inputs1[i]);""",
#     },
#     "div2": {
#         "loop_body": """\t\t{{dt_ext}}_t res = inputs1[i] / 2;""",
#     },
    
#     "div4": {
#         "loop_body": """\t\t{{dt_ext}}_t res = inputs1[i] / 4;""",
#     },
    # Define CUSTOM overflow workarounds
    "add" : {
        "loop_assert" :
"""
\t\tbool ov = ovf::will_add_overflow<{{dt_ext}}_t>(mipp_get_{{dt_ext}}(r1, i), mipp_get_{{dt_ext}}(r2, i));
\t\tif(ov) {
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
    
    "div" : {
        "loop_assert" :"""
\t\tif(mipp_get_{{dt_ext}}(r2, i) == 0) {
\t\t\tINFO("Division by zero, skipping assert");
\t\t}else{\n\t"""+ AS_REG_BINOP + """\n\t\t}"""},
    
    "hadd_to_scal" : {
        "loop_assert" :"""\t\tbool ov = false; {{dt_ext}}_t res = 0;
\t\tfor(int j = 0; j < {{size}}; j++){
\t\t\tov |= ovf::will_add_overflow<{{dt_ext}}_t>(res, inputs1[j]);
\t\t\tif(ov) break;
\t\t\tres += inputs1[j];
\t\t}
\t\tif(ov) {
\t\t\tINFO("Overflow occurred, skipping assert");
\t\t}else{\n\t"""
+ "\t\t {{dt_ext}}_t res1 = mipp_{{func}}_{{dt_ext}}(r1);\n \t\t{{dt_ext}}_t res2 = mipp_scalar_{{func}}_{{dt_ext}}(s1);\n"
+ "{% if is_int%}"
+ "\t\tREQUIRE(abs_diff::abs_diff(res1,res2) == 0);"
+ "{% else %}"
+ "\n\t\t{{dt_ext}}_t tol  = 1e-5f * abs_diff::abs_diff(res2) + 1.0f;"
+ "\n\t\t{{dt_ext}}_t diff = abs_diff::abs_diff(res1, res2);"
+ "\n\t\tREQUIRE(diff <= tol);"
+ "{% endif %}"
+ """\n\t\t}""",
    },
    
    
    "hadd": {
        "loop_assert": """\t\tbool ov = false; {{dt_ext}}_t res = 0;
\t\tfor(int j = 0; j < {{size}}; j++){
\t\t\tov |= ovf::will_add_overflow<{{dt_ext}}_t>(res, inputs1[j]);
\t\t\tif(ov) break;
\t\t\tres += inputs1[j];
\t\t}
\t\tif(ov) {
\t\t\tINFO("Overflow occurred, skipping assert");
\t\t}else{\n\t"""
+ "\t\t {{dt_ext}}_t res1 = mipp_get_{{dt_ext}}( r3,0);\n \t\t{{dt_ext}}_t res2 = mipp_scalar_get_{{dt_ext}}(s3,0);\n"
+ "{% if is_int%}"
+ "\t\tREQUIRE(abs_diff::abs_diff(res1,res2) == 0);"
+ "{% else %}"
+ "\n\t\t{{dt_ext}}_t tol  = 1e-5f * abs_diff::abs_diff(res2) + 1.0f;"
+ "\n\t\t{{dt_ext}}_t diff = abs_diff::abs_diff(res1, res2);"
+ "\n\t\tREQUIRE(diff <= tol);;"
+ "{% endif %}"
+ """\n\t\t}""",
    },
    
    "hmul": {
        "loop_assert": """\t\tbool ov = false; {{dt_ext}}_t res = 1;
\t\tfor(int j = 0; j < {{size}}; j++){
\t\t\tov |= ovf::will_mul_overflow<{{dt_ext}}_t>(res, inputs1[j]);
\t\t\tif(ov) break;
\t\t\tres *= inputs1[j];
\t\t}
\t\tif(ov) {
\t\t\tINFO("Overflow occurred, skipping assert");
\t\t}else{\n\t"""+ "\t\t {{dt_ext}}_t res1 = mipp_get_{{dt_ext}}(r3,0);\n \t\t{{dt_ext}}_t res2 = mipp_scalar_get_{{dt_ext}}(s3,0);\n"
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
        "loop_assert": """\tREQUIRE(mipp_get_{{dt_ext}}(r3, 0) == mipp_scalar_get_{{dt_ext}}(s3, 0));""",
    },
    
    
    "hmax": {
        "loop_assert": """\tREQUIRE(mipp_get_{{dt_ext}}(r3, 0) == mipp_scalar_get_{{dt_ext}}(s3, 0));""",
    },
    
    "rsqrt" : {
# if inputs1[i] < 0 the result is a NaN and the assert will fail bc of how nan comparison works. 
# so skip in that case
        "loop_assert": """\t\tif(inputs1[i] < 0) {
\t\t\tINFO("Input is negative, result is NaN, skipping assert");
\t\t}else{\n\t"""+ "\t\t {{dt_ext}}_t res1 = mipp_get_{{dt_ext}}(r3,i);\n \t\t{{dt_ext}}_t res2 = mipp_scalar_get_{{dt_ext}}(s3,i);\n"
+ "\n\t\t{{dt_ext}}_t tol  = 1e-5f * abs_diff::abs_diff(res2) + 1.0f;"
+ "\n\t\t{{dt_ext}}_t diff = abs_diff::abs_diff(res1, res2);"
+ "\n\t\tREQUIRE(diff <= tol);;"
+ """\n\t\t}""",
    },
    
    # sometimes produces different bitwise results that both represent the same float value. So just compare w == instead of bitwise asssertion.
    # when fractional part is exactly 0.5 round and roundf from math.h round to upper int 
    # while some round intrinsics round to lower int. So we skip assert in that case.
    "round": {
        "loop_assert": "\t\t{{dt_ext}}_t fractional_part = inputs1[i] - std::floor(inputs1[i]);\n" +
        "\t\tif(fractional_part == 0.5f) {\n" +
        "\t\t\tINFO(\"Fractional part is exactly 0.5, different rounding methods may round differently, skipping assert\");\n" +
        "\t\t}else{\n\t\t\tREQUIRE(mipp_get_{{dt_ext}}(r3, i) == mipp_scalar_get_{{dt_ext}}(s3, i));\n\t\t}",
        },
    
    
    "cast": {
        "func_decl": """void test_cmipp_cast_{{dt1_ext}}_{{dt2_ext}}(){""",
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
        "func_decl": """void test_cmipp_cast_k_{{dt1_ext}}_{{dt2_ext}}(){""",
        "decl": DECL_CAST_2ARGS_MSK,
        "init": INIT_CAST_2ARGS,
        "load": LOAD_CAST_2ARGS_MASK,
        "operation": OP_CAST_MSK,
        "loop_body": "",
        "loop_assert": """for(size_t i = 0; i < {{size}} * sizeof({{dt1_ext}}_t) / sizeof({{dt2_ext}}_t); i++){\n""" +AS_CAST_2ARGS_MSK + "\n\t}",
    },
    
#\t\tREQUIRE(std::abs(mipp_{{func}}_{{dt_ext}}(r1) - mipp_scalar_{{func}}_{{dt_ext}}(s1)) < 1e-2);

}

NO_LOOP_FUNCS = {"hadd", "hmul", "hmin", "hmax", 
                  "getfirst", "testz", 
                 "testz_2", "cast","cast_k",
                 "hadd_to_scal"
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
    for f in NO_LOOP_FUNCS:
        if f in gen_test_dict:
            gen_test_dict[f]["template"] = GENERIC_NO_LOOP
    return gen_dict

gen_test_dict = build_layer_gen_test_dict(
    layer_name="c",
    template=GENERIC_FOR_LOOP,
    mipp_funcs=mipp_funcs,
    shape_templates=shape_templates,
    deny_funcs=deny,
)

gen_test_dict = apply_overrides(gen_test_dict)