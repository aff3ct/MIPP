import os
import sys
from jinja2 import Template, StrictUndefined

path = os.getcwd()
from tools import all_datatypes

sys.path.insert(1, path + "/../")

# this file contains templates for generating test functions,
# the philosophy is to have very small template for each part of the
# test function declaration. In order to have a lot of genericity

# not complete obv
set_mask_op = {"set_k", "set1_k", "set0_k", "andb_k", "orb_k", "xorb_k", "andnb_k", "notb_k"}

#what's annoying is that andb_k exists in cmipp
#but in cpp it's an overload of andb. So ig we can manually 
#filter out the "_k" when passing the func to the template creator. 
#I don't like this solution tbh
set_remove_k = {"andb_k", "orb_k", "xorb_k", "andnb_k", "notb_k"}

# -----------------------------------------------------------------------------
# Template fragments
# -----------------------------------------------------------------------------

tpl_func_declaration = {
    "c": """void test_cmipp_{{func}}_{{dt_ext}}(){""",
    "cpp": """template <typename T>\nvoid test_cppmipp_{{func}}(){""",
    "obj": """template <typename T>\nvoid test_objmipp_{{func}}(){""",
}

tpl_body_declaration = {
    # I think masks only loading from i32 is odd.
    "c1arg_int32": """\tconst int vectorSize = {{size}}; int32_t inputs1[vectorSize] = {0};""",
    "cpp1arg_int32": """\tconst int vectorSize = mipp::N<T>(); int32_t inputs1[vectorSize] = {0};""",
    
    "c2args_int32": """\tconst int vectorSize = {{size}};\n\tint32_t inputs1[vectorSize] = {0},inputs2[vectorSize] = {0};""",
    "cpp2args_int32": """\tconst int vectorSize = mipp::N<T>();\n\tint32_t inputs1[vectorSize] = {0},inputs2[vectorSize] = {0};""",
    
    "c1arg": """\tconst int vectorSize = {{size}}; {{dt_ext}}_t inputs1[vectorSize];""",
    "c2args": """\tconst int vectorSize = {{size}};\n\t{{dt_ext}}_t inputs1[vectorSize],inputs2[vectorSize];""",
    
    "cpp1arg": """\tconst int vectorSize = mipp::N<T>(); T inputs1[vectorSize];""",
    "cpp2args": """\tconst int vectorSize = mipp::N<T>(); T inputs1[vectorSize],inputs2[vectorSize];""",
    "cpp3args": """\tT inputs1[vectorSize],inputs2[vectorSize],inputs3[vectorSize];""",
    
    "c_scalar_1arg": """\t{{dt_ext}}_t inputs1 = 0; const int vectorSize = {{size}};""",
    "cpp_scalar_1arg": """\tT inputs1 = 0; const int vectorSize = mipp::N<T>();""",
    
    "c_vectoSize_only": """\tconst int vectorSize = {{size}};""",
    "cpp_vectoSize_only": """\tconst int vectorSize = mipp::N<T>();""",
}

