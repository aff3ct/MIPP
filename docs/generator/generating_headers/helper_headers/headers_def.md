`headers_def.py` contains three dictionnaries : 

- `protos`
- `mipp_funcs_concepts`
- `mipp_funcs`

These three dictionnaries are very important to how MIPP is generated.

## protos 

Contains generic prototypes that are used to create mipp functions in the different layers. 

For instance : 

<code>
<br/>"ret_reg_2args_reg": {
<br/>		"ret" :
<br/>			{"type": "reg", "charac": "WO", "fixeddatatype": False},
<br/>		"args" : [
<br/>			{"type": "reg", "charac": "RO", "fixeddatatype": False},
<br/>			{"type": "reg", "charac": "RO", "fixeddatatype": False},
<br/>		]
<br/>	},
</code>

Is a prototype used by every MIPP functions that takes two SIMD registers as argument and that returns a register. 

### values for each field

#### "type"

- msk  : mask register (rvm)
- reg  : value register (rvd)
- Nele : array of scalars (N elements)
- val  : scalar value
- ptr  : pointer

#### "charac"

- WO : write only 
- RO : read only

#### "fixeddatatype"

- False : datatype of the return value / argument is not fixed 
- any type in `helper_headers/tools.py` : datatype of the argument / return can only be of this type.

### mipp_func_concepts

is a dictionnary where keys are concepts like "all_arithm_op, all_loads" that correspond to a "category" of MIPP functions, and 
values are a list of MIPP function that belong to this category. 

N.B : a MIPP function can be in at most one category. If it isn't in any category in `mipp_func_concepts`, it will generaly 
be put in a default "miscellaneous" category.

### mipp_funcs 

Is the most important dictionnary defined in this file. It can be seen as the MIPP specification. It's keys are MIPP function names. It's values 
are dictionnary that defines how these functions *should* be defined. 

For instance :

`"add":     { "proto": protos["ret_reg_2args_reg"           ], "datatypes": all_datatypes          , "horizontal": False , "mask" : all_mask_support} ,`


Tells that the mipp `add` function should have the `"ret_reg_2args_reg"` prototype. i.e take two `rvd` as argument and return one `rvd`. It should be defined 
on every datatypes. It is not a reduction. And it supports every kind of mask variants. 

This "specification" is used by `gen_c_funcs`, `gen_ci_funcs`, `gen_cpp_funcs` etc to generate coherent MIPP prototypes for every layer of MIPP.