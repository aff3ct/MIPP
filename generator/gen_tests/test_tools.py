import os
import sys
from jinja2 import Template, StrictUndefined

path = os.getcwd()
from tools import all_datatypes

sys.path.insert(1,path + '/../')

#this file contains templates for generating test functions, 
#the philosophy is to have very small template for each past of the 
#test function declaration. In order to have a lot of genericity 

#not complete obv
set_mask_op = { "set_k", "set1_k", "set0_k"}

#template for the function declaration
#e.g. void test_cmipp_add_i8() or template <typename T> void test_cppmipp_add()
tpl_func_declaration = {
    "c": """void test_cmipp_{{func}}_{{dt_ext}}(){""",
    "cpp": """template <typename T>\nvoid test_cppmipp_{{func}}(){""",
    "obj": """template <typename T>\nvoid test_objmipp_{{func}}(){""",
}

#template for the variable declaration and initialization
#e.g. defining the input arrays
tpl_body_declaration = {
    
    #I think masks only loading from i32 is odd. 
    "c1arg_int32": """\tconst int vectorSize = {{size}}; int32_t inputs1[vectorSize] = {0};""",
    "cpp1arg_int32": """\tconst int vectorSize = mipp::N<T>(); int32_t inputs1[vectorSize] = {0};""",
    
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

#template for the initialization of the input arrays
#e.g. filling them with some values
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
    #for things like sub, we want the guarantee that inputs1[i] > inputs2[i] 
    #to avoid negative results that might cause issues with unsigned types.
    "2args_sub": """\tstd::iota(inputs1, inputs1 + vectorSize, 1);
\tstd::iota(inputs2, inputs2 + vectorSize, 1);
\tstd::mt19937 g;
\tstd::shuffle(inputs1, inputs1 + vectorSize, g);
\tstd::shuffle(inputs2, inputs2 + vectorSize, g);
\tfor(int i = 0; i < vectorSize; i++)
\t{
\t\tinputs1[i] += inputs2[i];
\t}""",

    "1arg_msk":
"""\tfor (auto i = 0; i < vectorSize; i++)
\t\tinputs1[i] = i % 2 ? 1 : 0;
""",

    #reusable for set1, set0 maybe _k variants too?
    "constant_input_1arg":
"""\tfor (auto i = 0; i < vectorSize; i++)
\t\tinputs1[i] = 0;
"""
}

#template for loading the input arrays into mipp registers
tpl_body_load = {
    "c1arg": """\t{{reg_type}} r1 = mipp_load_{{dt_ext}}(inputs1);""",
    
    "c2args": """\t{{reg_type}} r1 = mipp_load_{{dt_ext}}(inputs1);
\t{{reg_type}} r2 = mipp_load_{{dt_ext}}(inputs2);""",

    "c3args": """\t{{reg_type}} r1 = mipp_load_{{dt_ext}}(inputs1);
\t{{reg_type}} r2 = mipp_load_{{dt_ext}}(inputs2);
\t{{reg_type}} r3 = mipp_load_{{dt_ext}}(inputs3);""",


    "cpp1arg": """\t{{reg_type}} r1 = mipp::load<{{dt_ext}}>(inputs1);""",
    "cpp2args": """\t{{reg_type}} r1 = mipp::load<{{dt_ext}}>(inputs1), r2 = mipp::load<{{dt_ext}}>(inputs2);""",
    
    
    "obj1arg":"""\t//{{reg_type}} r1(inputs);//waiting for load to be fixed in obj layer
\t{{reg_type}} r1; r1.r = mipp::load<T>(inputs1);""",

    "obj2args":
"""\t//{{reg_type}} r1(inputs1), r2(inputs2);//waiting for load to be fixed in obj layer
\t{{reg_type}} r1, r2; r1.r = mipp::load<T>(inputs1); r2.r = mipp::load<T>(inputs2);""",

    "c1arg_msk": """\t{{msk_type}} m1 = mipp_{{func}}_{{dt_ext}}(inputs1); {{reg_type}} r1 = mipp_toreg_{{dt_ext}}(m1);""",
    "cpp1arg_msk": """\t{{msk_type}} m1 = mipp::{{func}}<{{dt_ext}}>(inputs1); {{reg_type}} r1 = mipp::toreg(m1);""",
    "obj1arg_msk": """\t{{msk_type}} m1; m1.m = mipp::{{func}}<{{dt_ext}}>(inputs1); {{reg_type}} r1; r1.r = mipp::toreg(m1.m);""",

    "c1arg_set" : """\t{{reg_type}} r1 = mipp_{{func}}_{{dt_ext}}(inputs1);""",
    "cpp1arg_set" : """\t{{reg_type}} r1 = mipp::{{func}}<{{dt_ext}}>(inputs1);""",
    "obj1arg_set" : """\t{{reg_type}} r1; r1.r = mipp::{{func}}<{{dt_ext}}>(inputs1);""",
}

