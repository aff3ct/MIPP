#include "mipp.h"

// -------------------------------------------------------------------------------------------------------- X86 AVX-512
// --------------------------------------------------------------------------------------------------------------------
#if defined(__MIC__) || defined(__KNCNI__) || defined(__AVX512__) || defined(__AVX512F__)

	// ---------------------------------------------------------------------------------------------------------- blend
	template <>
	inline reg blend<double>(const reg v1, const reg v2, const msk m) {
		return _mm512_castpd_ps(_mm512_mask_blend_pd((__mmask8)m, _mm512_castps_pd(v2), _mm512_castps_pd(v1)));
	}

	template <>
	inline reg blend<float>(const reg v1, const reg v2, const msk m) {
		return _mm512_mask_blend_ps((__mmask16)m, v2, v1);
	}

	template <>
	inline reg blend<int64_t>(const reg v1, const reg v2, const msk m) {
		return _mm512_castsi512_ps(_mm512_mask_blend_epi64((__mmask8)m, _mm512_castps_si512(v2), _mm512_castps_si512(v1)));
	}


	template <>
	inline reg blend<int32_t>(const reg v1, const reg v2, const msk m) {
		return _mm512_castsi512_ps(_mm512_mask_blend_epi32((__mmask16)m, _mm512_castps_si512(v2), _mm512_castps_si512(v1)));
	}

#if defined(__AVX512BW__)
	template <>
	inline reg blend<int16_t>(const reg v1, const reg v2, const msk m) {
		return _mm512_castsi512_ps(_mm512_mask_blend_epi16((__mmask32)m, _mm512_castps_si512(v2), _mm512_castps_si512(v1)));
	}

	template <>
	inline reg blend<int8_t>(const reg v1, const reg v2, const msk m) {
		return _mm512_castsi512_ps(_mm512_mask_blend_epi8((__mmask64)m, _mm512_castps_si512(v2), _mm512_castps_si512(v1)));
	}
#endif


	// ---------------------------------------------------------------------------------------------------------- loadu
#if defined(__AVX512F__)
	template <>
	inline reg loadu<float>(const float *mem_addr) {
		return _mm512_loadu_ps(mem_addr);
	}

	template <>
	inline reg loadu<double>(const double *mem_addr) {
		return _mm512_castpd_ps(_mm512_loadu_pd(mem_addr));
	}

	template <>
	inline reg loadu<int64_t>(const int64_t *mem_addr) {
		return _mm512_loadu_ps((const float*) mem_addr);
	}

	template <>
	inline reg loadu<int32_t>(const int32_t *mem_addr) {
		return _mm512_loadu_ps((const float*) mem_addr);
	}

	template <>
	inline reg loadu<int16_t>(const int16_t *mem_addr) {
		return _mm512_loadu_ps((const float*) mem_addr);
	}

	template <>
	inline reg loadu<int8_t>(const int8_t *mem_addr) {
		return _mm512_loadu_ps((const float*) mem_addr);
	}

#if defined(__AVX__)
	template <>
	inline reg_2 loadu_2<int32_t>(const int32_t *mem_addr) {
		return _mm256_loadu_ps((const float*) mem_addr);
	}
#endif

#endif

	// ----------------------------------------------------------------------------------------------------------- load
#ifdef MIPP_ALIGNED_LOADS
	template <>
	inline reg load<float>(const float *mem_addr) {
		return _mm512_load_ps(mem_addr);
	}

	template <>
	inline reg load<double>(const double *mem_addr) {
		return _mm512_castpd_ps(_mm512_load_pd(mem_addr));
	}

	template <>
	inline reg load<int64_t>(const int64_t *mem_addr) {
		return _mm512_load_ps((const float*) mem_addr);
	}

	template <>
	inline reg load<int32_t>(const int32_t *mem_addr) {
		return _mm512_load_ps((const float*) mem_addr);
	}

	template <>
	inline reg load<int16_t>(const int16_t *mem_addr) {
		return _mm512_load_ps((const float*) mem_addr);
	}

	template <>
	inline reg load<int8_t>(const int8_t *mem_addr) {
		return _mm512_load_ps((const float*) mem_addr);
	}

#if defined(__AVX__)
	template <>
	inline reg_2 load_2<int32_t>(const int32_t *mem_addr) {
		return _mm256_load_ps((const float*) mem_addr);
	}
#endif
#else
	template <>
	inline reg load<float>(const float *mem_addr) {
		return mipp::loadu<float>(mem_addr);
	}

	template <>
	inline reg load<double>(const double *mem_addr) {
		return mipp::loadu<double>(mem_addr);
	}

	template <>
	inline reg load<int64_t>(const int64_t *mem_addr) {
		return mipp::loadu<int64_t>(mem_addr);
	}

	template <>
	inline reg load<int32_t>(const int32_t *mem_addr) {
		return mipp::loadu<int32_t>(mem_addr);
	}

	template <>
	inline reg load<int16_t>(const int16_t *mem_addr) {
		return mipp::loadu<int16_t>(mem_addr);
	}

	template <>
	inline reg load<int8_t>(const int8_t *mem_addr) {
		return mipp::loadu<int8_t>(mem_addr);
	}

	template <>
	inline reg_2 load_2<int32_t>(const int32_t *mem_addr) {
		return mipp::loadu_2<int32_t>(mem_addr);
	}
#endif

	// --------------------------------------------------------------------------------------------------------- storeu
#if defined(__AVX512F__)
	template <>
	inline void storeu<float>(float *mem_addr, const reg v) {
		_mm512_storeu_ps(mem_addr, v);
	}

	template <>
	inline void storeu<double>(double *mem_addr, const reg v) {
		_mm512_storeu_pd(mem_addr, _mm512_castps_pd(v));
	}

	template <>
	inline void storeu<int64_t>(int64_t *mem_addr, const reg v) {
		_mm512_storeu_ps((float *)mem_addr, v);
	}

	template <>
	inline void storeu<int32_t>(int32_t *mem_addr, const reg v) {
		_mm512_storeu_ps((float *)mem_addr, v);
	}

	template <>
	inline void storeu<int16_t>(int16_t *mem_addr, const reg v) {
		_mm512_storeu_ps((float *)mem_addr, v);
	}

	template <>
	inline void storeu<int8_t>(int8_t *mem_addr, const reg v) {
		_mm512_storeu_ps((float *)mem_addr, v);
	}
#endif

	// ---------------------------------------------------------------------------------------------------------- store
#ifdef MIPP_ALIGNED_LOADS
	template <>
	inline void store<float>(float *mem_addr, const reg v) {
		_mm512_store_ps(mem_addr, v);
	}

	template <>
	inline void store<double>(double *mem_addr, const reg v) {
		_mm512_store_pd(mem_addr, _mm512_castps_pd(v));
	}

	template <>
	inline void store<int64_t>(int64_t *mem_addr, const reg v) {
		_mm512_store_ps((float *)mem_addr, v);
	}

	template <>
	inline void store<int32_t>(int32_t *mem_addr, const reg v) {
		_mm512_store_ps((float *)mem_addr, v);
	}

	template <>
	inline void store<int16_t>(int16_t *mem_addr, const reg v) {
		_mm512_store_ps((float *)mem_addr, v);
	}

	template <>
	inline void store<int8_t>(int8_t *mem_addr, const reg v) {
		_mm512_store_ps((float *)mem_addr, v);
	}
#else
	template <>
	inline void store<float>(float *mem_addr, const reg v) {
		mipp::storeu<float>(mem_addr, v);
	}

	template <>
	inline void store<double>(double *mem_addr, const reg v) {
		mipp::storeu<double>(mem_addr, v);
	}

	template <>
	inline void store<int64_t>(int64_t *mem_addr, const reg v) {
		mipp::storeu<int64_t>(mem_addr, v);
	}

	template <>
	inline void store<int32_t>(int32_t *mem_addr, const reg v) {
		mipp::storeu<int32_t>(mem_addr, v);
	}

	template <>
	inline void store<int16_t>(int16_t *mem_addr, const reg v) {
		mipp::storeu<int16_t>(mem_addr, v);
	}

	template <>
	inline void store<int8_t>(int8_t *mem_addr, const reg v) {
		mipp::storeu<int8_t>(mem_addr, v);
	}
#endif

	// --------------------------------------------------------------------------------------------------------- gather
#if defined(__AVX512F__)
	template <>
	inline reg gather<double,int64_t>(const double *mem_addr, const reg idx) {
		return _mm512_castpd_ps(_mm512_i64gather_pd(_mm512_castps_si512(idx),mem_addr,8));
	}

	template <>
	inline reg gather<float,int32_t>(const float *mem_addr, const reg idx) {
		return _mm512_i32gather_ps(_mm512_castps_si512(idx),mem_addr,4);
	}

	template <>
	inline reg gather<int64_t,int64_t>(const int64_t *mem_addr, const reg idx) {
		return _mm512_castsi512_ps(_mm512_i64gather_epi64(_mm512_castps_si512(idx),mem_addr,8));
	}

	template <>
	inline reg gather<int32_t,int32_t>(const int32_t *mem_addr, const reg idx) {
		return _mm512_castsi512_ps(_mm512_i32gather_epi32(_mm512_castps_si512(idx),mem_addr,4));
	}
#else
	template <>
	inline reg gather<double,int64_t>(const double *mem_addr, const reg idx) {
		return gather_seq<double,int64_t>(mem_addr, idx);
	}

	template <>
	inline reg gather<float,int32_t>(const float *mem_addr, const reg idx) {
		return gather_seq<float,int32_t>(mem_addr, idx);
	}

	template <>
	inline reg gather<int64_t,int64_t>(const int64_t *mem_addr, const reg idx) {
		return gather_seq<int64_t,int64_t>(mem_addr, idx);
	}

	template <>
	inline reg gather<int32_t,int32_t>(const int32_t *mem_addr, const reg idx) {
		return gather_seq<int32_t,int32_t>(mem_addr, idx);
	}
#endif
	template <>
	inline reg gather<int16_t,int16_t>(const int16_t *mem_addr, const reg idx) {
		return gather_seq<int16_t,int16_t>(mem_addr, idx);
	}

	template <>
	inline reg gather<int8_t,int8_t>(const int8_t *mem_addr, const reg idx) {
		return gather_seq<int8_t,int8_t>(mem_addr, idx);
	}

	// -------------------------------------------------------------------------------------------------- masked gather
#if defined(__AVX512F__)
	template <>
	inline reg maskzgat<double,int64_t>(const msk m, const double *mem_addr, const reg idx) {
		return _mm512_castpd_ps(_mm512_mask_i64gather_pd(_mm512_setzero_pd(),(__mmask8)m,_mm512_castps_si512(idx),mem_addr,8));
	}

	template <>
	inline reg maskzgat<float,int32_t>(const msk m, const float *mem_addr, const reg idx) {
		return _mm512_mask_i32gather_ps(_mm512_setzero_ps(),(__mmask16)m,_mm512_castps_si512(idx),mem_addr,4);
	}

	template <>
	inline reg maskzgat<int64_t,int64_t>(const msk m, const int64_t *mem_addr, const reg idx) {
		return _mm512_castsi512_ps(_mm512_mask_i64gather_epi64(_mm512_setzero_si512(),(__mmask8)m,_mm512_castps_si512(idx),mem_addr,8));
	}

	template <>
	inline reg maskzgat<int32_t,int32_t>(const msk m, const int32_t *mem_addr, const reg idx) {
		return _mm512_castsi512_ps(_mm512_mask_i32gather_epi32(_mm512_setzero_si512(),(__mmask16)m,_mm512_castps_si512(idx),mem_addr,4));
	}
#endif

	// -------------------------------------------------------------------------------------------------------- scatter
#if defined(__AVX512F__)
	template <>
	inline void scatter<double,int64_t>(double *mem_addr, const reg idx, const reg r) {
		_mm512_i64scatter_pd(mem_addr,_mm512_castps_si512(idx),_mm512_castps_pd(r),8);
	}

	template <>
	inline void scatter<float,int32_t>(float *mem_addr, const reg idx, const reg r) {
		_mm512_i32scatter_ps(mem_addr,_mm512_castps_si512(idx),r,4);
	}

	template <>
	inline void scatter<int64_t,int64_t>(int64_t *mem_addr, const reg idx, const reg r) {
		_mm512_i64scatter_epi64(mem_addr,_mm512_castps_si512(idx),_mm512_castps_si512(r),8);
	}

	template <>
	inline void scatter<int32_t,int32_t>(int32_t *mem_addr, const reg idx, const reg r) {
		_mm512_i32scatter_epi32(mem_addr,_mm512_castps_si512(idx),_mm512_castps_si512(r),4);
	}
#else
	template <>
	inline void scatter<double,int64_t>(double *mem_addr, const reg idx, const reg r) {
		scatter_seq<double,int64_t>(mem_addr, idx, r);
	}

	template <>
	inline void scatter<float,int32_t>(float *mem_addr, const reg idx, const reg r) {
		scatter_seq<float,int32_t>(mem_addr, idx, r);
	}

	template <>
	inline void scatter<int64_t,int64_t>(int64_t *mem_addr, const reg idx, const reg r) {
		scatter_seq<int64_t,int64_t>(mem_addr, idx, r);
	}

	template <>
	inline void scatter<int32_t,int32_t>(int32_t *mem_addr, const reg idx, const reg r) {
		scatter_seq<int32_t,int32_t>(mem_addr, idx, r);
	}
#endif
	template <>
	inline void scatter<int16_t,int16_t>(int16_t *mem_addr, const reg idx, const reg r) {
		scatter_seq<int16_t,int16_t>(mem_addr, idx, r);
	}

	template <>
	inline void scatter<int8_t,int8_t>(int8_t *mem_addr, const reg idx, const reg r) {
		scatter_seq<int8_t,int8_t>(mem_addr, idx, r);
	}

	// ------------------------------------------------------------------------------------------------- masked scatter
#if defined(__AVX512F__)
	template <>
	inline void masksca<double,int64_t>(const msk m, double *mem_addr, const reg idx, const reg r) {
		_mm512_mask_i64scatter_pd(mem_addr,(__mmask8)m,_mm512_castps_si512(idx),_mm512_castps_pd(r),8);
	}

	template <>
	inline void masksca<float,int32_t>(const msk m, float *mem_addr, const reg idx, const reg r) {
		_mm512_mask_i32scatter_ps(mem_addr,(__mmask16)m,_mm512_castps_si512(idx),r,4);
	}

	template <>
	inline void masksca<int64_t,int64_t>(const msk m, int64_t *mem_addr, const reg idx, const reg r) {
		_mm512_mask_i64scatter_epi64(mem_addr,(__mmask8)m,_mm512_castps_si512(idx),_mm512_castps_si512(r),8);
	}

	template <>
	inline void masksca<int32_t,int32_t>(const msk m, int32_t *mem_addr, const reg idx, const reg r) {
		_mm512_mask_i32scatter_epi32(mem_addr,(__mmask16)m,_mm512_castps_si512(idx),_mm512_castps_si512(r),4);
	}
#endif

	// -------------------------------------------------------------------------------------------------------- maskzld
#if defined(__AVX512F__)
	template <>
	inline reg maskzld<double>(const msk m, const double* memp){
		return _mm512_castpd_ps(_mm512_mask_load_pd(_mm512_setzero_pd(),(__mmask8)m,memp));
	}

	template <>
	inline reg maskzld<float>(const msk m, const float* memp){
		return _mm512_mask_load_ps(_mm512_setzero_ps(),(__mmask16)m,memp);
	}

	template <>
	inline reg maskzld<int64_t>(const msk m, const int64_t* memp){
		return _mm512_castsi512_ps(_mm512_mask_load_epi64(_mm512_setzero_si512(),(__mmask8)m,memp));
	}

	template <>
	inline reg maskzld<int32_t>(const msk m, const int32_t* memp){
		return _mm512_castsi512_ps(_mm512_mask_load_epi32(_mm512_setzero_si512(),(__mmask16)m,memp));
	}
#endif

	// --------------------------------------------------------------------------------------------------------- maskst
#if defined(__AVX512F__)
	template <>
	inline void maskst<double>(const msk m, double* memp, const reg a){
		_mm512_mask_store_pd(memp,(__mmask8)m,_mm512_castps_pd(a));
	}

	template <>
	inline void maskst<float>(const msk m, float* memp, const reg a){
		_mm512_mask_store_ps(memp,(__mmask16)m,a);
	}

	template <>
	inline void maskst<int64_t>(const msk m, int64_t* memp, const reg a){
		_mm512_mask_store_epi64(memp,(__mmask8)m,_mm512_castps_si512(a));
	}

	template <>
	inline void maskst<int32_t>(const msk m, int32_t* memp, const reg a){
		_mm512_mask_store_epi32(memp,(__mmask16)m,_mm512_castps_si512(a));
	}
#endif

	// ------------------------------------------------------------------------------------------------------- getfirst
#if defined(__AVX512F__)
	template <>
	inline double getfirst<double>(const mipp::reg r){
		return _mm512_cvtsd_f64(_mm512_castps_pd(r));
	}

	template <>
	inline float getfirst<float>(const mipp::reg r){
		return _mm512_cvtss_f32(r);
	}
#endif

	// ---------------------------------------------------------------------------------------------------------- cmpeq
	template <>
	inline msk cmpeq<double>(const reg v1, const reg v2) {
		return (msk) _mm512_cmp_pd_mask(_mm512_castps_pd(v1), _mm512_castps_pd(v2), _CMP_EQ_OQ);
	}

	template <>
	inline msk cmpeq<float>(const reg v1, const reg v2) {
		return (msk) _mm512_cmp_ps_mask(v1, v2, _CMP_EQ_OQ);
	}

#if defined(__AVX512F__)
	template <>
	inline msk cmpeq<int64_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmpeq_epi64_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}
#endif

	template <>
	inline msk cmpeq<int32_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmpeq_epi32_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}

#if defined(__AVX512BW__)
	template <>
	inline msk cmpeq<int16_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmpeq_epi16_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}

	template <>
	inline msk cmpeq<int8_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmpeq_epi8_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- set1
#ifdef __AVX512F__
	template <>
	inline reg set1<float>(const float val) {
		return _mm512_set1_ps(val);
	}

	template <>
	inline reg set1<double>(const double val) {
		return _mm512_castpd_ps(_mm512_set1_pd(val));
	}

	template <>
	inline reg set1<int64_t>(const int64_t val) {
		return _mm512_castsi512_ps(_mm512_set1_epi64(val));
	}

	template <>
	inline reg set1<uint64_t>(const uint64_t val) {
		uint64_t t[mipp::N<uint64_t>()] = { val, val, val, val, val, val, val, val };
		return loadu<int64_t>((int64_t*)t);
	}

	template <>
	inline reg set1<int32_t>(const int32_t val) {
		return _mm512_castsi512_ps(_mm512_set1_epi32(val));
	}

	template <>
	inline reg set1<uint32_t>(const uint32_t val) {
		uint32_t t[mipp::N<uint32_t>()] = { val, val, val, val, val, val, val, val,
		                                    val, val, val, val, val, val, val, val };
		return loadu<int32_t>((int32_t*)t);
	}

	template <>
	inline reg set1<int16_t>(const int16_t val) {
		return _mm512_castsi512_ps(_mm512_set1_epi16(val));
	}

	template <>
	inline reg set1<uint16_t>(const uint16_t val) {
		uint16_t t[mipp::N<uint16_t>()] = { val, val, val, val, val, val, val, val,
		                                    val, val, val, val, val, val, val, val,
		                                    val, val, val, val, val, val, val, val,
		                                    val, val, val, val, val, val, val, val };
		return loadu<int16_t>((int16_t*)t);
	}

	template <>
	inline reg set1<int8_t>(const int8_t val) {
		return _mm512_castsi512_ps(_mm512_set1_epi8(val));
	}

	template <>
	inline reg set1<uint8_t>(const uint8_t val) {
		uint8_t t[mipp::N<uint8_t>()] = { val, val, val, val, val, val, val, val,
		                                  val, val, val, val, val, val, val, val,
		                                  val, val, val, val, val, val, val, val,
		                                  val, val, val, val, val, val, val, val,
		                                  val, val, val, val, val, val, val, val,
		                                  val, val, val, val, val, val, val, val,
		                                  val, val, val, val, val, val, val, val,
		                                  val, val, val, val, val, val, val, val };
		return loadu<int8_t>((int8_t*)t);
	}

#elif defined(__MIC__) || defined(__KNCNI__)
	template <>
	inline reg set1<double>(const double val) {
		double init[8] __attribute__((aligned(64))) = {val, val, val, val, val, val, val, val};
		return load<double>(init);
	}

	template <>
	inline reg set1<float>(const float val) {
		float init[16] __attribute__((aligned(64))) = {val, val, val, val, val, val, val, val,
		                                               val, val, val, val, val, val, val, val};
		return load<float>(init);
	}

	template <>
	inline reg set1<int64_t>(const int64_t val) {
		int64_t init[8] __attribute__((aligned(64))) = {val, val, val, val, val, val, val, val};
		return load<int64_t>(init);
	}

	template <>
	inline reg set1<int32_t>(const int32_t val) {
		int32_t init[16] __attribute__((aligned(64))) = {val, val, val, val, val, val, val, val,
		                                                 val, val, val, val, val, val, val, val};
		return load<int32_t>(init);
	}
#endif

	// ---------------------------------------------------------------------------------------------------- set1 (mask)
	template <>
	inline msk set1<8>(const bool val) {
		auto r1 = set1<int64_t>(val ? (uint64_t)0xFFFFFFFFFFFFFFFF : 0);
		auto r2 = set1<int64_t>(      (uint64_t)0xFFFFFFFFFFFFFFFF    );

		return (msk) cmpeq<int64_t>(r1, r2);
	}

	template <>
	inline msk set1<16>(const bool val) {
		auto r1 = set1<int32_t>(val ? 0xFFFFFFFF : 0);
		auto r2 = set1<int32_t>(      0xFFFFFFFF    );

		return (msk) cmpeq<int32_t>(r1, r2);
	}

	template <>
	inline msk set1<32>(const bool val) {
		auto r1 = set1<int16_t>(val ? 0xFFFF : 0);
		auto r2 = set1<int16_t>(      0xFFFF    );

		return (msk) cmpeq<int16_t>(r1, r2);
	}

	template <>
	inline msk set1<64>(const bool val) {
		auto r1 = set1<int8_t>(val ? 0xFF : 0);
		auto r2 = set1<int8_t>(      0xFF    );

		return (msk) cmpeq<int8_t>(r1, r2);
	}

	// ----------------------------------------------------------------------------------------------------------- set0
#if defined(__AVX512F__)
	template <>
	inline reg set0<double>() {
		return _mm512_castpd_ps(_mm512_setzero_pd());
	}

	template <>
	inline reg set0<float>() {
		return _mm512_setzero_ps();
	}

	template <>
	inline reg set0<int64_t>() {
		return _mm512_castsi512_ps(_mm512_setzero_si512());
	}

	template <>
	inline reg set0<uint64_t>() {
		return _mm512_castsi512_ps(_mm512_setzero_si512());
	}

	template <>
	inline reg set0<int32_t>() {
		return _mm512_castsi512_ps(_mm512_setzero_si512());
	}

	template <>
	inline reg set0<uint32_t>() {
		return _mm512_castsi512_ps(_mm512_setzero_si512());
	}

	template <>
	inline reg set0<int16_t>() {
		return _mm512_castsi512_ps(_mm512_setzero_si512());
	}

	template <>
	inline reg set0<uint16_t>() {
		return _mm512_castsi512_ps(_mm512_setzero_si512());
	}

	template <>
	inline reg set0<int8_t>() {
		return _mm512_castsi512_ps(_mm512_setzero_si512());
	}

	template <>
	inline reg set0<uint8_t>() {
		return _mm512_castsi512_ps(_mm512_setzero_si512());
	}

#elif defined(__MIC__) || defined(__KNCNI__)
	template <>
	inline reg set0<float>() {
		return set1<float>(0.f);
	}

	template <>
	inline reg set0<double>() {
		return set1<double>(0.0);
	}

	template <>
	inline reg set0<int32_t>() {
		return set1<int32_t>(0);
	}
#endif

	// ---------------------------------------------------------------------------------------------------- set0 (mask)
	template <>
	inline msk set0<8>() {
//		auto r1 = set0<int32_t>(          );
//		auto r2 = set1<int32_t>(0xFFFFFFFF);
//
//		return (msk) cmpeq<int32_t>(r1, r2);

		msk m = 0;
		return _mm512_kxor(m, m);
	}

	template <>
	inline msk set0<16>() {
//		auto r1 = set0<int32_t>(          );
//		auto r2 = set1<int32_t>(0xFFFFFFFF);
//
//		return (msk) cmpeq<int32_t>(r1, r2);

		msk m = 0;
		return _mm512_kxor(m, m);
	}

	template <>
	inline msk set0<32>() {
//		auto r1 = set0<int32_t>(          );
//		auto r2 = set1<int32_t>(0xFFFFFFFF);
//
//		return (msk) cmpeq<int32_t>(r1, r2);

		msk m = 0;
		return _mm512_kxor(m, m);
	}

	template <>
	inline msk set0<64>() {
//		auto r1 = set0<int32_t>(          );
//		auto r2 = set1<int32_t>(0xFFFFFFFF);
//
//		return (msk) cmpeq<int32_t>(r1, r2);

		msk m = 0;
		return _mm512_kxor(m, m);
	}

	// ------------------------------------------------------------------------------------------------------------ set
#if defined(__AVX512F__)
	template <>
	inline reg set<double>(const double vals[nElReg<double>()]) {
		return _mm512_castpd_ps(_mm512_set_pd(vals[7], vals[6], vals[5], vals[4], vals[3], vals[2], vals[1], vals[0]));
	}

	template <>
	inline reg set<float>(const float vals[nElReg<float>()]) {
		return _mm512_set_ps(vals[15], vals[14], vals[13], vals[12], vals[11], vals[10], vals[9], vals[8],
		                     vals[ 7], vals[ 6], vals[ 5], vals[ 4], vals[ 3], vals[ 2], vals[1], vals[0]);
	}

	template <>
	inline reg set<int64_t>(const int64_t vals[nElReg<int64_t>()]) {
		return _mm512_castsi512_ps(_mm512_set_epi64(vals[ 7], vals[ 6], vals[ 5], vals[ 4],
		                                            vals[ 3], vals[ 2], vals[ 1], vals[ 0]));
	}

	template <>
	inline reg set<int32_t>(const int32_t vals[nElReg<int32_t>()]) {
		return _mm512_castsi512_ps(_mm512_set_epi32(vals[15], vals[14], vals[13], vals[12],
		                                            vals[11], vals[10], vals[ 9], vals[ 8],
		                                            vals[ 7], vals[ 6], vals[ 5], vals[ 4],
		                                            vals[ 3], vals[ 2], vals[ 1], vals[ 0]));
	}