tpl_body_init = {
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
    # for things like sub, we want the guarantee that inputs1[i] > inputs2[i]
    # to avoid negative results that might cause issues with unsigned types.
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
\t\tinputs1[i] = i % 2 ? 1 : 0;
""",

    "2args_msk": """\tfor (auto i = 0; i < vectorSize; i++){
\t\tinputs1[i] = i % 2 ? 1 : 0;
\t\tinputs2[i] = (i+1) % 2 ? 1 : 0;}
\tstd::mt19937 g;
\tstd::shuffle(inputs1, inputs1 + vectorSize, g);
\tstd::shuffle(inputs2, inputs2 + vectorSize, g);
""",

    # reusable for set1, set0 maybe _k variants too?
    "constant_input_1arg": """\tfor (auto i = 0; i < vectorSize; i++)
\t\tinputs1[i] = 0;
""",
}

tpl_body_load = {
    "c1arg": """\t{{reg_type}} r1 = mipp_load_{{dt_ext}}(inputs1);""",
    "c2args": """\t{{reg_type}} r1 = mipp_load_{{dt_ext}}(inputs1);
\t{{reg_type}} r2 = mipp_load_{{dt_ext}}(inputs2);""",
    "c3args": """\t{{reg_type}} r1 = mipp_load_{{dt_ext}}(inputs1);
\t{{reg_type}} r2 = mipp_load_{{dt_ext}}(inputs2);
\t{{reg_type}} r3 = mipp_load_{{dt_ext}}(inputs3);""",

    "cpp1arg": """\t{{reg_type}} r1 = mipp::load<{{dt_ext}}>(inputs1);""",
    "cpp2args": """\t{{reg_type}} r1 = mipp::load<{{dt_ext}}>(inputs1), r2 = mipp::load<{{dt_ext}}>(inputs2);""",
    
    "obj1arg": """\t//{{reg_type}} r1(inputs);//waiting for load to be fixed in obj layer
\t{{reg_type}} r1; r1.r = mipp::load<T>(inputs1);""",
    "obj2args": """\t//{{reg_type}} r1(inputs1), r2(inputs2);//waiting for load to be fixed in obj layer
\t{{reg_type}} r1, r2; r1.r = mipp::load<T>(inputs1); r2.r = mipp::load<T>(inputs2);""",

    "c1arg_msk": """\t{{msk_type}} m1 = mipp_set_k_{{dt_ext}}(inputs1); //{{reg_type}} r1 = mipp_toreg_{{dt_ext}}(m1);""",
    "cpp1arg_msk": """\t{{msk_type}} m1 = mipp::set_k<{{dt_ext}}>(inputs1); //{{reg_type}} r1 = mipp::toreg(m1);""",
    "obj1arg_msk": """\t{{msk_type}} m1; m1.m = mipp::set_k<{{dt_ext}}>(inputs1); //{{reg_type}} r1; r1.r = mipp::toreg(m1.m);""",
    
    "c1arg_set1k": """\t{{msk_type}} m1 = mipp_set1_k_{{dt_ext}}(inputs1); {{reg_type}} r1 = mipp_toreg_{{dt_ext}}(m1);""",
    "cpp1arg_set1k": """\t{{msk_type}} m1 = mipp::set1_k<{{dt_ext}}>(inputs1); {{reg_type}} r1 = mipp::toreg(m1);""",
    "obj1arg_set1k": """\t{{msk_type}} m1; m1.m = mipp::set1_k<{{dt_ext}}>(inputs1); {{reg_type}} r1; r1.r = mipp::toreg(m1.m);""",
    
    "c2args_msk": """\t{{msk_type}} m1 = mipp_set_k_{{dt_ext}}(inputs1); {{msk_type}} m2 = mipp_set_k_{{dt_ext}}(inputs2);""",
    "cpp2args_msk": """\t{{msk_type}} m1 = mipp::set_k<T>(inputs1); {{msk_type}} m2 = mipp::set_k<T>(inputs2);""",
    "obj2args_msk": """\t{{msk_type}} m1, m2; m1.m = mipp::set_k<T>(inputs1); m2.m = mipp::set_k<T>(inputs2);""",
    
    "c1arg_set": """\t{{reg_type}} r1 = mipp_{{func}}_{{dt_ext}}(inputs1);""",
    "cpp1arg_set": """\t{{reg_type}} r1 = mipp::{{func}}<{{dt_ext}}>(inputs1);""",
    "obj1arg_set": """\t{{reg_type}} r1; r1.r = mipp::{{func}}<{{dt_ext}}>(inputs1);""",
}

tpl_body_operation = {
    
    "c_operator_1arg": """\tr1 = mipp_{{func}}_{{dt_ext}}(r1);""",
    "cpp_operator_1arg": """\tr1 = mipp::{{func}}(r1);""",
    "obj_operator_1arg": """\tr1.r = mipp::{{func}}(r1.r);""",
    
    "c_operator_2args": """\t{{reg_type}} r3 = mipp_{{func}}_{{dt_ext}}(r1, r2);""",
    "cpp_operator_2args": """\t{{reg_type}} r3 = mipp::{{func}}(r1, r2);""",
    "obj_operator_2args": """\t{{reg_type}} r3 = r1 {{op}} r2;""",
    
    "obj_fn_call_2args": """\t{{reg_type}} r3; r3.r = mipp::{{func}}(r1.r, r2.r);""",
    
    "c_store": """\tmipp_store_{{dt_ext}}(inputs2, r1);""",
    "cpp_store": """\tmipp::store(inputs2, r1);""",
    "obj_store": """\tmipp::store(inputs2, r1.r);""",
    
    
    "c_msk_operator_1arg": """\t{{msk_type}} m2 = mipp_{{func}}_{{dt_ext}}(m1); {{reg_type}} r1 = mipp_toreg_{{dt_ext}}(m2);""",
    "cpp_msk_operator_1arg": """\t{{msk_type}} m2 = mipp::{{func}}(m1); {{reg_type}} r1 = mipp::toreg(m2);""",
    "obj_msk_operator_1arg": """\t{{msk_type}} m2; m2.m = mipp::{{func}}(m1.m); {{reg_type}} r1; r1.r = mipp::toreg(m2.m);""",
    
    
    "c_msk_operator_2args": """\t{{msk_type}} m3 = mipp_{{func}}_{{dt_ext}}(m1, m2); {{reg_type}} r1 = mipp_toreg_{{dt_ext}}(m3);""",
    "cpp_msk_operator_2args": """\t{{msk_type}} m3 = mipp::{{func}}(m1, m2); {{reg_type}} r1 = mipp::toreg(m3);""",
    "obj_msk_operator_2args": """\t{{msk_type}} m3; m3.m = mipp::{{func}}(m1.m, m2.m); {{reg_type}} r1; r1.r = mipp::toreg(m3.m);""",
}

