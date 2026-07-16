from registry import interfaces
from .templates import GENERIC_FOR_LOOP, GENERIC_NO_LOOP
from .common import (
    TemplateParts,
    build_layer_gen_test_dict,
    SHAPE_RET_REG_2ARGS_REG,
    SHAPE_RET_MSK_2ARGS_REG, #cmple, cmplt, cmpgt, cmpge, cmpeq, cmpneq
    SHAPE_RET_REG_1ARG_PTR,
    SHAPE_RET_VOID_2ARGS_PTR_REG,
    SHAPE_RET_VAL_2ARGS_REG_VAL,#get
    SHAPE_RET_REG_1ARG_NELE,#set
    SHAPE_RET_MSK_1ARG_NELE, #set_k
    SHAPE_RET_REG_1ARG_VAL, #set1
    SHAPE_RET_MSK_1ARG_I32, #set1_k
    SHAPE_RET_REG_0ARG, #set0
    SHAPE_RET_MSK_0ARG,#set0_k
    SHAPE_RET_VAL_2ARGS_MSK_VAL, #get_k
    SHAPE_RET_VAL_1ARG_REG,#getfirst,hadd_to_scal, hadd,
    SHAPE_RET_REG_3ARGS_2REG_1MSK, #blend
    SHAPE_RET_MSK_2ARGS_MSK, #andb_k orb_k xorb_k andnb_k
    SHAPE_RET_REG_1ARG_REG, #notb
    SHAPE_RET_MSK_1ARG_MSK, #notb_k and cast_k
    SHAPE_RET_REG_1ARG_MSK, #toreg
    SHAPE_RET_REG_3ARGS_REG, #fmadd, fmsub
    SHAPE_RET_I32_2ARGS_MSK,# testz
    SHAPE_RET_I32_1ARG_MSK, #testz2
    SHAPE_RET_REG_3ARGS_1MSK_2REG, #maskz_add
    SHAPE_RET_MSK_1ARG_REG, #tomsk

    SHAPE_RET_REG_2ARGS_PTR_REG, #gather only
    SHAPE_RET_VOID_3ARGS_PTR_REG_REG, #scatter only

    SHAPE_RET_REG_2ARGS_REG_VAL, # lshift, rshift

)

# --------------------------
# CPP fragments
# --------------------------

# --------------------------------------------
# FN decl 
# --------------------------------------------

FUNC_DECL = """template <typename T>\nvoid test_cppmipp_{{func}}(){"""
FUNC_DECL_FLOAT_WORKAROUND = " {% if is_int %} " + FUNC_DECL + " {% else %} template <typename T>\nvoid test_cppmipp_{{func}}_float{{type_size}}(){  {% endif %}"

FUNC_DECL_GATHER = """template <typename T, typename U>\nvoid test_cppmipp_{{func}}(){"""

# --------------------------------------------
# SCALAR VEC DECL
# --------------------------------------------
DECL_GET_CATCH_SEED = "\n\tstd::mt19937 seed(Catch::getSeed()+n);\n"

DECL_G_SNIPPET = """\tstd::mt19937 g;\n\tstd::uniform_int_distribution<uint16_t> dis(0, 1);"""

DECL_1ARG_INT32 = DECL_GET_CATCH_SEED + """ int32_t inputs1[{{size}}];"""
DECL_1ARG_SCALAR = DECL_GET_CATCH_SEED + """ \t T input1 = 12;"""
DECL_1ARG_SCALAR_INT32 = DECL_GET_CATCH_SEED + """ \tint32_t input1 = 12;"""

DECL_2ARGS = DECL_GET_CATCH_SEED + """ T inputs1[{{size}}],inputs2[{{size}}];"""
DECL_1ARG = DECL_GET_CATCH_SEED + """ T inputs1[{{size}}];"""
DECL_2ARGS_FOR_STORE = DECL_GET_CATCH_SEED + """ T inputs1[{{size}}],inputs2[{{size}}];"""

DECL_2ARGS_INT32 = DECL_GET_CATCH_SEED +  "\n\tint32_t inputs1[{{size}}],inputs2[{{size}}];"

DECL_3ARGS = DECL_GET_CATCH_SEED + """\n\tT inputs1[{{size}}],inputs2[{{size}}],inputs3[{{size}}];"""