#ifdef __AVX512BW__

	static __m512i _mm512_set_epi16 (short e31, short e30, short e29, short e28, short e27, short e26, short e25, short e24,
	                                 short e23, short e22, short e21, short e20, short e19, short e18, short e17, short e16,
	                                 short e15, short e14, short e13, short e12, short e11, short e10, short  e9, short  e8,
	                                 short  e7, short  e6, short  e5, short  e4, short  e3, short  e2, short  e1, short  e0)
	{
		short data[32] = {e0,   e1,  e2,  e3,  e4,  e5,  e6,  e7,
		                  e8,   e9, e10, e11, e12, e13, e14, e15,
		                  e16, e17, e18, e19, e20, e21, e22, e23,
		                  e24, e25, e26, e27, e28, e29, e30, e31};

		return _mm512_castps_si512(mipp::load<int16_t>((int16_t*)data));
	}

	static __m512i _mm512_setr_epi16 (short  e0, short  e1, short  e2, short  e3, short  e4, short  e5, short  e6, short e7,
	                                  short  e8, short  e9, short e10, short e11, short e12, short e13, short e14, short e15,
	                                  short e16, short e17, short e18, short e19, short e20, short e21, short e22, short e23,
	                                  short e24, short e25, short e26, short e27, short e28, short e29, short e30, short e31)
	{
		short data[32] = {e0,   e1,  e2,  e3,  e4,  e5,  e6,  e7,
		                  e8,   e9, e10, e11, e12, e13, e14, e15,
		                  e16, e17, e18, e19, e20, e21, e22, e23,
		                  e24, e25, e26, e27, e28, e29, e30, e31};

		return _mm512_castps_si512(mipp::load<int16_t>((int16_t*)data));
	}

	static __m512i _mm512_set_epi8 (char e63, char e62, char e61, char e60, char e59, char e58, char e57, char e56,
	                                char e55, char e54, char e53, char e52, char e51, char e50, char e49, char e48,
	                                char e47, char e46, char e45, char e44, char e43, char e42, char e41, char e40,
	                                char e39, char e38, char e37, char e36, char e35, char e34, char e33, char e32,
	                                char e31, char e30, char e29, char e28, char e27, char e26, char e25, char e24,
	                                char e23, char e22, char e21, char e20, char e19, char e18, char e17, char e16,
	                                char e15, char e14, char e13, char e12, char e11, char e10, char  e9, char  e8,
	                                char  e7, char  e6, char  e5, char  e4, char  e3, char  e2, char  e1, char  e0)
	{
		char data[64] = {e0,   e1,  e2,  e3,  e4,  e5,  e6,  e7,
		                 e8,   e9, e10, e11, e12, e13, e14, e15,
		                 e16, e17, e18, e19, e20, e21, e22, e23,
		                 e24, e25, e26, e27, e28, e29, e30, e31,
		                 e32, e33, e34, e35, e36, e37, e38, e39,
		                 e40, e41, e42, e43, e44, e45, e46, e47,
		                 e48, e49, e50, e51, e52, e53, e54, e55,
		                 e56, e57, e58, e59, e60, e61, e62, e63};

		return _mm512_castps_si512(mipp::load<int8_t>((int8_t*)data));
	}

	// static __m512i _mm512_setr_epi8 (char  e0, char  e1, char  e2, char  e3, char  e4, char  e5, char  e6, char  e7,
	//                                  char  e8, char  e9, char e10, char e11, char e12, char e13, char e14, char e15,
	//                                  char e16, char e17, char e18, char e19, char e20, char e21, char e22, char e23,
	//                                  char e24, char e25, char e26, char e27, char e28, char e29, char e30, char e31,
	//                                  char e32, char e33, char e34, char e35, char e36, char e37, char e38, char e39,
	//                                  char e40, char e41, char e42, char e43, char e44, char e45, char e46, char e47,
	//                                  char e48, char e49, char e50, char e51, char e52, char e53, char e54, char e55,
	//                                  char e56, char e57, char e58, char e59, char e60, char e61, char e62, char e63)
	// {
	// 	char data[64] = {e0,   e1,  e2,  e3,  e4,  e5,  e6,  e7,
	// 	                 e8,   e9, e10, e11, e12, e13, e14, e15,
	// 	                 e16, e17, e18, e19, e20, e21, e22, e23,
	// 	                 e24, e25, e26, e27, e28, e29, e30, e31,
	// 	                 e32, e33, e34, e35, e36, e37, e38, e39,
	// 	                 e40, e41, e42, e43, e44, e45, e46, e47,
	// 	                 e48, e49, e50, e51, e52, e53, e54, e55,
	// 	                 e56, e57, e58, e59, e60, e61, e62, e63};

	// 	return _mm512_castps_si512(mipp::load<int8_t>((int8_t*)data));
	// }

	template <>
	inline reg set<int16_t>(const int16_t vals[nElReg<int16_t>()]) {
		return _mm512_castsi512_ps(_mm512_set_epi16((int16_t)vals[31], (int16_t)vals[30], (int16_t)vals[29], (int16_t)vals[28],
		                                            (int16_t)vals[27], (int16_t)vals[26], (int16_t)vals[25], (int16_t)vals[24],
		                                            (int16_t)vals[23], (int16_t)vals[22], (int16_t)vals[21], (int16_t)vals[20],
		                                            (int16_t)vals[19], (int16_t)vals[18], (int16_t)vals[17], (int16_t)vals[16],
		                                            (int16_t)vals[15], (int16_t)vals[14], (int16_t)vals[13], (int16_t)vals[12],
		                                            (int16_t)vals[11], (int16_t)vals[10], (int16_t)vals[ 9], (int16_t)vals[ 8],
		                                            (int16_t)vals[ 7], (int16_t)vals[ 6], (int16_t)vals[ 5], (int16_t)vals[ 4],
		                                            (int16_t)vals[ 3], (int16_t)vals[ 2], (int16_t)vals[ 1], (int16_t)vals[ 0]));
	}

	template <>
	inline reg set<int8_t>(const int8_t vals[nElReg<int8_t>()]) {
		return _mm512_castsi512_ps(_mm512_set_epi8((int8_t)vals[63], (int8_t)vals[62], (int8_t)vals[61], (int8_t)vals[60],
		                                           (int8_t)vals[59], (int8_t)vals[58], (int8_t)vals[57], (int8_t)vals[56],
		                                           (int8_t)vals[55], (int8_t)vals[54], (int8_t)vals[53], (int8_t)vals[52],
		                                           (int8_t)vals[51], (int8_t)vals[50], (int8_t)vals[49], (int8_t)vals[48],
		                                           (int8_t)vals[47], (int8_t)vals[46], (int8_t)vals[45], (int8_t)vals[44],
		                                           (int8_t)vals[43], (int8_t)vals[42], (int8_t)vals[41], (int8_t)vals[40],
		                                           (int8_t)vals[39], (int8_t)vals[38], (int8_t)vals[37], (int8_t)vals[36],
		                                           (int8_t)vals[35], (int8_t)vals[34], (int8_t)vals[33], (int8_t)vals[32],
		                                           (int8_t)vals[31], (int8_t)vals[30], (int8_t)vals[29], (int8_t)vals[28],
		                                           (int8_t)vals[27], (int8_t)vals[26], (int8_t)vals[25], (int8_t)vals[24],
		                                           (int8_t)vals[23], (int8_t)vals[22], (int8_t)vals[21], (int8_t)vals[20],
		                                           (int8_t)vals[19], (int8_t)vals[18], (int8_t)vals[17], (int8_t)vals[16],
		                                           (int8_t)vals[15], (int8_t)vals[14], (int8_t)vals[13], (int8_t)vals[12],
		                                           (int8_t)vals[11], (int8_t)vals[10], (int8_t)vals[ 9], (int8_t)vals[ 8],
		                                           (int8_t)vals[ 7], (int8_t)vals[ 6], (int8_t)vals[ 5], (int8_t)vals[ 4],
		                                           (int8_t)vals[ 3], (int8_t)vals[ 2], (int8_t)vals[ 1], (int8_t)vals[ 0]));
	}
#endif

#elif defined(__MIC__) || defined(__KNCNI__)
	template <>
	inline reg set<double>(const double vals[nElReg<double>()]) {
		double init[8] __attribute__((aligned(64))) = {vals[0], vals[1], vals[2], vals[3],
		                                               vals[4], vals[5], vals[6], vals[7]};
		return load<double>(init);
	}

	template <>
	inline reg set<float>(const float vals[nElReg<float>()]) {
		float init[16] __attribute__((aligned(64))) = {vals[ 0], vals[ 1], vals[ 2], vals[ 3],
		                                               vals[ 4], vals[ 5], vals[ 6], vals[ 7],
		                                               vals[ 8], vals[ 9], vals[10], vals[11],
		                                               vals[12], vals[13], vals[14], vals[15]};
		return load<float>(init);
	}

	template <>
	inline reg set<int64_t>(const int64_t vals[nElReg<int64_t>()]) {
		int64_t init[8] __attribute__((aligned(64))) = {vals[0], vals[1], vals[2], vals[3],
		                                                vals[4], vals[5], vals[6], vals[7]};
		return load<int64_t>(init);
	}

	template <>
	inline reg set<int32_t>(const int32_t vals[nElReg<int32_t>()]) {
		int32_t init[16] __attribute__((aligned(64))) = {vals[ 0], vals[ 1], vals[ 2], vals[ 3],
		                                                 vals[ 4], vals[ 5], vals[ 6], vals[ 7],
		                                                 vals[ 8], vals[ 9], vals[10], vals[11],
		                                                 vals[12], vals[13], vals[14], vals[15]};
		return load<int32_t>(init);
	}
#endif

	// ----------------------------------------------------------------------------------------------------- set (mask)
#ifdef __AVX512F__
	template <>
	inline msk set<8>(const bool vals[8]) {
		uint64_t v[8] = {vals[0] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0,
		                 vals[1] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0,
		                 vals[2] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0,
		                 vals[3] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0,
		                 vals[4] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0,
		                 vals[5] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0,
		                 vals[6] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0,
		                 vals[7] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0};
		auto r1 = set <int64_t>((int64_t*)v);
		auto r2 = set1<int64_t>((uint64_t)0xFFFFFFFFFFFFFFFF);

//		return (msk)_mm512_test_epi64_mask(_mm512_castps_si512(r1), _mm512_castps_si512(r2));
		return (msk) cmpeq<int64_t>(r1, r2);
	}
#endif

	template <>
	inline msk set<16>(const bool vals[16]) {
		uint32_t v[16] = {vals[ 0] ? 0xFFFFFFFF : 0, vals[ 1] ? 0xFFFFFFFF : 0,
		                  vals[ 2] ? 0xFFFFFFFF : 0, vals[ 3] ? 0xFFFFFFFF : 0,
		                  vals[ 4] ? 0xFFFFFFFF : 0, vals[ 5] ? 0xFFFFFFFF : 0,
		                  vals[ 6] ? 0xFFFFFFFF : 0, vals[ 7] ? 0xFFFFFFFF : 0,
		                  vals[ 8] ? 0xFFFFFFFF : 0, vals[ 9] ? 0xFFFFFFFF : 0,
		                  vals[10] ? 0xFFFFFFFF : 0, vals[11] ? 0xFFFFFFFF : 0,
		                  vals[12] ? 0xFFFFFFFF : 0, vals[13] ? 0xFFFFFFFF : 0,
		                  vals[14] ? 0xFFFFFFFF : 0, vals[15] ? 0xFFFFFFFF : 0};
		auto r1 = set <int32_t>((int32_t*)v);
		auto r2 = set1<int32_t>(0xFFFFFFFF);

//		return (msk)_mm512_test_epi32_mask(_mm512_castps_si512(r1), _mm512_castps_si512(r2));
		return (msk) cmpeq<int32_t>(r1, r2);
	}

#ifdef __AVX512BW__
	template <>
	inline msk set<32>(const bool vals[32]) {
		uint16_t v[32] = {vals[ 0] ? (uint16_t)0xFFFF : (uint16_t)0, vals[ 1] ? (uint16_t)0xFFFF : (uint16_t)0,
		                  vals[ 2] ? (uint16_t)0xFFFF : (uint16_t)0, vals[ 3] ? (uint16_t)0xFFFF : (uint16_t)0,
		                  vals[ 4] ? (uint16_t)0xFFFF : (uint16_t)0, vals[ 5] ? (uint16_t)0xFFFF : (uint16_t)0,
		                  vals[ 6] ? (uint16_t)0xFFFF : (uint16_t)0, vals[ 7] ? (uint16_t)0xFFFF : (uint16_t)0,
		                  vals[ 8] ? (uint16_t)0xFFFF : (uint16_t)0, vals[ 9] ? (uint16_t)0xFFFF : (uint16_t)0,
		                  vals[10] ? (uint16_t)0xFFFF : (uint16_t)0, vals[11] ? (uint16_t)0xFFFF : (uint16_t)0,
		                  vals[12] ? (uint16_t)0xFFFF : (uint16_t)0, vals[13] ? (uint16_t)0xFFFF : (uint16_t)0,
		                  vals[14] ? (uint16_t)0xFFFF : (uint16_t)0, vals[15] ? (uint16_t)0xFFFF : (uint16_t)0,
		                  vals[16] ? (uint16_t)0xFFFF : (uint16_t)0, vals[17] ? (uint16_t)0xFFFF : (uint16_t)0,
		                  vals[18] ? (uint16_t)0xFFFF : (uint16_t)0, vals[19] ? (uint16_t)0xFFFF : (uint16_t)0,
		                  vals[20] ? (uint16_t)0xFFFF : (uint16_t)0, vals[21] ? (uint16_t)0xFFFF : (uint16_t)0,
		                  vals[22] ? (uint16_t)0xFFFF : (uint16_t)0, vals[23] ? (uint16_t)0xFFFF : (uint16_t)0,
		                  vals[24] ? (uint16_t)0xFFFF : (uint16_t)0, vals[25] ? (uint16_t)0xFFFF : (uint16_t)0,
		                  vals[26] ? (uint16_t)0xFFFF : (uint16_t)0, vals[27] ? (uint16_t)0xFFFF : (uint16_t)0,
		                  vals[28] ? (uint16_t)0xFFFF : (uint16_t)0, vals[29] ? (uint16_t)0xFFFF : (uint16_t)0,
		                  vals[30] ? (uint16_t)0xFFFF : (uint16_t)0, vals[31] ? (uint16_t)0xFFFF : (uint16_t)0};
		auto r1 = set <int16_t>((int16_t*)v);
		auto r2 = set1<int16_t>(0xFFFF);

//		return (msk)_mm512_test_epi16_mask(_mm512_castps_si512(r1), _mm512_castps_si512(r2));
		return (msk) cmpeq<int16_t>(r1, r2);
	}

	template <>
	inline msk set<64>(const bool vals[64]) {
		uint8_t v[64] = {vals[ 0] ? (uint8_t)0xFF : (uint8_t)0, vals[ 1] ? (uint8_t)0xFF : (uint8_t)0, vals[ 2] ? (uint8_t)0xFF : (uint8_t)0, vals[ 3] ? (uint8_t)0xFF : (uint8_t)0,
		                 vals[ 4] ? (uint8_t)0xFF : (uint8_t)0, vals[ 5] ? (uint8_t)0xFF : (uint8_t)0, vals[ 6] ? (uint8_t)0xFF : (uint8_t)0, vals[ 7] ? (uint8_t)0xFF : (uint8_t)0,
		                 vals[ 8] ? (uint8_t)0xFF : (uint8_t)0, vals[ 9] ? (uint8_t)0xFF : (uint8_t)0, vals[10] ? (uint8_t)0xFF : (uint8_t)0, vals[11] ? (uint8_t)0xFF : (uint8_t)0,
		                 vals[12] ? (uint8_t)0xFF : (uint8_t)0, vals[13] ? (uint8_t)0xFF : (uint8_t)0, vals[14] ? (uint8_t)0xFF : (uint8_t)0, vals[15] ? (uint8_t)0xFF : (uint8_t)0,
		                 vals[16] ? (uint8_t)0xFF : (uint8_t)0, vals[17] ? (uint8_t)0xFF : (uint8_t)0, vals[18] ? (uint8_t)0xFF : (uint8_t)0, vals[19] ? (uint8_t)0xFF : (uint8_t)0,
		                 vals[20] ? (uint8_t)0xFF : (uint8_t)0, vals[21] ? (uint8_t)0xFF : (uint8_t)0, vals[22] ? (uint8_t)0xFF : (uint8_t)0, vals[23] ? (uint8_t)0xFF : (uint8_t)0,
		                 vals[24] ? (uint8_t)0xFF : (uint8_t)0, vals[25] ? (uint8_t)0xFF : (uint8_t)0, vals[26] ? (uint8_t)0xFF : (uint8_t)0, vals[27] ? (uint8_t)0xFF : (uint8_t)0,
		                 vals[28] ? (uint8_t)0xFF : (uint8_t)0, vals[29] ? (uint8_t)0xFF : (uint8_t)0, vals[30] ? (uint8_t)0xFF : (uint8_t)0, vals[31] ? (uint8_t)0xFF : (uint8_t)0,
		                 vals[32] ? (uint8_t)0xFF : (uint8_t)0, vals[33] ? (uint8_t)0xFF : (uint8_t)0, vals[34] ? (uint8_t)0xFF : (uint8_t)0, vals[35] ? (uint8_t)0xFF : (uint8_t)0,
		                 vals[36] ? (uint8_t)0xFF : (uint8_t)0, vals[37] ? (uint8_t)0xFF : (uint8_t)0, vals[38] ? (uint8_t)0xFF : (uint8_t)0, vals[39] ? (uint8_t)0xFF : (uint8_t)0,
		                 vals[40] ? (uint8_t)0xFF : (uint8_t)0, vals[41] ? (uint8_t)0xFF : (uint8_t)0, vals[42] ? (uint8_t)0xFF : (uint8_t)0, vals[43] ? (uint8_t)0xFF : (uint8_t)0,
		                 vals[44] ? (uint8_t)0xFF : (uint8_t)0, vals[45] ? (uint8_t)0xFF : (uint8_t)0, vals[46] ? (uint8_t)0xFF : (uint8_t)0, vals[47] ? (uint8_t)0xFF : (uint8_t)0,
		                 vals[48] ? (uint8_t)0xFF : (uint8_t)0, vals[49] ? (uint8_t)0xFF : (uint8_t)0, vals[50] ? (uint8_t)0xFF : (uint8_t)0, vals[51] ? (uint8_t)0xFF : (uint8_t)0,
		                 vals[52] ? (uint8_t)0xFF : (uint8_t)0, vals[53] ? (uint8_t)0xFF : (uint8_t)0, vals[54] ? (uint8_t)0xFF : (uint8_t)0, vals[55] ? (uint8_t)0xFF : (uint8_t)0,
		                 vals[56] ? (uint8_t)0xFF : (uint8_t)0, vals[57] ? (uint8_t)0xFF : (uint8_t)0, vals[58] ? (uint8_t)0xFF : (uint8_t)0, vals[59] ? (uint8_t)0xFF : (uint8_t)0,
		                 vals[60] ? (uint8_t)0xFF : (uint8_t)0, vals[61] ? (uint8_t)0xFF : (uint8_t)0, vals[62] ? (uint8_t)0xFF : (uint8_t)0, vals[63] ? (uint8_t)0xFF : (uint8_t)0};
		auto r1 = set <int8_t>((int8_t*)v);
		auto r2 = set1<int8_t>(0xFF);

//		return (msk)_mm512_test_epi8_mask(_mm512_castps_si512(r1), _mm512_castps_si512(r2));
		return (msk) cmpeq<int8_t>(r1, r2);
	}
#endif

	// ---------------------------------------------------------------------------------------------------------- toreg
	template <>
	inline reg toreg<8>(const msk m) {
		auto one  = set1<int64_t>((uint64_t)0xFFFFFFFFFFFFFFFF);
		auto zero = set1<int64_t>(0);

		return blend<int64_t>(one, zero, m);
	}

	template <>
	inline reg toreg<16>(const msk m) {
		auto one  = set1<int32_t>(0xFFFFFFFF);
		auto zero = set1<int32_t>(0);

		return blend<int32_t>(one, zero, m);
	}

#ifdef __AVX512BW__
	template <>
	inline reg toreg<32>(const msk m) {
		auto one  = set1<int16_t>(0xFFFF);
		auto zero = set1<int16_t>(0);

		return blend<int16_t>(one, zero, m);
	}

	template <>
	inline reg toreg<64>(const msk m) {
		auto one  = set1<int8_t>(0xFF);
		auto zero = set1<int8_t>(0);

		return blend<int8_t>(one, zero, m);
	}
#endif


	// ------------------------------------------------------------------------------------------------------------ low
#if defined(__AVX512F__)
	template <>
	inline reg_2 low<double>(const reg v) {
		return _mm256_castpd_ps(_mm512_extractf64x4_pd(_mm512_castps_pd(v), 0));
	}

	template <>
	inline reg_2 low<float>(const reg v) {
		return _mm256_castpd_ps(_mm512_extractf64x4_pd(_mm512_castps_pd(v), 0));
	}

	template <>
	inline reg_2 low<int64_t>(const reg v) {
		return _mm256_castpd_ps(_mm512_extractf64x4_pd(_mm512_castps_pd(v), 0));
	}

	template <>
	inline reg_2 low<int32_t>(const reg v) {
		return _mm256_castpd_ps(_mm512_extractf64x4_pd(_mm512_castps_pd(v), 0));
	}

	template <>
	inline reg_2 low<int16_t>(const reg v) {
		return _mm256_castpd_ps(_mm512_extractf64x4_pd(_mm512_castps_pd(v), 0));
	}

	template <>
	inline reg_2 low<int8_t>(const reg v) {
		return _mm256_castpd_ps(_mm512_extractf64x4_pd(_mm512_castps_pd(v), 0));
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- high
#if defined(__AVX512F__)
	template <>
	inline reg_2 high<double>(const reg v) {
		return _mm256_castpd_ps(_mm512_extractf64x4_pd(_mm512_castps_pd(v), 1));
	}

	template <>
	inline reg_2 high<float>(const reg v) {
		return _mm256_castpd_ps(_mm512_extractf64x4_pd(_mm512_castps_pd(v), 1));
	}

	template <>
	inline reg_2 high<int64_t>(const reg v) {
		return _mm256_castpd_ps(_mm512_extractf64x4_pd(_mm512_castps_pd(v), 1));
	}

	template <>
	inline reg_2 high<int32_t>(const reg v) {
		return _mm256_castpd_ps(_mm512_extractf64x4_pd(_mm512_castps_pd(v), 1));
	}

	template <>
	inline reg_2 high<int16_t>(const reg v) {
		return _mm256_castpd_ps(_mm512_extractf64x4_pd(_mm512_castps_pd(v), 1));
	}

	template <>
	inline reg_2 high<int8_t>(const reg v) {
		return _mm256_castpd_ps(_mm512_extractf64x4_pd(_mm512_castps_pd(v), 1));
	}
#endif

	// -------------------------------------------------------------------------------------------------------- combine
#if defined(__AVX512F__)
	template <>
	inline reg combine<double>(const reg_2 v1, const reg_2 v2)
	{
		auto v3 = _mm512_castps256_ps512(v1);
		return _mm512_castpd_ps(_mm512_insertf64x4(_mm512_castps_pd(v3), _mm256_castps_pd(v2), 1));
	}

	template <>
	inline reg combine<int64_t>(const reg_2 v1, const reg_2 v2)
	{
		auto v3 = _mm512_castps256_ps512(v1);
		return _mm512_castpd_ps(_mm512_insertf64x4(_mm512_castps_pd(v3), _mm256_castps_pd(v2), 1));
	}

	template <>
	inline reg combine<float>(const reg_2 v1, const reg_2 v2)
	{
		auto v3 = _mm512_castps256_ps512(v1);
		return _mm512_castpd_ps(_mm512_insertf64x4(_mm512_castps_pd(v3), _mm256_castps_pd(v2), 1));
	}

	template <>
	inline reg combine<int32_t>(const reg_2 v1, const reg_2 v2)
	{
		auto v3 = _mm512_castps256_ps512(v1);
		return _mm512_castpd_ps(_mm512_insertf64x4(_mm512_castps_pd(v3), _mm256_castps_pd(v2), 1));
	}

	template <>
	inline reg combine<int16_t>(const reg_2 v1, const reg_2 v2)
	{
		auto v3 = _mm512_castps256_ps512(v1);
		return _mm512_castpd_ps(_mm512_insertf64x4(_mm512_castps_pd(v3), _mm256_castps_pd(v2), 1));
	}

	template <>
	inline reg combine<int8_t>(const reg_2 v1, const reg_2 v2)
	{
		auto v3 = _mm512_castps256_ps512(v1);
		return _mm512_castpd_ps(_mm512_insertf64x4(_mm512_castps_pd(v3), _mm256_castps_pd(v2), 1));
	}
#endif

	// -------------------------------------------------------------------------------------------------- combine (bis)
#if defined(__AVX512F__)
	// float ------------------------------------------------------------------
	template <> inline reg combine< 0, float>(const reg v1, const reg v2) { return v1; }
	template <> inline reg combine< 1, float>(const reg v1, const reg v2) { return _mm512_permutex2var_ps(v1, _mm512_setr_epi32( 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16), v2); }
	template <> inline reg combine< 2, float>(const reg v1, const reg v2) { return _mm512_permutex2var_ps(v1, _mm512_setr_epi32( 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17), v2); }
	template <> inline reg combine< 3, float>(const reg v1, const reg v2) { return _mm512_permutex2var_ps(v1, _mm512_setr_epi32( 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18), v2); }
	template <> inline reg combine< 4, float>(const reg v1, const reg v2) { return _mm512_permutex2var_ps(v1, _mm512_setr_epi32( 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19), v2); }
	template <> inline reg combine< 5, float>(const reg v1, const reg v2) { return _mm512_permutex2var_ps(v1, _mm512_setr_epi32( 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20), v2); }
	template <> inline reg combine< 6, float>(const reg v1, const reg v2) { return _mm512_permutex2var_ps(v1, _mm512_setr_epi32( 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21), v2); }
	template <> inline reg combine< 7, float>(const reg v1, const reg v2) { return _mm512_permutex2var_ps(v1, _mm512_setr_epi32( 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22), v2); }
	template <> inline reg combine< 8, float>(const reg v1, const reg v2) { return _mm512_permutex2var_ps(v1, _mm512_setr_epi32( 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23), v2); }
	template <> inline reg combine< 9, float>(const reg v1, const reg v2) { return _mm512_permutex2var_ps(v1, _mm512_setr_epi32( 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24), v2); }
	template <> inline reg combine<10, float>(const reg v1, const reg v2) { return _mm512_permutex2var_ps(v1, _mm512_setr_epi32(10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25), v2); }
	template <> inline reg combine<11, float>(const reg v1, const reg v2) { return _mm512_permutex2var_ps(v1, _mm512_setr_epi32(11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26), v2); }
	template <> inline reg combine<12, float>(const reg v1, const reg v2) { return _mm512_permutex2var_ps(v1, _mm512_setr_epi32(12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27), v2); }
	template <> inline reg combine<13, float>(const reg v1, const reg v2) { return _mm512_permutex2var_ps(v1, _mm512_setr_epi32(13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28), v2); }
	template <> inline reg combine<14, float>(const reg v1, const reg v2) { return _mm512_permutex2var_ps(v1, _mm512_setr_epi32(14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29), v2); }
	template <> inline reg combine<15, float>(const reg v1, const reg v2) { return _mm512_permutex2var_ps(v1, _mm512_setr_epi32(15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30), v2); }

	// int32_t ----------------------------------------------------------------
	template <> inline reg combine< 0, int32_t>(const reg v1, const reg v2) { return combine< 0, float>(v1, v2); }
	template <> inline reg combine< 1, int32_t>(const reg v1, const reg v2) { return combine< 1, float>(v1, v2); }
	template <> inline reg combine< 2, int32_t>(const reg v1, const reg v2) { return combine< 2, float>(v1, v2); }
	template <> inline reg combine< 3, int32_t>(const reg v1, const reg v2) { return combine< 3, float>(v1, v2); }
	template <> inline reg combine< 4, int32_t>(const reg v1, const reg v2) { return combine< 4, float>(v1, v2); }
	template <> inline reg combine< 5, int32_t>(const reg v1, const reg v2) { return combine< 5, float>(v1, v2); }
	template <> inline reg combine< 6, int32_t>(const reg v1, const reg v2) { return combine< 6, float>(v1, v2); }
	template <> inline reg combine< 7, int32_t>(const reg v1, const reg v2) { return combine< 7, float>(v1, v2); }
	template <> inline reg combine< 8, int32_t>(const reg v1, const reg v2) { return combine< 8, float>(v1, v2); }
	template <> inline reg combine< 9, int32_t>(const reg v1, const reg v2) { return combine< 9, float>(v1, v2); }
	template <> inline reg combine<10, int32_t>(const reg v1, const reg v2) { return combine<10, float>(v1, v2); }
	template <> inline reg combine<11, int32_t>(const reg v1, const reg v2) { return combine<11, float>(v1, v2); }
	template <> inline reg combine<12, int32_t>(const reg v1, const reg v2) { return combine<12, float>(v1, v2); }
	template <> inline reg combine<13, int32_t>(const reg v1, const reg v2) { return combine<13, float>(v1, v2); }
	template <> inline reg combine<14, int32_t>(const reg v1, const reg v2) { return combine<14, float>(v1, v2); }
	template <> inline reg combine<15, int32_t>(const reg v1, const reg v2) { return combine<15, float>(v1, v2); }

	// double -----------------------------------------------------------------
	template <> inline reg combine< 0, double>(const reg v1, const reg v2) { return combine< 0, float>(v1, v2); }
	template <> inline reg combine< 1, double>(const reg v1, const reg v2) { return combine< 2, float>(v1, v2); }
	template <> inline reg combine< 2, double>(const reg v1, const reg v2) { return combine< 4, float>(v1, v2); }
	template <> inline reg combine< 3, double>(const reg v1, const reg v2) { return combine< 6, float>(v1, v2); }
	template <> inline reg combine< 4, double>(const reg v1, const reg v2) { return combine< 8, float>(v1, v2); }
	template <> inline reg combine< 5, double>(const reg v1, const reg v2) { return combine<10, float>(v1, v2); }
	template <> inline reg combine< 6, double>(const reg v1, const reg v2) { return combine<12, float>(v1, v2); }
	template <> inline reg combine< 7, double>(const reg v1, const reg v2) { return combine<14, float>(v1, v2); }

	// int64_t ----------------------------------------------------------------
	template <> inline reg combine< 0, int64_t>(const reg v1, const reg v2) { return combine<0, double>(v1, v2); }
	template <> inline reg combine< 1, int64_t>(const reg v1, const reg v2) { return combine<1, double>(v1, v2); }
	template <> inline reg combine< 2, int64_t>(const reg v1, const reg v2) { return combine<2, double>(v1, v2); }
	template <> inline reg combine< 3, int64_t>(const reg v1, const reg v2) { return combine<3, double>(v1, v2); }
	template <> inline reg combine< 4, int64_t>(const reg v1, const reg v2) { return combine<4, double>(v1, v2); }
	template <> inline reg combine< 5, int64_t>(const reg v1, const reg v2) { return combine<5, double>(v1, v2); }
	template <> inline reg combine< 6, int64_t>(const reg v1, const reg v2) { return combine<6, double>(v1, v2); }
	template <> inline reg combine< 7, int64_t>(const reg v1, const reg v2) { return combine<7, double>(v1, v2); }
#endif

#if defined(__AVX512BW__)
	// int16_t ----------------------------------------------------------------
	template <> inline reg combine< 0, int16_t>(const reg v1, const reg v2) { return v1; }
	template <> inline reg combine< 1, int16_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi16(_mm512_castps_si512(v1), _mm512_setr_epi16( 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32), _mm512_castps_si512(v2))); }
	template <> inline reg combine< 2, int16_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi16(_mm512_castps_si512(v1), _mm512_setr_epi16( 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33), _mm512_castps_si512(v2))); }
	template <> inline reg combine< 3, int16_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi16(_mm512_castps_si512(v1), _mm512_setr_epi16( 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34), _mm512_castps_si512(v2))); }
	template <> inline reg combine< 4, int16_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi16(_mm512_castps_si512(v1), _mm512_setr_epi16( 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35), _mm512_castps_si512(v2))); }
	template <> inline reg combine< 5, int16_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi16(_mm512_castps_si512(v1), _mm512_setr_epi16( 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36), _mm512_castps_si512(v2))); }
	template <> inline reg combine< 6, int16_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi16(_mm512_castps_si512(v1), _mm512_setr_epi16( 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37), _mm512_castps_si512(v2))); }
	template <> inline reg combine< 7, int16_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi16(_mm512_castps_si512(v1), _mm512_setr_epi16( 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38), _mm512_castps_si512(v2))); }
	template <> inline reg combine< 8, int16_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi16(_mm512_castps_si512(v1), _mm512_setr_epi16( 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39), _mm512_castps_si512(v2))); }
	template <> inline reg combine< 9, int16_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi16(_mm512_castps_si512(v1), _mm512_setr_epi16( 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40), _mm512_castps_si512(v2))); }
	template <> inline reg combine<10, int16_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi16(_mm512_castps_si512(v1), _mm512_setr_epi16(10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41), _mm512_castps_si512(v2))); }
	template <> inline reg combine<11, int16_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi16(_mm512_castps_si512(v1), _mm512_setr_epi16(11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42), _mm512_castps_si512(v2))); }
	template <> inline reg combine<12, int16_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi16(_mm512_castps_si512(v1), _mm512_setr_epi16(12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43), _mm512_castps_si512(v2))); }
	template <> inline reg combine<13, int16_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi16(_mm512_castps_si512(v1), _mm512_setr_epi16(13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44), _mm512_castps_si512(v2))); }
	template <> inline reg combine<14, int16_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi16(_mm512_castps_si512(v1), _mm512_setr_epi16(14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45), _mm512_castps_si512(v2))); }
	template <> inline reg combine<15, int16_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi16(_mm512_castps_si512(v1), _mm512_setr_epi16(15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46), _mm512_castps_si512(v2))); }
	template <> inline reg combine<16, int16_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi16(_mm512_castps_si512(v1), _mm512_setr_epi16(16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47), _mm512_castps_si512(v2))); }
	template <> inline reg combine<17, int16_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi16(_mm512_castps_si512(v1), _mm512_setr_epi16(17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48), _mm512_castps_si512(v2))); }
	template <> inline reg combine<18, int16_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi16(_mm512_castps_si512(v1), _mm512_setr_epi16(18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49), _mm512_castps_si512(v2))); }
	template <> inline reg combine<19, int16_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi16(_mm512_castps_si512(v1), _mm512_setr_epi16(19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50), _mm512_castps_si512(v2))); }
	template <> inline reg combine<20, int16_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi16(_mm512_castps_si512(v1), _mm512_setr_epi16(20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51), _mm512_castps_si512(v2))); }
	template <> inline reg combine<21, int16_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi16(_mm512_castps_si512(v1), _mm512_setr_epi16(21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52), _mm512_castps_si512(v2))); }
	template <> inline reg combine<22, int16_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi16(_mm512_castps_si512(v1), _mm512_setr_epi16(22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53), _mm512_castps_si512(v2))); }
	template <> inline reg combine<23, int16_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi16(_mm512_castps_si512(v1), _mm512_setr_epi16(23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54), _mm512_castps_si512(v2))); }
	template <> inline reg combine<24, int16_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi16(_mm512_castps_si512(v1), _mm512_setr_epi16(24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55), _mm512_castps_si512(v2))); }
	template <> inline reg combine<25, int16_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi16(_mm512_castps_si512(v1), _mm512_setr_epi16(25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56), _mm512_castps_si512(v2))); }
	template <> inline reg combine<26, int16_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi16(_mm512_castps_si512(v1), _mm512_setr_epi16(26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57), _mm512_castps_si512(v2))); }
	template <> inline reg combine<27, int16_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi16(_mm512_castps_si512(v1), _mm512_setr_epi16(27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58), _mm512_castps_si512(v2))); }
	template <> inline reg combine<28, int16_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi16(_mm512_castps_si512(v1), _mm512_setr_epi16(28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59), _mm512_castps_si512(v2))); }
	template <> inline reg combine<29, int16_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi16(_mm512_castps_si512(v1), _mm512_setr_epi16(29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60), _mm512_castps_si512(v2))); }
	template <> inline reg combine<30, int16_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi16(_mm512_castps_si512(v1), _mm512_setr_epi16(30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61), _mm512_castps_si512(v2))); }
	template <> inline reg combine<31, int16_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi16(_mm512_castps_si512(v1), _mm512_setr_epi16(31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62), _mm512_castps_si512(v2))); }
