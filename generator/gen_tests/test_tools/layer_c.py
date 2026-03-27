from .common import (
    K_FUNC_DECL, K_DECL, K_INIT, K_LOAD, K_OP, K_LOOP_BODY, K_LOOP_ASRT,
    lang_proto, override, mk_gen_test_dict
)
from .templates import GENERIC_FOR_LOOP

# --------------------------
# C fragments
# --------------------------
tpl_func_decl = """void test_cmipp_{{func}}_{{dt_ext}}(){"""

tpl_decl = {
    "1arg_int32": """\tconst int vectorSize = {{size}}; int32_t inputs1[vectorSize] = {0};""",
    "2args_int32": """\tconst int vectorSize = {{size}};\n\tint32_t inputs1[vectorSize] = {0},inputs2[vectorSize] = {0};""",

    "1arg": """\tconst int vectorSize = {{size}}; {{dt_ext}}_t inputs1[vectorSize];""",
    "2args": """\tconst int vectorSize = {{size}};\n\t{{dt_ext}}_t inputs1[vectorSize],inputs2[vectorSize];""",

    "scalar_1arg": """\t{{dt_ext}}_t inputs1 = 0; const int vectorSize = {{size}};""",
}

tpl_init = {
    "1arg": """\tstd::iota(inputs1, inputs1 + vectorSize, 1);
\tstd::mt19937 g;
\tstd::shuffle(inputs1, inputs1 + vectorSize, g);
""",
    "2args": """\tstd::iota(inputs1, inputs1 + vectorSize, 1);
\tstd::iota(inputs2, inputs2 + vectorSize, 1);

\tstd::mt19937 g;
\tstd::shuffle(inputs1, inputs1 + vectorSize, g);
\tstd::shuffle(inputs2, inputs2 + vectorSize, g);
""",
    "2args_sub": """\tstd::iota(inputs1, inputs1 + vectorSize, 1);
\tstd::iota(inputs2, inputs2 + vectorSize, 1);
\tstd::mt19937 g;
\tstd::shuffle(inputs1, inputs1 + vectorSize, g);
\tstd::shuffle(inputs2, inputs2 + vectorSize, g);
\tfor(int i = 0; i < vectorSize; i++)
\t{
\t\tinputs1[i] += inputs2[i];
\t}""",

    "1arg_msk": """\tfor (auto i = 0; i < vectorSize; i++)
\t\tinputs1[i] = i % 2 ? -1 : 0;
""",
    "2args_msk": """\tfor (auto i = 0; i < vectorSize; i++){
\t\tinputs1[i] = i % 2 ? -1 : 0;
\t\tinputs2[i] = (i+1) % 2 ? -1 : 0;}
\tstd::mt19937 g;
\tstd::shuffle(inputs1, inputs1 + vectorSize, g);
\tstd::shuffle(inputs2, inputs2 + vectorSize, g);
""",
    "constant_input_1arg": """\tfor (auto i = 0; i < vectorSize; i++)
\t\tinputs1[i] = 0;
""",
}

tpl_load = {
    "1arg": """\t{{reg_type}} r1 = mipp_load_{{dt_ext}}(inputs1);""",
    "2args": """\t{{reg_type}} r1 = mipp_load_{{dt_ext}}(inputs1);
\t{{reg_type}} r2 = mipp_load_{{dt_ext}}(inputs2);""",

    "1arg_msk": """\t{{msk_type}} m1 = mipp_set_k_{{dt_ext}}(inputs1); //{{reg_type}} r1 = mipp_toreg_{{dt_ext}}(m1);""",
    "2args_msk": """\t{{msk_type}} m1 = mipp_set_k_{{dt_ext}}(inputs1); {{msk_type}} m2 = mipp_set_k_{{dt_ext}}(inputs2);""",

    "1arg_set": """\t{{reg_type}} r1 = mipp_{{func}}_{{dt_ext}}(inputs1);""",
    "1arg_set1k": """\t{{msk_type}} m1 = mipp_set1_k_{{dt_ext}}(inputs1); {{reg_type}} r1 = mipp_toreg_{{dt_ext}}(m1);""",
}

tpl_op = {
    "operator_1arg": """\tr1 = mipp_{{func}}_{{dt_ext}}(r1);""",
    "operator_2args": """\t{{reg_type}} r3 = mipp_{{func}}_{{dt_ext}}(r1, r2);""",

    "store": """\tmipp_store_{{dt_ext}}(inputs2, r1);""",

    "msk_operator_1arg": """\t{{msk_type}} m2 = mipp_{{func}}_{{dt_ext}}(m1); {{reg_type}} r1 = mipp_toreg_{{dt_ext}}(m2);""",
    "msk_operator_2args": """\t{{msk_type}} m3 = mipp_{{func}}_{{dt_ext}}(m1, m2); {{reg_type}} r1 = mipp_toreg_{{dt_ext}}(m3);""",
}