tpl_body_loop_body = {
    "c_operator_2args": """\t\t{{dt_ext}}_t res = inputs1[i] {{op}}  inputs2[i];""",
    "cpp_operator_2args": """\t\tT res = inputs1[i] {{op}}  inputs2[i];""",
    
    "bool_2args": """\t\tbool res = inputs1[i] {{op}}  inputs2[i];""",
    
    "c_operator_1arg": """\t\t{{dt_ext}}_t res = {{op}} inputs1[i];""",
    "cpp_operator_1arg": """\t\tT res = {{op}} inputs1[i];""",
    "obj_operator_1arg": """\t\tT res = {{op}} inputs1[i];""",
    
    "c_fn_call_2args": """\t\t{{dt_ext}}_t res = {{func}}(inputs1[i], inputs2[i]);""",
    "c_fn_call_1arg": """\t\t{{dt_ext}}_t res = {{func}}(inputs1[i]);""",
    
    "c_store": """\t\t{{dt_ext}}_t res = inputs1[i];""",
    "cpp_store": """\t\tT res = inputs1[i];""",
    "obj_store": """\t\tT res = inputs1[i];""",
}

tpl_body_loop_assert = {
    "c_operator_2args": """\t\tREQUIRE(mipp_get_{{dt_ext}}(r3, i) == res);""",
    "cpp_operator_2args": """\t\tREQUIRE(mipp::get(r3, i) == res);""",
    "obj_operator_2args": """\t\tREQUIRE(r3[i] == res);""",
    
    "c_operator_1arg": """\t\tREQUIRE(mipp_get_{{dt_ext}}(r1, i) == res);""",
    "cpp_operator_1arg": """\t\tREQUIRE(mipp::get(r1, i) == res);""",
    "obj_operator_1arg": """\t\tREQUIRE(r1[i] == res);""",
    
    "store": """\t\tREQUIRE(inputs2[i] == res);""",
    
    "c_mask_2args": """\t\tif(res) REQUIRE(mipp_get_{{dt_ext}}(r1, i) != 0); else REQUIRE(mipp_get_{{dt_ext}}(r1, i) == 0);""",
    "cpp_mask_2args": """\t\tif(res) REQUIRE(mipp::get(r1, i) != 0); else REQUIRE(mipp::get(r1, i) == 0);""",
    "obj_mask_2args": """\t\tif(res) REQUIRE(r1[i] != 0); else REQUIRE(r1[i] == 0);""",
}

tpl_bodies = {
    "generic_for_loop": """{{func_declaration}}
{{declaration}}
{{init}}

{{load}}
{{operation}}

\tfor(int i = 0; i < vectorSize; i++)
\t{
\t{{loop_body}}
\t{{loop_assert}}
\t}
}
""",
}


# avoid copy pasting the literal keys
K_FUNC_DECL = "tpl_func_declaration"
K_DECL = "tpl_body_declaration"
K_INIT = "tpl_body_initialization"
K_LOAD = "tpl_body_load"
K_LOOP_BODY = "tpl_body_loop_body"
K_LOOP_ASRT = "tpl_body_loop_assert"
K_OP = "tpl_body_operation"


def lang_proto(*, func_decl, decl, init, load, loop_body, loop_assert, op=""):
    return {
        K_FUNC_DECL: func_decl,
        K_DECL: decl,
        K_INIT: init,
        K_LOAD: load,
        K_LOOP_BODY: loop_body,
        K_LOOP_ASRT: loop_assert,
        K_OP: op,
    }

# I used to manually change 1 field to create new prototypes 
# this is better tbh
def override(proto: dict, **updates) -> dict:
    out = dict(proto)
    out.update(updates)
    return out

