from headers_def import mipp_funcs
from .templates import GENERIC_FOR_LOOP, GENERIC_NO_LOOP
from .common import (
    TemplateParts,
    build_layer_gen_test_dict,
    SHAPE_RET_REG_2ARGS_REG,
    SHAPE_RET_MSK_2ARGS_REG,  # cmple, cmplt, cmpgt, cmpge, cmpeq, cmpneq
    SHAPE_RET_REG_1ARG_PTR,
    SHAPE_RET_VOID_2ARGS_PTR_REG,
    SHAPE_RET_VAL_2ARGS_REG_VAL,  # get
    SHAPE_RET_REG_1ARG_NELE,  # set
    SHAPE_RET_MSK_1ARG_NELE,  # set_k
    SHAPE_RET_REG_1ARG_VAL,  # set1
    SHAPE_RET_MSK_1ARG_I32,  # set1_k
    SHAPE_RET_REG_0ARG,  # set0
    SHAPE_RET_MSK_0ARG,  # set0_k
    SHAPE_RET_VAL_2ARGS_MSK_VAL,  # get_k
    SHAPE_RET_VAL_1ARG_REG,  # getfirst,hadd_to_scal
    SHAPE_RET_REG_3ARGS_2REG_1MSK,  # blend
    SHAPE_RET_MSK_2ARGS_MSK,  # andb_k orb_k xorb_k andnb_k
    SHAPE_RET_REG_1ARG_REG,  # notb
    SHAPE_RET_MSK_1ARG_MSK,  # notb_k and cast_k
    SHAPE_RET_REG_1ARG_MSK,  # toreg
    SHAPE_RET_REG_3ARGS_REG,  # fmadd, fmsub
    SHAPE_RET_I32_2ARGS_MSK,  # testz
    SHAPE_RET_I32_1ARG_MSK,  # testz2
    SHAPE_RET_REG_3ARGS_1MSK_2REG,  # maskz_add
    SHAPE_RET_MSK_1ARG_REG,  # tomsk
)

# --------------------------
# CPP fragments (LMUL: suffix + coeff)
# --------------------------

# --------------------------------------------
# FN decl
# --------------------------------------------
FUNC_DECL = """template <typename T>\nvoid test_cppmipp_{{func}}_{{lmul_suffix}}(){"""
FUNC_DECL_FLOAT_WORKAROUND = (
    " {% if is_int %} "
    + FUNC_DECL
    + " {% else %} template <typename T>\nvoid test_cppmipp_{{func}}_float{{type_size}}_{{lmul_suffix}}(){  {% endif %}"
)

# --------------------------------------------
# SCALAR VEC DECL
# --------------------------------------------
DECL_GET_CATCH_SEED = "\n\tstd::mt19937 seed(Catch::getSeed()+n);\n"

DECL_G_SNIPPET = """\tstd::mt19937 g;\n\tstd::uniform_int_distribution<uint16_t> dis(0, 1);"""

DECL_1ARG_INT32 = DECL_GET_CATCH_SEED + """ int32_t inputs1[{{size}} * {{lmul_coeff}}];"""
DECL_1ARG_SCALAR = DECL_GET_CATCH_SEED + """ \t T input1 = 12;"""
DECL_1ARG_SCALAR_INT32 = DECL_GET_CATCH_SEED + """ \tint32_t input1 = 12;"""

DECL_2ARGS = DECL_GET_CATCH_SEED + """ T inputs1[{{size}} * {{lmul_coeff}}],inputs2[{{size}} * {{lmul_coeff}}];"""
DECL_1ARG = DECL_GET_CATCH_SEED + """ T inputs1[{{size}} * {{lmul_coeff}}];"""
DECL_2ARGS_FOR_STORE = DECL_GET_CATCH_SEED + """ T inputs1[{{size}} * {{lmul_coeff}}],inputs2[{{size}} * {{lmul_coeff}}];"""

DECL_2ARGS_INT32 = DECL_GET_CATCH_SEED +  "\n\tint32_t inputs1[{{size}} * {{lmul_coeff}}],inputs2[{{size}} * {{lmul_coeff}}];"

DECL_3ARGS = DECL_GET_CATCH_SEED + """\n\tT inputs1[{{size}} * {{lmul_coeff}}],inputs2[{{size}} * {{lmul_coeff}}],inputs3[{{size}} * {{lmul_coeff}}];"""

DECL_CAST_2ARGS = DECL_GET_CATCH_SEED +  "\n\t{{dt2_ext}} inputs1[{{size}} * {{lmul_coeff}}];\n\tconstexpr size_t bytes = sizeof(inputs1);\n\t{{dt1_ext}}_t inputs2[bytes / sizeof({{dt1_ext}}_t)];"