DECL_CAST_2ARGS = DECL_GET_CATCH_SEED +  "\n\t{{dt2_ext}} inputs1[{{size}}];\n\tconstexpr size_t bytes = sizeof(inputs1);\n\t{{dt1_ext}}_t inputs2[bytes / sizeof({{dt1_ext}}_t)];"

DECL_CAST_2ARGS_MSK = DECL_GET_CATCH_SEED + "\n\tint32_t inputs1[{{size}}];\n\tconstexpr size_t bytes = sizeof(inputs1);\n\t{{dt1_ext}}_t inputs2[bytes / sizeof({{dt1_ext}}_t)];"


DECL_GATHER = DECL_GET_CATCH_SEED + """
T inputs1[{{size}}];
U indexes[{{size}}];
"""

DECL_SCATTER = DECL_GET_CATCH_SEED + """
T inputs1[{{size}}];
U indexes[{{size}}];
T outputs[{{size}}];
T outputs_scal[{{size}}];
"""
# --------------------------------------------
# SCALAR VEC INIT
# --------------------------------------------

INIT_2ARGS = """\tstd::iota(inputs1, inputs1 + {{size}}, 1);
\tfor(size_t i = 0; i < {{size}}; i++)
\t{
\t\tinputs1[i] = rnd::uniform<{{dt_ext}}>(seed);
\t\tinputs2[i] = rnd::uniform<{{dt_ext}}>(seed);
\t}
"""

INIT_2ARGS_NOUFLOW = INIT_2ARGS + """\tfor(size_t i = 0; i < {{size}}; i++)
\t{
\t\tinputs1[i] += inputs2[i];
\t}
"""

INIT_1ARG = """
\tfor(size_t i = 0; i < {{size}}; i++)
\t{
\t\tinputs1[i] = rnd::uniform<{{dt_ext}}>(seed);
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
\t\tinputs1[i] = rnd::uniform<{{dt_ext}}>(seed);
\t\tinputs2[i] = rnd::uniform<{{dt_ext}}>(seed);
\t\tinputs3[i] = rnd::uniform<{{dt_ext}}>(seed);
\t}
"""

INIT_CAST_2ARGS = """\tstd::iota(inputs1, inputs1 + {{size}}, 1);\n\tmemcpy(inputs2, inputs1, sizeof(inputs1));"""

INIT_GATHER = """
\tfor(size_t i = 0; i < {{size}}; i++)
{
\t\tinputs1[i] = rnd::uniform<T>(seed);
\t\tindexes[i] = (i * rnd::uniform<U>(seed)) % {{size}}; // ensure indexes are within bounds and not all the same
}
"""

INIT_SCATTER = """
\tfor(size_t i = 0; i < {{size}}; i++)
{
\t\tinputs1[i] = rnd::uniform<T>(seed);
\t\tindexes[i] = (i * rnd::uniform<U>(seed)) % {{size}}; // ensure indexes are within bounds and not all the same
\t\toutputs[i] = 0;
\t\toutputs_scal[i] = 0;
}"""

# --------------------------------------------
# LOADS
# --------------------------------------------


LOAD_2ARGS_REG = """\t{{reg_type}} r1 = mipp::load<{{dt_ext}}>(inputs1);
\t{{reg_type}} r2 = mipp::load<{{dt_ext}}>(inputs2);
\t{{reg_type_scalar}} s1 = mipp::load<{{dt_ext}}, 1, mipp::ISA::SCALAR>(inputs1);
\t{{reg_type_scalar}} s2 = mipp::load<{{dt_ext}}, 1, mipp::ISA::SCALAR>(inputs2);
"""

LOAD_1ARG_REG = """\t{{reg_type}} r1 = mipp::load<{{dt_ext}}>(inputs1);
\t{{reg_type_scalar}} s1 = mipp::load<{{dt_ext}}, 1, mipp::ISA::SCALAR>(inputs1);
"""

LOAD_1ARG_MASK = """\t{{msk_type}} m1 = mipp::set_k<T>(inputs1);
\t{{msk_type_scalar}} ms1 = mipp::set_k<{{dt_ext}}, 1, mipp::ISA::SCALAR>(inputs1);
"""

LOAD_1SCALAR_REG = """\t{{reg_type}} r1 = mipp::set1(input1);
\t{{reg_type_scalar}} s1 = mipp::set1<T, 1, mipp::ISA::SCALAR>(input1);
"""

LOAD_1SCALAR_MASK = """\t{{msk_type}} m1 = mipp::set1_k<T>(input1);
\t{{msk_type_scalar}} ms1 = mipp::set1_k<{{dt_ext}}, 1, mipp::ISA::SCALAR>(input1);
"""

