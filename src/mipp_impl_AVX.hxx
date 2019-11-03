#include "mipp.h"

// -------------------------------------------------------------------------------------------------------- X86 AVX-256
// --------------------------------------------------------------------------------------------------------------------
#if defined(__AVX__)

	// ---------------------------------------------------------------------------------------------------------- loadu
	template <>
	inline reg loadu<float>(const float *mem_addr) {
		return _mm256_loadu_ps(mem_addr);
	}

	template <>
	inline reg loadu<double>(const double *mem_addr) {
		return _mm256_castpd_ps(_mm256_loadu_pd(mem_addr));
	}

	template <>
	inline reg loadu<int64_t>(const int64_t *mem_addr) {
		return _mm256_castpd_ps(_mm256_loadu_pd((const double*) mem_addr));
	}

	template <>
	inline reg loadu<int32_t>(const int32_t *mem_addr) {
		return _mm256_loadu_ps((const float*) mem_addr);
	}

	template <>
	inline reg loadu<int16_t>(const int16_t *mem_addr) {
		return _mm256_loadu_ps((const float*) mem_addr);
	}

	template <>
	inline reg loadu<int8_t>(const int8_t *mem_addr) {
		return _mm256_loadu_ps((const float*) mem_addr);
	}

	// ----------------------------------------------------------------------------------------------------------- load
#ifdef MIPP_ALIGNED_LOADS
	template <>
	inline reg load<float>(const float *mem_addr) {
		return _mm256_load_ps(mem_addr);
	}

	template <>
	inline reg load<double>(const double *mem_addr) {
		return _mm256_castpd_ps(_mm256_load_pd(mem_addr));
	}

	template <>
	inline reg load<int64_t>(const int64_t *mem_addr) {
		return _mm256_castpd_ps(_mm256_load_pd((const double*)mem_addr));
	}

	template <>
	inline reg load<int32_t>(const int32_t *mem_addr) {
		return _mm256_load_ps((const float*) mem_addr);
	}

	template <>
	inline reg load<int16_t>(const int16_t *mem_addr) {
		return _mm256_load_ps((const float*) mem_addr);
	}

	template <>
	inline reg load<int8_t>(const int8_t *mem_addr) {
		return _mm256_load_ps((const float*) mem_addr);
	}
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
#endif

	// --------------------------------------------------------------------------------------------------------- storeu
	template <>
	inline void storeu<float>(float *mem_addr, const reg v) {
		_mm256_storeu_ps(mem_addr, v);
	}

	template <>
	inline void storeu<double>(double *mem_addr, const reg v) {
		_mm256_storeu_pd(mem_addr, _mm256_castps_pd(v));
	}

	template <>
	inline void storeu<int64_t>(int64_t *mem_addr, const reg v) {
		_mm256_storeu_ps((float *)mem_addr, v);
	}

	template <>
	inline void storeu<int32_t>(int32_t *mem_addr, const reg v) {
		_mm256_storeu_ps((float *)mem_addr, v);
	}

	template <>
	inline void storeu<int16_t>(int16_t *mem_addr, const reg v) {
		_mm256_storeu_ps((float *)mem_addr, v);
	}

	template <>
	inline void storeu<int8_t>(int8_t *mem_addr, const reg v) {
		_mm256_storeu_ps((float *)mem_addr, v);
	}

	// ---------------------------------------------------------------------------------------------------------- store