DECL_CAST_2ARGS_MSK = DECL_GET_CATCH_SEED + "\n\tint32_t inputs1[{{size}} * {{lmul_coeff}}];\n\tconstexpr size_t bytes = sizeof(inputs1);\n\t{{dt1_ext}}_t inputs2[bytes / sizeof({{dt1_ext}}_t)];"
# --------------------------------------------
# SCALAR VEC INIT (unchanged)
# --------------------------------------------

INIT_2ARGS = """\tstd::iota(inputs1, inputs1 + {{size}} * {{lmul_coeff}}, 1);
\tfor(size_t i = 0; i < {{size}} * {{lmul_coeff}}; i++)
\t{
\t\tinputs1[i] = rnd::uniform<{{dt_ext}}>(seed);
\t\tinputs2[i] = rnd::uniform<{{dt_ext}}>(seed);
\t}
"""

INIT_2ARGS_NOUFLOW = INIT_2ARGS + """\tfor(size_t i = 0; i < {{size}} * {{lmul_coeff}}; i++)
\t{
\t\tinputs1[i] += inputs2[i];
\t}
"""

INIT_1ARG = """
\tfor(size_t i = 0; i < {{size}} * {{lmul_coeff}}; i++)
\t{
\t\tinputs1[i] = rnd::uniform<{{dt_ext}}>(seed);
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
\t\tinputs1[i] = rnd::uniform<{{dt_ext}}>(seed);
\t\tinputs2[i] = rnd::uniform<{{dt_ext}}>(seed);
\t\tinputs3[i] = rnd::uniform<{{dt_ext}}>(seed);
\t}
"""

INIT_CAST_2ARGS = """\tstd::iota(inputs1, inputs1 + {{size}} * {{lmul_coeff}}, 1);\n\tmemcpy(inputs2, inputs1, sizeof(inputs1));"""

# --------------------------------------------
# LOADS (LMUL-aware: second template parameter)
# --------------------------------------------

LOAD_2ARGS_REG = """\t{{reg_type}} r1 = mipp::load<{{dt_ext}}, {{lmul_coeff}}>(inputs1);
\t{{reg_type}} r2 = mipp::load<{{dt_ext}}, {{lmul_coeff}}>(inputs2);
\t{{reg_type_scalar}} s1 = mipp::load<{{dt_ext}}, {{lmul_coeff}}, mipp::ISA::SCALAR>(inputs1);
\t{{reg_type_scalar}} s2 = mipp::load<{{dt_ext}}, {{lmul_coeff}}, mipp::ISA::SCALAR>(inputs2);
"""

LOAD_1ARG_REG = """\t{{reg_type}} r1 = mipp::load<{{dt_ext}}, {{lmul_coeff}}>(inputs1);
\t{{reg_type_scalar}} s1 = mipp::load<{{dt_ext}}, {{lmul_coeff}}, mipp::ISA::SCALAR>(inputs1);
"""

LOAD_1ARG_MASK = """\t{{msk_type}} m1 = mipp::set_k<T, {{lmul_coeff}}>(inputs1);
\t{{msk_type_scalar}} ms1 = mipp::set_k<{{dt_ext}}, {{lmul_coeff}}, mipp::ISA::SCALAR>(inputs1);
"""

LOAD_1SCALAR_REG = """\t{{reg_type}} r1 = mipp::set1(input1);
\t{{reg_type_scalar}} s1 = mipp::set1<T, 1, mipp::ISA::SCALAR>(input1);
"""

LOAD_1SCALAR_MASK = """\t{{msk_type}} m1 = mipp::set1_k<T, {{lmul_coeff}}>(input1);
\t{{msk_type_scalar}} ms1 = mipp::set1_k<{{dt_ext}}, {{lmul_coeff}}, mipp::ISA::SCALAR>(input1);
"""

LOAD_SET0_REG = """\t{{reg_type}} r1 = mipp::set0<T, {{lmul_coeff}}>();
\t{{reg_type_scalar}} s1 = mipp::set0<T, {{lmul_coeff}}, mipp::ISA::SCALAR>();
"""

LOAD_SET0_MASK = """\t{{msk_type}} m1 = mipp::set0_k<T>();
\t{{msk_type_scalar}} ms1 = mipp::set0_k<{{dt_ext}}, {{lmul_coeff}}, mipp::ISA::SCALAR>();
"""