#template for the operation on the registers
#e.g. r3 = r1 + r2 or r3 = mipp::add(r1, r2)
tpl_body_operation = {
    "c_operator_2args": """\t{{reg_type}} r3 = mipp_{{func}}_{{dt_ext}}(r1, r2);""",
    "cpp_operator_2args": """\t{{reg_type}} r3 = mipp::{{func}}(r1, r2);""",
    "obj_operator_2args": """\t{{reg_type}} r3 = r1 {{op}} r2;""",

    "c_store": """\tmipp_store_{{dt_ext}}(inputs2, r1);""",
    "cpp_store": """\tmipp::store(inputs2, r1);""",
    "obj_store": """\tmipp::store(inputs2, r1.r);""",
}

#template for the body of the loop that performs the op on the scalar inputs
#TODO : some asserts don't use loop think about it @ some point
tpl_body_loop_body = {
    "c_operator_2args": """\t\t{{dt_ext}}_t res = inputs1[i] {{op}}  inputs2[i];""",
    "cpp_operator_2args": """\t\tT res = inputs1[i] {{op}}  inputs2[i];""",
    
    "c_operator_1arg": """\t\t{{dt_ext}}_t res = {{op}} inputs1[i];""",
    "cpp_operator_1arg": """\t\tT res = {{op}} inputs1[i];""",
    "obj_operator_1arg": """\t\tT res = {{op}} inputs1[i];""",
    
    "c_fn_call_2args": """\t\t{{dt_ext}}_t res = {{func}}(inputs1[i], inputs2[i]);""",
    "c_fn_call_1arg": """\t\t{{dt_ext}}_t res = {{func}}(inputs1[i]);""",
    
    "c_store": """\t\t{{dt_ext}}_t res = inputs1[i];""",
    "cpp_store": """\t\tT res = inputs1[i];""",
    "obj_store": """\t\tT res = inputs1[i];""",
    
}

#template for the body of the loop that performs the assertion
#TODO : some asserts don't use loop think about it @ some point
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


#"high level" template for the whole test
#when rendered, creates a "specialized" template 
#that is rendered again with the specific func, datatype, op, etc to create the final test function body