#endif

#if defined(__AVX512VBMI__)
	static inline __m512i _mm512_setr_epi8(char  e0, char  e1, char  e2, char  e3, char  e4, char  e5, char  e6,
	                                       char  e7, char  e8, char  e9, char e10, char e11, char e12, char e13,
	                                       char e14, char e15, char e16, char e17, char e18, char e19, char e20,
	                                       char e21, char e22, char e23, char e24, char e25, char e26, char e27,
	                                       char e28, char e29, char e30, char e31, char e32, char e33, char e34,
	                                       char e35, char e36, char e37, char e38, char e39, char e40, char e41,
	                                       char e42, char e43, char e44, char e45, char e46, char e47, char e48,
	                                       char e49, char e50, char e51, char e52, char e53, char e54, char e55,
	                                       char e56, char e57, char e58, char e59, char e60, char e61, char e62,
	                                       char e63) {
		return _mm512_set_epi8(e63, e62, e61, e60, e59, e58, e57, e56, e55, e54, e53, e52, e51, e50, e49, e48, e47,
			                   e46, e45, e44, e43, e42, e41, e40, e39, e38, e37, e36, e35, e34, e33, e32, e31, e30,
			                   e29, e28, e27, e26, e25, e24, e23, e22, e21, e20, e19, e18, e17, e16, e15, e14, e13,
			                   e12, e11, e10,  e9,  e8,  e7,  e6,  e5,  e4,  e3,  e2,  e1,  e0);
	}

	// int8_t -----------------------------------------------------------------
	template <> inline reg combine< 0, int8_t>(const reg v1, const reg v2) { return v1; }
	template <> inline reg combine< 1, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8( 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64), _mm512_castps_si512(v2))); }
	template <> inline reg combine< 2, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8( 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65), _mm512_castps_si512(v2))); }
	template <> inline reg combine< 3, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8( 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66), _mm512_castps_si512(v2))); }
	template <> inline reg combine< 4, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8( 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67), _mm512_castps_si512(v2))); }
	template <> inline reg combine< 5, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8( 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68), _mm512_castps_si512(v2))); }
	template <> inline reg combine< 6, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8( 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69), _mm512_castps_si512(v2))); }
	template <> inline reg combine< 7, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8( 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70), _mm512_castps_si512(v2))); }
	template <> inline reg combine< 8, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8( 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71), _mm512_castps_si512(v2))); }
	template <> inline reg combine< 9, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8( 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72), _mm512_castps_si512(v2))); }
	template <> inline reg combine<10, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73), _mm512_castps_si512(v2))); }
	template <> inline reg combine<11, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74), _mm512_castps_si512(v2))); }
	template <> inline reg combine<12, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75), _mm512_castps_si512(v2))); }
	template <> inline reg combine<13, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76), _mm512_castps_si512(v2))); }
	template <> inline reg combine<14, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77), _mm512_castps_si512(v2))); }
	template <> inline reg combine<15, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78), _mm512_castps_si512(v2))); }
	template <> inline reg combine<16, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79), _mm512_castps_si512(v2))); }
	template <> inline reg combine<17, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80), _mm512_castps_si512(v2))); }
	template <> inline reg combine<18, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81), _mm512_castps_si512(v2))); }
	template <> inline reg combine<19, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82), _mm512_castps_si512(v2))); }
	template <> inline reg combine<20, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83), _mm512_castps_si512(v2))); }
	template <> inline reg combine<21, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84), _mm512_castps_si512(v2))); }
	template <> inline reg combine<22, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85), _mm512_castps_si512(v2))); }
	template <> inline reg combine<23, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86), _mm512_castps_si512(v2))); }
	template <> inline reg combine<24, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87), _mm512_castps_si512(v2))); }
	template <> inline reg combine<25, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88), _mm512_castps_si512(v2))); }
	template <> inline reg combine<26, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89), _mm512_castps_si512(v2))); }
	template <> inline reg combine<27, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90), _mm512_castps_si512(v2))); }
	template <> inline reg combine<28, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91), _mm512_castps_si512(v2))); }
	template <> inline reg combine<29, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92), _mm512_castps_si512(v2))); }
	template <> inline reg combine<30, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93), _mm512_castps_si512(v2))); }
	template <> inline reg combine<31, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94), _mm512_castps_si512(v2))); }
	template <> inline reg combine<32, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95), _mm512_castps_si512(v2))); }
	template <> inline reg combine<33, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96), _mm512_castps_si512(v2))); }
	template <> inline reg combine<34, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97), _mm512_castps_si512(v2))); }
	template <> inline reg combine<35, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98), _mm512_castps_si512(v2))); }
	template <> inline reg combine<36, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99), _mm512_castps_si512(v2))); }
	template <> inline reg combine<37, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100), _mm512_castps_si512(v2))); }
	template <> inline reg combine<38, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101), _mm512_castps_si512(v2))); }
	template <> inline reg combine<39, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102), _mm512_castps_si512(v2))); }
	template <> inline reg combine<40, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103), _mm512_castps_si512(v2))); }
	template <> inline reg combine<41, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104), _mm512_castps_si512(v2))); }
	template <> inline reg combine<42, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105), _mm512_castps_si512(v2))); }
	template <> inline reg combine<43, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106), _mm512_castps_si512(v2))); }
	template <> inline reg combine<44, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107), _mm512_castps_si512(v2))); }
	template <> inline reg combine<45, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108), _mm512_castps_si512(v2))); }
	template <> inline reg combine<46, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109), _mm512_castps_si512(v2))); }
	template <> inline reg combine<47, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110), _mm512_castps_si512(v2))); }
	template <> inline reg combine<48, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111), _mm512_castps_si512(v2))); }
	template <> inline reg combine<49, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112), _mm512_castps_si512(v2))); }
	template <> inline reg combine<50, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113), _mm512_castps_si512(v2))); }
	template <> inline reg combine<51, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114), _mm512_castps_si512(v2))); }
	template <> inline reg combine<52, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115), _mm512_castps_si512(v2))); }
	template <> inline reg combine<53, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116), _mm512_castps_si512(v2))); }
	template <> inline reg combine<54, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117), _mm512_castps_si512(v2))); }
	template <> inline reg combine<55, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118), _mm512_castps_si512(v2))); }
	template <> inline reg combine<56, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119), _mm512_castps_si512(v2))); }
	template <> inline reg combine<57, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120), _mm512_castps_si512(v2))); }
	template <> inline reg combine<58, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121), _mm512_castps_si512(v2))); }
	template <> inline reg combine<59, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122), _mm512_castps_si512(v2))); }
	template <> inline reg combine<60, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123), _mm512_castps_si512(v2))); }
	template <> inline reg combine<61, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124), _mm512_castps_si512(v2))); }
	template <> inline reg combine<62, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125), _mm512_castps_si512(v2))); }
	template <> inline reg combine<63, int8_t>(const reg v1, const reg v2) { return _mm512_castsi512_ps(_mm512_permutex2var_epi8(_mm512_castps_si512(v1), _mm512_setr_epi8(63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126), _mm512_castps_si512(v2))); }
#endif

	// ---------------------------------------------------------------------------------------------------------- cmask
#if defined(__AVX512F__)
	template <>
	inline reg cmask<double>(const uint32_t vals[nElReg<double>()]) {
		return _mm512_castsi512_ps(_mm512_set_epi32((int32_t)vals[7]*2 +1, (int32_t)vals[7]*2 +0, (int32_t)vals[6]*2 +1, (int32_t)vals[6]*2 +0,
		                                            (int32_t)vals[5]*2 +1, (int32_t)vals[5]*2 +0, (int32_t)vals[4]*2 +1, (int32_t)vals[4]*2 +0,
		                                            (int32_t)vals[3]*2 +1, (int32_t)vals[3]*2 +0, (int32_t)vals[2]*2 +1, (int32_t)vals[2]*2 +0,
		                                            (int32_t)vals[1]*2 +1, (int32_t)vals[1]*2 +0, (int32_t)vals[0]*2 +1, (int32_t)vals[0]*2 +0));
	}

	template <>
	inline reg cmask<float>(const uint32_t vals[nElReg<float>()]) {
		return _mm512_castsi512_ps(_mm512_set_epi32((int32_t)vals[15], (int32_t)vals[14], (int32_t)vals[13], (int32_t)vals[12],
		                                            (int32_t)vals[11], (int32_t)vals[10], (int32_t)vals[ 9], (int32_t)vals[ 8],
		                                            (int32_t)vals[ 7], (int32_t)vals[ 6], (int32_t)vals[ 5], (int32_t)vals[ 4],
		                                            (int32_t)vals[ 3], (int32_t)vals[ 2], (int32_t)vals[ 1], (int32_t)vals[ 0]));
	}

	template <>
	inline reg cmask<int64_t>(const uint32_t vals[nElReg<int64_t>()]) {
		return _mm512_castsi512_ps(_mm512_set_epi32((int32_t)vals[7]*2 +1, (int32_t)vals[7]*2 +0, (int32_t)vals[6]*2 +1, (int32_t)vals[6]*2 +0,
		                                            (int32_t)vals[5]*2 +1, (int32_t)vals[5]*2 +0, (int32_t)vals[4]*2 +1, (int32_t)vals[4]*2 +0,
		                                            (int32_t)vals[3]*2 +1, (int32_t)vals[3]*2 +0, (int32_t)vals[2]*2 +1, (int32_t)vals[2]*2 +0,
		                                            (int32_t)vals[1]*2 +1, (int32_t)vals[1]*2 +0, (int32_t)vals[0]*2 +1, (int32_t)vals[0]*2 +0));
	}

	template <>
	inline reg cmask<int32_t>(const uint32_t vals[nElReg<int32_t>()]) {
		return _mm512_castsi512_ps(_mm512_set_epi32((int32_t)vals[15], (int32_t)vals[14], (int32_t)vals[13], (int32_t)vals[12],
		                                            (int32_t)vals[11], (int32_t)vals[10], (int32_t)vals[ 9], (int32_t)vals[ 8],
		                                            (int32_t)vals[ 7], (int32_t)vals[ 6], (int32_t)vals[ 5], (int32_t)vals[ 4],
		                                            (int32_t)vals[ 3], (int32_t)vals[ 2], (int32_t)vals[ 1], (int32_t)vals[ 0]));
	}
#endif

#if defined(__AVX512BW__)
	template <>
	inline reg cmask<int16_t>(const uint32_t val[nElReg<int16_t>()]) {
		return _mm512_castsi512_ps(_mm512_set_epi16((int16_t)val[31], (int16_t)val[30], (int16_t)val[29], (int16_t)val[28],
		                                            (int16_t)val[27], (int16_t)val[26], (int16_t)val[25], (int16_t)val[24],
		                                            (int16_t)val[23], (int16_t)val[22], (int16_t)val[21], (int16_t)val[20],
		                                            (int16_t)val[19], (int16_t)val[18], (int16_t)val[17], (int16_t)val[16],
		                                            (int16_t)val[15], (int16_t)val[14], (int16_t)val[13], (int16_t)val[12],
		                                            (int16_t)val[11], (int16_t)val[10], (int16_t)val[ 9], (int16_t)val[ 8],
		                                            (int16_t)val[ 7], (int16_t)val[ 6], (int16_t)val[ 5], (int16_t)val[ 4],
		                                            (int16_t)val[ 3], (int16_t)val[ 2], (int16_t)val[ 1], (int16_t)val[ 0]));
	}
#endif

#if defined(__AVX512VBMI__)
	template <>
	inline reg cmask<int8_t>(const uint32_t val[nElReg<int8_t>()]) {
		// return _mm512_castsi512_ps(_mm512_setr_epi8((int8_t)val[ 0], (int8_t)val[ 1], (int8_t)val[ 2], (int8_t)val[ 3],
		//                                             (int8_t)val[ 4], (int8_t)val[ 5], (int8_t)val[ 6], (int8_t)val[ 7],
		//                                             (int8_t)val[ 8], (int8_t)val[ 9], (int8_t)val[10], (int8_t)val[11],
		//                                             (int8_t)val[12], (int8_t)val[13], (int8_t)val[14], (int8_t)val[15],
		//                                             (int8_t)val[16], (int8_t)val[17], (int8_t)val[18], (int8_t)val[19],
		//                                             (int8_t)val[20], (int8_t)val[21], (int8_t)val[22], (int8_t)val[23],
		//                                             (int8_t)val[24], (int8_t)val[25], (int8_t)val[26], (int8_t)val[27],
		//                                             (int8_t)val[28], (int8_t)val[29], (int8_t)val[30], (int8_t)val[31],
		//                                             (int8_t)val[32], (int8_t)val[33], (int8_t)val[34], (int8_t)val[35],
		//                                             (int8_t)val[36], (int8_t)val[37], (int8_t)val[38], (int8_t)val[39],
		//                                             (int8_t)val[40], (int8_t)val[41], (int8_t)val[42], (int8_t)val[43],
		//                                             (int8_t)val[44], (int8_t)val[45], (int8_t)val[46], (int8_t)val[47],
		//                                             (int8_t)val[48], (int8_t)val[49], (int8_t)val[50], (int8_t)val[51],
		//                                             (int8_t)val[52], (int8_t)val[53], (int8_t)val[54], (int8_t)val[55],
		//                                             (int8_t)val[56], (int8_t)val[57], (int8_t)val[58], (int8_t)val[59],
		//                                             (int8_t)val[60], (int8_t)val[61], (int8_t)val[62], (int8_t)val[63]));
		return _mm512_castsi512_ps(_mm512_set_epi8((int8_t)val[63], (int8_t)val[62], (int8_t)val[61], (int8_t)val[60],
		                                           (int8_t)val[59], (int8_t)val[58], (int8_t)val[57], (int8_t)val[56],
		                                           (int8_t)val[55], (int8_t)val[54], (int8_t)val[53], (int8_t)val[52],
		                                           (int8_t)val[51], (int8_t)val[50], (int8_t)val[49], (int8_t)val[48],
		                                           (int8_t)val[47], (int8_t)val[46], (int8_t)val[45], (int8_t)val[44],
		                                           (int8_t)val[43], (int8_t)val[42], (int8_t)val[41], (int8_t)val[40],
		                                           (int8_t)val[39], (int8_t)val[38], (int8_t)val[37], (int8_t)val[36],
		                                           (int8_t)val[35], (int8_t)val[34], (int8_t)val[33], (int8_t)val[32],
		                                           (int8_t)val[31], (int8_t)val[30], (int8_t)val[29], (int8_t)val[28],
		                                           (int8_t)val[27], (int8_t)val[26], (int8_t)val[25], (int8_t)val[24],
		                                           (int8_t)val[23], (int8_t)val[22], (int8_t)val[21], (int8_t)val[20],
		                                           (int8_t)val[19], (int8_t)val[18], (int8_t)val[17], (int8_t)val[16],
		                                           (int8_t)val[15], (int8_t)val[14], (int8_t)val[13], (int8_t)val[12],
		                                           (int8_t)val[11], (int8_t)val[10], (int8_t)val[ 9], (int8_t)val[ 8],
		                                           (int8_t)val[ 7], (int8_t)val[ 6], (int8_t)val[ 5], (int8_t)val[ 4],
		                                           (int8_t)val[ 3], (int8_t)val[ 2], (int8_t)val[ 1], (int8_t)val[ 0]));
	}
#endif

	// --------------------------------------------------------------------------------------------------------- cmask2
#if defined(__AVX512F__)
	template <>
	inline reg cmask2<double>(const uint32_t vals[nElReg<double>()/2]) {
		return _mm512_castsi512_ps(_mm512_set_epi32((int32_t)vals[3]*2 +1+8, (int32_t)vals[3]*2 +0+8, (int32_t)vals[2]*2 +1+8, (int32_t)vals[2]*2 +0+8,
		                                            (int32_t)vals[1]*2 +1+8, (int32_t)vals[1]*2 +0+8, (int32_t)vals[0]*2 +1+8, (int32_t)vals[0]*2 +0+8,
		                                            (int32_t)vals[3]*2 +1+0, (int32_t)vals[3]*2 +0+0, (int32_t)vals[2]*2 +1+0, (int32_t)vals[2]*2 +0+0,
		                                            (int32_t)vals[1]*2 +1+0, (int32_t)vals[1]*2 +0+0, (int32_t)vals[0]*2 +1+0, (int32_t)vals[0]*2 +0+0));
	}

	template <>
	inline reg cmask2<float>(const uint32_t vals[nElReg<float>()/2]) {
		return _mm512_castsi512_ps(_mm512_set_epi32((int32_t)vals[ 7]+8, (int32_t)vals[ 6]+8, (int32_t)vals[ 5]+8, (int32_t)vals[ 4]+8,
		                                            (int32_t)vals[ 3]+8, (int32_t)vals[ 2]+8, (int32_t)vals[ 1]+8, (int32_t)vals[ 0]+8,
		                                            (int32_t)vals[ 7]+0, (int32_t)vals[ 6]+0, (int32_t)vals[ 5]+0, (int32_t)vals[ 4]+0,
		                                            (int32_t)vals[ 3]+0, (int32_t)vals[ 2]+0, (int32_t)vals[ 1]+0, (int32_t)vals[ 0]+0));
	}

	template <>
	inline reg cmask2<int64_t>(const uint32_t vals[nElReg<int64_t>()/2]) {
		return _mm512_castsi512_ps(_mm512_set_epi32((int32_t)vals[3]*2 +1+8, (int32_t)vals[3]*2 +0+8, (int32_t)vals[2]*2 +1+8, (int32_t)vals[2]*2 +0+8,
		                                            (int32_t)vals[1]*2 +1+8, (int32_t)vals[1]*2 +0+8, (int32_t)vals[0]*2 +1+8, (int32_t)vals[0]*2 +0+8,
		                                            (int32_t)vals[3]*2 +1+0, (int32_t)vals[3]*2 +0+0, (int32_t)vals[2]*2 +1+0, (int32_t)vals[2]*2 +0+0,
		                                            (int32_t)vals[1]*2 +1+0, (int32_t)vals[1]*2 +0+0, (int32_t)vals[0]*2 +1+0, (int32_t)vals[0]*2 +0+0));
	}

	template <>
	inline reg cmask2<int32_t>(const uint32_t vals[nElReg<int32_t>()/2]) {
		return _mm512_castsi512_ps(_mm512_set_epi32((int32_t)vals[ 7]+8, (int32_t)vals[ 6]+8, (int32_t)vals[ 5]+8, (int32_t)vals[ 4]+8,
		                                            (int32_t)vals[ 3]+8, (int32_t)vals[ 2]+8, (int32_t)vals[ 1]+8, (int32_t)vals[ 0]+8,
		                                            (int32_t)vals[ 7]+0, (int32_t)vals[ 6]+0, (int32_t)vals[ 5]+0, (int32_t)vals[ 4]+0,
		                                            (int32_t)vals[ 3]+0, (int32_t)vals[ 2]+0, (int32_t)vals[ 1]+0, (int32_t)vals[ 0]+0));
	}
#endif

#if defined(__AVX512BW__)
	template <>
	inline reg cmask2<int16_t>(const uint32_t vals[nElReg<int16_t>()/2]) {
		return _mm512_castsi512_ps(_mm512_set_epi16((int16_t)vals[15]+16, (int16_t)vals[14]+16, (int16_t)vals[13]+16, (int16_t)vals[12]+16,
		                                            (int16_t)vals[11]+16, (int16_t)vals[10]+16, (int16_t)vals[ 9]+16, (int16_t)vals[ 8]+16,
		                                            (int16_t)vals[ 7]+16, (int16_t)vals[ 6]+16, (int16_t)vals[ 5]+16, (int16_t)vals[ 4]+16,
		                                            (int16_t)vals[ 3]+16, (int16_t)vals[ 2]+16, (int16_t)vals[ 1]+16, (int16_t)vals[ 0]+16,
		                                            (int16_t)vals[15]+ 0, (int16_t)vals[14]+ 0, (int16_t)vals[13]+ 0, (int16_t)vals[12]+ 0,
		                                            (int16_t)vals[11]+ 0, (int16_t)vals[10]+ 0, (int16_t)vals[ 9]+ 0, (int16_t)vals[ 8]+ 0,
		                                            (int16_t)vals[ 7]+ 0, (int16_t)vals[ 6]+ 0, (int16_t)vals[ 5]+ 0, (int16_t)vals[ 4]+ 0,
		                                            (int16_t)vals[ 3]+ 0, (int16_t)vals[ 2]+ 0, (int16_t)vals[ 1]+ 0, (int16_t)vals[ 0]+ 0));
	}
#endif