LOAD_SET1_2ARGS_REG = """\t{{reg_type}} r1 = mipp::set1((T)1); \n\t{{reg_type}} r2 = mipp::set1((T)2);
\t{{reg_type_scalar}} s1 = mipp::set1<T, {{lmul_coeff}}, mipp::ISA::SCALAR>((T)1); \n\t{{reg_type_scalar}} s2 = mipp::set1<T, {{lmul_coeff}}, mipp::ISA::SCALAR>((T)2);
"""

LOAD_2ARGS_MASK = """\t{{msk_type}} m1 = mipp::set_k<T>(inputs1); 
\t{{msk_type}} m2 = mipp::set_k<T>(inputs2);
\t{{msk_type_scalar}} ms1 = mipp::set_k<{{dt_ext}}, {{lmul_coeff}}, mipp::ISA::SCALAR>(inputs1);
\t{{msk_type_scalar}} ms2 = mipp::set_k<{{dt_ext}}, {{lmul_coeff}}, mipp::ISA::SCALAR>(inputs2);
"""

LOAD_3ARGS_REG = """\t{{reg_type}} r1 = mipp::load(inputs1);
\t{{reg_type}} r2 = mipp::load(inputs2);
\t{{reg_type}} r3 = mipp::load(inputs3);
\t{{reg_type_scalar}} s1 = mipp::load<{{dt_ext}}, {{lmul_coeff}}, mipp::ISA::SCALAR>(inputs1);
\t{{reg_type_scalar}} s2 = mipp::load<{{dt_ext}}, {{lmul_coeff}}, mipp::ISA::SCALAR>(inputs2);
\t{{reg_type_scalar}} s3 = mipp::load<{{dt_ext}}, {{lmul_coeff}}, mipp::ISA::SCALAR>(inputs3);
"""

LOAD_CAST_2ARGS = """\t{{reg1_type}} r1 = mipp::load<{{dt_ext}}, {{lmul_coeff}}>(inputs1);\n\t{{reg1_type_scalar}} s1 = mipp::load<{{dt_ext}}, {{lmul_coeff}}, mipp::ISA::SCALAR>(inputs1);"""

LOAD_CAST_2ARGS_MASK = """\t{{msk1_type}} m1 = mipp::set_k<T, {{lmul_coeff}}>(inputs1);\n\t{{msk1_type_scalar}} ms1 = mipp::set_k<{{dt_ext}}, {{lmul_coeff}}, mipp::ISA::SCALAR>(inputs1);"""


# --------------------------------------------
# OPERATIONS (LMUL via arg types; keep calls identical)
# --------------------------------------------

OP_REG_BINOP = """\t{{reg_type}} r3 = mipp::{{func}}(r1, r2);
\t{{reg_type_scalar}} s3 = mipp::{{func}}(s1, s2);
"""

OP_STORE = """\tmipp::store(inputs2, r1);"""

OP_REG_NOOP = """\t{{reg_type}} r3 = r1;\n\t{{reg_type_scalar}} s3 = s1;"""

OP_TOREG = """\t{{reg_type}} r3 = mipp::toreg(m1);\n\t{{reg_type_scalar}} s3 = mipp::toreg(ms1);"""
OP_SCAL_UNOP = """\tT res = mipp::{{func}}(r1);\n\tT sres = mipp::{{func}}(s1);"""

OP_3ARGS_2REG_1MSK = """\t{{reg_type}} r3 = mipp::{{func}}(r1, r2, m1);\n\t{{reg_type_scalar}} s3 = mipp::{{func}}(s1, s2, ms1);"""
OP_3ARGS_1MSK_2REG = """\t{{reg_type}} r3 = mipp::{{func}}(m1, r1, r2);\n\t{{reg_type_scalar}} s3 = mipp::{{func}}(ms1, s1, s2);"""

OP_2ARGS_2MASK = """\t{{msk_type}} m3 = mipp::{{func}}(m1, m2);\n\t{{reg_type}} r3 = mipp::toreg(m3);
\n\t{{msk_type_scalar}} ms3 = mipp::{{func}}(ms1, ms2);\n\t{{reg_type_scalar}} s3 = mipp::toreg(ms3);
"""

OP_REG_UNOP = """\t{{reg_type}} r3 = mipp::{{func}}(r1);\n\t{{reg_type_scalar}} s3 = mipp::{{func}}(s1);"""

OP_1ARG_1MASK = """\t{{msk_type}} m3 = mipp::{{func}}(m1); {{reg_type}} r3 = mipp::toreg(m3);
\n\t{{msk_type_scalar}} ms3 = mipp::{{func}}(ms1); {{reg_type_scalar}} s3 = mipp::toreg(ms3);"""