#ifdef MIPP_ALIGNED_LOADS
	template <>
	inline void store<float>(float *mem_addr, const reg v) {
		_mm256_store_ps(mem_addr, v);
	}

	template <>
	inline void store<double>(double *mem_addr, const reg v) {
		_mm256_store_pd(mem_addr, _mm256_castps_pd(v));
	}

	template <>
	inline void store<int64_t>(int64_t *mem_addr, const reg v) {
		_mm256_store_ps((float *)mem_addr, v);
	}

	template <>
	inline void store<int32_t>(int32_t *mem_addr, const reg v) {
		_mm256_store_ps((float *)mem_addr, v);
	}

	template <>
	inline void store<int16_t>(int16_t *mem_addr, const reg v) {
		_mm256_store_ps((float *)mem_addr, v);
	}

	template <>
	inline void store<int8_t>(int8_t *mem_addr, const reg v) {
		_mm256_store_ps((float *)mem_addr, v);
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

	// ------------------------------------------------------------------------------------------------------------ set
	template <>
	inline reg set<double>(const double vals[nElReg<double>()]) {
		return _mm256_castpd_ps(_mm256_set_pd(vals[3], vals[2], vals[1], vals[0]));
	}

	template <>
	inline reg set<float>(const float vals[nElReg<float>()]) {
		return _mm256_set_ps(vals[7], vals[6], vals[5], vals[4], vals[3], vals[2], vals[1], vals[0]);
	}

	template <>
	inline reg set<int64_t>(const int64_t vals[nElReg<int64_t>()]) {
		return _mm256_castsi256_ps(_mm256_set_epi64x(vals[3], vals[2], vals[1], vals[0]));
	}

	template <>
	inline reg set<int32_t>(const int32_t vals[nElReg<int32_t>()]) {
		return _mm256_castsi256_ps(_mm256_set_epi32(vals[7], vals[6], vals[5], vals[4],
		                                            vals[3], vals[2], vals[1], vals[0]));
	}

	template <>
	inline reg set<int16_t>(const int16_t vals[nElReg<int16_t>()]) {
		return _mm256_castsi256_ps(_mm256_set_epi16(vals[15], vals[14], vals[13], vals[12],
		                                            vals[11], vals[10], vals[ 9], vals[ 8],
		                                            vals[ 7], vals[ 6], vals[ 5], vals[ 4],
		                                            vals[ 3], vals[ 2], vals[ 1], vals[ 0]));
	}

	template <>
	inline reg set<int8_t>(const int8_t vals[nElReg<int8_t>()]) {
		return _mm256_castsi256_ps(_mm256_set_epi8((int8_t)vals[31], (int8_t)vals[30], (int8_t)vals[29], (int8_t)vals[28],
		                                           (int8_t)vals[27], (int8_t)vals[26], (int8_t)vals[25], (int8_t)vals[24],
		                                           (int8_t)vals[23], (int8_t)vals[22], (int8_t)vals[21], (int8_t)vals[20],
		                                           (int8_t)vals[19], (int8_t)vals[18], (int8_t)vals[17], (int8_t)vals[16],
		                                           (int8_t)vals[15], (int8_t)vals[14], (int8_t)vals[13], (int8_t)vals[12],
		                                           (int8_t)vals[11], (int8_t)vals[10], (int8_t)vals[ 9], (int8_t)vals[ 8],
		                                           (int8_t)vals[ 7], (int8_t)vals[ 6], (int8_t)vals[ 5], (int8_t)vals[ 4],
		                                           (int8_t)vals[ 3], (int8_t)vals[ 2], (int8_t)vals[ 1], (int8_t)vals[ 0]));
	}

	// ----------------------------------------------------------------------------------------------------- set (mask)
	template <>
	inline msk set<4>(const bool vals[4]) {
		return _mm256_set_epi64x(vals[3] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0,
		                         vals[2] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0,
		                         vals[1] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0,
		                         vals[0] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0);
	}

	template <>
	inline msk set<8>(const bool vals[8]) {
		return _mm256_set_epi32(vals[7] ? 0xFFFFFFFF : 0, vals[6] ? 0xFFFFFFFF : 0,
		                        vals[5] ? 0xFFFFFFFF : 0, vals[4] ? 0xFFFFFFFF : 0,
		                        vals[3] ? 0xFFFFFFFF : 0, vals[2] ? 0xFFFFFFFF : 0,
		                        vals[1] ? 0xFFFFFFFF : 0, vals[0] ? 0xFFFFFFFF : 0);
	}

	template <>
	inline msk set<16>(const bool vals[16]) {
		return _mm256_set_epi16(vals[15] ? 0xFFFF : 0, vals[14] ? 0xFFFF : 0,
		                        vals[13] ? 0xFFFF : 0, vals[12] ? 0xFFFF : 0,
		                        vals[11] ? 0xFFFF : 0, vals[10] ? 0xFFFF : 0,
		                        vals[ 9] ? 0xFFFF : 0, vals[ 8] ? 0xFFFF : 0,
		                        vals[ 7] ? 0xFFFF : 0, vals[ 6] ? 0xFFFF : 0,
		                        vals[ 5] ? 0xFFFF : 0, vals[ 4] ? 0xFFFF : 0,
		                        vals[ 3] ? 0xFFFF : 0, vals[ 2] ? 0xFFFF : 0,
		                        vals[ 1] ? 0xFFFF : 0, vals[ 0] ? 0xFFFF : 0);
	}

	template <>
	inline msk set<32>(const bool vals[32]) {
		return _mm256_set_epi8(vals[31] ? 0xFF : 0, vals[30] ? 0xFF : 0, vals[29] ? 0xFF : 0, vals[28] ? 0xFF : 0,
		                       vals[27] ? 0xFF : 0, vals[26] ? 0xFF : 0, vals[25] ? 0xFF : 0, vals[24] ? 0xFF : 0,
		                       vals[23] ? 0xFF : 0, vals[22] ? 0xFF : 0, vals[21] ? 0xFF : 0, vals[20] ? 0xFF : 0,
		                       vals[19] ? 0xFF : 0, vals[18] ? 0xFF : 0, vals[17] ? 0xFF : 0, vals[16] ? 0xFF : 0,
		                       vals[15] ? 0xFF : 0, vals[14] ? 0xFF : 0, vals[13] ? 0xFF : 0, vals[12] ? 0xFF : 0,
		                       vals[11] ? 0xFF : 0, vals[10] ? 0xFF : 0, vals[ 9] ? 0xFF : 0, vals[ 8] ? 0xFF : 0,
		                       vals[ 7] ? 0xFF : 0, vals[ 6] ? 0xFF : 0, vals[ 5] ? 0xFF : 0, vals[ 4] ? 0xFF : 0,
		                       vals[ 3] ? 0xFF : 0, vals[ 2] ? 0xFF : 0, vals[ 1] ? 0xFF : 0, vals[ 0] ? 0xFF : 0);
	}

	// ----------------------------------------------------------------------------------------------------------- set1
	template <>
	inline reg set1<double>(const double val) {
		return _mm256_castpd_ps(_mm256_set1_pd(val));
	}

	template <>
	inline reg set1<float>(const float val) {
		return _mm256_set1_ps(val);
	}

	template <>
	inline reg set1<int64_t>(const int64_t val) {
		return _mm256_castsi256_ps(_mm256_set1_epi64x(val));
	}

	template <>
	inline reg set1<int32_t>(const int32_t val) {
		return _mm256_castsi256_ps(_mm256_set1_epi32(val));
	}

#ifdef __AVX2__
	template <>
	inline reg set1<int16_t>(const int16_t val) {
		return _mm256_castsi256_ps(_mm256_set1_epi16(val));
	}

	template <>
	inline reg set1<int8_t>(const int8_t val) {
		return _mm256_castsi256_ps(_mm256_set1_epi8(val));
	}
#endif

	// ---------------------------------------------------------------------------------------------------- set1 (mask)
	template <>
	inline msk set1<4>(const bool val) {
		return _mm256_set1_epi64x(val ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0);
	}

	template <>
	inline msk set1<8>(const bool val) {
		return _mm256_set1_epi32(val ? 0xFFFFFFFF : 0);
	}

#ifdef __AVX2__
	template <>
	inline msk set1<16>(const bool val) {
		return _mm256_set1_epi16(val ? 0xFFFF : 0);
	}

	template <>
	inline msk set1<32>(const bool val) {
		return _mm256_set1_epi8(val ? 0xFF : 0);
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- set0
	template <>
	inline reg set0<double>() {
		return _mm256_castpd_ps(_mm256_setzero_pd());
	}

	template <>
	inline reg set0<float>() {
		return _mm256_setzero_ps();
	}

	template <>
	inline reg set0<int64_t>() {
		return _mm256_castsi256_ps(_mm256_setzero_si256());
	}

	template <>
	inline reg set0<int32_t>() {
		return _mm256_castsi256_ps(_mm256_setzero_si256());
	}

	template <>
	inline reg set0<int16_t>() {
		return _mm256_castsi256_ps(_mm256_setzero_si256());
	}

	template <>
	inline reg set0<int8_t>() {
		return _mm256_castsi256_ps(_mm256_setzero_si256());
	}

	// ---------------------------------------------------------------------------------------------------- set0 (mask)
	template <>
	inline msk set0<4>() {
		return _mm256_setzero_si256();
	}

	template <>
	inline msk set0<8>() {
		return _mm256_setzero_si256();
	}

	template <>
	inline msk set0<16>() {
		return _mm256_setzero_si256();
	}

	template <>
	inline msk set0<32>() {
		return _mm256_setzero_si256();
	}

	// ------------------------------------------------------------------------------------------------------------ low
	template <>
	inline reg_2 low<double>(const reg v) {
		return _mm_castsi128_ps(_mm256_extractf128_si256(_mm256_castps_si256(v), 0));
	}

	template <>
	inline reg_2 low<float>(const reg v) {
		return _mm_castsi128_ps(_mm256_extractf128_si256(_mm256_castps_si256(v), 0));
	}

	template <>
	inline reg_2 low<int64_t>(const reg v) {
		return _mm_castsi128_ps(_mm256_extractf128_si256(_mm256_castps_si256(v), 0));
	}

	template <>
	inline reg_2 low<int32_t>(const reg v) {
		return _mm_castsi128_ps(_mm256_extractf128_si256(_mm256_castps_si256(v), 0));
	}

	template <>
	inline reg_2 low<int16_t>(const reg v) {
		return _mm_castsi128_ps(_mm256_extractf128_si256(_mm256_castps_si256(v), 0));
	}

	template <>
	inline reg_2 low<int8_t>(const reg v) {
		return _mm_castsi128_ps(_mm256_extractf128_si256(_mm256_castps_si256(v), 0));
	}

	// ----------------------------------------------------------------------------------------------------------- high
	template <>
	inline reg_2 high<double>(const reg v) {
		return _mm_castsi128_ps(_mm256_extractf128_si256(_mm256_castps_si256(v), 1));
	}

	template <>
	inline reg_2 high<float>(const reg v) {
		return _mm_castsi128_ps(_mm256_extractf128_si256(_mm256_castps_si256(v), 1));
	}

	template <>
	inline reg_2 high<int64_t>(const reg v) {
		return _mm_castsi128_ps(_mm256_extractf128_si256(_mm256_castps_si256(v), 1));
	}

	template <>
	inline reg_2 high<int32_t>(const reg v) {
		return _mm_castsi128_ps(_mm256_extractf128_si256(_mm256_castps_si256(v), 1));
	}

	template <>
	inline reg_2 high<int16_t>(const reg v) {
		return _mm_castsi128_ps(_mm256_extractf128_si256(_mm256_castps_si256(v), 1));
	}

	template <>
	inline reg_2 high<int8_t>(const reg v) {
		return _mm_castsi128_ps(_mm256_extractf128_si256(_mm256_castps_si256(v), 1));
	}

	// ---------------------------------------------------------------------------------------------------------- cmask
	template <>
	inline reg cmask<double>(const uint32_t val[nElReg<double>()]) {
		int64_t val_bis[nElReg<int64_t>()] = {(int64_t)val[0], (int64_t)val[1], (int64_t)val[2], (int64_t)val[3]};
		return mipp::set<int64_t>(val_bis);
	}

	template <>
	inline reg cmask<float>(const uint32_t val[nElReg<float>()]) {
		int32_t val_bis[nElReg<int32_t>()] = {(int32_t)val[0], (int32_t)val[1], (int32_t)val[2], (int32_t)val[3],
		                                      (int32_t)val[4], (int32_t)val[5], (int32_t)val[6], (int32_t)val[7]};
		return mipp::set<int32_t>(val_bis);
	}

	template <>
	inline reg cmask<int64_t>(const uint32_t val[nElReg<int64_t>()]) {
		int64_t val_bis[nElReg<int64_t>()] = {(int64_t)val[0], (int64_t)val[1], (int64_t)val[2], (int64_t)val[3]};
		return mipp::set<int64_t>(val_bis);
	}

	template <>
	inline reg cmask<int32_t>(const uint32_t val[nElReg<int32_t>()]) {
		int32_t val_bis[nElReg<int32_t>()] = {(int32_t)val[0], (int32_t)val[1], (int32_t)val[2], (int32_t)val[3],
		                                      (int32_t)val[4], (int32_t)val[5], (int32_t)val[6], (int32_t)val[7]};
		return mipp::set<int32_t>(val_bis);
	}

	template <>
	inline reg cmask<int16_t>(const uint32_t val[nElReg<int16_t>()]) {
		int16_t val_bis[nElReg<int16_t>()] = {(int16_t)val[ 0], (int16_t)val[ 1], (int16_t)val[ 2], (int16_t)val[3],
		                                      (int16_t)val[ 4], (int16_t)val[ 5], (int16_t)val[ 6], (int16_t)val[7],
		                                      (int16_t)val[ 8], (int16_t)val[ 9], (int16_t)val[10], (int16_t)val[11],
		                                      (int16_t)val[12], (int16_t)val[13], (int16_t)val[14], (int16_t)val[15]};
		return mipp::set<int16_t>(val_bis);
	}

	template <>
	inline reg cmask<int8_t>(const uint32_t val[nElReg<int8_t>()]) {
		int8_t val_bis[nElReg<int8_t>()] = {(int8_t)val[ 0], (int8_t)val[ 1], (int8_t)val[ 2], (int8_t)val[ 3],
		                                    (int8_t)val[ 4], (int8_t)val[ 5], (int8_t)val[ 6], (int8_t)val[ 7],
		                                    (int8_t)val[ 8], (int8_t)val[ 9], (int8_t)val[10], (int8_t)val[11],
		                                    (int8_t)val[12], (int8_t)val[13], (int8_t)val[14], (int8_t)val[15],
		                                    (int8_t)val[16], (int8_t)val[17], (int8_t)val[18], (int8_t)val[19],
		                                    (int8_t)val[20], (int8_t)val[21], (int8_t)val[22], (int8_t)val[23],
		                                    (int8_t)val[24], (int8_t)val[25], (int8_t)val[26], (int8_t)val[27],
		                                    (int8_t)val[28], (int8_t)val[29], (int8_t)val[30], (int8_t)val[31]};
		return mipp::set<int8_t>(val_bis);
	}

	// --------------------------------------------------------------------------------------------------------- cmask2
	template <>
	inline reg cmask2<double>(const uint32_t val[nElReg<double>()/2]) {
		int8_t val_bis[nElReg<int8_t>()] = {(int8_t)(val[0]*8 + 0), (int8_t)(val[0]*8 + 1),
		                                    (int8_t)(val[0]*8 + 2), (int8_t)(val[0]*8 + 3),
		                                    (int8_t)(val[0]*8 + 4), (int8_t)(val[0]*8 + 5),
		                                    (int8_t)(val[0]*8 + 6), (int8_t)(val[0]*8 + 7),
		                                    (int8_t)(val[1]*8 + 0), (int8_t)(val[1]*8 + 1),
		                                    (int8_t)(val[1]*8 + 2), (int8_t)(val[1]*8 + 3),
		                                    (int8_t)(val[1]*8 + 4), (int8_t)(val[1]*8 + 5),
		                                    (int8_t)(val[1]*8 + 6), (int8_t)(val[1]*8 + 7),
		                                    (int8_t)(val[0]*8 + 0), (int8_t)(val[0]*8 + 1),
		                                    (int8_t)(val[0]*8 + 2), (int8_t)(val[0]*8 + 3),
		                                    (int8_t)(val[0]*8 + 4), (int8_t)(val[0]*8 + 5),
		                                    (int8_t)(val[0]*8 + 6), (int8_t)(val[0]*8 + 7),
		                                    (int8_t)(val[1]*8 + 0), (int8_t)(val[1]*8 + 1),
		                                    (int8_t)(val[1]*8 + 2), (int8_t)(val[1]*8 + 3),
		                                    (int8_t)(val[1]*8 + 4), (int8_t)(val[1]*8 + 5),
		                                    (int8_t)(val[1]*8 + 6), (int8_t)(val[1]*8 + 7)};
		return mipp::set<int8_t>(val_bis);
	}

	template <>
	inline reg cmask2<float>(const uint32_t val[nElReg<float>()/2]) {
		int8_t val_bis[nElReg<int8_t>()] = {(int8_t)(val[0]*4 + 0), (int8_t)(val[0]*4 + 1),
		                                    (int8_t)(val[0]*4 + 2), (int8_t)(val[0]*4 + 3),
		                                    (int8_t)(val[1]*4 + 0), (int8_t)(val[1]*4 + 1),
		                                    (int8_t)(val[1]*4 + 2), (int8_t)(val[1]*4 + 3),
		                                    (int8_t)(val[2]*4 + 0), (int8_t)(val[2]*4 + 1),
		                                    (int8_t)(val[2]*4 + 2), (int8_t)(val[2]*4 + 3),
		                                    (int8_t)(val[3]*4 + 0), (int8_t)(val[3]*4 + 1),
		                                    (int8_t)(val[3]*4 + 2), (int8_t)(val[3]*4 + 3),
		                                    (int8_t)(val[0]*4 + 0), (int8_t)(val[0]*4 + 1),
		                                    (int8_t)(val[0]*4 + 2), (int8_t)(val[0]*4 + 3),
		                                    (int8_t)(val[1]*4 + 0), (int8_t)(val[1]*4 + 1),
		                                    (int8_t)(val[1]*4 + 2), (int8_t)(val[1]*4 + 3),
		                                    (int8_t)(val[2]*4 + 0), (int8_t)(val[2]*4 + 1),
		                                    (int8_t)(val[2]*4 + 2), (int8_t)(val[2]*4 + 3),
		                                    (int8_t)(val[3]*4 + 0), (int8_t)(val[3]*4 + 1),
		                                    (int8_t)(val[3]*4 + 2), (int8_t)(val[3]*4 + 3)};
		return mipp::set<int8_t>(val_bis);
	}

	template <>
	inline reg cmask2<int64_t>(const uint32_t val[nElReg<int64_t>()/2]) {
		int8_t val_bis[nElReg<int8_t>()] = {(int8_t)(val[0]*8 + 0), (int8_t)(val[0]*8 + 1),
		                                    (int8_t)(val[0]*8 + 2), (int8_t)(val[0]*8 + 3),
		                                    (int8_t)(val[0]*8 + 4), (int8_t)(val[0]*8 + 5),
		                                    (int8_t)(val[0]*8 + 6), (int8_t)(val[0]*8 + 7),
		                                    (int8_t)(val[1]*8 + 0), (int8_t)(val[1]*8 + 1),
		                                    (int8_t)(val[1]*8 + 2), (int8_t)(val[1]*8 + 3),
		                                    (int8_t)(val[1]*8 + 4), (int8_t)(val[1]*8 + 5),
		                                    (int8_t)(val[1]*8 + 6), (int8_t)(val[1]*8 + 7),
		                                    (int8_t)(val[0]*8 + 0), (int8_t)(val[0]*8 + 1),
		                                    (int8_t)(val[0]*8 + 2), (int8_t)(val[0]*8 + 3),
		                                    (int8_t)(val[0]*8 + 4), (int8_t)(val[0]*8 + 5),
		                                    (int8_t)(val[0]*8 + 6), (int8_t)(val[0]*8 + 7),
		                                    (int8_t)(val[1]*8 + 0), (int8_t)(val[1]*8 + 1),
		                                    (int8_t)(val[1]*8 + 2), (int8_t)(val[1]*8 + 3),
		                                    (int8_t)(val[1]*8 + 4), (int8_t)(val[1]*8 + 5),
		                                    (int8_t)(val[1]*8 + 6), (int8_t)(val[1]*8 + 7)};
		return mipp::set<int8_t>(val_bis);
	}

	template <>
	inline reg cmask2<int32_t>(const uint32_t val[nElReg<int32_t>()/2]) {
		int8_t val_bis[nElReg<int8_t>()] = {(int8_t)(val[0]*4 + 0), (int8_t)(val[0]*4 + 1),
		                                    (int8_t)(val[0]*4 + 2), (int8_t)(val[0]*4 + 3),
		                                    (int8_t)(val[1]*4 + 0), (int8_t)(val[1]*4 + 1),
		                                    (int8_t)(val[1]*4 + 2), (int8_t)(val[1]*4 + 3),
		                                    (int8_t)(val[2]*4 + 0), (int8_t)(val[2]*4 + 1),
		                                    (int8_t)(val[2]*4 + 2), (int8_t)(val[2]*4 + 3),
		                                    (int8_t)(val[3]*4 + 0), (int8_t)(val[3]*4 + 1),
		                                    (int8_t)(val[3]*4 + 2), (int8_t)(val[3]*4 + 3),
		                                    (int8_t)(val[0]*4 + 0), (int8_t)(val[0]*4 + 1),
		                                    (int8_t)(val[0]*4 + 2), (int8_t)(val[0]*4 + 3),
		                                    (int8_t)(val[1]*4 + 0), (int8_t)(val[1]*4 + 1),
		                                    (int8_t)(val[1]*4 + 2), (int8_t)(val[1]*4 + 3),
		                                    (int8_t)(val[2]*4 + 0), (int8_t)(val[2]*4 + 1),
		                                    (int8_t)(val[2]*4 + 2), (int8_t)(val[2]*4 + 3),
		                                    (int8_t)(val[3]*4 + 0), (int8_t)(val[3]*4 + 1),
		                                    (int8_t)(val[3]*4 + 2), (int8_t)(val[3]*4 + 3)};
		return mipp::set<int8_t>(val_bis);
	}

	template <>
	inline reg cmask2<int16_t>(const uint32_t val[nElReg<int16_t>()/2]) {
		int8_t val_bis[nElReg<int8_t>()] = {(int8_t)(val[ 0]*2 + 0), (int8_t)(val[ 0]*2 + 1),
		                                    (int8_t)(val[ 1]*2 + 0), (int8_t)(val[ 1]*2 + 1),
		                                    (int8_t)(val[ 2]*2 + 0), (int8_t)(val[ 2]*2 + 1),
		                                    (int8_t)(val[ 3]*2 + 0), (int8_t)(val[ 3]*2 + 1),
		                                    (int8_t)(val[ 4]*2 + 0), (int8_t)(val[ 4]*2 + 1),
		                                    (int8_t)(val[ 5]*2 + 0), (int8_t)(val[ 5]*2 + 1),
		                                    (int8_t)(val[ 6]*2 + 0), (int8_t)(val[ 6]*2 + 1),
		                                    (int8_t)(val[ 7]*2 + 0), (int8_t)(val[ 7]*2 + 1),
		                                    (int8_t)(val[ 0]*2 + 0), (int8_t)(val[ 0]*2 + 1),
		                                    (int8_t)(val[ 1]*2 + 0), (int8_t)(val[ 1]*2 + 1),
		                                    (int8_t)(val[ 2]*2 + 0), (int8_t)(val[ 2]*2 + 1),
		                                    (int8_t)(val[ 3]*2 + 0), (int8_t)(val[ 3]*2 + 1),
		                                    (int8_t)(val[ 4]*2 + 0), (int8_t)(val[ 4]*2 + 1),
		                                    (int8_t)(val[ 5]*2 + 0), (int8_t)(val[ 5]*2 + 1),
		                                    (int8_t)(val[ 6]*2 + 0), (int8_t)(val[ 6]*2 + 1),
		                                    (int8_t)(val[ 7]*2 + 0), (int8_t)(val[ 7]*2 + 1)};
		return mipp::set<int8_t>(val_bis);
	}

	template <>
	inline reg cmask2<int8_t>(const uint32_t val[nElReg<int8_t>()/2]) {
		int8_t val_bis[nElReg<int8_t>()] = {(int8_t)val[ 0], (int8_t)val[ 1],
		                                    (int8_t)val[ 2], (int8_t)val[ 3],
		                                    (int8_t)val[ 4], (int8_t)val[ 5],
		                                    (int8_t)val[ 6], (int8_t)val[ 7],
		                                    (int8_t)val[ 8], (int8_t)val[ 9],
		                                    (int8_t)val[10], (int8_t)val[11],
		                                    (int8_t)val[12], (int8_t)val[13],
		                                    (int8_t)val[14], (int8_t)val[15],
		                                    (int8_t)val[ 0], (int8_t)val[ 1],
		                                    (int8_t)val[ 2], (int8_t)val[ 3],
		                                    (int8_t)val[ 4], (int8_t)val[ 5],
		                                    (int8_t)val[ 6], (int8_t)val[ 7],
		                                    (int8_t)val[ 8], (int8_t)val[ 9],
		                                    (int8_t)val[10], (int8_t)val[11],
		                                    (int8_t)val[12], (int8_t)val[13],
		                                    (int8_t)val[14], (int8_t)val[15]};
		return mipp::set<int8_t>(val_bis);
	}

	// --------------------------------------------------------------------------------------------------------- cmask4
	template <>
	inline reg cmask4<double>(const uint32_t val[nElReg<double>()/4]) {
		int8_t val_bis[nElReg<int8_t>()] = {(int8_t)(val[0]*8 + 0 + 0), (int8_t)(val[0]*8 + 1 + 0),
		                                    (int8_t)(val[0]*8 + 2 + 0), (int8_t)(val[0]*8 + 3 + 0),
		                                    (int8_t)(val[0]*8 + 4 + 0), (int8_t)(val[0]*8 + 5 + 0),
		                                    (int8_t)(val[0]*8 + 6 + 0), (int8_t)(val[0]*8 + 7 + 0),
		                                    (int8_t)(val[0]*8 + 0 + 8), (int8_t)(val[0]*8 + 1 + 8),
		                                    (int8_t)(val[0]*8 + 2 + 8), (int8_t)(val[0]*8 + 3 + 8),
		                                    (int8_t)(val[0]*8 + 4 + 8), (int8_t)(val[0]*8 + 5 + 8),
		                                    (int8_t)(val[0]*8 + 6 + 8), (int8_t)(val[0]*8 + 7 + 8),
		                                    (int8_t)(val[0]*8 + 0 + 0), (int8_t)(val[0]*8 + 1 + 0),
		                                    (int8_t)(val[0]*8 + 2 + 0), (int8_t)(val[0]*8 + 3 + 0),
		                                    (int8_t)(val[0]*8 + 4 + 0), (int8_t)(val[0]*8 + 5 + 0),
		                                    (int8_t)(val[0]*8 + 6 + 0), (int8_t)(val[0]*8 + 7 + 0),
		                                    (int8_t)(val[0]*8 + 0 + 8), (int8_t)(val[0]*8 + 1 + 8),
		                                    (int8_t)(val[0]*8 + 2 + 8), (int8_t)(val[0]*8 + 3 + 8),
		                                    (int8_t)(val[0]*8 + 4 + 8), (int8_t)(val[0]*8 + 5 + 8),
		                                    (int8_t)(val[0]*8 + 6 + 8), (int8_t)(val[0]*8 + 7 + 8)};
		return mipp::set<int8_t>(val_bis);
	}

	template <>
	inline reg cmask4<float>(const uint32_t val[nElReg<float>()/4]) {
		int8_t val_bis[nElReg<int8_t>()] = {(int8_t)(val[0]*4 + 0 + 0), (int8_t)(val[0]*4 + 1 + 0),
		                                    (int8_t)(val[0]*4 + 2 + 0), (int8_t)(val[0]*4 + 3 + 0),
		                                    (int8_t)(val[1]*4 + 0 + 0), (int8_t)(val[1]*4 + 1 + 0),
		                                    (int8_t)(val[1]*4 + 2 + 0), (int8_t)(val[1]*4 + 3 + 0),
		                                    (int8_t)(val[0]*4 + 0 + 8), (int8_t)(val[0]*4 + 1 + 8),
		                                    (int8_t)(val[0]*4 + 2 + 8), (int8_t)(val[0]*4 + 3 + 8),
		                                    (int8_t)(val[1]*4 + 0 + 8), (int8_t)(val[1]*4 + 1 + 8),
		                                    (int8_t)(val[1]*4 + 2 + 8), (int8_t)(val[1]*4 + 3 + 8),
		                                    (int8_t)(val[0]*4 + 0 + 0), (int8_t)(val[0]*4 + 1 + 0),
		                                    (int8_t)(val[0]*4 + 2 + 0), (int8_t)(val[0]*4 + 3 + 0),
		                                    (int8_t)(val[1]*4 + 0 + 0), (int8_t)(val[1]*4 + 1 + 0),
		                                    (int8_t)(val[1]*4 + 2 + 0), (int8_t)(val[1]*4 + 3 + 0),
		                                    (int8_t)(val[0]*4 + 0 + 8), (int8_t)(val[0]*4 + 1 + 8),
		                                    (int8_t)(val[0]*4 + 2 + 8), (int8_t)(val[0]*4 + 3 + 8),
		                                    (int8_t)(val[1]*4 + 0 + 8), (int8_t)(val[1]*4 + 1 + 8),
		                                    (int8_t)(val[1]*4 + 2 + 8), (int8_t)(val[1]*4 + 3 + 8)};
		return mipp::set<int8_t>(val_bis);
	}

	template <>
	inline reg cmask4<int64_t>(const uint32_t val[nElReg<int64_t>()/4]) {
		int8_t val_bis[nElReg<int8_t>()] = {(int8_t)(val[0]*8 + 0 + 0), (int8_t)(val[0]*8 + 1 + 0),
		                                    (int8_t)(val[0]*8 + 2 + 0), (int8_t)(val[0]*8 + 3 + 0),
		                                    (int8_t)(val[0]*8 + 4 + 0), (int8_t)(val[0]*8 + 5 + 0),
		                                    (int8_t)(val[0]*8 + 6 + 0), (int8_t)(val[0]*8 + 7 + 0),
		                                    (int8_t)(val[0]*8 + 0 + 8), (int8_t)(val[0]*8 + 1 + 8),
		                                    (int8_t)(val[0]*8 + 2 + 8), (int8_t)(val[0]*8 + 3 + 8),
		                                    (int8_t)(val[0]*8 + 4 + 8), (int8_t)(val[0]*8 + 5 + 8),
		                                    (int8_t)(val[0]*8 + 6 + 8), (int8_t)(val[0]*8 + 7 + 8),
		                                    (int8_t)(val[0]*8 + 0 + 0), (int8_t)(val[0]*8 + 1 + 0),
		                                    (int8_t)(val[0]*8 + 2 + 0), (int8_t)(val[0]*8 + 3 + 0),
		                                    (int8_t)(val[0]*8 + 4 + 0), (int8_t)(val[0]*8 + 5 + 0),
		                                    (int8_t)(val[0]*8 + 6 + 0), (int8_t)(val[0]*8 + 7 + 0),
		                                    (int8_t)(val[0]*8 + 0 + 8), (int8_t)(val[0]*8 + 1 + 8),
		                                    (int8_t)(val[0]*8 + 2 + 8), (int8_t)(val[0]*8 + 3 + 8),
		                                    (int8_t)(val[0]*8 + 4 + 8), (int8_t)(val[0]*8 + 5 + 8),
		                                    (int8_t)(val[0]*8 + 6 + 8), (int8_t)(val[0]*8 + 7 + 8)};
		return mipp::set<int8_t>(val_bis);
	}

	template <>
	inline reg cmask4<int32_t>(const uint32_t val[nElReg<int32_t>()/4]) {
		int8_t val_bis[nElReg<int8_t>()] = {(int8_t)(val[0]*4 + 0 + 0), (int8_t)(val[0]*4 + 1 + 0),
		                                    (int8_t)(val[0]*4 + 2 + 0), (int8_t)(val[0]*4 + 3 + 0),
		                                    (int8_t)(val[1]*4 + 0 + 0), (int8_t)(val[1]*4 + 1 + 0),
		                                    (int8_t)(val[1]*4 + 2 + 0), (int8_t)(val[1]*4 + 3 + 0),
		                                    (int8_t)(val[0]*4 + 0 + 8), (int8_t)(val[0]*4 + 1 + 8),
		                                    (int8_t)(val[0]*4 + 2 + 8), (int8_t)(val[0]*4 + 3 + 8),
		                                    (int8_t)(val[1]*4 + 0 + 8), (int8_t)(val[1]*4 + 1 + 8),
		                                    (int8_t)(val[1]*4 + 2 + 8), (int8_t)(val[1]*4 + 3 + 8),
		                                    (int8_t)(val[0]*4 + 0 + 0), (int8_t)(val[0]*4 + 1 + 0),
		                                    (int8_t)(val[0]*4 + 2 + 0), (int8_t)(val[0]*4 + 3 + 0),
		                                    (int8_t)(val[1]*4 + 0 + 0), (int8_t)(val[1]*4 + 1 + 0),
		                                    (int8_t)(val[1]*4 + 2 + 0), (int8_t)(val[1]*4 + 3 + 0),
		                                    (int8_t)(val[0]*4 + 0 + 8), (int8_t)(val[0]*4 + 1 + 8),
		                                    (int8_t)(val[0]*4 + 2 + 8), (int8_t)(val[0]*4 + 3 + 8),
		                                    (int8_t)(val[1]*4 + 0 + 8), (int8_t)(val[1]*4 + 1 + 8),
		                                    (int8_t)(val[1]*4 + 2 + 8), (int8_t)(val[1]*4 + 3 + 8)};
		return mipp::set<int8_t>(val_bis);
	}

	template <>
	inline reg cmask4<int16_t>(const uint32_t val[nElReg<int16_t>()/4]) {
		int8_t val_bis[nElReg<int8_t>()] = {(int8_t)(val[ 0]*2 + 0 + 0), (int8_t)(val[ 0]*2 + 1 + 0),
		                                    (int8_t)(val[ 1]*2 + 0 + 0), (int8_t)(val[ 1]*2 + 1 + 0),
		                                    (int8_t)(val[ 2]*2 + 0 + 0), (int8_t)(val[ 2]*2 + 1 + 0),
		                                    (int8_t)(val[ 3]*2 + 0 + 0), (int8_t)(val[ 3]*2 + 1 + 0),
		                                    (int8_t)(val[ 0]*2 + 0 + 8), (int8_t)(val[ 0]*2 + 1 + 8),
		                                    (int8_t)(val[ 1]*2 + 0 + 8), (int8_t)(val[ 1]*2 + 1 + 8),
		                                    (int8_t)(val[ 2]*2 + 0 + 8), (int8_t)(val[ 2]*2 + 1 + 8),
		                                    (int8_t)(val[ 3]*2 + 0 + 8), (int8_t)(val[ 3]*2 + 1 + 8),
		                                    (int8_t)(val[ 0]*2 + 0 + 0), (int8_t)(val[ 0]*2 + 1 + 0),
		                                    (int8_t)(val[ 1]*2 + 0 + 0), (int8_t)(val[ 1]*2 + 1 + 0),
		                                    (int8_t)(val[ 2]*2 + 0 + 0), (int8_t)(val[ 2]*2 + 1 + 0),
		                                    (int8_t)(val[ 3]*2 + 0 + 0), (int8_t)(val[ 3]*2 + 1 + 0),
		                                    (int8_t)(val[ 0]*2 + 0 + 8), (int8_t)(val[ 0]*2 + 1 + 8),
		                                    (int8_t)(val[ 1]*2 + 0 + 8), (int8_t)(val[ 1]*2 + 1 + 8),
		                                    (int8_t)(val[ 2]*2 + 0 + 8), (int8_t)(val[ 2]*2 + 1 + 8),
		                                    (int8_t)(val[ 3]*2 + 0 + 8), (int8_t)(val[ 3]*2 + 1 + 8)};
		return mipp::set<int8_t>(val_bis);
	}

	template <>
	inline reg cmask4<int8_t>(const uint32_t val[nElReg<int8_t>()/4]) {
		int8_t val_bis[nElReg<int8_t>()] = {(int8_t)(val[ 0] + 0), (int8_t)(val[ 1] + 0),
		                                    (int8_t)(val[ 2] + 0), (int8_t)(val[ 3] + 0),
		                                    (int8_t)(val[ 4] + 0), (int8_t)(val[ 5] + 0),
		                                    (int8_t)(val[ 6] + 0), (int8_t)(val[ 7] + 0),
		                                    (int8_t)(val[ 0] + 8), (int8_t)(val[ 1] + 8),
		                                    (int8_t)(val[ 2] + 8), (int8_t)(val[ 3] + 8),
		                                    (int8_t)(val[ 4] + 8), (int8_t)(val[ 5] + 8),
		                                    (int8_t)(val[ 6] + 8), (int8_t)(val[ 7] + 8),
		                                    (int8_t)(val[ 0] + 0), (int8_t)(val[ 1] + 0),
		                                    (int8_t)(val[ 2] + 0), (int8_t)(val[ 3] + 0),
		                                    (int8_t)(val[ 4] + 0), (int8_t)(val[ 5] + 0),
		                                    (int8_t)(val[ 6] + 0), (int8_t)(val[ 7] + 0),
		                                    (int8_t)(val[ 0] + 8), (int8_t)(val[ 1] + 8),
		                                    (int8_t)(val[ 2] + 8), (int8_t)(val[ 3] + 8),
		                                    (int8_t)(val[ 4] + 8), (int8_t)(val[ 5] + 8),
		                                    (int8_t)(val[ 6] + 8), (int8_t)(val[ 7] + 8)};
		return mipp::set<int8_t>(val_bis);
	}

	// ---------------------------------------------------------------------------------------------------------- shuff
	template <>
	inline reg shuff<double>(const reg v, const reg cm) {
		constexpr int N = mipp::N<double>();

		double out[N];
		for (auto i = 0; i < N; i++)
			out[i] = *((double*)&v + (*((int64_t*)&cm +i)));

		return mipp::loadu<double>(out);
	}

	template <>
	inline reg shuff<float>(const reg v, const reg cm) {
		constexpr int N = mipp::N<float>();

		float out[N];
		for (auto i = 0; i < N; i++)
			out[i] = *((float*)&v + (*((int32_t*)&cm +i)));

		return mipp::loadu<float>(out);
	}

	template <>
	inline reg shuff<int64_t>(const reg v, const reg cm) {
		constexpr int N = mipp::N<int64_t>();

		int64_t out[N];
		for (auto i = 0; i < N; i++)
			out[i] = *((int64_t*)&v + (*((int64_t*)&cm +i)));

		return mipp::loadu<int64_t>(out);
	}

	template <>
	inline reg shuff<int32_t>(const reg v, const reg cm) {
		constexpr int N = mipp::N<int32_t>();

		int32_t out[N];
		for (auto i = 0; i < N; i++)
			out[i] = *((int32_t*)&v + (*((int32_t*)&cm +i)));

		return mipp::loadu<int32_t>(out);
	}

	template <>
	inline reg shuff<int16_t>(const reg v, const reg cm) {
		constexpr int N = mipp::N<int16_t>();

		int16_t out[N];
		for (auto i = 0; i < N; i++)
			out[i] = *((int16_t*)&v + (*((int16_t*)&cm +i)));

		return mipp::loadu<int16_t>(out);
	}

	template <>
	inline reg shuff<int8_t>(const reg v, const reg cm) {
		constexpr int N = mipp::N<int8_t>();

		int8_t out[N];
		for (auto i = 0; i < N; i++)
			out[i] = *((int8_t*)&v + (*((int8_t*)&cm +i)));

		return mipp::loadu<int8_t>(out);
	}

	// --------------------------------------------------------------------------------------------------------- shuff2
#ifdef __AVX2__
	template <>
	inline reg shuff2<double>(const reg v, const reg cm) {
		return _mm256_castsi256_ps(_mm256_shuffle_epi8(_mm256_castps_si256(v), _mm256_castps_si256(cm)));
	}

	template <>
	inline reg shuff2<float>(const reg v, const reg cm) {
		return _mm256_castsi256_ps(_mm256_shuffle_epi8(_mm256_castps_si256(v), _mm256_castps_si256(cm)));
	}

	template <>
	inline reg shuff2<int64_t>(const reg v, const reg cm) {
		return _mm256_castsi256_ps(_mm256_shuffle_epi8(_mm256_castps_si256(v), _mm256_castps_si256(cm)));
	}

	template <>
	inline reg shuff2<int32_t>(const reg v, const reg cm) {
		return _mm256_castsi256_ps(_mm256_shuffle_epi8(_mm256_castps_si256(v), _mm256_castps_si256(cm)));
	}

	template <>
	inline reg shuff2<int16_t>(const reg v, const reg cm) {
		return _mm256_castsi256_ps(_mm256_shuffle_epi8(_mm256_castps_si256(v), _mm256_castps_si256(cm)));
	}

	template <>
	inline reg shuff2<int8_t>(const reg v, const reg cm) {
		return _mm256_castsi256_ps(_mm256_shuffle_epi8(_mm256_castps_si256(v), _mm256_castps_si256(cm)));
	}
#endif

	// --------------------------------------------------------------------------------------------------------- shuff4
#ifdef __AVX2__
	template <>
	inline reg shuff4<double>(const reg v, const reg cm) {
		return mipp::shuff2<double>(v, cm);
	}

	template <>
	inline reg shuff4<float>(const reg v, const reg cm) {
		return mipp::shuff2<float>(v, cm);
	}

	template <>
	inline reg shuff4<int64_t>(const reg v, const reg cm) {
		return mipp::shuff2<int64_t>(v, cm);
	}

	template <>
	inline reg shuff4<int32_t>(const reg v, const reg cm) {
		return mipp::shuff2<int32_t>(v, cm);
	}

	template <>
	inline reg shuff4<int16_t>(const reg v, const reg cm) {
		return mipp::shuff2<int16_t>(v, cm);
	}

	template <>
	inline reg shuff4<int8_t>(const reg v, const reg cm) {
		return mipp::shuff2<int8_t>(v, cm);
	}
#endif

	// -------------------------------------------------------------------------------------------------- interleavelo2
#ifdef __AVX2__
	template <>
	inline reg interleavelo2<double>(const reg v1, const reg v2) {
		return _mm256_castsi256_ps(_mm256_unpacklo_epi64(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}

	template <>
	inline reg interleavelo2<float>(const reg v1, const reg v2) {
		// v1  = [a0, b0, c0, d0, e0, f0, g0, h0], v2 = [a1, b1, c1, d1, e1, f1, g1, h1]
		// res = [a0, a1, b0, b1, e0, e1, f0, f1]
		return _mm256_castsi256_ps(_mm256_unpacklo_epi32(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}

	template <>
	inline reg interleavelo2<int64_t>(const reg v1, const reg v2) {
		return _mm256_castsi256_ps(_mm256_unpacklo_epi64(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}

	template <>
	inline reg interleavelo2<int32_t>(const reg v1, const reg v2) {
		// v1  = [a0, b0, c0, d0, e0, f0, g0, h0], v2 = [a1, b1, c1, d1, e1, f1, g1, h1]
		// res = [a0, a1, b0, b1, e0, e1, f0, f1]
		return _mm256_castsi256_ps(_mm256_unpacklo_epi32(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}

	template <>
	inline reg interleavelo2<int16_t>(const reg v1, const reg v2) {
		return _mm256_castsi256_ps(_mm256_unpacklo_epi16(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}

	template <>
	inline reg interleavelo2<int8_t>(const reg v1, const reg v2) {
		return _mm256_castsi256_ps(_mm256_unpacklo_epi8(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}
#endif

	// -------------------------------------------------------------------------------------------------- interleavehi2
#ifdef __AVX2__
	template <>
	inline reg interleavehi2<double>(const reg v1, const reg v2) {
		return _mm256_castsi256_ps(_mm256_unpackhi_epi64(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}

	template <>
	inline reg interleavehi2<float>(const reg v1, const reg v2) {
		// v1  = [a0, b0, c0, d0, e0, f0, g0, h0], v2 = [a1, b1, c1, d1, e1, f1, g1, h1]
		// res = [c0, c1, d0, d1, g0, g1, h0, h1]
		return _mm256_castsi256_ps(_mm256_unpackhi_epi32(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}

	template <>
	inline reg interleavehi2<int64_t>(const reg v1, const reg v2) {
		return _mm256_castsi256_ps(_mm256_unpackhi_epi64(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}

	template <>
	inline reg interleavehi2<int32_t>(const reg v1, const reg v2) {
		// v1  = [a0, b0, c0, d0, e0, f0, g0, h0], v2 = [a1, b1, c1, d1, e1, f1, g1, h1]
		// res = [c0, c1, d0, d1, g0, g1, h0, h1]
		return _mm256_castsi256_ps(_mm256_unpackhi_epi32(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}

	template <>
	inline reg interleavehi2<int16_t>(const reg v1, const reg v2) {
		return _mm256_castsi256_ps(_mm256_unpackhi_epi16(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}

	template <>
	inline reg interleavehi2<int8_t>(const reg v1, const reg v2) {
		return _mm256_castsi256_ps(_mm256_unpackhi_epi8(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}
#endif

	// ----------------------------------------------------------------------------------------------------- interleave
#ifdef __AVX2__
	template <>
	inline regx2 interleave<double>(const reg v1, const reg v2) {
		auto lo = _mm256_unpacklo_epi64(_mm256_castps_si256(v1), _mm256_castps_si256(v2));
		auto hi = _mm256_unpackhi_epi64(_mm256_castps_si256(v1), _mm256_castps_si256(v2));

		return {{_mm256_castsi256_ps(_mm256_permute2f128_si256(lo, hi, _MM_SHUFFLE(0,2,0,0))),
		         _mm256_castsi256_ps(_mm256_permute2f128_si256(lo, hi, _MM_SHUFFLE(0,3,0,1)))}};
	}

	template <>
	inline regx2 interleave<int64_t>(const reg v1, const reg v2) {
		auto lo = _mm256_unpacklo_epi64(_mm256_castps_si256(v1), _mm256_castps_si256(v2));
		auto hi = _mm256_unpackhi_epi64(_mm256_castps_si256(v1), _mm256_castps_si256(v2));

		return {{_mm256_castsi256_ps(_mm256_permute2f128_si256(lo, hi, _MM_SHUFFLE(0,2,0,0))),
		         _mm256_castsi256_ps(_mm256_permute2f128_si256(lo, hi, _MM_SHUFFLE(0,3,0,1)))}};
	}

	template <>
	inline regx2 interleave<float>(const reg v1, const reg v2) {
		// v1         = [a0, b0, c0, d0, e0, f0, g0, h0], v2         = [a1, b1, c1, d1, e1, f1, g1, h1]
		// res.val[0] = [a0, a1, b0, b1, c0, c1, d0, d1], res.val[1] = [e0, e1, f0, f1, g0, g1, h0, h1]
		auto lo = _mm256_unpacklo_epi32(_mm256_castps_si256(v1), _mm256_castps_si256(v2));
		auto hi = _mm256_unpackhi_epi32(_mm256_castps_si256(v1), _mm256_castps_si256(v2));

		return {{_mm256_castsi256_ps(_mm256_permute2f128_si256(lo, hi, _MM_SHUFFLE(0,2,0,0))),
		         _mm256_castsi256_ps(_mm256_permute2f128_si256(lo, hi, _MM_SHUFFLE(0,3,0,1)))}};
	}

	template <>
	inline regx2 interleave<int32_t>(const reg v1, const reg v2) {
		// v1         = [a0, b0, c0, d0, e0, f0, g0, h0], v2         = [a1, b1, c1, d1, e1, f1, g1, h1]
		// res.val[0] = [a0, a1, b0, b1, c0, c1, d0, d1], res.val[1] = [e0, e1, f0, f1, g0, g1, h0, h1]
		auto lo = _mm256_unpacklo_epi32(_mm256_castps_si256(v1), _mm256_castps_si256(v2));
		auto hi = _mm256_unpackhi_epi32(_mm256_castps_si256(v1), _mm256_castps_si256(v2));

		return {{_mm256_castsi256_ps(_mm256_permute2f128_si256(lo, hi, _MM_SHUFFLE(0,2,0,0))),
		         _mm256_castsi256_ps(_mm256_permute2f128_si256(lo, hi, _MM_SHUFFLE(0,3,0,1)))}};
	}

	template <>
	inline regx2 interleave<int16_t>(const reg v1, const reg v2) {
		auto lo = _mm256_unpacklo_epi16(_mm256_castps_si256(v1), _mm256_castps_si256(v2));
		auto hi = _mm256_unpackhi_epi16(_mm256_castps_si256(v1), _mm256_castps_si256(v2));

		return {{_mm256_castsi256_ps(_mm256_permute2f128_si256(lo, hi, _MM_SHUFFLE(0,2,0,0))),
		         _mm256_castsi256_ps(_mm256_permute2f128_si256(lo, hi, _MM_SHUFFLE(0,3,0,1)))}};
	}

	template <>
	inline regx2 interleave<int8_t>(const reg v1, const reg v2) {
		auto lo = _mm256_unpacklo_epi8(_mm256_castps_si256(v1), _mm256_castps_si256(v2));
		auto hi = _mm256_unpackhi_epi8(_mm256_castps_si256(v1), _mm256_castps_si256(v2));

		return {{_mm256_castsi256_ps(_mm256_permute2f128_si256(lo, hi, _MM_SHUFFLE(0,2,0,0))),
		         _mm256_castsi256_ps(_mm256_permute2f128_si256(lo, hi, _MM_SHUFFLE(0,3,0,1)))}};
	}
#endif

	// ----------------------------------------------------------------------------------------------------- interleave
	template <>
	inline reg interleave<double>(const reg v) {
		auto v_permute = _mm256_permute2f128_pd(_mm256_castps_pd(v), _mm256_castps_pd(v), _MM_SHUFFLE(0,0,0,3));

		auto lo = _mm256_unpacklo_pd(_mm256_castps_pd(v), v_permute);
		auto hi = _mm256_unpackhi_pd(_mm256_castps_pd(v), v_permute);

		return _mm256_castpd_ps(_mm256_permute2f128_pd(lo, hi, _MM_SHUFFLE(0,2,0,0)));
	}

	template <>
	inline reg interleave<float>(const reg v) {
		auto v_permute = _mm256_permute2f128_ps(v, v, _MM_SHUFFLE(0,0,0,3));

		auto lo = _mm256_unpacklo_ps(v, v_permute);
		auto hi = _mm256_unpackhi_ps(v, v_permute);

		return _mm256_permute2f128_ps(lo, hi, _MM_SHUFFLE(0,2,0,0));
	}

	template <>
	inline reg interleave<int64_t>(const reg v) {
		return interleave<double>(v);
	}

	template <>
	inline reg interleave<int32_t>(const reg v) {
		return interleave<float>(v);
	}

#ifdef __AVX2__
	template <>
	inline reg interleave<int16_t>(const reg v) {
		auto v_permute = _mm256_permute2f128_si256(_mm256_castps_si256(v), _mm256_castps_si256(v), _MM_SHUFFLE(0,0,0,3));

		auto lo = _mm256_unpacklo_epi16(_mm256_castps_si256(v), v_permute);
		auto hi = _mm256_unpackhi_epi16(_mm256_castps_si256(v), v_permute);

		return _mm256_castsi256_ps(_mm256_permute2f128_si256(lo, hi, _MM_SHUFFLE(0,2,0,0)));
	}

	template <>
	inline reg interleave<int8_t>(const reg v) {
		auto v_permute = _mm256_permute2f128_si256(_mm256_castps_si256(v), _mm256_castps_si256(v), _MM_SHUFFLE(0,0,0,3));

		auto lo = _mm256_unpacklo_epi8(_mm256_castps_si256(v), v_permute);
		auto hi = _mm256_unpackhi_epi8(_mm256_castps_si256(v), v_permute);

		return _mm256_castsi256_ps(_mm256_permute2f128_si256(lo, hi, _MM_SHUFFLE(0,2,0,0)));
	}
#endif

	// --------------------------------------------------------------------------------------------------- interleavelo
	template <>
	inline reg interleavelo<double>(const reg v1, const reg v2) {
		auto rx2 = interleave<double>(v1, v2);
		return rx2.val[0];
	}

	template <>
	inline reg interleavelo<float>(const reg v1, const reg v2) {
		auto rx2 = interleave<float>(v1, v2);
		return rx2.val[0];
	}

	template <>
	inline reg interleavelo<int64_t>(const reg v1, const reg v2) {
		auto rx2 = interleave<int64_t>(v1, v2);
		return rx2.val[0];
	}

	template <>
	inline reg interleavelo<int32_t>(const reg v1, const reg v2) {
		auto rx2 = interleave<int32_t>(v1, v2);
		return rx2.val[0];
	}

	template <>
	inline reg interleavelo<int16_t>(const reg v1, const reg v2) {
		auto rx2 = interleave<int16_t>(v1, v2);
		return rx2.val[0];
	}

	template <>
	inline reg interleavelo<int8_t>(const reg v1, const reg v2) {
		auto rx2 = interleave<int8_t>(v1, v2);
		return rx2.val[0];
	}

	// --------------------------------------------------------------------------------------------------- interleavehi
	template <>
	inline reg interleavehi<double>(const reg v1, const reg v2) {
		auto rx2 = interleave<double>(v1, v2);
		return rx2.val[1];
	}

	template <>
	inline reg interleavehi<int64_t>(const reg v1, const reg v2) {
		auto rx2 = interleave<int64_t>(v1, v2);
		return rx2.val[1];
	}

	template <>
	inline reg interleavehi<float>(const reg v1, const reg v2) {
		auto rx2 = interleave<float>(v1, v2);
		return rx2.val[1];
	}

	template <>
	inline reg interleavehi<int32_t>(const reg v1, const reg v2) {
		auto rx2 = interleave<int32_t>(v1, v2);
		return rx2.val[1];
	}

	template <>
	inline reg interleavehi<int16_t>(const reg v1, const reg v2) {
		auto rx2 = interleave<int16_t>(v1, v2);
		return rx2.val[1];
	}

	template <>
	inline reg interleavehi<int8_t>(const reg v1, const reg v2) {
		auto rx2 = interleave<int8_t>(v1, v2);
		return rx2.val[1];
	}

	// ---------------------------------------------------------------------------------------------------- interleave2
	template <>
	inline regx2 interleave2<double>(const reg v1, const reg v2) {
		regx2 res = {{mipp::interleavelo2<double>(v1, v2), mipp::interleavehi2<double>(v1, v2)}};
		return res;
	}

	template <>
	inline regx2 interleave2<float>(const reg v1, const reg v2) {
		regx2 res = {{mipp::interleavelo2<float>(v1, v2), mipp::interleavehi2<float>(v1, v2)}};
		return res;
	}

	template <>
	inline regx2 interleave2<int64_t>(const reg v1, const reg v2) {
		regx2 res = {{mipp::interleavelo2<int64_t>(v1, v2), mipp::interleavehi2<int64_t>(v1, v2)}};
		return res;
	}

	template <>
	inline regx2 interleave2<int32_t>(const reg v1, const reg v2) {
		regx2 res = {{mipp::interleavelo2<int32_t>(v1, v2), mipp::interleavehi2<int32_t>(v1, v2)}};
		return res;
	}

	template <>
	inline regx2 interleave2<int16_t>(const reg v1, const reg v2) {
		regx2 res = {{mipp::interleavelo2<int16_t>(v1, v2), mipp::interleavehi2<int16_t>(v1, v2)}};
		return res;
	}

	template <>
	inline regx2 interleave2<int8_t>(const reg v1, const reg v2) {
		regx2 res = {{mipp::interleavelo2<int8_t>(v1, v2), mipp::interleavehi2<int8_t>(v1, v2)}};
		return res;
	}

	// --------------------------------------------------------------------------------------------------- interleavex2
#ifdef __AVX2__
	template <>
	inline regx2 interleavex2<float>(const reg v1, const reg v2) {
		// v1         = [a, b, c, d,| e, f, g, h]
		// v2         = [A, B, C, D,| E, F, G, H]
		// =>
		// res.val[0] = [a, b, c, d,| A, B, C, D]
		// res.val[1] = [e, f, g, h,| E, F, G, H]
		auto lo = _mm256_castsi256_ps(_mm256_permute2f128_si256(_mm256_castps_si256(v1),
		                                                        _mm256_castps_si256(v2),
		                                                        _MM_SHUFFLE(0,2,0,0)));
		auto hi = _mm256_castsi256_ps(_mm256_permute2f128_si256(_mm256_castps_si256(v1),
		                                                        _mm256_castps_si256(v2),
		                                                        _MM_SHUFFLE(0,3,0,1)));
		regx2 res = {{lo, hi}};
		return res;
	}
#endif

	// --------------------------------------------------------------------------------------------------- interleavex4
#ifdef __AVX2__
	template <>
	inline reg interleavex4<int16_t>(const reg v) {
		// [a, b, c, d,| e, f, g, h,| i, j, k, l,| m, n, o, p]
		// =>
		// [a, b, c, d,| i, j, k, l,| e, f, g, h,| m, n, o, p]
		return _mm256_castsi256_ps(_mm256_permute4x64_epi64(_mm256_castps_si256(v), _MM_SHUFFLE(3,1,2,0)));
	}

	template <>
	inline reg interleavex4<int8_t>(const reg v) {
		return _mm256_castsi256_ps(_mm256_permute4x64_epi64(_mm256_castps_si256(v), _MM_SHUFFLE(3,1,2,0)));
	}
#endif

	// -------------------------------------------------------------------------------------------------- interleavex16
	template <>
	inline reg interleavex16<int8_t>(const reg v) {
		return mipp::interleave<int16_t>(v);
	}

	// ------------------------------------------------------------------------------------------------------ transpose
#ifdef __AVX2__
	template <>
	inline void transpose<float>(reg tab[nElReg<float>()]) {
		// Transpose the 8x8 matrix:
		// -------------------------
		// tab[0] = [a0, a1, a2, a3, a4, a5, a6, a7]        tab[0] = [a0, b0, c0, d0, e0, f0, g0, h0]
		// tab[1] = [b0, b1, b2, b3, b4, b5, b6, b7]        tab[1] = [a1, b1, c1, d1, e1, f1, g1, h1]
		// tab[2] = [c0, c1, c2, c3, c4, c5, c6, c7]        tab[2] = [a2, b2, c2, d2, e2, f2, g2, h2]
		// tab[3] = [d0, d1, d2, d3, d4, d5, d6, d7]        tab[3] = [a3, b3, c3, d3, e3, f3, g3, h3]
		// tab[4] = [e0, e1, e2, e3, e4, e5, e6, e7]   =>   tab[4] = [a4, b4, c4, d4, e4, f4, g4, h4]
		// tab[5] = [f0, f1, f2, f3, f4, f5, f6, f7]        tab[5] = [a5, b5, c5, d5, e5, f5, g5, h5]
		// tab[6] = [g0, g1, g2, g3, g4, g5, g6, g7]        tab[6] = [a6, b6, c6, d6, e6, f6, g6, h6]
		// tab[7] = [h0, h1, h2, h3, h4, h5, h6, h7]        tab[7] = [a7, b7, c7, d7, e7, f7, g7, h7]

		auto ab = mipp::interleave<float>(tab[0], tab[1]);
		auto cd = mipp::interleave<float>(tab[2], tab[3]);
		auto ef = mipp::interleave<float>(tab[4], tab[5]);
		auto gh = mipp::interleave<float>(tab[6], tab[7]);

		auto a03b03 = ab.val[0];
		auto c03d03 = cd.val[0];
		auto e03f03 = ef.val[0];
		auto g03h03 = gh.val[0];
		auto a47b47 = ab.val[1];
		auto c47d47 = cd.val[1];
		auto e47f47 = ef.val[1];
		auto g47h47 = gh.val[1];

		auto a03b03c03d03 = mipp::interleave<int64_t>(a03b03, c03d03);
		auto e03f03g03h03 = mipp::interleave<int64_t>(e03f03, g03h03);
		auto a47b47c47d47 = mipp::interleave<int64_t>(a47b47, c47d47);
		auto e47f47g47h47 = mipp::interleave<int64_t>(e47f47, g47h47);

		auto a01b01c01d01 = a03b03c03d03.val[0];
		auto a23b23c23d23 = a03b03c03d03.val[1];
		auto e01f01g01h01 = e03f03g03h03.val[0];
		auto e23f23g23h23 = e03f03g03h03.val[1];
		auto a45b45c45d45 = a47b47c47d47.val[0];
		auto a67b67c67d67 = a47b47c47d47.val[1];
		auto e45f45g45h45 = e47f47g47h47.val[0];
		auto e67f67g67h67 = e47f47g47h47.val[1];

		auto a01b01c01d01e01f01g01h01 = mipp::interleavex2<float>(a01b01c01d01, e01f01g01h01);
		auto a23b23c23d23e23f23g23h23 = mipp::interleavex2<float>(a23b23c23d23, e23f23g23h23);
		auto a45b45c45d45e45f45g45h45 = mipp::interleavex2<float>(a45b45c45d45, e45f45g45h45);
		auto a67b67c67d67e67f67g67h67 = mipp::interleavex2<float>(a67b67c67d67, e67f67g67h67);

		auto a0b0c0d0e0f0g0h0 = a01b01c01d01e01f01g01h01.val[0];
		auto a1b1c1d1e1f1g1h1 = a01b01c01d01e01f01g01h01.val[1];
		auto a2b2c2d2e2f2g2h2 = a23b23c23d23e23f23g23h23.val[0];
		auto a3b3c3d3e3f3g3h3 = a23b23c23d23e23f23g23h23.val[1];
		auto a4b4c4d4e4f4g4h4 = a45b45c45d45e45f45g45h45.val[0];
		auto a5b5c5d5e5f5g5h5 = a45b45c45d45e45f45g45h45.val[1];
		auto a6b6c6d6e6f6g6h6 = a67b67c67d67e67f67g67h67.val[0];
		auto a7b7c7d7e7f7g7h7 = a67b67c67d67e67f67g67h67.val[1];

		tab[0] = (reg)a0b0c0d0e0f0g0h0;
		tab[1] = (reg)a1b1c1d1e1f1g1h1;
		tab[2] = (reg)a2b2c2d2e2f2g2h2;
		tab[3] = (reg)a3b3c3d3e3f3g3h3;
		tab[4] = (reg)a4b4c4d4e4f4g4h4;
		tab[5] = (reg)a5b5c5d5e5f5g5h5;
		tab[6] = (reg)a6b6c6d6e6f6g6h6;
		tab[7] = (reg)a7b7c7d7e7f7g7h7;
	}
#endif

	// ----------------------------------------------------------------------------------------------------- transpose2
#ifdef __AVX2__
	template <>
	inline void transpose2<int16_t>(reg tab[nElReg<int16_t>()/2]) {
		// Transpose the 8x8 matrix:
		// -------------------------
		//
		// Input:
		// ------
		// tab[0] = [a0, a1, a2, a3, a4, a5, a6, a7,  A0, A1, A2, A3, A4, A5, A6, A7]
		// tab[1] = [b0, b1, b2, b3, b4, b5, b6, b7,  B0, B1, B2, B3, B4, B5, B6, B7]
		// tab[2] = [c0, c1, c2, c3, c4, c5, c6, c7,  C0, C1, C2, C3, C4, C5, C6, C7]
		// tab[3] = [d0, d1, d2, d3, d4, d5, d6, d7,  D0, D1, D2, D3, D4, D5, D6, D7]
		// tab[4] = [e0, e1, e2, e3, e4, e5, e6, e7,  E0, E1, E2, E3, E4, E5, E6, E7]
		// tab[5] = [f0, f1, f2, f3, f4, f5, f6, f7,  F0, F1, F2, F3, F4, F5, F6, F7]
		// tab[6] = [g0, g1, g2, g3, g4, g5, g6, g7,  G0, G1, G2, G3, G4, G5, G6, G7]
		// tab[7] = [h0, h1, h2, h3, h4, h5, h6, h7,  H0, H1, H2, H3, H4, H5, H6, H7]
		//
		// Output:
		// -------
		// tab[0] = [a0, b0, c0, d0, e0, f0, g0, h0,  A0, B0, C0, D0, E0, F0, G0, H0]
		// tab[1] = [a1, b1, c1, d1, e1, f1, g1, h1,  A1, B1, C1, D1, E1, F1, G1, H1]
		// tab[2] = [a2, b2, c2, d2, e2, f2, g2, h2,  A2, B2, C2, D2, E2, F2, G2, H2]
		// tab[3] = [a3, b3, c3, d3, e3, f3, g3, h3,  A3, B3, C3, D3, E3, F3, G3, H3]
		// tab[4] = [a4, b4, c4, d4, e4, f4, g4, h4,  A4, B4, C4, D4, E4, F4, G4, H4]
		// tab[5] = [a5, b5, c5, d5, e5, f5, g5, h5,  A5, B5, C5, D5, E5, F5, G5, H5]
		// tab[6] = [a6, b6, c6, d6, e6, f6, g6, h6,  A6, B6, C6, D6, E6, F6, G6, H6]
		// tab[7] = [a7, b7, c7, d7, e7, f7, g7, h7,  A7, B7, C7, D7, E7, F7, G7, H7]

		auto a03b03 = mipp::interleavelo2<int16_t>(tab[0], tab[1]);
		auto c03d03 = mipp::interleavelo2<int16_t>(tab[2], tab[3]);
		auto e03f03 = mipp::interleavelo2<int16_t>(tab[4], tab[5]);
		auto g03h03 = mipp::interleavelo2<int16_t>(tab[6], tab[7]);
		auto a47b47 = mipp::interleavehi2<int16_t>(tab[0], tab[1]);
		auto c47d47 = mipp::interleavehi2<int16_t>(tab[2], tab[3]);
		auto e47f47 = mipp::interleavehi2<int16_t>(tab[4], tab[5]);
		auto g47h47 = mipp::interleavehi2<int16_t>(tab[6], tab[7]);

		auto a01b01c01d01 = mipp::interleavelo2<int32_t>(a03b03, c03d03);
		auto a23b23c23d23 = mipp::interleavehi2<int32_t>(a03b03, c03d03);
		auto e01f01g01h01 = mipp::interleavelo2<int32_t>(e03f03, g03h03);
		auto e23f23g23h23 = mipp::interleavehi2<int32_t>(e03f03, g03h03);
		auto a45b45c45d45 = mipp::interleavelo2<int32_t>(a47b47, c47d47);
		auto a67b67c67d67 = mipp::interleavehi2<int32_t>(a47b47, c47d47);
		auto e45f45g45h45 = mipp::interleavelo2<int32_t>(e47f47, g47h47);
		auto e67f67g67h67 = mipp::interleavehi2<int32_t>(e47f47, g47h47);

		auto a0b0c0d0e0f0g0h0 = mipp::interleavelo2<int64_t>(a01b01c01d01, e01f01g01h01);
		auto a1b1c1d1e1f1g1h1 = mipp::interleavehi2<int64_t>(a01b01c01d01, e01f01g01h01);
		auto a2b2c2d2e2f2g2h2 = mipp::interleavelo2<int64_t>(a23b23c23d23, e23f23g23h23);
		auto a3b3c3d3e3f3g3h3 = mipp::interleavehi2<int64_t>(a23b23c23d23, e23f23g23h23);
		auto a4b4c4d4e4f4g4h4 = mipp::interleavelo2<int64_t>(a45b45c45d45, e45f45g45h45);
		auto a5b5c5d5e5f5g5h5 = mipp::interleavehi2<int64_t>(a45b45c45d45, e45f45g45h45);
		auto a6b6c6d6e6f6g6h6 = mipp::interleavelo2<int64_t>(a67b67c67d67, e67f67g67h67);
		auto a7b7c7d7e7f7g7h7 = mipp::interleavehi2<int64_t>(a67b67c67d67, e67f67g67h67);

		tab[0] = (reg)a0b0c0d0e0f0g0h0;
		tab[1] = (reg)a1b1c1d1e1f1g1h1;
		tab[2] = (reg)a2b2c2d2e2f2g2h2;
		tab[3] = (reg)a3b3c3d3e3f3g3h3;
		tab[4] = (reg)a4b4c4d4e4f4g4h4;
		tab[5] = (reg)a5b5c5d5e5f5g5h5;
		tab[6] = (reg)a6b6c6d6e6f6g6h6;
		tab[7] = (reg)a7b7c7d7e7f7g7h7;
	}
#endif

	// -------------------------------------------------------------------------------------------------- transpose28x8
	template <>
	inline void transpose28x8<int8_t>(reg tab[8]) {
		mipp::transpose2<int16_t>(tab);
	}

	// ----------------------------------------------------------------------------------------------------------- andb
	template <>
	inline reg andb<double>(const reg v1, const reg v2) {
		return _mm256_castpd_ps(_mm256_and_pd(_mm256_castps_pd(v1), _mm256_castps_pd(v2)));
	}

	template <>
	inline reg andb<float>(const reg v1, const reg v2) {
		return _mm256_and_ps(v1, v2);
	}

	template <>
	inline reg andb<int64_t>(const reg v1, const reg v2) {
		return _mm256_castpd_ps(_mm256_and_pd(_mm256_castps_pd(v1), _mm256_castps_pd(v2)));
	}

	template <>
	inline reg andb<int32_t>(const reg v1, const reg v2) {
		return _mm256_and_ps(v1, v2);
	}

#ifdef __AVX2__
	template <>
	inline reg andb<int16_t>(const reg v1, const reg v2) {
		return _mm256_castsi256_ps(_mm256_and_si256(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}

	template <>
	inline reg andb<int8_t>(const reg v1, const reg v2) {
		return _mm256_castsi256_ps(_mm256_and_si256(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}
#endif

	// ---------------------------------------------------------------------------------------------------- andb (mask)
	template <>
	inline msk andb<4>(const msk v1, const msk v2) {
		return _mm256_castpd_si256(_mm256_and_pd(_mm256_castsi256_pd(v1), _mm256_castsi256_pd(v2)));
	}

	template <>
	inline msk andb<8>(const msk v1, const msk v2) {
		return _mm256_castps_si256(_mm256_and_ps(_mm256_castsi256_ps(v1), _mm256_castsi256_ps(v2)));
	}

#ifdef __AVX2__
	template <>
	inline msk andb<16>(const msk v1, const msk v2) {
		return _mm256_and_si256(v1, v2);
	}

	template <>
	inline msk andb<32>(const msk v1, const msk v2) {
		return _mm256_and_si256(v1, v2);
	}
#endif

	// ---------------------------------------------------------------------------------------------------------- andnb
	template <>
	inline reg andnb<double>(const reg v1, const reg v2) {
		return _mm256_castpd_ps(_mm256_andnot_pd(_mm256_castps_pd(v1), _mm256_castps_pd(v2)));
	}

	template <>
	inline reg andnb<float>(const reg v1, const reg v2) {
		return _mm256_andnot_ps(v1, v2);
	}

	template <>
	inline reg andnb<int64_t>(const reg v1, const reg v2) {
		return _mm256_castpd_ps(_mm256_andnot_pd(_mm256_castps_pd(v1), _mm256_castps_pd(v2)));
	}

	template <>
	inline reg andnb<int32_t>(const reg v1, const reg v2) {
		return _mm256_andnot_ps(v1, v2);
	}

#ifdef __AVX2__
	template <>
	inline reg andnb<int16_t>(const reg v1, const reg v2) {
		return _mm256_castsi256_ps(_mm256_andnot_si256(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}

	template <>
	inline reg andnb<int8_t>(const reg v1, const reg v2) {
		return _mm256_castsi256_ps(_mm256_andnot_si256(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}
#endif

	// --------------------------------------------------------------------------------------------------- andnb (mask)
	template <>
	inline msk andnb<4>(const msk v1, const msk v2) {
		return _mm256_castpd_si256(_mm256_andnot_pd(_mm256_castsi256_pd(v1), _mm256_castsi256_pd(v2)));
	}

	template <>
	inline msk andnb<8>(const msk v1, const msk v2) {
		return _mm256_castps_si256(_mm256_andnot_ps(_mm256_castsi256_ps(v1), _mm256_castsi256_ps(v2)));
	}

#ifdef __AVX2__
	template <>
	inline msk andnb<16>(const msk v1, const msk v2) {
		return _mm256_andnot_si256(v1, v2);
	}

	template <>
	inline msk andnb<32>(const msk v1, const msk v2) {
		return _mm256_andnot_si256(v1, v2);
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- notb
	template <>
	inline reg notb<float>(const reg v) {
		return andnb<float>(v, set1<int32_t>(0xFFFFFFFF));
	}

	template <>
	inline reg notb<double>(const reg v) {
		return andnb<double>(v, set1<int64_t>(0xFFFFFFFFFFFFFFFF));
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
	inline msk notb<4>(const msk v) {
		return andnb<4>(v, _mm256_castps_si256(set1<int64_t>(0xFFFFFFFFFFFFFFFF)));
	}

	template <>
	inline msk notb<8>(const msk v) {
		return andnb<8>(v, _mm256_castps_si256(set1<int32_t>(0xFFFFFFFF)));
	}

	template <>
	inline msk notb<16>(const msk v) {
#ifdef _MSC_VER
#pragma warning( disable : 4309 )
#endif
		return andnb<16>(v, _mm256_castps_si256(set1<int16_t>(0xFFFF)));
#ifdef _MSC_VER
#pragma warning( default : 4309 )
#endif
	}

	template <>
	inline msk notb<32>(const msk v) {
#ifdef _MSC_VER
#pragma warning( disable : 4309 )
#endif
		return andnb<32>(v, _mm256_castps_si256(set1<int8_t>(0xFF)));
#ifdef _MSC_VER
#pragma warning( default : 4309 )
#endif
	}

	// ------------------------------------------------------------------------------------------------------------ orb
	template <>
	inline reg orb<float>(const reg v1, const reg v2) {
		return _mm256_or_ps(v1, v2);
	}

	template <>
	inline reg orb<double>(const reg v1, const reg v2) {
		return _mm256_castpd_ps(_mm256_or_pd(_mm256_castps_pd(v1), _mm256_castps_pd(v2)));
	}

	template <>
	inline reg orb<int64_t>(const reg v1, const reg v2) {
		return _mm256_castpd_ps(_mm256_or_pd(_mm256_castps_pd(v1), _mm256_castps_pd(v2)));
	}

	template <>
	inline reg orb<int32_t>(const reg v1, const reg v2) {
		return _mm256_or_ps(v1, v2);
	}

#ifdef __AVX2__
	template <>
	inline reg orb<int16_t>(const reg v1, const reg v2) {
		return _mm256_castsi256_ps(_mm256_or_si256(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}

	template <>
	inline reg orb<int8_t>(const reg v1, const reg v2) {
		return _mm256_castsi256_ps(_mm256_or_si256(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}
#endif

	// ----------------------------------------------------------------------------------------------------- orb (mask)
	template <>
	inline msk orb<4>(const msk v1, const msk v2) {
		return _mm256_castpd_si256(_mm256_or_pd(_mm256_castsi256_pd(v1), _mm256_castsi256_pd(v2)));
	}

	template <>
	inline msk orb<8>(const msk v1, const msk v2) {
		return _mm256_castps_si256(_mm256_or_ps(_mm256_castsi256_ps(v1), _mm256_castsi256_ps(v2)));
	}

#ifdef __AVX2__
	template <>
	inline msk orb<16>(const msk v1, const msk v2) {
		return _mm256_or_si256(v1, v2);
	}

	template <>
	inline msk orb<32>(const msk v1, const msk v2) {
		return _mm256_or_si256(v1, v2);
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- xorb
	template <>
	inline reg xorb<float>(const reg v1, const reg v2) {
		return _mm256_xor_ps(v1, v2);
	}

	template <>
	inline reg xorb<double>(const reg v1, const reg v2) {
		return _mm256_castpd_ps(_mm256_xor_pd(_mm256_castps_pd(v1), _mm256_castps_pd(v2)));
	}

	template <>
	inline reg xorb<int64_t>(const reg v1, const reg v2) {
		return _mm256_castpd_ps(_mm256_xor_pd(_mm256_castps_pd(v1), _mm256_castps_pd(v2)));
	}

	template <>
	inline reg xorb<int32_t>(const reg v1, const reg v2) {
		return _mm256_xor_ps(v1, v2);
	}

#ifdef __AVX2__
	template <>
	inline reg xorb<int16_t>(const reg v1, const reg v2) {
		return _mm256_castsi256_ps(_mm256_xor_si256(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}

	template <>
	inline reg xorb<int8_t>(const reg v1, const reg v2) {
		return _mm256_castsi256_ps(_mm256_xor_si256(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}
#endif

	// ---------------------------------------------------------------------------------------------------- xorb (mask)
	template <>
	inline msk xorb<4>(const msk v1, const msk v2) {
		return _mm256_castps_si256(_mm256_xor_ps(_mm256_castsi256_ps(v1), _mm256_castsi256_ps(v2)));
	}

	template <>
	inline msk xorb<8>(const msk v1, const msk v2) {
		return _mm256_castps_si256(_mm256_xor_ps(_mm256_castsi256_ps(v1), _mm256_castsi256_ps(v2)));
	}

#ifdef __AVX2__
	template <>
	inline msk xorb<16>(const msk v1, const msk v2) {
		return _mm256_xor_si256(v1, v2);
	}

	template <>
	inline msk xorb<32>(const msk v1, const msk v2) {
		return _mm256_xor_si256(v1, v2);
	}
#endif

	// --------------------------------------------------------------------------------------------------------- lshift
#ifdef __AVX2__
	template <>
	inline reg lshift<int64_t>(const reg v1, const uint32_t n) {
		return _mm256_castsi256_ps(_mm256_slli_epi64(_mm256_castps_si256(v1), n));
	}

	template <>
	inline reg lshift<int32_t>(const reg v1, const uint32_t n) {
		return _mm256_castsi256_ps(_mm256_slli_epi32(_mm256_castps_si256(v1), n));
	}

	template <>
	inline reg lshift<int16_t>(const reg v1, const uint32_t n) {
		return _mm256_castsi256_ps(_mm256_slli_epi16(_mm256_castps_si256(v1), n));
	}

	template <>
	inline reg lshift<int8_t>(const reg v1, const uint32_t n) {
//		auto shu = _mm256_set_epi8(30,31,28,29,26,27,24,25,22,23,20,21,18,19,16,17,14,15,12,13,10,11,8,9,6,7,4,5,2,3,0,1);
//		reg v2 = _mm256_castsi256_ps(_mm256_shuffle_epi8(_mm256_castps_si256(v1), shu));
//		reg lsh1 = lshift<int16_t>(v1, n);
//		reg lsh2 = lshift<int16_t>(v2, n);
//		lsh2 = _mm256_castsi256_ps(_mm256_shuffle_epi8(_mm256_castps_si256(lsh2), shu));
//
//		reg msk = set1<int16_t>(0x00FF);
//		lsh1 = andb <int16_t>(msk, lsh1);
//		lsh2 = andnb<int16_t>(msk, lsh2);
//
//		return xorb<int16_t>(lsh1, lsh2);

		auto msk = set1<int8_t>((1 << n) -1);
		reg lsh = lshift<int16_t>(v1, n);
		lsh = andnb<int16_t>(msk, lsh);
		return lsh;

//		// TODO: Be careful this is not a shift 8 but a shift 16 bits...
//		return _mm256_castsi256_ps(_mm256_slli_epi16(_mm256_castps_si256(v1), n));
	}
#else
	template <>
	inline reg lshift<int32_t>(const reg v1, const uint32_t n) {
		__m128 v1_lane0, v1_lane1;
		__m256 res = v1;

		// apply left shift on lane 0
		v1_lane0 = _mm256_castps256_ps128(v1);
		v1_lane0 = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(v1_lane0), n));

		// permute lane 0 with lane 1
		//   -> _mm256_permute2f128_ps(a, a, _MM_SHUFFLE(0, 0, 0, 1)
		//            lane 0        lane 1
		//       in[7, 6, 5, 4, | 3, 2, 1, 0] =>
		//      out[3, 2, 1, 0, | 7, 6, 5, 4]
		res = _mm256_permute2f128_ps(v1, v1, _MM_SHUFFLE(0, 0, 0, 1));

		// apply left shift on lane 1
		v1_lane1 = _mm256_castps256_ps128(res);
		v1_lane1 = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(v1_lane1), n));

		// convert two SSE-128 registers into one AVX-256 register
		res = _mm256_castps128_ps256(v1_lane0);
		res = _mm256_insertf128_ps(res, v1_lane1, 1);

		return res;
	}
#endif

	// -------------------------------------------------------------------------------------------------- lshift (mask)

	// --------------------------------------------------------------------------------------------------------- rshift
#ifdef __AVX2__
	template <>
	inline reg rshift<int64_t>(const reg v1, const uint32_t n) {
		return _mm256_castsi256_ps(_mm256_srli_epi64(_mm256_castps_si256(v1), n));
	}

	template <>
	inline reg rshift<int32_t>(const reg v1, const uint32_t n) {
		return _mm256_castsi256_ps(_mm256_srli_epi32(_mm256_castps_si256(v1), n));
	}

	template <>
	inline reg rshift<int16_t>(const reg v1, const uint32_t n) {
		return _mm256_castsi256_ps(_mm256_srli_epi16(_mm256_castps_si256(v1), n));
	}

	template <>
	inline reg rshift<int8_t>(const reg v1, const uint32_t n) {
//		auto shu = _mm256_set_epi8(30,31,28,29,26,27,24,25,22,23,20,21,18,19,16,17,14,15,12,13,10,11,8,9,6,7,4,5,2,3,0,1);
//		reg v2 = _mm256_castsi256_ps(_mm256_shuffle_epi8(_mm256_castps_si256(v1), shu));
//		reg rsh1 = rshift<int16_t>(v1, n);
//		reg rsh2 = rshift<int16_t>(v2, n);
//		rsh2 = _mm256_castsi256_ps(_mm256_shuffle_epi8(_mm256_castps_si256(rsh2), shu));
//
//		reg msk = set1<int16_t>(0xFF00);
//		rsh1 = andb <int16_t>(msk, rsh1);
//		rsh2 = andnb<int16_t>(msk, rsh2);
//
//		return xorb<int16_t>(rsh1, rsh2);

		auto msk = set1<int8_t>((1 << (8 -n)) -1);
		reg rsh = rshift<int16_t>(v1, n);
		rsh = andb<int16_t>(msk, rsh);
		return rsh;

//		// TODO: Be careful this is not a shift 8 but a shift 16 bits...
//		return _mm256_castsi256_ps(_mm256_srli_epi16(_mm256_castps_si256(v1), n));
	}
#else
	template <>
	inline reg rshift<int32_t>(const reg v1, const uint32_t n) {
		__m128 v1_lane0, v1_lane1;
		__m256 res = v1;

		// apply left shift on lane 0
		v1_lane0 = _mm256_castps256_ps128(v1);
		v1_lane0 = _mm_castsi128_ps(_mm_srli_epi32(_mm_castps_si128(v1_lane0), n));

		// permute lane 0 with lane 1
		//   -> _mm256_permute2f128_ps(a, a, _MM_SHUFFLE(0, 0, 0, 1))
		//            lane 0        lane 1
		//       in[7, 6, 5, 4, | 3, 2, 1, 0] =>
		//      out[3, 2, 1, 0, | 7, 6, 5, 4]
		res = _mm256_permute2f128_ps(v1, v1, _MM_SHUFFLE(0, 0, 0, 1));

		// apply left shift on lane 1
		v1_lane1 = _mm256_castps256_ps128(res);
		v1_lane1 = _mm_castsi128_ps(_mm_srli_epi32(_mm_castps_si128(v1_lane1), n));

		// convert two SSE-128 registers into one AVX-256 register
		res = _mm256_castps128_ps256(v1_lane0);
		res = _mm256_insertf128_ps(res, v1_lane1, 1);

		return res;
	}
#endif

	// -------------------------------------------------------------------------------------------------- rshift (mask)

	// ---------------------------------------------------------------------------------------------------------- cmpeq
	template <>
	inline msk cmpeq<float>(const reg v1, const reg v2) {
		return _mm256_castps_si256(_mm256_cmp_ps(v1, v2, _CMP_EQ_OQ));
	}

	template <>
	inline msk cmpeq<double>(const reg v1, const reg v2) {
		return _mm256_castpd_si256(_mm256_cmp_pd(_mm256_castps_pd(v1), _mm256_castps_pd(v2), _CMP_EQ_OQ));
	}

#ifdef __AVX2__
	template <>
	inline msk cmpeq<int64_t>(const reg v1, const reg v2) {
		return _mm256_cmpeq_epi64(_mm256_castps_si256(v1), _mm256_castps_si256(v2));
	}

	template <>
	inline msk cmpeq<int32_t>(const reg v1, const reg v2) {
		return _mm256_cmpeq_epi32(_mm256_castps_si256(v1), _mm256_castps_si256(v2));
	}

	template <>
	inline msk cmpeq<int16_t>(const reg v1, const reg v2) {
		return _mm256_cmpeq_epi16(_mm256_castps_si256(v1), _mm256_castps_si256(v2));
	}

	template <>
	inline msk cmpeq<int8_t>(const reg v1, const reg v2) {
		return _mm256_cmpeq_epi8(_mm256_castps_si256(v1), _mm256_castps_si256(v2));
	}
#elif !defined(__INTEL_COMPILER) && !defined(__ICL) && !defined(__ICC)
	template <>
	inline msk cmpeq<int64_t>(const reg v1, const reg v2) {
		return cmpeq<double>(v1, v2);
	}

	template <>
	inline msk cmpeq<int32_t>(const reg v1, const reg v2) {
		return cmpeq<float>(v1, v2);
	}
#endif

	// --------------------------------------------------------------------------------------------------------- cmpneq
	template <>
	inline msk cmpneq<float>(const reg v1, const reg v2) {
		return _mm256_castps_si256(_mm256_cmp_ps(v1, v2, _CMP_NEQ_OQ));
	}

	template <>
	inline msk cmpneq<double>(const reg v1, const reg v2) {
		return _mm256_castpd_si256(_mm256_cmp_pd(_mm256_castps_pd(v1), _mm256_castps_pd(v2), _CMP_NEQ_OQ));
	}

	template <>
	inline msk cmpneq<int64_t>(const reg v1, const reg v2) {
		return notb<N<int64_t>()>(cmpeq<int64_t>(v1, v2));
	}

	template <>
	inline msk cmpneq<int32_t>(const reg v1, const reg v2) {
		return notb<N<int32_t>()>(cmpeq<int32_t>(v1, v2));
	}

	template <>
	inline msk cmpneq<int16_t>(const reg v1, const reg v2) {
		return notb<N<int16_t>()>(cmpeq<int16_t>(v1, v2));
	}

	template <>
	inline msk cmpneq<int8_t>(const reg v1, const reg v2) {
		return notb<N<int8_t>()>(cmpeq<int8_t>(v1, v2));
	}

	// ---------------------------------------------------------------------------------------------------------- cmpgt
	template <>
	inline msk cmpgt<float>(const reg v1, const reg v2) {
		return _mm256_castps_si256(_mm256_cmp_ps(v1, v2, _CMP_GT_OS));
	}

	template <>
	inline msk cmpgt<double>(const reg v1, const reg v2) {
		return _mm256_castpd_si256(_mm256_cmp_pd(_mm256_castps_pd(v1), _mm256_castps_pd(v2), _CMP_GT_OS));
	}

#ifdef __AVX2__
	template <>
	inline msk cmpgt<int64_t>(const reg v1, const reg v2) {
		return _mm256_cmpgt_epi64(_mm256_castps_si256(v1), _mm256_castps_si256(v2));
	}

	template <>
	inline msk cmpgt<int32_t>(const reg v1, const reg v2) {
		return _mm256_cmpgt_epi32(_mm256_castps_si256(v1), _mm256_castps_si256(v2));
	}

	template <>
	inline msk cmpgt<int16_t>(const reg v1, const reg v2) {
		return _mm256_cmpgt_epi16(_mm256_castps_si256(v1), _mm256_castps_si256(v2));
	}

	template <>
	inline msk cmpgt<int8_t>(const reg v1, const reg v2) {
		return _mm256_cmpgt_epi8(_mm256_castps_si256(v1), _mm256_castps_si256(v2));
	}
#endif

	// ---------------------------------------------------------------------------------------------------------- cmpge
	template <>
	inline msk cmpge<float>(const reg v1, const reg v2) {
		return _mm256_castps_si256(_mm256_cmp_ps(v1, v2, _CMP_GE_OS));
	}

	template <>
	inline msk cmpge<double>(const reg v1, const reg v2) {
		return _mm256_castpd_si256(_mm256_cmp_pd(_mm256_castps_pd(v1), _mm256_castps_pd(v2), _CMP_GE_OS));
	}

	template <>
	inline msk cmpge<int64_t>(const reg v1, const reg v2) {
		return orb<N<int64_t>()>(cmpeq<int64_t>(v1, v2), cmpgt<int64_t>(v1, v2));
	}

	template <>
	inline msk cmpge<int32_t>(const reg v1, const reg v2) {
		return orb<N<int32_t>()>(cmpeq<int32_t>(v1, v2), cmpgt<int32_t>(v1, v2));
	}

	template <>
	inline msk cmpge<int16_t>(const reg v1, const reg v2) {
		return orb<N<int16_t>()>(cmpeq<int16_t>(v1, v2), cmpgt<int16_t>(v1, v2));
	}

	template <>
	inline msk cmpge<int8_t>(const reg v1, const reg v2) {
		return orb<N<int8_t>()>(cmpeq<int8_t>(v1, v2), cmpgt<int8_t>(v1, v2));
	}

	// ---------------------------------------------------------------------------------------------------------- cmple
	template <>
	inline msk cmple<float>(const reg v1, const reg v2) {
		return _mm256_castps_si256(_mm256_cmp_ps(v1, v2, _CMP_LE_OS));
	}

	template <>
	inline msk cmple<double>(const reg v1, const reg v2) {
		return _mm256_castpd_si256(_mm256_cmp_pd(_mm256_castps_pd(v1), _mm256_castps_pd(v2), _CMP_LE_OS));
	}

	template <>
	inline msk cmple<int64_t>(const reg v1, const reg v2) {
		return notb<N<int64_t>()>(cmpgt<int64_t>(v1, v2));
	}

	template <>
	inline msk cmple<int32_t>(const reg v1, const reg v2) {
		return notb<N<int32_t>()>(cmpgt<int32_t>(v1, v2));
	}

	template <>
	inline msk cmple<int16_t>(const reg v1, const reg v2) {
		return notb<N<int16_t>()>(cmpgt<int16_t>(v1, v2));
	}

	template <>
	inline msk cmple<int8_t>(const reg v1, const reg v2) {
		return notb<N<int8_t>()>(cmpgt<int8_t>(v1, v2));
	}

	// ---------------------------------------------------------------------------------------------------------- cmplt
	template <>
	inline msk cmplt<float>(const reg v1, const reg v2) {
		return _mm256_castps_si256(_mm256_cmp_ps(v1, v2, _CMP_LT_OS));
	}

	template <>
	inline msk cmplt<double>(const reg v1, const reg v2) {
		return _mm256_castpd_si256(_mm256_cmp_pd(_mm256_castps_pd(v1), _mm256_castps_pd(v2), _CMP_LT_OS));
	}

	template <>
	inline msk cmplt<int64_t>(const reg v1, const reg v2) {
		return cmpgt<int64_t>(v2, v1);
	}

	template <>
	inline msk cmplt<int32_t>(const reg v1, const reg v2) {
		return cmpgt<int32_t>(v2, v1);
	}

	template <>
	inline msk cmplt<int16_t>(const reg v1, const reg v2) {
		return cmpgt<int16_t>(v2, v1);
	}

	template <>
	inline msk cmplt<int8_t>(const reg v1, const reg v2) {
		return cmpgt<int8_t>(v2, v1);
	}

	// ------------------------------------------------------------------------------------------------------------ add
	template <>
	inline reg add<float>(const reg v1, const reg v2) {
		return _mm256_add_ps(v1, v2);
	}

	template <>
	inline reg add<double>(const reg v1, const reg v2) {
		return _mm256_castpd_ps(_mm256_add_pd(_mm256_castps_pd(v1), _mm256_castps_pd(v2)));
	}

#ifdef __AVX2__
	template <>
	inline reg add<int64_t>(const reg v1, const reg v2) {
		return _mm256_castsi256_ps(_mm256_add_epi64(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}

	template <>
	inline reg add<int32_t>(const reg v1, const reg v2) {
		return _mm256_castsi256_ps(_mm256_add_epi32(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}

	template <>
	inline reg add<int16_t>(const reg v1, const reg v2) {
		return _mm256_castsi256_ps(_mm256_adds_epi16(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}

	template <>
	inline reg add<int8_t>(const reg v1, const reg v2) {
		return _mm256_castsi256_ps(_mm256_adds_epi8(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ sub
	template <>
	inline reg sub<float>(const reg v1, const reg v2) {
		return _mm256_sub_ps(v1, v2);
	}

	template <>
	inline reg sub<double>(const reg v1, const reg v2) {
		return _mm256_castpd_ps(_mm256_sub_pd(_mm256_castps_pd(v1), _mm256_castps_pd(v2)));
	}

#ifdef __AVX2__
	template <>
	inline reg sub<int64_t>(const reg v1, const reg v2) {
		return _mm256_castsi256_ps(_mm256_sub_epi64(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}

	template <>
	inline reg sub<int32_t>(const reg v1, const reg v2) {
		return _mm256_castsi256_ps(_mm256_sub_epi32(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}

	template <>
	inline reg sub<int16_t>(const reg v1, const reg v2) {
		return _mm256_castsi256_ps(_mm256_subs_epi16(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}

	template <>
	inline reg sub<int8_t>(const reg v1, const reg v2) {
		return _mm256_castsi256_ps(_mm256_subs_epi8(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ mul
	template <>
	inline reg mul<float>(const reg v1, const reg v2) {
		return _mm256_mul_ps(v1, v2);
	}

	template <>
	inline reg mul<double>(const reg v1, const reg v2) {
		return _mm256_castpd_ps(_mm256_mul_pd(_mm256_castps_pd(v1), _mm256_castps_pd(v2)));
	}

#ifdef __AVX2__
	template <>
	inline reg mul<int32_t>(const reg v1, const reg v2) {
		return _mm256_castsi256_ps(_mm256_mullo_epi32(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}

	template <>
	inline reg mul<int16_t>(const reg v1, const reg v2) {
		return _mm256_castsi256_ps(_mm256_mullo_epi16(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ div
	template <>
	inline reg div<float>(const reg v1, const reg v2) {
		return _mm256_div_ps(v1, v2);
	}

	template <>
	inline reg div<double>(const reg v1, const reg v2) {
		return _mm256_castpd_ps(_mm256_div_pd(_mm256_castps_pd(v1), _mm256_castps_pd(v2)));
	}

	// ------------------------------------------------------------------------------------------------------------ min
	template <>
	inline reg min<float>(const reg v1, const reg v2) {
		return _mm256_min_ps(v1, v2);
	}

	template <>
	inline reg min<double>(const reg v1, const reg v2) {
		return _mm256_castpd_ps(_mm256_min_pd(_mm256_castps_pd(v1), _mm256_castps_pd(v2)));
	}

#ifdef __AVX2__
	template <>
	inline reg min<int32_t>(const reg v1, const reg v2) {
		return _mm256_castsi256_ps(_mm256_min_epi32(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}

	template <>
	inline reg min<int16_t>(const reg v1, const reg v2) {
		return _mm256_castsi256_ps(_mm256_min_epi16(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}

	template <>
	inline reg min<int8_t>(const reg v1, const reg v2) {
		return _mm256_castsi256_ps(_mm256_min_epi8(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ max
	template <>
	inline reg max<float>(const reg v1, const reg v2) {
		return _mm256_max_ps(v1, v2);
	}

	template <>
	inline reg max<double>(const reg v1, const reg v2) {
		return _mm256_castpd_ps(_mm256_max_pd(_mm256_castps_pd(v1), _mm256_castps_pd(v2)));
	}

#ifdef __AVX2__
	template <>
	inline reg max<int32_t>(const reg v1, const reg v2) {
		return _mm256_castsi256_ps(_mm256_max_epi32(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}

	template <>
	inline reg max<int16_t>(const reg v1, const reg v2) {
		return _mm256_castsi256_ps(_mm256_max_epi16(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}

	template <>
	inline reg max<int8_t>(const reg v1, const reg v2) {
		return _mm256_castsi256_ps(_mm256_max_epi8(_mm256_castps_si256(v1), _mm256_castps_si256(v2)));
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ msb
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
	inline reg neg<float>(const reg v1, const reg v2) {
		return xorb<float>(v1, msb<float>(v2));
	}

	template <>
	inline reg neg<float>(const reg v1, const msk v2) {
		return neg<float>(v1, toreg<8>(v2));
	}

	template <>
	inline reg neg<double>(const reg v1, const reg v2) {
		return xorb<double>(v1, msb<double>(v2));
	}

	template <>
	inline reg neg<double>(const reg v1, const msk v2) {
		return neg<double>(v1, toreg<4>(v2));
	}

#ifdef __AVX2__
	template <>
	inline reg neg<int32_t>(const reg v1, const reg v2) {
		reg v2_2 = orb<int32_t>(v2, set1<int32_t>(1)); // hack to avoid -0 case
		return _mm256_castsi256_ps(_mm256_sign_epi32(_mm256_castps_si256(v1), _mm256_castps_si256(v2_2)));
	}

	template <>
	inline reg neg<int32_t>(const reg v1, const msk v2) {
		return neg<int32_t>(v1, toreg<8>(v2));
	}

	template <>
	inline reg neg<int16_t>(const reg v1, const reg v2) {
		reg v2_2 = orb<int16_t>(v2, set1<int16_t>(1)); // hack to avoid -0 case
		return _mm256_castsi256_ps(_mm256_sign_epi16(_mm256_castps_si256(v1), _mm256_castps_si256(v2_2)));
	}

	template <>
	inline reg neg<int16_t>(const reg v1, const msk v2) {
		return neg<int16_t>(v1, toreg<16>(v2));
	}

	template <>
	inline reg neg<int8_t>(const reg v1, const reg v2) {
		reg v2_2 = orb<int8_t>(v2, set1<int8_t>(1)); // hack to avoid -0 case
		return _mm256_castsi256_ps(_mm256_sign_epi8(_mm256_castps_si256(v1), _mm256_castps_si256(v2_2)));
	}

	template <>
	inline reg neg<int8_t>(const reg v1, const msk v2) {
		return neg<int8_t>(v1, toreg<32>(v2));
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ abs
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

#ifdef __AVX2__
	template <>
	inline reg abs<int32_t>(const reg v1) {
		return _mm256_castsi256_ps(_mm256_abs_epi32(_mm256_castps_si256(v1)));
	}

	template <>
	inline reg abs<int16_t>(const reg v1) {
		return _mm256_castsi256_ps(_mm256_abs_epi16(_mm256_castps_si256(v1)));
	}

	template <>
	inline reg abs<int8_t>(const reg v1) {
		return _mm256_castsi256_ps(_mm256_abs_epi8(_mm256_castps_si256(v1)));
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- sqrt
	template <>
	inline reg sqrt<float>(const reg v1) {
		return _mm256_sqrt_ps(v1);
	}

	template <>
	inline reg sqrt<double>(const reg v1) {
		return _mm256_castpd_ps(_mm256_sqrt_pd(_mm256_castps_pd(v1)));
	}

	// ---------------------------------------------------------------------------------------------------------- rsqrt
	template <>
	inline reg rsqrt<float>(const reg v1) {
		return _mm256_rsqrt_ps(v1);
	}

	template <>
	inline reg rsqrt<double>(const reg v1) {
		return div<double>(set1<double>(1.0), sqrt<double>(v1));
	}

	// ------------------------------------------------------------------------------------------------------------ log
#if defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC)
	template <>
	inline reg log<float>(const reg v) {
		return _mm256_log_ps(v);
	}

	template <>
	inline reg log<double>(const reg v) {
		return _mm256_castpd_ps(_mm256_log_pd(_mm256_castps_pd(v)));
	}
#else
	template <>
	inline reg log<float>(const reg v) {
		auto v_bis = v;
		return log256_ps(v_bis);
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ exp
#if defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC)
	template <>
	inline reg exp<float>(const reg v) {
		return _mm256_exp_ps(v);
	}

	template <>
	inline reg exp<double>(const reg v) {
		return _mm256_castpd_ps(_mm256_exp_pd(_mm256_castps_pd(v)));
	}
#else
	template <>
	inline reg exp<float>(const reg v) {
		auto v_bis = v;
		return exp256_ps(v_bis);
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ sin
#if defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC)
	template <>
	inline reg sin<float>(const reg v) {
		return _mm256_sin_ps(v);
	}

	template <>
	inline reg sin<double>(const reg v) {
		return _mm256_castpd_ps(_mm256_sin_pd(_mm256_castps_pd(v)));
	}
#else
	template <>
	inline reg sin<float>(const reg v) {
		auto v_bis = v;
		return sin256_ps(v_bis);
	}
#endif

	// ------------------------------------------------------------------------------------------------------------ cos
#if defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC)
	template <>
	inline reg cos<float>(const reg v) {
		return _mm256_cos_ps(v);
	}

	template <>
	inline reg cos<double>(const reg v) {
		return _mm256_castpd_ps(_mm256_cos_pd(_mm256_castps_pd(v)));
	}
#else
	template <>
	inline reg cos<float>(const reg v) {
		auto v_bis = v;
		return cos256_ps(v_bis);
	}
#endif

	// --------------------------------------------------------------------------------------------------------- sincos
#if defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC)
	template <>
	inline void sincos<float>(const reg x, reg &s, reg &c) {
		s = _mm256_sincos_ps(&c, x);
	}

	template <>
	inline void sincos<double>(const reg x, reg &s, reg &c) {
		s = (reg)_mm256_sincos_pd((__m256d*) &c, (__m256d)x);
	}
#else
	template <>
	inline void sincos<float>(const reg x, reg &s, reg &c) {
		sincos256_ps(x, &s, &c);
	}
#endif

	// ---------------------------------------------------------------------------------------------------------- fmadd
#ifdef __FMA__
	template <>
	inline reg fmadd<float>(const reg v1, const reg v2, const reg v3) {
		return _mm256_fmadd_ps(v1, v2, v3);
	}

	template <>
	inline reg fmadd<double>(const reg v1, const reg v2, const reg v3) {
		return _mm256_castpd_ps(_mm256_fmadd_pd(_mm256_castps_pd(v1), _mm256_castps_pd(v2), _mm256_castps_pd(v3)));
	}
#else
	template <>
	inline reg fmadd<float>(const reg v1, const reg v2, const reg v3) {
		return add<float>(v3, mul<float>(v1, v2));
	}

	template <>
	inline reg fmadd<double>(const reg v1, const reg v2, const reg v3) {
		return add<double>(v3, mul<double>(v1, v2));
	}
#endif

	// --------------------------------------------------------------------------------------------------------- fnmadd
#ifdef __FMA__
	template <>
	inline reg fnmadd<float>(const reg v1, const reg v2, const reg v3) {
		return _mm256_fnmadd_ps(v1, v2, v3);
	}

	template <>
	inline reg fnmadd<double>(const reg v1, const reg v2, const reg v3) {
		return _mm256_castpd_ps(_mm256_fnmadd_pd(_mm256_castps_pd(v1), _mm256_castps_pd(v2), _mm256_castps_pd(v3)));
	}
#else
	template <>
	inline reg fnmadd<float>(const reg v1, const reg v2, const reg v3) {
		return sub<float>(v3, mul<float>(v1, v2));
	}

	template <>
	inline reg fnmadd<double>(const reg v1, const reg v2, const reg v3) {
		return sub<double>(v3, mul<double>(v1, v2));
	}
#endif

	// ---------------------------------------------------------------------------------------------------------- fmsub
#ifdef __FMA__
	template <>
	inline reg fmsub<float>(const reg v1, const reg v2, const reg v3) {
		return _mm256_fmsub_ps(v1, v2, v3);
	}

	template <>
	inline reg fmsub<double>(const reg v1, const reg v2, const reg v3) {
		return _mm256_castpd_ps(_mm256_fmsub_pd(_mm256_castps_pd(v1), _mm256_castps_pd(v2), _mm256_castps_pd(v3)));
	}
#else
	template <>
	inline reg fmsub<float>(const reg v1, const reg v2, const reg v3) {
		return sub<float>(mul<float>(v1, v2), v3);
	}

	template <>
	inline reg fmsub<double>(const reg v1, const reg v2, const reg v3) {
		return sub<double>(mul<double>(v1, v2), v3);
	}
#endif

	// --------------------------------------------------------------------------------------------------------- fnmsub
#ifdef __FMA__
	template <>
	inline reg fnmsub<float>(const reg v1, const reg v2, const reg v3) {
		return _mm256_fnmsub_ps(v1, v2, v3);
	}

	template <>
	inline reg fnmsub<double>(const reg v1, const reg v2, const reg v3) {
		return _mm256_castpd_ps(_mm256_fnmsub_pd(_mm256_castps_pd(v1), _mm256_castps_pd(v2), _mm256_castps_pd(v3)));
	}
#else
	template <>
	inline reg fnmsub<float>(const reg v1, const reg v2, const reg v3) {
		return sub<float>(sub<float>(set0<float>(), mul<float>(v1, v2)), v3);
	}

	template <>
	inline reg fnmsub<double>(const reg v1, const reg v2, const reg v3) {
		return sub<double>(sub<double>(set0<double>(), mul<double>(v1, v2)), v3);
	}
#endif

	// ---------------------------------------------------------------------------------------------------------- blend
	template <>
	inline reg blend<double>(const reg v1, const reg v2, const msk m) {
		return _mm256_castpd_ps(_mm256_blendv_pd(_mm256_castps_pd(v2), _mm256_castps_pd(v1), _mm256_castsi256_pd(m)));
	}

	template <>
	inline reg blend<float>(const reg v1, const reg v2, const msk m) {
		return _mm256_blendv_ps(v2, v1, _mm256_castsi256_ps(m));
	}

	template <>
	inline reg blend<int64_t>(const reg v1, const reg v2, const msk m) {
		return _mm256_castpd_ps(_mm256_blendv_pd(_mm256_castps_pd(v2), _mm256_castps_pd(v1), _mm256_castsi256_pd(m)));
	}

	template <>
	inline reg blend<int32_t>(const reg v1, const reg v2, const msk m) {
		return _mm256_blendv_ps(v2, v1, _mm256_castsi256_ps(m));
	}

#ifdef __AVX2__
	template <>
	inline reg blend<int16_t>(const reg v1, const reg v2, const msk m) {
		return _mm256_castsi256_ps(_mm256_blendv_epi8(_mm256_castps_si256(v2),
		                                              _mm256_castps_si256(v1),
		                                              m));
	}

	template <>
	inline reg blend<int8_t>(const reg v1, const reg v2, const msk m) {
		return _mm256_castsi256_ps(_mm256_blendv_epi8(_mm256_castps_si256(v2),
		                                              _mm256_castps_si256(v1),
		                                              m));
	}
#else
	template <>
	inline reg blend<int16_t>(const reg v1, const reg v2, const msk m) {
		auto m_reg = toreg<16>(m);
		auto v1_2 = andb <int32_t>(m_reg, v1);
		auto v2_2 = andnb<int32_t>(m_reg, v2);
		auto blen = xorb <int32_t>(v1_2, v2_2);
		return blen;
	}

	template <>
	inline reg blend<int8_t>(const reg v1, const reg v2, const msk m) {
		auto m_reg = toreg<32>(m);
		auto v1_2 = andb <int32_t>(m_reg, v1);
		auto v2_2 = andnb<int32_t>(m_reg, v2);
		auto blen = xorb <int32_t>(v1_2, v2_2);
		return blen;
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- lrot
#ifdef __AVX2__
	template <>
	inline reg lrot<double>(const reg v1) {
		return _mm256_castpd_ps(_mm256_permute4x64_pd(_mm256_castps_pd(v1), _MM_SHUFFLE(0, 3, 2 ,1)));
	}

	template <>
	inline reg lrot<float>(const reg v1) {
		return _mm256_permutevar8x32_ps(v1, _mm256_setr_epi32(1, 2, 3, 4, 5, 6, 7, 0));
	}

	template <>
	inline reg lrot<int64_t>(const reg v1) {
		return _mm256_castpd_ps(_mm256_permute4x64_pd(_mm256_castps_pd(v1), _MM_SHUFFLE(0, 3, 2 ,1)));
	}

	template <>
	inline reg lrot<int32_t>(const reg v1) {
		return _mm256_permutevar8x32_ps(v1, _mm256_setr_epi32(1, 2, 3, 4, 5, 6, 7, 0));
	}

	template <>
	inline reg lrot<int16_t>(const reg v1) {
		auto r = _mm256_castsi256_ps(_mm256_shuffle_epi8(_mm256_castps_si256(v1),
		                                                 _mm256_set_epi8(1,0,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2)));

		const uint16_t mask[16] = {0,0,0,0,0,0,0,0xFFFF,0,0,0,0,0,0,0,0xFFFF};
		auto m = set<int16_t>((int16_t*)mask);
		auto r2 = _mm256_permutevar8x32_ps(r, _mm256_setr_epi32(0, 1, 2, 7, 4, 5, 6, 3));
		return blend<int16_t>(r2, r, _mm256_castps_si256(m));
	}

	template <>
	inline reg lrot<int8_t>(const reg v1) {
		auto r = _mm256_castsi256_ps(_mm256_shuffle_epi8(_mm256_castps_si256(v1),
		                                                 _mm256_set_epi8(0,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1)));

		const uint8_t mask[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0xFF,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0xFF};
		auto m = set<int8_t>((int8_t*)mask);
		auto r2 = _mm256_permutevar8x32_ps(r, _mm256_setr_epi32(0, 1, 2, 7, 4, 5, 6, 3));
		return blend<int8_t>(r2, r, _mm256_castps_si256(m));
	}
#else
	template <>
	inline reg lrot<double>(const reg v1) {
		// make a rotation in:[3, 2 , 1, 0] => out:[0, 3, 2, 1]
		//
		//   -> _mm256_permute_pd(a, _MM_SHUFFLE(1, 1, 1, 1)) # rotation per lane of 128 bits
		//      /!\ I think this is a wrong shuffle and the good one is: _MM_SHUFFLE(0, 1, 0, 1)
		//           l0      l1
		//       in[3, 2, | 1, 0] =>
		//      out[2, 3, | 0, 1]
		//
		//   -> _mm256_permute2f128_pd(a, a, _MM_SHUFFLE(0, 0, 0, 1)) # switch lanes
		//           l0     l1
		//       in[3, 2, | 1, 0] =>
		//      out[1, 0, | 3, 2]
		//
		//   -> _mm256_blend_pd(a, b, _MM_SHUFFLE(0, 0, 2, 2))
		//      ina[3a, 2a, 1a, 0a] and inb[3b, 2b, 1b, 0b] => out[3b, 2a, 1b, 0a]
		auto rTmp = _mm256_permute_pd(_mm256_castps_pd(v1), _MM_SHUFFLE(0, 0, 1, 1));
		return _mm256_castpd_ps(_mm256_blend_pd(rTmp,
		                                        _mm256_permute2f128_pd(rTmp,
		                                                               rTmp,
		                                                               _MM_SHUFFLE(0, 0, 0, 1)),
		                                        _MM_SHUFFLE(0, 0, 2, 2)));
	}

	template <>
	inline reg lrot<float>(const reg v1) {
		// make a rotation in:[7, 6, 5, 4, 3, 2 , 1, 0] =>  out:[0, 7, 6, 5, 4, 3, 2, 1]
		//
		//   -> _mm256_permute_ps(a, _MM_SHUFFLE(0, 3, 2, 1)) # rotation per lane of 128 bits
		//            lane 0        lane 1
		//       in[7, 6, 5, 4, | 3, 2, 1, 0] =>
		//      out[4, 5, 6, 7, | 0, 3, 2, 1]
		//
		//   -> _mm256_permute2f128_ps(a, a, _MM_SHUFFLE(0, 0, 0, 1)) # switch lanes
		//            lane 0        lane 1
		//       in[7, 6, 5, 4, | 3, 2, 1, 0] =>
		//      out[3, 2, 1, 0, | 7, 6, 5, 4]
		//
		//   -> _mm256_blend_ps(a, b, _MM_SHUFFLE(2, 0, 2, 0))
		//         ina[7a, 6a, 5a, 4a, 3a, 2a, 1a, 0a]
		//         inb[7b, 6b, 5b, 4b, 3b, 2b, 1b, 0b] =>
		//         out[7b, 6a, 5a, 4a, 3b, 2a, 1a, 0a]
		auto rTmp = _mm256_permute_ps(v1, _MM_SHUFFLE(0, 3, 2, 1));
		return _mm256_blend_ps(rTmp,
		                       _mm256_permute2f128_ps(rTmp, rTmp, _MM_SHUFFLE(0, 0, 0, 1)),
		                       _MM_SHUFFLE(2, 0, 2, 0));
	}

	template <>
	inline reg lrot<int64_t>(const reg v1) {
		return lrot<double>(v1);
	}

	template <>
	inline reg lrot<int32_t>(const reg v1) {
		return lrot<float>(v1);
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- rrot
#ifdef __AVX2__
	template <>
	inline reg rrot<double>(const reg v1) {
		return _mm256_castpd_ps(_mm256_permute4x64_pd(_mm256_castps_pd(v1), _MM_SHUFFLE(2 ,1, 0, 3)));
	}

	template <>
	inline reg rrot<float>(const reg v1) {
		return _mm256_permutevar8x32_ps(v1, _mm256_setr_epi32(7, 0, 1, 2, 3, 4, 5, 6));
	}

	template <>
	inline reg rrot<int64_t>(const reg v1) {
		return _mm256_castpd_ps(_mm256_permute4x64_pd(_mm256_castps_pd(v1), _MM_SHUFFLE(2 ,1, 0, 3)));
	}

	template <>
	inline reg rrot<int32_t>(const reg v1) {
		return _mm256_permutevar8x32_ps(v1, _mm256_setr_epi32(7, 0, 1, 2, 3, 4, 5, 6));
	}

	template <>
	inline reg rrot<int16_t>(const reg v1) {
		auto r = _mm256_castsi256_ps(_mm256_shuffle_epi8(_mm256_castps_si256(v1),
		                                                 _mm256_set_epi8(29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0,31,30)));

		const uint16_t mask[16] = {0xFFFF,0,0,0,0,0,0,0,0xFFFF,0,0,0,0,0,0,0};
		auto m = set<int16_t>((int16_t*)mask);
		auto r2 = _mm256_permutevar8x32_ps(r, _mm256_setr_epi32(4, 1, 2, 3, 0, 5, 6, 7));
		return blend<int16_t>(r2, r, _mm256_castps_si256(m));
	}

	template <>
	inline reg rrot<int8_t>(const reg v1) {
		auto r = _mm256_castsi256_ps(_mm256_shuffle_epi8(_mm256_castps_si256(v1),
		                                                 _mm256_set_epi8(30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0,31)));

		const uint8_t mask[32] = {0xFF,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0xFF,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		auto m = set<int8_t>((int8_t*)mask);
		auto r2 = _mm256_permutevar8x32_ps(r, _mm256_setr_epi32(4, 1, 2, 3, 0, 5, 6, 7));
		return blend<int8_t>(r2, r, _mm256_castps_si256(m));
	}
#else
	template <>
	inline reg rrot<double>(const reg v1) {
		auto rTmp = _mm256_permute_pd(_mm256_castps_pd(v1), _MM_SHUFFLE(0, 0, 1, 1));
		return _mm256_castpd_ps(_mm256_blend_pd(rTmp,
		                                        _mm256_permute2f128_pd(rTmp,
		                                                               rTmp,
		                                                               _MM_SHUFFLE(0, 0, 0, 1)),
		                                        _MM_SHUFFLE(0, 0, 1, 1)));
	}

	template <>
	inline reg rrot<float>(const reg v1) {
		auto rTmp = _mm256_permute_ps(v1, _MM_SHUFFLE(2, 1, 0, 3));
		return _mm256_blend_ps(rTmp,
		                       _mm256_permute2f128_ps(rTmp, rTmp, _MM_SHUFFLE(0, 0, 0, 1)),
		                       _MM_SHUFFLE(0, 1, 0, 1));
	}

	template <>
	inline reg rrot<int64_t>(const reg v1) {
		return rrot<double>(v1);
	}

	template <>
	inline reg rrot<int32_t>(const reg v1) {
		return rrot<float>(v1);
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

#ifdef __AVX2__
	template <>
	inline reg div2<int32_t>(const reg v1) {
//		return _mm256_castsi256_ps(_mm256_srai_epi32(_mm256_castps_si256(v1), 1)); // seems to do not work
		reg abs_v1 = abs<int32_t>(v1);
		reg sh = rshift<int32_t>(abs_v1, 1);
		sh = neg<int32_t>(sh, v1);
		return sh;
	}

	template <>
	inline reg div2<int16_t>(const reg v1) {
//		return _mm256_castsi256_ps(_mm256_srai_epi16(_mm256_castps_si256(v1), 1)); // seems to do not work
		reg abs_v1 = abs<int16_t>(v1);
		reg sh = rshift<int16_t>(abs_v1, 1);
		sh = neg<int16_t>(sh, v1);
		return sh;
	}

	template <>
	inline reg div2<int8_t>(const reg v1) {
		reg abs_v1 = abs<int8_t>(v1);
		reg sh16 = rshift<int16_t>(abs_v1, 1);
#ifdef _MSC_VER
#pragma warning( disable : 4309 )
#endif
		sh16 = andnb<int8_t>(set1<int8_t>(0x80), sh16);
#ifdef _MSC_VER
#pragma warning( default : 4309 )
#endif
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

#ifdef __AVX2__
	template <>
	inline reg div4<int32_t>(const reg v1) {
//		return _mm256_castsi256_ps(_mm256_srai_epi32(_mm256_castps_si256(v1), 2)); // seems to do not work
		reg abs_v1 = abs<int32_t>(v1);
		reg sh = rshift<int32_t>(abs_v1, 2);
		sh = neg<int32_t>(sh, v1);
		return sh;
	}

	template <>
	inline reg div4<int16_t>(const reg v1) {
//		return _mm256_castsi256_ps(_mm256_srai_epi16(_mm256_castps_si256(v1), 2)); // seems to do not work
		reg abs_v1 = abs<int16_t>(v1);
		reg sh = rshift<int16_t>(abs_v1, 2);
		sh = neg<int16_t>(sh, v1);
		return sh;
	}

	template <>
	inline reg div4<int8_t>(const reg v1) {
		reg abs_v1 = abs<int8_t>(v1);
		reg sh16 = rshift<int16_t>(abs_v1, 2);
#ifdef _MSC_VER
#pragma warning( disable : 4309 )
#endif
		sh16 = andnb<int8_t>(set1<int8_t>(0xc0), sh16);
#ifdef _MSC_VER
#pragma warning( default : 4309 )
#endif
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
	inline reg sat<int32_t>(const reg v1, int32_t min, int32_t max) {
		return mipp::min<int32_t>(mipp::max<int32_t>(v1, set1<int32_t>(min)), set1<int32_t>(max));
	}

	template <>
	inline reg sat<int16_t>(const reg v1, int16_t min, int16_t max) {
		return mipp::min<int16_t>(mipp::max<int16_t>(v1, set1<int16_t>(min)), set1<int16_t>(max));
	}

	template <>
	inline reg sat<int8_t>(const reg v1, int8_t min, int8_t max) {
		return mipp::min<int8_t>(mipp::max<int8_t>(v1, set1<int8_t>(min)), set1<int8_t>(max));
	}

	// ---------------------------------------------------------------------------------------------------------- round
	template <>
	inline reg round<float>(const reg v) {
		return _mm256_round_ps(v, _MM_FROUND_TO_NEAREST_INT |_MM_FROUND_NO_EXC);
	}

	template <>
	inline reg round<double>(const reg v) {
		return _mm256_castpd_ps(_mm256_round_pd(_mm256_castps_pd(v), _MM_FROUND_TO_NEAREST_INT |_MM_FROUND_NO_EXC));
	}

	// ------------------------------------------------------------------------------------------------------------ cvt
	template <>
	inline reg cvt<float,int32_t>(const reg v) {
		return _mm256_castsi256_ps(_mm256_cvtps_epi32(v));
	}

	template <>
	inline reg cvt<int32_t,float>(const reg v) {
		return _mm256_cvtepi32_ps(_mm256_castps_si256(v));
	}

#ifdef __AVX2__
	template <>
	inline reg cvt<int8_t,int16_t>(const reg_2 v) {
		return _mm256_castsi256_ps(_mm256_cvtepi8_epi16(_mm_castps_si128(v)));
	}

	template <>
	inline reg cvt<int16_t,int32_t>(const reg_2 v) {
		return _mm256_castsi256_ps(_mm256_cvtepi16_epi32(_mm_castps_si128(v)));
	}

	template <>
	inline reg cvt<int32_t,int64_t>(const reg_2 v) {
		return _mm256_castsi256_ps(_mm256_cvtepi32_epi64(_mm_castps_si128(v)));
	}
#endif

	// ----------------------------------------------------------------------------------------------------------- pack
#ifdef __AVX2__
	template <>
	inline reg pack<int32_t,int16_t>(const reg v1, const reg v2) {
		return _mm256_castsi256_ps(_mm256_permute4x64_epi64(_mm256_packs_epi32(_mm256_castps_si256(v1),
		                                                                       _mm256_castps_si256(v2)),
		                                                    _MM_SHUFFLE(3, 1, 2, 0)));
	}

	template <>
	inline reg pack<int16_t,int8_t>(const reg v1, const reg v2) {
		return _mm256_castsi256_ps(_mm256_permute4x64_epi64(_mm256_packs_epi16(_mm256_castps_si256(v1),
		                                                                       _mm256_castps_si256(v2)),
		                                                    _MM_SHUFFLE(3, 1, 2, 0)));
	}
#endif

	// ---------------------------------------------------------------------------------------------------------- testz
	template <>
	inline bool testz<float>(const reg v1, const reg v2) {
		return _mm256_testz_ps(v1, v2);
	}

	template <>
	inline bool testz<double>(const reg v1, const reg v2) {
		return _mm256_testz_pd(_mm256_castps_pd(v1), _mm256_castps_pd(v2));
	}

	template <>
	inline bool testz<int64_t>(const reg v1, const reg v2) {
		return _mm256_testz_si256(_mm256_castps_si256(v1), _mm256_castps_si256(v2));
	}

	template <>
	inline bool testz<int32_t>(const reg v1, const reg v2) {
		return _mm256_testz_si256(_mm256_castps_si256(v1), _mm256_castps_si256(v2));
	}

	template <>
	inline bool testz<int16_t>(const reg v1, const reg v2) {
		return _mm256_testz_si256(_mm256_castps_si256(v1), _mm256_castps_si256(v2));
	}

	template <>
	inline bool testz<int8_t>(const reg v1, const reg v2) {
		return _mm256_testz_si256(_mm256_castps_si256(v1), _mm256_castps_si256(v2));
	}

	template <>
	inline bool testz<double>(const reg v1) {
		return testz<double>(v1, mipp::set1<int64_t>(-1));
	}

	template <>
	inline bool testz<float>(const reg v1) {
		return testz<float>(v1, mipp::set1<int32_t>(-1));
	}

	template <>
	inline bool testz<int64_t>(const reg v1) {
		return testz<int64_t>(v1, mipp::set1<int64_t>(-1));
	}

	template <>
	inline bool testz<int32_t>(const reg v1) {
		return testz<int32_t>(v1, mipp::set1<int32_t>(-1));
	}

	template <>
	inline bool testz<int16_t>(const reg v1) {
		return testz<int16_t>(v1, mipp::set1<int16_t>(-1));
	}

	template <>
	inline bool testz<int8_t>(const reg v1) {
		return testz<int8_t>(v1, mipp::set1<int8_t>(-1));
	}

	// --------------------------------------------------------------------------------------------------- testz (mask)
	template <>
	inline bool testz<4>(const msk v1, const msk v2) {
		return _mm256_testz_si256(v1, v2);
	}

	template <>
	inline bool testz<8>(const msk v1, const msk v2) {
		return _mm256_testz_si256(v1, v2);
	}

	template <>
	inline bool testz<16>(const msk v1, const msk v2) {
		return _mm256_testz_si256(v1, v2);
	}

	template <>
	inline bool testz<32>(const msk v1, const msk v2) {
		return _mm256_testz_si256(v1, v2);
	}

	template <>
	inline bool testz<4>(const msk v1) {
		return testz<4>(v1, _mm256_castps_si256(mipp::set1<int64_t>(-1)));
	}

	template <>
	inline bool testz<8>(const msk v1) {
		return testz<8>(v1, _mm256_castps_si256(mipp::set1<int32_t>(-1)));
	}

	template <>
	inline bool testz<16>(const msk v1) {
		return testz<16>(v1, _mm256_castps_si256(mipp::set1<int16_t>(-1)));
	}

	template <>
	inline bool testz<32>(const msk v1) {
		return testz<32>(v1, _mm256_castps_si256(mipp::set1<int8_t>(-1)));
	}

	// ------------------------------------------------------------------------------------------------------ reduction
	template <red_op<double> OP>
	struct _reduction<double,OP>
	{
		static reg apply(const reg v1) {
			auto val = v1;
			val = OP(val, _mm256_permute2f128_ps(val, val, _MM_SHUFFLE(0,0,0,1)));
			val = OP(val, _mm256_shuffle_ps     (val, val, _MM_SHUFFLE(1,0,3,2)));
			return val;
		}
	};

	template <Red_op<double> OP>
	struct _Reduction<double,OP>
	{
		static const Reg<double> apply(const Reg<double> v1) {
			auto val = v1;
			val = OP(val, Reg<double>(_mm256_permute2f128_ps(val.r, val.r, _MM_SHUFFLE(0,0,0,1))));
			val = OP(val, Reg<double>(_mm256_shuffle_ps     (val.r, val.r, _MM_SHUFFLE(1,0,3,2))));
			return val;
		}
	};

	template <red_op<float> OP>
	struct _reduction<float,OP>
	{
		static reg apply(const reg v1) {
			auto val = v1;
			val = OP(val, _mm256_permute2f128_ps(val, val, _MM_SHUFFLE(0,0,0,1)));
			val = OP(val, _mm256_shuffle_ps     (val, val, _MM_SHUFFLE(1,0,3,2)));
			val = OP(val, _mm256_shuffle_ps     (val, val, _MM_SHUFFLE(2,3,0,1)));
			return val;
		}
	};

	template <Red_op<float> OP>
	struct _Reduction<float,OP>
	{
		static Reg<float> apply(const Reg<float> v1) {
			auto val = v1;
			val = OP(val, Reg<float>(_mm256_permute2f128_ps(val.r, val.r, _MM_SHUFFLE(0,0,0,1))));
			val = OP(val, Reg<float>(_mm256_shuffle_ps     (val.r, val.r, _MM_SHUFFLE(1,0,3,2))));
			val = OP(val, Reg<float>(_mm256_shuffle_ps     (val.r, val.r, _MM_SHUFFLE(2,3,0,1))));
			return val;
		}
	};

	template <red_op<int64_t> OP>
	struct _reduction<int64_t,OP>
	{
		static reg apply(const reg v1) {
			auto val = v1;
			val = OP(val, _mm256_permute2f128_ps(val, val, _MM_SHUFFLE(0,0,0,1)));
			val = OP(val, _mm256_shuffle_ps     (val, val, _MM_SHUFFLE(1,0,3,2)));
			return val;
		}
	};

	template <Red_op<int64_t> OP>
	struct _Reduction<int64_t,OP>
	{
		static const Reg<int64_t> apply(const Reg<int64_t> v1) {
			auto val = v1;
			val = OP(val, Reg<int64_t>(_mm256_permute2f128_ps(val.r, val.r, _MM_SHUFFLE(0,0,0,1))));
			val = OP(val, Reg<int64_t>(_mm256_shuffle_ps     (val.r, val.r, _MM_SHUFFLE(1,0,3,2))));
			return val;
		}
	};

	template <red_op<int32_t> OP>
	struct _reduction<int32_t,OP>
	{
		static reg apply(const reg v1) {
			auto val = v1;
			val = OP(val, _mm256_permute2f128_ps(val, val, _MM_SHUFFLE(0,0,0,1)));
			val = OP(val, _mm256_shuffle_ps     (val, val, _MM_SHUFFLE(1,0,3,2)));
			val = OP(val, _mm256_shuffle_ps     (val, val, _MM_SHUFFLE(2,3,0,1)));
			return val;
		}
	};

	template <Red_op<int32_t> OP>
	struct _Reduction<int32_t,OP>
	{
		static Reg<int32_t> apply(const Reg<int32_t> v1) {
			auto val = v1;
			val = OP(val, Reg<int32_t>(_mm256_permute2f128_ps(val.r, val.r, _MM_SHUFFLE(0,0,0,1))));
			val = OP(val, Reg<int32_t>(_mm256_shuffle_ps     (val.r, val.r, _MM_SHUFFLE(1,0,3,2))));
			val = OP(val, Reg<int32_t>(_mm256_shuffle_ps     (val.r, val.r, _MM_SHUFFLE(2,3,0,1))));
			return val;
		}
	};

#ifdef __AVX2__
	template <red_op<int16_t> OP>
	struct _reduction<int16_t,OP>
	{
		static reg apply(const reg v1) {
			__m256i mask_16 = _mm256_set_epi8(29, 28, 31, 30, 25, 24, 27, 26, 21, 20, 23, 22, 17, 16, 19, 18, 13, 12, 15,
			                                  14, 9, 8, 11, 10, 5, 4, 7, 6, 1, 0, 3, 2);

			auto val = v1;
			val = OP(val, _mm256_castsi256_ps(_mm256_permute2f128_si256(_mm256_castps_si256(val),
			                                                            _mm256_castps_si256(val),
			                                                            _MM_SHUFFLE(0,0,0,1))));
			val = OP(val, _mm256_castsi256_ps(_mm256_permute4x64_epi64 (_mm256_castps_si256(val),
			                                                            _MM_SHUFFLE(2,3,0,1))));
			val = OP(val, _mm256_castsi256_ps(_mm256_shuffle_epi32     (_mm256_castps_si256(val),
			                                                            _MM_SHUFFLE(2,3,0,1))));
			val = OP(val, _mm256_castsi256_ps(_mm256_shuffle_epi8      (_mm256_castps_si256(val),
			                                                            mask_16)));
			return val;
		}
	};

	template <Red_op<int16_t> OP>
	struct _Reduction<int16_t,OP>
	{
		static Reg<int16_t> apply(const Reg<int16_t> v1) {
			__m256i mask_16 = _mm256_set_epi8(29, 28, 31, 30, 25, 24, 27, 26, 21, 20, 23, 22, 17, 16, 19, 18, 13, 12, 15,
			                                  14, 9, 8, 11, 10, 5, 4, 7, 6, 1, 0, 3, 2);

			auto val = v1;
			val = OP(val, Reg<int16_t>(_mm256_castsi256_ps(_mm256_permute2f128_si256(_mm256_castps_si256(val.r),
			                                                                         _mm256_castps_si256(val.r),
			                                                                         _MM_SHUFFLE(0,0,0,1)))));
			val = OP(val, Reg<int16_t>(_mm256_castsi256_ps(_mm256_permute4x64_epi64 (_mm256_castps_si256(val.r),
			                                                                         _MM_SHUFFLE(2,3,0,1)))));
			val = OP(val, Reg<int16_t>(_mm256_castsi256_ps(_mm256_shuffle_epi32     (_mm256_castps_si256(val.r),
			                                                                         _MM_SHUFFLE(2,3,0,1)))));
			val = OP(val, Reg<int16_t>(_mm256_castsi256_ps(_mm256_shuffle_epi8      (_mm256_castps_si256(val.r),
			                                                                         mask_16))));
			return val;
		}
	};
#endif

#ifdef __AVX2__
	template <red_op<int8_t> OP>
	struct _reduction<int8_t,OP>
	{
		static reg apply(const reg v1) {
			__m256i mask_16 = _mm256_set_epi8(29, 28, 31, 30, 25, 24, 27, 26, 21, 20, 23, 22, 17, 16, 19, 18, 13, 12, 15,
			                                  14, 9, 8, 11, 10, 5, 4, 7, 6, 1, 0, 3, 2);
			__m256i mask_8  = _mm256_set_epi8(30, 31, 28, 29, 26, 27, 24, 25, 22, 23, 20, 21, 18, 19, 16, 17, 14, 15, 12,
			                                  13, 10, 11, 8, 9, 6, 7, 4, 5, 2, 3, 0, 1);

			auto val = v1;
			val = OP(val, _mm256_castsi256_ps(_mm256_permute2f128_si256(_mm256_castps_si256(val),
			                                                            _mm256_castps_si256(val),
			                                                            _MM_SHUFFLE(0,0,0,1))));
			val = OP(val, _mm256_castsi256_ps(_mm256_permute4x64_epi64 (_mm256_castps_si256(val),
			                                                            _MM_SHUFFLE(2,3,0,1))));
			val = OP(val, _mm256_castsi256_ps(_mm256_shuffle_epi32     (_mm256_castps_si256(val),
			                                                            _MM_SHUFFLE(2,3,0,1))));
			val = OP(val, _mm256_castsi256_ps(_mm256_shuffle_epi8      (_mm256_castps_si256(val),
			                                                            mask_16)));
			val = OP(val, _mm256_castsi256_ps(_mm256_shuffle_epi8      (_mm256_castps_si256(val),
			                                                            mask_8)));
			return val;
		}
	};

	template <Red_op<int8_t> OP>
	struct _Reduction<int8_t,OP>
	{
		static Reg<int8_t> apply(const Reg<int8_t> v1) {
			__m256i mask_16 = _mm256_set_epi8(29, 28, 31, 30, 25, 24, 27, 26, 21, 20, 23, 22, 17, 16, 19, 18, 13, 12, 15,
			                                  14, 9, 8, 11, 10, 5, 4, 7, 6, 1, 0, 3, 2);
			__m256i mask_8  = _mm256_set_epi8(30, 31, 28, 29, 26, 27, 24, 25, 22, 23, 20, 21, 18, 19, 16, 17, 14, 15, 12,
			                                  13, 10, 11, 8, 9, 6, 7, 4, 5, 2, 3, 0, 1);

			auto val = v1;
			val = OP(val, Reg<int8_t>(_mm256_castsi256_ps(_mm256_permute2f128_si256(_mm256_castps_si256(val.r),
			                                                                        _mm256_castps_si256(val.r),
			                                                                        _MM_SHUFFLE(0,0,0,1)))));
			val = OP(val, Reg<int8_t>(_mm256_castsi256_ps(_mm256_permute4x64_epi64 (_mm256_castps_si256(val.r),
			                                                                        _MM_SHUFFLE(2,3,0,1)))));
			val = OP(val, Reg<int8_t>(_mm256_castsi256_ps(_mm256_shuffle_epi32     (_mm256_castps_si256(val.r),
			                                                                        _MM_SHUFFLE(2,3,0,1)))));
			val = OP(val, Reg<int8_t>(_mm256_castsi256_ps(_mm256_shuffle_epi8      (_mm256_castps_si256(val.r),
			                                                                        mask_16))));
			val = OP(val, Reg<int8_t>(_mm256_castsi256_ps(_mm256_shuffle_epi8      (_mm256_castps_si256(val.r),
			                                                                        mask_8))));
			return val;
		}
	};
#endif
#endif
