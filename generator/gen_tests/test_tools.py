import os
import sys
from jinja2 import Template, StrictUndefined

path = os.getcwd()
from tools import all_datatypes

sys.path.insert(1,path + '/../')

#this file contains templates for generating test functions, 
#the philosophy is to have very small template for each past of the 
#test function declaration. In order to have a lot of genericity 

#there is also a huge dict w template info
#but that dict might be split at some point 


#template for the function declaration
#e.g. void test_cmipp_add_i8() or template <typename T> void test_cppmipp_add()
tpl_func_declaration = {
    "c_operator_2args": """void test_cmipp_{{func}}_{{dt_ext}}(){""",
    "cpp_operator_2args": """template <typename T>\nvoid test_cppmipp_{{func}}(){""",
    "obj_operator_2args": """template <typename T>\nvoid test_objmipp_{{func}}(){""",
}

#template for the variable declaration and initialization
#e.g. defining the input arrays
tpl_body_declaration = {
    "c1arg": """\tconst int vectorSize = {{size}}; {{dt_ext}}_t inputs[vectorSize];""",
    "c2args": """\tconst int vectorSize = {{size}};\n\t{{dt_ext}}_t inputs1[vectorSize],inputs2[vectorSize];""",
    "cpp2args": """\tconst int vectorSize = mipp::N<T>(); T inputs1[vectorSize],inputs2[vectorSize];""",
    "cpp3args": """\tT inputs1[vectorSize],inputs2[vectorSize],inputs3[vectorSize];""",
}

#template for the initialization of the input arrays
#e.g. filling them with some values
tpl_body_init = {
    "1arg": """\tfor(int i = 0; i < vectorSize; i++)
\t{
\t\t//todo : randomize inputs or smth
\t\tinputs[i] = 2;
\t}""",
    "2args": """\tfor(int i = 0; i < vectorSize; i++)
\t{
\t\t//todo : randomize inputs or smth
\t\tinputs1[i] = 2;
\t\tinputs2[i] = 1;
\t}""",
}

#template for loading the input arrays into mipp registers
tpl_body_load = {
    "c1arg": """\t{{reg_type}} r1 = mipp_load_{{dt_ext}}(inputs);""",
    
    "c2args": """\t{{reg_type}} r1 = mipp_load_{{dt_ext}}(inputs1);
\t{{reg_type}} r2 = mipp_load_{{dt_ext}}(inputs2);""",

    "c3args": """\t{{reg_type}} r1 = mipp_load_{{dt_ext}}(inputs1);
\t{{reg_type}} r2 = mipp_load_{{dt_ext}}(inputs2);
\t{{reg_type}} r3 = mipp_load_{{dt_ext}}(inputs3);""",

    "cpp2args": """\t{{reg_type}} r1 = mipp::load<{{dt_ext}}>(inputs1), r2 = mipp::load<{{dt_ext}}>(inputs2);""",
    
    "obj2args":
"""\t//{{reg_type}} r1(inputs1), r2(inputs2);//waiting for load to be fixed in obj layer
\t{{reg_type}} r1, r2; r1.r = mipp::load<T>(inputs1); r2.r = mipp::load<T>(inputs2);""",

}

#template for the operation on the registers
#e.g. r3 = r1 + r2 or r3 = mipp::add(r1, r2)
tpl_body_operation = {
    "c_operator_2args": """\t{{reg_type}} r3 = mipp_{{func}}_{{dt_ext}}(r1, r2);""",
    "cpp_operator_2args": """\t{{reg_type}} r3 = mipp::{{func}}(r1, r2);""",
    "obj_operator_2args": """\t{{reg_type}} r3 = r1 {{op}} r2;""",
}

#template for the body of the loop that performs the op on the scalar inputs
#TODO : some asserts don't use loop think about it @ some point
tpl_body_loop_body = {
    "c_operator_2args": """\t\t{{dt_ext}}_t res = inputs1[i] {{op}}  inputs2[i];""",
    "cpp_operator_2args": """\t\tT res = inputs1[i] {{op}}  inputs2[i];""",
    "fn_call_2args": """\t\t{{dt_ext}}_t res = {{func}}(inputs1[i], inputs2[i]);""",
    "operator_1arg": """\t\t{{dt_ext}}_t res = {{op}} inputs[i];""",
    "fn_call_1arg": """\t\t{{dt_ext}}_t res = {{func}}(inputs[i]);""",
}