OP_CMP_2REG = """\t{{msk_type}} m3 = mipp::{{func}}(r1, r2); {{reg_type}} r3 = mipp::toreg(m3);
\t{{msk_type_scalar}} ms3 = mipp::{{func}}(s1, s2); {{reg_type_scalar}} s3 = mipp::toreg(ms3);
"""

OP_3ARGS_REG = """\t{{reg_type}} r4 = mipp::{{func}}(r1, r2, r3);
\t{{reg_type_scalar}} s4 = mipp::{{func}}(s1, s2, s3);
"""

OP_CAST = """\t{{reg2_type}} r2 = mipp::cast_{{dt1_ext}}(r1);\n\t{{reg2_type_scalar}} s2 = mipp::cast_{{dt1_ext}}(s1);"""
OP_CAST_MSK = """\t{{msk2_type}} m2 = mipp::cast_{{dt1_ext}}(m1);\n\t{{msk2_type_scalar}} ms2 = mipp::cast_{{dt1_ext}}(ms1);"""

# --------------------------------------------
# OPERATION IN LOOP BODY (unchanged)
# --------------------------------------------
# LB_REG_BINOP = """\t\tT res = inputs1[i] {{op}} inputs2[i];"""
# LB_SET_OP = """\t\tT res = inputs1[i];"""
# LB_SET_SCALAR_OP = """\t\tT res = input1;"""

# LB_CMP_2REG = """\t\tbool res = inputs1[i] {{op}} inputs2[i];"""
# LB_CAST_2ARGS = """\t\t{{dt1_ext}}_t res = inputs2[i];"""

# LB_REG_BINOP_FLOAT_WORKAROUND = """{% if is_int %}""" + LB_REG_BINOP + """{% else %}
#         \tT res = std::bit_cast<T,uint{{type_size}}_t>(
# \t\t\t\tstd::bit_cast<uint{{type_size}}_t,T>(inputs1[i]) 
# \t\t\t\t{{op}} 
# \t\t\t\tstd::bit_cast<uint{{type_size}}_t,T>(inputs2[i]));{% endif %}"""

# --------------------------------------------
# ASSERTS IN LOOP BODY (unchanged: mipp::get works with rvd<T,LMUL>)
# --------------------------------------------

AS_REG_BINOP = """\t\tREQUIRE(mipp::get(r3, i) == mipp::get(s3, i));"""
AS_CMP_2REG = """\t\tREQUIRE(mipp::get(r3, i) == mipp::get(s3, i));"""

AS_LOAD = """\t\tREQUIRE(mipp::get(r1, i) == mipp::get(s1, i));"""
AS_STORE = """\t\tREQUIRE(inputs2[i] == mipp::get(s1, i));"""

AS_3ARGS = """\t\tREQUIRE(mipp::get(r4, i) == mipp::get(s4, i));"""

AS_3ARGS_TOL = """\t\t{{dt_ext}} res1 = mipp::get(r4, i);
\t\t{{dt_ext}} res2 = mipp::get(s4, i);
\t\t{{dt_ext}} tol  = 1e-5f * abs_diff::abs_diff(res2) + 1.0f;
\t\t{{dt_ext}} diff = abs_diff::abs_diff(res1, res2);
\t\tREQUIRE(diff <= tol);"""

AS_CAST_2ARGS = """\t\tREQUIRE(mipp::get(r2, i) == mipp::get(s2, i));"""
AS_CAST_2ARGS_MSK = """\t\tif(res) REQUIRE(mipp::get(m2, i) != 0); else REQUIRE(mipp::get(m2, i) == 0);"""


AS_CMP_BINOP_LOGI_FLOAT_WORKAROUND = """REQUIRE(!! mipp::get(r3, i) == !!mipp::get(s3, i) );"""

