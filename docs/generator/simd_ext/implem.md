# TITLE?

`implem_isa.py` must define three dictionnaries. 

- `isa` : general informations about the extension, it's name, architecture, 
  what guard to check if it's defined, and informations about the naming
  conventions of it's intrinsics and datatypes. These informations are used in 
  templated calls to the intrinsics, variable declarations and so on. 
- `tpl_implem_isa` : a dictionnary where the values are templated code snippets 
  used in `implems_isa`. These code snippets, once "specialized" will be the 
  bodies of the MIPP functions in `include/isa/mipp_impl_isa_gen.h`.
- `implems_isa` : a dictionnary where each key is a MIPP function, and the value 
  is a list of dictionnary. Each dictionnary contains a template in 
  `tpl_implem_isa` and a list of datatypes. This is used in `gen_c_funcs` to 
  generate a C function for each datatype the MIPP function is defined for. The 
  dictionnary can also contain an `"if"` key. It's used to add a guard when the 
  function uses intrinsics that are defined is "sub-isas". For instance, 
  the `__m256d _mm256_fmadd_pd (__m256d a, __m256d b, __m256d c)` intrinsic, 
  used for the MIPP `fmadd` function in `implem_avx.py` will exist only if the 
  architecture supports AVX2+FMA.