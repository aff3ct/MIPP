import os
import sys
from jinja2 import Template, StrictUndefined

path = os.getcwd()
from tools import all_datatypes

sys.path.insert(1,path + '/../')


tpl_bodies = {
    "arithmetic_2args": """
\tconst int vectorSize = {{size}};
\tint32_t inputs1[vectorSize],inputs2[vectorSize];
\tfor(int i = 0; i < vectorSize; i++)
\t{
\t\t//todo : randomize inputs or smth
\t\tinputs1[i] = 1;
\t\tinputs2[i] = 2;
\t}

\t{{reg_type}} r1 = mipp_load_{{dt_ext}}(inputs1);
\t{{reg_type}} r2 = mipp_load_{{dt_ext}}(inputs2);
\t{{reg_type}} r3 = mipp_{{func}}_{{dt_ext}}(r1, r2);

\tfor (int i = 0; i < vectorSize; i++)
\t{
\t\t{{dt_ext}}_t res = inputs1[i] + inputs2[i];
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

bodies_dict = {
    "add" : tpl_bodies["arithmetic_2args"],
    "sub" : tpl_bodies["arithmetic_2args"],
    "mul" : tpl_bodies["arithmetic_2args"],
    "div" : tpl_bodies["arithmetic_2args"],
    
    "and" : tpl_bodies["logical_2args"],
    "or" : tpl_bodies["logical_2args"],
    "xor" : tpl_bodies["logical_2args"],
    "not" : tpl_bodies["logical_2args"],
}

types_dict = {}
for type in all_datatypes:
    types_dict[type] = type + "mipp_t"