import os
import sys
from jinja2 import Template, StrictUndefined

path = os.getcwd()
from tools import all_datatypes

sys.path.insert(1,path + '/../')


tpl_bodies = {
    "arithmetic_2args": """
\tconst int vectorSize = {{size}};
\t{{dt_ext}}_t inputs1[vectorSize],inputs2[vectorSize];
\tfor(int i = 0; i < vectorSize; i++)
\t{
\t\t//todo : randomize inputs or smth
\t\tinputs1[i] = 2;
\t\tinputs2[i] = 1;
\t}

\t{{reg_type}} r1 = mipp_load_{{dt_ext}}(inputs1);
\t{{reg_type}} r2 = mipp_load_{{dt_ext}}(inputs2);
\t{{reg_type}} r3 = mipp_{{func}}_{{dt_ext}}(r1, r2);

\tfor (int i = 0; i < vectorSize; i++)
\t{
\t\t{{dt_ext}}_t res = inputs1[i] {{op}}  inputs2[i];
\t\tREQUIRE(mipp_get_{{dt_ext}}(r3, i) == res);
\t}    
""",
    "arithmetic_3args": """\t\t//TODO: generate test body for arithmetic 3 args\n""",
    "logical_2args": """\t\t//TODO: generate test body for logical 2 args\n""",
    "logical_3args": """\t\t//TODO: generate test body for logical 3 args\n""",
    "comparison_2args": """\t\t//TODO: generate test body for comparison 2 args\n""",
    "comparison_3args": """\t\t//TODO: generate test body for comparison 3 args\n""",
    "load": """\t\t//TODO: generate test body for load\n""",
    "store": """\t\t//TODO: generate test body for store\n""",
}

gen_test_dict = {
    "add" : {"template" : tpl_bodies["arithmetic_2args"], "long_name" : "Addition", "short_name" : "add", "op" : "+"},
    "sub" : {"template" : tpl_bodies["arithmetic_2args"], "long_name" : "Subtraction", "short_name" : "sub", "op" : "-"},
    "mul" : {"template" : tpl_bodies["arithmetic_2args"], "long_name" : "Multiplication", "short_name" : "mul", "op" : "*"},
    "div" : {"template" : tpl_bodies["arithmetic_2args"], "long_name" : "Division", "short_name" : "div", "op" : "/"},
}