shape_templates = {
    SHAPE_RET_REG_2ARGS_REG: TemplateParts( # add div sub mul subs andb andnb orb xorb
        func_decl=FUNC_DECL,
        decl=DECL_2ARGS,
        init=INIT_2ARGS,
        load=LOAD_2ARGS_REG,
        operation=OP_REG_BINOP,
        loop_body="",
        loop_assert=AS_REG_BINOP,
    ),
    SHAPE_RET_MSK_2ARGS_REG: TemplateParts( # cmpeq cmpneq cmpgt cmpge cmplt cmple
        func_decl=FUNC_DECL,
        decl=DECL_2ARGS,
        init=INIT_2ARGS,
        load=LOAD_2ARGS_REG,
        operation=OP_CMP_2REG,
        loop_body="",
        loop_assert=AS_CMP_BINOP_LOGI_FLOAT_WORKAROUND,
    ),
    # SHAPE_RET_REG_1ARG_PTR: TemplateParts(
    #     func_decl=FUNC_DECL,
    #     decl=DECL_1ARG,
    #     init=INIT_1ARG,
    #     load=LOAD_1ARG_REG,
    #     operation="",  # load is in LOAD_1ARG line already
    #     loop_body="",
    #     loop_assert=AS_LOAD,
    # ),
    # SHAPE_RET_VOID_2ARGS_PTR_REG: TemplateParts(
    #     func_decl=FUNC_DECL,
    #     decl=DECL_2ARGS_FOR_STORE,
    #     init=INIT_1ARG,  # only inputs1 needs init; inputs2 is output
    #     load=LOAD_1ARG_REG,  # store uses r1 loaded from inputs1
    #     operation=OP_STORE,
    #     loop_body="",
    #     loop_assert=AS_STORE,
    # ),
    # SHAPE_RET_VAL_2ARGS_REG_VAL: TemplateParts(
    #     func_decl=FUNC_DECL,
    #     decl=DECL_1ARG,
    #     init=INIT_1ARG,
    #     load=LOAD_1ARG_REG,
    #     operation=OP_REG_NOOP,
    #     loop_body="",
    #     loop_assert=AS_REG_BINOP,
    # ),
    # SHAPE_RET_REG_1ARG_NELE: TemplateParts(
    #     func_decl=FUNC_DECL,
    #     decl=DECL_1ARG,
    #     init=INIT_1ARG,
    #     load=LOAD_1ARG_REG,
    #     operation=OP_REG_NOOP,
    #     loop_body="",
    #     loop_assert=AS_REG_BINOP,
    # ),
    # SHAPE_RET_MSK_1ARG_NELE: TemplateParts(
    #     func_decl=FUNC_DECL,
    #     decl=DECL_1ARG_INT32,
    #     init=INIT_1ARG,
    #     load=LOAD_1ARG_MASK,
    #     operation=OP_TOREG,
    #     loop_body="",
    #     loop_assert=AS_CMP_2REG,
    # ),
    # SHAPE_RET_REG_1ARG_VAL: TemplateParts(
    #     func_decl=FUNC_DECL,
    #     decl=DECL_1ARG_SCALAR,
    #     init="",
    #     load=LOAD_1SCALAR_REG,
    #     operation=OP_REG_NOOP,
    #     loop_body="",
    #     loop_assert=AS_REG_BINOP,
    # ),
    # SHAPE_RET_MSK_1ARG_I32: TemplateParts(
    #     func_decl=FUNC_DECL,
    #     decl=DECL_1ARG_SCALAR_INT32,
    #     init="",
    #     load=LOAD_1SCALAR_MASK,
    #     operation=OP_TOREG,
    #     loop_body="",
    #     loop_assert=AS_CMP_2REG,
    # ),
    # SHAPE_RET_REG_0ARG: TemplateParts(
    #     func_decl=FUNC_DECL,
    #     decl=DECL_VECTOR_SIZE,
    #     init="",
    #     load=LOAD_SET0_REG,
    #     operation=OP_REG_NOOP,
    #     loop_body="",
    #     loop_assert=AS_REG_BINOP,
    # ),
    # SHAPE_RET_MSK_0ARG: TemplateParts(
    #     func_decl=FUNC_DECL,
    #     decl=DECL_VECTOR_SIZE,
    #     init="",
    #     load=LOAD_SET0_MASK,
    #     operation=OP_TOREG,
    #     loop_body="",
    #     loop_assert=AS_CMP_2REG,
    # ),
    # SHAPE_RET_VAL_2ARGS_MSK_VAL: TemplateParts(
    #     func_decl=FUNC_DECL,
    #     decl=DECL_1ARG_INT32,
    #     init=INIT_1ARG,
    #     load=LOAD_1ARG_MASK,
    #     operation=OP_TOREG,
    #     loop_body="",
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
    #     loop_body="\t\tT res = mipp::get(m1, i) ? mipp::get(r1, i) : mipp::get(r2, i);",
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
    #     load="\t{{msk_type}} m1 = mipp::set1_k<T, {{lmul_coeff}}>(1); \n\t{{msk_type}} m2 = mipp::set1_k<T, {{lmul_coeff}}>(0);",
    #     operation="",
    #     loop_body="",
    #     loop_assert="\tREQUIRE(mipp::testz(m1, m1) == 0);\n\tREQUIRE(mipp::testz(m2, m2) != 0);",
    # ),
    # SHAPE_RET_I32_1ARG_MSK: TemplateParts(
    #     func_decl=FUNC_DECL,
    #     decl="",
    #     init="",
    #     load="\t{{msk_type}} m1 = mipp::set1_k<T, {{lmul_coeff}}>(1); \n\t{{msk_type}} m2 = mipp::set1_k<T, {{lmul_coeff}}>(0);",
    #     operation="",
    #     loop_body="",
    #     loop_assert="\tREQUIRE(mipp::testz_2(m1) == 0);\n\tREQUIRE(mipp::testz_2(m2) != 0);",
    # ),
    # SHAPE_RET_REG_3ARGS_1MSK_2REG: TemplateParts(
    #     func_decl=FUNC_DECL,
    #     decl=DECL_1ARG_INT32,
    #     init=INIT_1ARG,
    #     load=LOAD_1ARG_MASK + "\n" + LOAD_SET1_2ARGS_REG,
    #     operation=OP_3ARGS_1MSK_2REG,
    #     loop_body="\t\tT res = mipp::get(m1, i) ? 3 : 0;",
    #     loop_assert=AS_REG_BINOP,
    # ),
    # SHAPE_RET_MSK_1ARG_REG: TemplateParts(
    #     func_decl=FUNC_DECL,
    #     decl=DECL_1ARG,
    #     init=INIT_1ARG,
    #     load=LOAD_1ARG_REG,
    #     operation="\t{{msk_type}} m1 = mipp::tomsk(r1);\n{{reg_type}} r3 = mipp::toreg(m1);",
    #     loop_body="\t\tT res = inputs1[i] ? 1 : 0;",
    #     loop_assert=AS_CMP_2REG,
    # ),
}