LOAD_SET0_REG = """\t{{reg_type}} r1 = mipp::set0<T>();
\t{{reg_type_scalar}} s1 = mipp::set0<T, 1, mipp::ISA::SCALAR>();
"""

LOAD_SET0_MASK = """\t{{msk_type}} m1 = mipp::set0_k<T>();
\t{{msk_type_scalar}} ms1 = mipp::set0_k<{{dt_ext}}, 1, mipp::ISA::SCALAR>();
"""

LOAD_SET1_2ARGS_REG = """\t{{reg_type}} r1 = mipp::set1((T)1); \n\t{{reg_type}} r2 = mipp::set1((T)2);
\t{{reg_type_scalar}} s1 = mipp::set1<T, 1, mipp::ISA::SCALAR>((T)1); \n\t{{reg_type_scalar}} s2 = mipp::set1<T, 1, mipp::ISA::SCALAR>((T)2);
"""

LOAD_2ARGS_MASK = """\t{{msk_type}} m1 = mipp::set_k<T>(inputs1); 
\t{{msk_type}} m2 = mipp::set_k<T>(inputs2);
\t{{msk_type_scalar}} ms1 = mipp::set_k<{{dt_ext}}, 1, mipp::ISA::SCALAR>(inputs1);
\t{{msk_type_scalar}} ms2 = mipp::set_k<{{dt_ext}}, 1, mipp::ISA::SCALAR>(inputs2);
"""

LOAD_3ARGS_REG = """\t{{reg_type}} r1 = mipp::load(inputs1);
\t{{reg_type}} r2 = mipp::load(inputs2);
\t{{reg_type}} r3 = mipp::load(inputs3);
\t{{reg_type_scalar}} s1 = mipp::load<{{dt_ext}}, 1, mipp::ISA::SCALAR>(inputs1);
\t{{reg_type_scalar}} s2 = mipp::load<{{dt_ext}}, 1, mipp::ISA::SCALAR>(inputs2);
\t{{reg_type_scalar}} s3 = mipp::load<{{dt_ext}}, 1, mipp::ISA::SCALAR>(inputs3);
"""


LOAD_CAST_2ARGS = """\t{{reg1_type}} r1 = mipp::load(inputs1);\n\t{{reg1_type_scalar}} s1 = mipp::load<T, 1, mipp::ISA::SCALAR>(inputs1);"""

LOAD_CAST_2ARGS_MASK = """\t{{msk1_type}} m1 = mipp::set_k<T>(inputs1);\n\t{{msk1_type_scalar}} ms1 = mipp::set_k<T, 1, mipp::ISA::SCALAR>(inputs1);"""

LOAD_GATHER = """\t{{reg_type_uint}} ri1 = mipp::load(indexes);
\t{{reg_type_scalar_uint}} rsi1 = mipp::load<U, 1, mipp::ISA::SCALAR>(indexes);
"""

LOAD_SCATTER = """\t{{reg_type_uint}} ri1 = mipp::load(indexes);
\t{{reg_type}} r1 = mipp::load(inputs1);
\t{{reg_type_scalar_uint}} rsi1 = mipp::load<U, 1, mipp::ISA::SCALAR>(indexes);
\t{{reg_type_scalar}} s1 = mipp::load<T, 1, mipp::ISA::SCALAR>(inputs1);
"""

# --------------------------------------------
# OPERATIONS
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

OP_GATHER = """\t{{reg_type}} r2 = mipp::gather(inputs1, ri1);\n\t {{reg_type_scalar}} s2 = mipp::gather(inputs1,rsi1);"""
OP_SCATTER = """mipp::scatter(outputs, ri1, r1);\n\tmipp::scatter(outputs_scal, rsi1, s1);"""

OP_CVT = """ \t{{reg2_type}} r2 = mipp::cvt_{{dt1_ext}}(r1);\n\t{{reg2_type_scalar}} s2 = mipp::cvt_{{dt1_ext}}(s1);"""
OP_WCVT = """ \t{{reg2_type}} r2 = mipp::wcvt_{{dt1_ext}}(r1);\n\t{{reg2_type_scalar}} s2 = mipp::wcvt_{{dt1_ext}}(s1);"""