#if defined(__AVX512VBMI__)
	template <>
	inline reg cmask2<int8_t>(const uint32_t val[nElReg<int8_t>()/2]) {
		// return _mm512_castsi512_ps(_mm512_setr_epi8((int8_t)(val[ 0] + 0), (int8_t)(val[ 1] + 0), (int8_t)(val[ 2] + 0), (int8_t)(val[ 3] + 0),
		//                                             (int8_t)(val[ 4] + 0), (int8_t)(val[ 5] + 0), (int8_t)(val[ 6] + 0), (int8_t)(val[ 7] + 0),
		//                                             (int8_t)(val[ 8] + 0), (int8_t)(val[ 9] + 0), (int8_t)(val[10] + 0), (int8_t)(val[11] + 0),
		//                                             (int8_t)(val[12] + 0), (int8_t)(val[13] + 0), (int8_t)(val[14] + 0), (int8_t)(val[15] + 0),
		//                                             (int8_t)(val[16] + 0), (int8_t)(val[17] + 0), (int8_t)(val[18] + 0), (int8_t)(val[19] + 0),
		//                                             (int8_t)(val[20] + 0), (int8_t)(val[21] + 0), (int8_t)(val[22] + 0), (int8_t)(val[23] + 0),
		//                                             (int8_t)(val[24] + 0), (int8_t)(val[25] + 0), (int8_t)(val[26] + 0), (int8_t)(val[27] + 0),
		//                                             (int8_t)(val[28] + 0), (int8_t)(val[29] + 0), (int8_t)(val[30] + 0), (int8_t)(val[31] + 0),
		//                                             (int8_t)(val[ 0] +32), (int8_t)(val[ 1] +32), (int8_t)(val[ 2] +32), (int8_t)(val[ 3] +32),
		//                                             (int8_t)(val[ 4] +32), (int8_t)(val[ 5] +32), (int8_t)(val[ 6] +32), (int8_t)(val[ 7] +32),
		//                                             (int8_t)(val[ 8] +32), (int8_t)(val[ 9] +32), (int8_t)(val[10] +32), (int8_t)(val[11] +32),
		//                                             (int8_t)(val[12] +32), (int8_t)(val[13] +32), (int8_t)(val[14] +32), (int8_t)(val[15] +32),
		//                                             (int8_t)(val[16] +32), (int8_t)(val[17] +32), (int8_t)(val[18] +32), (int8_t)(val[19] +32),
		//                                             (int8_t)(val[20] +32), (int8_t)(val[21] +32), (int8_t)(val[22] +32), (int8_t)(val[23] +32),
		//                                             (int8_t)(val[24] +32), (int8_t)(val[25] +32), (int8_t)(val[26] +32), (int8_t)(val[27] +32),
		//                                             (int8_t)(val[28] +32), (int8_t)(val[29] +32), (int8_t)(val[30] +32), (int8_t)(val[31] +32)));

		return _mm512_castsi512_ps(_mm512_set_epi8((int8_t)(val[31] +32), (int8_t)(val[30] +32), (int8_t)(val[29] +32), (int8_t)(val[28] +32),
		                                           (int8_t)(val[27] +32), (int8_t)(val[26] +32), (int8_t)(val[25] +32), (int8_t)(val[24] +32),
		                                           (int8_t)(val[23] +32), (int8_t)(val[22] +32), (int8_t)(val[21] +32), (int8_t)(val[20] +32),
		                                           (int8_t)(val[19] +32), (int8_t)(val[18] +32), (int8_t)(val[17] +32), (int8_t)(val[16] +32),
		                                           (int8_t)(val[15] +32), (int8_t)(val[14] +32), (int8_t)(val[13] +32), (int8_t)(val[12] +32),
		                                           (int8_t)(val[11] +32), (int8_t)(val[10] +32), (int8_t)(val[ 9] +32), (int8_t)(val[ 8] +32),
		                                           (int8_t)(val[ 7] +32), (int8_t)(val[ 6] +32), (int8_t)(val[ 5] +32), (int8_t)(val[ 4] +32),
		                                           (int8_t)(val[ 3] +32), (int8_t)(val[ 2] +32), (int8_t)(val[ 1] +32), (int8_t)(val[ 0] +32),
		                                           (int8_t)(val[31] + 0), (int8_t)(val[30] + 0), (int8_t)(val[29] + 0), (int8_t)(val[28] + 0),
		                                           (int8_t)(val[27] + 0), (int8_t)(val[26] + 0), (int8_t)(val[25] + 0), (int8_t)(val[24] + 0),
		                                           (int8_t)(val[23] + 0), (int8_t)(val[22] + 0), (int8_t)(val[21] + 0), (int8_t)(val[20] + 0),
		                                           (int8_t)(val[19] + 0), (int8_t)(val[18] + 0), (int8_t)(val[17] + 0), (int8_t)(val[16] + 0),
		                                           (int8_t)(val[15] + 0), (int8_t)(val[14] + 0), (int8_t)(val[13] + 0), (int8_t)(val[12] + 0),
		                                           (int8_t)(val[11] + 0), (int8_t)(val[10] + 0), (int8_t)(val[ 9] + 0), (int8_t)(val[ 8] + 0),
		                                           (int8_t)(val[ 7] + 0), (int8_t)(val[ 6] + 0), (int8_t)(val[ 5] + 0), (int8_t)(val[ 4] + 0),
		                                           (int8_t)(val[ 3] + 0), (int8_t)(val[ 2] + 0), (int8_t)(val[ 1] + 0), (int8_t)(val[ 0] + 0)));
	}
#endif

	// --------------------------------------------------------------------------------------------------------- cmask4
#if defined(__AVX512F__)
	template <>
	inline reg cmask4<double>(const uint32_t vals[nElReg<double>()/4]) {
		return _mm512_castsi512_ps(_mm512_set_epi32((int32_t)vals[1]*2 +1+12, (int32_t)vals[1]*2 +0+12, (int32_t)vals[0]*2 +1+12, (int32_t)vals[0]*2 +0+12,
		                                            (int32_t)vals[1]*2 +1+ 8, (int32_t)vals[1]*2 +0+ 8, (int32_t)vals[0]*2 +1+ 8, (int32_t)vals[0]*2 +0+ 8,
		                                            (int32_t)vals[1]*2 +1+ 4, (int32_t)vals[1]*2 +0+ 4, (int32_t)vals[0]*2 +1+ 4, (int32_t)vals[0]*2 +0+ 4,
		                                            (int32_t)vals[1]*2 +1+ 0, (int32_t)vals[1]*2 +0+ 0, (int32_t)vals[0]*2 +1+ 0, (int32_t)vals[0]*2 +0+ 0));
	}

	template <>
	inline reg cmask4<float>(const uint32_t vals[nElReg<float>()/4]) {
		return _mm512_castsi512_ps(_mm512_set_epi32((int32_t)vals[ 3]+12, (int32_t)vals[ 2]+12, (int32_t)vals[ 1]+12, (int32_t)vals[ 0]+12,
		                                            (int32_t)vals[ 3]+ 8, (int32_t)vals[ 2]+ 8, (int32_t)vals[ 1]+ 8, (int32_t)vals[ 0]+ 8,
		                                            (int32_t)vals[ 3]+ 4, (int32_t)vals[ 2]+ 4, (int32_t)vals[ 1]+ 4, (int32_t)vals[ 0]+ 4,
		                                            (int32_t)vals[ 3]+ 0, (int32_t)vals[ 2]+ 0, (int32_t)vals[ 1]+ 0, (int32_t)vals[ 0]+ 0));
	}

	template <>
	inline reg cmask4<int64_t>(const uint32_t vals[nElReg<int64_t>()/4]) {
		return _mm512_castsi512_ps(_mm512_set_epi32((int32_t)vals[1]*2 +1+12, (int32_t)vals[1]*2 +0+12, (int32_t)vals[0]*2 +1+12, (int32_t)vals[0]*2 +0+12,
		                                            (int32_t)vals[1]*2 +1+ 8, (int32_t)vals[1]*2 +0+ 8, (int32_t)vals[0]*2 +1+ 8, (int32_t)vals[0]*2 +0+ 8,
		                                            (int32_t)vals[1]*2 +1+ 4, (int32_t)vals[1]*2 +0+ 4, (int32_t)vals[0]*2 +1+ 4, (int32_t)vals[0]*2 +0+ 4,
		                                            (int32_t)vals[1]*2 +1+ 0, (int32_t)vals[1]*2 +0+ 0, (int32_t)vals[0]*2 +1+ 0, (int32_t)vals[0]*2 +0+ 0));
	}

	template <>
	inline reg cmask4<int32_t>(const uint32_t vals[nElReg<int32_t>()/4]) {
		return _mm512_castsi512_ps(_mm512_set_epi32((int32_t)vals[ 3]+12, (int32_t)vals[ 2]+12, (int32_t)vals[ 1]+12, (int32_t)vals[ 0]+12,
		                                            (int32_t)vals[ 3]+ 8, (int32_t)vals[ 2]+ 8, (int32_t)vals[ 1]+ 8, (int32_t)vals[ 0]+ 8,
		                                            (int32_t)vals[ 3]+ 4, (int32_t)vals[ 2]+ 4, (int32_t)vals[ 1]+ 4, (int32_t)vals[ 0]+ 4,
		                                            (int32_t)vals[ 3]+ 0, (int32_t)vals[ 2]+ 0, (int32_t)vals[ 1]+ 0, (int32_t)vals[ 0]+ 0));
	}
#endif

#if defined(__AVX512BW__)
	template <>
	inline reg cmask4<int16_t>(const uint32_t vals[nElReg<int16_t>()/4]) {
		return _mm512_castsi512_ps(_mm512_set_epi16((int32_t)vals[7]+24, (int32_t)vals[6]+24, (int32_t)vals[5]+24, (int32_t)vals[4]+24,
		                                            (int32_t)vals[3]+24, (int32_t)vals[2]+24, (int32_t)vals[1]+24, (int32_t)vals[0]+24,
		                                            (int32_t)vals[7]+16, (int32_t)vals[6]+16, (int32_t)vals[5]+16, (int32_t)vals[4]+16,
		                                            (int32_t)vals[3]+16, (int32_t)vals[2]+16, (int32_t)vals[1]+16, (int32_t)vals[0]+16,
		                                            (int32_t)vals[7]+ 8, (int32_t)vals[6]+ 8, (int32_t)vals[5]+ 8, (int32_t)vals[4]+ 8,
		                                            (int32_t)vals[3]+ 8, (int32_t)vals[2]+ 8, (int32_t)vals[1]+ 8, (int32_t)vals[0]+ 8,
		                                            (int32_t)vals[7]+ 0, (int32_t)vals[6]+ 0, (int32_t)vals[5]+ 0, (int32_t)vals[4]+ 0,
		                                            (int32_t)vals[3]+ 0, (int32_t)vals[2]+ 0, (int32_t)vals[1]+ 0, (int32_t)vals[0]+ 0));
	}

	template <>
	inline reg cmask4<int8_t>(const uint32_t val[nElReg<int8_t>()/4]) {
		return _mm512_castsi512_ps(_mm512_set_epi8((int8_t)(val[15] +48), (int8_t)(val[14] +48), (int8_t)(val[13] +48), (int8_t)(val[12] +48),
		                                           (int8_t)(val[11] +48), (int8_t)(val[10] +48), (int8_t)(val[ 9] +48), (int8_t)(val[ 8] +48),
		                                           (int8_t)(val[ 7] +48), (int8_t)(val[ 6] +48), (int8_t)(val[ 5] +48), (int8_t)(val[ 4] +48),
		                                           (int8_t)(val[ 3] +48), (int8_t)(val[ 2] +48), (int8_t)(val[ 1] +48), (int8_t)(val[ 0] +48),
		                                           (int8_t)(val[15] +32), (int8_t)(val[14] +32), (int8_t)(val[13] +32), (int8_t)(val[12] +32),
		                                           (int8_t)(val[11] +32), (int8_t)(val[10] +32), (int8_t)(val[ 9] +32), (int8_t)(val[ 8] +32),
		                                           (int8_t)(val[ 7] +32), (int8_t)(val[ 6] +32), (int8_t)(val[ 5] +32), (int8_t)(val[ 4] +32),
		                                           (int8_t)(val[ 3] +32), (int8_t)(val[ 2] +32), (int8_t)(val[ 1] +32), (int8_t)(val[ 0] +32),
		                                           (int8_t)(val[15] +16), (int8_t)(val[14] +16), (int8_t)(val[13] +16), (int8_t)(val[12] +16),
		                                           (int8_t)(val[11] +16), (int8_t)(val[10] +16), (int8_t)(val[ 9] +16), (int8_t)(val[ 8] +16),
		                                           (int8_t)(val[ 7] +16), (int8_t)(val[ 6] +16), (int8_t)(val[ 5] +16), (int8_t)(val[ 4] +16),
		                                           (int8_t)(val[ 3] +16), (int8_t)(val[ 2] +16), (int8_t)(val[ 1] +16), (int8_t)(val[ 0] +16),
		                                           (int8_t)(val[15] + 0), (int8_t)(val[14] + 0), (int8_t)(val[13] + 0), (int8_t)(val[12] + 0),
		                                           (int8_t)(val[11] + 0), (int8_t)(val[10] + 0), (int8_t)(val[ 9] + 0), (int8_t)(val[ 8] + 0),
		                                           (int8_t)(val[ 7] + 0), (int8_t)(val[ 6] + 0), (int8_t)(val[ 5] + 0), (int8_t)(val[ 4] + 0),
		                                           (int8_t)(val[ 3] + 0), (int8_t)(val[ 2] + 0), (int8_t)(val[ 1] + 0), (int8_t)(val[ 0] + 0)));
	}
#endif

	// ---------------------------------------------------------------------------------------------------------- shuff
#if defined(__AVX512F__)
	template <>
	inline reg shuff<double>(const reg v, const reg cm) {
		return _mm512_permutexvar_ps(_mm512_castps_si512(cm), v);
	}

	template <>
	inline reg shuff<float>(const reg v, const reg cm) {
		return _mm512_permutexvar_ps(_mm512_castps_si512(cm), v);
	}

	template <>
	inline reg shuff<int64_t>(const reg v, const reg cm) {
		return _mm512_permutexvar_ps(_mm512_castps_si512(cm), v);
	}

	template <>
	inline reg shuff<int32_t>(const reg v, const reg cm) {
		return _mm512_permutexvar_ps(_mm512_castps_si512(cm), v);
	}
#endif

#if defined(__AVX512BW__)
	template <>
	inline reg shuff<int16_t>(const reg v, const reg cm) {
		return _mm512_castsi512_ps(_mm512_permutexvar_epi16(_mm512_castps_si512(cm), _mm512_castps_si512(v)));
	}
#endif

#if defined(__AVX512VBMI__)
	template <>
	inline reg shuff<int8_t>(const reg v, const reg cm) {
		return _mm512_castsi512_ps(_mm512_permutexvar_epi8(_mm512_castps_si512(cm), _mm512_castps_si512(v)));
	}
#endif

	// --------------------------------------------------------------------------------------------------------- shuff2
#if defined(__AVX512F__)
	template <>
	inline reg shuff2<double>(const reg v, const reg cm) {
		return mipp::shuff<double>(v, cm);
	}

	template <>
	inline reg shuff2<float>(const reg v, const reg cm) {
		return mipp::shuff<float>(v, cm);
	}

	template <>
	inline reg shuff2<int64_t>(const reg v, const reg cm) {
		return mipp::shuff<int64_t>(v, cm);
	}

	template <>
	inline reg shuff2<int32_t>(const reg v, const reg cm) {
		return mipp::shuff<int32_t>(v, cm);
	}
#endif

#if defined(__AVX512BW__)
	template <>
	inline reg shuff2<int16_t>(const reg v, const reg cm) {
		return mipp::shuff<int16_t>(v, cm);
	}
#endif

#if defined(__AVX512VBMI__)
	template <>
	inline reg shuff2<int8_t>(const reg v, const reg cm) {
		return mipp::shuff<int8_t>(v, cm);
	}
#endif

	// --------------------------------------------------------------------------------------------------------- shuff4
#if defined(__AVX512F__)
	template <>
	inline reg shuff4<double>(const reg v, const reg cm) {
		return mipp::shuff<double>(v, cm);
	}

	template <>
	inline reg shuff4<float>(const reg v, const reg cm) {
		return mipp::shuff<float>(v, cm);
	}

	template <>
	inline reg shuff4<int64_t>(const reg v, const reg cm) {
		return mipp::shuff<int64_t>(v, cm);
	}

	template <>
	inline reg shuff4<int32_t>(const reg v, const reg cm) {
		return mipp::shuff<int32_t>(v, cm);
	}
#endif

#if defined(__AVX512BW__)
	template <>
	inline reg shuff4<int16_t>(const reg v, const reg cm) {
		return mipp::shuff<int16_t>(v, cm);
	}

	template <>
	inline reg shuff4<int8_t>(const reg v, const reg cm) {
		return _mm512_castsi512_ps(_mm512_shuffle_epi8(_mm512_castps_si512(v), _mm512_castps_si512(cm)));
	}
#endif

	// -------------------------------------------------------------------------------------------------- interleavelo4
