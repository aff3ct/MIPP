# How it Works

`common.py` defines utility functions to generate tests SHAPES as well as the 
TemplateParts class.

The attributes of the TemplateParts class are strings. These strings are 
templates used to generate a test file. Each string is a fragment of the test, 
i.e the declaration of the function, the declaration of the variable in the 
function, the initialisation of these variables etc.


Each SHAPE defined in `common.py` corresponds to a prototype in 
`headers_def.py`. Each `layer_X.py` file defines a dictionnary that matches 
(some of) the SHAPES in `common.py` to TemplateParts.

This dictionnary makes it possible to generate a generic test for each function 
whose prototype corresponds to a shape. 

!!! tips
    The prototype "ret_reg_2args_reg" used by add, div, mul, sub, andb,... is 
    matched with the shape `SHAPE_RET_REG_2ARGS_REG`. In the `shape_templates` 
    dictionnary defined in each layer, the SHAPE_RET_REG_2ARGS_REG key is 
    associated with a TemplateParts object.

```Python title="Extracted from the 'generator/helper_tests/layer_c.py' file"
SHAPE_RET_REG_2ARGS_REG: TemplateParts(
    func_decl=FUNC_DECL,
    decl=DECL_2ARGS,
    init=INIT_2ARGS,
    load=LOAD_2ARGS_REG,
    operation=OP_REG_BINOP,
    loop_body=LB_REG_BINOP,
    loop_assert=AS_REG_BINOP,
)
```

Each attribute of the TemplateParts is a snippet of templated code. For 
instance:

```Python
FUNC_DECL = """void test_cmipp_{{func}}_{{dt_ext}}(){"""
DECL_2ARGS = """\tconst int vectorSize = {{size}};\n\t{{dt_ext}}_t inputs1[vectorSize],inputs2[vectorSize];"""
```

This makes it possible to create generic templates for the different functions 
that share the same prototype. In some cases, you might want to change a field 
of TemplateParts for a specific function. 

In order to handle this, each `layer_X.py` file defines a `LAYER_OVERRIDES` 
dictionnary. It's keys are MIPP function names. (i.e "andnb", "sub",...). It's 
values are dictionnaries where the keys are TemplateParts field names 
("func_decl", "decl",...) and it's values are the templated code that this field 
should be for this specific function's test. 

Example: 

```Python
"hadd": {
        "loop_body": """\t{{dt_ext}}_t res = 0; uint64_t ures = 0;
\tfor(int j = 0; j < vectorSize; j++){
\t\tres {{op}} inputs1[j];
\t\tures{{op}} inputs1[j];
\t}""",
        "loop_assert": """\tif(ures == (uint64_t)res) REQUIRE(mipp_get\_\{\{dt_ext\}\}(r3, 0) == res);""",
}
```

This makes it possible to easily change the TemplateParts (thus it's generated 
test file) of a function sharing a SHAPE with other functions without impacting 
the other functions.