OP_REG_VAL = """\t{{reg_type}} r3 = mipp::{{func}}(r1, input1);\n\t{{reg_type_scalar}} s3 = mipp::{{func}}(s1, input1);"""

# --------------------------------------------
# ASSERTS IN LOOP BODY
# ------------------------------------------

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

# not done

AS_CAST_2ARGS = """\t\tREQUIRE(mipp::get(r2, i) == mipp::get(s2, i));"""
AS_CAST_2ARGS_MSK = """\t\tif(res) REQUIRE(mipp::get(m2, i) != 0); else REQUIRE(mipp::get(m2, i) == 0);"""


AS_CMP_BINOP_LOGI_FLOAT_WORKAROUND = """REQUIRE(!! mipp::get(r3, i) == !!mipp::get(s3, i) );"""

# AS_CMP_BINOP_FLOAT_WORKAROUND ="""\n\t\tREQUIRE(std::bit_cast<uint64_t>(mipp::get(r3, i))\
#     \n\t\t\t==
#     \t\tstd::bit_cast<uint64_t>(mipp::get(s3, i)) );"""

AS_GATHER = """
REQUIRE(mipp::get(r2,i) == mipp::get(s2,i));
"""

AS_SCATTER = """REQUIRE(outputs[i] == outputs_scal[i]);
"""