#if defined(__AVX512F__)
	template <>
	inline reg interleavelo4<double>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_unpacklo_epi64(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg interleavelo4<float>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_unpacklo_epi32(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg interleavelo4<int64_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_unpacklo_epi64(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg interleavelo4<int32_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_unpacklo_epi32(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}
#endif

#if defined(__AVX512BW__)
	template <>
	inline reg interleavelo4<int16_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_unpacklo_epi16(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg interleavelo4<int8_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_unpacklo_epi8(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}
#endif

	// -------------------------------------------------------------------------------------------------- interleavehi4
#if defined(__AVX512F__)
	template <>
	inline reg interleavehi4<double>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_unpackhi_epi64(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg interleavehi4<float>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_unpackhi_epi32(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg interleavehi4<int64_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_unpackhi_epi64(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg interleavehi4<int32_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_unpackhi_epi32(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}
#endif

#if defined(__AVX512BW__)
	template <>
	inline reg interleavehi4<int16_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_unpackhi_epi16(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg interleavehi4<int8_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_unpackhi_epi8(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}
#endif

	// -------------------------------------------------------------------------------------------------- interleavelo2
#if defined(__AVX512F__)
	template <>
	inline reg interleavelo2<double>(const reg v1, const reg v2) {
		auto lo4 = mipp::interleavelo4<double>(v1, v2);
		auto hi4 = mipp::interleavehi4<double>(v1, v2);
		auto idx = _mm512_set_epi64(8|5,8|4,
		                              5,  4,
		                            8|1,8|0,
		                              1,  0);

		return _mm512_castpd_ps(_mm512_permutex2var_pd(_mm512_castps_pd(lo4), idx, _mm512_castps_pd(hi4)));
	}

	template <>
	inline reg interleavelo2<float>(const reg v1, const reg v2) {
		auto lo4 = mipp::interleavelo4<float>(v1, v2);
		auto hi4 = mipp::interleavehi4<float>(v1, v2);
		auto idx = _mm512_set_epi32(16|11,16|10,16|9,16|8,
		                               11,   10,   9,   8,
		                            16| 3,16| 2,16|1,16|0,
		                                3,    2,   1,   0);

		return _mm512_permutex2var_ps(lo4, idx, hi4);
	}

	template <>
	inline reg interleavelo2<int64_t>(const reg v1, const reg v2) {
		auto lo4 = mipp::interleavelo4<int64_t>(v1, v2);
		auto hi4 = mipp::interleavehi4<int64_t>(v1, v2);
		auto idx = _mm512_set_epi64(8|5,8|4,
		                              5,  4,
		                            8|1,8|0,
		                              1,  0);

		return _mm512_castsi512_ps(_mm512_permutex2var_epi64(_mm512_castps_si512(lo4), idx, _mm512_castps_si512(hi4)));
	}

	template <>
	inline reg interleavelo2<int32_t>(const reg v1, const reg v2) {
		auto lo4 = mipp::interleavelo4<int32_t>(v1, v2);
		auto hi4 = mipp::interleavehi4<int32_t>(v1, v2);
		auto idx = _mm512_set_epi64(8|5,8|4,
		                              5,  4,
		                            8|1,8|0,
		                              1,  0);

		return _mm512_castsi512_ps(_mm512_permutex2var_epi64(_mm512_castps_si512(lo4), idx, _mm512_castps_si512(hi4)));
	}
#endif

#if defined(__AVX512BW__)
	template <>
	inline reg interleavelo2<int16_t>(const reg v1, const reg v2) {
		auto lo4 = mipp::interleavelo4<int16_t>(v1, v2);
		auto hi4 = mipp::interleavehi4<int16_t>(v1, v2);
		auto idx = _mm512_set_epi64(8|5,8|4,
		                              5,  4,
		                            8|1,8|0,
		                              1,  0);

		return _mm512_castsi512_ps(_mm512_permutex2var_epi64(_mm512_castps_si512(lo4), idx, _mm512_castps_si512(hi4)));
	}

	template <>
	inline reg interleavelo2<int8_t>(const reg v1, const reg v2) {
		auto lo4 = mipp::interleavelo4<int8_t>(v1, v2);
		auto hi4 = mipp::interleavehi4<int8_t>(v1, v2);
		auto idx = _mm512_set_epi64(8|5,8|4,
		                              5,  4,
		                            8|1,8|0,
		                              1,  0);

		return _mm512_castsi512_ps(_mm512_permutex2var_epi64(_mm512_castps_si512(lo4), idx, _mm512_castps_si512(hi4)));
	}
#endif

	// -------------------------------------------------------------------------------------------------- interleavehi2
#if defined(__AVX512F__)
	template <>
	inline reg interleavehi2<double>(const reg v1, const reg v2) {
		auto lo4 = mipp::interleavelo4<double>(v1, v2);
		auto hi4 = mipp::interleavehi4<double>(v1, v2);
		auto idx = _mm512_set_epi64(8|7,8|6,
		                              7,  6,
		                            8|3,8|2,
		                              3,  2);

		return _mm512_castpd_ps(_mm512_permutex2var_pd(_mm512_castps_pd(lo4), idx, _mm512_castps_pd(hi4)));
	}

	template <>
	inline reg interleavehi2<float>(const reg v1, const reg v2) {
		auto lo4 = mipp::interleavelo4<float>(v1, v2);
		auto hi4 = mipp::interleavehi4<float>(v1, v2);
		auto idx = _mm512_set_epi64(8|7,8|6,
		                              7,  6,
		                            8|3,8|2,
		                              3,  2);

		return _mm512_castpd_ps(_mm512_permutex2var_pd(_mm512_castps_pd(lo4), idx, _mm512_castps_pd(hi4)));
	}

	template <>
	inline reg interleavehi2<int64_t>(const reg v1, const reg v2) {
		auto lo4 = mipp::interleavelo4<int64_t>(v1, v2);
		auto hi4 = mipp::interleavehi4<int64_t>(v1, v2);
		auto idx = _mm512_set_epi64(8|7,8|6,
		                              7,  6,
		                            8|3,8|2,
		                              3,  2);

		return _mm512_castpd_ps(_mm512_permutex2var_pd(_mm512_castps_pd(lo4), idx, _mm512_castps_pd(hi4)));
	}

	template <>
	inline reg interleavehi2<int32_t>(const reg v1, const reg v2) {
		auto lo4 = mipp::interleavelo4<int32_t>(v1, v2);
		auto hi4 = mipp::interleavehi4<int32_t>(v1, v2);
		auto idx = _mm512_set_epi64(8|7,8|6,
		                              7,  6,
		                            8|3,8|2,
		                              3,  2);

		return _mm512_castpd_ps(_mm512_permutex2var_pd(_mm512_castps_pd(lo4), idx, _mm512_castps_pd(hi4)));
	}
#endif

#if defined(__AVX512BW__)
	template <>
	inline reg interleavehi2<int16_t>(const reg v1, const reg v2) {
		auto lo4 = mipp::interleavelo4<int16_t>(v1, v2);
		auto hi4 = mipp::interleavehi4<int16_t>(v1, v2);
		auto idx = _mm512_set_epi64(8|7,8|6,
		                              7,  6,
		                            8|3,8|2,
		                              3,  2);

		return _mm512_castpd_ps(_mm512_permutex2var_pd(_mm512_castps_pd(lo4), idx, _mm512_castps_pd(hi4)));
	}

	template <>
	inline reg interleavehi2<int8_t>(const reg v1, const reg v2) {
		auto lo4 = mipp::interleavelo4<int8_t>(v1, v2);
		auto hi4 = mipp::interleavehi4<int8_t>(v1, v2);
		auto idx = _mm512_set_epi64(8|7,8|6,
		                              7,  6,
		                            8|3,8|2,
		                              3,  2);

		return _mm512_castpd_ps(_mm512_permutex2var_pd(_mm512_castps_pd(lo4), idx, _mm512_castps_pd(hi4)));
	}
#endif

	// ----------------------------------------------------------------------------------------------------- interleave
#if defined(__AVX512F__)
	template <>
	inline regx2 interleave<double>(const reg v1, const reg v2) {
		__m512i idx = _mm512_setr_epi64(0, 8, 1, 9, 2, 10, 3, 11);
		auto hi = _mm512_permutex2var_pd(_mm512_castps_pd(v1), idx, _mm512_castps_pd(v2));
		idx = _mm512_setr_epi64(4, 12, 5, 13, 6, 14, 7, 15);
		auto lo = _mm512_permutex2var_pd(_mm512_castps_pd(v1), idx, _mm512_castps_pd(v2));
		return {{_mm512_castpd_ps(hi), _mm512_castpd_ps(lo)}};
	}

	template <>
	inline regx2 interleave<float>(const reg v1, const reg v2) {
		__m512i idx = _mm512_setr_epi32(0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23);
		auto hi = _mm512_permutex2var_ps(v1, idx, v2);
		idx = _mm512_setr_epi32(8, 24, 9, 25, 10, 26, 11, 27, 12, 28, 13, 29, 14, 30, 15, 31);
		auto lo = _mm512_permutex2var_ps(v1, idx, v2);
		return {{hi, lo}};
	}

	template <>
	inline regx2 interleave<int64_t>(const reg v1, const reg v2) {
		__m512i idx = _mm512_setr_epi64(0, 8, 1, 9, 2, 10, 3, 11);
		auto hi = _mm512_permutex2var_epi64(_mm512_castps_si512(v1), idx, _mm512_castps_si512(v2));
		idx = _mm512_setr_epi64(4, 12, 5, 13, 6, 14, 7, 15);
		auto lo = _mm512_permutex2var_epi64(_mm512_castps_si512(v1), idx, _mm512_castps_si512(v2));
		return {{_mm512_castsi512_ps(hi), _mm512_castsi512_ps(lo)}};
	}

	template <>
	inline regx2 interleave<int32_t>(const reg v1, const reg v2) {
		__m512i idx = _mm512_setr_epi32(0, 16, 1, 17, 2, 18, 3, 19, 4, 20, 5, 21, 6, 22, 7, 23);
		auto hi = _mm512_permutex2var_epi32(_mm512_castps_si512(v1), idx, _mm512_castps_si512(v2));
		idx = _mm512_setr_epi32(8, 24, 9, 25, 10, 26, 11, 27, 12, 28, 13, 29, 14, 30, 15, 31);
		auto lo = _mm512_permutex2var_epi32(_mm512_castps_si512(v1), idx, _mm512_castps_si512(v2));
		return {{_mm512_castsi512_ps(hi), _mm512_castsi512_ps(lo)}};
	}
#endif

#if defined(__AVX512BW__)
	template <>
	inline regx2 interleave<int16_t>(const reg v1, const reg v2) {
		__m512i idx = _mm512_setr_epi16(0, 32, 1, 33,  2, 34,  3, 35,  4, 36,  5, 37,  6, 38,  7, 39,
		                                8, 40, 9, 41, 10, 42, 11, 43, 12, 44, 13, 45, 14, 46, 15, 47);
		auto hi = _mm512_permutex2var_epi16(_mm512_castps_si512(v1), idx, _mm512_castps_si512(v2));
		idx = _mm512_setr_epi16(16, 48, 17, 49, 18, 50, 19, 51, 20, 52, 21, 53, 22, 54, 23, 55,
		                        24, 56, 25, 57, 26, 58, 27, 59, 28, 60, 29, 61, 30, 62, 31, 63);
		auto lo = _mm512_permutex2var_epi16(_mm512_castps_si512(v1), idx, _mm512_castps_si512(v2));
		return {{_mm512_castsi512_ps(hi), _mm512_castsi512_ps(lo)}};
	}

#if defined(__AVX512VMBI__)
	template <>
	inline regx2 interleave<int8_t>(const reg v1, const reg v2) {
		__m512i idx = _mm512_setr_epi8( 0, 64,  1, 65,  2, 66,  3, 67,  4, 68,  5, 69,  6, 70,  7, 71,
		                                8, 72,  9, 73, 10, 74, 11, 75, 12, 76, 13, 77, 14, 78, 15, 79,
		                               16, 80, 17, 81, 18, 82, 19, 83, 20, 84, 21, 85, 22, 86, 23, 87,
		                               24, 88, 25, 89, 26, 90, 27, 91, 28, 92, 29, 93, 30, 94, 31, 95);
		auto hi = _mm512_permutex2var_epi8(_mm512_castps_si512(v1), idx, _mm512_castps_si512(v2));
		idx = _mm512_setr_epi8(32,  96, 33,  97, 34,  98, 35,  99, 36, 100, 37, 101, 38, 102, 39, 103,
		                       40, 104, 41, 105, 42, 106, 43, 107, 44, 108, 45, 109, 46, 110, 47, 111,
		                       48, 112, 49, 113, 50, 114, 51, 115, 52, 116, 53, 117, 54, 118, 55, 119,
		                       56, 120, 57, 121, 58, 122, 59, 123, 60, 124, 61, 125, 62, 126, 63, 127);

		auto lo = _mm512_permutex2var_epi8(_mm512_castps_si512(v1), idx, _mm512_castps_si512(v2));
		return {{_mm512_castsi512_ps(hi), _mm512_castsi512_ps(lo)}};
	}
#else
	template <>
	inline regx2 interleave<int8_t>(const reg v1, const reg v2) {
		auto lo4 = mipp::interleavelo4<int8_t>(v1, v2);
		auto hi4 = mipp::interleavehi4<int8_t>(v1, v2);
		auto idxlo = _mm512_set_epi64(8|3,8|2,
		                                3,  2,
		                              8|1,8|0,
		                                1,  0);
		auto idxhi = _mm512_set_epi64(8|7,8|6,
		                                7,  6,
		                              8|5,8|4,
		                                5,  4);
		return {{_mm512_castpd_ps(_mm512_permutex2var_pd(_mm512_castps_pd(lo4), idxlo, _mm512_castps_pd(hi4))),
		         _mm512_castpd_ps(_mm512_permutex2var_pd(_mm512_castps_pd(lo4), idxhi, _mm512_castps_pd(hi4)))}};
	}
#endif
#endif

	// --------------------------------------------------------------------------------------------------- deinterleave
	template <>
	inline regx2 deinterleave<double>(const reg v0, const reg v1)
	{
		__m512i realIndicies = _mm512_setr_epi64(0, 2, 4, 6, 8, 10, 12, 14);
		__m512i imagIndicies = _mm512_setr_epi64(1, 3, 5, 7, 9, 11, 13, 15);
		auto v_re = _mm512_permutex2var_pd(_mm512_castps_pd(v0), realIndicies, _mm512_castps_pd(v1));
		auto v_im = _mm512_permutex2var_pd(_mm512_castps_pd(v0), imagIndicies, _mm512_castps_pd(v1));
		return {{_mm512_castpd_ps(v_re), _mm512_castpd_ps(v_im)}};
	}

	template <>
	inline regx2 deinterleave<int64_t>(const reg v0, const reg v1)
	{
		__m512i realIndicies = _mm512_setr_epi64(0, 2, 4, 6, 8, 10, 12, 14);
		__m512i imagIndicies = _mm512_setr_epi64(1, 3, 5, 7, 9, 11, 13, 15);
		auto v_re = _mm512_permutex2var_epi64(_mm512_castps_si512(v0), realIndicies, _mm512_castps_si512(v1));
		auto v_im = _mm512_permutex2var_epi64(_mm512_castps_si512(v0), imagIndicies, _mm512_castps_si512(v1));
		return {{_mm512_castsi512_ps(v_re), _mm512_castsi512_ps(v_im)}};
	}

	template <>
	inline regx2 deinterleave<float>(const reg v0, const reg v1)
	{
		__m512i realIndicies = _mm512_setr_epi32(0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30);
		__m512i imagIndicies = _mm512_setr_epi32(1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31);
		auto v_re = _mm512_permutex2var_ps(v0, realIndicies, v1);
		auto v_im = _mm512_permutex2var_ps(v0, imagIndicies, v1);
		return {{v_re, v_im}};
	}

	template <>
	inline regx2 deinterleave<int32_t>(const reg v0, const reg v1)
	{
		__m512i realIndicies = _mm512_setr_epi32(0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30);
		__m512i imagIndicies = _mm512_setr_epi32(1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31);
		auto v_re = _mm512_permutex2var_epi32(_mm512_castps_si512(v0), realIndicies, _mm512_castps_si512(v1));
		auto v_im = _mm512_permutex2var_epi32(_mm512_castps_si512(v0), imagIndicies, _mm512_castps_si512(v1));
		return {{_mm512_castsi512_ps(v_re), _mm512_castsi512_ps(v_im)}};
	}

#ifdef __AVX512BW__
	template <>
	inline regx2 deinterleave<int16_t>(const reg v0, const reg v1)
	{
		__m512i realIndicies = _mm512_setr_epi16( 0,  2,  4,  6,  8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30,
		                                         32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62);
		__m512i imagIndicies = _mm512_setr_epi16( 1,  3,  5,  7,  9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31,
		                                         33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53, 55, 57, 59, 61, 63);
		auto v_re = _mm512_permutex2var_epi16(_mm512_castps_si512(v0), realIndicies, _mm512_castps_si512(v1));
		auto v_im = _mm512_permutex2var_epi16(_mm512_castps_si512(v0), imagIndicies, _mm512_castps_si512(v1));
		return {{_mm512_castsi512_ps(v_re), _mm512_castsi512_ps(v_im)}};

	}

#if defined(__AVX512VMBI__)
	template <>
	inline regx2 deinterleave<int8_t>(const reg v0, const reg v1)
	{
		__m512i realIndicies = _mm512_setr_epi8( 0,  2,   4,   6,   8,  10,  12,  14,  16,  18,  20,  22,  24,  26,  28,  30,
		                                        32, 34,  36,  38,  40,  42,  44,  46,  48,  50,  52,  54,  56,  58,  60,  62,
		                                        64, 66,  68,  70,  72,  74,  76,  78,  80,  82,  84,  86,  88,  90,  92,  94,
		                                        96, 98, 100, 102, 104, 106, 108, 110, 112, 114, 116, 118, 120, 122, 124, 126);
		__m512i imagIndicies = _mm512_setr_epi8( 1,  3,  5,    7,   9,  11,  13,  15,  17,  19,  21,  23,  25,  27,  29,  31,
		                                        33, 35, 37,   39,  41,  43,  45,  47,  49,  51,  53,  55,  57,  59,  61,  63,
		                                        65, 67, 69,   71,  73,  75,  77,  79,  81,  83,  85,  87,  89,  91,  93,  95,
		                                        97, 99, 101, 103, 105, 107, 109, 111, 113, 115, 117, 119, 121, 123, 125, 127);
		auto v_re = _mm512_permutex2var_epi8(_mm512_castps_si512(v0), realIndicies, _mm512_castps_si512(v1));
		auto v_im = _mm512_permutex2var_epi8(_mm512_castps_si512(v0), imagIndicies, _mm512_castps_si512(v1));
		return {{_mm512_castsi512_ps(v_re), _mm512_castsi512_ps(v_im)}};
	}
#else
	template <>
	inline regx2 deinterleave<int8_t>(const reg v0, const reg v1)
	{
		// const uint32_t cmask[64] = { 0,  2,  4,  6,  8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30,
		//                             32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62,
		//                              1,  3,  5,  7,  9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31,
		//                             33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53, 55, 57, 59, 61, 63 };
		// auto cm = mipp::cmask<int8_t>(cmask);

		// auto cm = _mm512_castsi512_ps(_mm512_setr_epi8( 0,  2,  4,  6,  8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30,
		//                                                32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62,
		//                                                 1,  3,  5,  7,  9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31,
		//                                                33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53, 55, 57, 59, 61, 63));

		auto cm = _mm512_castsi512_ps(_mm512_set_epi8(63, 61, 59, 57, 55, 53, 51, 49, 47, 45, 43, 41, 39, 37, 35, 33,
		                                              31, 29, 27, 25, 23, 21, 19, 17, 15, 13, 11,  9,  7,  5,  3,  1,
		                                              62, 60, 58, 56, 54, 52, 50, 48, 46, 44, 42, 40, 38, 36, 34, 32,
		                                              30, 28, 26, 24, 22, 20, 18, 16, 14, 12, 10,  8,  6,  4,  2,  0));

		auto v0s = mipp::shuff<int8_t>(v0, cm);
		auto v1s = mipp::shuff<int8_t>(v1, cm);

		auto v0l = mipp::low<int8_t>(v0s);
		auto v1l = mipp::low<int8_t>(v1s);

		auto v0h = mipp::high<int8_t>(v0s);
		auto v1h = mipp::high<int8_t>(v1s);

		auto v_re = mipp::combine<int8_t>(v0l, v1l);
		auto v_im = mipp::combine<int8_t>(v0h, v1h);

		return {{v_re, v_im}};
	}
#endif
#endif

	// --------------------------------------------------------------------------------------------------- interleavelo
#if defined(__AVX512F__)
	template <>
	inline reg interleavelo<double>(const reg v1, const reg v2) {
		auto lo4 = mipp::interleavelo4<double>(v1, v2);
		auto hi4 = mipp::interleavehi4<double>(v1, v2);
		auto idxlo = _mm512_set_epi64(8|3,8|2,
		                                3,  2,
		                              8|1,8|0,
		                                1,  0);
		return _mm512_castpd_ps(_mm512_permutex2var_pd(_mm512_castps_pd(lo4), idxlo, _mm512_castps_pd(hi4)));
	}

	template <>
	inline reg interleavelo<float>(const reg v1, const reg v2) {
		auto lo4 = mipp::interleavelo4<float>(v1, v2);
		auto hi4 = mipp::interleavehi4<float>(v1, v2);
		auto idxlo = _mm512_set_epi64(8|3,8|2,
		                                3,  2,
		                              8|1,8|0,
		                                1,  0);
		return _mm512_castpd_ps(_mm512_permutex2var_pd(_mm512_castps_pd(lo4), idxlo, _mm512_castps_pd(hi4)));
	}

	template <>
	inline reg interleavelo<int64_t>(const reg v1, const reg v2) {
		auto lo4 = mipp::interleavelo4<int64_t>(v1, v2);
		auto hi4 = mipp::interleavehi4<int64_t>(v1, v2);
		auto idxlo = _mm512_set_epi64(8|3,8|2,
		                                3,  2,
		                              8|1,8|0,
		                                1,  0);
		return _mm512_castpd_ps(_mm512_permutex2var_pd(_mm512_castps_pd(lo4), idxlo, _mm512_castps_pd(hi4)));
	}

	template <>
	inline reg interleavelo<int32_t>(const reg v1, const reg v2) {
		auto lo4 = mipp::interleavelo4<int32_t>(v1, v2);
		auto hi4 = mipp::interleavehi4<int32_t>(v1, v2);
		auto idxlo = _mm512_set_epi64(8|3,8|2,
		                                3,  2,
		                              8|1,8|0,
		                                1,  0);
		return _mm512_castpd_ps(_mm512_permutex2var_pd(_mm512_castps_pd(lo4), idxlo, _mm512_castps_pd(hi4)));
	}
#endif

#if defined(__AVX512BW__)
	template <>
	inline reg interleavelo<int16_t>(const reg v1, const reg v2) {
		auto lo4 = mipp::interleavelo4<int16_t>(v1, v2);
		auto hi4 = mipp::interleavehi4<int16_t>(v1, v2);
		auto idxlo = _mm512_set_epi64(8|3,8|2,
		                                3,  2,
		                              8|1,8|0,
		                                1,  0);
		return _mm512_castpd_ps(_mm512_permutex2var_pd(_mm512_castps_pd(lo4), idxlo, _mm512_castps_pd(hi4)));
	}

	template <>
	inline reg interleavelo<int8_t>(const reg v1, const reg v2) {
		auto lo4 = mipp::interleavelo4<int8_t>(v1, v2);
		auto hi4 = mipp::interleavehi4<int8_t>(v1, v2);
		auto idxlo = _mm512_set_epi64(8|3,8|2,
		                                3,  2,
		                              8|1,8|0,
		                                1,  0);
		return _mm512_castpd_ps(_mm512_permutex2var_pd(_mm512_castps_pd(lo4), idxlo, _mm512_castps_pd(hi4)));
	}
#endif

	// --------------------------------------------------------------------------------------------------- interleavehi
#if defined(__AVX512F__)
	template <>
	inline reg interleavehi<double>(const reg v1, const reg v2) {
		auto lo4 = mipp::interleavelo4<double>(v1, v2);
		auto hi4 = mipp::interleavehi4<double>(v1, v2);
		auto idxhi = _mm512_set_epi64(8|7,8|6,
		                                7,  6,
		                              8|5,8|4,
		                                5,  4);
		return _mm512_castpd_ps(_mm512_permutex2var_pd(_mm512_castps_pd(lo4), idxhi, _mm512_castps_pd(hi4)));
	}

	template <>
	inline reg interleavehi<float>(const reg v1, const reg v2) {
		auto lo4 = mipp::interleavelo4<float>(v1, v2);
		auto hi4 = mipp::interleavehi4<float>(v1, v2);
		auto idxhi = _mm512_set_epi64(8|7,8|6,
		                                7,  6,
		                              8|5,8|4,
		                                5,  4);
		return _mm512_castpd_ps(_mm512_permutex2var_pd(_mm512_castps_pd(lo4), idxhi, _mm512_castps_pd(hi4)));
	}

	template <>
	inline reg interleavehi<int64_t>(const reg v1, const reg v2) {
		auto lo4 = mipp::interleavelo4<int64_t>(v1, v2);
		auto hi4 = mipp::interleavehi4<int64_t>(v1, v2);
		auto idxhi = _mm512_set_epi64(8|7,8|6,
		                                7,  6,
		                              8|5,8|4,
		                                5,  4);
		return _mm512_castpd_ps(_mm512_permutex2var_pd(_mm512_castps_pd(lo4), idxhi, _mm512_castps_pd(hi4)));
	}

	template <>
	inline reg interleavehi<int32_t>(const reg v1, const reg v2) {
		auto lo4 = mipp::interleavelo4<int32_t>(v1, v2);
		auto hi4 = mipp::interleavehi4<int32_t>(v1, v2);
		auto idxhi = _mm512_set_epi64(8|7,8|6,
		                                7,  6,
		                              8|5,8|4,
		                                5,  4);
		return _mm512_castpd_ps(_mm512_permutex2var_pd(_mm512_castps_pd(lo4), idxhi, _mm512_castps_pd(hi4)));
	}
#endif

#if defined(__AVX512BW__)
	template <>
	inline reg interleavehi<int16_t>(const reg v1, const reg v2) {
		auto lo4 = mipp::interleavelo4<int16_t>(v1, v2);
		auto hi4 = mipp::interleavehi4<int16_t>(v1, v2);
		auto idxhi = _mm512_set_epi64(8|7,8|6,
		                                7,  6,
		                              8|5,8|4,
		                                5,  4);
		return _mm512_castpd_ps(_mm512_permutex2var_pd(_mm512_castps_pd(lo4), idxhi, _mm512_castps_pd(hi4)));
	}

	template <>
	inline reg interleavehi<int8_t>(const reg v1, const reg v2) {
		auto lo4 = mipp::interleavelo4<int8_t>(v1, v2);
		auto hi4 = mipp::interleavehi4<int8_t>(v1, v2);
		auto idxhi = _mm512_set_epi64(8|7,8|6,
		                                7,  6,
		                              8|5,8|4,
		                                5,  4);
		return _mm512_castpd_ps(_mm512_permutex2var_pd(_mm512_castps_pd(lo4), idxhi, _mm512_castps_pd(hi4)));
	}
#endif

	// ---------------------------------------------------------------------------------------------------- interleave2
#if defined(__AVX512F__)
	template <>
	inline regx2 interleave2<double>(const reg v1, const reg v2) {
		auto lo4 = mipp::interleavelo4<double>(v1, v2);
		auto hi4 = mipp::interleavehi4<double>(v1, v2);
		auto idxlo = _mm512_set_epi64(8|5,8|4,
		                                5,  4,
		                              8|1,8|0,
		                                1,  0);
		auto idxhi = _mm512_set_epi64(8|7,8|6,
		                                7,  6,
		                              8|3,8|2,
		                                3,  2);
		return {{_mm512_castpd_ps(_mm512_permutex2var_pd(_mm512_castps_pd(lo4), idxlo, _mm512_castps_pd(hi4))),
		         _mm512_castpd_ps(_mm512_permutex2var_pd(_mm512_castps_pd(lo4), idxhi, _mm512_castps_pd(hi4)))}};
	}

	template <>
	inline regx2 interleave2<float>(const reg v1, const reg v2) {
		auto lo4 = mipp::interleavelo4<float>(v1, v2);
		auto hi4 = mipp::interleavehi4<float>(v1, v2);
		auto idxlo = _mm512_set_epi64(8|5,8|4,
		                                5,  4,
		                              8|1,8|0,
		                                1,  0);
		auto idxhi = _mm512_set_epi64(8|7,8|6,
		                                7,  6,
		                              8|3,8|2,
		                                3,  2);
		return {{_mm512_castpd_ps(_mm512_permutex2var_pd(_mm512_castps_pd(lo4), idxlo, _mm512_castps_pd(hi4))),
		         _mm512_castpd_ps(_mm512_permutex2var_pd(_mm512_castps_pd(lo4), idxhi, _mm512_castps_pd(hi4)))}};
	}

	template <>
	inline regx2 interleave2<int64_t>(const reg v1, const reg v2) {
		auto lo4 = mipp::interleavelo4<int64_t>(v1, v2);
		auto hi4 = mipp::interleavehi4<int64_t>(v1, v2);
		auto idxlo = _mm512_set_epi64(8|5,8|4,
		                                5,  4,
		                              8|1,8|0,
		                                1,  0);
		auto idxhi = _mm512_set_epi64(8|7,8|6,
		                                7,  6,
		                              8|3,8|2,
		                                3,  2);
		return {{_mm512_castpd_ps(_mm512_permutex2var_pd(_mm512_castps_pd(lo4), idxlo, _mm512_castps_pd(hi4))),
		         _mm512_castpd_ps(_mm512_permutex2var_pd(_mm512_castps_pd(lo4), idxhi, _mm512_castps_pd(hi4)))}};
	}

	template <>
	inline regx2 interleave2<int32_t>(const reg v1, const reg v2) {
		auto lo4 = mipp::interleavelo4<int32_t>(v1, v2);
		auto hi4 = mipp::interleavehi4<int32_t>(v1, v2);
		auto idxlo = _mm512_set_epi64(8|5,8|4,
		                                5,  4,
		                              8|1,8|0,
		                                1,  0);
		auto idxhi = _mm512_set_epi64(8|7,8|6,
		                                7,  6,
		                              8|3,8|2,
		                                3,  2);
		return {{_mm512_castpd_ps(_mm512_permutex2var_pd(_mm512_castps_pd(lo4), idxlo, _mm512_castps_pd(hi4))),
		         _mm512_castpd_ps(_mm512_permutex2var_pd(_mm512_castps_pd(lo4), idxhi, _mm512_castps_pd(hi4)))}};
	}
#endif

#if defined(__AVX512BW__)
	template <>
	inline regx2 interleave2<int16_t>(const reg v1, const reg v2) {
		auto lo4 = mipp::interleavelo4<int16_t>(v1, v2);
		auto hi4 = mipp::interleavehi4<int16_t>(v1, v2);
		auto idxlo = _mm512_set_epi64(8|5,8|4,
		                                5,  4,
		                              8|1,8|0,
		                                1,  0);
		auto idxhi = _mm512_set_epi64(8|7,8|6,
		                                7,  6,
		                              8|3,8|2,
		                                3,  2);
		return {{_mm512_castpd_ps(_mm512_permutex2var_pd(_mm512_castps_pd(lo4), idxlo, _mm512_castps_pd(hi4))),
		         _mm512_castpd_ps(_mm512_permutex2var_pd(_mm512_castps_pd(lo4), idxhi, _mm512_castps_pd(hi4)))}};
	}

	template <>
	inline regx2 interleave2<int8_t>(const reg v1, const reg v2) {
		auto lo4 = mipp::interleavelo4<int8_t>(v1, v2);
		auto hi4 = mipp::interleavehi4<int8_t>(v1, v2);
		auto idxlo = _mm512_set_epi64(8|5,8|4,
		                                5,  4,
		                              8|1,8|0,
		                                1,  0);
		auto idxhi = _mm512_set_epi64(8|7,8|6,
		                                7,  6,
		                              8|3,8|2,
		                                3,  2);
		return {{_mm512_castpd_ps(_mm512_permutex2var_pd(_mm512_castps_pd(lo4), idxlo, _mm512_castps_pd(hi4))),
		         _mm512_castpd_ps(_mm512_permutex2var_pd(_mm512_castps_pd(lo4), idxhi, _mm512_castps_pd(hi4)))}};
	}
#endif

	// ---------------------------------------------------------------------------------------------------- interleave4
#if defined(__AVX512F__)
	template <>
	inline regx2 interleave4<double>(const reg v1, const reg v2) {
		return {{mipp::interleavelo4<double>(v1, v2),
		         mipp::interleavehi4<double>(v1, v2)}};
	}

	template <>
	inline regx2 interleave4<float>(const reg v1, const reg v2) {
		return {{mipp::interleavelo4<float>(v1, v2),
		         mipp::interleavehi4<float>(v1, v2)}};
	}

	template <>
	inline regx2 interleave4<int64_t>(const reg v1, const reg v2) {
		return {{mipp::interleavelo4<int64_t>(v1, v2),
		         mipp::interleavehi4<int64_t>(v1, v2)}};
	}

	template <>
	inline regx2 interleave4<int32_t>(const reg v1, const reg v2) {
		return {{mipp::interleavelo4<int32_t>(v1, v2),
		         mipp::interleavehi4<int32_t>(v1, v2)}};
	}
#endif

#if defined(__AVX512BW__)
	template <>
	inline regx2 interleave4<int16_t>(const reg v1, const reg v2) {
		return {{mipp::interleavelo4<int16_t>(v1, v2),
		         mipp::interleavehi4<int16_t>(v1, v2)}};
	}

	template <>
	inline regx2 interleave4<int8_t>(const reg v1, const reg v2) {
		return {{mipp::interleavelo4<int8_t>(v1, v2),
		         mipp::interleavehi4<int8_t>(v1, v2)}};
	}
#endif

	// --------------------------------------------------------------------------------------------------- interleavex2

	// --------------------------------------------------------------------------------------------------- interleavex4

	// -------------------------------------------------------------------------------------------------- interleavex16

	// ------------------------------------------------------------------------------------------------------ transpose

	// ----------------------------------------------------------------------------------------------------- transpose2

	// -------------------------------------------------------------------------------------------------- transpose28x8

	// ------------------------------------------------------------------------------------------------------- compress
#if defined(__AVX512F__)
	template <> inline reg compress<double>(const reg v, const msk m) {
		return _mm512_castpd_ps(_mm512_maskz_compress_pd((__mmask8)m, _mm512_castps_pd(v)));
	}

	template <>
	inline reg compress<float>(const reg v, const msk m) {
		return _mm512_maskz_compress_ps((__mmask16)m, v);
	}

	template <>
	inline reg compress<int64_t>(const reg v, const msk m) {
		return _mm512_castsi512_ps(_mm512_maskz_compress_epi64((__mmask8)m, _mm512_castps_si512(v)));
	}

	template <>
	inline reg compress<int32_t>(const reg v, const msk m) {
		return _mm512_castsi512_ps(_mm512_maskz_compress_epi32((__mmask16)m, _mm512_castps_si512(v)));
	}
#endif

#if defined(__AVX512VBMI2__)
	template <>
	inline reg compress<int16_t>(const reg v, const msk m) {
		return _mm512_castsi512_ps(_mm512_maskz_compress_epi16((__mmask32)m, _mm512_castps_si512(v)));
	}

	template <>
	inline reg compress<int8_t>(const reg v, const msk m) {
		return _mm512_castsi512_ps(_mm512_maskz_compress_epi8((__mmask64)m, _mm512_castps_si512(v)));
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- andb
	template <>
	inline reg andb<double>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_and_si512(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg andb<float>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_and_si512(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg andb<int64_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_and_si512(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg andb<int32_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_and_si512(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg andb<int16_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_and_si512(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg andb<int8_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_and_si512(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	// ---------------------------------------------------------------------------------------------------- andb (mask)
	template <>
	inline msk andb<8>(const msk v1, const msk v2) {
		return _mm512_kand(v1, v2);
	}

	template <>
	inline msk andb<16>(const msk v1, const msk v2) {
		return _mm512_kand(v1, v2);
	}

#if defined(__AVX512BW__)
	template <>
	inline msk andb<32>(const msk v1, const msk v2) {
		// return _mm512_kand(v1, v2);
		return v1 & v2;
	}

	template <>
	inline msk andb<64>(const msk v1, const msk v2) {
		// return _mm512_kand(v1, v2);
		return v1 & v2;
	}
#endif

	// ---------------------------------------------------------------------------------------------------------- andnb
	template <>
	inline reg andnb<float>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_andnot_si512(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg andnb<double>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_andnot_si512(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg andnb<int64_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_andnot_si512(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg andnb<int32_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_andnot_si512(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg andnb<int16_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_andnot_si512(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg andnb<int8_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_andnot_si512(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	// --------------------------------------------------------------------------------------------------- andnb (mask)
	template <>
	inline msk andnb<8>(const msk v1, const msk v2) {
		return _mm512_kandn(v1, v2);
	}

	template <>
	inline msk andnb<16>(const msk v1, const msk v2) {
		return _mm512_kandn(v1, v2);
	}

#if defined(__AVX512BW__)
	template <>
	inline msk andnb<32>(const msk v1, const msk v2) {
		// return _mm512_kandn(v1, v2);
		return (~v1) & v2;
	}

	template <>
	inline msk andnb<64>(const msk v1, const msk v2) {
		// return _mm512_kandn(v1, v2);
		return (~v1) & v2;
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- notb
	template <>
	inline reg notb<double>(const reg v) {
		return andnb<double>(v, set1<int64_t>(0xFFFFFFFFFFFFFFFF));
	}

	template <>
	inline reg notb<float>(const reg v) {
		return andnb<float>(v, set1<int32_t>(0xFFFFFFFF));
	}

	template <>
	inline reg notb<int64_t>(const reg v) {
		return andnb<int64_t>(v, set1<int64_t>(0xFFFFFFFFFFFFFFFF));
	}

	template <>
	inline reg notb<int32_t>(const reg v) {
		return andnb<int32_t>(v, set1<int32_t>(0xFFFFFFFF));
	}

	template <>
	inline reg notb<int16_t>(const reg v) {
#ifdef _MSC_VER
#pragma warning( disable : 4309 )
#endif
		return andnb<int16_t>(v, set1<int16_t>(0xFFFF));
#ifdef _MSC_VER
#pragma warning( default : 4309 )
#endif
	}

	template <>
	inline reg notb<int8_t>(const reg v) {
#ifdef _MSC_VER
#pragma warning( disable : 4309 )
#endif
		return andnb<int8_t>(v, set1<int8_t>(0xFF));
#ifdef _MSC_VER
#pragma warning( default : 4309 )
#endif
	}

	// ---------------------------------------------------------------------------------------------------- notb (mask)
	template <>
	inline msk notb<8>(const msk v) {
		return _mm512_knot(v);
	}

	template <>
	inline msk notb<16>(const msk v) {
		return _mm512_knot(v);
	}

#if defined(__AVX512BW__)
	template <>
	inline msk notb<32>(const msk v) {
		// return _mm512_knot(v);
		return ~v;
	}

	template <>
	inline msk notb<64>(const msk v) {
		// return _mm512_knot(v);
		return ~v;
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ orb
	template <>
	inline reg orb<float>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_or_si512(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg orb<double>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_or_si512(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg orb<int64_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_or_si512(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg orb<int32_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_or_si512(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg orb<int16_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_or_si512(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg orb<int8_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_or_si512(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	// ----------------------------------------------------------------------------------------------------- orb (mask)
	template <>
	inline msk orb<8>(const msk v1, const msk v2) {
		return _mm512_kor(v1, v2);
	}

	template <>
	inline msk orb<16>(const msk v1, const msk v2) {
		return _mm512_kor(v1, v2);
	}

#if defined(__AVX512BW__)
	template <>
	inline msk orb<32>(const msk v1, const msk v2) {
		// return _mm512_kor(v1, v2);
		return v1 | v2;
	}

	template <>
	inline msk orb<64>(const msk v1, const msk v2) {
		// return _mm512_kor(v1, v2);
		return v1 | v2;
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- xorb
	template <>
	inline reg xorb<float>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_xor_si512(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg xorb<double>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_xor_si512(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg xorb<int64_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_xor_si512(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg xorb<int32_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_xor_si512(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg xorb<int16_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_xor_si512(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg xorb<int8_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_xor_si512(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	// ---------------------------------------------------------------------------------------------------- xorb (mask)
	template <>
	inline msk xorb<8>(const msk v1, const msk v2) {
		return _mm512_kxor(v1, v2);
	}

	template <>
	inline msk xorb<16>(const msk v1, const msk v2) {
		return _mm512_kxor(v1, v2);
	}

#if defined(__AVX512BW__)
	template <>
	inline msk xorb<32>(const msk v1, const msk v2) {
		// return _mm512_kxor(v1, v2);
		return v1 ^ v2;
	}

	template <>
	inline msk xorb<64>(const msk v1, const msk v2) {
		// return _mm512_kxor(v1, v2);
		return v1 ^ v2;
	}
#endif

	// --------------------------------------------------------------------------------------------------------- lshift
#if defined(__AVX512F__)
	template <>
	inline reg lshift<double>(const reg v1, const uint32_t n) {
		return _mm512_castsi512_ps(_mm512_slli_epi64(_mm512_castps_si512(v1), n));
	}
#endif

	template <>
	inline reg lshift<float>(const reg v1, const uint32_t n) {
		return _mm512_castsi512_ps(_mm512_slli_epi32(_mm512_castps_si512(v1), n));
	}

#if defined(__AVX512F__)
	template <>
	inline reg lshift<int64_t>(const reg v1, const uint32_t n) {
		return _mm512_castsi512_ps(_mm512_slli_epi64(_mm512_castps_si512(v1), n));
	}
#endif

	template <>
	inline reg lshift<int32_t>(const reg v1, const uint32_t n) {
		return _mm512_castsi512_ps(_mm512_slli_epi32(_mm512_castps_si512(v1), n));
	}

#if defined(__AVX512BW__)
	template <>
	inline reg lshift<int16_t>(const reg v1, const uint32_t n) {
		return _mm512_castsi512_ps(_mm512_slli_epi16(_mm512_castps_si512(v1), n));
	}

	template <>
	inline reg lshift<int8_t>(const reg v1, const uint32_t n) {
		auto msk = set1<int8_t>((1 << n) -1);
		reg lsh = lshift<int16_t>(v1, n);
		lsh = andnb<int16_t>(msk, lsh);
		return lsh;
	}
#endif

	// -------------------------------------------------------------------------------------------------------- lshiftr
#if defined(__AVX512F__)
	template <>
	inline reg lshiftr<int64_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_sllv_epi64(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}
#endif

#if defined(__AVX512F__) || defined(__MIC__) || defined(__KNCNI__)
	template <>
	inline reg lshiftr<int32_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_sllv_epi32(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}
#endif

#if defined(__AVX512F__)
	template <>
	inline reg lshiftr<int16_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_sllv_epi16(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}
#endif

	// -------------------------------------------------------------------------------------------------- lshift (mask)
	template <>
	inline msk lshift<8>(const msk v1, const uint32_t n) {
		return v1 << n;
	}

	template <>
	inline msk lshift<16>(const msk v1, const uint32_t n) {
		return v1 << n;
	}

#if defined(__AVX512BW__) // TODO: /!\ the shift on 16-bit and 8-bit masks fails on ICPC
	template <>
	inline msk lshift<32>(const msk v1, const uint32_t n) {
		return v1 << n;
	}

	template <>
	inline msk lshift<64>(const msk v1, const uint32_t n) {
		return v1 << n;
	}
#endif

	// --------------------------------------------------------------------------------------------------------- rshift
#if defined(__AVX512F__)
	template <>
	inline reg rshift<double>(const reg v1, const uint32_t n) {
		return _mm512_castsi512_ps(_mm512_srli_epi64(_mm512_castps_si512(v1), n));
	}
#endif

	template <>
	inline reg rshift<float>(const reg v1, const uint32_t n) {
		return _mm512_castsi512_ps(_mm512_srli_epi32(_mm512_castps_si512(v1), n));
	}

#if defined(__AVX512F__)
	template <>
	inline reg rshift<int64_t>(const reg v1, const uint32_t n) {
		return _mm512_castsi512_ps(_mm512_srli_epi64(_mm512_castps_si512(v1), n));
	}
#endif

	template <>
	inline reg rshift<int32_t>(const reg v1, const uint32_t n) {
		return _mm512_castsi512_ps(_mm512_srli_epi32(_mm512_castps_si512(v1), n));
	}

#if defined(__AVX512BW__)
	template <>
	inline reg rshift<int16_t>(const reg v1, const uint32_t n) {
		return _mm512_castsi512_ps(_mm512_srli_epi16(_mm512_castps_si512(v1), n));
	}

	template <>
	inline reg rshift<int8_t>(const reg v1, const uint32_t n) {
		auto msk = set1<int8_t>((1 << (8 -n)) -1);
		reg rsh = rshift<int16_t>(v1, n);
		rsh = andb<int16_t>(msk, rsh);
		return rsh;
	}
#endif

	// -------------------------------------------------------------------------------------------------------- rshiftr
#if defined(__AVX512F__)
	template <>
	inline reg rshiftr<int64_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_srlv_epi64(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}
#endif

#if defined(__AVX512F__) || defined(__MIC__) || defined(__KNCNI__)
	template <>
	inline reg rshiftr<int32_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_srlv_epi32(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}
#endif

#if defined(__AVX512F__)
	template <>
	inline reg rshiftr<int16_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_srlv_epi16(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}
#endif

	// -------------------------------------------------------------------------------------------------- rshift (mask)
	template <>
	inline msk rshift<8>(const msk v1, const uint32_t n) {
		return v1 >> n;
	}

	template <>
	inline msk rshift<16>(const msk v1, const uint32_t n) {
		return v1 >> n;
	}

#if defined(__AVX512BW__) // TODO: /!\ the shift on 16-bit and 8-bit masks fails on ICPC
	template <>
	inline msk rshift<32>(const msk v1, const uint32_t n) {
		return v1 >> n;
	}

	template <>
	inline msk rshift<64>(const msk v1, const uint32_t n) {
		return v1 >> n;
	}
#endif

	// --------------------------------------------------------------------------------------------------------- cmpneq
	template <>
	inline msk cmpneq<double>(const reg v1, const reg v2) {
		return (msk) _mm512_cmp_pd_mask(_mm512_castps_pd(v1), _mm512_castps_pd(v2), _CMP_NEQ_OQ);
	}

	template <>
	inline msk cmpneq<float>(const reg v1, const reg v2) {
		return (msk) _mm512_cmp_ps_mask(v1, v2, _CMP_NEQ_OQ);
	}

#if defined(__AVX512F__)
	template <>
	inline msk cmpneq<int64_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmpneq_epi64_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}
#endif

	template <>
	inline msk cmpneq<int32_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmpneq_epi32_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}

#if defined(__AVX512BW__)
	template <>
	inline msk cmpneq<int16_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmpneq_epi16_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}

	template <>
	inline msk cmpneq<int8_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmpneq_epi8_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}
#endif

	// ---------------------------------------------------------------------------------------------------------- cmplt
	template <>
	inline msk cmplt<double>(const reg v1, const reg v2) {
		return (msk) _mm512_cmp_pd_mask(_mm512_castps_pd(v1), _mm512_castps_pd(v2), _CMP_LT_OS);
	}

	template <>
	inline msk cmplt<float>(const reg v1, const reg v2) {
		return (msk) _mm512_cmp_ps_mask(v1, v2, _CMP_LT_OS);
	}

#if defined(__AVX512F__)
	template <>
	inline msk cmplt<int64_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmplt_epi64_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}

	template <>
	inline msk cmplt<uint64_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmplt_epu64_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}
#endif

	template <>
	inline msk cmplt<int32_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmplt_epi32_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}

	template <>
	inline msk cmplt<uint32_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmplt_epu32_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}

#if defined(__AVX512BW__)
	template <>
	inline msk cmplt<int16_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmplt_epi16_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}

	template <>
	inline msk cmplt<uint16_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmplt_epu16_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}

	template <>
	inline msk cmplt<int8_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmplt_epi8_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}

	template <>
	inline msk cmplt<uint8_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmplt_epu8_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}
#endif

	// ---------------------------------------------------------------------------------------------------------- cmple
	template <>
	inline msk cmple<double>(const reg v1, const reg v2) {
		return (msk) _mm512_cmp_pd_mask(_mm512_castps_pd(v1), _mm512_castps_pd(v2), _CMP_LE_OS);
	}

	template <>
	inline msk cmple<float>(const reg v1, const reg v2) {
		return (msk) _mm512_cmp_ps_mask(v1, v2, _CMP_LE_OS);
	}

#if defined(__AVX512F__)
	template <>
	inline msk cmple<int64_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmple_epi64_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}

	template <>
	inline msk cmple<uint64_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmple_epu64_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}
#endif

	template <>
	inline msk cmple<int32_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmple_epi32_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}

	template <>
	inline msk cmple<uint32_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmple_epu32_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}

#if defined(__AVX512BW__)
	template <>
	inline msk cmple<int16_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmple_epi16_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}

	template <>
	inline msk cmple<uint16_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmple_epu16_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}

	template <>
	inline msk cmple<int8_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmple_epi8_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}

	template <>
	inline msk cmple<uint8_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmple_epu8_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}
#endif

	// ---------------------------------------------------------------------------------------------------------- cmpgt
	template <>
	inline msk cmpgt<double>(const reg v1, const reg v2) {
		return (msk) _mm512_cmp_pd_mask(_mm512_castps_pd(v1), _mm512_castps_pd(v2), _CMP_GT_OS);
	}

	template <>
	inline msk cmpgt<float>(const reg v1, const reg v2) {
		return (msk) _mm512_cmp_ps_mask(v1, v2, _CMP_GT_OS);
	}

#if defined(__AVX512F__)
	template <>
	inline msk cmpgt<int64_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmpgt_epi64_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}

	template <>
	inline msk cmpgt<uint64_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmpgt_epu64_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}
#endif

	template <>
	inline msk cmpgt<int32_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmpgt_epi32_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}

	template <>
	inline msk cmpgt<uint32_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmpgt_epu32_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}

#if defined(__AVX512BW__)
	template <>
	inline msk cmpgt<int16_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmpgt_epi16_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}

	template <>
	inline msk cmpgt<uint16_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmpgt_epu16_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}

	template <>
	inline msk cmpgt<int8_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmpgt_epi8_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}

	template <>
	inline msk cmpgt<uint8_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmpgt_epu8_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}
#endif

	// ---------------------------------------------------------------------------------------------------------- cmpge
	template <>
	inline msk cmpge<double>(const reg v1, const reg v2) {
		return (msk) _mm512_cmp_pd_mask(_mm512_castps_pd(v1), _mm512_castps_pd(v2), _CMP_GE_OS);
	}

	template <>
	inline msk cmpge<float>(const reg v1, const reg v2) {
		return (msk) _mm512_cmp_ps_mask(v1, v2, _CMP_GE_OS);
	}

#if defined(__AVX512F__)
	template <>
	inline msk cmpge<int64_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmpge_epi64_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}

	template <>
	inline msk cmpge<uint64_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmpge_epu64_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}
#endif

	template <>
	inline msk cmpge<int32_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmpge_epi32_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}

	template <>
	inline msk cmpge<uint32_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmpge_epu32_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}

#if defined(__AVX512BW__)
	template <>
	inline msk cmpge<int16_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmpge_epi16_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}

	template <>
	inline msk cmpge<uint16_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmpge_epu16_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}

	template <>
	inline msk cmpge<int8_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmpge_epi8_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}

	template <>
	inline msk cmpge<uint8_t>(const reg v1, const reg v2) {
		return (msk) _mm512_cmpge_epu8_mask(_mm512_castps_si512(v1), _mm512_castps_si512(v2));
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ add
	// ------------------ double
	template <>
	inline reg add<double>(const reg v1, const reg v2) {
		return _mm512_castpd_ps(_mm512_add_pd(_mm512_castps_pd(v1), _mm512_castps_pd(v2)));
	}

	template <>
	inline reg mask<double,add<double>>(const msk m, const reg src, const reg v1, const reg v2) {
		return _mm512_castpd_ps(_mm512_mask_add_pd(_mm512_castps_pd(src), (__mmask8)m, _mm512_castps_pd(v1), _mm512_castps_pd(v2)));
	}

	template <>
	inline Reg<double> mask<double,add<double>>(const Msk<8> m, const Reg<double> src, const Reg<double> v1, const Reg<double> v2) {
		return mask<double,add<double>>(m.m, src.r, v1.r, v2.r);
	}

#if defined(__AVX512F__)
	template <>
	inline reg maskz<double,add<double>>(const msk m, const reg v1, const reg v2) {
		return _mm512_castpd_ps(_mm512_maskz_add_pd((__mmask8)m, _mm512_castps_pd(v1), _mm512_castps_pd(v2)));
	}

	template <>
	inline Reg<double> maskz<double,add<double>>(const Msk<8> m, const Reg<double> v1, const Reg<double> v2) {
		return maskz<double,add<double>>(m.m, v1.r, v2.r);
	}
#endif

	// ------------------ float
	template <>
	inline reg add<float>(const reg v1, const reg v2) {
		return _mm512_add_ps(v1, v2);
	}

	template <>
	inline reg mask<float,add<float>>(const msk m, const reg src, const reg v1, const reg v2) {
		return _mm512_mask_add_ps(src, (__mmask16)m, v1, v2);
	}

	template <>
	inline Reg<float> mask<float,add<float>>(const Msk<16> m, const Reg<float> src, const Reg<float> v1, const Reg<float> v2) {
		return mask<float,add<float>>(m.m, src.r, v1.r, v2.r);
	}

#if defined(__AVX512F__)
	template <>
	inline reg maskz<float,add<float>>(const msk m, const reg v1, const reg v2) {
		return _mm512_maskz_add_ps((__mmask16)m, v1, v2);
	}

	template <>
	inline Reg<float> maskz<float,add<float>>(const Msk<16> m, const Reg<float> v1, const Reg<float> v2) {
		return maskz<float,add<float>>(m.m, v1.r, v2.r);
	}
#endif

	// ------------------ int64
#if defined(__AVX512F__)
	template <>
	inline reg add<int64_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_add_epi64(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg mask<int64_t,add<int64_t>>(const msk m, const reg src, const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_mask_add_epi64(_mm512_castps_si512(src), (__mmask8)m, _mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline Reg<int64_t> mask<int64_t,add<int64_t>>(const Msk<8> m, const Reg<int64_t> src, const Reg<int64_t> v1, const Reg<int64_t> v2) {
		return mask<int64_t,add<int64_t>>(m.m, src.r, v1.r, v2.r);
	}

	template <>
	inline reg maskz<int64_t,add<int64_t>>(const msk m, const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_maskz_add_epi64((__mmask8)m, _mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline Reg<int64_t> maskz<int64_t,add<int64_t>>(const Msk<8> m, const Reg<int64_t> v1, const Reg<int64_t> v2) {
		return maskz<int64_t,add<int64_t>>(m.m, v1.r, v2.r);
	}
#endif

	// ------------------ int32
	template <>
	inline reg add<int32_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_add_epi32(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

#if defined(__AVX2__)
 	template <>
	inline reg_2 add<int32_t>(const reg_2 v1, const reg_2 v2) {
		return _mm256_castsi256_ps(_mm256_add_epi32(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}
#endif
	template <>
	inline reg mask<int32_t,add<int32_t>>(const msk m, const reg src, const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_mask_add_epi32(_mm512_castps_si512(src), (__mmask16)m, _mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline Reg<int32_t> mask<int32_t,add<int32_t>>(const Msk<16> m, const Reg<int32_t> src, const Reg<int32_t> v1, const Reg<int32_t> v2) {
		return mask<int32_t,add<int32_t>>(m.m, src.r, v1.r, v2.r);
	}

#if defined(__AVX512F__)
	template <>
	inline reg maskz<int32_t,add<int32_t>>(const msk m, const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_maskz_add_epi32((__mmask16)m, _mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline Reg<int32_t> maskz<int32_t,add<int32_t>>(const Msk<16> m, const Reg<int32_t> v1, const Reg<int32_t> v2) {
		return maskz<int32_t,add<int32_t>>(m.m, v1.r, v2.r);
	}
#endif

#if defined(__AVX512BW__)
	// ------------------ int16
	template <>
	inline reg add<int16_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_adds_epi16(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg mask<int16_t,add<int16_t>>(const msk m, const reg src, const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_mask_adds_epi16(_mm512_castps_si512(src), (__mmask32)m, _mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline Reg<int16_t> mask<int16_t,add<int16_t>>(const Msk<32> m, const Reg<int16_t> src, const Reg<int16_t> v1, const Reg<int16_t> v2) {
		return mask<int16_t,add<int16_t>>(m.m, src.r, v1.r, v2.r);
	}

	template <>
	inline reg maskz<int16_t,add<int16_t>>(const msk m, const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_maskz_adds_epi16((__mmask32)m, _mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline Reg<int16_t> maskz<int16_t,add<int16_t>>(const Msk<32> m, const Reg<int16_t> v1, const Reg<int16_t> v2) {
		return maskz<int16_t,add<int16_t>>(m.m, v1.r, v2.r);
	}

	// ------------------ uint16
	template <>
	inline reg add<uint16_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_adds_epu16(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg mask<uint16_t,add<uint16_t>>(const msk m, const reg src, const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_mask_adds_epu16(_mm512_castps_si512(src), (__mmask32)m, _mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline Reg<uint16_t> mask<uint16_t,add<uint16_t>>(const Msk<32> m, const Reg<uint16_t> src, const Reg<uint16_t> v1, const Reg<uint16_t> v2) {
		return mask<uint16_t,add<uint16_t>>(m.m, src.r, v1.r, v2.r);
	}

	template <>
	inline reg maskz<uint16_t,add<uint16_t>>(const msk m, const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_maskz_adds_epu16((__mmask32)m, _mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline Reg<uint16_t> maskz<uint16_t,add<uint16_t>>(const Msk<32> m, const Reg<uint16_t> v1, const Reg<uint16_t> v2) {
		return maskz<uint16_t,add<uint16_t>>(m.m, v1.r, v2.r);
	}

	// ------------------ int8
	template <>
	inline reg add<int8_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_adds_epi8(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg mask<int8_t,add<int8_t>>(const msk m, const reg src, const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_mask_adds_epi8(_mm512_castps_si512(src), (__mmask64)m, _mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline Reg<int8_t> mask<int8_t,add<int8_t>>(const Msk<64> m, const Reg<int8_t> src, const Reg<int8_t> v1, const Reg<int8_t> v2) {
		return mask<int8_t,add<int8_t>>(m.m, src.r, v1.r, v2.r);
	}

	template <>
	inline reg maskz<int8_t,add<int8_t>>(const msk m, const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_maskz_adds_epi8((__mmask64)m, _mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline Reg<int8_t> maskz<int8_t,add<int8_t>>(const Msk<64> m, const Reg<int8_t> v1, const Reg<int8_t> v2) {
		return maskz<int8_t,add<int8_t>>(m.m, v1.r, v2.r);
	}

	// ------------------ uint8
	template <>
	inline reg add<uint8_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_adds_epu8(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg mask<uint8_t,add<uint8_t>>(const msk m, const reg src, const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_mask_adds_epu8(_mm512_castps_si512(src), (__mmask64)m, _mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline Reg<uint8_t> mask<uint8_t,add<uint8_t>>(const Msk<64> m, const Reg<uint8_t> src, const Reg<uint8_t> v1, const Reg<uint8_t> v2) {
		return mask<uint8_t,add<uint8_t>>(m.m, src.r, v1.r, v2.r);
	}

	template <>
	inline reg maskz<uint8_t,add<uint8_t>>(const msk m, const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_maskz_adds_epu8((__mmask64)m, _mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline Reg<uint8_t> maskz<uint8_t,add<uint8_t>>(const Msk<64> m, const Reg<uint8_t> v1, const Reg<uint8_t> v2) {
		return maskz<uint8_t,add<uint8_t>>(m.m, v1.r, v2.r);
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ sub
	template <>
	inline reg sub<double>(const reg v1, const reg v2) {
		return _mm512_castpd_ps(_mm512_sub_pd(_mm512_castps_pd(v1), _mm512_castps_pd(v2)));
	}

	template <>
	inline reg sub<float>(const reg v1, const reg v2) {
		return _mm512_sub_ps(v1, v2);
	}

#if defined(__AVX512F__)
	template <>
	inline reg sub<int64_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_sub_epi64(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}
#endif

	template <>
	inline reg sub<int32_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_sub_epi32(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

#if defined(__AVX2__)
	template <>
	inline reg_2 sub<int32_t>(const reg_2 v1, const reg_2 v2) {
		return _mm256_castsi256_ps(_mm256_sub_epi32(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}
#endif

#if defined(__AVX512BW__)
	template <>
	inline reg sub<int16_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_subs_epi16(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg sub<uint16_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_subs_epu16(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg sub<int8_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_subs_epi8(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg sub<uint8_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_subs_epu8(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ mul
	template <>
	inline reg mul<double>(const reg v1, const reg v2) {
		return _mm512_castpd_ps(_mm512_mul_pd(_mm512_castps_pd(v1), _mm512_castps_pd(v2)));
	}

	template <>
	inline reg mul<float>(const reg v1, const reg v2) {
		return _mm512_mul_ps(v1, v2);
	}

	template <>
	inline reg mul<int32_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_mullo_epi32(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

#if defined(__AVX2__)
	template <>
	inline reg_2 mul<int32_t>(const reg_2 v1, const reg_2 v2) {
		return _mm256_castsi256_ps(_mm256_mullo_epi32(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}
#endif

#if defined(__AVX512BW__)
	template <>
	inline reg mul<int16_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_mullo_epi16(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ div
#if defined(__AVX512F__)
	template <>
	inline reg div<double>(const reg v1, const reg v2) {
		return _mm512_castpd_ps(_mm512_div_pd(_mm512_castps_pd(v1), _mm512_castps_pd(v2)));
	}

	template <>
	inline reg div<float>(const reg v1, const reg v2) {
		return _mm512_div_ps(v1, v2);
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ min
#if defined(__AVX512F__)
	template <>
	inline reg min<double>(const reg v1, const reg v2) {
		return _mm512_castpd_ps(_mm512_min_pd(_mm512_castps_pd(v1), _mm512_castps_pd(v2)));
	}

	template <>
	inline reg min<float>(const reg v1, const reg v2) {
		return _mm512_min_ps(v1, v2);
	}

	template <>
	inline reg min<int64_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_min_epi64(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg min<uint64_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_min_epu64(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg min<int32_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_min_epi32(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg min<uint32_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_min_epu32(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

#if defined(__AVX512BW__)
	template <>
	inline reg min<int16_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_min_epi16(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg min<uint16_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_min_epu16(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg min<int8_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_min_epi8(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg min<uint8_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_min_epu8(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}
#endif

#elif defined(__MIC__) || defined(__KNCNI__)
	template <>
	inline reg min<double>(const reg v1, const reg v2) {
		return _mm512_castpd_ps(_mm512_gmin_pd(_mm512_castps_pd(v1), _mm512_castps_pd(v2)));
	}

	template <>
	inline reg min<float>(const reg v1, const reg v2) {
		return _mm512_gmin_ps(v1, v2);
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ max
#if defined(__AVX512F__)
	template <>
	inline reg max<double>(const reg v1, const reg v2) {
		return _mm512_castpd_ps(_mm512_max_pd(_mm512_castps_pd(v1), _mm512_castps_pd(v2)));
	}

	template <>
	inline reg max<float>(const reg v1, const reg v2) {
		return _mm512_max_ps(v1, v2);
	}

	template <>
	inline reg max<int64_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_max_epi64(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg max<uint64_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_max_epu64(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg max<int32_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_max_epi32(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg max<uint32_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_max_epu32(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

#if defined(__AVX512BW__)
	template <>
	inline reg max<int16_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_max_epi16(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg max<uint16_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_max_epu16(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg max<int8_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_max_epi8(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}

	template <>
	inline reg max<uint8_t>(const reg v1, const reg v2) {
		return _mm512_castsi512_ps(_mm512_max_epu8(_mm512_castps_si512(v1), _mm512_castps_si512(v2)));
	}
#endif

#elif defined(__MIC__) || defined(__KNCNI__)
	template <>
	inline reg max<double>(const reg v1, const reg v2) {
		return _mm512_castpd_ps(_mm512_gmax_pd(_mm512_castps_pd(v1), _mm512_castps_pd(v2)));
	}

	template <>
	inline reg min<float>(const reg v1, const reg v2) {
		return _mm512_gmax_ps(v1, v2);
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ msb
	template <>
	inline reg msb<double>(const reg v1) {
		// msb_mask = 1000000000000000000000000000000000000000000000000000000000000000 // 64 bits
		const reg msb_mask = set1<int64_t>(0x8000000000000000);

		// indices = 63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34 33 32...
		// mask    =  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0...
		// v1      =  ù  €  è  é  à  &  z  y  x  w  v  u  t  s  r  q  p  o  n  m  l  k  j  i  h  g  f  e  d  c  b  a...
		// res     =  ù  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0...
		return andb<double>(v1, msb_mask);
	}

	template <>
	inline reg msb<double>(const reg v1, const reg v2) {
		reg msb_v1_v2 = xorb<double>(v1, v2);
		    msb_v1_v2 = msb<double>(msb_v1_v2);
		return msb_v1_v2;
	}

	template <>
	inline reg msb<float>(const reg v1) {
		// msb_mask = 10000000000000000000000000000000 // 32 bits
		const reg msb_mask = set1<int32_t>(0x80000000);

		// indices = 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
		// mask    =  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
		// v1      =  ù  €  è  é  à  &  z  y  x  w  v  u  t  s  r  q  p  o  n  m  l  k  j  i  h  g  f  e  d  c  b  a
		// res     =  ù  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
		return andb<float>(v1, msb_mask);
	}

	template <>
	inline reg msb<float>(const reg v1, const reg v2) {
		reg msb_v1_v2 = xorb<float>(v1, v2);
		    msb_v1_v2 = msb<float>(msb_v1_v2);
		return msb_v1_v2;
	}

	template <>
	inline reg msb<int16_t>(const reg v1) {
#ifdef _MSC_VER
#pragma warning( disable : 4309 )
#endif
		const reg msb_mask = set1<int16_t>(0x8000);
		return andb<int16_t>(v1, msb_mask);
#ifdef _MSC_VER
#pragma warning( default : 4309 )
#endif
	}

	template <>
	inline reg msb<int8_t>(const reg v1) {
#ifdef _MSC_VER
#pragma warning( disable : 4309 )
#endif
		// msb_mask = 10000000 // 8 bits
		const reg msb_mask = set1<int8_t>(0x80);
#ifdef _MSC_VER
#pragma warning( default : 4309 )
#endif
		// indices = 7  6  5  4  3  2  1  0
		// mask    = 1  0  0  0  0  0  0  0
		// v1      = h  g  f  e  d  c  b  a
		// res     = h  0  0  0  0  0  0  0
		return andb<int8_t>(v1, msb_mask);
	}

	template <>
	inline reg msb<int16_t>(const reg v1, const reg v2) {
		reg msb_v1_v2 = xorb<int16_t>(v1, v2);
		    msb_v1_v2 = msb<int16_t>(msb_v1_v2);
		return msb_v1_v2;
	}

	template <>
	inline reg msb<int8_t>(const reg v1, const reg v2) {
		reg msb_v1_v2 = xorb<int8_t>(v1, v2);
		    msb_v1_v2 = msb<int8_t>(msb_v1_v2);
		return msb_v1_v2;
	}

	// ----------------------------------------------------------------------------------------------------------- sign
	template <>
	inline msk sign<double>(const reg v1) {
		return cmplt<double>(v1, set0<double>());
	}

	template <>
	inline msk sign<float>(const reg v1) {
		return cmplt<float>(v1, set0<float>());
	}

	template <>
	inline msk sign<int64_t>(const reg v1) {
		return cmpgt<int64_t>(set0<int64_t>(), v1);
	}

	template <>
	inline msk sign<int32_t>(const reg v1) {
		return cmpgt<int32_t>(set0<int32_t>(), v1);
	}

	template <>
	inline msk sign<int16_t>(const reg v1) {
		return cmpgt<int16_t>(set0<int16_t>(), v1);
	}

	template <>
	inline msk sign<int8_t>(const reg v1) {
		return cmpgt<int8_t>(set0<int8_t>(), v1);
	}

	// ------------------------------------------------------------------------------------------------------------ neg
	template <>
	inline reg neg<double>(const reg v1, const reg v2) {
		return xorb<double>(v1, msb<double>(v2));
	}

	template <>
	inline reg neg<double>(const reg v1, const msk v2) {
		return neg<double>(v1, toreg<8>(v2));
	}

	template <>
	inline reg neg<float>(const reg v1, const reg v2) {
		return xorb<float>(v1, msb<float>(v2));
	}

	template <>
	inline reg neg<float>(const reg v1, const msk v2) {
		return neg<float>(v1, toreg<16>(v2));
	}

	template <>
	inline reg neg<int64_t>(const reg v1, const reg v2) {
		reg neg_v1 = mipp::sub<int64_t>(mipp::set0<int64_t>(), v1);
		reg v2_2   = mipp::orb<int64_t>(v2, set1<int64_t>(1)); // hack to avoid -0 case
		return mipp::blend<int64_t>(neg_v1, v1, mipp::cmplt<int64_t>(v2_2, set0<int64_t>()));
	}

	template <>
	inline reg neg<int64_t>(const reg v1, const msk v2) {
		return neg<int64_t>(v1, toreg<8>(v2));
	}

	template <>
	inline reg neg<int32_t>(const reg v1, const reg v2) {
		reg neg_v1 = mipp::sub<int32_t>(mipp::set0<int32_t>(), v1);
		reg v2_2   = mipp::orb<int32_t>(v2, set1<int32_t>(1)); // hack to avoid -0 case
		return mipp::blend<int32_t>(neg_v1, v1, mipp::cmplt<int32_t>(v2_2, set0<int32_t>()));
	}

	template <>
	inline reg neg<int32_t>(const reg v1, const msk v2) {
		return neg<int32_t>(v1, toreg<16>(v2));
	}

#if defined(__AVX512BW__)
	template <>
	inline reg neg<int16_t>(const reg v1, const reg v2) {
		reg neg_v1 = mipp::sub<int16_t>(mipp::set0<int16_t>(), v1);
		reg v2_2   = mipp::orb<int16_t>(v2, set1<int16_t>(1)); // hack to avoid -0 case
		return mipp::blend<int16_t>(neg_v1, v1, mipp::cmplt<int16_t>(v2_2, set0<int16_t>()));
	}

	template <>
	inline reg neg<int16_t>(const reg v1, const msk v2) {
		return neg<int16_t>(v1, toreg<32>(v2));
	}

	template <>
	inline reg neg<int8_t>(const reg v1, const reg v2) {
		reg neg_v1 = mipp::sub<int8_t>(mipp::set0<int8_t>(), v1);
		reg v2_2   = mipp::orb<int8_t>(v2, set1<int8_t>(1)); // hack to avoid -0 case
		return mipp::blend<int8_t>(neg_v1, v1, mipp::cmplt<int8_t>(v2_2, set0<int8_t>()));
	}

	template <>
	inline reg neg<int8_t>(const reg v1, const msk v2) {
		return neg<int8_t>(v1, toreg<64>(v2));
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ abs
	/* there is a bug in the GNU compiler, _mm512_abs_pd and _mm512_abs_ps are not defined...
	template <>
	inline reg abs<double>(const reg v1) {
		return _mm512_castpd_ps(_mm512_abs_pd(_mm512_castps_pd(v1)));
	}

	template <>
	inline reg abs<float>(const reg v1) {
		return _mm512_abs_ps(v1);
	}
	*/

	template <>
	inline reg abs<double>(const reg v1) {
		// abs_mask = 0111111111111111111111111111111111111111111111111111111111111111 // 64 bits
		const reg abs_mask = set1<int64_t>(0x7FFFFFFFFFFFFFFF);

		// indices = 63 62 61 60 59 58 57 56 55 54 53 52 51 50 49 48 47 46 45 44 43 42 41 40 39 38 37 36 35 34 33 32...
		// mask    =  0  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1...
		// v1      =  ù  €  è  é  à  &  z  y  x  w  v  u  t  s  r  q  p  o  n  m  l  k  j  i  h  g  f  e  d  c  b  a...
		// v1      =  0  €  è  é  à  &  z  y  x  w  v  u  t  s  r  q  p  o  n  m  l  k  j  i  h  g  f  e  d  c  b  a...
		// res is the sign because the first bit is the sign bit (0 = positive, 1 = negative)
		return andb<double>(v1, abs_mask);
	}

	template <>
	inline reg abs<float>(const reg v1) {
		// abs_mask = 01111111111111111111111111111111 // 32 bits
		const reg abs_mask = set1<int32_t>(0x7FFFFFFF);

		// indices = 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
		// mask    =  0  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1
		// v1      =  ù  €  è  é  à  &  z  y  x  w  v  u  t  s  r  q  p  o  n  m  l  k  j  i  h  g  f  e  d  c  b  a
		// v1      =  0  €  è  é  à  &  z  y  x  w  v  u  t  s  r  q  p  o  n  m  l  k  j  i  h  g  f  e  d  c  b  a
		// res is the sign because the first bit is the sign bit (0 = positive, 1 = negative)
		return andb<float>(v1, abs_mask);
	}

#if defined(__AVX512F__)
	template <>
	inline reg abs<int64_t>(const reg v1) {
		return _mm512_castsi512_ps(_mm512_abs_epi64(_mm512_castps_si512(v1)));
	}

	template <>
	inline reg abs<int32_t>(const reg v1) {
		return _mm512_castsi512_ps(_mm512_abs_epi32(_mm512_castps_si512(v1)));
	}
#endif

#if defined(__AVX512BW__)
	template <>
	inline reg abs<int16_t>(const reg v1) {
		return _mm512_castsi512_ps(_mm512_abs_epi16(_mm512_castps_si512(v1)));
	}

	template <>
	inline reg abs<int8_t>(const reg v1) {
		return _mm512_castsi512_ps(_mm512_abs_epi8(_mm512_castps_si512(v1)));
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- sqrt
#if defined(__AVX512F__)
	template <>
	inline reg sqrt<double>(const reg v1) {
		return _mm512_castpd_ps(_mm512_sqrt_pd(_mm512_castps_pd(v1)));
	}

	template <>
	inline reg sqrt<float>(const reg v1) {
		return _mm512_sqrt_ps(v1);
	}
#endif

	// ---------------------------------------------------------------------------------------------------------- rsqrt
#if defined(__AVX512ER__)
	template <>
	inline reg rsqrt<double>(const reg v1) {
		return _mm512_castpd_ps(_mm512_rsqrt28_pd(_mm512_castps_pd(v1)));
	}

	template <>
	inline reg rsqrt<float>(const reg v1) {
		return _mm512_rsqrt28_ps(v1);
	}

#elif defined(__AVX512F__)
	template <>
	inline reg rsqrt<double>(const reg v1) {
		return _mm512_castpd_ps(_mm512_rsqrt14_pd(_mm512_castps_pd(v1)));
	}

	template <>
	inline reg rsqrt<float>(const reg v1) {
		return _mm512_rsqrt14_ps(v1);
	}

#elif defined(__MIC__) || defined(__KNCNI__)
	template <>
	inline reg rsqrt<float>(const reg v1) {
		return _mm512_rsqrt23_ps(v1);
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ log
#if defined(__AVX512F__)
#if defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC)
	template <>
	inline reg log<double>(const reg v) {
		return _mm512_castpd_ps(_mm512_log_pd(_mm512_castps_pd(v)));
	}

	template <>
	inline reg log<float>(const reg v) {
		return _mm512_log_ps(v);
	}
#else
	template <>
	inline reg log<float>(const reg v) {
		auto v_bis = v;
		return log512_ps(v_bis);
	}
#endif
#endif

	// ------------------------------------------------------------------------------------------------------------ exp
#if defined(__AVX512F__)
#if defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC)
	template <>
	inline reg exp<double>(const reg v) {
		return _mm512_castpd_ps(_mm512_exp_pd(_mm512_castps_pd(v)));
	}

	template <>
	inline reg exp<float>(const reg v) {
		return _mm512_exp_ps(v);
	}
#else
	template <>
	inline reg exp<float>(const reg v) {
		auto v_bis = v;
		return exp512_ps(v_bis);
	}
#endif
#endif

	// ------------------------------------------------------------------------------------------------------------ sin
#if defined(__AVX512F__)
#if defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC)
	template <>
	inline reg sin<double>(const reg v) {
		return _mm512_castpd_ps(_mm512_sin_pd(_mm512_castps_pd(v)));
	}

	template <>
	inline reg sin<float>(const reg v) {
		return _mm512_sin_ps(v);
	}
#else
	template <>
	inline reg sin<float>(const reg v) {
		auto v_bis = v;
		return sin512_ps(v_bis);
	}
#endif
#endif

	// ------------------------------------------------------------------------------------------------------------ cos
#if defined(__AVX512F__)
#if defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC)
	template <>
	inline reg cos<double>(const reg v) {
		return _mm512_castpd_ps(_mm512_cos_pd(_mm512_castps_pd(v)));
	}

	template <>
	inline reg cos<float>(const reg v) {
		return _mm512_cos_ps(v);
	}
#else
	template <>
	inline reg cos<float>(const reg v) {
		auto v_bis = v;
		return cos512_ps(v_bis);
	}
#endif
#endif

	// --------------------------------------------------------------------------------------------------------- sincos
#if defined(__AVX512F__)
#if defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC)
	template <>
	inline void sincos<double>(const reg x, reg &s, reg &c) {
		s = (reg)_mm512_sincos_pd((__m512d*) &c, (__m512d)x);
	}

	template <>
	inline void sincos<float>(const reg x, reg &s, reg &c) {
		s = _mm512_sincos_ps(&c, x);
	}
#else
	template <>
	inline void sincos<float>(const reg x, reg &s, reg &c) {
		sincos512_ps(x, &s, &c);
	}
#endif
#endif

	// ---------------------------------------------------------------------------------------------------------- fmadd
	template <>
	inline reg fmadd<double>(const reg v1, const reg v2, const reg v3) {
		return _mm512_castpd_ps(_mm512_fmadd_pd(_mm512_castps_pd(v1), _mm512_castps_pd(v2), _mm512_castps_pd(v3)));
	}

	template <>
	inline reg fmadd<float>(const reg v1, const reg v2, const reg v3) {
		return _mm512_fmadd_ps(v1, v2, v3);
	}

#if defined(__MIC__) || defined(__KNCNI__)
	template <>
	inline reg fmadd<int32_t>(const reg v1, const reg v2, const reg v3) {
		return _mm512_castsi512_ps(_mm512_fmadd_epi32(_mm512_castps_si512(v1), _mm512_castps_si512(v2), _mm512_castps_si512(v3)));
	}
#endif

	// --------------------------------------------------------------------------------------------------------- fnmadd
	template <>
	inline reg fnmadd<double>(const reg v1, const reg v2, const reg v3) {
		return _mm512_castpd_ps(_mm512_fnmadd_pd(_mm512_castps_pd(v1), _mm512_castps_pd(v2), _mm512_castps_pd(v3)));
	}

	template <>
	inline reg fnmadd<float>(const reg v1, const reg v2, const reg v3) {
		return _mm512_fnmadd_ps(v1, v2, v3);
	}

	// ---------------------------------------------------------------------------------------------------------- fmsub
	template <>
	inline reg fmsub<double>(const reg v1, const reg v2, const reg v3) {
		return _mm512_castpd_ps(_mm512_fmsub_pd(_mm512_castps_pd(v1), _mm512_castps_pd(v2), _mm512_castps_pd(v3)));
	}

	template <>
	inline reg fmsub<float>(const reg v1, const reg v2, const reg v3) {
		return _mm512_fmsub_ps(v1, v2, v3);
	}

	// --------------------------------------------------------------------------------------------------------- fnmsub
	template <>
	inline reg fnmsub<double>(const reg v1, const reg v2, const reg v3) {
		return _mm512_castpd_ps(_mm512_fnmsub_pd(_mm512_castps_pd(v1), _mm512_castps_pd(v2), _mm512_castps_pd(v3)));
	}

	template <>
	inline reg fnmsub<float>(const reg v1, const reg v2, const reg v3) {
		return _mm512_fnmsub_ps(v1, v2, v3);
	}

	// ----------------------------------------------------------------------------------------------------------- lrot
#ifdef __AVX512F__
	template <>
	inline reg lrot<double>(const reg v1) {
		return _mm512_castpd_ps(_mm512_permutexvar_pd(_mm512_setr_epi64(1, 2, 3, 4, 5, 6, 7, 0), _mm512_castps_pd(v1)));
	}

	template <>
	inline reg lrot<float>(const reg v1) {
		return _mm512_permutexvar_ps(_mm512_setr_epi32(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0), v1);
	}

	template <>
	inline reg lrot<int64_t>(const reg v1) {
		return _mm512_castsi512_ps(_mm512_permutexvar_epi64(_mm512_setr_epi64(1, 2, 3, 4, 5, 6, 7, 0), _mm512_castps_si512(v1)));
	}

	template <>
	inline reg lrot<int32_t>(const reg v1) {
		return _mm512_castsi512_ps(_mm512_permutexvar_epi32(_mm512_setr_epi32(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0), _mm512_castps_si512(v1)));
	}
#endif

#ifdef __AVX512BW__
	template <>
	inline reg lrot<int16_t>(const reg v1) {
		// return _mm512_castsi512_ps(_mm512_permutexvar_epi16(_mm512_setr_epi16( 1,  2,  3,  4,  5,  6,  7,  8,
		//                                                                        9, 10, 11, 12, 13, 14, 15, 16,
		//                                                                       17, 18, 19, 20, 21, 22, 23, 24,
		//                                                                       25, 26, 27, 28, 29, 30, 31,  0), _mm512_castps_si512(v1)));

		return _mm512_castsi512_ps(_mm512_permutexvar_epi16(_mm512_set_epi16( 0, 31, 30, 29, 28, 27, 26, 25,
		                                                                     24, 23, 22, 21, 20, 19, 18, 17,
		                                                                     16, 15, 14, 13, 12, 11, 10,  9,
		                                                                      8,  7,  6,  5,  4,  3,  2,  1), _mm512_castps_si512(v1)));
	}
#endif

#ifdef __AVX512VBMI__
	template <>
	inline reg lrot<int8_t>(const reg v1) {
		// return _mm512_castsi512_ps(_mm512_permutexvar_epi8(_mm512_setr_epi8( 1,  2,  3,  4,  5,  6,  7,  8,
		//                                                                      9, 10, 11, 12, 13, 14, 15, 16,
		//                                                                     17, 18, 19, 20, 21, 22, 23, 24,
		//                                                                     25, 26, 27, 28, 29, 30, 31, 32,
		//                                                                     33, 34, 35, 36, 37, 38, 39, 40,
		//                                                                     41, 42, 43, 44, 45, 46, 47, 48,
		//                                                                     49, 50, 51, 52, 53, 54, 55, 56,
		//                                                                     57, 58, 59, 60, 61, 62, 63,  0), _mm512_castps_si512(v1)));

		return _mm512_castsi512_ps(_mm512_permutexvar_epi8(_mm512_set_epi8( 0, 63, 62, 61, 60, 59, 58, 57,
		                                                                   56, 55, 54, 53, 52, 51, 50, 49,
		                                                                   48, 47, 46, 45, 44, 43, 42, 41,
		                                                                   40, 39, 38, 37, 36, 35, 34, 33,
		                                                                   32, 31, 30, 29, 28, 27, 26, 25,
		                                                                   24, 23, 22, 21, 20, 19, 18, 17,
		                                                                   16, 15, 14, 13, 12, 11, 10,  9,
		                                                                    8,  7,  6,  5,  4,  3,  2,  1), _mm512_castps_si512(v1)));
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- rrot
#ifdef __AVX512F__
	template <>
	inline reg rrot<double>(const reg v1) {
		return _mm512_castpd_ps(_mm512_permutexvar_pd(_mm512_setr_epi64(7, 0, 1, 2, 3, 4, 5, 6), _mm512_castps_pd(v1)));
	}

	template <>
	inline reg rrot<float>(const reg v1) {
		return _mm512_permutexvar_ps(_mm512_setr_epi32(15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14), v1);
	}

	template <>
	inline reg rrot<int64_t>(const reg v1) {
		return _mm512_castsi512_ps(_mm512_permutexvar_epi64(_mm512_setr_epi64(7, 0, 1, 2, 3, 4, 5, 6), _mm512_castps_si512(v1)));
	}

	template <>
	inline reg rrot<int32_t>(const reg v1) {
		return _mm512_castsi512_ps(_mm512_permutexvar_epi32(_mm512_setr_epi32(15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14), _mm512_castps_si512(v1)));
	}
#endif

#ifdef __AVX512BW__
	template <>
	inline reg rrot<int16_t>(const reg v1) {
		// return _mm512_castsi512_ps(_mm512_permutexvar_epi16(_mm512_setr_epi16(31,  0,  1,  2,  3,  4,  5,  6,
		//                                                                        7,  8,  9, 10, 11, 12, 13, 14,
		//                                                                       15, 16, 17, 18, 19, 20, 21, 22,
		//                                                                       23, 24, 25, 26, 27, 28, 29, 30), _mm512_castps_si512(v1)));
		return _mm512_castsi512_ps(_mm512_permutexvar_epi16(_mm512_set_epi16(30, 29, 28, 27, 26, 25, 24, 23,
		                                                                     22, 21, 20, 19, 18, 17, 16, 15,
		                                                                     14, 13, 12, 11, 10,  9,  8,  7,
		                                                                      6,  5,  4,  3,  2,  1,  0, 31), _mm512_castps_si512(v1)));
	}
#endif

#ifdef __AVX512VBMI__
	template <>
	inline reg rrot<int8_t>(const reg v1) {
		// return _mm512_castsi512_ps(_mm512_permutexvar_epi8(_mm512_setr_epi8(63,  0,  1,  2,  3,  4,  5,  6,
		//                                                                      7,  8,  9, 10, 11, 12, 13, 14,
		//                                                                     15, 16, 17, 18, 19, 20, 21, 22,
		//                                                                     23, 24, 25, 26, 27, 28, 29, 30,
		//                                                                     31, 32, 33, 34, 35, 36, 37, 38,
		//                                                                     39, 40, 41, 42, 43, 44, 45, 46,
		//                                                                     47, 48, 49, 50, 51, 52, 53, 54,
		//                                                                     55, 56, 57, 58, 59, 60, 61, 62), _mm512_castps_si512(v1)));
		return _mm512_castsi512_ps(_mm512_permutexvar_epi8(_mm512_set_epi8(62, 61, 60, 59, 58, 57, 56, 55,
		                                                                   54, 53, 52, 51, 50, 49, 48, 47,
		                                                                   46, 45, 44, 43, 42, 41, 40, 39,
		                                                                   38, 37, 36, 35, 34, 33, 32, 31,
		                                                                   30, 29, 28, 27, 26, 25, 24, 23,
		                                                                   22, 21, 20, 19, 18, 17, 16, 15,
		                                                                   14, 13, 12, 11, 10,  9,  8,  7,
		                                                                    6,  5,  4,  3,  2,  1,  0, 63), _mm512_castps_si512(v1)));
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- div2
	template <>
	inline reg div2<float>(const reg v1) {
		return mul<float>(v1, set1<float>(0.5f));
	}

	template <>
	inline reg div2<double>(const reg v1) {
		return mul<double>(v1, set1<double>(0.5));
	}

	template <>
	inline reg div2<int64_t>(const reg v1) {
//		return _mm512_castsi512_ps(_mm512_srai_epi32(_mm512_castps_si512(v1), 1)); // seems to do not work
		reg abs_v1 = abs<int64_t>(v1);
		reg sh = rshift<int64_t>(abs_v1, 1);
		sh = neg<int64_t>(sh, v1);
		return sh;
	}

	template <>
	inline reg div2<int32_t>(const reg v1) {
//		return _mm512_castsi512_ps(_mm512_srai_epi32(_mm512_castps_si512(v1), 1)); // seems to do not work
		reg abs_v1 = abs<int32_t>(v1);
		reg sh = rshift<int32_t>(abs_v1, 1);
		sh = neg<int32_t>(sh, v1);
		return sh;
	}

#if defined(__AVX512BW__)
	template <>
	inline reg div2<int16_t>(const reg v1) {
//		return _mm512_castsi512_ps(_mm512_srai_epi16(_mm512_castps_si512(v1), 1)); // seems to do not work
		reg abs_v1 = abs<int16_t>(v1);
		reg sh = rshift<int16_t>(abs_v1, 1);
		sh = neg<int16_t>(sh, v1);
		return sh;
	}

	template <>
	inline reg div2<int8_t>(const reg v1) {
		reg abs_v1 = abs<int8_t>(v1);
		reg sh16 = rshift<int16_t>(abs_v1, 1);
		sh16 = andnb<int8_t>(set1<int8_t>(0x80), sh16);
		reg sh8 = neg<int8_t>(sh16, v1);
		return sh8;
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- div4
	template <>
	inline reg div4<float>(const reg v1) {
		return mul<float>(v1, set1<float>(0.25f));
	}

	template <>
	inline reg div4<double>(const reg v1) {
		return mul<double>(v1, set1<double>(0.25));
	}

	template <>
	inline reg div4<int64_t>(const reg v1) {
		// return _mm512_castsi512_ps(_mm512_srai_epi64(_mm512_castps_si512(v1), 2)); // seems to do not work
		reg abs_v1 = abs<int64_t>(v1);
		reg sh = rshift<int64_t>(abs_v1, 2);
		sh = neg<int64_t>(sh, v1);
		return sh;
	}

	template <>
	inline reg div4<int32_t>(const reg v1) {
		// return _mm512_castsi512_ps(_mm512_srai_epi32(_mm512_castps_si512(v1), 2)); // seems to do not work
		reg abs_v1 = abs<int32_t>(v1);
		reg sh = rshift<int32_t>(abs_v1, 2);
		sh = neg<int32_t>(sh, v1);
		return sh;
	}

#if defined(__AVX512BW__)
	template <>
	inline reg div4<int16_t>(const reg v1) {
		// return _mm512_castsi512_ps(_mm512_srai_epi16(_mm512_castps_si512(v1), 2)); // seems to do not work
		reg abs_v1 = abs<int16_t>(v1);
		reg sh = rshift<int16_t>(abs_v1, 2);
		sh = neg<int16_t>(sh, v1);
		return sh;
	}

	template <>
	inline reg div4<int8_t>(const reg v1) {
		reg abs_v1 = abs<int8_t>(v1);
		reg sh16 = rshift<int16_t>(abs_v1, 2);
		sh16 = andnb<int8_t>(set1<int8_t>(0xc0), sh16);
		reg sh8 = neg<int8_t>(sh16, v1);
		return sh8;
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ sat
	template <>
	inline reg sat<float>(const reg v1, float min, float max) {
		return mipp::min<float>(mipp::max<float>(v1, set1<float>(min)), set1<float>(max));
	}

	template <>
	inline reg sat<double>(const reg v1, double min, double max) {
		return mipp::min<double>(mipp::max<double>(v1, set1<double>(min)), set1<double>(max));
	}

	template <>
	inline reg sat<int64_t>(const reg v1, int64_t min, int64_t max) {
		return mipp::min<int64_t>(mipp::max<int64_t>(v1, set1<int64_t>(min)), set1<int64_t>(max));
	}

	template <>
	inline reg sat<uint64_t>(const reg v1, uint64_t min, uint64_t max) {
		return mipp::min<uint64_t>(mipp::max<uint64_t>(v1, set1<uint64_t>(min)), set1<uint64_t>(max));
	}

	template <>
	inline reg sat<int32_t>(const reg v1, int32_t min, int32_t max) {
		return mipp::min<int32_t>(mipp::max<int32_t>(v1, set1<int32_t>(min)), set1<int32_t>(max));
	}

	template <>
	inline reg sat<uint32_t>(const reg v1, uint32_t min, uint32_t max) {
		return mipp::min<uint32_t>(mipp::max<uint32_t>(v1, set1<uint32_t>(min)), set1<uint32_t>(max));
	}

	template <>
	inline reg sat<int16_t>(const reg v1, int16_t min, int16_t max) {
		return mipp::min<int16_t>(mipp::max<int16_t>(v1, set1<int16_t>(min)), set1<int16_t>(max));
	}

	template <>
	inline reg sat<uint16_t>(const reg v1, uint16_t min, uint16_t max) {
		return mipp::min<uint16_t>(mipp::max<uint16_t>(v1, set1<uint16_t>(min)), set1<uint16_t>(max));
	}

	template <>
	inline reg sat<int8_t>(const reg v1, int8_t min, int8_t max) {
		return mipp::min<int8_t>(mipp::max<int8_t>(v1, set1<int8_t>(min)), set1<int8_t>(max));
	}

	template <>
	inline reg sat<uint8_t>(const reg v1, uint8_t min, uint8_t max) {
		return mipp::min<uint8_t>(mipp::max<uint8_t>(v1, set1<uint8_t>(min)), set1<uint8_t>(max));
	}

	// ---------------------------------------------------------------------------------------------------------- round
#ifdef __AVX512F__
	template <>
	inline reg round<double>(const reg v) {
		return _mm512_castpd_ps(_mm512_roundscale_round_pd(_mm512_castps_pd(v), _MM_FROUND_TO_NEAREST_INT, _MM_FROUND_NO_EXC));
	}

	template <>
	inline reg round<float>(const reg v) {
		return _mm512_roundscale_round_ps(v, _MM_FROUND_TO_NEAREST_INT, _MM_FROUND_NO_EXC);
	}

#elif defined(__MIC__) || defined(__KNCNI__)
	template <>
	inline reg round<float>(const reg v) {
		return _mm512_round_ps(v, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC, _MM_EXPADJ_NONE);
	}
#endif

	// ---------------------------------------------------------------------------------------------------------- trunc
#ifdef __AVX512F__
	template <>
	inline reg trunc<double>(const reg v) {
		return _mm512_castpd_ps(_mm512_roundscale_round_pd(_mm512_castps_pd(v), _MM_FROUND_TO_ZERO, _MM_FROUND_NO_EXC));
	}

	template <>
	inline reg trunc<float>(const reg v) {
		return _mm512_roundscale_round_ps(v, _MM_FROUND_TO_ZERO, _MM_FROUND_NO_EXC);
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ cvt
#ifdef __AVX512DQ__
	template <>
	inline reg cvt<double,int64_t>(const reg v) {
		return _mm512_castsi512_ps(_mm512_cvtpd_epi64(_mm512_castps_pd(v)));
	}

	template <>
	inline reg cvt<double,uint64_t>(const reg v) {
		return _mm512_castsi512_ps(_mm512_cvtpd_epu64(_mm512_castps_pd(v)));
	}

	template <>
	inline reg cvt<int64_t,double>(const reg v) {
		return _mm512_castpd_ps(_mm512_cvtepi64_pd(_mm512_castps_si512(v)));
	}

	template <>
	inline reg cvt<uint64_t,double>(const reg v) {
		return _mm512_castpd_ps(_mm512_cvtepu64_pd(_mm512_castps_si512(v)));
	}
#endif

#ifdef __AVX512F__
	template <>
	inline reg cvt<float,int32_t>(const reg v) {
		return _mm512_castsi512_ps(_mm512_cvtps_epi32(v));
	}

	template <>
	inline reg cvt<float,uint32_t>(const reg v) {
		return _mm512_castsi512_ps(_mm512_cvtps_epu32(v));
	}

	template <>
	inline reg cvt<int32_t,float>(const reg v) {
		return _mm512_cvtepi32_ps(_mm512_castps_si512(v));
	}

	template <>
	inline reg cvt<uint32_t,float>(const reg v) {
		return _mm512_cvtepu32_ps(_mm512_castps_si512(v));
	}

	template <>
	inline reg cvt<int32_t,int64_t>(const reg_2 v) {
		return _mm512_castsi512_ps(_mm512_cvtepi32_epi64(_mm256_castps_si256(v)));
	}

	template <>
	inline reg cvt<uint32_t,uint64_t>(const reg_2 v) {
		return _mm512_castsi512_ps(_mm512_cvtepu32_epi64(_mm256_castps_si256(v)));
	}

	template <>
	inline reg cvt<int16_t,int32_t>(const reg_2 v) {
		return _mm512_castsi512_ps(_mm512_cvtepi16_epi32(_mm256_castps_si256(v)));
	}

	template <>
	inline reg cvt<uint16_t,uint32_t>(const reg_2 v) {
		return _mm512_castsi512_ps(_mm512_cvtepu16_epi32(_mm256_castps_si256(v)));
	}
#endif

#ifdef __AVX512BW__
	template <>
	inline reg cvt<int8_t,int16_t>(const reg_2 v) {
		return _mm512_castsi512_ps(_mm512_cvtepi8_epi16(_mm256_castps_si256(v)));
	}

	template <>
	inline reg cvt<uint8_t,uint16_t>(const reg_2 v) {
		return _mm512_castsi512_ps(_mm512_cvtepu8_epi16(_mm256_castps_si256(v)));
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- pack
#ifdef __AVX512BW__
	template <>
	inline reg pack<int32_t,int16_t>(const reg v1, const reg v2) {
		auto mask =_mm512_set_epi64(7,5,3,1,6,4,2,0);
		return _mm512_castsi512_ps(_mm512_permutexvar_epi64(mask, _mm512_packs_epi32(_mm512_castps_si512(v1),
		                                                                             _mm512_castps_si512(v2))));
	}

	template <>
	inline reg pack<uint32_t,uint16_t>(const reg v1, const reg v2) {
		auto mask =_mm512_set_epi64(7,5,3,1,6,4,2,0);
		return _mm512_castsi512_ps(_mm512_permutexvar_epi64(mask, _mm512_packus_epi32(_mm512_castps_si512(v1),
		                                                                              _mm512_castps_si512(v2))));
	}

	template <>
	inline reg pack<int16_t,int8_t>(const reg v1, const reg v2) {
		auto mask =_mm512_set_epi64(7,5,3,1,6,4,2,0);
		return _mm512_castsi512_ps(_mm512_permutexvar_epi64(mask, _mm512_packs_epi16(_mm512_castps_si512(v1),
		                                                                             _mm512_castps_si512(v2))));
	}

	template <>
	inline reg pack<uint16_t,uint8_t>(const reg v1, const reg v2) {
		auto mask =_mm512_set_epi64(7,5,3,1,6,4,2,0);
		return _mm512_castsi512_ps(_mm512_permutexvar_epi64(mask, _mm512_packus_epi16(_mm512_castps_si512(v1),
		                                                                              _mm512_castps_si512(v2))));
	}
#endif

	// ---------------------------------------------------------------------------------------------------------- testz
#if defined(__AVX512F__) || defined(__MIC__) || defined(__KNCNI__)
	template <>
	inline bool testz<int64_t>(const reg v1, const reg v2) {
		auto msk = mipp::cmpneq<int64_t>(mipp::andb<int64_t>(v1, v2), mipp::set0<int64_t>());
		return _mm512_kortestz(msk, mipp::set0<8>());
	}

	template <>
	inline bool testz<int32_t>(const reg v1, const reg v2) {
		auto msk = mipp::cmpneq<int32_t>(mipp::andb<int32_t>(v1, v2), mipp::set0<int32_t>());
		return _mm512_kortestz(msk, mipp::set0<16>());
	}

	template <>
	inline bool testz<int64_t>(const reg v1) {
		auto msk = mipp::cmpneq<int64_t>(v1, mipp::set0<int64_t>());
		return _mm512_kortestz(msk, mipp::set0<8>());
	}

	template <>
	inline bool testz<int32_t>(const reg v1) {
		auto msk = mipp::cmpneq<int32_t>(v1, mipp::set0<int32_t>());
		return _mm512_kortestz(msk, mipp::set0<16>());
	}
#endif

#if defined(__AVX512BW__)
	template <>
	inline bool testz<int16_t>(const reg v1, const reg v2) {
		auto msk = mipp::cmpneq<int16_t>(mipp::andb<int16_t>(v1, v2), mipp::set0<int16_t>());
		// return _mm512_kortestz(msk, mipp::set0<32>());
		return (uint64_t)msk == 0;
	}

	template <>
	inline bool testz<int8_t>(const reg v1, const reg v2) {
		auto msk = mipp::cmpneq<int8_t>(mipp::andb<int8_t>(v1, v2), mipp::set0<int8_t>());
		// return _mm512_kortestz(msk, mipp::set0<64>());
		return (uint64_t)msk == 0;
	}

	template <>
	inline bool testz<int16_t>(const reg v1) {
		auto msk = mipp::cmpneq<int16_t>(v1, mipp::set0<int16_t>());
		// return _mm512_kortestz(msk, mipp::set0<32>());
		return (uint64_t)msk == 0;
	}

	template <>
	inline bool testz<int8_t>(const reg v1) {
		auto msk = mipp::cmpneq<int8_t>(v1, mipp::set0<int8_t>());
		// return _mm512_kortestz(msk, mipp::set0<64>());
		return (uint64_t)msk == 0;
	}
#endif

	// --------------------------------------------------------------------------------------------------- testz (mask)
#if defined(__AVX512F__) || defined(__MIC__) || defined(__KNCNI__)
	template <>
	inline bool testz<8>(const msk v1, const msk v2) {
		return _mm512_kortestz(mipp::andb<8>(v1, v2), mipp::set0<8>());
	}

	template <>
	inline bool testz<16>(const msk v1, const msk v2) {
		return _mm512_kortestz(mipp::andb<16>(v1, v2), mipp::set0<16>());
	}

	template <>
	inline bool testz<8>(const msk v1) {
		return _mm512_kortestz(v1, mipp::set0<8>());
	}

	template <>
	inline bool testz<16>(const msk v1) {
		return _mm512_kortestz(v1, mipp::set0<16>());
	}
#endif

#if defined(__AVX512BW__)
	template <>
	inline bool testz<32>(const msk v1, const msk v2) {
		// return _mm512_kortestz(mipp::andb<32>(v1, v2), mipp::set0<32>());
		return ((uint64_t)v1 & (uint64_t)v2) == 0;
	}

	template <>
	inline bool testz<64>(const msk v1, const msk v2) {
		// return _mm512_kortestz(mipp::andb<64>(v1, v2), mipp::set0<64>());
		return ((uint64_t)v1 & (uint64_t)v2) == 0;
	}

	template <>
	inline bool testz<32>(const msk v1) {
		// return _mm512_kortestz(v1, mipp::set0<32>());
		return (uint64_t)v1 == 0;
	}

	template <>
	inline bool testz<64>(const msk v1) {
		// return _mm512_kortestz(v1, mipp::set0<64>());
		return (uint64_t)v1 == 0;
	}
#endif

	// ------------------------------------------------------------------------------------------------------ reduction
#if defined(__AVX512F__)
	template <red_op<double> OP>
	struct _reduction<double,OP>
	{
		static reg apply(const reg v1) {
			auto val = v1;
			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8), val)); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4), val)); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
//			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32(13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0,3,2), val)); // only AVX512F
			val = OP(val, _mm512_castsi512_ps(_mm512_shuffle_epi32(_mm512_castps_si512(val), _MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))))); // KNCI compatible
			return val;
		}
	};

	template <Red_op<double> OP>
	struct _Reduction<double,OP>
	{
		static const Reg<double> apply(const Reg<double> v1) {
			auto val = v1;
			val = OP(val, Reg<double>(_mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8), val.r))); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
			val = OP(val, Reg<double>(_mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4), val.r))); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
//			val = OP(val, Reg<double>(_mm512_permutexvar_ps(_mm512_set_epi32(13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0,3,2), val.r))); // only AVX512F
			val = OP(val, Reg<double>(_mm512_castsi512_ps(_mm512_shuffle_epi32(_mm512_castps_si512(val.r), _MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2)))))); // KNCI compatible
			return val;
		}
	};

	template <red_op<float> OP>
	struct _reduction<float,OP>
	{
		static reg apply(const reg v1) {
			auto val = v1;
			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8), val)); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4), val)); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
//			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32(13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0,3,2), val)); // only AVX512F
			val = OP(val, _mm512_castsi512_ps(_mm512_shuffle_epi32(_mm512_castps_si512(val), _MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))))); // KNCI compatible
//			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32(14,15,12,13,10,11, 8, 9, 6, 7, 4, 5, 2, 3,0,1), val)); // only AVX512F
			val = OP(val, _mm512_castsi512_ps(_mm512_shuffle_epi32(_mm512_castps_si512(val), _MM_PERM_ENUM(_MM_SHUFFLE(2,3,0,1))))); // KNCI compatible
			return val;
		}
	};

	template <Red_op<float> OP>
	struct _Reduction<float,OP>
	{
		static Reg<float> apply(const Reg<float> v1) {
			auto val = v1;
			val = OP(val, Reg<float>(_mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8), val.r))); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
			val = OP(val, Reg<float>(_mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4), val.r))); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
//			val = OP(val, Reg<float>(_mm512_permutexvar_ps(_mm512_set_epi32(13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0,3,2), val.r))); // only AVX512F
			val = OP(val, Reg<float>(_mm512_castsi512_ps(_mm512_shuffle_epi32(_mm512_castps_si512(val.r), _MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2)))))); // KNCI compatible
//			val = OP(val, Reg<float>(_mm512_permutexvar_ps(_mm512_set_epi32(14,15,12,13,10,11, 8, 9, 6, 7, 4, 5, 2, 3,0,1), val.r))); // only AVX512F
			val = OP(val, Reg<float>(_mm512_castsi512_ps(_mm512_shuffle_epi32(_mm512_castps_si512(val.r), _MM_PERM_ENUM(_MM_SHUFFLE(2,3,0,1)))))); // KNCI compatible
			return val;
		}
	};

	template <red_op<int64_t> OP>
	struct _reduction<int64_t,OP>
	{
		static reg apply(const reg v1) {
			auto val = v1;
			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8), val)); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4), val)); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
//			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32(13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0,3,2), val)); // only AVX512F
			val = OP(val, _mm512_castsi512_ps(_mm512_shuffle_epi32(_mm512_castps_si512(val), _MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))))); // KNCI compatible
			return val;
		}
	};

	template <Red_op<int64_t> OP>
	struct _Reduction<int64_t,OP>
	{
		static const Reg<int64_t> apply(const Reg<int64_t> v1) {
			auto val = v1;
			val = OP(val, Reg<int64_t>(_mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8), val.r))); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
			val = OP(val, Reg<int64_t>(_mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4), val.r))); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
//			val = OP(val, Reg<int64_t>(_mm512_permutexvar_ps(_mm512_set_epi32(13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0,3,2), val.r))); // only AVX512F
			val = OP(val, Reg<int64_t>(_mm512_castsi512_ps(_mm512_shuffle_epi32(_mm512_castps_si512(val.r), _MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2)))))); // KNCI compatible
			return val;
		}
	};

	template <red_op<uint64_t> OP>
	struct _reduction<uint64_t,OP>
	{
		static reg apply(const reg v1) {
			auto val = v1;
			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8), val)); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4), val)); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
//			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32(13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0,3,2), val)); // only AVX512F
			val = OP(val, _mm512_castsi512_ps(_mm512_shuffle_epi32(_mm512_castps_si512(val), _MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))))); // KNCI compatible
			return val;
		}
	};

	template <Red_op<uint64_t> OP>
	struct _Reduction<uint64_t,OP>
	{
		static const Reg<uint64_t> apply(const Reg<uint64_t> v1) {
			auto val = v1;
			val = OP(val, Reg<uint64_t>(_mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8), val.r))); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
			val = OP(val, Reg<uint64_t>(_mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4), val.r))); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
//			val = OP(val, Reg<uint64_t>(_mm512_permutexvar_ps(_mm512_set_epi32(13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0,3,2), val.r))); // only AVX512F
			val = OP(val, Reg<uint64_t>(_mm512_castsi512_ps(_mm512_shuffle_epi32(_mm512_castps_si512(val.r), _MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2)))))); // KNCI compatible
			return val;
		}
	};

	template <red_op<int32_t> OP>
	struct _reduction<int32_t,OP>
	{
		static reg apply(const reg v1) {
			auto val = v1;
			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8), val)); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4), val)); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
//			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32(13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0,3,2), val)); // only AVX512F
			val = OP(val, _mm512_castsi512_ps(_mm512_shuffle_epi32(_mm512_castps_si512(val), _MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))))); // KNCI compatible
//			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32(14,15,12,13,10,11, 8, 9, 6, 7, 4, 5, 2, 3,0,1), val)); // only AVX512F
			val = OP(val, _mm512_castsi512_ps(_mm512_shuffle_epi32(_mm512_castps_si512(val), _MM_PERM_ENUM(_MM_SHUFFLE(2,3,0,1))))); // KNCI compatible
			return val;
		}
	};

	template <Red_op<int32_t> OP>
	struct _Reduction<int32_t,OP>
	{
		static Reg<int32_t> apply(const Reg<int32_t> v1) {
			auto val = v1;
			val = OP(val, Reg<int32_t>(_mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8), val.r))); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
			val = OP(val, Reg<int32_t>(_mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4), val.r))); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
//			val = OP(val, Reg<int32_t>(_mm512_permutexvar_ps(_mm512_set_epi32(13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0,3,2), val.r))); // only AVX512F
			val = OP(val, Reg<int32_t>(_mm512_castsi512_ps(_mm512_shuffle_epi32(_mm512_castps_si512(val.r), _MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2)))))); // KNCI compatible
//			val = OP(val, Reg<int32_t>(_mm512_permutexvar_ps(_mm512_set_epi32(14,15,12,13,10,11, 8, 9, 6, 7, 4, 5, 2, 3,0,1), val.r))); // only AVX512F
			val = OP(val, Reg<int32_t>(_mm512_castsi512_ps(_mm512_shuffle_epi32(_mm512_castps_si512(val.r), _MM_PERM_ENUM(_MM_SHUFFLE(2,3,0,1)))))); // KNCI compatible
			return val;
		}
	};

	template <red_op<uint32_t> OP>
	struct _reduction<uint32_t,OP>
	{
		static reg apply(const reg v1) {
			auto val = v1;
			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8), val)); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4), val)); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
