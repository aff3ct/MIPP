# c_generator : 

The `c_generator.py` file contains four functions. 

- `gen_c_defines(isa, file)`
- `gen_c_structures(isa, file)`
- `gen_c_functions(isa, file, funcs, implems)`
- `gen_c_missing_functions(isa, file, funcs)`

## gen_c_defines :

Is the function that generates every relevant C "define" (i.e `#define foo_bar_baz`) for a given ISA and writes them 
in the file passed as argument. The function is called to generate the `#define` at the beginning of each `include/isa/mipp_impl_isa.h`. 

It's mainly used to define the number of elements in each type of register and the size (in byte and bits) of the vectors for a given 
ISA.

It is called by `gen_c_functions`.


## gen_c_structures : 

Is the function that generates the `struct rvd_isa_type_t` used in each `include/isa/mipp_impl_isa.h`. These struct all 
contain a single field called `r` for vector registers and `m` for mask registers. 

This field is used to "encapsulate" the vector / mask types defined by the intrinsics header of each ISA.

This allows the templates in each 
`simd_ext/isa/implem_*.py` and `helper_headers/generic_emu.py` to be generic. For instance the snippet : 

`%r<tp>% out;`
`out.r = {{isa.prefix}}_vle{{isa_dt_par.width}}_v_{{isa_dt_par.data_ext}}(({{ isa_dt_par.to_ptr }}*)p0, %N<tp>%);`
*taken from the loadu template, in simd_ext/implem_emu_rvv.py*

Will be valid in RVV when it is specialized whatever the type of `%r<tp>%` is resolved to because we know that 
it will be a struct with a field called `r`.

## gen_c_functions : 

Is the most important function of the file. Given an ISA, a dictionnary of functions that **should** be implemented (funcs) and the functions an ISA 
**actually** implements (implems), it generates a C function for each "function/datatype" pair. To generate those functions, it uses the body 
templates in `implem`. If there is an `"if"` field in `implem` for a "function/datatype" pair, `gen_c_functions` will generate a guard for the function
(see example).

Let's take the "add" mipp function in AVX : 


This is the template used by `add` in AVX : 
`"arith_2args":    { "format": "short", "code": "{{ isa.prefix }}_{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r);" }`


Using it, and the informations in `isa_avx` to resolve the templates, it will generate those functions : 

<code>
<br/>static inline rvd_avx_float64_t mipp_avx_add_float64(const rvd_avx_float64_t r0, const rvd_avx_float64_t r1) {
<br/>	rvd_avx_float64_t res;
<br/>	res.r = _mm256_add_pd(r0.r, r1.r);
<br/>	return res;
<br/>}
<br/>static inline rvd_avx_float32_t mipp_avx_add_float32(const rvd_avx_float32_t r0, const rvd_avx_float32_t r1) {
<br/>	rvd_avx_float32_t res;
<br/>	res.r = _mm256_add_ps(r0.r, r1.r);
<br/>	return res;
<br/>}
<br/>#if defined(__AVX2__)
<br/>static inline rvd_avx_int64_t mipp_avx_add_int64(const rvd_avx_int64_t r0, const rvd_avx_int64_t r1) {
<br/>	rvd_avx_int64_t res;
<br/>	res.r = _mm256_add_epi64(r0.r, r1.r);
<br/>	return res;
<br/>}
<br/>#endif
</code>

and writes them in `file`. The function (or a variant of it) is called twice in each `simd_ext/gen_isa.py` file, once with the `implems_isa` dictionnary, 
and once with the `implems_emu_isa` dictionnary.

N.B : mipp add is defined for more datatypes this is just an example.


The functions generated for each ISA will be used in `mipp.h` to create the generic MIPP interface like so :

<code>
<br/>static inline rvd_float64_t mipp_add_float64(const rvd_float64_t r0, const rvd_float64_t r1) {
<br/>#if defined(MIPP_AVX512)
<br/>	return mipp_avx512_add_float64(r0, r1);
<br/>#elif defined(MIPP_AVX)
<br/>	return mipp_avx_add_float64(r0, r1);
<br/>#elif defined(MIPP_SSE)
<br/>	return mipp_sse_add_float64(r0, r1);
<br/>#elif defined(MIPP_RVV)
<br/>	return mipp_rvv_add_float64(r0, r1);
<br/>#elif defined(MIPP_NEON)
<br/>	return mipp_neon_add_float64(r0, r1);
<br/>#elif defined(MIPP_SVE_2048)
<br/>	return mipp_sve2048_add_float64(r0, r1);
<br/>#elif defined(MIPP_SVE_1024)
<br/>	return mipp_sve1024_add_float64(r0, r1);
<br/>#elif defined(MIPP_SVE_512)
<br/>	return mipp_sve512_add_float64(r0, r1);
<br/>#elif defined(MIPP_SVE_256)
<br/>	return mipp_sve256_add_float64(r0, r1);
<br/>#elif defined(MIPP_SVE_128)
<br/>	return mipp_sve128_add_float64(r0, r1);
<br/>#else
<br/>	printf("MIPP panic: '%s', unsupported case, this should never happen.\n", "mipp_add_float64");
<br/>	exit(-1);
<br/>#endif
}
</code>

## gen_c_missing_functions :

`gen_c_missing_functions` generates the functions that **should** be supported by an ISA but are in **neither**  `simd_ext/isa/implem_*.py` or `helper_headers/generic_emu.py`.
The body of those functions are simple template that print out an error message and `exits(-1)` when called.
This is done so that every ISA can be easily "linked" in mipp.h, even if the ISA does not support a specific function.

TODO : link to explanation of isa