AS_REG_BINOP_NAN = """\t\tif(std::isnan(mipp::get(s3, i))) REQUIRE(std::isnan(mipp::get(r3, i))); else REQUIRE(mipp::get(r3, i) == mipp::get(s3, i));"""
AS_REG_BINOP_NAN_TOL = """\t\t{{dt_ext}} res1 = mipp::get(r3, i);
\t\t{{dt_ext}} res2 = mipp::get(s3, i);
\t\t{{dt_ext}} tol  = 1e-5f * abs_diff::abs_diff(res2) + 1.0f;
\t\t{{dt_ext}} diff = abs_diff::abs_diff(res1, res2);
\t\tif(std::isinf(tol) || std::isnan(tol)) continue; // skip comparison if tol is inf or nan
\t\tif(std::isnan(diff) || std::isnan(res2) || std::isnan(res1)) continue; // skip comparison if either result is nan
\t\tif(std::isinf(diff) || std::isinf(res2) || std::isinf(res1)) continue; // skip comparison if either result is inf
\t\tREQUIRE(diff <= tol);"""


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
        decl=DECL_2ARGS_FOR_STORE,
        init=INIT_1ARG,     # only inputs1 needs init; inputs2 is output
        load=LOAD_1ARG_REG,     # store uses r1 loaded from inputs1
        operation=OP_STORE,
        loop_body="",
        loop_assert=AS_STORE,
    ),
    
    SHAPE_RET_VAL_2ARGS_REG_VAL : TemplateParts( #get
        func_decl=FUNC_DECL,
        decl=DECL_1ARG,
        init=INIT_1ARG,
        load=LOAD_1ARG_REG,
        operation=OP_REG_NOOP,
        loop_body="",
        loop_assert=AS_REG_BINOP,
    ),
    
    SHAPE_RET_REG_1ARG_NELE : TemplateParts( # set
        func_decl=FUNC_DECL,
        decl=DECL_1ARG,
        init=INIT_1ARG,
        load=LOAD_1ARG_REG,
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
        decl="",
        init="",
        load=LOAD_SET0_REG,
        operation=OP_REG_NOOP,
        loop_body="",
        loop_assert=AS_REG_BINOP,
    ),
    
    SHAPE_RET_MSK_0ARG: TemplateParts( # set0_k
        func_decl=FUNC_DECL,
        decl="",
        init="",
        load=LOAD_SET0_MASK,
        operation=OP_TOREG,
        loop_body="",
        loop_assert=AS_CMP_2REG,
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
    
    SHAPE_RET_VAL_1ARG_REG: TemplateParts(  # getfirst, hadd_to_scal, hadd, hmul, hmin, hmax
        func_decl=FUNC_DECL,
        decl=DECL_1ARG,
        init=INIT_1ARG,
        load=LOAD_1ARG_REG,
        operation="",
        loop_body="",
        loop_assert="\t\tREQUIRE(mipp::{{func}}(r1) == mipp::{{func}}(s1));",
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

    SHAPE_RET_MSK_1ARG_MSK: TemplateParts( # notb_k, and cast_k
        func_decl=FUNC_DECL,
        decl=DECL_1ARG_INT32+DECL_G_SNIPPET,
        init=INIT_1ARG_DIS,
        load=LOAD_1ARG_MASK,
        operation=OP_1ARG_1MASK,
        loop_body="",
        loop_assert=AS_CMP_BINOP_LOGI_FLOAT_WORKAROUND,
    ),
    
    SHAPE_RET_REG_1ARG_REG: TemplateParts( # cast 
        func_decl=FUNC_DECL,
        decl=DECL_1ARG,
        init=INIT_1ARG,
        load=LOAD_1ARG_REG,
        operation=OP_REG_UNOP,
        loop_body="",
        loop_assert=AS_REG_BINOP,
    ),
    
    SHAPE_RET_REG_1ARG_MSK: TemplateParts( # toreg
        func_decl=FUNC_DECL,
        decl=DECL_1ARG_INT32+DECL_G_SNIPPET,
        init=INIT_1ARG_DIS,
        load=LOAD_1ARG_MASK,
        operation=OP_TOREG,
        loop_body="",
        loop_assert=AS_REG_BINOP,
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
    
    # testz
    SHAPE_RET_I32_2ARGS_MSK : TemplateParts(
        func_decl=FUNC_DECL,
        decl="",
        init="",
        load="\t{{msk_type}} m1 = mipp::set1_k<{{dt_ext}}>(1); \n\t{{msk_type}} m2 = mipp::set1_k<{{dt_ext}}>(0);",
        operation="",
        loop_body="",
        loop_assert="\tREQUIRE(mipp::testz(m1, m1) == 0);\n\tREQUIRE(mipp::testz(m2, m2) != 0);",
    ),
   
    # testz_2 
    SHAPE_RET_I32_1ARG_MSK : TemplateParts(
        func_decl=FUNC_DECL,
        decl="",
        init="",
        load="\t{{msk_type}} m1 = mipp::set1_k<{{dt_ext}}>(1); \n\t{{msk_type}} m2 = mipp::set1_k<{{dt_ext}}>(0);",
        operation="",
        loop_body="",
        loop_assert="\tREQUIRE(mipp::testz_2(m1) == 0);\n\tREQUIRE(mipp::testz_2(m2) != 0);",
    ),
    
    # #tomsk
    SHAPE_RET_MSK_1ARG_REG : TemplateParts(
        func_decl=FUNC_DECL,
        decl=DECL_1ARG,
        init=INIT_1ARG,
        load=LOAD_1ARG_REG,
        operation="""\t{{msk_type}} m1 = mipp::tomsk(r1);\n{{reg_type}} r3 = mipp::toreg(m1);
{{msk_type_scalar}} ms1 = mipp::tomsk(s1);\n\t{{reg_type_scalar}} s3 = mipp::toreg(ms1);""",
        loop_body="",
        loop_assert="""\t\tREQUIRE( (!!mipp::get(r3, i)) == (!!mipp::get(s3,i)) );""",
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
        func_decl=FUNC_DECL_GATHER,
        decl=DECL_SCATTER,
        init=INIT_SCATTER,
        load=LOAD_SCATTER,
        operation=OP_SCATTER,
        loop_body="",
        loop_assert=AS_SCATTER,
    ),

    # I may have forgotten about this shape when rewritting tests. Oops.
    SHAPE_RET_MSK_2ARGS_MSK : TemplateParts( # andb_k orb_k xorb_k andnb_k
        func_decl=FUNC_DECL,
        decl=DECL_2ARGS_INT32 + DECL_G_SNIPPET,
        init=INIT_2ARGS_DIS,
        load=LOAD_2ARGS_MASK,
        operation=OP_2ARGS_2MASK,
        loop_body="",
        loop_assert=AS_CMP_BINOP_LOGI_FLOAT_WORKAROUND,
    ),

    SHAPE_RET_REG_2ARGS_REG_VAL: TemplateParts( # lshift, rshift
        func_decl=FUNC_DECL, 
        decl=DECL_1ARG+ """ \tint32_t input1 = rnd::uniform<int32_t>(seed); input1 = input1 < 0 ? -input1 : input1; input1 = input1 %((sizeof(T) * 8)-2);""",
        init=INIT_1ARG,
        load=LOAD_1ARG_REG,
        operation=OP_REG_VAL,
        loop_body="",
        loop_assert=AS_REG_BINOP_NAN,
    ),
}


deny = {
    "maskzld", "maskst",
}

LAYER_OVERRIDES = {

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


    "hadd_to_scal" : {
        "loop_assert" :"""\t\tbool ov = false; {{dt_ext}} res = 0;
\t\tfor(size_t j = 0; j < {{size}}; j++){
\t\t\tov |= ovf::will_add_overflow<{{dt_ext}}>(res, inputs1[j]);
\t\t\tif(ov) break;
\t\t\tres += inputs1[j];
\t\t}
\t\tif(ov) {
\t\t\tINFO("Overflow occurred, skipping assert");
\t\t}else{\n\t"""
+ "\t\t {{dt_ext}} res1 = mipp::{{func}}(r1);\n \t\t{{dt_ext}} res2 = mipp::{{func}}(s1);\n"
+ "\n\t\t{{dt_ext}} tol  = 1e-4f * abs_diff::abs_diff(res2) + 1.0f;"
+ "\n\t\t{{dt_ext}} diff = abs_diff::abs_diff(res1, res2);"
+ "\n\t\tREQUIRE(diff <= tol);"
+ """\n\t\t}""",
    },

    "hadd" : {
        "loop_assert" :"""\t\tbool ov = false; {{dt_ext}} res = 0;
\t\tfor(size_t j = 0; j < {{size}}; j++){
\t\t\tov |= ovf::will_add_overflow<{{dt_ext}}>(res, inputs1[j]);
\t\t\tif(ov) break;
\t\t\tres += inputs1[j];
\t\t}
\t\tif(ov) {
\t\t\tINFO("Overflow occurred, skipping assert");
\t\t}else{\n\t"""
+ "\t\t {{dt_ext}} res1 = mipp::{{func}}(r1);\n \t\t{{dt_ext}} res2 = mipp::{{func}}(s1);\n"
+ "\n\t\t{{dt_ext}} tol  = 1e-4f * abs_diff::abs_diff(res2) + 1.0f;"
+ "\n\t\t{{dt_ext}} diff = abs_diff::abs_diff(res1, res2);"
+ "\n\t\tREQUIRE(diff <= tol);"
+ """\n\t\t}""",
    },

    "hmul": {
        "loop_assert": """\t\tbool ov = false; {{dt_ext}} res = 1;
\t\tfor(size_t j = 0; j < {{size}}; j++){
\t\t\tov |= ovf::will_mul_overflow<{{dt_ext}}>(res, inputs1[j]);
\t\t\tif(ov) break;
\t\t\tres *= inputs1[j];
\t\t}
\t\tif(ov) {
\t\t\tINFO("Overflow occurred, skipping assert");
\t\t}else{"""
+ "\t\t {{dt_ext}} res1 = mipp::{{func}}(r1);\n \t\t{{dt_ext}} res2 = mipp::{{func}}(s1);\n"
+ "\n\t\t{{dt_ext}} tol  = 1e-5f * abs_diff::abs_diff(res2) + 1.0f;"
+ "\n\t\t{{dt_ext}} diff = abs_diff::abs_diff(res1, res2);"
+ "\n\t\tREQUIRE(diff <= tol);;"
+ "\n\t\t}",
    },

    "hmin": {
        "loop_assert": """\tREQUIRE(mipp::{{func}}(r1) == mipp::{{func}}(s1));""",
    },
    
    
    "hmax": {
        "loop_assert": """\tREQUIRE(mipp::{{func}}(r1) == mipp::{{func}}(s1));""",
    },

     "rsqrt" : {
# if inputs1[i] < 0 the result is a NaN and the assert will fail bc of how nan comparison works. 
# so skip in that case
        "loop_assert": """\t\tif(inputs1[i] < 0) {
\t\t\tINFO("Input is negative, result is NaN, skipping assert");
\t\t}else{\n\t"""+ "\t\t {{dt_ext}} res1 = mipp::get(r3, i);\n \t\t{{dt_ext}} res2 = mipp::get(s3, i);\n"
+ "\n\t\t{{dt_ext}} tol  = 1e-5f * abs_diff::abs_diff(res2) + 1.0f;"
+ "\n\t\t{{dt_ext}} diff = abs_diff::abs_diff(res1, res2);"
+ "\n\t\tREQUIRE(diff <= tol);;"
+ """\n\t\t}""",
    },


    "sqrt" : {
# if inputs1[i] < 0 the result is a NaN and the assert will fail bc of how nan comparison works. 
# so skip in that case
        "loop_assert": """\t\tif(inputs1[i] < 0) {
\t\t\tINFO("Input is negative, result is NaN, skipping assert");
\t\t}else{\n\t"""+ "\t\t {{dt_ext}} res1 = mipp::get(r3, i);\n \t\t{{dt_ext}} res2 = mipp::get(s3, i);\n"
+ "\n\t\t{{dt_ext}} tol  = 1e-5f * abs_diff::abs_diff(res2) + 1.0f;"
+ "\n\t\t{{dt_ext}} diff = abs_diff::abs_diff(res1, res2);"
+ "\n\t\tREQUIRE(diff <= tol);;"
+ """\n\t\t}""",
    },

    "round": {
        "loop_assert": "\t\t{{dt_ext}} fractional_part = inputs1[i] - std::floor(inputs1[i]);\n" +
        "\t\tif(fractional_part == 0.5f) {\n" +
        "\t\t\tINFO(\"Fractional part is exactly 0.5, different rounding methods may round differently, skipping assert\");\n" +
        "\t\t}else{\n\t\t\tREQUIRE(mipp::get(r3, i) == mipp::get(s3, i));\n\t\t}",
        },
    
    "toreg" : {
        "loop_assert" : """\t\tREQUIRE(!!mipp::get(r3, i) == !!mipp::get(s3, i));""",
    },

    "cast": {
        "decl": DECL_CAST_2ARGS,
        "init": INIT_CAST_2ARGS,
        "load": LOAD_CAST_2ARGS,
        "operation": OP_CAST,
        "loop_body": """\tfor(size_t i = 0; i < {{size}} * sizeof({{dt2_ext}}) / sizeof({{dt1_ext}}_t); i++){\n""",
        "loop_assert": AS_CAST_2ARGS+ "\n\t}",
    },

    "cvt": {
        "decl": DECL_CAST_2ARGS,
        "init": INIT_CAST_2ARGS,
        "load": LOAD_CAST_2ARGS,
        "operation": OP_CVT,
        "loop_body": """\tfor(size_t i = 0; i < {{size}} * sizeof({{dt2_ext}}) / sizeof({{dt1_ext}}_t); i++){\n""",
        "loop_assert": AS_CAST_2ARGS+ "\n\t}",
    },

    "wcvt": {
        "decl": DECL_CAST_2ARGS,
        "init": INIT_CAST_2ARGS,
        "load": LOAD_CAST_2ARGS,
        "operation": OP_WCVT,
        "loop_body": """\tfor(size_t i = 0; i < {{size}} * sizeof({{dt2_ext}}) / sizeof({{dt1_ext}}_t); i++){\n""",
        "loop_assert": AS_CAST_2ARGS+ "\n\t}",
    },
    
    
    "cast_k": {
        "decl": DECL_CAST_2ARGS_MSK,
        "init": INIT_CAST_2ARGS,
        "load": LOAD_CAST_2ARGS_MASK,
        "operation": OP_CAST_MSK,
        "loop_body": """\tfor(size_t i = 0; i < {{size}} * sizeof(int32_t) / sizeof({{dt1_ext}}_t); i++){\n""",
        "loop_assert": AS_CAST_2ARGS_MSK + "\n\t}",
    },

    "exp": {
        "loop_assert": AS_REG_BINOP_NAN_TOL,
    },

    "log": {
        "loop_assert": AS_REG_BINOP_NAN_TOL,
    },


    "pow": {
        "init": """\tstd::iota(inputs1, inputs1 + {{size}}, 1);
\tfor(size_t i = 0; i < {{size}}; i++)
\t{
\t\tinputs1[i] = rnd::uniform<{{dt_ext}}>(seed);
\t\tinputs1[i] = inputs1[i] < 0 ? -inputs1[i] : inputs1[i]; // make sure inputs1 is non-negative for log(x)
\t\tinputs2[i] = rnd::uniform<{{dt_ext}}>(seed);
\t}
""",
        "loop_assert": AS_REG_BINOP_NAN_TOL,
    },


    
}

NO_LOOP_FUNCS = {"hadd", "hmul", "hmin", "hmax", 
                 "hadd_to_scal", "getfirst", "testz", 
                 "testz_2", "cast","cast_k", "cvt", "wcvt"}

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
    layer_name="cpp",
    template=GENERIC_FOR_LOOP,
    interfaces=interfaces,
    shape_templates=shape_templates,
    deny_funcs=deny,
)

gen_test_dict = apply_overrides(gen_test_dict)