deny = {
    # Keep same deny list as layer_cpp.py
    "maskzld",
    "maskst",
}

LAYER_OVERRIDES = {
#     "sub": {"init": INIT_2ARGS_NOUFLOW},
#     "div": {
#         "loop_assert": """\tREQUIRE(
# #if defined(MIPP_NEON) && !defined(__aarch64__)
# 			std::abs(mipp::get(r3, i) - res) < 1e-2
# #else
# 			mipp::get(r3, i) == res
# #endif
# 		);""",
#     },
#     "andnb_k": {"loop_body": """\t\tT res = ~(inputs1[i]) & (inputs2[i]);"""},
#     "notb": {"loop_body": """\t\tT res = ~(inputs1[i]);"""},
#     "fmadd": {"loop_body": """\t\tT res = inputs1[i] * inputs2[i] + inputs3[i];"""},
#     "fnmadd": {"loop_body": """\t\tT res = -(inputs1[i] * inputs2[i]) + inputs3[i];"""},
#     "fmsub": {"loop_body": """\t\tT res = inputs1[i] * inputs2[i] - inputs3[i];"""},
#     "fnmsub": {"loop_body": """\t\tT res = -(inputs1[i] * inputs2[i]) - inputs3[i];"""},
#     "max": {"loop_body": """\t\tT res = std::max(inputs1[i], inputs2[i]);"""},
#     "min": {"loop_body": """\t\tT res = std::min(inputs1[i], inputs2[i]);"""},
#     "sqrt": {"loop_body": """\t\tT res = std::sqrt(inputs1[i]);"""},
#     "rsqrt": {
#         "loop_body": """\t\tT res = 1.0 / std::sqrt(inputs1[i]);""",
#         "loop_assert": """\tREQUIRE(std::abs(mipp::get(r3, i) - res) < 1e-2);""",
#     },
#     "hadd": {
#         "loop_body": """\tT res = 0; uint64_t ures = 0;
# \tfor(int j = 0; j < vectorSize; j++){
# \t\tres {{op}} inputs1[j];
# \t\tures{{op}} inputs1[j];
# \t}""",
#         "loop_assert": """if((uint64_t)res==ures)\tREQUIRE(mipp::get(r3, 0) == res);""",
#     },
#     "hmul": {
#         "loop_body": """\tT res = 1;
# \tfor(int j = 0; j < vectorSize; j++)
# \t\tres {{op}} inputs1[j];""",
#         "loop_assert": """\tREQUIRE(mipp::get(r3, 0) == res);""",
#     },
#     "hmin": {
#         "loop_body": """\tT res = inputs1[0];
# \tfor(int j = 1; j < vectorSize; j++)
# \t\tres = std::min(res, inputs1[j]);""",
#         "loop_assert": """\tREQUIRE(mipp::get(r3, 0) == res);""",
#     },
#     "hmax": {
#         "loop_body": """\tT res = inputs1[0];
# \tfor(int j = 1; j < vectorSize; j++)
# \t\tres = std::max(res, inputs1[j]);""",
#         "loop_assert": """\tREQUIRE(mipp::get(r3, 0) == res);""",
#     },
#     "hadd_to_scal": {
#         "loop_body": """\tT res1 = 0; uint64_t ures1 = 0;
# \tfor(int j = 0; j < vectorSize; j++){
# \t\tres1 += inputs1[j];
# \t\tures1 += inputs1[j];
# \t}""",
#         "loop_assert": """\t\tif((uint64_t)res1 == ures1) REQUIRE(res == res1);""",
#     },
#     "msb": {"loop_body": "\tT res = inputs1[i] & ((T)1 << (sizeof(T)*8 - 1));"},
#     "cast": {
#         "decl": DECL_CAST_2ARGS,
#         "init": INIT_CAST_2ARGS,
#         "load": LOAD_CAST_2ARGS,
#         "operation": OP_CAST,
#         "loop_body": """\tfor(size_t i = 0; i < vectorSize * sizeof({{dt2_ext}}) / sizeof({{dt1_ext}}_t); i++){\n"""
#         + LB_CAST_2ARGS,
#         "loop_assert": AS_CAST_2ARGS + "\n\t}",
#     },
#     "cast_k": {
#         "decl": DECL_CAST_2ARGS_MSK,
#         "init": INIT_CAST_2ARGS,
#         "load": LOAD_CAST_2ARGS_MASK,
#         "operation": OP_CAST_MSK,
#         "loop_body": """\tfor(size_t i = 0; i < vectorSize * sizeof(int32_t) / sizeof({{dt1_ext}}_t); i++){\n"""
#         + LB_CAST_2ARGS,
#         "loop_assert": AS_CAST_2ARGS_MSK + "\n\t}",
#     },
#     # Float workarounds (preserve exactly, just ensure FUNC_DECL_FLOAT_WORKAROUND is LMUL-aware)
#     "andb": {
#         "func_decl": FUNC_DECL_FLOAT_WORKAROUND,
#         "loop_body": LB_REG_BINOP_FLOAT_WORKAROUND,
#         "loop_assert": AS_REG_BINOP_FLOAT_WORKAROUND,
#     },
#     "orb": {
#         "func_decl": FUNC_DECL_FLOAT_WORKAROUND,
#         "loop_body": LB_REG_BINOP_FLOAT_WORKAROUND,
#         "loop_assert": AS_REG_BINOP_FLOAT_WORKAROUND,
#     },
#     "xorb": {
#         "func_decl": FUNC_DECL_FLOAT_WORKAROUND,
#         "loop_body": LB_REG_BINOP_FLOAT_WORKAROUND,
#         "loop_assert": AS_REG_BINOP_FLOAT_WORKAROUND,
#     },
#     "notb": {
#         "func_decl": FUNC_DECL_FLOAT_WORKAROUND,
#         "loop_body": "{%if is_int %}"
#         + """\t\tT res = ~(inputs1[i]);"""
#         + """{% else %}"""
#         + """\tT res = std::bit_cast<T,uint{{type_size}}_t>(
# \t\t\t~std::bit_cast<uint{{type_size}}_t,T>(inputs1[i]));\n"""
#         + """{% endif %}""",
#         "loop_assert": AS_REG_BINOP_FLOAT_WORKAROUND,
#     },
#     "andnb": {
#         "func_decl": FUNC_DECL_FLOAT_WORKAROUND,
#         "loop_body": "{% if is_int %}"
#         + "\t\tT res = ~(inputs1[i]) & (inputs2[i]);"
#         + "{% else %}"
#         + """\tT res = std::bit_cast<T,uint{{type_size}}_t>(
# \t\t\t~std::bit_cast<uint{{type_size}}_t,T>(inputs1[i]) 
# \t\t\t&
# \t\t\tstd::bit_cast<uint{{type_size}}_t,T>(inputs2[i]) );\n"""
#         + """{% endif %}""",
#         "loop_assert": AS_REG_BINOP_FLOAT_WORKAROUND,
#     },
#     "msb": {
#         "func_decl": FUNC_DECL_FLOAT_WORKAROUND,
#         "loop_body": "{% if is_int %}"
#         + "\tT res = inputs1[i] & ((T)1 << (sizeof(T)*8 - 1));"
#         + "{% else %}"
#         + """\tT res = 
#         std::bit_cast<T,uint{{type_size}}_t>(
# \t\t\tstd::bit_cast<uint{{type_size}}_t, T>(inputs1[i])
# \t\t\t&((uint{{type_size}}_t)1 << (sizeof(T)*8 - 1))
# \t\t);\n"""
#         + """{% endif %}""",
#         "loop_assert": AS_REG_BINOP_FLOAT_WORKAROUND,
#     },
#     "notb_k": {
#         "func_decl": FUNC_DECL_FLOAT_WORKAROUND,
#         "loop_body": """{%if is_int %}"""
#         + """\t\tT res = ~(inputs1[i]);"""
#         + """{% else %} 
# uint{{type_size}}_t expected_bits = (inputs1[i] != 0)
#   ? 0
#   : -1;

# uint{{type_size}}_t got_bits = std::bit_cast<uint{{type_size}}_t>(mipp::get(r3, i));
# REQUIRE(got_bits == expected_bits);"""
#         + """{%endif%}""",
#         "loop_assert": "{% if is_int %}"
#         + AS_REG_BINOP
#         + "{% else %}REQUIRE( (!(!(got_bits))) == (!(!(expected_bits))) ); {% endif %}",
#     },
#     "round": {
#         "init": """\tstd::iota(inputs1, inputs1 + vectorSize, 1);
# \tstd::mt19937 g;
# std::uniform_real_distribution<float> dis(0.0, 1.0);
# \tfor(int i = 0; i < vectorSize; i++)
# \t{
# \t\tinputs1[i] += dis(g);
# \t}""",
#         "loop_body": """\t\tT res = std::round(inputs1[i]);""",
#     },
#     "div2": {"loop_body": """\t\tT res = inputs1[i] / 2;"""},
#     "div4": {"loop_body": """\t\tT res = inputs1[i] / 4;"""},

    "add" : {
        "loop_assert" :
"""
\t\tbool ov = ovf::will_add_overflow<T>(mipp::get(r1, i), mipp::get(r2, i));
\t\tif(ov) {
\t\t\tINFO("Overflow occurred, skipping assert");
\t\t}else{\n\t"""+ AS_REG_BINOP + """\n\t\t}"""},
    
    "sub" : {
        "loop_assert" :"""
\tbool ov = ovf::will_sub_overflow<T>(mipp::get(r1, i), mipp::get(r2, i));
\t\tif(ov) {
\t\t\tINFO("Overflow occurred, skipping assert");
\t\t}else{\n\t"""+ AS_REG_BINOP + """\n\t\t}"""},
    
    "mul" : {
        "loop_assert" :"""
\t\tbool ov = ovf::will_mul_overflow<T>(mipp::get(r1, i), mipp::get(r2, i));
\t\tif(ov) {
\t\t\tINFO("Overflow occurred, skipping assert");
\t\t}else{\n\t"""+ AS_REG_BINOP + """\n\t\t}"""},
    
    # division by zero is skipped + add some 
    # tolerance for float division to avoid precision issues.
    "div" : {
        "loop_assert" :"""
\t\tif(mipp::get(r2, i) == 0) {
\t\t\tINFO("Division by zero, skipping assert");
\t\t}else{\n\t"""+ "\t\t T res1 = mipp::get(r3, i);\n \t\tT res2 = mipp::get(s3, i);\n"
+ "\n\t\tT tol  = 1e-5f * abs_diff::abs_diff(res2) + 1.0f;"
+ "\n\t\tT diff = abs_diff::abs_diff(res1, res2);"
+ "\n\t\tREQUIRE(diff <= tol);"
+ """\n\t\t}""",
    },

    # always divivde by 2 so no 0 check
    "div2" : {
        "loop_assert" :"""
\t\t T res1 = mipp::get(r3, i);\n \t\tT res2 = mipp::get(s3, i);\n"""

+ "\n\t\tT tol  = 1e-5f * abs_diff::abs_diff(res2) + 1.0f;"
+ "\n\t\tT diff = abs_diff::abs_diff(res1, res2);"
+ "\n\t\tREQUIRE(diff <= tol);"
    },

    "div4" : {
        "loop_assert" :"""\t\t T res1 = mipp::get(r3, i);\n \t\tT res2 = mipp::get(s3, i);\n"""
+ "\n\t\tT tol  = 1e-5f * abs_diff::abs_diff(res2) + 1.0f;"
+ "\n\t\tT diff = abs_diff::abs_diff(res1, res2);"
+ "\n\t\tREQUIRE(diff <= tol);"
    },
}

NO_LOOP_FUNCS = {
    "hadd",
    "hmul",
    "hmin",
    "hmax",
    "hadd_to_scal",
    "getfirst",
    "testz",
    "testz_2",
    "cast",
    "cast_k",
}


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


gen_test_dict_lmul = build_layer_gen_test_dict(
    layer_name="cpp_lmul",
    template=GENERIC_FOR_LOOP,
    mipp_funcs=mipp_funcs,
    shape_templates=shape_templates,
    deny_funcs=deny,
)

gen_test_dict_lmul = apply_overrides(gen_test_dict_lmul)
