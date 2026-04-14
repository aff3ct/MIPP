# ci_generator

`ci_generator.py` is the file that generates `mipp.h`. `mipp.h` is a fairly straightforward file. Depending 
on which architecture you use MIPP on, the MIPP symbols (functions and defines) will be mapped to the ones defined in the relevant 

`include/isa/mipp_impl_isa_gen.h`. 

Examples : 

<code>
<br/>#if defined(MIPP_AVX512)
<br/>#define MIPP_RVD_SIZE_BYTE MIPP_AVX512_RVD_SIZE_BYTE
<br/>#define MIPP_N_FLOAT64 MIPP_AVX512_N_FLOAT64
<br/>#define MIPP_N_FLOAT32 MIPP_AVX512_N_FLOAT32
<br/>#define MIPP_N_INT64 MIPP_AVX512_N_INT64
<br/>#define MIPP_N_INT32 MIPP_AVX512_N_INT32
<br/>#define MIPP_N_INT16 MIPP_AVX512_N_INT16
<br/>#define MIPP_N_INT8 MIPP_AVX512_N_INT8
<br/>#define MIPP_N_UINT64 MIPP_AVX512_N_UINT64
<br/>#define MIPP_N_UINT32 MIPP_AVX512_N_UINT32
<br/>#define MIPP_N_UINT16 MIPP_AVX512_N_UINT16
<br/>#define MIPP_N_UINT8 MIPP_AVX512_N_UINT8
<br/>#elif defined(MIPP_AVX)
<br/>#define MIPP_RVD_SIZE_BYTE MIPP_AVX_RVD_SIZE_BYTE
<br/>#define MIPP_N_FLOAT64 MIPP_AVX_N_FLOAT64
<br/>#define MIPP_N_FLOAT32 MIPP_AVX_N_FLOAT32
<br/>#define MIPP_N_INT64 MIPP_AVX_N_INT64
<br/>#define MIPP_N_INT32 MIPP_AVX_N_INT32
<br/>#define MIPP_N_INT16 MIPP_AVX_N_INT16
<br/>#define MIPP_N_INT8 MIPP_AVX_N_INT8
<br/>#define MIPP_N_UINT64 MIPP_AVX_N_UINT64
<br/>#define MIPP_N_UINT32 MIPP_AVX_N_UINT32
<br/>#define MIPP_N_UINT16 MIPP_AVX_N_UINT16
<br/>#define MIPP_N_UINT8 MIPP_AVX_N_UINT8
<br/>#elif defined(MIPP_SSE)
<br>//etc
</code>

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