//			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32(13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0,3,2), val)); // only AVX512F
			val = OP(val, _mm512_castsi512_ps(_mm512_shuffle_epi32(_mm512_castps_si512(val), _MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))))); // KNCI compatible
//			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32(14,15,12,13,10,11, 8, 9, 6, 7, 4, 5, 2, 3,0,1), val)); // only AVX512F
			val = OP(val, _mm512_castsi512_ps(_mm512_shuffle_epi32(_mm512_castps_si512(val), _MM_PERM_ENUM(_MM_SHUFFLE(2,3,0,1))))); // KNCI compatible
			return val;
		}
	};

	template <Red_op<uint32_t> OP>
	struct _Reduction<uint32_t,OP>
	{
		static Reg<uint32_t> apply(const Reg<uint32_t> v1) {
			auto val = v1;
			val = OP(val, Reg<uint32_t>(_mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8), val.r))); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
			val = OP(val, Reg<uint32_t>(_mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4), val.r))); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
//			val = OP(val, Reg<uint32_t>(_mm512_permutexvar_ps(_mm512_set_epi32(13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0,3,2), val.r))); // only AVX512F
			val = OP(val, Reg<uint32_t>(_mm512_castsi512_ps(_mm512_shuffle_epi32(_mm512_castps_si512(val.r), _MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2)))))); // KNCI compatible
