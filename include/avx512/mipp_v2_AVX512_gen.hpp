#ifndef MY_INTRINSICS_PLUS_PLUS_HPP_
#define MY_INTRINSICS_PLUS_PLUS_HPP_

namespace mipp
{
// should throw an exception
template<typename T, int LMUL=1> struct rvd_type{};
template<> struct rvd_type<float64_t, 1>{ using type = rvd_avx512_float64_t; };
template<> struct rvd_type<float32_t, 1>{ using type = rvd_avx512_float32_t; };
template<> struct rvd_type<int64_t, 1>{ using type = rvd_avx512_int64_t; };
template<> struct rvd_type<int32_t, 1>{ using type = rvd_avx512_int32_t; };
template<> struct rvd_type<int16_t, 1>{ using type = rvd_avx512_int16_t; };
template<> struct rvd_type<int8_t, 1>{ using type = rvd_avx512_int8_t; };
template<> struct rvd_type<uint64_t, 1>{ using type = rvd_avx512_uint64_t; };
template<> struct rvd_type<uint32_t, 1>{ using type = rvd_avx512_uint32_t; };
template<> struct rvd_type<uint16_t, 1>{ using type = rvd_avx512_uint16_t; };
template<> struct rvd_type<uint8_t, 1>{ using type = rvd_avx512_uint8_t; };
template <typename T, int LMUL=1> using rvd = typename rvd_type<T,LMUL>::type;
// should throw an exception
template<typename T, int LMUL=1> struct rvm_type{};
template<> struct rvm_type<float64_t, 1>{ using type = rvm_avx512_float64_t; };
template<> struct rvm_type<float32_t, 1>{ using type = rvm_avx512_float32_t; };
template<> struct rvm_type<int64_t, 1>{ using type = rvm_avx512_int64_t; };
template<> struct rvm_type<int32_t, 1>{ using type = rvm_avx512_int32_t; };
template<> struct rvm_type<int16_t, 1>{ using type = rvm_avx512_int16_t; };
template<> struct rvm_type<int8_t, 1>{ using type = rvm_avx512_int8_t; };
template<> struct rvm_type<uint64_t, 1>{ using type = rvm_avx512_uint64_t; };
template<> struct rvm_type<uint32_t, 1>{ using type = rvm_avx512_uint32_t; };
template<> struct rvm_type<uint16_t, 1>{ using type = rvm_avx512_uint16_t; };
template<> struct rvm_type<uint8_t, 1>{ using type = rvm_avx512_uint8_t; };
template <typename T, int LMUL=1> using rvm = typename rvm_type<T,LMUL>::type;
// should throw an exception
template<typename T, int LMUL=1> constexpr uint32_t N(){ return 0; }
template<> constexpr uint32_t N<float64_t, 1>(){ return MIPP_AVX512_N_FLOAT64; }
template<> constexpr uint32_t N<float32_t, 1>(){ return MIPP_AVX512_N_FLOAT32; }
template<> constexpr uint32_t N<int64_t, 1>(){ return MIPP_AVX512_N_INT64; }
template<> constexpr uint32_t N<int32_t, 1>(){ return MIPP_AVX512_N_INT32; }
template<> constexpr uint32_t N<int16_t, 1>(){ return MIPP_AVX512_N_INT16; }
template<> constexpr uint32_t N<int8_t, 1>(){ return MIPP_AVX512_N_INT8; }
template<> constexpr uint32_t N<uint64_t, 1>(){ return MIPP_AVX512_N_UINT64; }
template<> constexpr uint32_t N<uint32_t, 1>(){ return MIPP_AVX512_N_UINT32; }
template<> constexpr uint32_t N<uint16_t, 1>(){ return MIPP_AVX512_N_UINT16; }
template<> constexpr uint32_t N<uint8_t, 1>(){ return MIPP_AVX512_N_UINT8; }
rvd<float64_t,1> cast_float64(const rvd<float64_t,1> r0) {
	return mipp_avx512_cast_float64_float64(r0);
}
rvd<float64_t,1> cast_float64(const rvd<float32_t,1> r0) {
	return mipp_avx512_cast_float32_float64(r0);
}
rvd<float64_t,1> cast_float64(const rvd<int64_t,1> r0) {
	return mipp_avx512_cast_int64_float64(r0);
}
rvd<float64_t,1> cast_float64(const rvd<int32_t,1> r0) {
	return mipp_avx512_cast_int32_float64(r0);
}
rvd<float64_t,1> cast_float64(const rvd<int16_t,1> r0) {
	return mipp_avx512_cast_int16_float64(r0);
}
rvd<float64_t,1> cast_float64(const rvd<int8_t,1> r0) {
	return mipp_avx512_cast_int8_float64(r0);
}
rvd<float64_t,1> cast_float64(const rvd<uint64_t,1> r0) {
	return mipp_avx512_cast_uint64_float64(r0);
}
rvd<float64_t,1> cast_float64(const rvd<uint32_t,1> r0) {
	return mipp_avx512_cast_uint32_float64(r0);
}
rvd<float64_t,1> cast_float64(const rvd<uint16_t,1> r0) {
	return mipp_avx512_cast_uint16_float64(r0);
}
rvd<float64_t,1> cast_float64(const rvd<uint8_t,1> r0) {
	return mipp_avx512_cast_uint8_float64(r0);
}
rvd<float32_t,1> cast_float32(const rvd<float64_t,1> r0) {
	return mipp_avx512_cast_float64_float32(r0);
}
rvd<float32_t,1> cast_float32(const rvd<float32_t,1> r0) {
	return mipp_avx512_cast_float32_float32(r0);
}
rvd<float32_t,1> cast_float32(const rvd<int64_t,1> r0) {
	return mipp_avx512_cast_int64_float32(r0);
}
rvd<float32_t,1> cast_float32(const rvd<int32_t,1> r0) {
	return mipp_avx512_cast_int32_float32(r0);
}
rvd<float32_t,1> cast_float32(const rvd<int16_t,1> r0) {
	return mipp_avx512_cast_int16_float32(r0);
}
rvd<float32_t,1> cast_float32(const rvd<int8_t,1> r0) {
	return mipp_avx512_cast_int8_float32(r0);
}
rvd<float32_t,1> cast_float32(const rvd<uint64_t,1> r0) {
	return mipp_avx512_cast_uint64_float32(r0);
}
rvd<float32_t,1> cast_float32(const rvd<uint32_t,1> r0) {
	return mipp_avx512_cast_uint32_float32(r0);
}
rvd<float32_t,1> cast_float32(const rvd<uint16_t,1> r0) {
	return mipp_avx512_cast_uint16_float32(r0);
}
rvd<float32_t,1> cast_float32(const rvd<uint8_t,1> r0) {
	return mipp_avx512_cast_uint8_float32(r0);
}
rvd<int64_t,1> cast_int64(const rvd<float64_t,1> r0) {
	return mipp_avx512_cast_float64_int64(r0);
}
rvd<int64_t,1> cast_int64(const rvd<float32_t,1> r0) {
	return mipp_avx512_cast_float32_int64(r0);
}
rvd<int64_t,1> cast_int64(const rvd<int64_t,1> r0) {
	return mipp_avx512_cast_int64_int64(r0);
}
rvd<int64_t,1> cast_int64(const rvd<int32_t,1> r0) {
	return mipp_avx512_cast_int32_int64(r0);
}
rvd<int64_t,1> cast_int64(const rvd<int16_t,1> r0) {
	return mipp_avx512_cast_int16_int64(r0);
}
rvd<int64_t,1> cast_int64(const rvd<int8_t,1> r0) {
	return mipp_avx512_cast_int8_int64(r0);
}
rvd<int64_t,1> cast_int64(const rvd<uint64_t,1> r0) {
	return mipp_avx512_cast_uint64_int64(r0);
}
rvd<int64_t,1> cast_int64(const rvd<uint32_t,1> r0) {
	return mipp_avx512_cast_uint32_int64(r0);
}
rvd<int64_t,1> cast_int64(const rvd<uint16_t,1> r0) {
	return mipp_avx512_cast_uint16_int64(r0);
}
rvd<int64_t,1> cast_int64(const rvd<uint8_t,1> r0) {
	return mipp_avx512_cast_uint8_int64(r0);
}
rvd<int32_t,1> cast_int32(const rvd<float64_t,1> r0) {
	return mipp_avx512_cast_float64_int32(r0);
}
rvd<int32_t,1> cast_int32(const rvd<float32_t,1> r0) {
	return mipp_avx512_cast_float32_int32(r0);
}
rvd<int32_t,1> cast_int32(const rvd<int64_t,1> r0) {
	return mipp_avx512_cast_int64_int32(r0);
}
rvd<int32_t,1> cast_int32(const rvd<int32_t,1> r0) {
	return mipp_avx512_cast_int32_int32(r0);
}
rvd<int32_t,1> cast_int32(const rvd<int16_t,1> r0) {
	return mipp_avx512_cast_int16_int32(r0);
}
rvd<int32_t,1> cast_int32(const rvd<int8_t,1> r0) {
	return mipp_avx512_cast_int8_int32(r0);
}
rvd<int32_t,1> cast_int32(const rvd<uint64_t,1> r0) {
	return mipp_avx512_cast_uint64_int32(r0);
}
rvd<int32_t,1> cast_int32(const rvd<uint32_t,1> r0) {
	return mipp_avx512_cast_uint32_int32(r0);
}
rvd<int32_t,1> cast_int32(const rvd<uint16_t,1> r0) {
	return mipp_avx512_cast_uint16_int32(r0);
}
rvd<int32_t,1> cast_int32(const rvd<uint8_t,1> r0) {
	return mipp_avx512_cast_uint8_int32(r0);
}
rvd<int16_t,1> cast_int16(const rvd<float64_t,1> r0) {
	return mipp_avx512_cast_float64_int16(r0);
}
rvd<int16_t,1> cast_int16(const rvd<float32_t,1> r0) {
	return mipp_avx512_cast_float32_int16(r0);
}
rvd<int16_t,1> cast_int16(const rvd<int64_t,1> r0) {
	return mipp_avx512_cast_int64_int16(r0);
}
rvd<int16_t,1> cast_int16(const rvd<int32_t,1> r0) {
	return mipp_avx512_cast_int32_int16(r0);
}
rvd<int16_t,1> cast_int16(const rvd<int16_t,1> r0) {
	return mipp_avx512_cast_int16_int16(r0);
}
rvd<int16_t,1> cast_int16(const rvd<int8_t,1> r0) {
	return mipp_avx512_cast_int8_int16(r0);
}
rvd<int16_t,1> cast_int16(const rvd<uint64_t,1> r0) {
	return mipp_avx512_cast_uint64_int16(r0);
}
rvd<int16_t,1> cast_int16(const rvd<uint32_t,1> r0) {
	return mipp_avx512_cast_uint32_int16(r0);
}
rvd<int16_t,1> cast_int16(const rvd<uint16_t,1> r0) {
	return mipp_avx512_cast_uint16_int16(r0);
}
rvd<int16_t,1> cast_int16(const rvd<uint8_t,1> r0) {
	return mipp_avx512_cast_uint8_int16(r0);
}
rvd<int8_t,1> cast_int8(const rvd<float64_t,1> r0) {
	return mipp_avx512_cast_float64_int8(r0);
}
rvd<int8_t,1> cast_int8(const rvd<float32_t,1> r0) {
	return mipp_avx512_cast_float32_int8(r0);
}
rvd<int8_t,1> cast_int8(const rvd<int64_t,1> r0) {
	return mipp_avx512_cast_int64_int8(r0);
}
rvd<int8_t,1> cast_int8(const rvd<int32_t,1> r0) {
	return mipp_avx512_cast_int32_int8(r0);
}
rvd<int8_t,1> cast_int8(const rvd<int16_t,1> r0) {
	return mipp_avx512_cast_int16_int8(r0);
}
rvd<int8_t,1> cast_int8(const rvd<int8_t,1> r0) {
	return mipp_avx512_cast_int8_int8(r0);
}
rvd<int8_t,1> cast_int8(const rvd<uint64_t,1> r0) {
	return mipp_avx512_cast_uint64_int8(r0);
}
rvd<int8_t,1> cast_int8(const rvd<uint32_t,1> r0) {
	return mipp_avx512_cast_uint32_int8(r0);
}
rvd<int8_t,1> cast_int8(const rvd<uint16_t,1> r0) {
	return mipp_avx512_cast_uint16_int8(r0);
}
rvd<int8_t,1> cast_int8(const rvd<uint8_t,1> r0) {
	return mipp_avx512_cast_uint8_int8(r0);
}
rvd<uint64_t,1> cast_uint64(const rvd<float64_t,1> r0) {
	return mipp_avx512_cast_float64_uint64(r0);
}
rvd<uint64_t,1> cast_uint64(const rvd<float32_t,1> r0) {
	return mipp_avx512_cast_float32_uint64(r0);
}
rvd<uint64_t,1> cast_uint64(const rvd<int64_t,1> r0) {
	return mipp_avx512_cast_int64_uint64(r0);
}
rvd<uint64_t,1> cast_uint64(const rvd<int32_t,1> r0) {
	return mipp_avx512_cast_int32_uint64(r0);
}
rvd<uint64_t,1> cast_uint64(const rvd<int16_t,1> r0) {
	return mipp_avx512_cast_int16_uint64(r0);
}
rvd<uint64_t,1> cast_uint64(const rvd<int8_t,1> r0) {
	return mipp_avx512_cast_int8_uint64(r0);
}
rvd<uint64_t,1> cast_uint64(const rvd<uint64_t,1> r0) {
	return mipp_avx512_cast_uint64_uint64(r0);
}
rvd<uint64_t,1> cast_uint64(const rvd<uint32_t,1> r0) {
	return mipp_avx512_cast_uint32_uint64(r0);
}
rvd<uint64_t,1> cast_uint64(const rvd<uint16_t,1> r0) {
	return mipp_avx512_cast_uint16_uint64(r0);
}
rvd<uint64_t,1> cast_uint64(const rvd<uint8_t,1> r0) {
	return mipp_avx512_cast_uint8_uint64(r0);
}
rvd<uint32_t,1> cast_uint32(const rvd<float64_t,1> r0) {
	return mipp_avx512_cast_float64_uint32(r0);
}
rvd<uint32_t,1> cast_uint32(const rvd<float32_t,1> r0) {
	return mipp_avx512_cast_float32_uint32(r0);
}
rvd<uint32_t,1> cast_uint32(const rvd<int64_t,1> r0) {
	return mipp_avx512_cast_int64_uint32(r0);
}
rvd<uint32_t,1> cast_uint32(const rvd<int32_t,1> r0) {
	return mipp_avx512_cast_int32_uint32(r0);
}
rvd<uint32_t,1> cast_uint32(const rvd<int16_t,1> r0) {
	return mipp_avx512_cast_int16_uint32(r0);
}
rvd<uint32_t,1> cast_uint32(const rvd<int8_t,1> r0) {
	return mipp_avx512_cast_int8_uint32(r0);
}
rvd<uint32_t,1> cast_uint32(const rvd<uint64_t,1> r0) {
	return mipp_avx512_cast_uint64_uint32(r0);
}
rvd<uint32_t,1> cast_uint32(const rvd<uint32_t,1> r0) {
	return mipp_avx512_cast_uint32_uint32(r0);
}
rvd<uint32_t,1> cast_uint32(const rvd<uint16_t,1> r0) {
	return mipp_avx512_cast_uint16_uint32(r0);
}
rvd<uint32_t,1> cast_uint32(const rvd<uint8_t,1> r0) {
	return mipp_avx512_cast_uint8_uint32(r0);
}
rvd<uint16_t,1> cast_uint16(const rvd<float64_t,1> r0) {
	return mipp_avx512_cast_float64_uint16(r0);
}
rvd<uint16_t,1> cast_uint16(const rvd<float32_t,1> r0) {
	return mipp_avx512_cast_float32_uint16(r0);
}
rvd<uint16_t,1> cast_uint16(const rvd<int64_t,1> r0) {
	return mipp_avx512_cast_int64_uint16(r0);
}
rvd<uint16_t,1> cast_uint16(const rvd<int32_t,1> r0) {
	return mipp_avx512_cast_int32_uint16(r0);
}
rvd<uint16_t,1> cast_uint16(const rvd<int16_t,1> r0) {
	return mipp_avx512_cast_int16_uint16(r0);
}
rvd<uint16_t,1> cast_uint16(const rvd<int8_t,1> r0) {
	return mipp_avx512_cast_int8_uint16(r0);
}
rvd<uint16_t,1> cast_uint16(const rvd<uint64_t,1> r0) {
	return mipp_avx512_cast_uint64_uint16(r0);
}
rvd<uint16_t,1> cast_uint16(const rvd<uint32_t,1> r0) {
	return mipp_avx512_cast_uint32_uint16(r0);
}
rvd<uint16_t,1> cast_uint16(const rvd<uint16_t,1> r0) {
	return mipp_avx512_cast_uint16_uint16(r0);
}
rvd<uint16_t,1> cast_uint16(const rvd<uint8_t,1> r0) {
	return mipp_avx512_cast_uint8_uint16(r0);
}
rvd<uint8_t,1> cast_uint8(const rvd<float64_t,1> r0) {
	return mipp_avx512_cast_float64_uint8(r0);
}
rvd<uint8_t,1> cast_uint8(const rvd<float32_t,1> r0) {
	return mipp_avx512_cast_float32_uint8(r0);
}
rvd<uint8_t,1> cast_uint8(const rvd<int64_t,1> r0) {
	return mipp_avx512_cast_int64_uint8(r0);
}
rvd<uint8_t,1> cast_uint8(const rvd<int32_t,1> r0) {
	return mipp_avx512_cast_int32_uint8(r0);
}
rvd<uint8_t,1> cast_uint8(const rvd<int16_t,1> r0) {
	return mipp_avx512_cast_int16_uint8(r0);
}
rvd<uint8_t,1> cast_uint8(const rvd<int8_t,1> r0) {
	return mipp_avx512_cast_int8_uint8(r0);
}
rvd<uint8_t,1> cast_uint8(const rvd<uint64_t,1> r0) {
	return mipp_avx512_cast_uint64_uint8(r0);
}
rvd<uint8_t,1> cast_uint8(const rvd<uint32_t,1> r0) {
	return mipp_avx512_cast_uint32_uint8(r0);
}
rvd<uint8_t,1> cast_uint8(const rvd<uint16_t,1> r0) {
	return mipp_avx512_cast_uint16_uint8(r0);
}
rvd<uint8_t,1> cast_uint8(const rvd<uint8_t,1> r0) {
	return mipp_avx512_cast_uint8_uint8(r0);
}
rvm<float64_t,1> cast_float64(const rvm<float64_t,1> m0) {
	return mipp_avx512_cast_k_float64_float64(m0);
}
rvm<float64_t,1> cast_float64(const rvm<float32_t,1> m0) {
	return mipp_avx512_cast_k_float32_float64(m0);
}
rvm<float64_t,1> cast_float64(const rvm<int64_t,1> m0) {
	return mipp_avx512_cast_k_int64_float64(m0);
}
rvm<float64_t,1> cast_float64(const rvm<int32_t,1> m0) {
	return mipp_avx512_cast_k_int32_float64(m0);
}
rvm<float64_t,1> cast_float64(const rvm<int16_t,1> m0) {
	return mipp_avx512_cast_k_int16_float64(m0);
}
rvm<float64_t,1> cast_float64(const rvm<int8_t,1> m0) {
	return mipp_avx512_cast_k_int8_float64(m0);
}
rvm<float64_t,1> cast_float64(const rvm<uint64_t,1> m0) {
	return mipp_avx512_cast_k_uint64_float64(m0);
}
rvm<float64_t,1> cast_float64(const rvm<uint32_t,1> m0) {
	return mipp_avx512_cast_k_uint32_float64(m0);
}
rvm<float64_t,1> cast_float64(const rvm<uint16_t,1> m0) {
	return mipp_avx512_cast_k_uint16_float64(m0);
}
rvm<float64_t,1> cast_float64(const rvm<uint8_t,1> m0) {
	return mipp_avx512_cast_k_uint8_float64(m0);
}
rvm<float32_t,1> cast_float32(const rvm<float64_t,1> m0) {
	return mipp_avx512_cast_k_float64_float32(m0);
}
rvm<float32_t,1> cast_float32(const rvm<float32_t,1> m0) {
	return mipp_avx512_cast_k_float32_float32(m0);
}
rvm<float32_t,1> cast_float32(const rvm<int64_t,1> m0) {
	return mipp_avx512_cast_k_int64_float32(m0);
}
rvm<float32_t,1> cast_float32(const rvm<int32_t,1> m0) {
	return mipp_avx512_cast_k_int32_float32(m0);
}
rvm<float32_t,1> cast_float32(const rvm<int16_t,1> m0) {
	return mipp_avx512_cast_k_int16_float32(m0);
}
rvm<float32_t,1> cast_float32(const rvm<int8_t,1> m0) {
	return mipp_avx512_cast_k_int8_float32(m0);
}
rvm<float32_t,1> cast_float32(const rvm<uint64_t,1> m0) {
	return mipp_avx512_cast_k_uint64_float32(m0);
}
rvm<float32_t,1> cast_float32(const rvm<uint32_t,1> m0) {
	return mipp_avx512_cast_k_uint32_float32(m0);
}
rvm<float32_t,1> cast_float32(const rvm<uint16_t,1> m0) {
	return mipp_avx512_cast_k_uint16_float32(m0);
}
rvm<float32_t,1> cast_float32(const rvm<uint8_t,1> m0) {
	return mipp_avx512_cast_k_uint8_float32(m0);
}
rvm<int64_t,1> cast_int64(const rvm<float64_t,1> m0) {
	return mipp_avx512_cast_k_float64_int64(m0);
}
rvm<int64_t,1> cast_int64(const rvm<float32_t,1> m0) {
	return mipp_avx512_cast_k_float32_int64(m0);
}
rvm<int64_t,1> cast_int64(const rvm<int64_t,1> m0) {
	return mipp_avx512_cast_k_int64_int64(m0);
}
rvm<int64_t,1> cast_int64(const rvm<int32_t,1> m0) {
	return mipp_avx512_cast_k_int32_int64(m0);
}
rvm<int64_t,1> cast_int64(const rvm<int16_t,1> m0) {
	return mipp_avx512_cast_k_int16_int64(m0);
}
rvm<int64_t,1> cast_int64(const rvm<int8_t,1> m0) {
	return mipp_avx512_cast_k_int8_int64(m0);
}
rvm<int64_t,1> cast_int64(const rvm<uint64_t,1> m0) {
	return mipp_avx512_cast_k_uint64_int64(m0);
}
rvm<int64_t,1> cast_int64(const rvm<uint32_t,1> m0) {
	return mipp_avx512_cast_k_uint32_int64(m0);
}
rvm<int64_t,1> cast_int64(const rvm<uint16_t,1> m0) {
	return mipp_avx512_cast_k_uint16_int64(m0);
}
rvm<int64_t,1> cast_int64(const rvm<uint8_t,1> m0) {
	return mipp_avx512_cast_k_uint8_int64(m0);
}
rvm<int32_t,1> cast_int32(const rvm<float64_t,1> m0) {
	return mipp_avx512_cast_k_float64_int32(m0);
}
rvm<int32_t,1> cast_int32(const rvm<float32_t,1> m0) {
	return mipp_avx512_cast_k_float32_int32(m0);
}
rvm<int32_t,1> cast_int32(const rvm<int64_t,1> m0) {
	return mipp_avx512_cast_k_int64_int32(m0);
}
rvm<int32_t,1> cast_int32(const rvm<int32_t,1> m0) {
	return mipp_avx512_cast_k_int32_int32(m0);
}
rvm<int32_t,1> cast_int32(const rvm<int16_t,1> m0) {
	return mipp_avx512_cast_k_int16_int32(m0);
}
rvm<int32_t,1> cast_int32(const rvm<int8_t,1> m0) {
	return mipp_avx512_cast_k_int8_int32(m0);
}
rvm<int32_t,1> cast_int32(const rvm<uint64_t,1> m0) {
	return mipp_avx512_cast_k_uint64_int32(m0);
}
rvm<int32_t,1> cast_int32(const rvm<uint32_t,1> m0) {
	return mipp_avx512_cast_k_uint32_int32(m0);
}
rvm<int32_t,1> cast_int32(const rvm<uint16_t,1> m0) {
	return mipp_avx512_cast_k_uint16_int32(m0);
}
rvm<int32_t,1> cast_int32(const rvm<uint8_t,1> m0) {
	return mipp_avx512_cast_k_uint8_int32(m0);
}
rvm<int16_t,1> cast_int16(const rvm<float64_t,1> m0) {
	return mipp_avx512_cast_k_float64_int16(m0);
}
rvm<int16_t,1> cast_int16(const rvm<float32_t,1> m0) {
	return mipp_avx512_cast_k_float32_int16(m0);
}
rvm<int16_t,1> cast_int16(const rvm<int64_t,1> m0) {
	return mipp_avx512_cast_k_int64_int16(m0);
}
rvm<int16_t,1> cast_int16(const rvm<int32_t,1> m0) {
	return mipp_avx512_cast_k_int32_int16(m0);
}
rvm<int16_t,1> cast_int16(const rvm<int16_t,1> m0) {
	return mipp_avx512_cast_k_int16_int16(m0);
}
rvm<int16_t,1> cast_int16(const rvm<int8_t,1> m0) {
	return mipp_avx512_cast_k_int8_int16(m0);
}
rvm<int16_t,1> cast_int16(const rvm<uint64_t,1> m0) {
	return mipp_avx512_cast_k_uint64_int16(m0);
}
rvm<int16_t,1> cast_int16(const rvm<uint32_t,1> m0) {
	return mipp_avx512_cast_k_uint32_int16(m0);
}
rvm<int16_t,1> cast_int16(const rvm<uint16_t,1> m0) {
	return mipp_avx512_cast_k_uint16_int16(m0);
}
rvm<int16_t,1> cast_int16(const rvm<uint8_t,1> m0) {
	return mipp_avx512_cast_k_uint8_int16(m0);
}
rvm<int8_t,1> cast_int8(const rvm<float64_t,1> m0) {
	return mipp_avx512_cast_k_float64_int8(m0);
}
rvm<int8_t,1> cast_int8(const rvm<float32_t,1> m0) {
	return mipp_avx512_cast_k_float32_int8(m0);
}
rvm<int8_t,1> cast_int8(const rvm<int64_t,1> m0) {
	return mipp_avx512_cast_k_int64_int8(m0);
}
rvm<int8_t,1> cast_int8(const rvm<int32_t,1> m0) {
	return mipp_avx512_cast_k_int32_int8(m0);
}
rvm<int8_t,1> cast_int8(const rvm<int16_t,1> m0) {
	return mipp_avx512_cast_k_int16_int8(m0);
}
rvm<int8_t,1> cast_int8(const rvm<int8_t,1> m0) {
	return mipp_avx512_cast_k_int8_int8(m0);
}
rvm<int8_t,1> cast_int8(const rvm<uint64_t,1> m0) {
	return mipp_avx512_cast_k_uint64_int8(m0);
}
rvm<int8_t,1> cast_int8(const rvm<uint32_t,1> m0) {
	return mipp_avx512_cast_k_uint32_int8(m0);
}
rvm<int8_t,1> cast_int8(const rvm<uint16_t,1> m0) {
	return mipp_avx512_cast_k_uint16_int8(m0);
}
rvm<int8_t,1> cast_int8(const rvm<uint8_t,1> m0) {
	return mipp_avx512_cast_k_uint8_int8(m0);
}
rvm<uint64_t,1> cast_uint64(const rvm<float64_t,1> m0) {
	return mipp_avx512_cast_k_float64_uint64(m0);
}
rvm<uint64_t,1> cast_uint64(const rvm<float32_t,1> m0) {
	return mipp_avx512_cast_k_float32_uint64(m0);
}
rvm<uint64_t,1> cast_uint64(const rvm<int64_t,1> m0) {
	return mipp_avx512_cast_k_int64_uint64(m0);
}
rvm<uint64_t,1> cast_uint64(const rvm<int32_t,1> m0) {
	return mipp_avx512_cast_k_int32_uint64(m0);
}
rvm<uint64_t,1> cast_uint64(const rvm<int16_t,1> m0) {
	return mipp_avx512_cast_k_int16_uint64(m0);
}
rvm<uint64_t,1> cast_uint64(const rvm<int8_t,1> m0) {
	return mipp_avx512_cast_k_int8_uint64(m0);
}
rvm<uint64_t,1> cast_uint64(const rvm<uint64_t,1> m0) {
	return mipp_avx512_cast_k_uint64_uint64(m0);
}
rvm<uint64_t,1> cast_uint64(const rvm<uint32_t,1> m0) {
	return mipp_avx512_cast_k_uint32_uint64(m0);
}
rvm<uint64_t,1> cast_uint64(const rvm<uint16_t,1> m0) {
	return mipp_avx512_cast_k_uint16_uint64(m0);
}
rvm<uint64_t,1> cast_uint64(const rvm<uint8_t,1> m0) {
	return mipp_avx512_cast_k_uint8_uint64(m0);
}
rvm<uint32_t,1> cast_uint32(const rvm<float64_t,1> m0) {
	return mipp_avx512_cast_k_float64_uint32(m0);
}
rvm<uint32_t,1> cast_uint32(const rvm<float32_t,1> m0) {
	return mipp_avx512_cast_k_float32_uint32(m0);
}
rvm<uint32_t,1> cast_uint32(const rvm<int64_t,1> m0) {
	return mipp_avx512_cast_k_int64_uint32(m0);
}
rvm<uint32_t,1> cast_uint32(const rvm<int32_t,1> m0) {
	return mipp_avx512_cast_k_int32_uint32(m0);
}
rvm<uint32_t,1> cast_uint32(const rvm<int16_t,1> m0) {
	return mipp_avx512_cast_k_int16_uint32(m0);
}
rvm<uint32_t,1> cast_uint32(const rvm<int8_t,1> m0) {
	return mipp_avx512_cast_k_int8_uint32(m0);
}
rvm<uint32_t,1> cast_uint32(const rvm<uint64_t,1> m0) {
	return mipp_avx512_cast_k_uint64_uint32(m0);
}
rvm<uint32_t,1> cast_uint32(const rvm<uint32_t,1> m0) {
	return mipp_avx512_cast_k_uint32_uint32(m0);
}
rvm<uint32_t,1> cast_uint32(const rvm<uint16_t,1> m0) {
	return mipp_avx512_cast_k_uint16_uint32(m0);
}
rvm<uint32_t,1> cast_uint32(const rvm<uint8_t,1> m0) {
	return mipp_avx512_cast_k_uint8_uint32(m0);
}
rvm<uint16_t,1> cast_uint16(const rvm<float64_t,1> m0) {
	return mipp_avx512_cast_k_float64_uint16(m0);
}
rvm<uint16_t,1> cast_uint16(const rvm<float32_t,1> m0) {
	return mipp_avx512_cast_k_float32_uint16(m0);
}
rvm<uint16_t,1> cast_uint16(const rvm<int64_t,1> m0) {
	return mipp_avx512_cast_k_int64_uint16(m0);
}
rvm<uint16_t,1> cast_uint16(const rvm<int32_t,1> m0) {
	return mipp_avx512_cast_k_int32_uint16(m0);
}
rvm<uint16_t,1> cast_uint16(const rvm<int16_t,1> m0) {
	return mipp_avx512_cast_k_int16_uint16(m0);
}
rvm<uint16_t,1> cast_uint16(const rvm<int8_t,1> m0) {
	return mipp_avx512_cast_k_int8_uint16(m0);
}
rvm<uint16_t,1> cast_uint16(const rvm<uint64_t,1> m0) {
	return mipp_avx512_cast_k_uint64_uint16(m0);
}
rvm<uint16_t,1> cast_uint16(const rvm<uint32_t,1> m0) {
	return mipp_avx512_cast_k_uint32_uint16(m0);
}
rvm<uint16_t,1> cast_uint16(const rvm<uint16_t,1> m0) {
	return mipp_avx512_cast_k_uint16_uint16(m0);
}
rvm<uint16_t,1> cast_uint16(const rvm<uint8_t,1> m0) {
	return mipp_avx512_cast_k_uint8_uint16(m0);
}
rvm<uint8_t,1> cast_uint8(const rvm<float64_t,1> m0) {
	return mipp_avx512_cast_k_float64_uint8(m0);
}
rvm<uint8_t,1> cast_uint8(const rvm<float32_t,1> m0) {
	return mipp_avx512_cast_k_float32_uint8(m0);
}
rvm<uint8_t,1> cast_uint8(const rvm<int64_t,1> m0) {
	return mipp_avx512_cast_k_int64_uint8(m0);
}
rvm<uint8_t,1> cast_uint8(const rvm<int32_t,1> m0) {
	return mipp_avx512_cast_k_int32_uint8(m0);
}
rvm<uint8_t,1> cast_uint8(const rvm<int16_t,1> m0) {
	return mipp_avx512_cast_k_int16_uint8(m0);
}
rvm<uint8_t,1> cast_uint8(const rvm<int8_t,1> m0) {
	return mipp_avx512_cast_k_int8_uint8(m0);
}
rvm<uint8_t,1> cast_uint8(const rvm<uint64_t,1> m0) {
	return mipp_avx512_cast_k_uint64_uint8(m0);
}
rvm<uint8_t,1> cast_uint8(const rvm<uint32_t,1> m0) {
	return mipp_avx512_cast_k_uint32_uint8(m0);
}
rvm<uint8_t,1> cast_uint8(const rvm<uint16_t,1> m0) {
	return mipp_avx512_cast_k_uint16_uint8(m0);
}
rvm<uint8_t,1> cast_uint8(const rvm<uint8_t,1> m0) {
	return mipp_avx512_cast_k_uint8_uint8(m0);
}
rvd<float64_t,1> toreg(const rvm<float64_t,1> m0) {
	return mipp_avx512_toreg_float64(m0);
}
rvd<float32_t,1> toreg(const rvm<float32_t,1> m0) {
	return mipp_avx512_toreg_float32(m0);
}
rvd<int64_t,1> toreg(const rvm<int64_t,1> m0) {
	return mipp_avx512_toreg_int64(m0);
}
rvd<int32_t,1> toreg(const rvm<int32_t,1> m0) {
	return mipp_avx512_toreg_int32(m0);
}
rvd<int16_t,1> toreg(const rvm<int16_t,1> m0) {
	return mipp_avx512_toreg_int16(m0);
}
rvd<int8_t,1> toreg(const rvm<int8_t,1> m0) {
	return mipp_avx512_toreg_int8(m0);
}
rvd<uint64_t,1> toreg(const rvm<uint64_t,1> m0) {
	return mipp_avx512_toreg_uint64(m0);
}
rvd<uint32_t,1> toreg(const rvm<uint32_t,1> m0) {
	return mipp_avx512_toreg_uint32(m0);
}
rvd<uint16_t,1> toreg(const rvm<uint16_t,1> m0) {
	return mipp_avx512_toreg_uint16(m0);
}
rvd<uint8_t,1> toreg(const rvm<uint8_t,1> m0) {
	return mipp_avx512_toreg_uint8(m0);
}
rvm<float64_t,1> tomsk(const rvd<float64_t,1> r0) {
	return mipp_avx512_tomsk_float64(r0);
}
rvm<float32_t,1> tomsk(const rvd<float32_t,1> r0) {
	return mipp_avx512_tomsk_float32(r0);
}
rvm<int64_t,1> tomsk(const rvd<int64_t,1> r0) {
	return mipp_avx512_tomsk_int64(r0);
}
rvm<int32_t,1> tomsk(const rvd<int32_t,1> r0) {
	return mipp_avx512_tomsk_int32(r0);
}
rvm<int16_t,1> tomsk(const rvd<int16_t,1> r0) {
	return mipp_avx512_tomsk_int16(r0);
}
rvm<int8_t,1> tomsk(const rvd<int8_t,1> r0) {
	return mipp_avx512_tomsk_int8(r0);
}
rvm<uint64_t,1> tomsk(const rvd<uint64_t,1> r0) {
	return mipp_avx512_tomsk_uint64(r0);
}
rvm<uint32_t,1> tomsk(const rvd<uint32_t,1> r0) {
	return mipp_avx512_tomsk_uint32(r0);
}
rvm<uint16_t,1> tomsk(const rvd<uint16_t,1> r0) {
	return mipp_avx512_tomsk_uint16(r0);
}
rvm<uint8_t,1> tomsk(const rvd<uint8_t,1> r0) {
	return mipp_avx512_tomsk_uint8(r0);
}
rvd<float64_t,1> load(const float64_t* p0) {
	return mipp_avx512_load_float64(p0);
}
rvd<float32_t,1> load(const float32_t* p0) {
	return mipp_avx512_load_float32(p0);
}
rvd<int64_t,1> load(const int64_t* p0) {
	return mipp_avx512_load_int64(p0);
}
rvd<int32_t,1> load(const int32_t* p0) {
	return mipp_avx512_load_int32(p0);
}
rvd<int16_t,1> load(const int16_t* p0) {
	return mipp_avx512_load_int16(p0);
}
rvd<int8_t,1> load(const int8_t* p0) {
	return mipp_avx512_load_int8(p0);
}
rvd<uint64_t,1> load(const uint64_t* p0) {
	return mipp_avx512_load_uint64(p0);
}
rvd<uint32_t,1> load(const uint32_t* p0) {
	return mipp_avx512_load_uint32(p0);
}
rvd<uint16_t,1> load(const uint16_t* p0) {
	return mipp_avx512_load_uint16(p0);
}
rvd<uint8_t,1> load(const uint8_t* p0) {
	return mipp_avx512_load_uint8(p0);
}
rvd<float64_t,1> loadu(const float64_t* p0) {
	return mipp_avx512_loadu_float64(p0);
}
rvd<float32_t,1> loadu(const float32_t* p0) {
	return mipp_avx512_loadu_float32(p0);
}
rvd<int64_t,1> loadu(const int64_t* p0) {
	return mipp_avx512_loadu_int64(p0);
}
rvd<int32_t,1> loadu(const int32_t* p0) {
	return mipp_avx512_loadu_int32(p0);
}
rvd<int16_t,1> loadu(const int16_t* p0) {
	return mipp_avx512_loadu_int16(p0);
}
rvd<int8_t,1> loadu(const int8_t* p0) {
	return mipp_avx512_loadu_int8(p0);
}
rvd<uint64_t,1> loadu(const uint64_t* p0) {
	return mipp_avx512_loadu_uint64(p0);
}
rvd<uint32_t,1> loadu(const uint32_t* p0) {
	return mipp_avx512_loadu_uint32(p0);
}
rvd<uint16_t,1> loadu(const uint16_t* p0) {
	return mipp_avx512_loadu_uint16(p0);
}
rvd<uint8_t,1> loadu(const uint8_t* p0) {
	return mipp_avx512_loadu_uint8(p0);
}
void store(float64_t* p0, const rvd<float64_t,1> r0) {
	mipp_avx512_store_float64(p0, r0);
}
void store(float32_t* p0, const rvd<float32_t,1> r0) {
	mipp_avx512_store_float32(p0, r0);
}
void store(int64_t* p0, const rvd<int64_t,1> r0) {
	mipp_avx512_store_int64(p0, r0);
}
void store(int32_t* p0, const rvd<int32_t,1> r0) {
	mipp_avx512_store_int32(p0, r0);
}
void store(int16_t* p0, const rvd<int16_t,1> r0) {
	mipp_avx512_store_int16(p0, r0);
}
void store(int8_t* p0, const rvd<int8_t,1> r0) {
	mipp_avx512_store_int8(p0, r0);
}
void store(uint64_t* p0, const rvd<uint64_t,1> r0) {
	mipp_avx512_store_uint64(p0, r0);
}
void store(uint32_t* p0, const rvd<uint32_t,1> r0) {
	mipp_avx512_store_uint32(p0, r0);
}
void store(uint16_t* p0, const rvd<uint16_t,1> r0) {
	mipp_avx512_store_uint16(p0, r0);
}
void store(uint8_t* p0, const rvd<uint8_t,1> r0) {
	mipp_avx512_store_uint8(p0, r0);
}
void storeu(float64_t* p0, const rvd<float64_t,1> r0) {
	mipp_avx512_storeu_float64(p0, r0);
}
void storeu(float32_t* p0, const rvd<float32_t,1> r0) {
	mipp_avx512_storeu_float32(p0, r0);
}
void storeu(int64_t* p0, const rvd<int64_t,1> r0) {
	mipp_avx512_storeu_int64(p0, r0);
}
void storeu(int32_t* p0, const rvd<int32_t,1> r0) {
	mipp_avx512_storeu_int32(p0, r0);
}
void storeu(int16_t* p0, const rvd<int16_t,1> r0) {
	mipp_avx512_storeu_int16(p0, r0);
}
void storeu(int8_t* p0, const rvd<int8_t,1> r0) {
	mipp_avx512_storeu_int8(p0, r0);
}
void storeu(uint64_t* p0, const rvd<uint64_t,1> r0) {
	mipp_avx512_storeu_uint64(p0, r0);
}
void storeu(uint32_t* p0, const rvd<uint32_t,1> r0) {
	mipp_avx512_storeu_uint32(p0, r0);
}
void storeu(uint16_t* p0, const rvd<uint16_t,1> r0) {
	mipp_avx512_storeu_uint16(p0, r0);
}
void storeu(uint8_t* p0, const rvd<uint8_t,1> r0) {
	mipp_avx512_storeu_uint8(p0, r0);
}
float64_t getfirst(const rvd<float64_t,1> r0) {
	return mipp_avx512_getfirst_float64(r0);
}
float32_t getfirst(const rvd<float32_t,1> r0) {
	return mipp_avx512_getfirst_float32(r0);
}
rvm<float64_t,1> set_float64() {
	return mipp_avx512_set_float64();
}
rvm<float32_t,1> set_float32() {
	return mipp_avx512_set_float32();
}
rvm<int64_t,1> set_int64() {
	return mipp_avx512_set_int64();
}
rvm<int32_t,1> set_int32() {
	return mipp_avx512_set_int32();
}
rvm<int16_t,1> set_int16() {
	return mipp_avx512_set_int16();
}
rvm<int8_t,1> set_int8() {
	return mipp_avx512_set_int8();
}
rvm<uint64_t,1> set_uint64() {
	return mipp_avx512_set_uint64();
}
rvm<uint32_t,1> set_uint32() {
	return mipp_avx512_set_uint32();
}
rvm<uint16_t,1> set_uint16() {
	return mipp_avx512_set_uint16();
}
rvm<uint8_t,1> set_uint8() {
	return mipp_avx512_set_uint8();
}
rvd<int64_t,1> set(const int64_t v0) {
	return mipp_avx512_set_k_int64(v0);
}
rvd<int32_t,1> set(const int32_t v0) {
	return mipp_avx512_set_k_int32(v0);
}
rvd<int16_t,1> set(const int16_t v0) {
	return mipp_avx512_set_k_int16(v0);
}
rvd<int8_t,1> set(const int8_t v0) {
	return mipp_avx512_set_k_int8(v0);
}
rvd<float64_t,1> set1(const float64_t v0) {
	return mipp_avx512_set1_float64(v0);
}
rvd<float32_t,1> set1(const float32_t v0) {
	return mipp_avx512_set1_float32(v0);
}
rvd<int64_t,1> set1(const int64_t v0) {
	return mipp_avx512_set1_int64(v0);
}
rvd<int32_t,1> set1(const int32_t v0) {
	return mipp_avx512_set1_int32(v0);
}
rvd<int16_t,1> set1(const int16_t v0) {
	return mipp_avx512_set1_int16(v0);
}
rvd<int8_t,1> set1(const int8_t v0) {
	return mipp_avx512_set1_int8(v0);
}
rvd<uint64_t,1> set1(const uint64_t v0) {
	return mipp_avx512_set1_uint64(v0);
}
rvd<uint32_t,1> set1(const uint32_t v0) {
	return mipp_avx512_set1_uint32(v0);
}
rvd<uint16_t,1> set1(const uint16_t v0) {
	return mipp_avx512_set1_uint16(v0);
}
rvd<uint8_t,1> set1(const uint8_t v0) {
	return mipp_avx512_set1_uint8(v0);
}
rvm<float64_t,1> set1_k_float64() {
	return mipp_avx512_set1_k_float64();
}
rvm<float32_t,1> set1_k_float32() {
	return mipp_avx512_set1_k_float32();
}
rvm<int64_t,1> set1_k_int64() {
	return mipp_avx512_set1_k_int64();
}
rvm<int32_t,1> set1_k_int32() {
	return mipp_avx512_set1_k_int32();
}
rvm<int16_t,1> set1_k_int16() {
	return mipp_avx512_set1_k_int16();
}
rvm<int8_t,1> set1_k_int8() {
	return mipp_avx512_set1_k_int8();
}
rvm<uint64_t,1> set1_k_uint64() {
	return mipp_avx512_set1_k_uint64();
}
rvm<uint32_t,1> set1_k_uint32() {
	return mipp_avx512_set1_k_uint32();
}
rvm<uint16_t,1> set1_k_uint16() {
	return mipp_avx512_set1_k_uint16();
}
rvm<uint8_t,1> set1_k_uint8() {
	return mipp_avx512_set1_k_uint8();
}
rvd<float64_t,1> set0_float64() {
	return mipp_avx512_set0_float64();
}
rvd<float32_t,1> set0_float32() {
	return mipp_avx512_set0_float32();
}
rvd<int64_t,1> set0_int64() {
	return mipp_avx512_set0_int64();
}
rvd<int32_t,1> set0_int32() {
	return mipp_avx512_set0_int32();
}
rvd<int16_t,1> set0_int16() {
	return mipp_avx512_set0_int16();
}
rvd<int8_t,1> set0_int8() {
	return mipp_avx512_set0_int8();
}
rvd<uint64_t,1> set0_uint64() {
	return mipp_avx512_set0_uint64();
}
rvd<uint32_t,1> set0_uint32() {
	return mipp_avx512_set0_uint32();
}
rvd<uint16_t,1> set0_uint16() {
	return mipp_avx512_set0_uint16();
}
rvd<uint8_t,1> set0_uint8() {
	return mipp_avx512_set0_uint8();
}
rvm<float64_t,1> set0_k_float64() {
	return mipp_avx512_set0_k_float64();
}
rvm<float32_t,1> set0_k_float32() {
	return mipp_avx512_set0_k_float32();
}
rvm<int64_t,1> set0_k_int64() {
	return mipp_avx512_set0_k_int64();
}
rvm<int32_t,1> set0_k_int32() {
	return mipp_avx512_set0_k_int32();
}
rvm<int16_t,1> set0_k_int16() {
	return mipp_avx512_set0_k_int16();
}
rvm<int8_t,1> set0_k_int8() {
	return mipp_avx512_set0_k_int8();
}
rvm<uint64_t,1> set0_k_uint64() {
	return mipp_avx512_set0_k_uint64();
}
rvm<uint32_t,1> set0_k_uint32() {
	return mipp_avx512_set0_k_uint32();
}
rvm<uint16_t,1> set0_k_uint16() {
	return mipp_avx512_set0_k_uint16();
}
rvm<uint8_t,1> set0_k_uint8() {
	return mipp_avx512_set0_k_uint8();
}
rvm<float64_t,1> set0_mk_float64() {
	return mipp_avx512_set0_mk_float64();
}
rvm<float32_t,1> set0_mk_float32() {
	return mipp_avx512_set0_mk_float32();
}
rvm<int32_t,1> set0_mk_int32() {
	return mipp_avx512_set0_mk_int32();
}
rvd<float64_t,1> sqrt(const rvd<float64_t,1> r0) {
	return mipp_avx512_sqrt_float64(r0);
}
rvd<float32_t,1> sqrt(const rvd<float32_t,1> r0) {
	return mipp_avx512_sqrt_float32(r0);
}
rvd<float32_t,1> rsqrt(const rvd<float32_t,1> r0) {
	return mipp_avx512_rsqrt_float32(r0);
}
rvd<float64_t,1> add(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_avx512_add_float64(r0, r1);
}
rvd<float32_t,1> add(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_avx512_add_float32(r0, r1);
}
rvd<int64_t,1> add(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_avx512_add_int64(r0, r1);
}
rvd<int32_t,1> add(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_avx512_add_int32(r0, r1);
}
rvd<int16_t,1> add(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_avx512_add_int16(r0, r1);
}
rvd<int8_t,1> add(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_avx512_add_int8(r0, r1);
}
rvd<uint64_t,1> add(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_avx512_add_uint64(r0, r1);
}
rvd<uint32_t,1> add(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_avx512_add_uint32(r0, r1);
}
rvd<uint16_t,1> add(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_avx512_add_uint16(r0, r1);
}
rvd<uint8_t,1> add(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_avx512_add_uint8(r0, r1);
}
rvd<float64_t,1> sub(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_avx512_sub_float64(r0, r1);
}
rvd<float32_t,1> sub(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_avx512_sub_float32(r0, r1);
}
rvd<int64_t,1> sub(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_avx512_sub_int64(r0, r1);
}
rvd<int32_t,1> sub(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_avx512_sub_int32(r0, r1);
}
rvd<int16_t,1> sub(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_avx512_sub_int16(r0, r1);
}
rvd<int8_t,1> sub(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_avx512_sub_int8(r0, r1);
}
rvd<float64_t,1> mul(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_avx512_mul_float64(r0, r1);
}
rvd<float32_t,1> mul(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_avx512_mul_float32(r0, r1);
}
rvd<int32_t,1> mul(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_avx512_mul_int32(r0, r1);
}
rvd<int16_t,1> mul(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_avx512_mul_int16(r0, r1);
}
rvd<float64_t,1> div(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_avx512_div_float64(r0, r1);
}
rvd<float32_t,1> div(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_avx512_div_float32(r0, r1);
}
rvd<float64_t,1> min(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_avx512_min_float64(r0, r1);
}
rvd<float32_t,1> min(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_avx512_min_float32(r0, r1);
}
rvd<int64_t,1> min(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_avx512_min_int64(r0, r1);
}
rvd<int32_t,1> min(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_avx512_min_int32(r0, r1);
}
rvd<int16_t,1> min(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_avx512_min_int16(r0, r1);
}
rvd<int8_t,1> min(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_avx512_min_int8(r0, r1);
}
rvd<float64_t,1> max(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_avx512_max_float64(r0, r1);
}
rvd<float32_t,1> max(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_avx512_max_float32(r0, r1);
}
rvd<int64_t,1> max(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_avx512_max_int64(r0, r1);
}
rvd<int32_t,1> max(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_avx512_max_int32(r0, r1);
}
rvd<int16_t,1> max(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_avx512_max_int16(r0, r1);
}
rvd<int8_t,1> max(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_avx512_max_int8(r0, r1);
}
rvd<float64_t,1> fmadd(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1, const rvd<float64_t,1> r2) {
	return mipp_avx512_fmadd_float64(r0, r1, r2);
}
rvd<float32_t,1> fmadd(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1, const rvd<float32_t,1> r2) {
	return mipp_avx512_fmadd_float32(r0, r1, r2);
}
rvd<int32_t,1> fmadd(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1, const rvd<int32_t,1> r2) {
	return mipp_avx512_fmadd_int32(r0, r1, r2);
}
rvd<float64_t,1> fmsub(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1, const rvd<float64_t,1> r2) {
	return mipp_avx512_fmsub_float64(r0, r1, r2);
}
rvd<float32_t,1> fmsub(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1, const rvd<float32_t,1> r2) {
	return mipp_avx512_fmsub_float32(r0, r1, r2);
}
rvd<int32_t,1> fmsub(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1, const rvd<int32_t,1> r2) {
	return mipp_avx512_fmsub_int32(r0, r1, r2);
}
rvd<float64_t,1> andb(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_avx512_andb_float64(r0, r1);
}
rvd<float32_t,1> andb(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_avx512_andb_float32(r0, r1);
}
rvd<int64_t,1> andb(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_avx512_andb_int64(r0, r1);
}
rvd<int32_t,1> andb(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_avx512_andb_int32(r0, r1);
}
rvd<int16_t,1> andb(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_avx512_andb_int16(r0, r1);
}
rvd<int8_t,1> andb(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_avx512_andb_int8(r0, r1);
}
rvd<uint64_t,1> andb(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_avx512_andb_uint64(r0, r1);
}
rvd<uint32_t,1> andb(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_avx512_andb_uint32(r0, r1);
}
rvd<uint16_t,1> andb(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_avx512_andb_uint16(r0, r1);
}
rvd<uint8_t,1> andb(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_avx512_andb_uint8(r0, r1);
}
rvm<float64_t,1> andb(const rvm<float64_t,1> m0, const rvm<float64_t,1> m1) {
	return mipp_avx512_andb_k_float64(m0, m1);
}
rvm<float32_t,1> andb(const rvm<float32_t,1> m0, const rvm<float32_t,1> m1) {
	return mipp_avx512_andb_k_float32(m0, m1);
}
rvm<int8_t,1> andb(const rvm<int8_t,1> m0, const rvm<int8_t,1> m1) {
	return mipp_avx512_andb_k_int8(m0, m1);
}
rvm<int16_t,1> andb(const rvm<int16_t,1> m0, const rvm<int16_t,1> m1) {
	return mipp_avx512_andb_k_int16(m0, m1);
}
rvd<float64_t,1> andnb(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_avx512_andnb_float64(r0, r1);
}
rvd<float32_t,1> andnb(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_avx512_andnb_float32(r0, r1);
}
rvd<int64_t,1> andnb(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_avx512_andnb_int64(r0, r1);
}
rvd<int32_t,1> andnb(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_avx512_andnb_int32(r0, r1);
}
rvd<int16_t,1> andnb(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_avx512_andnb_int16(r0, r1);
}
rvd<int8_t,1> andnb(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_avx512_andnb_int8(r0, r1);
}
rvd<uint64_t,1> andnb(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_avx512_andnb_uint64(r0, r1);
}
rvd<uint32_t,1> andnb(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_avx512_andnb_uint32(r0, r1);
}
rvd<uint16_t,1> andnb(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_avx512_andnb_uint16(r0, r1);
}
rvd<uint8_t,1> andnb(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_avx512_andnb_uint8(r0, r1);
}
rvm<float64_t,1> andnb(const rvm<float64_t,1> m0, const rvm<float64_t,1> m1) {
	return mipp_avx512_andnb_k_float64(m0, m1);
}
rvm<float32_t,1> andnb(const rvm<float32_t,1> m0, const rvm<float32_t,1> m1) {
	return mipp_avx512_andnb_k_float32(m0, m1);
}
rvm<int8_t,1> andnb(const rvm<int8_t,1> m0, const rvm<int8_t,1> m1) {
	return mipp_avx512_andnb_k_int8(m0, m1);
}
rvm<int16_t,1> andnb(const rvm<int16_t,1> m0, const rvm<int16_t,1> m1) {
	return mipp_avx512_andnb_k_int16(m0, m1);
}
rvd<float64_t,1> orb(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_avx512_orb_float64(r0, r1);
}
rvd<float32_t,1> orb(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_avx512_orb_float32(r0, r1);
}
rvd<int64_t,1> orb(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_avx512_orb_int64(r0, r1);
}
rvd<int32_t,1> orb(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_avx512_orb_int32(r0, r1);
}
rvd<int16_t,1> orb(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_avx512_orb_int16(r0, r1);
}
rvd<int8_t,1> orb(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_avx512_orb_int8(r0, r1);
}
rvd<uint64_t,1> orb(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_avx512_orb_uint64(r0, r1);
}
rvd<uint32_t,1> orb(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_avx512_orb_uint32(r0, r1);
}
rvd<uint16_t,1> orb(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_avx512_orb_uint16(r0, r1);
}
rvd<uint8_t,1> orb(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_avx512_orb_uint8(r0, r1);
}
rvm<float64_t,1> orb(const rvm<float64_t,1> m0, const rvm<float64_t,1> m1) {
	return mipp_avx512_orb_k_float64(m0, m1);
}
rvm<float32_t,1> orb(const rvm<float32_t,1> m0, const rvm<float32_t,1> m1) {
	return mipp_avx512_orb_k_float32(m0, m1);
}
rvm<int64_t,1> orb(const rvm<int64_t,1> m0, const rvm<int64_t,1> m1) {
	return mipp_avx512_orb_k_int64(m0, m1);
}
rvm<int32_t,1> orb(const rvm<int32_t,1> m0, const rvm<int32_t,1> m1) {
	return mipp_avx512_orb_k_int32(m0, m1);
}
rvm<int16_t,1> orb(const rvm<int16_t,1> m0, const rvm<int16_t,1> m1) {
	return mipp_avx512_orb_k_int16(m0, m1);
}
rvm<int8_t,1> orb(const rvm<int8_t,1> m0, const rvm<int8_t,1> m1) {
	return mipp_avx512_orb_k_int8(m0, m1);
}
rvm<uint64_t,1> orb(const rvm<uint64_t,1> m0, const rvm<uint64_t,1> m1) {
	return mipp_avx512_orb_k_uint64(m0, m1);
}
rvm<uint32_t,1> orb(const rvm<uint32_t,1> m0, const rvm<uint32_t,1> m1) {
	return mipp_avx512_orb_k_uint32(m0, m1);
}
rvm<uint16_t,1> orb(const rvm<uint16_t,1> m0, const rvm<uint16_t,1> m1) {
	return mipp_avx512_orb_k_uint16(m0, m1);
}
rvm<uint8_t,1> orb(const rvm<uint8_t,1> m0, const rvm<uint8_t,1> m1) {
	return mipp_avx512_orb_k_uint8(m0, m1);
}
rvd<float64_t,1> xorb(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_avx512_xorb_float64(r0, r1);
}
rvd<float32_t,1> xorb(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_avx512_xorb_float32(r0, r1);
}
rvd<int64_t,1> xorb(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_avx512_xorb_int64(r0, r1);
}
rvd<int32_t,1> xorb(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_avx512_xorb_int32(r0, r1);
}
rvd<int16_t,1> xorb(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_avx512_xorb_int16(r0, r1);
}
rvd<int8_t,1> xorb(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_avx512_xorb_int8(r0, r1);
}
rvd<uint64_t,1> xorb(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_avx512_xorb_uint64(r0, r1);
}
rvd<uint32_t,1> xorb(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_avx512_xorb_uint32(r0, r1);
}
rvd<uint16_t,1> xorb(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_avx512_xorb_uint16(r0, r1);
}
rvd<uint8_t,1> xorb(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_avx512_xorb_uint8(r0, r1);
}
rvm<float64_t,1> xorb(const rvm<float64_t,1> m0, const rvm<float64_t,1> m1) {
	return mipp_avx512_xorb_k_float64(m0, m1);
}
rvm<float32_t,1> xorb(const rvm<float32_t,1> m0, const rvm<float32_t,1> m1) {
	return mipp_avx512_xorb_k_float32(m0, m1);
}
rvm<int64_t,1> xorb(const rvm<int64_t,1> m0, const rvm<int64_t,1> m1) {
	return mipp_avx512_xorb_k_int64(m0, m1);
}
rvm<int32_t,1> xorb(const rvm<int32_t,1> m0, const rvm<int32_t,1> m1) {
	return mipp_avx512_xorb_k_int32(m0, m1);
}
rvm<int16_t,1> xorb(const rvm<int16_t,1> m0, const rvm<int16_t,1> m1) {
	return mipp_avx512_xorb_k_int16(m0, m1);
}
rvm<int8_t,1> xorb(const rvm<int8_t,1> m0, const rvm<int8_t,1> m1) {
	return mipp_avx512_xorb_k_int8(m0, m1);
}
rvm<uint64_t,1> xorb(const rvm<uint64_t,1> m0, const rvm<uint64_t,1> m1) {
	return mipp_avx512_xorb_k_uint64(m0, m1);
}
rvm<uint32_t,1> xorb(const rvm<uint32_t,1> m0, const rvm<uint32_t,1> m1) {
	return mipp_avx512_xorb_k_uint32(m0, m1);
}
rvm<uint16_t,1> xorb(const rvm<uint16_t,1> m0, const rvm<uint16_t,1> m1) {
	return mipp_avx512_xorb_k_uint16(m0, m1);
}
rvm<uint8_t,1> xorb(const rvm<uint8_t,1> m0, const rvm<uint8_t,1> m1) {
	return mipp_avx512_xorb_k_uint8(m0, m1);
}
rvd<float64_t,1> msb(const rvd<float64_t,1> r0) {
	return mipp_avx512_msb_float64(r0);
}
rvd<float32_t,1> msb(const rvd<float32_t,1> r0) {
	return mipp_avx512_msb_float32(r0);
}
rvd<int64_t,1> msb(const rvd<int64_t,1> r0) {
	return mipp_avx512_msb_int64(r0);
}
rvd<int32_t,1> msb(const rvd<int32_t,1> r0) {
	return mipp_avx512_msb_int32(r0);
}
rvd<int16_t,1> msb(const rvd<int16_t,1> r0) {
	return mipp_avx512_msb_int16(r0);
}
rvd<int8_t,1> msb(const rvd<int8_t,1> r0) {
	return mipp_avx512_msb_int8(r0);
}
rvd<uint64_t,1> msb(const rvd<uint64_t,1> r0) {
	return mipp_avx512_msb_uint64(r0);
}
rvd<uint32_t,1> msb(const rvd<uint32_t,1> r0) {
	return mipp_avx512_msb_uint32(r0);
}
rvd<uint16_t,1> msb(const rvd<uint16_t,1> r0) {
	return mipp_avx512_msb_uint16(r0);
}
rvd<uint8_t,1> msb(const rvd<uint8_t,1> r0) {
	return mipp_avx512_msb_uint8(r0);
}
rvd<float64_t,1> notb(const rvd<float64_t,1> r0) {
	return mipp_avx512_notb_float64(r0);
}
rvd<float32_t,1> notb(const rvd<float32_t,1> r0) {
	return mipp_avx512_notb_float32(r0);
}
rvd<int64_t,1> notb(const rvd<int64_t,1> r0) {
	return mipp_avx512_notb_int64(r0);
}
rvd<int32_t,1> notb(const rvd<int32_t,1> r0) {
	return mipp_avx512_notb_int32(r0);
}
rvd<int16_t,1> notb(const rvd<int16_t,1> r0) {
	return mipp_avx512_notb_int16(r0);
}
rvd<int8_t,1> notb(const rvd<int8_t,1> r0) {
	return mipp_avx512_notb_int8(r0);
}
rvd<uint64_t,1> notb(const rvd<uint64_t,1> r0) {
	return mipp_avx512_notb_uint64(r0);
}
rvd<uint32_t,1> notb(const rvd<uint32_t,1> r0) {
	return mipp_avx512_notb_uint32(r0);
}
rvd<uint16_t,1> notb(const rvd<uint16_t,1> r0) {
	return mipp_avx512_notb_uint16(r0);
}
rvd<uint8_t,1> notb(const rvd<uint8_t,1> r0) {
	return mipp_avx512_notb_uint8(r0);
}
rvm<float64_t,1> notb(const rvm<float64_t,1> m0) {
	return mipp_avx512_notb_k_float64(m0);
}
rvm<float32_t,1> notb(const rvm<float32_t,1> m0) {
	return mipp_avx512_notb_k_float32(m0);
}
rvm<int64_t,1> notb(const rvm<int64_t,1> m0) {
	return mipp_avx512_notb_k_int64(m0);
}
rvm<int32_t,1> notb(const rvm<int32_t,1> m0) {
	return mipp_avx512_notb_k_int32(m0);
}
rvm<int16_t,1> notb(const rvm<int16_t,1> m0) {
	return mipp_avx512_notb_k_int16(m0);
}
rvm<int8_t,1> notb(const rvm<int8_t,1> m0) {
	return mipp_avx512_notb_k_int8(m0);
}
rvm<uint64_t,1> notb(const rvm<uint64_t,1> m0) {
	return mipp_avx512_notb_k_uint64(m0);
}
rvm<uint32_t,1> notb(const rvm<uint32_t,1> m0) {
	return mipp_avx512_notb_k_uint32(m0);
}
rvm<uint16_t,1> notb(const rvm<uint16_t,1> m0) {
	return mipp_avx512_notb_k_uint16(m0);
}
rvm<uint8_t,1> notb(const rvm<uint8_t,1> m0) {
	return mipp_avx512_notb_k_uint8(m0);
}
rvm<float64_t,1> cmpeq(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_avx512_cmpeq_float64(r0, r1);
}
rvm<float32_t,1> cmpeq(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_avx512_cmpeq_float32(r0, r1);
}
rvm<int64_t,1> cmpeq(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_avx512_cmpeq_int64(r0, r1);
}
rvm<int32_t,1> cmpeq(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_avx512_cmpeq_int32(r0, r1);
}
rvm<int16_t,1> cmpeq(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_avx512_cmpeq_int16(r0, r1);
}
rvm<int8_t,1> cmpeq(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_avx512_cmpeq_int8(r0, r1);
}
rvm<uint64_t,1> cmpeq(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_avx512_cmpeq_uint64(r0, r1);
}
rvm<uint32_t,1> cmpeq(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_avx512_cmpeq_uint32(r0, r1);
}
rvm<uint16_t,1> cmpeq(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_avx512_cmpeq_uint16(r0, r1);
}
rvm<uint8_t,1> cmpeq(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_avx512_cmpeq_uint8(r0, r1);
}
rvm<float64_t,1> cmpneq(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_avx512_cmpneq_float64(r0, r1);
}
rvm<float32_t,1> cmpneq(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_avx512_cmpneq_float32(r0, r1);
}
rvm<int64_t,1> cmpneq(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_avx512_cmpneq_int64(r0, r1);
}
rvm<int32_t,1> cmpneq(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_avx512_cmpneq_int32(r0, r1);
}
rvm<int16_t,1> cmpneq(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_avx512_cmpneq_int16(r0, r1);
}
rvm<int8_t,1> cmpneq(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_avx512_cmpneq_int8(r0, r1);
}
rvm<uint64_t,1> cmpneq(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_avx512_cmpneq_uint64(r0, r1);
}
rvm<uint32_t,1> cmpneq(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_avx512_cmpneq_uint32(r0, r1);
}
rvm<uint16_t,1> cmpneq(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_avx512_cmpneq_uint16(r0, r1);
}
rvm<uint8_t,1> cmpneq(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_avx512_cmpneq_uint8(r0, r1);
}
rvm<float64_t,1> cmplt(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_avx512_cmplt_float64(r0, r1);
}
rvm<float32_t,1> cmplt(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_avx512_cmplt_float32(r0, r1);
}
rvm<int64_t,1> cmplt(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_avx512_cmplt_int64(r0, r1);
}
rvm<int32_t,1> cmplt(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_avx512_cmplt_int32(r0, r1);
}
rvm<int16_t,1> cmplt(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_avx512_cmplt_int16(r0, r1);
}
rvm<int8_t,1> cmplt(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_avx512_cmplt_int8(r0, r1);
}
rvm<uint64_t,1> cmplt(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_avx512_cmplt_uint64(r0, r1);
}
rvm<uint32_t,1> cmplt(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_avx512_cmplt_uint32(r0, r1);
}
rvm<uint16_t,1> cmplt(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_avx512_cmplt_uint16(r0, r1);
}
rvm<uint8_t,1> cmplt(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_avx512_cmplt_uint8(r0, r1);
}
rvm<float64_t,1> cmple(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_avx512_cmple_float64(r0, r1);
}
rvm<float32_t,1> cmple(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_avx512_cmple_float32(r0, r1);
}
rvm<int64_t,1> cmple(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_avx512_cmple_int64(r0, r1);
}
rvm<int32_t,1> cmple(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_avx512_cmple_int32(r0, r1);
}
rvm<int16_t,1> cmple(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_avx512_cmple_int16(r0, r1);
}
rvm<int8_t,1> cmple(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_avx512_cmple_int8(r0, r1);
}
rvm<uint64_t,1> cmple(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_avx512_cmple_uint64(r0, r1);
}
rvm<uint32_t,1> cmple(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_avx512_cmple_uint32(r0, r1);
}
rvm<uint16_t,1> cmple(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_avx512_cmple_uint16(r0, r1);
}
rvm<uint8_t,1> cmple(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_avx512_cmple_uint8(r0, r1);
}
rvm<float64_t,1> cmpge(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_avx512_cmpge_float64(r0, r1);
}
rvm<float32_t,1> cmpge(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_avx512_cmpge_float32(r0, r1);
}
rvm<int64_t,1> cmpge(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_avx512_cmpge_int64(r0, r1);
}
rvm<int32_t,1> cmpge(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_avx512_cmpge_int32(r0, r1);
}
rvm<int16_t,1> cmpge(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_avx512_cmpge_int16(r0, r1);
}
rvm<int8_t,1> cmpge(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_avx512_cmpge_int8(r0, r1);
}
rvm<uint64_t,1> cmpge(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_avx512_cmpge_uint64(r0, r1);
}
rvm<uint32_t,1> cmpge(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_avx512_cmpge_uint32(r0, r1);
}
rvm<uint16_t,1> cmpge(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_avx512_cmpge_uint16(r0, r1);
}
rvm<uint8_t,1> cmpge(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_avx512_cmpge_uint8(r0, r1);
}
rvm<float64_t,1> cmpgt(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_avx512_cmpgt_float64(r0, r1);
}
rvm<float32_t,1> cmpgt(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_avx512_cmpgt_float32(r0, r1);
}
rvm<int64_t,1> cmpgt(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_avx512_cmpgt_int64(r0, r1);
}
rvm<int32_t,1> cmpgt(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_avx512_cmpgt_int32(r0, r1);
}
rvm<int16_t,1> cmpgt(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_avx512_cmpgt_int16(r0, r1);
}
rvm<int8_t,1> cmpgt(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_avx512_cmpgt_int8(r0, r1);
}
rvm<uint64_t,1> cmpgt(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_avx512_cmpgt_uint64(r0, r1);
}
rvm<uint32_t,1> cmpgt(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_avx512_cmpgt_uint32(r0, r1);
}
rvm<uint16_t,1> cmpgt(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_avx512_cmpgt_uint16(r0, r1);
}
rvm<uint8_t,1> cmpgt(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_avx512_cmpgt_uint8(r0, r1);
}
float64_t round(const rvd<float64_t,1> r0) {
	return mipp_avx512_round_float64(r0);
}
float32_t round(const rvd<float32_t,1> r0) {
	return mipp_avx512_round_float32(r0);
}
rvd<float64_t,1> blend(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1, const rvm<float64_t,1> m0) {
	return mipp_avx512_blend_float64(r0, r1, m0);
}
rvd<float32_t,1> blend(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1, const rvm<float32_t,1> m0) {
	return mipp_avx512_blend_float32(r0, r1, m0);
}
rvd<int64_t,1> blend(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1, const rvm<int64_t,1> m0) {
	return mipp_avx512_blend_int64(r0, r1, m0);
}
rvd<int32_t,1> blend(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1, const rvm<int32_t,1> m0) {
	return mipp_avx512_blend_int32(r0, r1, m0);
}
rvd<int16_t,1> blend(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1, const rvm<int16_t,1> m0) {
	return mipp_avx512_blend_int16(r0, r1, m0);
}
rvd<int8_t,1> blend(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1, const rvm<int8_t,1> m0) {
	return mipp_avx512_blend_int8(r0, r1, m0);
}
rvd<uint64_t,1> blend(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1, const rvm<uint64_t,1> m0) {
	return mipp_avx512_blend_uint64(r0, r1, m0);
}
rvd<uint32_t,1> blend(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1, const rvm<uint32_t,1> m0) {
	return mipp_avx512_blend_uint32(r0, r1, m0);
}
rvd<uint16_t,1> blend(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1, const rvm<uint16_t,1> m0) {
	return mipp_avx512_blend_uint16(r0, r1, m0);
}
rvd<uint8_t,1> blend(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1, const rvm<uint8_t,1> m0) {
	return mipp_avx512_blend_uint8(r0, r1, m0);
}
int32_t testz(const rvd<int64_t,1> r0) {
	return mipp_avx512_testz_int64(r0);
}
int32_t testz(const rvd<int32_t,1> r0) {
	return mipp_avx512_testz_int32(r0);
}
int32_t testz(const rvd<int16_t,1> r0) {
	return mipp_avx512_testz_int16(r0);
}
int32_t testz(const rvd<int8_t,1> r0) {
	return mipp_avx512_testz_int8(r0);
}
int32_t testz(const rvd<uint64_t,1> r0) {
	return mipp_avx512_testz_uint64(r0);
}
int32_t testz(const rvd<uint32_t,1> r0) {
	return mipp_avx512_testz_uint32(r0);
}
int32_t testz(const rvd<uint16_t,1> r0) {
	return mipp_avx512_testz_uint16(r0);
}
int32_t testz(const rvd<uint8_t,1> r0) {
	return mipp_avx512_testz_uint8(r0);
}
int32_t testz_2(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_avx512_testz_2_int64(r0, r1);
}
int32_t testz_2(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_avx512_testz_2_int32(r0, r1);
}
int32_t testz_2(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_avx512_testz_2_int16(r0, r1);
}
int32_t testz_2(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_avx512_testz_2_int8(r0, r1);
}
int32_t testz_2(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_avx512_testz_2_uint64(r0, r1);
}
int32_t testz_2(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_avx512_testz_2_uint32(r0, r1);
}
int32_t testz_2(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_avx512_testz_2_uint16(r0, r1);
}
int32_t testz_2(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_avx512_testz_2_uint8(r0, r1);
}
rvd<float64_t,1> hadd(const rvd<float64_t,1> r0) {
	return mipp_avx512_hadd_float64(r0);
}
rvd<float32_t,1> hadd(const rvd<float32_t,1> r0) {
	return mipp_avx512_hadd_float32(r0);
}
rvd<int64_t,1> hadd(const rvd<int64_t,1> r0) {
	return mipp_avx512_hadd_int64(r0);
}
rvd<int32_t,1> hadd(const rvd<int32_t,1> r0) {
	return mipp_avx512_hadd_int32(r0);
}
rvd<int16_t,1> hadd(const rvd<int16_t,1> r0) {
	return mipp_avx512_hadd_int16(r0);
}
rvd<int8_t,1> hadd(const rvd<int8_t,1> r0) {
	return mipp_avx512_hadd_int8(r0);
}
rvd<uint64_t,1> hadd(const rvd<uint64_t,1> r0) {
	return mipp_avx512_hadd_uint64(r0);
}
rvd<uint32_t,1> hadd(const rvd<uint32_t,1> r0) {
	return mipp_avx512_hadd_uint32(r0);
}
rvd<uint16_t,1> hadd(const rvd<uint16_t,1> r0) {
	return mipp_avx512_hadd_uint16(r0);
}
rvd<uint8_t,1> hadd(const rvd<uint8_t,1> r0) {
	return mipp_avx512_hadd_uint8(r0);
}
rvd<float64_t,1> hmul(const rvd<float64_t,1> r0) {
	return mipp_avx512_hmul_float64(r0);
}
rvd<float32_t,1> hmul(const rvd<float32_t,1> r0) {
	return mipp_avx512_hmul_float32(r0);
}
rvd<int32_t,1> hmul(const rvd<int32_t,1> r0) {
	return mipp_avx512_hmul_int32(r0);
}
rvd<int16_t,1> hmul(const rvd<int16_t,1> r0) {
	return mipp_avx512_hmul_int16(r0);
}
rvd<float64_t,1> hmin(const rvd<float64_t,1> r0) {
	return mipp_avx512_hmin_float64(r0);
}
rvd<float32_t,1> hmin(const rvd<float32_t,1> r0) {
	return mipp_avx512_hmin_float32(r0);
}
rvd<int64_t,1> hmin(const rvd<int64_t,1> r0) {
	return mipp_avx512_hmin_int64(r0);
}
rvd<int32_t,1> hmin(const rvd<int32_t,1> r0) {
	return mipp_avx512_hmin_int32(r0);
}
rvd<int16_t,1> hmin(const rvd<int16_t,1> r0) {
	return mipp_avx512_hmin_int16(r0);
}
rvd<int8_t,1> hmin(const rvd<int8_t,1> r0) {
	return mipp_avx512_hmin_int8(r0);
}
rvd<uint64_t,1> hmin(const rvd<uint64_t,1> r0) {
	return mipp_avx512_hmin_uint64(r0);
}
rvd<uint32_t,1> hmin(const rvd<uint32_t,1> r0) {
	return mipp_avx512_hmin_uint32(r0);
}
rvd<uint16_t,1> hmin(const rvd<uint16_t,1> r0) {
	return mipp_avx512_hmin_uint16(r0);
}
rvd<uint8_t,1> hmin(const rvd<uint8_t,1> r0) {
	return mipp_avx512_hmin_uint8(r0);
}
rvd<float64_t,1> hmax(const rvd<float64_t,1> r0) {
	return mipp_avx512_hmax_float64(r0);
}
rvd<float32_t,1> hmax(const rvd<float32_t,1> r0) {
	return mipp_avx512_hmax_float32(r0);
}
rvd<int64_t,1> hmax(const rvd<int64_t,1> r0) {
	return mipp_avx512_hmax_int64(r0);
}
rvd<int32_t,1> hmax(const rvd<int32_t,1> r0) {
	return mipp_avx512_hmax_int32(r0);
}
rvd<int16_t,1> hmax(const rvd<int16_t,1> r0) {
	return mipp_avx512_hmax_int16(r0);
}
rvd<int8_t,1> hmax(const rvd<int8_t,1> r0) {
	return mipp_avx512_hmax_int8(r0);
}
rvd<uint64_t,1> hmax(const rvd<uint64_t,1> r0) {
	return mipp_avx512_hmax_uint64(r0);
}
rvd<uint32_t,1> hmax(const rvd<uint32_t,1> r0) {
	return mipp_avx512_hmax_uint32(r0);
}
rvd<uint16_t,1> hmax(const rvd<uint16_t,1> r0) {
	return mipp_avx512_hmax_uint16(r0);
}
rvd<uint8_t,1> hmax(const rvd<uint8_t,1> r0) {
	return mipp_avx512_hmax_uint8(r0);
}
}

	#endif /* MY_INTRINSICS_PLUS_PLUS_HPP_ */