def mk_prototype_registry() -> dict:
    # Base prototypes
    c_arith_2args = lang_proto(
        func_decl=tpl_func_declaration["c"],
        decl=tpl_body_declaration["c2args"],
        init=tpl_body_init["2args"],
        load=tpl_body_load["c2args"],
        loop_body=tpl_body_loop_body["c_operator_2args"],
        loop_assert=tpl_body_loop_assert["c_operator_2args"],
        op=tpl_body_operation["c_operator_2args"],
    )
    cpp_arith_2args = lang_proto(
        func_decl=tpl_func_declaration["cpp"],
        decl=tpl_body_declaration["cpp2args"],
        init=tpl_body_init["2args"],
        load=tpl_body_load["cpp2args"],
        loop_body=tpl_body_loop_body["cpp_operator_2args"],
        loop_assert=tpl_body_loop_assert["cpp_operator_2args"],
        op=tpl_body_operation["cpp_operator_2args"],
    )
    obj_arith_2args = lang_proto(
        func_decl=tpl_func_declaration["obj"],
        decl=tpl_body_declaration["cpp2args"],
        init=tpl_body_init["2args"],
        load=tpl_body_load["obj2args"],
        loop_body=tpl_body_loop_body["cpp_operator_2args"],
        loop_assert=tpl_body_loop_assert["obj_operator_2args"],
        op=tpl_body_operation["obj_operator_2args"],
    )

    arith_2args = {"c": c_arith_2args, "cpp": cpp_arith_2args, "obj": obj_arith_2args}
    sub_2args = {
        "c": override(c_arith_2args, **{K_INIT: tpl_body_init["2args_sub"]}),
        "cpp": override(cpp_arith_2args, **{K_INIT: tpl_body_init["2args_sub"]}),
        "obj": override(obj_arith_2args, **{K_INIT: tpl_body_init["2args_sub"]}),
    }

    load = {
        "c": lang_proto(
            func_decl=tpl_func_declaration["c"],
            decl=tpl_body_declaration["c1arg"],
            init=tpl_body_init["1arg"],
            load=tpl_body_load["c1arg"],
            loop_body=tpl_body_loop_body["c_operator_1arg"],
            loop_assert=tpl_body_loop_assert["c_operator_1arg"],
            op="",
        ),
        "cpp": lang_proto(
            func_decl=tpl_func_declaration["cpp"],
            decl=tpl_body_declaration["cpp1arg"],
            init=tpl_body_init["1arg"],
            load=tpl_body_load["cpp1arg"],
            loop_body=tpl_body_loop_body["cpp_operator_1arg"],
            loop_assert=tpl_body_loop_assert["cpp_operator_1arg"],
            op="",
        ),
        "obj": lang_proto(
            func_decl=tpl_func_declaration["obj"],
            decl=tpl_body_declaration["cpp1arg"],
            init=tpl_body_init["1arg"],
            load=tpl_body_load["obj1arg"],
            loop_body=tpl_body_loop_body["obj_operator_1arg"],
            loop_assert=tpl_body_loop_assert["obj_operator_1arg"],
            op="",
        ),
    }

    store = {
        "c": lang_proto(
            func_decl=tpl_func_declaration["c"],
            decl=tpl_body_declaration["c2args"],
            init=tpl_body_init["1arg"],  # other input array used to store
            load=tpl_body_load["c1arg"],
            loop_body=tpl_body_loop_body["c_store"],
            loop_assert=tpl_body_loop_assert["store"],
            op=tpl_body_operation["c_store"],
        ),
        "cpp": lang_proto(
            func_decl=tpl_func_declaration["cpp"],
            decl=tpl_body_declaration["cpp2args"],
            init=tpl_body_init["1arg"],
            load=tpl_body_load["cpp1arg"],
            loop_body=tpl_body_loop_body["cpp_store"],
            loop_assert=tpl_body_loop_assert["store"],
            op=tpl_body_operation["cpp_store"],
        ),
        "obj": lang_proto(
            func_decl=tpl_func_declaration["obj"],
            decl=tpl_body_declaration["cpp2args"],
            init=tpl_body_init["1arg"],
            load=tpl_body_load["obj1arg"],
            loop_body=tpl_body_loop_body["cpp_store"],
            loop_assert=tpl_body_loop_assert["store"],
            op=tpl_body_operation["obj_store"],
        ),
    }

    set_k = {
        "c": lang_proto(
            func_decl=tpl_func_declaration["c"],
            decl=tpl_body_declaration["c1arg_int32"],
            init=tpl_body_init["1arg_msk"],
            load=tpl_body_load["c1arg_msk"],
            loop_body=tpl_body_loop_body["c_store"],
            loop_assert=tpl_body_loop_assert["c_mask_2args"],
            op="",
        ),
        "cpp": lang_proto(
            func_decl=tpl_func_declaration["cpp"],
            decl=tpl_body_declaration["cpp1arg_int32"],
            init=tpl_body_init["1arg_msk"],
            load=tpl_body_load["cpp1arg_msk"],
            loop_body=tpl_body_loop_body["cpp_store"],
            loop_assert=tpl_body_loop_assert["cpp_mask_2args"],
            op="",
        ),
        "obj": lang_proto(
            func_decl=tpl_func_declaration["obj"],
            decl=tpl_body_declaration["cpp1arg_int32"],
            init=tpl_body_init["1arg_msk"],
            load=tpl_body_load["obj1arg_msk"],
            loop_body=tpl_body_loop_body["obj_store"],
            loop_assert=tpl_body_loop_assert["obj_mask_2args"],
            op="",
        ),
    }
    
    #andb can be derived from arith I think? 
    #we have to override a few things w the new templates though
    logical_2ops_msk = {
        "c": lang_proto(
            func_decl=tpl_func_declaration["c"],
            decl=tpl_body_declaration["c2args_int32"],
            init=tpl_body_init["2args_msk"],
            load=tpl_body_load["c2args_msk"],
            loop_body=tpl_body_loop_body["bool_2args"],
            loop_assert=tpl_body_loop_assert["c_mask_2args"],
            op=tpl_body_operation["c_msk_operator_2args"],
        ),
        "cpp": lang_proto(
            func_decl=tpl_func_declaration["cpp"],
            decl=tpl_body_declaration["cpp2args_int32"],
            init=tpl_body_init["2args_msk"],
            load=tpl_body_load["cpp2args_msk"],
            loop_body=tpl_body_loop_body["bool_2args"],
            loop_assert=tpl_body_loop_assert["cpp_mask_2args"],
            op=tpl_body_operation["cpp_msk_operator_2args"],
        ),
        "obj": lang_proto(
            func_decl=tpl_func_declaration["obj"],
            decl=tpl_body_declaration["cpp2args_int32"],
            init=tpl_body_init["2args_msk"],
            load=tpl_body_load["obj2args_msk"],
            loop_body=tpl_body_loop_body["bool_2args"],
            loop_assert=tpl_body_loop_assert["obj_mask_2args"],
            op=tpl_body_operation["obj_msk_operator_2args"],
        ),
    }
    #andnb_k is ~inputs1[i] & inputs2[i] so we can overload elegantly hopefuly
    andnb_k = {
        "c": override(logical_2ops_msk["c"], **{K_LOOP_BODY: "\t\tbool res = (~inputs1[i]) &  inputs2[i];"}),
        "cpp": override(logical_2ops_msk["cpp"], **{K_LOOP_BODY: "\t\tbool res = (~inputs1[i]) &  inputs2[i];"}),
        "obj": override(logical_2ops_msk["obj"], **{K_LOOP_BODY: "\t\tbool res = (~inputs1[i]) &  inputs2[i];"}),
    }
    
    #same for andnb without mask, it's just ~inputs1[i] & inputs2[i]
    andnb = {
        "c": override(c_arith_2args, **{K_LOOP_BODY: "\t\t{{dt_ext}}_t res = (~inputs1[i]) &  inputs2[i];"}),
        "cpp": override(cpp_arith_2args, **{K_LOOP_BODY: "\t\tT res = (~inputs1[i]) &  inputs2[i];"}),
        "obj": override(obj_arith_2args, **{K_LOOP_BODY: "\t\tT res = (~inputs1[i]) &  inputs2[i];", K_OP : tpl_body_operation["obj_fn_call_2args"]}),
    }

    set_ = {
        "c": lang_proto(
            func_decl=tpl_func_declaration["c"],
            decl=tpl_body_declaration["c1arg"],
            init=tpl_body_init["constant_input_1arg"],
            load=tpl_body_load["c1arg_set"],
            loop_body=tpl_body_loop_body["c_operator_1arg"],
            loop_assert=tpl_body_loop_assert["c_operator_1arg"],
            op="",
        ),
        "cpp": lang_proto(
            func_decl=tpl_func_declaration["cpp"],
            decl=tpl_body_declaration["cpp1arg"],
            init=tpl_body_init["constant_input_1arg"],
            load=tpl_body_load["cpp1arg_set"],
            loop_body=tpl_body_loop_body["cpp_operator_1arg"],
            loop_assert=tpl_body_loop_assert["cpp_operator_1arg"],
            op="",
        ),
        "obj": lang_proto(
            func_decl=tpl_func_declaration["obj"],
            decl=tpl_body_declaration["cpp1arg"],
            init=tpl_body_init["constant_input_1arg"],
            load=tpl_body_load["obj1arg_set"],
            loop_body=tpl_body_loop_body["obj_operator_1arg"],
            loop_assert=tpl_body_loop_assert["obj_operator_1arg"],
            op="",
        ),
    }

    set1 = {
        "c": lang_proto(
            func_decl=tpl_func_declaration["c"],
            decl=tpl_body_declaration["c_scalar_1arg"],
            init="",
            load=tpl_body_load["c1arg_set"],
            loop_body="\t\t{{dt_ext}}_t res = inputs1;",
            loop_assert=tpl_body_loop_assert["c_operator_1arg"],
            op="",
        ),
        "cpp": lang_proto(
            func_decl=tpl_func_declaration["cpp"],
            decl=tpl_body_declaration["cpp_scalar_1arg"],
            init="",
            load=tpl_body_load["cpp1arg_set"],
            loop_body="\t\tT res = inputs1;",
            loop_assert=tpl_body_loop_assert["cpp_operator_1arg"],
            op="",
        ),
        "obj": lang_proto(
            func_decl=tpl_func_declaration["obj"],
            decl=tpl_body_declaration["cpp_scalar_1arg"],
            init="",
            load=tpl_body_load["obj1arg_set"],
            loop_body="\t\tT res = inputs1;",
            loop_assert=tpl_body_loop_assert["obj_operator_1arg"],
            op="",
        ),
    }

    set1_k = {
        "c": lang_proto(
            func_decl=tpl_func_declaration["c"],
            decl=tpl_body_declaration["c_scalar_1arg"],
            init="",
            load=tpl_body_load["c1arg_set1k"],
            loop_body="\t\t{{dt_ext}}_t res = inputs1;",
            loop_assert=tpl_body_loop_assert["c_mask_2args"],
            op="",
        ),
        "cpp": lang_proto(
            func_decl=tpl_func_declaration["cpp"],
            decl=tpl_body_declaration["cpp_scalar_1arg"],
            init="",
            load=tpl_body_load["cpp1arg_set1k"],
            loop_body="\t\tT res = inputs1;",
            loop_assert=tpl_body_loop_assert["cpp_mask_2args"],
            op="",
        ),
        "obj": lang_proto(
            func_decl=tpl_func_declaration["obj"],
            decl=tpl_body_declaration["cpp_scalar_1arg"],
            init="",
            load=tpl_body_load["obj1arg_set1k"],
            loop_body="\t\tT res = inputs1;",
            loop_assert=tpl_body_loop_assert["obj_mask_2args"],
            op="",
        ),
    }

    set0 = {
        "c": lang_proto(
            func_decl=tpl_func_declaration["c"],
            decl=tpl_body_declaration["c_scalar_1arg"],
            init="",
            load="\t{{reg_type}} r1 = mipp_{{func}}_{{dt_ext}}();",
            loop_body="\t\t{{dt_ext}}_t res = 0;",
            loop_assert=tpl_body_loop_assert["c_operator_1arg"],
            op="",
        ),
        "cpp": lang_proto(
            func_decl=tpl_func_declaration["cpp"],
            decl=tpl_body_declaration["cpp_scalar_1arg"],
            init="",
            load="\t{{reg_type}} r1 = mipp::{{func}}<{{dt_ext}}>();",
            loop_body="\t\tT res = inputs1;",
            loop_assert="\t\tREQUIRE(res == 0);",
            op="",
        ),
        "obj": lang_proto(
            func_decl=tpl_func_declaration["obj"],
            decl=tpl_body_declaration["cpp_scalar_1arg"],
            init="",
            load="\t{{reg_type}} r1; r1.r = mipp::{{func}}<{{dt_ext}}>();",
            loop_body="\t\tT res = inputs1;",
            loop_assert="\t\tREQUIRE(res == 0);",
            op="",
        ),
    }

    set0_k = {
        "c": lang_proto(
            func_decl=tpl_func_declaration["c"],
            decl=tpl_body_declaration["c_scalar_1arg"],
            init="",
            load="\t{{msk_type}} m1 = mipp_{{func}}_{{dt_ext}}(); {{reg_type}} r1 = mipp_toreg_{{dt_ext}}(m1);",
            loop_body="\t\t{{dt_ext}}_t res = 0;",
            loop_assert=tpl_body_loop_assert["c_mask_2args"],
            op="",
        ),
        "cpp": lang_proto(
            func_decl=tpl_func_declaration["cpp"],
            decl=tpl_body_declaration["cpp_scalar_1arg"],
            init="",
            load="\t{{msk_type}} m1 = mipp::{{func}}<{{dt_ext}}>(); {{reg_type}} r1 = mipp::toreg(m1);",
            loop_body="\t\tT res = inputs1;",
            loop_assert=tpl_body_loop_assert["cpp_mask_2args"],
            op="",
        ),
        "obj": lang_proto(
            func_decl=tpl_func_declaration["obj"],
            decl=tpl_body_declaration["cpp_scalar_1arg"],
            init="",
            load="\t{{msk_type}} m1; m1.m = mipp::{{func}}<{{dt_ext}}>(); {{reg_type}} r1; r1.r = mipp::toreg(m1.m);",
            loop_body="\t\tT res = inputs1;",
            loop_assert=tpl_body_loop_assert["obj_mask_2args"],
            op="",
        ),
    }

    getfirst = {
        "c": lang_proto(
            func_decl=tpl_func_declaration["c"],
            decl=tpl_body_declaration["c1arg"],
            init=tpl_body_init["1arg"],
            load=tpl_body_load["c1arg"],
            loop_body="\t\t{{dt_ext}}_t res = mipp_getfirst_{{dt_ext}}(r1);",
            loop_assert="\t\tREQUIRE(res == inputs1[0]);",
            op="",
        ),
        "cpp": lang_proto(
            func_decl=tpl_func_declaration["cpp"],
            decl=tpl_body_declaration["cpp1arg"],
            init=tpl_body_init["1arg"],
            load=tpl_body_load["cpp1arg"],
            loop_body="\t\tT res = mipp::getfirst(r1);",
            loop_assert="\t\tREQUIRE(res == inputs1[0]);",
            op="",
        ),
        "obj": lang_proto(
            func_decl=tpl_func_declaration["obj"],
            decl=tpl_body_declaration["cpp1arg"],
            init=tpl_body_init["1arg"],
            load=tpl_body_load["obj1arg"],
            loop_body="\t\tT res = r1[0];",
            loop_assert="\t\tREQUIRE(res == inputs1[0]);",
            op="",
        ),
    }

    blend = {
        "c": lang_proto(
            func_decl=tpl_func_declaration["c"],
            decl=tpl_body_declaration["c2args"] + """\nint32_t mask1[vectorSize] = {0};""",
            init=tpl_body_init["2args"]
            + """\tfor (unsigned i = 0; i < vectorSize; i++)mask1[i] = i % 2 ? 1 : 0;\n""",
            load="\t{{msk_type}} m1 = mipp_set_k_{{dt_ext}}(mask1); {{reg_type}} r1 = mipp_set1_{{dt_ext}}(1); {{reg_type}} r2 = mipp_set1_{{dt_ext}}(2);",
            loop_body="\t\t{{dt_ext}}_t res = mipp_get_k_{{dt_ext}}(m1,i) ? mipp_get_{{dt_ext}}(r1, i) : mipp_get_{{dt_ext}}(r2, i);",
            loop_assert="\t\tREQUIRE(mipp_get_{{dt_ext}}(r3, i) == res);",
            op="\t{{reg_type}} r3 = mipp_blend_{{dt_ext}}(r1, r2, m1);",
        ),
        "cpp": lang_proto(
            func_decl=tpl_func_declaration["cpp"],
            decl=tpl_body_declaration["cpp2args"] + """\nint32_t mask1[vectorSize] = {0};""",
            init=tpl_body_init["2args"]
            + """\tfor (unsigned i = 0; i < vectorSize; i++)mask1[i] = i % 2 ? 1 : 0;\n""",
            load="\t{{msk_type}} m1 = mipp::set_k<{{dt_ext}}>(mask1); {{reg_type}} r1 = mipp::set1<{{dt_ext}}>(1); {{reg_type}} r2 = mipp::set1<{{dt_ext}}>(2);",
            loop_body="\t\t{{dt_ext}} res = mipp::get(m1,i) ? mipp::get(r1, i) : mipp::get(r2, i);",
            loop_assert="\t\tREQUIRE(mipp::get(r3, i) == res);",
            op="\t{{reg_type}} r3 = mipp::blend(r1, r2, m1);",
        ),
        "obj": lang_proto(
            func_decl=tpl_func_declaration["obj"],
            decl=tpl_body_declaration["cpp2args"] + """\nint32_t mask1[vectorSize] = {0};""",
            init=tpl_body_init["2args"]
            + """\tfor (unsigned i = 0; i < vectorSize; i++)mask1[i] = i % 2 ? 1 : 0;\n""",
            load="\t{{msk_type}} m1; m1.m = mipp::set_k<{{dt_ext}}>(mask1); {{reg_type}} r1; r1.r = mipp::set1<{{dt_ext}}>(1); {{reg_type}} r2; r2.r = mipp::set1<{{dt_ext}}>(2);",
            loop_body="\t\t{{dt_ext}} res = mipp::get(m1.m,i) ? mipp::get(r1.r, i) : mipp::get(r2.r, i);",
            loop_assert="\t\tREQUIRE(r3[i] == res);",
            op="\t{{reg_type}} r3; r3.r = mipp::blend(r1.r, r2.r, m1.m);",
        ),
    }
    
    arith_1arg = {
        "c": lang_proto(
            func_decl=tpl_func_declaration["c"],
            decl=tpl_body_declaration["c1arg"],
            init=tpl_body_init["1arg"],
            load=tpl_body_load["c1arg"],
            loop_body=tpl_body_loop_body["c_operator_1arg"],
            loop_assert=tpl_body_loop_assert["c_operator_1arg"],
            op=tpl_body_operation["c_operator_1arg"],
        ),
        "cpp": lang_proto(
            func_decl=tpl_func_declaration["cpp"],
            decl=tpl_body_declaration["cpp1arg"],
            init=tpl_body_init["1arg"],
            load=tpl_body_load["cpp1arg"],
            loop_body=tpl_body_loop_body["cpp_operator_1arg"],
            loop_assert=tpl_body_loop_assert["cpp_operator_1arg"],
            op=tpl_body_operation["cpp_operator_1arg"],
        ),
        "obj": lang_proto(
            func_decl=tpl_func_declaration["obj"],
            decl=tpl_body_declaration["cpp1arg"],
            init=tpl_body_init["1arg"],
            load=tpl_body_load["obj1arg"],
            loop_body=tpl_body_loop_body["obj_operator_1arg"],
            loop_assert=tpl_body_loop_assert["obj_operator_1arg"],
            op=tpl_body_operation["obj_operator_1arg"],
        ),
    }
    
    logi_1op_msk = {
        "c": lang_proto(
            func_decl=tpl_func_declaration["c"],
            decl=tpl_body_declaration["c1arg_int32"],
            init=tpl_body_init["1arg_msk"],
            load=tpl_body_load["c1arg_msk"],
            loop_body="\t\tbool res = ~inputs1[i];",
            loop_assert=tpl_body_loop_assert["c_mask_2args"],
            op=tpl_body_operation["c_msk_operator_1arg"],
        ),
        "cpp": lang_proto(
            func_decl=tpl_func_declaration["cpp"],
            decl=tpl_body_declaration["cpp1arg_int32"],
            init=tpl_body_init["1arg_msk"],
            load=tpl_body_load["cpp1arg_msk"],
            loop_body="\t\tbool res = ~inputs1[i];",
            loop_assert=tpl_body_loop_assert["cpp_mask_2args"],
            op=tpl_body_operation["cpp_msk_operator_1arg"],
        ),
        "obj": lang_proto(
            func_decl=tpl_func_declaration["obj"],
            decl=tpl_body_declaration["cpp1arg_int32"],
            init=tpl_body_init["1arg_msk"],
            load=tpl_body_load["obj1arg_msk"],
            loop_body="\t\tbool res = ~inputs1[i];",
            loop_assert=tpl_body_loop_assert["obj_mask_2args"],
            op=tpl_body_operation["obj_msk_operator_1arg"]
        ),
    }

    return {
        "arith_2args": arith_2args,
        "sub_2args": sub_2args,
        "load": load,
        "store": store,
        "set_k": set_k,
        "set": set_,
        "set1": set1,
        "set1_k": set1_k,
        "set0": set0,
        "set0_k": set0_k,
        "getfirst": getfirst,
        "blend": blend,
        "logical_2ops_msk": logical_2ops_msk,
        "andnb_k": andnb_k,
        "andnb": andnb,
        "arith_1arg": arith_1arg,
        "logi_1op_msk": logi_1op_msk,
    }