//			val = OP(val, Reg<uint32_t>(_mm512_permutexvar_ps(_mm512_set_epi32(14,15,12,13,10,11, 8, 9, 6, 7, 4, 5, 2, 3,0,1), val.r))); // only AVX512F
			val = OP(val, Reg<uint32_t>(_mm512_castsi512_ps(_mm512_shuffle_epi32(_mm512_castps_si512(val.r), _MM_PERM_ENUM(_MM_SHUFFLE(2,3,0,1)))))); // KNCI compatible
			return val;
		}
	};

#if defined(__AVX512BW__)
	template <red_op<int16_t> OP>
	struct _reduction<int16_t,OP>
	{
		static reg apply(const reg v1) {
//			__m512i mask_no = _mm512_set_epi8(63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,
//			                                  47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,
//			                                  31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,
//			                                  15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);

			__m512i mask_16 = _mm512_set_epi8(61,60,63,62,57,56,59,58,53,52,55,54,49,48,51,50,
			                                  45,44,47,46,41,40,43,42,37,36,39,38,33,32,35,34,
			                                  29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,
			                                  13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0, 3, 2);

			auto val = v1;
			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8), val)); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4), val)); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
//			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32(13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0,3,2), val)); // only AVX512F
			val = OP(val, _mm512_castsi512_ps(_mm512_shuffle_epi32(_mm512_castps_si512(val), _MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))))); // KNCI compatible