#template for the body of the loop that performs the assertion
#TODO : some asserts don't use loop think about it @ some point
tpl_body_loop_assert = {
    "c_operator_2args": """\t\tREQUIRE(mipp_get_{{dt_ext}}(r3, i) == res);""",
    "cpp_operator_2args": """\t\tREQUIRE(mipp::get(r3, i) == res);""",
    "obj_operator_2args": """\t\tREQUIRE(r3[i] == res);""",
    "mask_2args": """\t\tif(res) REQUIRE(mipp_get_{{dt_ext}}(r3, i) != 0); else REQUIRE(mipp_get_{{dt_ext}}(r3, i) == 0);""",
}


#"high level" template for the whole test
#when rendered, creates a "specialized" template 
#that is rendered again with the specific func, datatype, op, etc to create the final test function body
tpl_bodies = {
    "arithmetic_2args": 
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

    "arithmetic_3args": """\t\t//TODO: generate test body for arithmetic 3 args\n""",
    "logical_2args": """\t\t//TODO: generate test body for logical 2 args\n""",
    "logical_3args": """\t\t//TODO: generate test body for logical 3 args\n""",
    "comparison_2args": """\t\t//TODO: generate test body for comparison 2 args\n""",
    "comparison_3args": """\t\t//TODO: generate test body for comparison 3 args\n""",
    "load": """\t\t//TODO: generate test body for load\n""",
    "store": """\t\t//TODO: generate test body for store\n""",
}


#used to store "common" template patterns. 
#for instance, arith_2args is a valid 
#pattern for all arithmetic/logical operators with 2 args.
prototype_registry = {
    "arith_2args" : {
            "c": {
                    "tpl_func_declaration" : tpl_func_declaration["c_operator_2args"], 
                    "tpl_body_declaration" : tpl_body_declaration["c2args"], 
                    "tpl_body_initialization" : tpl_body_init["2args"], 
                    "tpl_body_load" : tpl_body_load["c2args"], 
                    "tpl_body_loop_body" : tpl_body_loop_body["c_operator_2args"], 
                    "tpl_body_loop_assert" : tpl_body_loop_assert["c_operator_2args"], 
                    "tpl_body_operation" : tpl_body_operation["c_operator_2args"]},
            "cpp": {
                    "tpl_func_declaration" : tpl_func_declaration["cpp_operator_2args"], 
                    "tpl_body_declaration" : tpl_body_declaration["cpp2args"], 
                    "tpl_body_initialization" : tpl_body_init["2args"], 
                    "tpl_body_load" : tpl_body_load["cpp2args"], 
                    "tpl_body_loop_body" : tpl_body_loop_body["cpp_operator_2args"], 
                    "tpl_body_loop_assert" : tpl_body_loop_assert["cpp_operator_2args"], 
                    "tpl_body_operation" : tpl_body_operation["cpp_operator_2args"]},
             "obj": {
             
                    "tpl_func_declaration" : tpl_func_declaration["obj_operator_2args"], 
                    "tpl_body_declaration" : tpl_body_declaration["cpp2args"], 
                    "tpl_body_initialization" : tpl_body_init["2args"], 
                    "tpl_body_load" : tpl_body_load["obj2args"], 
                    "tpl_body_loop_body" : tpl_body_loop_body["cpp_operator_2args"], 
                    "tpl_body_loop_assert" : tpl_body_loop_assert["obj_operator_2args"], 
                    "tpl_body_operation" : tpl_body_operation["obj_operator_2args"]}

    },
}


#contains necessary info to generate tests for a specific mipp function.
gen_test_dict = {
    "add" : {"template" : tpl_bodies["arithmetic_2args"], 
             "long_name" : "Addition", "short_name" : "add",
             "op" : "+", 
             "protos" : prototype_registry["arith_2args"]
            },
             
    "sub" : {"template" : tpl_bodies["arithmetic_2args"], 
             "long_name" : "Subtraction", "short_name" : "sub",
             "op" : "-",
             "protos" : prototype_registry["arith_2args"]
            },
    
    "mul" : {"template" : tpl_bodies["arithmetic_2args"], 
             "long_name" : "Multiplication", "short_name" : "mul",
             "op" : "*",
             "protos" : prototype_registry["arith_2args"]
            },
    "div" : {"template" : tpl_bodies["arithmetic_2args"], 
             "long_name" : "Division", "short_name" : "div",
             "op" : "/",
             "protos" : prototype_registry["arith_2args"]
            },
}