tpl_bodies = {
    "generic_for_loop": 
"""{{func_declaration}}
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


#used to store "common" template patterns. 
#for instance, arith_2args is a valid 
#pattern for all arithmetic/logical operators with 2 args.
prototype_registry = {
    "arith_2args" : {
            "c": {
                    "tpl_func_declaration" : tpl_func_declaration["c"], 
                    "tpl_body_declaration" : tpl_body_declaration["c2args"], 
                    "tpl_body_initialization" : tpl_body_init["2args"], 
                    "tpl_body_load" : tpl_body_load["c2args"], 
                    "tpl_body_loop_body" : tpl_body_loop_body["c_operator_2args"], 
                    "tpl_body_loop_assert" : tpl_body_loop_assert["c_operator_2args"], 
                    "tpl_body_operation" : tpl_body_operation["c_operator_2args"]},
            "cpp": {
                    "tpl_func_declaration" : tpl_func_declaration["cpp"], 
                    "tpl_body_declaration" : tpl_body_declaration["cpp2args"], 
                    "tpl_body_initialization" : tpl_body_init["2args"], 
                    "tpl_body_load" : tpl_body_load["cpp2args"], 
                    "tpl_body_loop_body" : tpl_body_loop_body["cpp_operator_2args"], 
                    "tpl_body_loop_assert" : tpl_body_loop_assert["cpp_operator_2args"], 
                    "tpl_body_operation" : tpl_body_operation["cpp_operator_2args"]},
             "obj": {
             
                    "tpl_func_declaration" : tpl_func_declaration["obj"], 
                    "tpl_body_declaration" : tpl_body_declaration["cpp2args"], 
                    "tpl_body_initialization" : tpl_body_init["2args"], 
                    "tpl_body_load" : tpl_body_load["obj2args"], 
                    "tpl_body_loop_body" : tpl_body_loop_body["cpp_operator_2args"], 
                    "tpl_body_loop_assert" : tpl_body_loop_assert["obj_operator_2args"], 
                    "tpl_body_operation" : tpl_body_operation["obj_operator_2args"]}

    },      
    
    "sub_2args" : {
            "c": {
                    "tpl_func_declaration" : tpl_func_declaration["c"], 
                    "tpl_body_declaration" : tpl_body_declaration["c2args"], 
                    "tpl_body_initialization" : tpl_body_init["2args_sub"], 
                    "tpl_body_load" : tpl_body_load["c2args"], 
                    "tpl_body_loop_body" : tpl_body_loop_body["c_operator_2args"], 
                    "tpl_body_loop_assert" : tpl_body_loop_assert["c_operator_2args"], 
                    "tpl_body_operation" : tpl_body_operation["c_operator_2args"]},
            "cpp": {
                    "tpl_func_declaration" : tpl_func_declaration["cpp"], 
                    "tpl_body_declaration" : tpl_body_declaration["cpp2args"], 
                    "tpl_body_initialization" : tpl_body_init["2args_sub"], 
                    "tpl_body_load" : tpl_body_load["cpp2args"], 
                    "tpl_body_loop_body" : tpl_body_loop_body["cpp_operator_2args"], 
                    "tpl_body_loop_assert" : tpl_body_loop_assert["cpp_operator_2args"], 
                    "tpl_body_operation" : tpl_body_operation["cpp_operator_2args"]},
             "obj": {
                    "tpl_func_declaration" : tpl_func_declaration["obj"], 
                    "tpl_body_declaration" : tpl_body_declaration["cpp2args"], 
                    "tpl_body_initialization" : tpl_body_init["2args_sub"], 
                    "tpl_body_load" : tpl_body_load["obj2args"], 
                    "tpl_body_loop_body" : tpl_body_loop_body["cpp_operator_2args"], 
                    "tpl_body_loop_assert" : tpl_body_loop_assert["obj_operator_2args"], 
                    "tpl_body_operation" : tpl_body_operation["obj_operator_2args"]}
    },
    
    #load is the same as arithmetic. Except the load 
    #already IS the operation so we don't need to perform any operation on the registers.
    "load" : {
            "c": {
                    "tpl_func_declaration" : tpl_func_declaration["c"], 
                    "tpl_body_declaration" : tpl_body_declaration["c1arg"], 
                    "tpl_body_initialization" : tpl_body_init["1arg"], 
                    "tpl_body_load" : tpl_body_load["c1arg"], 
                    "tpl_body_loop_body" : tpl_body_loop_body["c_operator_1arg"], 
                    "tpl_body_loop_assert" : tpl_body_loop_assert["c_operator_1arg"], 
                    "tpl_body_operation" : ""},#no operation for load test
            "cpp": {
                    "tpl_func_declaration" : tpl_func_declaration["cpp"], 
                    "tpl_body_declaration" : tpl_body_declaration["cpp1arg"], 
                    "tpl_body_initialization" : tpl_body_init["1arg"], 
                    "tpl_body_load" : tpl_body_load["cpp1arg"], 
                    "tpl_body_loop_body" : tpl_body_loop_body["cpp_operator_1arg"], 
                    "tpl_body_loop_assert" : tpl_body_loop_assert["cpp_operator_1arg"],
                    "tpl_body_operation" : ""},#no operation for load test
             "obj": {  
                    "tpl_func_declaration" : tpl_func_declaration["obj"], 
                    "tpl_body_declaration" : tpl_body_declaration["cpp1arg"], 
                    "tpl_body_initialization" : tpl_body_init["1arg"], 
                    "tpl_body_load" : tpl_body_load["obj1arg"], 
                    "tpl_body_loop_body" : tpl_body_loop_body["obj_operator_1arg"], 
                    "tpl_body_loop_assert" : tpl_body_loop_assert["obj_operator_1arg"],
                    "tpl_body_operation" : ""}#no operation for load test
    },
    #store is weird I think a lot of new 
    #templates will have to be created for it. 
    "store" : {
        "c" : {
            "tpl_func_declaration" : tpl_func_declaration["c"], 
            "tpl_body_declaration" : tpl_body_declaration["c2args"], 
            "tpl_body_initialization" : tpl_body_init["1arg"],#other input array used to store
            "tpl_body_load" : tpl_body_load["c1arg"], 
            "tpl_body_loop_body" : tpl_body_loop_body["c_store"], 
            "tpl_body_loop_assert" : tpl_body_loop_assert["store"], 
            "tpl_body_operation" : tpl_body_operation["c_store"]
        },
        "cpp" : {
            "tpl_func_declaration" : tpl_func_declaration["cpp"], 
            "tpl_body_declaration" : tpl_body_declaration["cpp2args"], 
            "tpl_body_initialization" : tpl_body_init["1arg"], 
            "tpl_body_load" : tpl_body_load["cpp1arg"], 
            "tpl_body_loop_body" : tpl_body_loop_body["cpp_store"], 
            "tpl_body_loop_assert" : tpl_body_loop_assert["store"], 
            "tpl_body_operation" : tpl_body_operation["cpp_store"]
        },
        "obj" : {
            "tpl_func_declaration" : tpl_func_declaration["obj"], 
            "tpl_body_declaration" : tpl_body_declaration["cpp2args"], 
            "tpl_body_initialization" : tpl_body_init["1arg"], 
            "tpl_body_load" : tpl_body_load["obj1arg"], 
            "tpl_body_loop_body" : tpl_body_loop_body["cpp_store"], #store test has the same loop body as cpp operator test
            "tpl_body_loop_assert" : tpl_body_loop_assert["store"], 
            "tpl_body_operation" : tpl_body_operation["obj_store"]
        },
    },
    
    "set_k" : {
        "c" : {
            "tpl_func_declaration" : tpl_func_declaration["c"], 
            "tpl_body_declaration" : tpl_body_declaration["c1arg_int32"], 
            "tpl_body_initialization" : tpl_body_init["1arg_msk"], 
            "tpl_body_load" : tpl_body_load["c1arg_msk"], 
            "tpl_body_loop_body" : tpl_body_loop_body["c_store"], 
            "tpl_body_loop_assert" : tpl_body_loop_assert["c_mask_2args"], 
            "tpl_body_operation" : "" #no operation for set_k test
        },
        "cpp" : {
            "tpl_func_declaration" : tpl_func_declaration["cpp"], 
            "tpl_body_declaration" : tpl_body_declaration["cpp1arg_int32"], 
            "tpl_body_initialization" : tpl_body_init["1arg_msk"], 
            "tpl_body_load" : tpl_body_load["cpp1arg_msk"], 
            "tpl_body_loop_body" : tpl_body_loop_body["cpp_store"], 
            "tpl_body_loop_assert" : tpl_body_loop_assert["cpp_mask_2args"], 
            "tpl_body_operation" : "" #no operation for set_k test
        },
        "obj" : {
            "tpl_func_declaration" : tpl_func_declaration["obj"], 
            "tpl_body_declaration" : tpl_body_declaration["cpp1arg_int32"], 
            "tpl_body_initialization" : tpl_body_init["1arg_msk"], 
            "tpl_body_load" : tpl_body_load["obj1arg_msk"], 
            "tpl_body_loop_body" : tpl_body_loop_body["obj_store"],
            "tpl_body_loop_assert" : tpl_body_loop_assert["obj_mask_2args"], 
            "tpl_body_operation" : "" #no operation for set_k test
        },
    },
    
    "set" : {
        "c" : {
            "tpl_func_declaration" : tpl_func_declaration["c"], 
            "tpl_body_declaration" : tpl_body_declaration["c1arg"], 
            "tpl_body_initialization" : tpl_body_init["constant_input_1arg"], 
            "tpl_body_load" : tpl_body_load["c1arg_set"], 
            "tpl_body_loop_body" : tpl_body_loop_body["c_operator_1arg"], 
            "tpl_body_loop_assert" : tpl_body_loop_assert["c_operator_1arg"], 
            "tpl_body_operation" : "" #for set test we can just do res = 1 in the loop body and check that the register value is 1 in the assert
        },
        "cpp" : {
            "tpl_func_declaration" : tpl_func_declaration["cpp"], 
            "tpl_body_declaration" : tpl_body_declaration["cpp1arg"], 
            "tpl_body_initialization" : tpl_body_init["constant_input_1arg"], 
            "tpl_body_load" : tpl_body_load["cpp1arg_set"],
            "tpl_body_loop_body" : tpl_body_loop_body["cpp_operator_1arg"], 
            "tpl_body_loop_assert" : tpl_body_loop_assert["cpp_operator_1arg"], 
            "tpl_body_operation" : "" #no operation for set test
        },
        "obj" : {
            "tpl_func_declaration" : tpl_func_declaration["obj"], 
            "tpl_body_declaration" : tpl_body_declaration["cpp1arg"], 
            "tpl_body_initialization" : tpl_body_init["constant_input_1arg"], 
            "tpl_body_load" : tpl_body_load["obj1arg_set"],
            "tpl_body_loop_body" : tpl_body_loop_body["obj_operator_1arg"], 
            "tpl_body_loop_assert" : tpl_body_loop_assert["obj_operator_1arg"], 
            "tpl_body_operation" : "" #no operation for set test
        },
    },
    
    "set1" : {
        "c" : {
            "tpl_func_declaration" : tpl_func_declaration["c"], 
            "tpl_body_declaration" : tpl_body_declaration["c_scalar_1arg"], 
            "tpl_body_initialization" : "", 
            "tpl_body_load" : tpl_body_load["c1arg_set"], 
            "tpl_body_loop_body" : "\t\t{{dt_ext}}_t res = inputs1;", 
            "tpl_body_loop_assert" : tpl_body_loop_assert["c_operator_1arg"], 
            "tpl_body_operation" : "" 
        },
        "cpp" : {
            "tpl_func_declaration" : tpl_func_declaration["cpp"], 
            "tpl_body_declaration" : tpl_body_declaration["cpp_scalar_1arg"], 
            "tpl_body_initialization" : "", 
            "tpl_body_load" : tpl_body_load["cpp1arg_set"],
            "tpl_body_loop_body" : "\t\tT res = inputs1;", 
            "tpl_body_loop_assert" : tpl_body_loop_assert["cpp_operator_1arg"], 
            "tpl_body_operation" : ""
        },
        "obj" : {
            "tpl_func_declaration" : tpl_func_declaration["obj"], 
            "tpl_body_declaration" : tpl_body_declaration["cpp_scalar_1arg"], 
            "tpl_body_initialization" : "", 
            "tpl_body_load" : tpl_body_load["obj1arg_set"],
            "tpl_body_loop_body" : "\t\tT res = inputs1;", 
            "tpl_body_loop_assert" : tpl_body_loop_assert["obj_operator_1arg"], 
            "tpl_body_operation" : ""
        },
    },
    
    "set1_k" : {
        "c" : {
            "tpl_func_declaration" : tpl_func_declaration["c"], 
            "tpl_body_declaration" : tpl_body_declaration["c_scalar_1arg"], 
            "tpl_body_initialization" : "", 
            "tpl_body_load" : tpl_body_load["c1arg_msk"], 
            "tpl_body_loop_body" : "\t\t{{dt_ext}}_t res = inputs1;", 
            "tpl_body_loop_assert" : tpl_body_loop_assert["c_mask_2args"], 
            "tpl_body_operation" : "" 
        },
        "cpp" : {
            "tpl_func_declaration" : tpl_func_declaration["cpp"], 
            "tpl_body_declaration" : tpl_body_declaration["cpp_scalar_1arg"], 
            "tpl_body_initialization" : "", 
            "tpl_body_load" : tpl_body_load["cpp1arg_msk"],
            "tpl_body_loop_body" : "\t\tT res = inputs1;", 
            "tpl_body_loop_assert" : tpl_body_loop_assert["cpp_mask_2args"], 
            "tpl_body_operation" : ""
        },
        "obj" : {
            "tpl_func_declaration" : tpl_func_declaration["obj"], 
            "tpl_body_declaration" : tpl_body_declaration["cpp_scalar_1arg"], 
            "tpl_body_initialization" : "", 
            "tpl_body_load" : tpl_body_load["obj1arg_msk"],
            "tpl_body_loop_body" : "\t\tT res = inputs1;", 
            "tpl_body_loop_assert" : tpl_body_loop_assert["obj_mask_2args"], 
            "tpl_body_operation" : ""
        },
    },
    
    "set0" : {
        "c" : {
            "tpl_func_declaration" : tpl_func_declaration["c"], 
            "tpl_body_declaration" : tpl_body_declaration["c_scalar_1arg"],
            "tpl_body_initialization" : "",
            "tpl_body_load" : "\t{{reg_type}} r1 = mipp_{{func}}_{{dt_ext}}();",
            "tpl_body_loop_body" : "\t\t{{dt_ext}}_t res = 0;",
            "tpl_body_loop_assert" : tpl_body_loop_assert["c_operator_1arg"],
            "tpl_body_operation" : "" 
        },
        "cpp" : {
            "tpl_func_declaration" : tpl_func_declaration["cpp"], 
            "tpl_body_declaration" : tpl_body_declaration["cpp_scalar_1arg"], 
            "tpl_body_initialization" : "", 
            "tpl_body_load" : "\t{{reg_type}} r1 = mipp::{{func}}<{{dt_ext}}>();",
            "tpl_body_loop_body" : "\t\tT res = inputs1;", 
            "tpl_body_loop_assert" : "\t\tREQUIRE(res == 0);", 
            "tpl_body_operation" : ""
        },
        "obj" : {
            "tpl_func_declaration" : tpl_func_declaration["obj"], 
            "tpl_body_declaration" : tpl_body_declaration["cpp_scalar_1arg"], 
            "tpl_body_initialization" : "", 
            "tpl_body_load" : "\t{{reg_type}} r1; r1.r = mipp::{{func}}<{{dt_ext}}>();",
            "tpl_body_loop_body" : "\t\tT res = inputs1;", 
            "tpl_body_loop_assert" : "\t\tREQUIRE(res == 0);", 
            "tpl_body_operation" : ""
        },
    },
    
    "set0_k" : {
        "c" : {
            "tpl_func_declaration" : tpl_func_declaration["c"], 
            "tpl_body_declaration" : tpl_body_declaration["c_scalar_1arg"],
            "tpl_body_initialization" : "", 
            "tpl_body_load" : "\t{{msk_type}} m1 = mipp_{{func}}_{{dt_ext}}(); {{reg_type}} r1 = mipp_toreg_{{dt_ext}}(m1);",
            "tpl_body_loop_body" : "\t\t{{dt_ext}}_t res = 0;",
            "tpl_body_loop_assert" : tpl_body_loop_assert["c_mask_2args"],
            "tpl_body_operation" : "" 
        },
        "cpp" : {
            "tpl_func_declaration" : tpl_func_declaration["cpp"], 
            "tpl_body_declaration" : tpl_body_declaration["cpp_scalar_1arg"], 
            "tpl_body_initialization" : "", 
            "tpl_body_load" : "\t{{msk_type}} m1 = mipp::{{func}}<{{dt_ext}}>(); {{reg_type}} r1 = mipp::toreg(m1);",
            "tpl_body_loop_body" : "\t\tT res = inputs1;", 
            "tpl_body_loop_assert" : tpl_body_loop_assert["cpp_mask_2args"], 
            "tpl_body_operation" : ""
        },
        "obj" : {
            "tpl_func_declaration" : tpl_func_declaration["obj"], 
            "tpl_body_declaration" : tpl_body_declaration["cpp_scalar_1arg"], 
            "tpl_body_initialization" : "", 
            "tpl_body_load" : "\t{{msk_type}} m1; m1.m = mipp::{{func}}<{{dt_ext}}>(); {{reg_type}} r1; r1.r = mipp::toreg(m1.m);",
            "tpl_body_loop_body" : "\t\tT res = inputs1;", 
            "tpl_body_loop_assert" : tpl_body_loop_assert["obj_mask_2args"], 
            "tpl_body_operation" : ""
        },
    },
    
    
    "getfirst" : {
        "c" : {
            "tpl_func_declaration" : tpl_func_declaration["c"], 
            "tpl_body_declaration" : tpl_body_declaration["c1arg"], 
            "tpl_body_initialization" : tpl_body_init["1arg"], 
            "tpl_body_load" : tpl_body_load["c1arg"], 
            "tpl_body_loop_body" : "\t\t{{dt_ext}}_t res = mipp_getfirst_{{dt_ext}}(r1);", 
            "tpl_body_loop_assert" : "\t\tREQUIRE(res == inputs1[0]);", 
            "tpl_body_operation" : ""
        },
        "cpp" : {
            "tpl_func_declaration" : tpl_func_declaration["cpp"], 
            "tpl_body_declaration" : tpl_body_declaration["cpp1arg"], 
            "tpl_body_initialization" : tpl_body_init["1arg"], 
            "tpl_body_load" : tpl_body_load["cpp1arg"], 
            "tpl_body_loop_body" : "\t\tT res = mipp::getfirst(r1);", 
            "tpl_body_loop_assert" : "\t\tREQUIRE(res == inputs1[0]);", 
            "tpl_body_operation" : ""
        },
        "obj" : {
            "tpl_func_declaration" : tpl_func_declaration["obj"], 
            "tpl_body_declaration" : tpl_body_declaration["cpp1arg"], 
            "tpl_body_initialization" : tpl_body_init["1arg"], 
            "tpl_body_load" : tpl_body_load["obj1arg"], 
            "tpl_body_loop_body" : "\t\tT res = r1[0];", 
            "tpl_body_loop_assert" : "\t\tREQUIRE(res == inputs1[0]);", 
            "tpl_body_operation" : ""
        },
    },
    
    #this is what the generated test for blend should look like 
    #in the cpp version.
    
    
    "blend" : {
        "c" : {
            "tpl_func_declaration" : tpl_func_declaration["c"], 
            "tpl_body_declaration" : tpl_body_declaration["c2args"] + """\nint32_t mask1[vectorSize] = {0};""", 
            "tpl_body_initialization" : tpl_body_init["2args"] + """\tfor (unsigned i = 0; i < vectorSize; i++)mask1[i] = i % 2 ? 1 : 0;\n""",
            "tpl_body_load" : "\t{{msk_type}} m1 = mipp_set_k_{{dt_ext}}(mask1); {{reg_type}} r1 = mipp_set1_{{dt_ext}}(1); {{reg_type}} r2 = mipp_set1_{{dt_ext}}(2);",
            "tpl_body_loop_body" : "\t\t{{dt_ext}}_t res = mipp_get_k_{{dt_ext}}(m1,i) ? mipp_get_{{dt_ext}}(r1, i) : mipp_get_{{dt_ext}}(r2, i);",
            "tpl_body_loop_assert" : "\t\tREQUIRE(mipp_get_{{dt_ext}}(r3, i) == res);", 
            "tpl_body_operation" : "\t{{reg_type}} r3 = mipp_blend_{{dt_ext}}(r1, r2, m1);"
        },
        "cpp" : {
            "tpl_func_declaration" : tpl_func_declaration["cpp"], 
            "tpl_body_declaration" : tpl_body_declaration["cpp2args"] + """\nint32_t mask1[vectorSize] = {0};""", 
            "tpl_body_initialization" : tpl_body_init["2args"] + """\tfor (unsigned i = 0; i < vectorSize; i++)mask1[i] = i % 2 ? 1 : 0;\n""",
            "tpl_body_load" : "\t{{msk_type}} m1 = mipp::set_k<{{dt_ext}}>(mask1); {{reg_type}} r1 = mipp::set1<{{dt_ext}}>(1); {{reg_type}} r2 = mipp::set1<{{dt_ext}}>(2);",
            "tpl_body_loop_body" : "\t\t{{dt_ext}} res = mipp::get(m1,i) ? mipp::get(r1, i) : mipp::get(r2, i);",
            "tpl_body_loop_assert" : "\t\tREQUIRE(mipp::get(r3, i) == res);", 
            "tpl_body_operation" : "\t{{reg_type}} r3 = mipp::blend(r1, r2, m1);"
        },
        "obj" : {
            "tpl_func_declaration" : tpl_func_declaration["obj"], 
            "tpl_body_declaration" : tpl_body_declaration["cpp2args"] + """\nint32_t mask1[vectorSize] = {0};""", 
            "tpl_body_initialization" : tpl_body_init["2args"] + """\tfor (unsigned i = 0; i < vectorSize; i++)mask1[i] = i % 2 ? 1 : 0;\n""",
            "tpl_body_load" : "\t{{msk_type}} m1; m1.m = mipp::set_k<{{dt_ext}}>(mask1); {{reg_type}} r1; r1.r = mipp::set1<{{dt_ext}}>(1); {{reg_type}} r2; r2.r = mipp::set1<{{dt_ext}}>(2);",
            "tpl_body_loop_body" : "\t\t{{dt_ext}} res = mipp::get(m1.m,i) ? mipp::get(r1.r, i) : mipp::get(r2.r, i);",
            "tpl_body_loop_assert" : "\t\tREQUIRE(r3[i] == res);", 
            "tpl_body_operation" : "\t{{reg_type}} r3; r3.r = mipp::blend(r1.r, r2.r, m1.m);"
        }
    },
}

#float support of logical operators 
#is odd. Will come back to them later.
set_skip_float = {
    "andb",
    "orb",
    "xorb",
    "notb",
    "andnotb",
}

#contains necessary info to generate tests for a specific mipp function.
gen_test_dict = {
    
    #arithmetic functions
    
    "add" : {"template" : tpl_bodies["generic_for_loop"], 
             "long_name" : "Addition", "short_name" : "add",
             "op" : "+", 
             "protos" : prototype_registry["arith_2args"]
            },
             
    "sub" : {"template" : tpl_bodies["generic_for_loop"], 
             "long_name" : "Subtraction", "short_name" : "sub",
             "op" : "-",
             "protos" : prototype_registry["sub_2args"]
            },
    
    "mul" : {"template" : tpl_bodies["generic_for_loop"], 
             "long_name" : "Multiplication", "short_name" : "mul",
             "op" : "*",
             "protos" : prototype_registry["arith_2args"]
            },
    "div" : {"template" : tpl_bodies["generic_for_loop"], 
             "long_name" : "Division", "short_name" : "div",
             "op" : "/",
             "protos" : prototype_registry["arith_2args"]
            },
    "andb" : {"template" : tpl_bodies["generic_for_loop"], 
             "long_name" : "Bitwise And", "short_name" : "andb",
             "op" : "&",
             "protos" : prototype_registry["arith_2args"]
            },
    "orb" : {"template" : tpl_bodies["generic_for_loop"], 
             "long_name" : "Bitwise Or", "short_name" : "orb",
             "op" : "|",
             "protos" : prototype_registry["arith_2args"]
            },
    "xorb" : {"template" : tpl_bodies["generic_for_loop"], 
             "long_name" : "Bitwise Xor", "short_name" : "xorb",
             "op" : "^",
             "protos" : prototype_registry["arith_2args"]
            },

    
    # memory access functions
    "load" : {"template" : tpl_bodies["generic_for_loop"], 
             "long_name" : "Load", "short_name" : "load",
             "op" : "",
             "protos" : prototype_registry["load"]
            },
    "loadu" : {"template" : tpl_bodies["generic_for_loop"], 
             "long_name" : "Load Unaligned", "short_name" : "loadu",
             "op" : "",
             "protos" : prototype_registry["load"]
            },
    
    "store" : {"template" : tpl_bodies["generic_for_loop"],
             "long_name" : "Store", "short_name" : "store",
             "op" : "",
             "protos" : prototype_registry["store"]
    },
    
    "storeu" : {"template" : tpl_bodies["generic_for_loop"],
             "long_name" : "Store Unaligned", "short_name" : "storeu",
             "op" : "",
             "protos" : prototype_registry["store"]
    },
    
    "set" : {"template" : tpl_bodies["generic_for_loop"], 
             "long_name" : "Set", "short_name" : "set",
             "op" : "",
             "protos" : prototype_registry["set"]
    },
    
    "set_k" : {"template" : tpl_bodies["generic_for_loop"], 
             "long_name" : "Set Mask", "short_name" : "set_k",
             "op" : "",
             "protos" : prototype_registry["set_k"]
        
    },
    
    "set1" : {"template" : tpl_bodies["generic_for_loop"], 
             "long_name" : "Set to scalar", "short_name" : "set1",
             "op" : "",
             "protos" : prototype_registry["set1"]
    },
    
    "set1_k" : {"template" : tpl_bodies["generic_for_loop"], 
             "long_name" : "Set Mask to scalar", "short_name" : "set1_k",
             "op" : "",
             "protos" : prototype_registry["set1_k"]
    },
    
    "set0" : {"template" : tpl_bodies["generic_for_loop"], 
             "long_name" : "Set to zero", "short_name" : "set0",
             "op" : "",
             "protos" : prototype_registry["set0"]
    },
    
    "set0_k" : {"template" : tpl_bodies["generic_for_loop"],
                "long_name" : "Set Mask to zero", "short_name" : "set0_k",
                "op" : "",
                "protos" : prototype_registry["set0_k"]
    },
    
    "get" : {"template" : tpl_bodies["generic_for_loop"],
             "long_name" : "Get", "short_name" : "get",
             "op" : "",
             "protos" : prototype_registry["load"]
    },
    
    "getfirst" : {"template" : tpl_bodies["generic_for_loop"],
                  "long_name" : "Get First Lane", "short_name" : "getfirst",
                   "op" : "",
                   "protos" : prototype_registry["getfirst"]
    },
    
    "blend" : {"template" : tpl_bodies["generic_for_loop"],
             "long_name" : "Blend", "short_name" : "blend",
             "op" : "",
             "protos" : prototype_registry["blend"]
    },
    
    "andb_k" : {"template" : tpl_bodies["generic_for_loop"],
             "long_name" : "Bitwise And with Mask", "short_name" : "andb_k",
             "op" : "",
             "protos" : prototype_registry["set_k"]
    },
    #"orb_k" : {"template" : tpl_bodies["generic_for_loop"],
    #         "long_name" : "Bitwise Or with Mask", "short_name" : "orb_k",
    #         "op" : "",
    #         "protos" : prototype_registry["set_k"]
    #},
    
    #"get_k" : {}
}