//			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32(14,15,12,13,10,11, 8, 9, 6, 7, 4, 5, 2, 3,0,1), val)); // only AVX512F
			val = OP(val, _mm512_castsi512_ps(_mm512_shuffle_epi32(_mm512_castps_si512(val), _MM_PERM_ENUM(_MM_SHUFFLE(2,3,0,1))))); // KNCI compatible
			val = OP(val, _mm512_castsi512_ps(_mm512_shuffle_epi8(_mm512_castps_si512(val), mask_16))); // only AVX512BW
			return val;
		}
	};

	template <Red_op<int16_t> OP>
	struct _Reduction<int16_t,OP>
	{
		static Reg<int16_t> apply(const Reg<int16_t> v1) {
			__m512i mask_16 = _mm512_set_epi8(61,60,63,62,57,56,59,58,53,52,55,54,49,48,51,50,
			                                  45,44,47,46,41,40,43,42,37,36,39,38,33,32,35,34,
			                                  29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,
			                                  13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0, 3, 2);

			auto val = v1;
			val = OP(val, Reg<int16_t>(_mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8), val.r))); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
			val = OP(val, Reg<int16_t>(_mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4), val.r))); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
//			val = OP(val, Reg<int16_t>(_mm512_permutexvar_ps(_mm512_set_epi32(13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0,3,2), val.r))); // only AVX512F
			val = OP(val, Reg<int16_t>(_mm512_castsi512_ps(_mm512_shuffle_epi32(_mm512_castps_si512(val.r), _MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2)))))); // KNCI compatible
//			val = OP(val, Reg<int16_t>(_mm512_permutexvar_ps(_mm512_set_epi32(14,15,12,13,10,11, 8, 9, 6, 7, 4, 5, 2, 3,0,1), val.r))); // only AVX512F
			val = OP(val, Reg<int16_t>(_mm512_castsi512_ps(_mm512_shuffle_epi32(_mm512_castps_si512(val.r), _MM_PERM_ENUM(_MM_SHUFFLE(2,3,0,1)))))); // KNCI compatible
			val = OP(val, Reg<int16_t>(_mm512_castsi512_ps(_mm512_shuffle_epi8(_mm512_castps_si512(val.r), mask_16)))); // only AVX512BW
			return val;
		}
	};

	template <red_op<uint16_t> OP>
	struct _reduction<uint16_t,OP>
	{
		static reg apply(const reg v1) {
//			__m512i mask_no = _mm512_set_epi8(63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,
//			                                  47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,
//			                                  31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,
//			                                  15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);

			__m512i mask_16 = _mm512_set_epi8(61,60,63,62,57,56,59,58,53,52,55,54,49,48,51,50,
			                                  45,44,47,46,41,40,43,42,37,36,39,38,33,32,35,34,
			                                  29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,
			                                  13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0, 3, 2);

			auto val = v1;
			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8), val)); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4), val)); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
//			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32(13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0,3,2), val)); // only AVX512F
			val = OP(val, _mm512_castsi512_ps(_mm512_shuffle_epi32(_mm512_castps_si512(val), _MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))))); // KNCI compatible
//			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32(14,15,12,13,10,11, 8, 9, 6, 7, 4, 5, 2, 3,0,1), val)); // only AVX512F
			val = OP(val, _mm512_castsi512_ps(_mm512_shuffle_epi32(_mm512_castps_si512(val), _MM_PERM_ENUM(_MM_SHUFFLE(2,3,0,1))))); // KNCI compatible
			val = OP(val, _mm512_castsi512_ps(_mm512_shuffle_epi8(_mm512_castps_si512(val), mask_16))); // only AVX512BW
			return val;
		}
	};

	template <Red_op<uint16_t> OP>
	struct _Reduction<uint16_t,OP>
	{
		static Reg<uint16_t> apply(const Reg<uint16_t> v1) {
			__m512i mask_16 = _mm512_set_epi8(61,60,63,62,57,56,59,58,53,52,55,54,49,48,51,50,
			                                  45,44,47,46,41,40,43,42,37,36,39,38,33,32,35,34,
			                                  29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,
			                                  13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0, 3, 2);

			auto val = v1;
			val = OP(val, Reg<uint16_t>(_mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8), val.r))); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
			val = OP(val, Reg<uint16_t>(_mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4), val.r))); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
//			val = OP(val, Reg<uint16_t>(_mm512_permutexvar_ps(_mm512_set_epi32(13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0,3,2), val.r))); // only AVX512F
			val = OP(val, Reg<uint16_t>(_mm512_castsi512_ps(_mm512_shuffle_epi32(_mm512_castps_si512(val.r), _MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2)))))); // KNCI compatible
//			val = OP(val, Reg<uint16_t>(_mm512_permutexvar_ps(_mm512_set_epi32(14,15,12,13,10,11, 8, 9, 6, 7, 4, 5, 2, 3,0,1), val.r))); // only AVX512F
			val = OP(val, Reg<uint16_t>(_mm512_castsi512_ps(_mm512_shuffle_epi32(_mm512_castps_si512(val.r), _MM_PERM_ENUM(_MM_SHUFFLE(2,3,0,1)))))); // KNCI compatible
			val = OP(val, Reg<uint16_t>(_mm512_castsi512_ps(_mm512_shuffle_epi8(_mm512_castps_si512(val.r), mask_16)))); // only AVX512BW
			return val;
		}
	};

	template <red_op<int8_t> OP>
	struct _reduction<int8_t,OP>
	{
		static reg apply(const reg v1) {
			__m512i mask_16 = _mm512_set_epi8(61,60,63,62,57,56,59,58,53,52,55,54,49,48,51,50,
			                                  45,44,47,46,41,40,43,42,37,36,39,38,33,32,35,34,
			                                  29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,
			                                  13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0, 3, 2);

			__m512i mask_8  = _mm512_set_epi8(62,63,60,61,58,59,56,57,54,55,52,53,50,51,48,49,
			                                  46,47,44,45,42,43,40,41,38,39,36,37,34,35,32,33,
			                                  30,31,28,29,26,27,24,25,22,23,20,21,18,19,16,17,
			                                  14,15,12,13,10,11, 8, 9, 6, 7, 4, 5, 2, 3, 0, 1);

			auto val = v1;
			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8), val)); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4), val)); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
//			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32(13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0,3,2), val)); // only AVX512F
			val = OP(val, _mm512_castsi512_ps(_mm512_shuffle_epi32(_mm512_castps_si512(val), _MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))))); // KNCI compatible
//			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32(14,15,12,13,10,11, 8, 9, 6, 7, 4, 5, 2, 3,0,1), val)); // only AVX512F
			val = OP(val, _mm512_castsi512_ps(_mm512_shuffle_epi32(_mm512_castps_si512(val), _MM_PERM_ENUM(_MM_SHUFFLE(2,3,0,1))))); // KNCI compatible
			val = OP(val, _mm512_castsi512_ps(_mm512_shuffle_epi8(_mm512_castps_si512(val), mask_16))); // only AVX512BW
			val = OP(val, _mm512_castsi512_ps(_mm512_shuffle_epi8(_mm512_castps_si512(val), mask_8))); // only AVX512BW
			return val;
		}
	};

	template <Red_op<int8_t> OP>
	struct _Reduction<int8_t,OP>
	{
		static Reg<int8_t> apply(const Reg<int8_t> v1) {
			__m512i mask_16 = _mm512_set_epi8(61,60,63,62,57,56,59,58,53,52,55,54,49,48,51,50,
			                                  45,44,47,46,41,40,43,42,37,36,39,38,33,32,35,34,
			                                  29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,
			                                  13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0, 3, 2);

			__m512i mask_8  = _mm512_set_epi8(62,63,60,61,58,59,56,57,54,55,52,53,50,51,48,49,
			                                  46,47,44,45,42,43,40,41,38,39,36,37,34,35,32,33,
			                                  30,31,28,29,26,27,24,25,22,23,20,21,18,19,16,17,
			                                  14,15,12,13,10,11, 8, 9, 6, 7, 4, 5, 2, 3, 0, 1);

			auto val = v1;
			val = OP(val, Reg<int8_t>(_mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8), val.r))); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
			val = OP(val, Reg<int8_t>(_mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4), val.r))); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
//			val = OP(val, Reg<int8_t>(_mm512_permutexvar_ps(_mm512_set_epi32(13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0,3,2), val.r))); // only AVX512F
			val = OP(val, Reg<int8_t>(_mm512_castsi512_ps(_mm512_shuffle_epi32(_mm512_castps_si512(val.r), _MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2)))))); // KNCI compatible
//			val = OP(val, Reg<int8_t>(_mm512_permutexvar_ps(_mm512_set_epi32(14,15,12,13,10,11, 8, 9, 6, 7, 4, 5, 2, 3,0,1), val.r))); // only AVX512F
			val = OP(val, Reg<int8_t>(_mm512_castsi512_ps(_mm512_shuffle_epi32(_mm512_castps_si512(val.r), _MM_PERM_ENUM(_MM_SHUFFLE(2,3,0,1)))))); // KNCI compatible
			val = OP(val, Reg<int8_t>(_mm512_castsi512_ps(_mm512_shuffle_epi8(_mm512_castps_si512(val.r), mask_16)))); // only AVX512BW
			val = OP(val, Reg<int8_t>(_mm512_castsi512_ps(_mm512_shuffle_epi8(_mm512_castps_si512(val.r), mask_8)))); // only AVX512BW
			return val;
		}
	};

	template <red_op<uint8_t> OP>
	struct _reduction<uint8_t,OP>
	{
		static reg apply(const reg v1) {
			__m512i mask_16 = _mm512_set_epi8(61,60,63,62,57,56,59,58,53,52,55,54,49,48,51,50,
			                                  45,44,47,46,41,40,43,42,37,36,39,38,33,32,35,34,
			                                  29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,
			                                  13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0, 3, 2);

			__m512i mask_8  = _mm512_set_epi8(62,63,60,61,58,59,56,57,54,55,52,53,50,51,48,49,
			                                  46,47,44,45,42,43,40,41,38,39,36,37,34,35,32,33,
			                                  30,31,28,29,26,27,24,25,22,23,20,21,18,19,16,17,
			                                  14,15,12,13,10,11, 8, 9, 6, 7, 4, 5, 2, 3, 0, 1);

			auto val = v1;
			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8), val)); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4), val)); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
//			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32(13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0,3,2), val)); // only AVX512F
			val = OP(val, _mm512_castsi512_ps(_mm512_shuffle_epi32(_mm512_castps_si512(val), _MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2))))); // KNCI compatible
//			val = OP(val, _mm512_permutexvar_ps(_mm512_set_epi32(14,15,12,13,10,11, 8, 9, 6, 7, 4, 5, 2, 3,0,1), val)); // only AVX512F
			val = OP(val, _mm512_castsi512_ps(_mm512_shuffle_epi32(_mm512_castps_si512(val), _MM_PERM_ENUM(_MM_SHUFFLE(2,3,0,1))))); // KNCI compatible
			val = OP(val, _mm512_castsi512_ps(_mm512_shuffle_epi8(_mm512_castps_si512(val), mask_16))); // only AVX512BW
			val = OP(val, _mm512_castsi512_ps(_mm512_shuffle_epi8(_mm512_castps_si512(val), mask_8))); // only AVX512BW
			return val;
		}
	};

	template <Red_op<uint8_t> OP>
	struct _Reduction<uint8_t,OP>
	{
		static Reg<uint8_t> apply(const Reg<uint8_t> v1) {
			__m512i mask_16 = _mm512_set_epi8(61,60,63,62,57,56,59,58,53,52,55,54,49,48,51,50,
			                                  45,44,47,46,41,40,43,42,37,36,39,38,33,32,35,34,
			                                  29,28,31,30,25,24,27,26,21,20,23,22,17,16,19,18,
			                                  13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0, 3, 2);

			__m512i mask_8  = _mm512_set_epi8(62,63,60,61,58,59,56,57,54,55,52,53,50,51,48,49,
			                                  46,47,44,45,42,43,40,41,38,39,36,37,34,35,32,33,
			                                  30,31,28,29,26,27,24,25,22,23,20,21,18,19,16,17,
			                                  14,15,12,13,10,11, 8, 9, 6, 7, 4, 5, 2, 3, 0, 1);

			auto val = v1;
			val = OP(val, Reg<uint8_t>(_mm512_permutexvar_ps(_mm512_set_epi32( 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10,9,8), val.r))); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
			val = OP(val, Reg<uint8_t>(_mm512_permutexvar_ps(_mm512_set_epi32(11,10, 9, 8,15,14,13,12, 3, 2, 1, 0, 7, 6,5,4), val.r))); // only AVX512F (for KNCI use _mm512_permute4f128_epi32)
//			val = OP(val, Reg<uint8_t>(_mm512_permutexvar_ps(_mm512_set_epi32(13,12,15,14, 9, 8,11,10, 5, 4, 7, 6, 1, 0,3,2), val.r))); // only AVX512F
			val = OP(val, Reg<uint8_t>(_mm512_castsi512_ps(_mm512_shuffle_epi32(_mm512_castps_si512(val.r), _MM_PERM_ENUM(_MM_SHUFFLE(1,0,3,2)))))); // KNCI compatible
//			val = OP(val, Reg<uint8_t>(_mm512_permutexvar_ps(_mm512_set_epi32(14,15,12,13,10,11, 8, 9, 6, 7, 4, 5, 2, 3,0,1), val.r))); // only AVX512F
			val = OP(val, Reg<uint8_t>(_mm512_castsi512_ps(_mm512_shuffle_epi32(_mm512_castps_si512(val.r), _MM_PERM_ENUM(_MM_SHUFFLE(2,3,0,1)))))); // KNCI compatible
			val = OP(val, Reg<uint8_t>(_mm512_castsi512_ps(_mm512_shuffle_epi8(_mm512_castps_si512(val.r), mask_16)))); // only AVX512BW
			val = OP(val, Reg<uint8_t>(_mm512_castsi512_ps(_mm512_shuffle_epi8(_mm512_castps_si512(val.r), mask_8)))); // only AVX512BW
			return val;
		}
	};
#endif
#endif

#endif
