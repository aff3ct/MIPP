#ifndef MY_INTRINSICS_PLUS_PLUS_HPP_
#define MY_INTRINSICS_PLUS_PLUS_HPP_

namespace mipp

{
// should throw an exception
template<typename T, int LMUL=1> struct rvd_type{};
template<> struct rvd_type<float64_t, 1>{ using type = rvd_avx_float64_t; };
template<> struct rvd_type<float32_t, 1>{ using type = rvd_avx_float32_t; };
template<> struct rvd_type<int64_t, 1>{ using type = rvd_avx_int64_t; };
template<> struct rvd_type<int32_t, 1>{ using type = rvd_avx_int32_t; };
template<> struct rvd_type<int16_t, 1>{ using type = rvd_avx_int16_t; };
template<> struct rvd_type<int8_t, 1>{ using type = rvd_avx_int8_t; };
template<> struct rvd_type<uint64_t, 1>{ using type = rvd_avx_uint64_t; };
template<> struct rvd_type<uint32_t, 1>{ using type = rvd_avx_uint32_t; };
template<> struct rvd_type<uint16_t, 1>{ using type = rvd_avx_uint16_t; };
template<> struct rvd_type<uint8_t, 1>{ using type = rvd_avx_uint8_t; };
template <typename T, int LMUL=1> using rvd = typename rvd_type<T,LMUL>::type;
// should throw an exception
template<typename T, int LMUL=1> struct rvm_type{};
template<> struct rvm_type<float64_t, 1>{ using type = rvd_avx_float64_t; };
template<> struct rvm_type<float32_t, 1>{ using type = rvd_avx_float32_t; };
template<> struct rvm_type<int64_t, 1>{ using type = rvd_avx_int64_t; };
template<> struct rvm_type<int32_t, 1>{ using type = rvd_avx_int32_t; };
template<> struct rvm_type<int16_t, 1>{ using type = rvd_avx_int16_t; };
template<> struct rvm_type<int8_t, 1>{ using type = rvd_avx_int8_t; };
template<> struct rvm_type<uint64_t, 1>{ using type = rvd_avx_uint64_t; };
template<> struct rvm_type<uint32_t, 1>{ using type = rvd_avx_uint32_t; };
template<> struct rvm_type<uint16_t, 1>{ using type = rvd_avx_uint16_t; };
template<> struct rvm_type<uint8_t, 1>{ using type = rvd_avx_uint8_t; };
template <typename T, int LMUL=1> using rvm = typename rvm_type<T,LMUL>::type;
// should throw an exception
template<typename T, int LMUL=1> constexpr uint32_t N(){ return 0; }
template<> constexpr uint32_t N<float64_t, 1>(){ return MIPP_AVX_N_FLOAT64; }
template<> constexpr uint32_t N<float32_t, 1>(){ return MIPP_AVX_N_FLOAT32; }
template<> constexpr uint32_t N<int64_t, 1>(){ return MIPP_AVX_N_INT64; }
template<> constexpr uint32_t N<int32_t, 1>(){ return MIPP_AVX_N_INT32; }
template<> constexpr uint32_t N<int16_t, 1>(){ return MIPP_AVX_N_INT16; }
template<> constexpr uint32_t N<int8_t, 1>(){ return MIPP_AVX_N_INT8; }
template<> constexpr uint32_t N<uint64_t, 1>(){ return MIPP_AVX_N_UINT64; }
template<> constexpr uint32_t N<uint32_t, 1>(){ return MIPP_AVX_N_UINT32; }
template<> constexpr uint32_t N<uint16_t, 1>(){ return MIPP_AVX_N_UINT16; }
template<> constexpr uint32_t N<uint8_t, 1>(){ return MIPP_AVX_N_UINT8; }
rvd<float64_t,1> cast_float64_float64(const rvd<float64_t,1> r0) {
	return mipp_avx_cast_float64_float64(r0);
}
rvd<float64_t,1> cast_float32_float64(const rvd<float32_t,1> r0) {
	return mipp_avx_cast_float32_float64(r0);
}
rvd<float64_t,1> cast_int64_float64(const rvd<int64_t,1> r0) {
	return mipp_avx_cast_int64_float64(r0);
}
rvd<float64_t,1> cast_int32_float64(const rvd<int32_t,1> r0) {
	return mipp_avx_cast_int32_float64(r0);
}
rvd<float64_t,1> cast_int16_float64(const rvd<int16_t,1> r0) {
	return mipp_avx_cast_int16_float64(r0);
}
rvd<float64_t,1> cast_int8_float64(const rvd<int8_t,1> r0) {
	return mipp_avx_cast_int8_float64(r0);
}
rvd<float64_t,1> cast_uint64_float64(const rvd<uint64_t,1> r0) {
	return mipp_avx_cast_uint64_float64(r0);
}
rvd<float64_t,1> cast_uint32_float64(const rvd<uint32_t,1> r0) {
	return mipp_avx_cast_uint32_float64(r0);
}
rvd<float64_t,1> cast_uint16_float64(const rvd<uint16_t,1> r0) {
	return mipp_avx_cast_uint16_float64(r0);
}
rvd<float64_t,1> cast_uint8_float64(const rvd<uint8_t,1> r0) {
	return mipp_avx_cast_uint8_float64(r0);
}
rvd<float32_t,1> cast_float64_float32(const rvd<float64_t,1> r0) {
	return mipp_avx_cast_float64_float32(r0);
}
rvd<float32_t,1> cast_float32_float32(const rvd<float32_t,1> r0) {
	return mipp_avx_cast_float32_float32(r0);
}
rvd<float32_t,1> cast_int64_float32(const rvd<int64_t,1> r0) {
	return mipp_avx_cast_int64_float32(r0);
}
rvd<float32_t,1> cast_int32_float32(const rvd<int32_t,1> r0) {
	return mipp_avx_cast_int32_float32(r0);
}
rvd<float32_t,1> cast_int16_float32(const rvd<int16_t,1> r0) {
	return mipp_avx_cast_int16_float32(r0);
}
rvd<float32_t,1> cast_int8_float32(const rvd<int8_t,1> r0) {
	return mipp_avx_cast_int8_float32(r0);
}
rvd<float32_t,1> cast_uint64_float32(const rvd<uint64_t,1> r0) {
	return mipp_avx_cast_uint64_float32(r0);
}
rvd<float32_t,1> cast_uint32_float32(const rvd<uint32_t,1> r0) {
	return mipp_avx_cast_uint32_float32(r0);
}
rvd<float32_t,1> cast_uint16_float32(const rvd<uint16_t,1> r0) {
	return mipp_avx_cast_uint16_float32(r0);
}
rvd<float32_t,1> cast_uint8_float32(const rvd<uint8_t,1> r0) {
	return mipp_avx_cast_uint8_float32(r0);
}
rvd<int64_t,1> cast_float64_int64(const rvd<float64_t,1> r0) {
	return mipp_avx_cast_float64_int64(r0);
}
rvd<int64_t,1> cast_float32_int64(const rvd<float32_t,1> r0) {
	return mipp_avx_cast_float32_int64(r0);
}
rvd<int64_t,1> cast_int64_int64(const rvd<int64_t,1> r0) {
	return mipp_avx_cast_int64_int64(r0);
}
rvd<int64_t,1> cast_int32_int64(const rvd<int32_t,1> r0) {
	return mipp_avx_cast_int32_int64(r0);
}
rvd<int64_t,1> cast_int16_int64(const rvd<int16_t,1> r0) {
	return mipp_avx_cast_int16_int64(r0);
}
rvd<int64_t,1> cast_int8_int64(const rvd<int8_t,1> r0) {
	return mipp_avx_cast_int8_int64(r0);
}
rvd<int64_t,1> cast_uint64_int64(const rvd<uint64_t,1> r0) {
	return mipp_avx_cast_uint64_int64(r0);
}
rvd<int64_t,1> cast_uint32_int64(const rvd<uint32_t,1> r0) {
	return mipp_avx_cast_uint32_int64(r0);
}
rvd<int64_t,1> cast_uint16_int64(const rvd<uint16_t,1> r0) {
	return mipp_avx_cast_uint16_int64(r0);
}
rvd<int64_t,1> cast_uint8_int64(const rvd<uint8_t,1> r0) {
	return mipp_avx_cast_uint8_int64(r0);
}
rvd<int32_t,1> cast_float64_int32(const rvd<float64_t,1> r0) {
	return mipp_avx_cast_float64_int32(r0);
}
rvd<int32_t,1> cast_float32_int32(const rvd<float32_t,1> r0) {
	return mipp_avx_cast_float32_int32(r0);
}
rvd<int32_t,1> cast_int64_int32(const rvd<int64_t,1> r0) {
	return mipp_avx_cast_int64_int32(r0);
}
rvd<int32_t,1> cast_int32_int32(const rvd<int32_t,1> r0) {
	return mipp_avx_cast_int32_int32(r0);
}
rvd<int32_t,1> cast_int16_int32(const rvd<int16_t,1> r0) {
	return mipp_avx_cast_int16_int32(r0);
}
rvd<int32_t,1> cast_int8_int32(const rvd<int8_t,1> r0) {
	return mipp_avx_cast_int8_int32(r0);
}
rvd<int32_t,1> cast_uint64_int32(const rvd<uint64_t,1> r0) {
	return mipp_avx_cast_uint64_int32(r0);
}
rvd<int32_t,1> cast_uint32_int32(const rvd<uint32_t,1> r0) {
	return mipp_avx_cast_uint32_int32(r0);
}
rvd<int32_t,1> cast_uint16_int32(const rvd<uint16_t,1> r0) {
	return mipp_avx_cast_uint16_int32(r0);
}
rvd<int32_t,1> cast_uint8_int32(const rvd<uint8_t,1> r0) {
	return mipp_avx_cast_uint8_int32(r0);
}
rvd<int16_t,1> cast_float64_int16(const rvd<float64_t,1> r0) {
	return mipp_avx_cast_float64_int16(r0);
}
rvd<int16_t,1> cast_float32_int16(const rvd<float32_t,1> r0) {
	return mipp_avx_cast_float32_int16(r0);
}
rvd<int16_t,1> cast_int64_int16(const rvd<int64_t,1> r0) {
	return mipp_avx_cast_int64_int16(r0);
}
rvd<int16_t,1> cast_int32_int16(const rvd<int32_t,1> r0) {
	return mipp_avx_cast_int32_int16(r0);
}
rvd<int16_t,1> cast_int16_int16(const rvd<int16_t,1> r0) {
	return mipp_avx_cast_int16_int16(r0);
}
rvd<int16_t,1> cast_int8_int16(const rvd<int8_t,1> r0) {
	return mipp_avx_cast_int8_int16(r0);
}
rvd<int16_t,1> cast_uint64_int16(const rvd<uint64_t,1> r0) {
	return mipp_avx_cast_uint64_int16(r0);
}
rvd<int16_t,1> cast_uint32_int16(const rvd<uint32_t,1> r0) {
	return mipp_avx_cast_uint32_int16(r0);
}
rvd<int16_t,1> cast_uint16_int16(const rvd<uint16_t,1> r0) {
	return mipp_avx_cast_uint16_int16(r0);
}
rvd<int16_t,1> cast_uint8_int16(const rvd<uint8_t,1> r0) {
	return mipp_avx_cast_uint8_int16(r0);
}
rvd<int8_t,1> cast_float64_int8(const rvd<float64_t,1> r0) {
	return mipp_avx_cast_float64_int8(r0);
}
rvd<int8_t,1> cast_float32_int8(const rvd<float32_t,1> r0) {
	return mipp_avx_cast_float32_int8(r0);
}
rvd<int8_t,1> cast_int64_int8(const rvd<int64_t,1> r0) {
	return mipp_avx_cast_int64_int8(r0);
}
rvd<int8_t,1> cast_int32_int8(const rvd<int32_t,1> r0) {
	return mipp_avx_cast_int32_int8(r0);
}
rvd<int8_t,1> cast_int16_int8(const rvd<int16_t,1> r0) {
	return mipp_avx_cast_int16_int8(r0);
}
rvd<int8_t,1> cast_int8_int8(const rvd<int8_t,1> r0) {
	return mipp_avx_cast_int8_int8(r0);
}
rvd<int8_t,1> cast_uint64_int8(const rvd<uint64_t,1> r0) {
	return mipp_avx_cast_uint64_int8(r0);
}
rvd<int8_t,1> cast_uint32_int8(const rvd<uint32_t,1> r0) {
	return mipp_avx_cast_uint32_int8(r0);
}
rvd<int8_t,1> cast_uint16_int8(const rvd<uint16_t,1> r0) {
	return mipp_avx_cast_uint16_int8(r0);
}
rvd<int8_t,1> cast_uint8_int8(const rvd<uint8_t,1> r0) {
	return mipp_avx_cast_uint8_int8(r0);
}
rvd<uint64_t,1> cast_float64_uint64(const rvd<float64_t,1> r0) {
	return mipp_avx_cast_float64_uint64(r0);
}
rvd<uint64_t,1> cast_float32_uint64(const rvd<float32_t,1> r0) {
	return mipp_avx_cast_float32_uint64(r0);
}
rvd<uint64_t,1> cast_int64_uint64(const rvd<int64_t,1> r0) {
	return mipp_avx_cast_int64_uint64(r0);
}
rvd<uint64_t,1> cast_int32_uint64(const rvd<int32_t,1> r0) {
	return mipp_avx_cast_int32_uint64(r0);
}
rvd<uint64_t,1> cast_int16_uint64(const rvd<int16_t,1> r0) {
	return mipp_avx_cast_int16_uint64(r0);
}
rvd<uint64_t,1> cast_int8_uint64(const rvd<int8_t,1> r0) {
	return mipp_avx_cast_int8_uint64(r0);
}
rvd<uint64_t,1> cast_uint64_uint64(const rvd<uint64_t,1> r0) {
	return mipp_avx_cast_uint64_uint64(r0);
}
rvd<uint64_t,1> cast_uint32_uint64(const rvd<uint32_t,1> r0) {
	return mipp_avx_cast_uint32_uint64(r0);
}
rvd<uint64_t,1> cast_uint16_uint64(const rvd<uint16_t,1> r0) {
	return mipp_avx_cast_uint16_uint64(r0);
}
rvd<uint64_t,1> cast_uint8_uint64(const rvd<uint8_t,1> r0) {
	return mipp_avx_cast_uint8_uint64(r0);
}
rvd<uint32_t,1> cast_float64_uint32(const rvd<float64_t,1> r0) {
	return mipp_avx_cast_float64_uint32(r0);
}
rvd<uint32_t,1> cast_float32_uint32(const rvd<float32_t,1> r0) {
	return mipp_avx_cast_float32_uint32(r0);
}
rvd<uint32_t,1> cast_int64_uint32(const rvd<int64_t,1> r0) {
	return mipp_avx_cast_int64_uint32(r0);
}
rvd<uint32_t,1> cast_int32_uint32(const rvd<int32_t,1> r0) {
	return mipp_avx_cast_int32_uint32(r0);
}
rvd<uint32_t,1> cast_int16_uint32(const rvd<int16_t,1> r0) {
	return mipp_avx_cast_int16_uint32(r0);
}
rvd<uint32_t,1> cast_int8_uint32(const rvd<int8_t,1> r0) {
	return mipp_avx_cast_int8_uint32(r0);
}
rvd<uint32_t,1> cast_uint64_uint32(const rvd<uint64_t,1> r0) {
	return mipp_avx_cast_uint64_uint32(r0);
}
rvd<uint32_t,1> cast_uint32_uint32(const rvd<uint32_t,1> r0) {
	return mipp_avx_cast_uint32_uint32(r0);
}
rvd<uint32_t,1> cast_uint16_uint32(const rvd<uint16_t,1> r0) {
	return mipp_avx_cast_uint16_uint32(r0);
}
rvd<uint32_t,1> cast_uint8_uint32(const rvd<uint8_t,1> r0) {
	return mipp_avx_cast_uint8_uint32(r0);
}
rvd<uint16_t,1> cast_float64_uint16(const rvd<float64_t,1> r0) {
	return mipp_avx_cast_float64_uint16(r0);
}
rvd<uint16_t,1> cast_float32_uint16(const rvd<float32_t,1> r0) {
	return mipp_avx_cast_float32_uint16(r0);
}
rvd<uint16_t,1> cast_int64_uint16(const rvd<int64_t,1> r0) {
	return mipp_avx_cast_int64_uint16(r0);
}
rvd<uint16_t,1> cast_int32_uint16(const rvd<int32_t,1> r0) {
	return mipp_avx_cast_int32_uint16(r0);
}
rvd<uint16_t,1> cast_int16_uint16(const rvd<int16_t,1> r0) {
	return mipp_avx_cast_int16_uint16(r0);
}
rvd<uint16_t,1> cast_int8_uint16(const rvd<int8_t,1> r0) {
	return mipp_avx_cast_int8_uint16(r0);
}
rvd<uint16_t,1> cast_uint64_uint16(const rvd<uint64_t,1> r0) {
	return mipp_avx_cast_uint64_uint16(r0);
}
rvd<uint16_t,1> cast_uint32_uint16(const rvd<uint32_t,1> r0) {
	return mipp_avx_cast_uint32_uint16(r0);
}
rvd<uint16_t,1> cast_uint16_uint16(const rvd<uint16_t,1> r0) {
	return mipp_avx_cast_uint16_uint16(r0);
}
rvd<uint16_t,1> cast_uint8_uint16(const rvd<uint8_t,1> r0) {
	return mipp_avx_cast_uint8_uint16(r0);
}
rvd<uint8_t,1> cast_float64_uint8(const rvd<float64_t,1> r0) {
	return mipp_avx_cast_float64_uint8(r0);
}
rvd<uint8_t,1> cast_float32_uint8(const rvd<float32_t,1> r0) {
	return mipp_avx_cast_float32_uint8(r0);
}
rvd<uint8_t,1> cast_int64_uint8(const rvd<int64_t,1> r0) {
	return mipp_avx_cast_int64_uint8(r0);
}
rvd<uint8_t,1> cast_int32_uint8(const rvd<int32_t,1> r0) {
	return mipp_avx_cast_int32_uint8(r0);
}
rvd<uint8_t,1> cast_int16_uint8(const rvd<int16_t,1> r0) {
	return mipp_avx_cast_int16_uint8(r0);
}
rvd<uint8_t,1> cast_int8_uint8(const rvd<int8_t,1> r0) {
	return mipp_avx_cast_int8_uint8(r0);
}
rvd<uint8_t,1> cast_uint64_uint8(const rvd<uint64_t,1> r0) {
	return mipp_avx_cast_uint64_uint8(r0);
}
rvd<uint8_t,1> cast_uint32_uint8(const rvd<uint32_t,1> r0) {
	return mipp_avx_cast_uint32_uint8(r0);
}
rvd<uint8_t,1> cast_uint16_uint8(const rvd<uint16_t,1> r0) {
	return mipp_avx_cast_uint16_uint8(r0);
}
rvd<uint8_t,1> cast_uint8_uint8(const rvd<uint8_t,1> r0) {
	return mipp_avx_cast_uint8_uint8(r0);
}
rvm<float64_t,1> cast_k_float64_float64(const rvm<float64_t,1> m0) {
	return mipp_avx_cast_k_float64_float64(m0);
}
rvm<float64_t,1> cast_k_float32_float64(const rvm<float32_t,1> m0) {
	return mipp_avx_cast_k_float32_float64(m0);
}
rvm<float64_t,1> cast_k_int64_float64(const rvm<int64_t,1> m0) {
	return mipp_avx_cast_k_int64_float64(m0);
}
rvm<float64_t,1> cast_k_int32_float64(const rvm<int32_t,1> m0) {
	return mipp_avx_cast_k_int32_float64(m0);
}
rvm<float64_t,1> cast_k_int16_float64(const rvm<int16_t,1> m0) {
	return mipp_avx_cast_k_int16_float64(m0);
}
rvm<float64_t,1> cast_k_int8_float64(const rvm<int8_t,1> m0) {
	return mipp_avx_cast_k_int8_float64(m0);
}
rvm<float64_t,1> cast_k_uint64_float64(const rvm<uint64_t,1> m0) {
	return mipp_avx_cast_k_uint64_float64(m0);
}
rvm<float64_t,1> cast_k_uint32_float64(const rvm<uint32_t,1> m0) {
	return mipp_avx_cast_k_uint32_float64(m0);
}
rvm<float64_t,1> cast_k_uint16_float64(const rvm<uint16_t,1> m0) {
	return mipp_avx_cast_k_uint16_float64(m0);
}
rvm<float64_t,1> cast_k_uint8_float64(const rvm<uint8_t,1> m0) {
	return mipp_avx_cast_k_uint8_float64(m0);
}
rvm<float32_t,1> cast_k_float64_float32(const rvm<float64_t,1> m0) {
	return mipp_avx_cast_k_float64_float32(m0);
}
rvm<float32_t,1> cast_k_float32_float32(const rvm<float32_t,1> m0) {
	return mipp_avx_cast_k_float32_float32(m0);
}
rvm<float32_t,1> cast_k_int64_float32(const rvm<int64_t,1> m0) {
	return mipp_avx_cast_k_int64_float32(m0);
}
rvm<float32_t,1> cast_k_int32_float32(const rvm<int32_t,1> m0) {
	return mipp_avx_cast_k_int32_float32(m0);
}
rvm<float32_t,1> cast_k_int16_float32(const rvm<int16_t,1> m0) {
	return mipp_avx_cast_k_int16_float32(m0);
}
rvm<float32_t,1> cast_k_int8_float32(const rvm<int8_t,1> m0) {
	return mipp_avx_cast_k_int8_float32(m0);
}
rvm<float32_t,1> cast_k_uint64_float32(const rvm<uint64_t,1> m0) {
	return mipp_avx_cast_k_uint64_float32(m0);
}
rvm<float32_t,1> cast_k_uint32_float32(const rvm<uint32_t,1> m0) {
	return mipp_avx_cast_k_uint32_float32(m0);
}
rvm<float32_t,1> cast_k_uint16_float32(const rvm<uint16_t,1> m0) {
	return mipp_avx_cast_k_uint16_float32(m0);
}
rvm<float32_t,1> cast_k_uint8_float32(const rvm<uint8_t,1> m0) {
	return mipp_avx_cast_k_uint8_float32(m0);
}
rvm<int64_t,1> cast_k_float64_int64(const rvm<float64_t,1> m0) {
	return mipp_avx_cast_k_float64_int64(m0);
}
rvm<int64_t,1> cast_k_float32_int64(const rvm<float32_t,1> m0) {
	return mipp_avx_cast_k_float32_int64(m0);
}
rvm<int64_t,1> cast_k_int64_int64(const rvm<int64_t,1> m0) {
	return mipp_avx_cast_k_int64_int64(m0);
}
rvm<int64_t,1> cast_k_int32_int64(const rvm<int32_t,1> m0) {
	return mipp_avx_cast_k_int32_int64(m0);
}
rvm<int64_t,1> cast_k_int16_int64(const rvm<int16_t,1> m0) {
	return mipp_avx_cast_k_int16_int64(m0);
}
rvm<int64_t,1> cast_k_int8_int64(const rvm<int8_t,1> m0) {
	return mipp_avx_cast_k_int8_int64(m0);
}
rvm<int64_t,1> cast_k_uint64_int64(const rvm<uint64_t,1> m0) {
	return mipp_avx_cast_k_uint64_int64(m0);
}
rvm<int64_t,1> cast_k_uint32_int64(const rvm<uint32_t,1> m0) {
	return mipp_avx_cast_k_uint32_int64(m0);
}
rvm<int64_t,1> cast_k_uint16_int64(const rvm<uint16_t,1> m0) {
	return mipp_avx_cast_k_uint16_int64(m0);
}
rvm<int64_t,1> cast_k_uint8_int64(const rvm<uint8_t,1> m0) {
	return mipp_avx_cast_k_uint8_int64(m0);
}
rvm<int32_t,1> cast_k_float64_int32(const rvm<float64_t,1> m0) {
	return mipp_avx_cast_k_float64_int32(m0);
}
rvm<int32_t,1> cast_k_float32_int32(const rvm<float32_t,1> m0) {
	return mipp_avx_cast_k_float32_int32(m0);
}
rvm<int32_t,1> cast_k_int64_int32(const rvm<int64_t,1> m0) {
	return mipp_avx_cast_k_int64_int32(m0);
}
rvm<int32_t,1> cast_k_int32_int32(const rvm<int32_t,1> m0) {
	return mipp_avx_cast_k_int32_int32(m0);
}
rvm<int32_t,1> cast_k_int16_int32(const rvm<int16_t,1> m0) {
	return mipp_avx_cast_k_int16_int32(m0);
}
rvm<int32_t,1> cast_k_int8_int32(const rvm<int8_t,1> m0) {
	return mipp_avx_cast_k_int8_int32(m0);
}
rvm<int32_t,1> cast_k_uint64_int32(const rvm<uint64_t,1> m0) {
	return mipp_avx_cast_k_uint64_int32(m0);
}
rvm<int32_t,1> cast_k_uint32_int32(const rvm<uint32_t,1> m0) {
	return mipp_avx_cast_k_uint32_int32(m0);
}
rvm<int32_t,1> cast_k_uint16_int32(const rvm<uint16_t,1> m0) {
	return mipp_avx_cast_k_uint16_int32(m0);
}
rvm<int32_t,1> cast_k_uint8_int32(const rvm<uint8_t,1> m0) {
	return mipp_avx_cast_k_uint8_int32(m0);
}
rvm<int16_t,1> cast_k_float64_int16(const rvm<float64_t,1> m0) {
	return mipp_avx_cast_k_float64_int16(m0);
}
rvm<int16_t,1> cast_k_float32_int16(const rvm<float32_t,1> m0) {
	return mipp_avx_cast_k_float32_int16(m0);
}
rvm<int16_t,1> cast_k_int64_int16(const rvm<int64_t,1> m0) {
	return mipp_avx_cast_k_int64_int16(m0);
}
rvm<int16_t,1> cast_k_int32_int16(const rvm<int32_t,1> m0) {
	return mipp_avx_cast_k_int32_int16(m0);
}
rvm<int16_t,1> cast_k_int16_int16(const rvm<int16_t,1> m0) {
	return mipp_avx_cast_k_int16_int16(m0);
}
rvm<int16_t,1> cast_k_int8_int16(const rvm<int8_t,1> m0) {
	return mipp_avx_cast_k_int8_int16(m0);
}
rvm<int16_t,1> cast_k_uint64_int16(const rvm<uint64_t,1> m0) {
	return mipp_avx_cast_k_uint64_int16(m0);
}
rvm<int16_t,1> cast_k_uint32_int16(const rvm<uint32_t,1> m0) {
	return mipp_avx_cast_k_uint32_int16(m0);
}
rvm<int16_t,1> cast_k_uint16_int16(const rvm<uint16_t,1> m0) {
	return mipp_avx_cast_k_uint16_int16(m0);
}
rvm<int16_t,1> cast_k_uint8_int16(const rvm<uint8_t,1> m0) {
	return mipp_avx_cast_k_uint8_int16(m0);
}
rvm<int8_t,1> cast_k_float64_int8(const rvm<float64_t,1> m0) {
	return mipp_avx_cast_k_float64_int8(m0);
}
rvm<int8_t,1> cast_k_float32_int8(const rvm<float32_t,1> m0) {
	return mipp_avx_cast_k_float32_int8(m0);
}
rvm<int8_t,1> cast_k_int64_int8(const rvm<int64_t,1> m0) {
	return mipp_avx_cast_k_int64_int8(m0);
}
rvm<int8_t,1> cast_k_int32_int8(const rvm<int32_t,1> m0) {
	return mipp_avx_cast_k_int32_int8(m0);
}
rvm<int8_t,1> cast_k_int16_int8(const rvm<int16_t,1> m0) {
	return mipp_avx_cast_k_int16_int8(m0);
}
rvm<int8_t,1> cast_k_int8_int8(const rvm<int8_t,1> m0) {
	return mipp_avx_cast_k_int8_int8(m0);
}
rvm<int8_t,1> cast_k_uint64_int8(const rvm<uint64_t,1> m0) {
	return mipp_avx_cast_k_uint64_int8(m0);
}
rvm<int8_t,1> cast_k_uint32_int8(const rvm<uint32_t,1> m0) {
	return mipp_avx_cast_k_uint32_int8(m0);
}
rvm<int8_t,1> cast_k_uint16_int8(const rvm<uint16_t,1> m0) {
	return mipp_avx_cast_k_uint16_int8(m0);
}
rvm<int8_t,1> cast_k_uint8_int8(const rvm<uint8_t,1> m0) {
	return mipp_avx_cast_k_uint8_int8(m0);
}
rvm<uint64_t,1> cast_k_float64_uint64(const rvm<float64_t,1> m0) {
	return mipp_avx_cast_k_float64_uint64(m0);
}
rvm<uint64_t,1> cast_k_float32_uint64(const rvm<float32_t,1> m0) {
	return mipp_avx_cast_k_float32_uint64(m0);
}
rvm<uint64_t,1> cast_k_int64_uint64(const rvm<int64_t,1> m0) {
	return mipp_avx_cast_k_int64_uint64(m0);
}
rvm<uint64_t,1> cast_k_int32_uint64(const rvm<int32_t,1> m0) {
	return mipp_avx_cast_k_int32_uint64(m0);
}
rvm<uint64_t,1> cast_k_int16_uint64(const rvm<int16_t,1> m0) {
	return mipp_avx_cast_k_int16_uint64(m0);
}
rvm<uint64_t,1> cast_k_int8_uint64(const rvm<int8_t,1> m0) {
	return mipp_avx_cast_k_int8_uint64(m0);
}
rvm<uint64_t,1> cast_k_uint64_uint64(const rvm<uint64_t,1> m0) {
	return mipp_avx_cast_k_uint64_uint64(m0);
}
rvm<uint64_t,1> cast_k_uint32_uint64(const rvm<uint32_t,1> m0) {
	return mipp_avx_cast_k_uint32_uint64(m0);
}
rvm<uint64_t,1> cast_k_uint16_uint64(const rvm<uint16_t,1> m0) {
	return mipp_avx_cast_k_uint16_uint64(m0);
}
rvm<uint64_t,1> cast_k_uint8_uint64(const rvm<uint8_t,1> m0) {
	return mipp_avx_cast_k_uint8_uint64(m0);
}
rvm<uint32_t,1> cast_k_float64_uint32(const rvm<float64_t,1> m0) {
	return mipp_avx_cast_k_float64_uint32(m0);
}
rvm<uint32_t,1> cast_k_float32_uint32(const rvm<float32_t,1> m0) {
	return mipp_avx_cast_k_float32_uint32(m0);
}
rvm<uint32_t,1> cast_k_int64_uint32(const rvm<int64_t,1> m0) {
	return mipp_avx_cast_k_int64_uint32(m0);
}
rvm<uint32_t,1> cast_k_int32_uint32(const rvm<int32_t,1> m0) {
	return mipp_avx_cast_k_int32_uint32(m0);
}
rvm<uint32_t,1> cast_k_int16_uint32(const rvm<int16_t,1> m0) {
	return mipp_avx_cast_k_int16_uint32(m0);
}
rvm<uint32_t,1> cast_k_int8_uint32(const rvm<int8_t,1> m0) {
	return mipp_avx_cast_k_int8_uint32(m0);
}
rvm<uint32_t,1> cast_k_uint64_uint32(const rvm<uint64_t,1> m0) {
	return mipp_avx_cast_k_uint64_uint32(m0);
}
rvm<uint32_t,1> cast_k_uint32_uint32(const rvm<uint32_t,1> m0) {
	return mipp_avx_cast_k_uint32_uint32(m0);
}
rvm<uint32_t,1> cast_k_uint16_uint32(const rvm<uint16_t,1> m0) {
	return mipp_avx_cast_k_uint16_uint32(m0);
}
rvm<uint32_t,1> cast_k_uint8_uint32(const rvm<uint8_t,1> m0) {
	return mipp_avx_cast_k_uint8_uint32(m0);
}
rvm<uint16_t,1> cast_k_float64_uint16(const rvm<float64_t,1> m0) {
	return mipp_avx_cast_k_float64_uint16(m0);
}
rvm<uint16_t,1> cast_k_float32_uint16(const rvm<float32_t,1> m0) {
	return mipp_avx_cast_k_float32_uint16(m0);
}
rvm<uint16_t,1> cast_k_int64_uint16(const rvm<int64_t,1> m0) {
	return mipp_avx_cast_k_int64_uint16(m0);
}
rvm<uint16_t,1> cast_k_int32_uint16(const rvm<int32_t,1> m0) {
	return mipp_avx_cast_k_int32_uint16(m0);
}
rvm<uint16_t,1> cast_k_int16_uint16(const rvm<int16_t,1> m0) {
	return mipp_avx_cast_k_int16_uint16(m0);
}
rvm<uint16_t,1> cast_k_int8_uint16(const rvm<int8_t,1> m0) {
	return mipp_avx_cast_k_int8_uint16(m0);
}
rvm<uint16_t,1> cast_k_uint64_uint16(const rvm<uint64_t,1> m0) {
	return mipp_avx_cast_k_uint64_uint16(m0);
}
rvm<uint16_t,1> cast_k_uint32_uint16(const rvm<uint32_t,1> m0) {
	return mipp_avx_cast_k_uint32_uint16(m0);
}
rvm<uint16_t,1> cast_k_uint16_uint16(const rvm<uint16_t,1> m0) {
	return mipp_avx_cast_k_uint16_uint16(m0);
}
rvm<uint16_t,1> cast_k_uint8_uint16(const rvm<uint8_t,1> m0) {
	return mipp_avx_cast_k_uint8_uint16(m0);
}
rvm<uint8_t,1> cast_k_float64_uint8(const rvm<float64_t,1> m0) {
	return mipp_avx_cast_k_float64_uint8(m0);
}
rvm<uint8_t,1> cast_k_float32_uint8(const rvm<float32_t,1> m0) {
	return mipp_avx_cast_k_float32_uint8(m0);
}
rvm<uint8_t,1> cast_k_int64_uint8(const rvm<int64_t,1> m0) {
	return mipp_avx_cast_k_int64_uint8(m0);
}
rvm<uint8_t,1> cast_k_int32_uint8(const rvm<int32_t,1> m0) {
	return mipp_avx_cast_k_int32_uint8(m0);
}
rvm<uint8_t,1> cast_k_int16_uint8(const rvm<int16_t,1> m0) {
	return mipp_avx_cast_k_int16_uint8(m0);
}
rvm<uint8_t,1> cast_k_int8_uint8(const rvm<int8_t,1> m0) {
	return mipp_avx_cast_k_int8_uint8(m0);
}
rvm<uint8_t,1> cast_k_uint64_uint8(const rvm<uint64_t,1> m0) {
	return mipp_avx_cast_k_uint64_uint8(m0);
}
rvm<uint8_t,1> cast_k_uint32_uint8(const rvm<uint32_t,1> m0) {
	return mipp_avx_cast_k_uint32_uint8(m0);
}
rvm<uint8_t,1> cast_k_uint16_uint8(const rvm<uint16_t,1> m0) {
	return mipp_avx_cast_k_uint16_uint8(m0);
}
rvm<uint8_t,1> cast_k_uint8_uint8(const rvm<uint8_t,1> m0) {
	return mipp_avx_cast_k_uint8_uint8(m0);
}
rvd<float64_t,1> toreg_float64(const rvm<float64_t,1> m0) {
	return mipp_avx_toreg_float64(m0);
}
rvd<float32_t,1> toreg_float32(const rvm<float32_t,1> m0) {
	return mipp_avx_toreg_float32(m0);
}
rvd<int64_t,1> toreg_int64(const rvm<int64_t,1> m0) {
	return mipp_avx_toreg_int64(m0);
}
rvd<int32_t,1> toreg_int32(const rvm<int32_t,1> m0) {
	return mipp_avx_toreg_int32(m0);
}
rvd<int16_t,1> toreg_int16(const rvm<int16_t,1> m0) {
	return mipp_avx_toreg_int16(m0);
}
rvd<int8_t,1> toreg_int8(const rvm<int8_t,1> m0) {
	return mipp_avx_toreg_int8(m0);
}
rvd<uint64_t,1> toreg_uint64(const rvm<uint64_t,1> m0) {
	return mipp_avx_toreg_uint64(m0);
}
rvd<uint32_t,1> toreg_uint32(const rvm<uint32_t,1> m0) {
	return mipp_avx_toreg_uint32(m0);
}
rvd<uint16_t,1> toreg_uint16(const rvm<uint16_t,1> m0) {
	return mipp_avx_toreg_uint16(m0);
}
rvd<uint8_t,1> toreg_uint8(const rvm<uint8_t,1> m0) {
	return mipp_avx_toreg_uint8(m0);
}
rvm<float64_t,1> tomsk_float64(const rvd<float64_t,1> r0) {
	return mipp_avx_tomsk_float64(r0);
}
rvm<float32_t,1> tomsk_float32(const rvd<float32_t,1> r0) {
	return mipp_avx_tomsk_float32(r0);
}
rvm<int64_t,1> tomsk_int64(const rvd<int64_t,1> r0) {
	return mipp_avx_tomsk_int64(r0);
}
rvm<int32_t,1> tomsk_int32(const rvd<int32_t,1> r0) {
	return mipp_avx_tomsk_int32(r0);
}
rvm<int16_t,1> tomsk_int16(const rvd<int16_t,1> r0) {
	return mipp_avx_tomsk_int16(r0);
}
rvm<int8_t,1> tomsk_int8(const rvd<int8_t,1> r0) {
	return mipp_avx_tomsk_int8(r0);
}
rvm<uint64_t,1> tomsk_uint64(const rvd<uint64_t,1> r0) {
	return mipp_avx_tomsk_uint64(r0);
}
rvm<uint32_t,1> tomsk_uint32(const rvd<uint32_t,1> r0) {
	return mipp_avx_tomsk_uint32(r0);
}
rvm<uint16_t,1> tomsk_uint16(const rvd<uint16_t,1> r0) {
	return mipp_avx_tomsk_uint16(r0);
}
rvm<uint8_t,1> tomsk_uint8(const rvd<uint8_t,1> r0) {
	return mipp_avx_tomsk_uint8(r0);
}
rvd<float64_t,1> load_float64(const float64_t* p0) {
	return mipp_avx_load_float64(p0);
}
rvd<float32_t,1> load_float32(const float32_t* p0) {
	return mipp_avx_load_float32(p0);
}
rvd<int64_t,1> load_int64(const int64_t* p0) {
	return mipp_avx_load_int64(p0);
}
rvd<int32_t,1> load_int32(const int32_t* p0) {
	return mipp_avx_load_int32(p0);
}
rvd<int16_t,1> load_int16(const int16_t* p0) {
	return mipp_avx_load_int16(p0);
}
rvd<int8_t,1> load_int8(const int8_t* p0) {
	return mipp_avx_load_int8(p0);
}
rvd<uint64_t,1> load_uint64(const uint64_t* p0) {
	return mipp_avx_load_uint64(p0);
}
rvd<uint32_t,1> load_uint32(const uint32_t* p0) {
	return mipp_avx_load_uint32(p0);
}
rvd<uint16_t,1> load_uint16(const uint16_t* p0) {
	return mipp_avx_load_uint16(p0);
}
rvd<uint8_t,1> load_uint8(const uint8_t* p0) {
	return mipp_avx_load_uint8(p0);
}
rvd<float64_t,1> loadu_float64(const float64_t* p0) {
	return mipp_avx_loadu_float64(p0);
}
rvd<float32_t,1> loadu_float32(const float32_t* p0) {
	return mipp_avx_loadu_float32(p0);
}
rvd<int64_t,1> loadu_int64(const int64_t* p0) {
	return mipp_avx_loadu_int64(p0);
}
rvd<int32_t,1> loadu_int32(const int32_t* p0) {
	return mipp_avx_loadu_int32(p0);
}
rvd<int16_t,1> loadu_int16(const int16_t* p0) {
	return mipp_avx_loadu_int16(p0);
}
rvd<int8_t,1> loadu_int8(const int8_t* p0) {
	return mipp_avx_loadu_int8(p0);
}
rvd<uint64_t,1> loadu_uint64(const uint64_t* p0) {
	return mipp_avx_loadu_uint64(p0);
}
rvd<uint32_t,1> loadu_uint32(const uint32_t* p0) {
	return mipp_avx_loadu_uint32(p0);
}
rvd<uint16_t,1> loadu_uint16(const uint16_t* p0) {
	return mipp_avx_loadu_uint16(p0);
}
rvd<uint8_t,1> loadu_uint8(const uint8_t* p0) {
	return mipp_avx_loadu_uint8(p0);
}
void store_float64(float64_t* p0, const rvd<float64_t,1> r0) {
	mipp_avx_store_float64(p0, r0);
}
void store_float32(float32_t* p0, const rvd<float32_t,1> r0) {
	mipp_avx_store_float32(p0, r0);
}
void store_int64(int64_t* p0, const rvd<int64_t,1> r0) {
	mipp_avx_store_int64(p0, r0);
}
void store_int32(int32_t* p0, const rvd<int32_t,1> r0) {
	mipp_avx_store_int32(p0, r0);
}
void store_int16(int16_t* p0, const rvd<int16_t,1> r0) {
	mipp_avx_store_int16(p0, r0);
}
void store_int8(int8_t* p0, const rvd<int8_t,1> r0) {
	mipp_avx_store_int8(p0, r0);
}
void store_uint64(uint64_t* p0, const rvd<uint64_t,1> r0) {
	mipp_avx_store_uint64(p0, r0);
}
void store_uint32(uint32_t* p0, const rvd<uint32_t,1> r0) {
	mipp_avx_store_uint32(p0, r0);
}
void store_uint16(uint16_t* p0, const rvd<uint16_t,1> r0) {
	mipp_avx_store_uint16(p0, r0);
}
void store_uint8(uint8_t* p0, const rvd<uint8_t,1> r0) {
	mipp_avx_store_uint8(p0, r0);
}
void storeu_float64(float64_t* p0, const rvd<float64_t,1> r0) {
	mipp_avx_storeu_float64(p0, r0);
}
void storeu_float32(float32_t* p0, const rvd<float32_t,1> r0) {
	mipp_avx_storeu_float32(p0, r0);
}
void storeu_int64(int64_t* p0, const rvd<int64_t,1> r0) {
	mipp_avx_storeu_int64(p0, r0);
}
void storeu_int32(int32_t* p0, const rvd<int32_t,1> r0) {
	mipp_avx_storeu_int32(p0, r0);
}
void storeu_int16(int16_t* p0, const rvd<int16_t,1> r0) {
	mipp_avx_storeu_int16(p0, r0);
}
void storeu_int8(int8_t* p0, const rvd<int8_t,1> r0) {
	mipp_avx_storeu_int8(p0, r0);
}
void storeu_uint64(uint64_t* p0, const rvd<uint64_t,1> r0) {
	mipp_avx_storeu_uint64(p0, r0);
}
void storeu_uint32(uint32_t* p0, const rvd<uint32_t,1> r0) {
	mipp_avx_storeu_uint32(p0, r0);
}
void storeu_uint16(uint16_t* p0, const rvd<uint16_t,1> r0) {
	mipp_avx_storeu_uint16(p0, r0);
}
void storeu_uint8(uint8_t* p0, const rvd<uint8_t,1> r0) {
	mipp_avx_storeu_uint8(p0, r0);
}
rvd<float64_t,1> set1_float64(const float64_t v0) {
	return mipp_avx_set1_float64(v0);
}
rvd<float32_t,1> set1_float32(const float32_t v0) {
	return mipp_avx_set1_float32(v0);
}
rvd<int64_t,1> set1_int64(const int64_t v0) {
	return mipp_avx_set1_int64(v0);
}
rvd<int32_t,1> set1_int32(const int32_t v0) {
	return mipp_avx_set1_int32(v0);
}
rvd<int16_t,1> set1_int16(const int16_t v0) {
	return mipp_avx_set1_int16(v0);
}
rvd<int8_t,1> set1_int8(const int8_t v0) {
	return mipp_avx_set1_int8(v0);
}
rvd<uint64_t,1> set1_uint64(const uint64_t v0) {
	return mipp_avx_set1_uint64(v0);
}
rvd<uint32_t,1> set1_uint32(const uint32_t v0) {
	return mipp_avx_set1_uint32(v0);
}
rvd<uint16_t,1> set1_uint16(const uint16_t v0) {
	return mipp_avx_set1_uint16(v0);
}
rvd<uint8_t,1> set1_uint8(const uint8_t v0) {
	return mipp_avx_set1_uint8(v0);
}
rvd<float64_t,1> set0_float64() {
	return mipp_avx_set0_float64();
}
rvd<float32_t,1> set0_float32() {
	return mipp_avx_set0_float32();
}
rvd<int64_t,1> set0_int64() {
	return mipp_avx_set0_int64();
}
rvd<int32_t,1> set0_int32() {
	return mipp_avx_set0_int32();
}
rvd<int16_t,1> set0_int16() {
	return mipp_avx_set0_int16();
}
rvd<int8_t,1> set0_int8() {
	return mipp_avx_set0_int8();
}
rvd<uint64_t,1> set0_uint64() {
	return mipp_avx_set0_uint64();
}
rvd<uint32_t,1> set0_uint32() {
	return mipp_avx_set0_uint32();
}
rvd<uint16_t,1> set0_uint16() {
	return mipp_avx_set0_uint16();
}
rvd<uint8_t,1> set0_uint8() {
	return mipp_avx_set0_uint8();
}
rvm<float64_t,1> set0_k_float64() {
	return mipp_avx_set0_k_float64();
}
rvm<float32_t,1> set0_k_float32() {
	return mipp_avx_set0_k_float32();
}
rvm<int64_t,1> set0_k_int64() {
	return mipp_avx_set0_k_int64();
}
rvm<int32_t,1> set0_k_int32() {
	return mipp_avx_set0_k_int32();
}
rvm<int16_t,1> set0_k_int16() {
	return mipp_avx_set0_k_int16();
}
rvm<int8_t,1> set0_k_int8() {
	return mipp_avx_set0_k_int8();
}
rvm<uint64_t,1> set0_k_uint64() {
	return mipp_avx_set0_k_uint64();
}
rvm<uint32_t,1> set0_k_uint32() {
	return mipp_avx_set0_k_uint32();
}
rvm<uint16_t,1> set0_k_uint16() {
	return mipp_avx_set0_k_uint16();
}
rvm<uint8_t,1> set0_k_uint8() {
	return mipp_avx_set0_k_uint8();
}
float64_t get_float64(const rvd<float64_t,1> r0, const uint32_t v0) {
	return mipp_avx_get_float64(r0, v0);
}
float32_t get_float32(const rvd<float32_t,1> r0, const uint32_t v0) {
	return mipp_avx_get_float32(r0, v0);
}
int64_t get_int64(const rvd<int64_t,1> r0, const uint32_t v0) {
	return mipp_avx_get_int64(r0, v0);
}
int32_t get_int32(const rvd<int32_t,1> r0, const uint32_t v0) {
	return mipp_avx_get_int32(r0, v0);
}
int16_t get_int16(const rvd<int16_t,1> r0, const uint32_t v0) {
	return mipp_avx_get_int16(r0, v0);
}
int8_t get_int8(const rvd<int8_t,1> r0, const uint32_t v0) {
	return mipp_avx_get_int8(r0, v0);
}
uint64_t get_uint64(const rvd<uint64_t,1> r0, const uint32_t v0) {
	return mipp_avx_get_uint64(r0, v0);
}
uint32_t get_uint32(const rvd<uint32_t,1> r0, const uint32_t v0) {
	return mipp_avx_get_uint32(r0, v0);
}
uint16_t get_uint16(const rvd<uint16_t,1> r0, const uint32_t v0) {
	return mipp_avx_get_uint16(r0, v0);
}
uint8_t get_uint8(const rvd<uint8_t,1> r0, const uint32_t v0) {
	return mipp_avx_get_uint8(r0, v0);
}
float64_t getfirst_float64(const rvd<float64_t,1> r0) {
	return mipp_avx_getfirst_float64(r0);
}
float32_t getfirst_float32(const rvd<float32_t,1> r0) {
	return mipp_avx_getfirst_float32(r0);
}
int64_t getfirst_int64(const rvd<int64_t,1> r0) {
	return mipp_avx_getfirst_int64(r0);
}
int32_t getfirst_int32(const rvd<int32_t,1> r0) {
	return mipp_avx_getfirst_int32(r0);
}
int16_t getfirst_int16(const rvd<int16_t,1> r0) {
	return mipp_avx_getfirst_int16(r0);
}
int8_t getfirst_int8(const rvd<int8_t,1> r0) {
	return mipp_avx_getfirst_int8(r0);
}
uint64_t getfirst_uint64(const rvd<uint64_t,1> r0) {
	return mipp_avx_getfirst_uint64(r0);
}
uint32_t getfirst_uint32(const rvd<uint32_t,1> r0) {
	return mipp_avx_getfirst_uint32(r0);
}
uint16_t getfirst_uint16(const rvd<uint16_t,1> r0) {
	return mipp_avx_getfirst_uint16(r0);
}
uint8_t getfirst_uint8(const rvd<uint8_t,1> r0) {
	return mipp_avx_getfirst_uint8(r0);
}
rvd<float64_t,1> sqrt_float64(const rvd<float64_t,1> r0) {
	return mipp_avx_sqrt_float64(r0);
}
rvd<float32_t,1> sqrt_float32(const rvd<float32_t,1> r0) {
	return mipp_avx_sqrt_float32(r0);
}
rvd<float64_t,1> rsqrt_float64(const rvd<float64_t,1> r0) {
	return mipp_avx_rsqrt_float64(r0);
}
rvd<float32_t,1> rsqrt_float32(const rvd<float32_t,1> r0) {
	return mipp_avx_rsqrt_float32(r0);
}
rvd<float64_t,1> add_float64(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_avx_add_float64(r0, r1);
}
rvd<float32_t,1> add_float32(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_avx_add_float32(r0, r1);
}
rvd<int64_t,1> add_int64(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_avx_add_int64(r0, r1);
}
rvd<int32_t,1> add_int32(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_avx_add_int32(r0, r1);
}
rvd<int16_t,1> add_int16(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_avx_add_int16(r0, r1);
}
rvd<int8_t,1> add_int8(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_avx_add_int8(r0, r1);
}
rvd<uint64_t,1> add_uint64(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_avx_add_uint64(r0, r1);
}
rvd<uint32_t,1> add_uint32(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_avx_add_uint32(r0, r1);
}
rvd<uint16_t,1> add_uint16(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_avx_add_uint16(r0, r1);
}
rvd<uint8_t,1> add_uint8(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_avx_add_uint8(r0, r1);
}
rvd<float64_t,1> sub_float64(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_avx_sub_float64(r0, r1);
}
rvd<float32_t,1> sub_float32(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_avx_sub_float32(r0, r1);
}
rvd<int64_t,1> sub_int64(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_avx_sub_int64(r0, r1);
}
rvd<int32_t,1> sub_int32(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_avx_sub_int32(r0, r1);
}
rvd<int16_t,1> sub_int16(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_avx_sub_int16(r0, r1);
}
rvd<int8_t,1> sub_int8(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_avx_sub_int8(r0, r1);
}
rvd<uint64_t,1> sub_uint64(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_avx_sub_uint64(r0, r1);
}
rvd<uint32_t,1> sub_uint32(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_avx_sub_uint32(r0, r1);
}
rvd<uint16_t,1> sub_uint16(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_avx_sub_uint16(r0, r1);
}
rvd<uint8_t,1> sub_uint8(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_avx_sub_uint8(r0, r1);
}
rvd<float64_t,1> mul_float64(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_avx_mul_float64(r0, r1);
}
rvd<float32_t,1> mul_float32(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_avx_mul_float32(r0, r1);
}
rvd<int64_t,1> mul_int64(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_avx_mul_int64(r0, r1);
}
rvd<int32_t,1> mul_int32(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_avx_mul_int32(r0, r1);
}
rvd<int16_t,1> mul_int16(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_avx_mul_int16(r0, r1);
}
rvd<int8_t,1> mul_int8(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_avx_mul_int8(r0, r1);
}
rvd<uint64_t,1> mul_uint64(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_avx_mul_uint64(r0, r1);
}
rvd<uint32_t,1> mul_uint32(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_avx_mul_uint32(r0, r1);
}
rvd<uint16_t,1> mul_uint16(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_avx_mul_uint16(r0, r1);
}
rvd<uint8_t,1> mul_uint8(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_avx_mul_uint8(r0, r1);
}
rvd<float64_t,1> div_float64(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_avx_div_float64(r0, r1);
}
rvd<float32_t,1> div_float32(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_avx_div_float32(r0, r1);
}
rvd<float64_t,1> min_float64(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_avx_min_float64(r0, r1);
}
rvd<float32_t,1> min_float32(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_avx_min_float32(r0, r1);
}
rvd<int64_t,1> min_int64(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_avx_min_int64(r0, r1);
}
rvd<int32_t,1> min_int32(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_avx_min_int32(r0, r1);
}
rvd<int16_t,1> min_int16(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_avx_min_int16(r0, r1);
}
rvd<int8_t,1> min_int8(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_avx_min_int8(r0, r1);
}
rvd<uint64_t,1> min_uint64(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_avx_min_uint64(r0, r1);
}
rvd<uint32_t,1> min_uint32(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_avx_min_uint32(r0, r1);
}
rvd<uint16_t,1> min_uint16(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_avx_min_uint16(r0, r1);
}
rvd<uint8_t,1> min_uint8(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_avx_min_uint8(r0, r1);
}
rvd<float64_t,1> max_float64(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_avx_max_float64(r0, r1);
}
rvd<float32_t,1> max_float32(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_avx_max_float32(r0, r1);
}
rvd<int64_t,1> max_int64(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_avx_max_int64(r0, r1);
}
rvd<int32_t,1> max_int32(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_avx_max_int32(r0, r1);
}
rvd<int16_t,1> max_int16(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_avx_max_int16(r0, r1);
}
rvd<int8_t,1> max_int8(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_avx_max_int8(r0, r1);
}
rvd<uint64_t,1> max_uint64(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_avx_max_uint64(r0, r1);
}
rvd<uint32_t,1> max_uint32(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_avx_max_uint32(r0, r1);
}
rvd<uint16_t,1> max_uint16(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_avx_max_uint16(r0, r1);
}
rvd<uint8_t,1> max_uint8(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_avx_max_uint8(r0, r1);
}
rvd<float64_t,1> fmadd_float64(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1, const rvd<float64_t,1> r2) {
	return mipp_avx_fmadd_float64(r0, r1, r2);
}
rvd<float32_t,1> fmadd_float32(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1, const rvd<float32_t,1> r2) {
	return mipp_avx_fmadd_float32(r0, r1, r2);
}
rvd<float64_t,1> fmsub_float64(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1, const rvd<float64_t,1> r2) {
	return mipp_avx_fmsub_float64(r0, r1, r2);
}
rvd<float32_t,1> fmsub_float32(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1, const rvd<float32_t,1> r2) {
	return mipp_avx_fmsub_float32(r0, r1, r2);
}
rvd<float64_t,1> andb_float64(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_avx_andb_float64(r0, r1);
}
rvd<float32_t,1> andb_float32(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_avx_andb_float32(r0, r1);
}
rvd<int64_t,1> andb_int64(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_avx_andb_int64(r0, r1);
}
rvd<int32_t,1> andb_int32(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_avx_andb_int32(r0, r1);
}
rvd<int16_t,1> andb_int16(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_avx_andb_int16(r0, r1);
}
rvd<int8_t,1> andb_int8(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_avx_andb_int8(r0, r1);
}
rvd<uint64_t,1> andb_uint64(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_avx_andb_uint64(r0, r1);
}
rvd<uint32_t,1> andb_uint32(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_avx_andb_uint32(r0, r1);
}
rvd<uint16_t,1> andb_uint16(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_avx_andb_uint16(r0, r1);
}
rvd<uint8_t,1> andb_uint8(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_avx_andb_uint8(r0, r1);
}
rvm<float64_t,1> andb_float64(const rvm<float64_t,1> m0, const rvm<float64_t,1> m1) {
	return mipp_avx_andb_k_float64(m0, m1);
}
rvm<float32_t,1> andb_float32(const rvm<float32_t,1> m0, const rvm<float32_t,1> m1) {
	return mipp_avx_andb_k_float32(m0, m1);
}
rvm<int64_t,1> andb_int64(const rvm<int64_t,1> m0, const rvm<int64_t,1> m1) {
	return mipp_avx_andb_k_int64(m0, m1);
}
rvm<int32_t,1> andb_int32(const rvm<int32_t,1> m0, const rvm<int32_t,1> m1) {
	return mipp_avx_andb_k_int32(m0, m1);
}
rvm<int16_t,1> andb_int16(const rvm<int16_t,1> m0, const rvm<int16_t,1> m1) {
	return mipp_avx_andb_k_int16(m0, m1);
}
rvm<int8_t,1> andb_int8(const rvm<int8_t,1> m0, const rvm<int8_t,1> m1) {
	return mipp_avx_andb_k_int8(m0, m1);
}
rvm<uint64_t,1> andb_uint64(const rvm<uint64_t,1> m0, const rvm<uint64_t,1> m1) {
	return mipp_avx_andb_k_uint64(m0, m1);
}
rvm<uint32_t,1> andb_uint32(const rvm<uint32_t,1> m0, const rvm<uint32_t,1> m1) {
	return mipp_avx_andb_k_uint32(m0, m1);
}
rvm<uint16_t,1> andb_uint16(const rvm<uint16_t,1> m0, const rvm<uint16_t,1> m1) {
	return mipp_avx_andb_k_uint16(m0, m1);
}
rvm<uint8_t,1> andb_uint8(const rvm<uint8_t,1> m0, const rvm<uint8_t,1> m1) {
	return mipp_avx_andb_k_uint8(m0, m1);
}
rvd<float64_t,1> andnb_float64(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_avx_andnb_float64(r0, r1);
}
rvd<float32_t,1> andnb_float32(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_avx_andnb_float32(r0, r1);
}
rvd<int64_t,1> andnb_int64(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_avx_andnb_int64(r0, r1);
}
rvd<int32_t,1> andnb_int32(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_avx_andnb_int32(r0, r1);
}
rvd<int16_t,1> andnb_int16(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_avx_andnb_int16(r0, r1);
}
rvd<int8_t,1> andnb_int8(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_avx_andnb_int8(r0, r1);
}
rvd<uint64_t,1> andnb_uint64(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_avx_andnb_uint64(r0, r1);
}
rvd<uint32_t,1> andnb_uint32(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_avx_andnb_uint32(r0, r1);
}
rvd<uint16_t,1> andnb_uint16(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_avx_andnb_uint16(r0, r1);
}
rvd<uint8_t,1> andnb_uint8(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_avx_andnb_uint8(r0, r1);
}
rvm<float64_t,1> andnb_float64(const rvm<float64_t,1> m0, const rvm<float64_t,1> m1) {
	return mipp_avx_andnb_k_float64(m0, m1);
}
rvm<float32_t,1> andnb_float32(const rvm<float32_t,1> m0, const rvm<float32_t,1> m1) {
	return mipp_avx_andnb_k_float32(m0, m1);
}
rvm<int64_t,1> andnb_int64(const rvm<int64_t,1> m0, const rvm<int64_t,1> m1) {
	return mipp_avx_andnb_k_int64(m0, m1);
}
rvm<int32_t,1> andnb_int32(const rvm<int32_t,1> m0, const rvm<int32_t,1> m1) {
	return mipp_avx_andnb_k_int32(m0, m1);
}
rvm<int16_t,1> andnb_int16(const rvm<int16_t,1> m0, const rvm<int16_t,1> m1) {
	return mipp_avx_andnb_k_int16(m0, m1);
}
rvm<int8_t,1> andnb_int8(const rvm<int8_t,1> m0, const rvm<int8_t,1> m1) {
	return mipp_avx_andnb_k_int8(m0, m1);
}
rvm<uint64_t,1> andnb_uint64(const rvm<uint64_t,1> m0, const rvm<uint64_t,1> m1) {
	return mipp_avx_andnb_k_uint64(m0, m1);
}
rvm<uint32_t,1> andnb_uint32(const rvm<uint32_t,1> m0, const rvm<uint32_t,1> m1) {
	return mipp_avx_andnb_k_uint32(m0, m1);
}
rvm<uint16_t,1> andnb_uint16(const rvm<uint16_t,1> m0, const rvm<uint16_t,1> m1) {
	return mipp_avx_andnb_k_uint16(m0, m1);
}
rvm<uint8_t,1> andnb_uint8(const rvm<uint8_t,1> m0, const rvm<uint8_t,1> m1) {
	return mipp_avx_andnb_k_uint8(m0, m1);
}
rvd<float64_t,1> orb_float64(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_avx_orb_float64(r0, r1);
}
rvd<float32_t,1> orb_float32(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_avx_orb_float32(r0, r1);
}
rvd<int64_t,1> orb_int64(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_avx_orb_int64(r0, r1);
}
rvd<int32_t,1> orb_int32(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_avx_orb_int32(r0, r1);
}
rvd<int16_t,1> orb_int16(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_avx_orb_int16(r0, r1);
}
rvd<int8_t,1> orb_int8(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_avx_orb_int8(r0, r1);
}
rvd<uint64_t,1> orb_uint64(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_avx_orb_uint64(r0, r1);
}
rvd<uint32_t,1> orb_uint32(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_avx_orb_uint32(r0, r1);
}
rvd<uint16_t,1> orb_uint16(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_avx_orb_uint16(r0, r1);
}
rvd<uint8_t,1> orb_uint8(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_avx_orb_uint8(r0, r1);
}
rvm<float64_t,1> orb_float64(const rvm<float64_t,1> m0, const rvm<float64_t,1> m1) {
	return mipp_avx_orb_k_float64(m0, m1);
}
rvm<float32_t,1> orb_float32(const rvm<float32_t,1> m0, const rvm<float32_t,1> m1) {
	return mipp_avx_orb_k_float32(m0, m1);
}
rvm<int64_t,1> orb_int64(const rvm<int64_t,1> m0, const rvm<int64_t,1> m1) {
	return mipp_avx_orb_k_int64(m0, m1);
}
rvm<int32_t,1> orb_int32(const rvm<int32_t,1> m0, const rvm<int32_t,1> m1) {
	return mipp_avx_orb_k_int32(m0, m1);
}
rvm<int16_t,1> orb_int16(const rvm<int16_t,1> m0, const rvm<int16_t,1> m1) {
	return mipp_avx_orb_k_int16(m0, m1);
}
rvm<int8_t,1> orb_int8(const rvm<int8_t,1> m0, const rvm<int8_t,1> m1) {
	return mipp_avx_orb_k_int8(m0, m1);
}
rvm<uint64_t,1> orb_uint64(const rvm<uint64_t,1> m0, const rvm<uint64_t,1> m1) {
	return mipp_avx_orb_k_uint64(m0, m1);
}
rvm<uint32_t,1> orb_uint32(const rvm<uint32_t,1> m0, const rvm<uint32_t,1> m1) {
	return mipp_avx_orb_k_uint32(m0, m1);
}
rvm<uint16_t,1> orb_uint16(const rvm<uint16_t,1> m0, const rvm<uint16_t,1> m1) {
	return mipp_avx_orb_k_uint16(m0, m1);
}
rvm<uint8_t,1> orb_uint8(const rvm<uint8_t,1> m0, const rvm<uint8_t,1> m1) {
	return mipp_avx_orb_k_uint8(m0, m1);
}
rvd<float64_t,1> xorb_float64(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_avx_xorb_float64(r0, r1);
}
rvd<float32_t,1> xorb_float32(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_avx_xorb_float32(r0, r1);
}
rvd<int64_t,1> xorb_int64(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_avx_xorb_int64(r0, r1);
}
rvd<int32_t,1> xorb_int32(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_avx_xorb_int32(r0, r1);
}
rvd<int16_t,1> xorb_int16(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_avx_xorb_int16(r0, r1);
}
rvd<int8_t,1> xorb_int8(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_avx_xorb_int8(r0, r1);
}
rvd<uint64_t,1> xorb_uint64(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_avx_xorb_uint64(r0, r1);
}
rvd<uint32_t,1> xorb_uint32(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_avx_xorb_uint32(r0, r1);
}
rvd<uint16_t,1> xorb_uint16(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_avx_xorb_uint16(r0, r1);
}
rvd<uint8_t,1> xorb_uint8(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_avx_xorb_uint8(r0, r1);
}
rvm<float64_t,1> xorb_float64(const rvm<float64_t,1> m0, const rvm<float64_t,1> m1) {
	return mipp_avx_xorb_k_float64(m0, m1);
}
rvm<float32_t,1> xorb_float32(const rvm<float32_t,1> m0, const rvm<float32_t,1> m1) {
	return mipp_avx_xorb_k_float32(m0, m1);
}
rvm<int64_t,1> xorb_int64(const rvm<int64_t,1> m0, const rvm<int64_t,1> m1) {
	return mipp_avx_xorb_k_int64(m0, m1);
}
rvm<int32_t,1> xorb_int32(const rvm<int32_t,1> m0, const rvm<int32_t,1> m1) {
	return mipp_avx_xorb_k_int32(m0, m1);
}
rvm<int16_t,1> xorb_int16(const rvm<int16_t,1> m0, const rvm<int16_t,1> m1) {
	return mipp_avx_xorb_k_int16(m0, m1);
}
rvm<int8_t,1> xorb_int8(const rvm<int8_t,1> m0, const rvm<int8_t,1> m1) {
	return mipp_avx_xorb_k_int8(m0, m1);
}
rvm<uint64_t,1> xorb_uint64(const rvm<uint64_t,1> m0, const rvm<uint64_t,1> m1) {
	return mipp_avx_xorb_k_uint64(m0, m1);
}
rvm<uint32_t,1> xorb_uint32(const rvm<uint32_t,1> m0, const rvm<uint32_t,1> m1) {
	return mipp_avx_xorb_k_uint32(m0, m1);
}
rvm<uint16_t,1> xorb_uint16(const rvm<uint16_t,1> m0, const rvm<uint16_t,1> m1) {
	return mipp_avx_xorb_k_uint16(m0, m1);
}
rvm<uint8_t,1> xorb_uint8(const rvm<uint8_t,1> m0, const rvm<uint8_t,1> m1) {
	return mipp_avx_xorb_k_uint8(m0, m1);
}
rvd<float64_t,1> msb_float64(const rvd<float64_t,1> r0) {
	return mipp_avx_msb_float64(r0);
}
rvd<float32_t,1> msb_float32(const rvd<float32_t,1> r0) {
	return mipp_avx_msb_float32(r0);
}
rvd<int64_t,1> msb_int64(const rvd<int64_t,1> r0) {
	return mipp_avx_msb_int64(r0);
}
rvd<int32_t,1> msb_int32(const rvd<int32_t,1> r0) {
	return mipp_avx_msb_int32(r0);
}
rvd<int16_t,1> msb_int16(const rvd<int16_t,1> r0) {
	return mipp_avx_msb_int16(r0);
}
rvd<int8_t,1> msb_int8(const rvd<int8_t,1> r0) {
	return mipp_avx_msb_int8(r0);
}
rvd<uint64_t,1> msb_uint64(const rvd<uint64_t,1> r0) {
	return mipp_avx_msb_uint64(r0);
}
rvd<uint32_t,1> msb_uint32(const rvd<uint32_t,1> r0) {
	return mipp_avx_msb_uint32(r0);
}
rvd<uint16_t,1> msb_uint16(const rvd<uint16_t,1> r0) {
	return mipp_avx_msb_uint16(r0);
}
rvd<uint8_t,1> msb_uint8(const rvd<uint8_t,1> r0) {
	return mipp_avx_msb_uint8(r0);
}
rvd<float64_t,1> notb_float64(const rvd<float64_t,1> r0) {
	return mipp_avx_notb_float64(r0);
}
rvd<float32_t,1> notb_float32(const rvd<float32_t,1> r0) {
	return mipp_avx_notb_float32(r0);
}
rvd<int64_t,1> notb_int64(const rvd<int64_t,1> r0) {
	return mipp_avx_notb_int64(r0);
}
rvd<int32_t,1> notb_int32(const rvd<int32_t,1> r0) {
	return mipp_avx_notb_int32(r0);
}
rvd<int16_t,1> notb_int16(const rvd<int16_t,1> r0) {
	return mipp_avx_notb_int16(r0);
}
rvd<int8_t,1> notb_int8(const rvd<int8_t,1> r0) {
	return mipp_avx_notb_int8(r0);
}
rvd<uint64_t,1> notb_uint64(const rvd<uint64_t,1> r0) {
	return mipp_avx_notb_uint64(r0);
}
rvd<uint32_t,1> notb_uint32(const rvd<uint32_t,1> r0) {
	return mipp_avx_notb_uint32(r0);
}
rvd<uint16_t,1> notb_uint16(const rvd<uint16_t,1> r0) {
	return mipp_avx_notb_uint16(r0);
}
rvd<uint8_t,1> notb_uint8(const rvd<uint8_t,1> r0) {
	return mipp_avx_notb_uint8(r0);
}
rvm<float64_t,1> notb_float64(const rvm<float64_t,1> m0) {
	return mipp_avx_notb_k_float64(m0);
}
rvm<float32_t,1> notb_float32(const rvm<float32_t,1> m0) {
	return mipp_avx_notb_k_float32(m0);
}
rvm<int64_t,1> notb_int64(const rvm<int64_t,1> m0) {
	return mipp_avx_notb_k_int64(m0);
}
rvm<int32_t,1> notb_int32(const rvm<int32_t,1> m0) {
	return mipp_avx_notb_k_int32(m0);
}
rvm<int16_t,1> notb_int16(const rvm<int16_t,1> m0) {
	return mipp_avx_notb_k_int16(m0);
}
rvm<int8_t,1> notb_int8(const rvm<int8_t,1> m0) {
	return mipp_avx_notb_k_int8(m0);
}
rvm<uint64_t,1> notb_uint64(const rvm<uint64_t,1> m0) {
	return mipp_avx_notb_k_uint64(m0);
}
rvm<uint32_t,1> notb_uint32(const rvm<uint32_t,1> m0) {
	return mipp_avx_notb_k_uint32(m0);
}
rvm<uint16_t,1> notb_uint16(const rvm<uint16_t,1> m0) {
	return mipp_avx_notb_k_uint16(m0);
}
rvm<uint8_t,1> notb_uint8(const rvm<uint8_t,1> m0) {
	return mipp_avx_notb_k_uint8(m0);
}
rvm<float64_t,1> cmpeq_float64(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_avx_cmpeq_float64(r0, r1);
}
rvm<float32_t,1> cmpeq_float32(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_avx_cmpeq_float32(r0, r1);
}
rvm<int64_t,1> cmpeq_int64(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_avx_cmpeq_int64(r0, r1);
}
rvm<int32_t,1> cmpeq_int32(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_avx_cmpeq_int32(r0, r1);
}
rvm<int16_t,1> cmpeq_int16(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_avx_cmpeq_int16(r0, r1);
}
rvm<int8_t,1> cmpeq_int8(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_avx_cmpeq_int8(r0, r1);
}
rvm<uint64_t,1> cmpeq_uint64(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_avx_cmpeq_uint64(r0, r1);
}
rvm<uint32_t,1> cmpeq_uint32(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_avx_cmpeq_uint32(r0, r1);
}
rvm<uint16_t,1> cmpeq_uint16(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_avx_cmpeq_uint16(r0, r1);
}
rvm<uint8_t,1> cmpeq_uint8(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_avx_cmpeq_uint8(r0, r1);
}
rvm<float64_t,1> cmpneq_float64(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_avx_cmpneq_float64(r0, r1);
}
rvm<float32_t,1> cmpneq_float32(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_avx_cmpneq_float32(r0, r1);
}
rvm<int64_t,1> cmpneq_int64(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_avx_cmpneq_int64(r0, r1);
}
rvm<int32_t,1> cmpneq_int32(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_avx_cmpneq_int32(r0, r1);
}
rvm<int16_t,1> cmpneq_int16(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_avx_cmpneq_int16(r0, r1);
}
rvm<int8_t,1> cmpneq_int8(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_avx_cmpneq_int8(r0, r1);
}
rvm<uint64_t,1> cmpneq_uint64(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_avx_cmpneq_uint64(r0, r1);
}
rvm<uint32_t,1> cmpneq_uint32(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_avx_cmpneq_uint32(r0, r1);
}
rvm<uint16_t,1> cmpneq_uint16(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_avx_cmpneq_uint16(r0, r1);
}
rvm<uint8_t,1> cmpneq_uint8(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_avx_cmpneq_uint8(r0, r1);
}
rvm<float64_t,1> cmplt_float64(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_avx_cmplt_float64(r0, r1);
}
rvm<float32_t,1> cmplt_float32(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_avx_cmplt_float32(r0, r1);
}
rvm<int64_t,1> cmplt_int64(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_avx_cmplt_int64(r0, r1);
}
rvm<int32_t,1> cmplt_int32(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_avx_cmplt_int32(r0, r1);
}
rvm<int16_t,1> cmplt_int16(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_avx_cmplt_int16(r0, r1);
}
rvm<int8_t,1> cmplt_int8(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_avx_cmplt_int8(r0, r1);
}
rvm<uint64_t,1> cmplt_uint64(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_avx_cmplt_uint64(r0, r1);
}
rvm<uint32_t,1> cmplt_uint32(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_avx_cmplt_uint32(r0, r1);
}
rvm<uint16_t,1> cmplt_uint16(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_avx_cmplt_uint16(r0, r1);
}
rvm<uint8_t,1> cmplt_uint8(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_avx_cmplt_uint8(r0, r1);
}
rvm<float64_t,1> cmple_float64(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_avx_cmple_float64(r0, r1);
}
rvm<float32_t,1> cmple_float32(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_avx_cmple_float32(r0, r1);
}
rvm<int64_t,1> cmple_int64(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_avx_cmple_int64(r0, r1);
}
rvm<int32_t,1> cmple_int32(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_avx_cmple_int32(r0, r1);
}
rvm<int16_t,1> cmple_int16(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_avx_cmple_int16(r0, r1);
}
rvm<int8_t,1> cmple_int8(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_avx_cmple_int8(r0, r1);
}
rvm<uint64_t,1> cmple_uint64(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_avx_cmple_uint64(r0, r1);
}
rvm<uint32_t,1> cmple_uint32(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_avx_cmple_uint32(r0, r1);
}
rvm<uint16_t,1> cmple_uint16(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_avx_cmple_uint16(r0, r1);
}
rvm<uint8_t,1> cmple_uint8(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_avx_cmple_uint8(r0, r1);
}
rvm<float64_t,1> cmpge_float64(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_avx_cmpge_float64(r0, r1);
}
rvm<float32_t,1> cmpge_float32(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_avx_cmpge_float32(r0, r1);
}
rvm<int64_t,1> cmpge_int64(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_avx_cmpge_int64(r0, r1);
}
rvm<int32_t,1> cmpge_int32(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_avx_cmpge_int32(r0, r1);
}
rvm<int16_t,1> cmpge_int16(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_avx_cmpge_int16(r0, r1);
}
rvm<int8_t,1> cmpge_int8(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_avx_cmpge_int8(r0, r1);
}
rvm<uint64_t,1> cmpge_uint64(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_avx_cmpge_uint64(r0, r1);
}
rvm<uint32_t,1> cmpge_uint32(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_avx_cmpge_uint32(r0, r1);
}
rvm<uint16_t,1> cmpge_uint16(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_avx_cmpge_uint16(r0, r1);
}
rvm<uint8_t,1> cmpge_uint8(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_avx_cmpge_uint8(r0, r1);
}
rvm<float64_t,1> cmpgt_float64(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_avx_cmpgt_float64(r0, r1);
}
rvm<float32_t,1> cmpgt_float32(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_avx_cmpgt_float32(r0, r1);
}
rvm<int64_t,1> cmpgt_int64(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_avx_cmpgt_int64(r0, r1);
}
rvm<int32_t,1> cmpgt_int32(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_avx_cmpgt_int32(r0, r1);
}
rvm<int16_t,1> cmpgt_int16(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_avx_cmpgt_int16(r0, r1);
}
rvm<int8_t,1> cmpgt_int8(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_avx_cmpgt_int8(r0, r1);
}
rvm<uint64_t,1> cmpgt_uint64(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_avx_cmpgt_uint64(r0, r1);
}
rvm<uint32_t,1> cmpgt_uint32(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_avx_cmpgt_uint32(r0, r1);
}
rvm<uint16_t,1> cmpgt_uint16(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_avx_cmpgt_uint16(r0, r1);
}
rvm<uint8_t,1> cmpgt_uint8(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_avx_cmpgt_uint8(r0, r1);
}
float64_t round_float64(const rvd<float64_t,1> r0) {
	return mipp_avx_round_float64(r0);
}
float32_t round_float32(const rvd<float32_t,1> r0) {
	return mipp_avx_round_float32(r0);
}
int64_t round_int64(const rvd<int64_t,1> r0) {
	return mipp_avx_round_int64(r0);
}
int32_t round_int32(const rvd<int32_t,1> r0) {
	return mipp_avx_round_int32(r0);
}
int16_t round_int16(const rvd<int16_t,1> r0) {
	return mipp_avx_round_int16(r0);
}
int8_t round_int8(const rvd<int8_t,1> r0) {
	return mipp_avx_round_int8(r0);
}
uint64_t round_uint64(const rvd<uint64_t,1> r0) {
	return mipp_avx_round_uint64(r0);
}
uint32_t round_uint32(const rvd<uint32_t,1> r0) {
	return mipp_avx_round_uint32(r0);
}
uint16_t round_uint16(const rvd<uint16_t,1> r0) {
	return mipp_avx_round_uint16(r0);
}
uint8_t round_uint8(const rvd<uint8_t,1> r0) {
	return mipp_avx_round_uint8(r0);
}
rvd<float64_t,1> blend_float64(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1, const rvm<float64_t,1> m0) {
	return mipp_avx_blend_float64(r0, r1, m0);
}
rvd<float32_t,1> blend_float32(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1, const rvm<float32_t,1> m0) {
	return mipp_avx_blend_float32(r0, r1, m0);
}
rvd<int64_t,1> blend_int64(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1, const rvm<int64_t,1> m0) {
	return mipp_avx_blend_int64(r0, r1, m0);
}
rvd<int32_t,1> blend_int32(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1, const rvm<int32_t,1> m0) {
	return mipp_avx_blend_int32(r0, r1, m0);
}
rvd<int16_t,1> blend_int16(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1, const rvm<int16_t,1> m0) {
	return mipp_avx_blend_int16(r0, r1, m0);
}
rvd<int8_t,1> blend_int8(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1, const rvm<int8_t,1> m0) {
	return mipp_avx_blend_int8(r0, r1, m0);
}
rvd<uint64_t,1> blend_uint64(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1, const rvm<uint64_t,1> m0) {
	return mipp_avx_blend_uint64(r0, r1, m0);
}
rvd<uint32_t,1> blend_uint32(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1, const rvm<uint32_t,1> m0) {
	return mipp_avx_blend_uint32(r0, r1, m0);
}
rvd<uint16_t,1> blend_uint16(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1, const rvm<uint16_t,1> m0) {
	return mipp_avx_blend_uint16(r0, r1, m0);
}
rvd<uint8_t,1> blend_uint8(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1, const rvm<uint8_t,1> m0) {
	return mipp_avx_blend_uint8(r0, r1, m0);
}
int32_t testz_float64(const rvm<float64_t,1> m0, const rvm<float64_t,1> m1) {
	return mipp_avx_testz_float64(m0, m1);
}
int32_t testz_float32(const rvm<float32_t,1> m0, const rvm<float32_t,1> m1) {
	return mipp_avx_testz_float32(m0, m1);
}
int32_t testz_int64(const rvm<int64_t,1> m0, const rvm<int64_t,1> m1) {
	return mipp_avx_testz_int64(m0, m1);
}
int32_t testz_int32(const rvm<int32_t,1> m0, const rvm<int32_t,1> m1) {
	return mipp_avx_testz_int32(m0, m1);
}
int32_t testz_int16(const rvm<int16_t,1> m0, const rvm<int16_t,1> m1) {
	return mipp_avx_testz_int16(m0, m1);
}
int32_t testz_int8(const rvm<int8_t,1> m0, const rvm<int8_t,1> m1) {
	return mipp_avx_testz_int8(m0, m1);
}
int32_t testz_uint64(const rvm<uint64_t,1> m0, const rvm<uint64_t,1> m1) {
	return mipp_avx_testz_uint64(m0, m1);
}
int32_t testz_uint32(const rvm<uint32_t,1> m0, const rvm<uint32_t,1> m1) {
	return mipp_avx_testz_uint32(m0, m1);
}
int32_t testz_uint16(const rvm<uint16_t,1> m0, const rvm<uint16_t,1> m1) {
	return mipp_avx_testz_uint16(m0, m1);
}
int32_t testz_uint8(const rvm<uint8_t,1> m0, const rvm<uint8_t,1> m1) {
	return mipp_avx_testz_uint8(m0, m1);
}
int32_t testz_2_float64(const rvm<float64_t,1> m0) {
	return mipp_avx_testz_2_float64(m0);
}
int32_t testz_2_float32(const rvm<float32_t,1> m0) {
	return mipp_avx_testz_2_float32(m0);
}
int32_t testz_2_int64(const rvm<int64_t,1> m0) {
	return mipp_avx_testz_2_int64(m0);
}
int32_t testz_2_int32(const rvm<int32_t,1> m0) {
	return mipp_avx_testz_2_int32(m0);
}
int32_t testz_2_int16(const rvm<int16_t,1> m0) {
	return mipp_avx_testz_2_int16(m0);
}
int32_t testz_2_int8(const rvm<int8_t,1> m0) {
	return mipp_avx_testz_2_int8(m0);
}
int32_t testz_2_uint64(const rvm<uint64_t,1> m0) {
	return mipp_avx_testz_2_uint64(m0);
}
int32_t testz_2_uint32(const rvm<uint32_t,1> m0) {
	return mipp_avx_testz_2_uint32(m0);
}
int32_t testz_2_uint16(const rvm<uint16_t,1> m0) {
	return mipp_avx_testz_2_uint16(m0);
}
int32_t testz_2_uint8(const rvm<uint8_t,1> m0) {
	return mipp_avx_testz_2_uint8(m0);
}
rvd<float64_t,1> hadd_float64(const rvd<float64_t,1> r0) {
	return mipp_avx_hadd_float64(r0);
}
rvd<float32_t,1> hadd_float32(const rvd<float32_t,1> r0) {
	return mipp_avx_hadd_float32(r0);
}
rvd<int64_t,1> hadd_int64(const rvd<int64_t,1> r0) {
	return mipp_avx_hadd_int64(r0);
}
rvd<int32_t,1> hadd_int32(const rvd<int32_t,1> r0) {
	return mipp_avx_hadd_int32(r0);
}
rvd<int16_t,1> hadd_int16(const rvd<int16_t,1> r0) {
	return mipp_avx_hadd_int16(r0);
}
rvd<int8_t,1> hadd_int8(const rvd<int8_t,1> r0) {
	return mipp_avx_hadd_int8(r0);
}
rvd<uint64_t,1> hadd_uint64(const rvd<uint64_t,1> r0) {
	return mipp_avx_hadd_uint64(r0);
}
rvd<uint32_t,1> hadd_uint32(const rvd<uint32_t,1> r0) {
	return mipp_avx_hadd_uint32(r0);
}
rvd<uint16_t,1> hadd_uint16(const rvd<uint16_t,1> r0) {
	return mipp_avx_hadd_uint16(r0);
}
rvd<uint8_t,1> hadd_uint8(const rvd<uint8_t,1> r0) {
	return mipp_avx_hadd_uint8(r0);
}
rvd<float64_t,1> hmul_float64(const rvd<float64_t,1> r0) {
	return mipp_avx_hmul_float64(r0);
}
rvd<float32_t,1> hmul_float32(const rvd<float32_t,1> r0) {
	return mipp_avx_hmul_float32(r0);
}
rvd<int64_t,1> hmul_int64(const rvd<int64_t,1> r0) {
	return mipp_avx_hmul_int64(r0);
}
rvd<int32_t,1> hmul_int32(const rvd<int32_t,1> r0) {
	return mipp_avx_hmul_int32(r0);
}
rvd<int16_t,1> hmul_int16(const rvd<int16_t,1> r0) {
	return mipp_avx_hmul_int16(r0);
}
rvd<int8_t,1> hmul_int8(const rvd<int8_t,1> r0) {
	return mipp_avx_hmul_int8(r0);
}
rvd<uint64_t,1> hmul_uint64(const rvd<uint64_t,1> r0) {
	return mipp_avx_hmul_uint64(r0);
}
rvd<uint32_t,1> hmul_uint32(const rvd<uint32_t,1> r0) {
	return mipp_avx_hmul_uint32(r0);
}
rvd<uint16_t,1> hmul_uint16(const rvd<uint16_t,1> r0) {
	return mipp_avx_hmul_uint16(r0);
}
rvd<uint8_t,1> hmul_uint8(const rvd<uint8_t,1> r0) {
	return mipp_avx_hmul_uint8(r0);
}
rvd<float64_t,1> hmin_float64(const rvd<float64_t,1> r0) {
	return mipp_avx_hmin_float64(r0);
}
rvd<float32_t,1> hmin_float32(const rvd<float32_t,1> r0) {
	return mipp_avx_hmin_float32(r0);
}
rvd<int64_t,1> hmin_int64(const rvd<int64_t,1> r0) {
	return mipp_avx_hmin_int64(r0);
}
rvd<int32_t,1> hmin_int32(const rvd<int32_t,1> r0) {
	return mipp_avx_hmin_int32(r0);
}
rvd<int16_t,1> hmin_int16(const rvd<int16_t,1> r0) {
	return mipp_avx_hmin_int16(r0);
}
rvd<int8_t,1> hmin_int8(const rvd<int8_t,1> r0) {
	return mipp_avx_hmin_int8(r0);
}
rvd<uint64_t,1> hmin_uint64(const rvd<uint64_t,1> r0) {
	return mipp_avx_hmin_uint64(r0);
}
rvd<uint32_t,1> hmin_uint32(const rvd<uint32_t,1> r0) {
	return mipp_avx_hmin_uint32(r0);
}
rvd<uint16_t,1> hmin_uint16(const rvd<uint16_t,1> r0) {
	return mipp_avx_hmin_uint16(r0);
}
rvd<uint8_t,1> hmin_uint8(const rvd<uint8_t,1> r0) {
	return mipp_avx_hmin_uint8(r0);
}
rvd<float64_t,1> hmax_float64(const rvd<float64_t,1> r0) {
	return mipp_avx_hmax_float64(r0);
}
rvd<float32_t,1> hmax_float32(const rvd<float32_t,1> r0) {
	return mipp_avx_hmax_float32(r0);
}
rvd<int64_t,1> hmax_int64(const rvd<int64_t,1> r0) {
	return mipp_avx_hmax_int64(r0);
}
rvd<int32_t,1> hmax_int32(const rvd<int32_t,1> r0) {
	return mipp_avx_hmax_int32(r0);
}
rvd<int16_t,1> hmax_int16(const rvd<int16_t,1> r0) {
	return mipp_avx_hmax_int16(r0);
}
rvd<int8_t,1> hmax_int8(const rvd<int8_t,1> r0) {
	return mipp_avx_hmax_int8(r0);
}
rvd<uint64_t,1> hmax_uint64(const rvd<uint64_t,1> r0) {
	return mipp_avx_hmax_uint64(r0);
}
rvd<uint32_t,1> hmax_uint32(const rvd<uint32_t,1> r0) {
	return mipp_avx_hmax_uint32(r0);
}
rvd<uint16_t,1> hmax_uint16(const rvd<uint16_t,1> r0) {
	return mipp_avx_hmax_uint16(r0);
}
rvd<uint8_t,1> hmax_uint8(const rvd<uint8_t,1> r0) {
	return mipp_avx_hmax_uint8(r0);
}
}

#endif /* MY_INTRINSICS_PLUS_PLUS_HPP_ */