tpl_loop_body = {
    "operator_2args": """\t\t{{dt_ext}}_t res = inputs1[i] {{op}}  inputs2[i];""",
    "operator_1arg": """\t\t{{dt_ext}}_t res = {{op}} inputs1[i];""",

    "fn_call_2args": """\t\t{{dt_ext}}_t res = {{func}}(inputs1[i], inputs2[i]);""",

    "store": """\t\t{{dt_ext}}_t res = inputs1[i];""",
    "bool_2args": """\t\tbool res = inputs1[i] {{op}}  inputs2[i];""",
}

tpl_assert = {
    "operator_2args": """\t\tREQUIRE(mipp_get_{{dt_ext}}(r3, i) == res);""",
    "operator_1arg": """\t\tREQUIRE(mipp_get_{{dt_ext}}(r1, i) == res);""",
    "store": """\t\tREQUIRE(inputs2[i] == res);""",

    "mask_2args": """\t\tif(res) REQUIRE(mipp_get_{{dt_ext}}(r1, i) != 0); else REQUIRE(mipp_get_{{dt_ext}}(r1, i) == 0);""",
}

def mk_prototype_registry() -> dict:
    arith_2args = lang_proto(
        func_decl=tpl_func_decl,
        decl=tpl_decl["2args"],
        init=tpl_init["2args"],
        load=tpl_load["2args"],
        operation=tpl_op["operator_2args"],
        loop_body=tpl_loop_body["operator_2args"],
        loop_assert=tpl_assert["operator_2args"],
    )

    sub_2args = override(arith_2args, **{K_INIT: tpl_init["2args_sub"]})

    load = lang_proto(
        func_decl=tpl_func_decl,
        decl=tpl_decl["1arg"],
        init=tpl_init["1arg"],
        load=tpl_load["1arg"],
        operation="",  # load itself is in tpl_load
        loop_body=tpl_loop_body["operator_1arg"],
        loop_assert=tpl_assert["operator_1arg"],
    )

    store = lang_proto(
        func_decl=tpl_func_decl,
        decl=tpl_decl["2args"],
        init=tpl_init["1arg"],  # other input array used to store
        load=tpl_load["1arg"],
        operation=tpl_op["store"],
        loop_body=tpl_loop_body["store"],
        loop_assert=tpl_assert["store"],
    )

    set_k = lang_proto(
        func_decl=tpl_func_decl,
        decl=tpl_decl["1arg_int32"],
        init=tpl_init["1arg_msk"],
        load=tpl_load["1arg_msk"],
        operation="",
        loop_body=tpl_loop_body["store"],
        loop_assert=tpl_assert["mask_2args"],
    )

    logical_2ops_msk = lang_proto(
        func_decl=tpl_func_decl,
        decl=tpl_decl["2args_int32"],
        init=tpl_init["2args_msk"],
        load=tpl_load["2args_msk"],
        operation=tpl_op["msk_operator_2args"],
        loop_body=tpl_loop_body["bool_2args"],
        loop_assert=tpl_assert["mask_2args"],
    )

    andnb_k = override(logical_2ops_msk, **{
        K_LOOP_BODY: "\t\tbool res = (~inputs1[i]) &  inputs2[i];"
    })

    andnb = override(arith_2args, **{
        K_LOOP_BODY: "\t\t{{dt_ext}}_t res = (~inputs1[i]) &  inputs2[i];",
    })

    set_ = lang_proto(
        func_decl=tpl_func_decl,
        decl=tpl_decl["1arg"],
        init=tpl_init["constant_input_1arg"],
        load=tpl_load["1arg_set"],
        operation="",
        loop_body=tpl_loop_body["operator_1arg"],
        loop_assert=tpl_assert["operator_1arg"],
    )

    set1 = lang_proto(
        func_decl=tpl_func_decl,
        decl=tpl_decl["scalar_1arg"],
        init="",
        load=tpl_load["1arg_set"],
        operation="",
        loop_body="\t\t{{dt_ext}}_t res = inputs1;",
        loop_assert=tpl_assert["operator_1arg"],
    )

    set1_k = lang_proto(
        func_decl=tpl_func_decl,
        decl=tpl_decl["scalar_1arg"],
        init="",
        load=tpl_load["1arg_set1k"],
        operation="",
        loop_body="\t\t{{dt_ext}}_t res = inputs1;",
        loop_assert=tpl_assert["mask_2args"],
    )

    set0 = lang_proto(
        func_decl=tpl_func_decl,
        decl=tpl_decl["scalar_1arg"],
        init="",
        load="\t{{reg_type}} r1 = mipp_{{func}}_{{dt_ext}}();",
        operation="",
        loop_body="\t\t{{dt_ext}}_t res = 0;",
        loop_assert=tpl_assert["operator_1arg"],
    )

    set0_k = lang_proto(
        func_decl=tpl_func_decl,
        decl=tpl_decl["scalar_1arg"],
        init="",
        load="\t{{msk_type}} m1 = mipp_{{func}}_{{dt_ext}}(); {{reg_type}} r1 = mipp_toreg_{{dt_ext}}(m1);",
        operation="",
        loop_body="\t\t{{dt_ext}}_t res = 0;",
        loop_assert=tpl_assert["mask_2args"],
    )

    getfirst = lang_proto(
        func_decl=tpl_func_decl,
        decl=tpl_decl["1arg"],
        init=tpl_init["1arg"],
        load=tpl_load["1arg"],
        operation="",
        loop_body="\t\t{{dt_ext}}_t res = mipp_getfirst_{{dt_ext}}(r1);",
        loop_assert="\t\tREQUIRE(res == inputs1[0]);",
    )

    blend = lang_proto(
        func_decl=tpl_func_decl,
        decl=tpl_decl["2args"] + """\nint32_t mask1[vectorSize] = {0};""",
        init=tpl_init["2args"] + """\tfor (unsigned i = 0; i < vectorSize; i++)mask1[i] = i % 2 ? 1 : 0;\n""",
        load="\t{{msk_type}} m1 = mipp_set_k_{{dt_ext}}(mask1); {{reg_type}} r1 = mipp_set1_{{dt_ext}}(1); {{reg_type}} r2 = mipp_set1_{{dt_ext}}(2);",
        operation="\t{{reg_type}} r3 = mipp_blend_{{dt_ext}}(r1, r2, m1);",
        loop_body="\t\t{{dt_ext}}_t res = mipp_get_k_{{dt_ext}}(m1,i) ? mipp_get_{{dt_ext}}(r1, i) : mipp_get_{{dt_ext}}(r2, i);",
        loop_assert="\t\tREQUIRE(mipp_get_{{dt_ext}}(r3, i) == res);",
    )

    arith_1arg = lang_proto(
        func_decl=tpl_func_decl,
        decl=tpl_decl["1arg"],
        init=tpl_init["1arg"],
        load=tpl_load["1arg"],
        operation=tpl_op["operator_1arg"],
        loop_body=tpl_loop_body["operator_1arg"],
        loop_assert=tpl_assert["operator_1arg"],
    )

    logi_1op_msk = lang_proto(
        func_decl=tpl_func_decl,
        decl=tpl_decl["1arg_int32"],
        init=tpl_init["1arg_msk"],
        load=tpl_load["1arg_msk"],
        operation=tpl_op["msk_operator_1arg"],
        loop_body="\t\tbool res = ~inputs1[i];",
        loop_assert=tpl_assert["mask_2args"],
    )
    
    arith_2args_r3msk = lang_proto(
        func_decl=tpl_func_decl,
        decl=tpl_decl["2args"],
        init=tpl_init["2args"],
        load=tpl_load["2args"],
        operation=tpl_op["operator_2args"],
        loop_body=tpl_loop_body["operator_2args"],
        loop_assert=tpl_assert["operator_2args"],
    )

    return {
        "arith_2args": arith_2args,
        "sub_2args": sub_2args,
        "load": load,
        "store": store,
        "set_k": set_k,
        "logical_2ops_msk": logical_2ops_msk,
        "andnb_k": andnb_k,
        "andnb": andnb,
        "set": set_,
        "set1": set1,
        "set1_k": set1_k,
        "set0": set0,
        "set0_k": set0_k,
        "getfirst": getfirst,
        "blend": blend,
        "arith_1arg": arith_1arg,
        "logi_1op_msk": logi_1op_msk,
        "arith_2args_r3msk" : arith_2args_r3msk,
    }

prototype_registry = mk_prototype_registry()
gen_test_dict = mk_gen_test_dict(template=GENERIC_FOR_LOOP, prototype_registry=prototype_registry)