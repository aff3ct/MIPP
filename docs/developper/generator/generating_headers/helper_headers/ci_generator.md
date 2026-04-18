# ci_generator.py

`ci_generator.py` is the file that generates `mipp.h`. `mipp.h` is a fairly 
straightforward file. Depending on which architecture you use MIPP on, the MIPP 
symbols (functions and defines) will be mapped to the ones defined in the 
relevant `include/isa/mipp_impl_[isa]_gen.h` file. 

Examples:

```c title="Extracted from the 'include/avx/mipp_impl_avx_gen.h' generated file" 
#if defined(MIPP_AVX512)
#define MIPP_RVD_SIZE_BYTE MIPP_AVX512_RVD_SIZE_BYTE
#define MIPP_N_FLOAT64 MIPP_AVX512_N_FLOAT64
#define MIPP_N_FLOAT32 MIPP_AVX512_N_FLOAT32
#define MIPP_N_INT64 MIPP_AVX512_N_INT64
#define MIPP_N_INT32 MIPP_AVX512_N_INT32
#define MIPP_N_INT16 MIPP_AVX512_N_INT16
#define MIPP_N_INT8 MIPP_AVX512_N_INT8
#define MIPP_N_UINT64 MIPP_AVX512_N_UINT64
#define MIPP_N_UINT32 MIPP_AVX512_N_UINT32
#define MIPP_N_UINT16 MIPP_AVX512_N_UINT16
#define MIPP_N_UINT8 MIPP_AVX512_N_UINT8
#elif defined(MIPP_AVX)
#define MIPP_RVD_SIZE_BYTE MIPP_AVX_RVD_SIZE_BYTE
#define MIPP_N_FLOAT64 MIPP_AVX_N_FLOAT64
#define MIPP_N_FLOAT32 MIPP_AVX_N_FLOAT32
#define MIPP_N_INT64 MIPP_AVX_N_INT64
#define MIPP_N_INT32 MIPP_AVX_N_INT32
#define MIPP_N_INT16 MIPP_AVX_N_INT16
#define MIPP_N_INT8 MIPP_AVX_N_INT8
#define MIPP_N_UINT64 MIPP_AVX_N_UINT64
#define MIPP_N_UINT32 MIPP_AVX_N_UINT32
#define MIPP_N_UINT16 MIPP_AVX_N_UINT16
#define MIPP_N_UINT8 MIPP_AVX_N_UINT8
#elif defined(MIPP_SSE)
// and so on
```

```c
static inline rvd_float64_t mipp_add_float64(const rvd_float64_t r0, const rvd_float64_t r1) {
#if defined(MIPP_AVX512)
	return mipp_avx512_add_float64(r0, r1);
#elif defined(MIPP_AVX)
	return mipp_avx_add_float64(r0, r1);
#elif defined(MIPP_SSE)
	return mipp_sse_add_float64(r0, r1);
#elif defined(MIPP_RVV)
	return mipp_rvv_add_float64(r0, r1);
#elif defined(MIPP_NEON)
	return mipp_neon_add_float64(r0, r1);
#elif defined(MIPP_SVE_2048)
	return mipp_sve2048_add_float64(r0, r1);
#elif defined(MIPP_SVE_1024)
	return mipp_sve1024_add_float64(r0, r1);
#elif defined(MIPP_SVE_512)
	return mipp_sve512_add_float64(r0, r1);
#elif defined(MIPP_SVE_256)
	return mipp_sve256_add_float64(r0, r1);
#elif defined(MIPP_SVE_128)
	return mipp_sve128_add_float64(r0, r1);
#else
	printf("MIPP panic: '%s', unsupported case, this should never happen.\n", "mipp_add_float64");
	exit(-1);
#endif
}
```