prototype_registry = mk_prototype_registry()

# float support of logical operators is odd. Will come back to them later.
set_skip_float = {
    "andb",
    "orb",
    "xorb",
    "notb",
    "andnb",
}

def mk_gen_test_dict() -> dict:
    generic = tpl_bodies["generic_for_loop"]

    def spec(func, long_name, short_name, op, proto_key):
        return {
            "template": generic,
            "long_name": long_name,
            "short_name": short_name,
            "op": op,
            "protos": prototype_registry[proto_key],
        }

    return {
        # arithmetic functions
        "add": spec("add", "Addition", "add", "+", "arith_2args"),
        "sub": spec("sub", "Subtraction", "sub", "-", "sub_2args"),
        "mul": spec("mul", "Multiplication", "mul", "*", "arith_2args"),
        "div": spec("div", "Division", "div", "/", "arith_2args"),
        "andb": spec("andb", "Bitwise And", "andb", "&", "arith_2args"),
        "orb": spec("orb", "Bitwise Or", "orb", "|", "arith_2args"),
        "xorb": spec("xorb", "Bitwise Xor", "xorb", "^", "arith_2args"),
        # memory access functions
        "load": spec("load", "Load", "load", "", "load"),
        "loadu": spec("loadu", "Load Unaligned", "loadu", "", "load"),
        "store": spec("store", "Store", "store", "", "store"),
        "storeu": spec("storeu", "Store Unaligned", "storeu", "", "store"),
        "set": spec("set", "Set", "set", "", "set"),
        "set_k": spec("set_k", "Set Mask", "set_k", "", "set_k"),
        "set1": spec("set1", "Set to scalar", "set1", "", "set1"),
        "set1_k": spec("set1_k", "Set Mask to scalar", "set1_k", "", "set1_k"),
        "set0": spec("set0", "Set to zero", "set0", "", "set0"),
        "set0_k": spec("set0_k", "Set Mask to zero", "set0_k", "", "set0_k"),
        "get": spec("get", "Get", "get", "", "load"),
        "getfirst": spec("getfirst", "Get First Lane", "getfirst", "", "getfirst"),
        "blend": spec("blend", "Blend", "blend", "", "blend"),
        "andb_k": spec("andb_k", "Bitwise And with Mask", "andb_k", "&", "logical_2ops_msk"),
        "orb_k": spec("orb_k", "Bitwise Or with Mask", "orb_k", "|", "logical_2ops_msk"),
        "xorb_k": spec("xorb_k", "Bitwise Xor with Mask", "xorb_k", "^", "logical_2ops_msk"),
        
        "andnb_k": spec("andnb_k", "Bitwise And Not with Mask", "andnb_k", "", "andnb_k"),
        "andnb": spec("andnb", "Bitwise And Not", "andnb", "", "andnb"),
        
        "notb": spec("notb", "Bitwise Not", "notb", "~", "arith_1arg"),
        "notb_k": spec("notb_k", "Bitwise Not with Mask", "notb_k", "~", "logi_1op_msk"),
        
    }

gen_test_dict = mk_gen_test_dict()
