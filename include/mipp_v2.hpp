#ifndef MY_INTRINSICS_PLUS_PLUS_HPP_
#define MY_INTRINSICS_PLUS_PLUS_HPP_

#include "mipp_v2_interface_gen.h"

namespace mipp
{
// should throw an exception
template<typename T, int LMUL=1> struct rvd_type{};
template<> struct rvd_type<float64_t, 1>{ using type = rvd_float64_m1_t; };
template<> struct rvd_type<float32_t, 1>{ using type = rvd_float32_m1_t; };
template<> struct rvd_type<int64_t, 1>{ using type = rvd_int64_m1_t; };
template<> struct rvd_type<int32_t, 1>{ using type = rvd_int32_m1_t; };
template<> struct rvd_type<int16_t, 1>{ using type = rvd_int16_m1_t; };
template<> struct rvd_type<int8_t, 1>{ using type = rvd_int8_m1_t; };
template<> struct rvd_type<uint64_t, 1>{ using type = rvd_uint64_m1_t; };
template<> struct rvd_type<uint32_t, 1>{ using type = rvd_uint32_m1_t; };
template<> struct rvd_type<uint16_t, 1>{ using type = rvd_uint16_m1_t; };
template<> struct rvd_type<uint8_t, 1>{ using type = rvd_uint8_m1_t; };
template<> struct rvd_type<float64_t, 2>{ using type = rvd_float64_m2_t; };
template<> struct rvd_type<float32_t, 2>{ using type = rvd_float32_m2_t; };
template<> struct rvd_type<int64_t, 2>{ using type = rvd_int64_m2_t; };
template<> struct rvd_type<int32_t, 2>{ using type = rvd_int32_m2_t; };
template<> struct rvd_type<int16_t, 2>{ using type = rvd_int16_m2_t; };
template<> struct rvd_type<int8_t, 2>{ using type = rvd_int8_m2_t; };
template<> struct rvd_type<uint64_t, 2>{ using type = rvd_uint64_m2_t; };
template<> struct rvd_type<uint32_t, 2>{ using type = rvd_uint32_m2_t; };
template<> struct rvd_type<uint16_t, 2>{ using type = rvd_uint16_m2_t; };
template<> struct rvd_type<uint8_t, 2>{ using type = rvd_uint8_m2_t; };
template<> struct rvd_type<float64_t, 4>{ using type = rvd_float64_m4_t; };
template<> struct rvd_type<float32_t, 4>{ using type = rvd_float32_m4_t; };
template<> struct rvd_type<int64_t, 4>{ using type = rvd_int64_m4_t; };
template<> struct rvd_type<int32_t, 4>{ using type = rvd_int32_m4_t; };
template<> struct rvd_type<int16_t, 4>{ using type = rvd_int16_m4_t; };
template<> struct rvd_type<int8_t, 4>{ using type = rvd_int8_m4_t; };
template<> struct rvd_type<uint64_t, 4>{ using type = rvd_uint64_m4_t; };
template<> struct rvd_type<uint32_t, 4>{ using type = rvd_uint32_m4_t; };
template<> struct rvd_type<uint16_t, 4>{ using type = rvd_uint16_m4_t; };
template<> struct rvd_type<uint8_t, 4>{ using type = rvd_uint8_m4_t; };
template<> struct rvd_type<float64_t, 8>{ using type = rvd_float64_m8_t; };
template<> struct rvd_type<float32_t, 8>{ using type = rvd_float32_m8_t; };
template<> struct rvd_type<int64_t, 8>{ using type = rvd_int64_m8_t; };
template<> struct rvd_type<int32_t, 8>{ using type = rvd_int32_m8_t; };
template<> struct rvd_type<int16_t, 8>{ using type = rvd_int16_m8_t; };
template<> struct rvd_type<int8_t, 8>{ using type = rvd_int8_m8_t; };
template<> struct rvd_type<uint64_t, 8>{ using type = rvd_uint64_m8_t; };
template<> struct rvd_type<uint32_t, 8>{ using type = rvd_uint32_m8_t; };
template<> struct rvd_type<uint16_t, 8>{ using type = rvd_uint16_m8_t; };
template<> struct rvd_type<uint8_t, 8>{ using type = rvd_uint8_m8_t; };
template <typename T, int LMUL=1> using rvd = typename rvd_type<T,LMUL>::type;
// should throw an exception
template<typename T, int LMUL=1> struct rvm_type{};
template<> struct rvm_type<float64_t, 1>{ using type = rvm_float64_m1_t; };
template<> struct rvm_type<float32_t, 1>{ using type = rvm_float32_m1_t; };
template<> struct rvm_type<int64_t, 1>{ using type = rvm_int64_m1_t; };
template<> struct rvm_type<int32_t, 1>{ using type = rvm_int32_m1_t; };
template<> struct rvm_type<int16_t, 1>{ using type = rvm_int16_m1_t; };
template<> struct rvm_type<int8_t, 1>{ using type = rvm_int8_m1_t; };
template<> struct rvm_type<uint64_t, 1>{ using type = rvm_uint64_m1_t; };
template<> struct rvm_type<uint32_t, 1>{ using type = rvm_uint32_m1_t; };
template<> struct rvm_type<uint16_t, 1>{ using type = rvm_uint16_m1_t; };
template<> struct rvm_type<uint8_t, 1>{ using type = rvm_uint8_m1_t; };
template<> struct rvm_type<float64_t, 2>{ using type = rvm_float64_m2_t; };
template<> struct rvm_type<float32_t, 2>{ using type = rvm_float32_m2_t; };
template<> struct rvm_type<int64_t, 2>{ using type = rvm_int64_m2_t; };
template<> struct rvm_type<int32_t, 2>{ using type = rvm_int32_m2_t; };
template<> struct rvm_type<int16_t, 2>{ using type = rvm_int16_m2_t; };
template<> struct rvm_type<int8_t, 2>{ using type = rvm_int8_m2_t; };
template<> struct rvm_type<uint64_t, 2>{ using type = rvm_uint64_m2_t; };
template<> struct rvm_type<uint32_t, 2>{ using type = rvm_uint32_m2_t; };
template<> struct rvm_type<uint16_t, 2>{ using type = rvm_uint16_m2_t; };
template<> struct rvm_type<uint8_t, 2>{ using type = rvm_uint8_m2_t; };
template<> struct rvm_type<float64_t, 4>{ using type = rvm_float64_m4_t; };
template<> struct rvm_type<float32_t, 4>{ using type = rvm_float32_m4_t; };
template<> struct rvm_type<int64_t, 4>{ using type = rvm_int64_m4_t; };
template<> struct rvm_type<int32_t, 4>{ using type = rvm_int32_m4_t; };
template<> struct rvm_type<int16_t, 4>{ using type = rvm_int16_m4_t; };
template<> struct rvm_type<int8_t, 4>{ using type = rvm_int8_m4_t; };
template<> struct rvm_type<uint64_t, 4>{ using type = rvm_uint64_m4_t; };
template<> struct rvm_type<uint32_t, 4>{ using type = rvm_uint32_m4_t; };
template<> struct rvm_type<uint16_t, 4>{ using type = rvm_uint16_m4_t; };
template<> struct rvm_type<uint8_t, 4>{ using type = rvm_uint8_m4_t; };
template<> struct rvm_type<float64_t, 8>{ using type = rvm_float64_m8_t; };
template<> struct rvm_type<float32_t, 8>{ using type = rvm_float32_m8_t; };
template<> struct rvm_type<int64_t, 8>{ using type = rvm_int64_m8_t; };
template<> struct rvm_type<int32_t, 8>{ using type = rvm_int32_m8_t; };
template<> struct rvm_type<int16_t, 8>{ using type = rvm_int16_m8_t; };
template<> struct rvm_type<int8_t, 8>{ using type = rvm_int8_m8_t; };
template<> struct rvm_type<uint64_t, 8>{ using type = rvm_uint64_m8_t; };
template<> struct rvm_type<uint32_t, 8>{ using type = rvm_uint32_m8_t; };
template<> struct rvm_type<uint16_t, 8>{ using type = rvm_uint16_m8_t; };
template<> struct rvm_type<uint8_t, 8>{ using type = rvm_uint8_m8_t; };
template <typename T, int LMUL=1> using rvm = typename rvm_type<T,LMUL>::type;
// should throw an exception
template<typename T, int LMUL=1> constexpr uint32_t N(){ return 0; }
template<> constexpr uint32_t N<float64_t, 1>(){ return MIPP_N_FLOAT64; }
template<> constexpr uint32_t N<float32_t, 1>(){ return MIPP_N_FLOAT32; }
template<> constexpr uint32_t N<int64_t, 1>(){ return MIPP_N_INT64; }
template<> constexpr uint32_t N<int32_t, 1>(){ return MIPP_N_INT32; }
template<> constexpr uint32_t N<int16_t, 1>(){ return MIPP_N_INT16; }
template<> constexpr uint32_t N<int8_t, 1>(){ return MIPP_N_INT8; }
template<> constexpr uint32_t N<uint64_t, 1>(){ return MIPP_N_UINT64; }
template<> constexpr uint32_t N<uint32_t, 1>(){ return MIPP_N_UINT32; }
template<> constexpr uint32_t N<uint16_t, 1>(){ return MIPP_N_UINT16; }
template<> constexpr uint32_t N<uint8_t, 1>(){ return MIPP_N_UINT8; }
template<> constexpr uint32_t N<float64_t, 2>(){ return MIPP_N_FLOAT64; }
template<> constexpr uint32_t N<float32_t, 2>(){ return MIPP_N_FLOAT32; }
template<> constexpr uint32_t N<int64_t, 2>(){ return MIPP_N_INT64; }
template<> constexpr uint32_t N<int32_t, 2>(){ return MIPP_N_INT32; }
template<> constexpr uint32_t N<int16_t, 2>(){ return MIPP_N_INT16; }
template<> constexpr uint32_t N<int8_t, 2>(){ return MIPP_N_INT8; }
template<> constexpr uint32_t N<uint64_t, 2>(){ return MIPP_N_UINT64; }
template<> constexpr uint32_t N<uint32_t, 2>(){ return MIPP_N_UINT32; }
template<> constexpr uint32_t N<uint16_t, 2>(){ return MIPP_N_UINT16; }
template<> constexpr uint32_t N<uint8_t, 2>(){ return MIPP_N_UINT8; }
template<> constexpr uint32_t N<float64_t, 4>(){ return MIPP_N_FLOAT64; }
template<> constexpr uint32_t N<float32_t, 4>(){ return MIPP_N_FLOAT32; }
template<> constexpr uint32_t N<int64_t, 4>(){ return MIPP_N_INT64; }
template<> constexpr uint32_t N<int32_t, 4>(){ return MIPP_N_INT32; }
template<> constexpr uint32_t N<int16_t, 4>(){ return MIPP_N_INT16; }
template<> constexpr uint32_t N<int8_t, 4>(){ return MIPP_N_INT8; }
template<> constexpr uint32_t N<uint64_t, 4>(){ return MIPP_N_UINT64; }
template<> constexpr uint32_t N<uint32_t, 4>(){ return MIPP_N_UINT32; }
template<> constexpr uint32_t N<uint16_t, 4>(){ return MIPP_N_UINT16; }
template<> constexpr uint32_t N<uint8_t, 4>(){ return MIPP_N_UINT8; }
template<> constexpr uint32_t N<float64_t, 8>(){ return MIPP_N_FLOAT64; }
template<> constexpr uint32_t N<float32_t, 8>(){ return MIPP_N_FLOAT32; }
template<> constexpr uint32_t N<int64_t, 8>(){ return MIPP_N_INT64; }
template<> constexpr uint32_t N<int32_t, 8>(){ return MIPP_N_INT32; }
template<> constexpr uint32_t N<int16_t, 8>(){ return MIPP_N_INT16; }
template<> constexpr uint32_t N<int8_t, 8>(){ return MIPP_N_INT8; }
template<> constexpr uint32_t N<uint64_t, 8>(){ return MIPP_N_UINT64; }
template<> constexpr uint32_t N<uint32_t, 8>(){ return MIPP_N_UINT32; }
template<> constexpr uint32_t N<uint16_t, 8>(){ return MIPP_N_UINT16; }
template<> constexpr uint32_t N<uint8_t, 8>(){ return MIPP_N_UINT8; }
inline rvd<float64_t,1> cast_float64(const rvd<float64_t,1> r0) {
	return mipp_cast_float64_float64_m1(r0);
}
inline rvd<float64_t,2> cast_float64(const rvd<float64_t,2> r0) {
	return mipp_cast_float64_float64_m2(r0);
}
inline rvd<float64_t,4> cast_float64(const rvd<float64_t,4> r0) {
	return mipp_cast_float64_float64_m4(r0);
}
inline rvd<float64_t,8> cast_float64(const rvd<float64_t,8> r0) {
	return mipp_cast_float64_float64_m8(r0);
}
inline rvd<float64_t,1> cast_float64(const rvd<float32_t,1> r0) {
	return mipp_cast_float32_float64_m1(r0);
}
inline rvd<float64_t,2> cast_float64(const rvd<float32_t,2> r0) {
	return mipp_cast_float32_float64_m2(r0);
}
inline rvd<float64_t,4> cast_float64(const rvd<float32_t,4> r0) {
	return mipp_cast_float32_float64_m4(r0);
}
inline rvd<float64_t,8> cast_float64(const rvd<float32_t,8> r0) {
	return mipp_cast_float32_float64_m8(r0);
}
inline rvd<float64_t,1> cast_float64(const rvd<int64_t,1> r0) {
	return mipp_cast_int64_float64_m1(r0);
}
inline rvd<float64_t,2> cast_float64(const rvd<int64_t,2> r0) {
	return mipp_cast_int64_float64_m2(r0);
}
inline rvd<float64_t,4> cast_float64(const rvd<int64_t,4> r0) {
	return mipp_cast_int64_float64_m4(r0);
}
inline rvd<float64_t,8> cast_float64(const rvd<int64_t,8> r0) {
	return mipp_cast_int64_float64_m8(r0);
}
inline rvd<float64_t,1> cast_float64(const rvd<int32_t,1> r0) {
	return mipp_cast_int32_float64_m1(r0);
}
inline rvd<float64_t,2> cast_float64(const rvd<int32_t,2> r0) {
	return mipp_cast_int32_float64_m2(r0);
}
inline rvd<float64_t,4> cast_float64(const rvd<int32_t,4> r0) {
	return mipp_cast_int32_float64_m4(r0);
}
inline rvd<float64_t,8> cast_float64(const rvd<int32_t,8> r0) {
	return mipp_cast_int32_float64_m8(r0);
}
inline rvd<float64_t,1> cast_float64(const rvd<int16_t,1> r0) {
	return mipp_cast_int16_float64_m1(r0);
}
inline rvd<float64_t,2> cast_float64(const rvd<int16_t,2> r0) {
	return mipp_cast_int16_float64_m2(r0);
}
inline rvd<float64_t,4> cast_float64(const rvd<int16_t,4> r0) {
	return mipp_cast_int16_float64_m4(r0);
}
inline rvd<float64_t,8> cast_float64(const rvd<int16_t,8> r0) {
	return mipp_cast_int16_float64_m8(r0);
}
inline rvd<float64_t,1> cast_float64(const rvd<int8_t,1> r0) {
	return mipp_cast_int8_float64_m1(r0);
}
inline rvd<float64_t,2> cast_float64(const rvd<int8_t,2> r0) {
	return mipp_cast_int8_float64_m2(r0);
}
inline rvd<float64_t,4> cast_float64(const rvd<int8_t,4> r0) {
	return mipp_cast_int8_float64_m4(r0);
}
inline rvd<float64_t,8> cast_float64(const rvd<int8_t,8> r0) {
	return mipp_cast_int8_float64_m8(r0);
}
inline rvd<float64_t,1> cast_float64(const rvd<uint64_t,1> r0) {
	return mipp_cast_uint64_float64_m1(r0);
}
inline rvd<float64_t,2> cast_float64(const rvd<uint64_t,2> r0) {
	return mipp_cast_uint64_float64_m2(r0);
}
inline rvd<float64_t,4> cast_float64(const rvd<uint64_t,4> r0) {
	return mipp_cast_uint64_float64_m4(r0);
}
inline rvd<float64_t,8> cast_float64(const rvd<uint64_t,8> r0) {
	return mipp_cast_uint64_float64_m8(r0);
}
inline rvd<float64_t,1> cast_float64(const rvd<uint32_t,1> r0) {
	return mipp_cast_uint32_float64_m1(r0);
}
inline rvd<float64_t,2> cast_float64(const rvd<uint32_t,2> r0) {
	return mipp_cast_uint32_float64_m2(r0);
}
inline rvd<float64_t,4> cast_float64(const rvd<uint32_t,4> r0) {
	return mipp_cast_uint32_float64_m4(r0);
}
inline rvd<float64_t,8> cast_float64(const rvd<uint32_t,8> r0) {
	return mipp_cast_uint32_float64_m8(r0);
}
inline rvd<float64_t,1> cast_float64(const rvd<uint16_t,1> r0) {
	return mipp_cast_uint16_float64_m1(r0);
}
inline rvd<float64_t,2> cast_float64(const rvd<uint16_t,2> r0) {
	return mipp_cast_uint16_float64_m2(r0);
}
inline rvd<float64_t,4> cast_float64(const rvd<uint16_t,4> r0) {
	return mipp_cast_uint16_float64_m4(r0);
}
inline rvd<float64_t,8> cast_float64(const rvd<uint16_t,8> r0) {
	return mipp_cast_uint16_float64_m8(r0);
}
inline rvd<float64_t,1> cast_float64(const rvd<uint8_t,1> r0) {
	return mipp_cast_uint8_float64_m1(r0);
}
inline rvd<float64_t,2> cast_float64(const rvd<uint8_t,2> r0) {
	return mipp_cast_uint8_float64_m2(r0);
}
inline rvd<float64_t,4> cast_float64(const rvd<uint8_t,4> r0) {
	return mipp_cast_uint8_float64_m4(r0);
}
inline rvd<float64_t,8> cast_float64(const rvd<uint8_t,8> r0) {
	return mipp_cast_uint8_float64_m8(r0);
}
inline rvd<float32_t,1> cast_float32(const rvd<float64_t,1> r0) {
	return mipp_cast_float64_float32_m1(r0);
}
inline rvd<float32_t,2> cast_float32(const rvd<float64_t,2> r0) {
	return mipp_cast_float64_float32_m2(r0);
}
inline rvd<float32_t,4> cast_float32(const rvd<float64_t,4> r0) {
	return mipp_cast_float64_float32_m4(r0);
}
inline rvd<float32_t,8> cast_float32(const rvd<float64_t,8> r0) {
	return mipp_cast_float64_float32_m8(r0);
}
inline rvd<float32_t,1> cast_float32(const rvd<float32_t,1> r0) {
	return mipp_cast_float32_float32_m1(r0);
}
inline rvd<float32_t,2> cast_float32(const rvd<float32_t,2> r0) {
	return mipp_cast_float32_float32_m2(r0);
}
inline rvd<float32_t,4> cast_float32(const rvd<float32_t,4> r0) {
	return mipp_cast_float32_float32_m4(r0);
}
inline rvd<float32_t,8> cast_float32(const rvd<float32_t,8> r0) {
	return mipp_cast_float32_float32_m8(r0);
}
inline rvd<float32_t,1> cast_float32(const rvd<int64_t,1> r0) {
	return mipp_cast_int64_float32_m1(r0);
}
inline rvd<float32_t,2> cast_float32(const rvd<int64_t,2> r0) {
	return mipp_cast_int64_float32_m2(r0);
}
inline rvd<float32_t,4> cast_float32(const rvd<int64_t,4> r0) {
	return mipp_cast_int64_float32_m4(r0);
}
inline rvd<float32_t,8> cast_float32(const rvd<int64_t,8> r0) {
	return mipp_cast_int64_float32_m8(r0);
}
inline rvd<float32_t,1> cast_float32(const rvd<int32_t,1> r0) {
	return mipp_cast_int32_float32_m1(r0);
}
inline rvd<float32_t,2> cast_float32(const rvd<int32_t,2> r0) {
	return mipp_cast_int32_float32_m2(r0);
}
inline rvd<float32_t,4> cast_float32(const rvd<int32_t,4> r0) {
	return mipp_cast_int32_float32_m4(r0);
}
inline rvd<float32_t,8> cast_float32(const rvd<int32_t,8> r0) {
	return mipp_cast_int32_float32_m8(r0);
}
inline rvd<float32_t,1> cast_float32(const rvd<int16_t,1> r0) {
	return mipp_cast_int16_float32_m1(r0);
}
inline rvd<float32_t,2> cast_float32(const rvd<int16_t,2> r0) {
	return mipp_cast_int16_float32_m2(r0);
}
inline rvd<float32_t,4> cast_float32(const rvd<int16_t,4> r0) {
	return mipp_cast_int16_float32_m4(r0);
}
inline rvd<float32_t,8> cast_float32(const rvd<int16_t,8> r0) {
	return mipp_cast_int16_float32_m8(r0);
}
inline rvd<float32_t,1> cast_float32(const rvd<int8_t,1> r0) {
	return mipp_cast_int8_float32_m1(r0);
}
inline rvd<float32_t,2> cast_float32(const rvd<int8_t,2> r0) {
	return mipp_cast_int8_float32_m2(r0);
}
inline rvd<float32_t,4> cast_float32(const rvd<int8_t,4> r0) {
	return mipp_cast_int8_float32_m4(r0);
}
inline rvd<float32_t,8> cast_float32(const rvd<int8_t,8> r0) {
	return mipp_cast_int8_float32_m8(r0);
}
inline rvd<float32_t,1> cast_float32(const rvd<uint64_t,1> r0) {
	return mipp_cast_uint64_float32_m1(r0);
}
inline rvd<float32_t,2> cast_float32(const rvd<uint64_t,2> r0) {
	return mipp_cast_uint64_float32_m2(r0);
}
inline rvd<float32_t,4> cast_float32(const rvd<uint64_t,4> r0) {
	return mipp_cast_uint64_float32_m4(r0);
}
inline rvd<float32_t,8> cast_float32(const rvd<uint64_t,8> r0) {
	return mipp_cast_uint64_float32_m8(r0);
}
inline rvd<float32_t,1> cast_float32(const rvd<uint32_t,1> r0) {
	return mipp_cast_uint32_float32_m1(r0);
}
inline rvd<float32_t,2> cast_float32(const rvd<uint32_t,2> r0) {
	return mipp_cast_uint32_float32_m2(r0);
}
inline rvd<float32_t,4> cast_float32(const rvd<uint32_t,4> r0) {
	return mipp_cast_uint32_float32_m4(r0);
}
inline rvd<float32_t,8> cast_float32(const rvd<uint32_t,8> r0) {
	return mipp_cast_uint32_float32_m8(r0);
}
inline rvd<float32_t,1> cast_float32(const rvd<uint16_t,1> r0) {
	return mipp_cast_uint16_float32_m1(r0);
}
inline rvd<float32_t,2> cast_float32(const rvd<uint16_t,2> r0) {
	return mipp_cast_uint16_float32_m2(r0);
}
inline rvd<float32_t,4> cast_float32(const rvd<uint16_t,4> r0) {
	return mipp_cast_uint16_float32_m4(r0);
}
inline rvd<float32_t,8> cast_float32(const rvd<uint16_t,8> r0) {
	return mipp_cast_uint16_float32_m8(r0);
}
inline rvd<float32_t,1> cast_float32(const rvd<uint8_t,1> r0) {
	return mipp_cast_uint8_float32_m1(r0);
}
inline rvd<float32_t,2> cast_float32(const rvd<uint8_t,2> r0) {
	return mipp_cast_uint8_float32_m2(r0);
}
inline rvd<float32_t,4> cast_float32(const rvd<uint8_t,4> r0) {
	return mipp_cast_uint8_float32_m4(r0);
}
inline rvd<float32_t,8> cast_float32(const rvd<uint8_t,8> r0) {
	return mipp_cast_uint8_float32_m8(r0);
}
inline rvd<int64_t,1> cast_int64(const rvd<float64_t,1> r0) {
	return mipp_cast_float64_int64_m1(r0);
}
inline rvd<int64_t,2> cast_int64(const rvd<float64_t,2> r0) {
	return mipp_cast_float64_int64_m2(r0);
}
inline rvd<int64_t,4> cast_int64(const rvd<float64_t,4> r0) {
	return mipp_cast_float64_int64_m4(r0);
}
inline rvd<int64_t,8> cast_int64(const rvd<float64_t,8> r0) {
	return mipp_cast_float64_int64_m8(r0);
}
inline rvd<int64_t,1> cast_int64(const rvd<float32_t,1> r0) {
	return mipp_cast_float32_int64_m1(r0);
}
inline rvd<int64_t,2> cast_int64(const rvd<float32_t,2> r0) {
	return mipp_cast_float32_int64_m2(r0);
}
inline rvd<int64_t,4> cast_int64(const rvd<float32_t,4> r0) {
	return mipp_cast_float32_int64_m4(r0);
}
inline rvd<int64_t,8> cast_int64(const rvd<float32_t,8> r0) {
	return mipp_cast_float32_int64_m8(r0);
}
inline rvd<int64_t,1> cast_int64(const rvd<int64_t,1> r0) {
	return mipp_cast_int64_int64_m1(r0);
}
inline rvd<int64_t,2> cast_int64(const rvd<int64_t,2> r0) {
	return mipp_cast_int64_int64_m2(r0);
}
inline rvd<int64_t,4> cast_int64(const rvd<int64_t,4> r0) {
	return mipp_cast_int64_int64_m4(r0);
}
inline rvd<int64_t,8> cast_int64(const rvd<int64_t,8> r0) {
	return mipp_cast_int64_int64_m8(r0);
}
inline rvd<int64_t,1> cast_int64(const rvd<int32_t,1> r0) {
	return mipp_cast_int32_int64_m1(r0);
}
inline rvd<int64_t,2> cast_int64(const rvd<int32_t,2> r0) {
	return mipp_cast_int32_int64_m2(r0);
}
inline rvd<int64_t,4> cast_int64(const rvd<int32_t,4> r0) {
	return mipp_cast_int32_int64_m4(r0);
}
inline rvd<int64_t,8> cast_int64(const rvd<int32_t,8> r0) {
	return mipp_cast_int32_int64_m8(r0);
}
inline rvd<int64_t,1> cast_int64(const rvd<int16_t,1> r0) {
	return mipp_cast_int16_int64_m1(r0);
}
inline rvd<int64_t,2> cast_int64(const rvd<int16_t,2> r0) {
	return mipp_cast_int16_int64_m2(r0);
}
inline rvd<int64_t,4> cast_int64(const rvd<int16_t,4> r0) {
	return mipp_cast_int16_int64_m4(r0);
}
inline rvd<int64_t,8> cast_int64(const rvd<int16_t,8> r0) {
	return mipp_cast_int16_int64_m8(r0);
}
inline rvd<int64_t,1> cast_int64(const rvd<int8_t,1> r0) {
	return mipp_cast_int8_int64_m1(r0);
}
inline rvd<int64_t,2> cast_int64(const rvd<int8_t,2> r0) {
	return mipp_cast_int8_int64_m2(r0);
}
inline rvd<int64_t,4> cast_int64(const rvd<int8_t,4> r0) {
	return mipp_cast_int8_int64_m4(r0);
}
inline rvd<int64_t,8> cast_int64(const rvd<int8_t,8> r0) {
	return mipp_cast_int8_int64_m8(r0);
}
inline rvd<int64_t,1> cast_int64(const rvd<uint64_t,1> r0) {
	return mipp_cast_uint64_int64_m1(r0);
}
inline rvd<int64_t,2> cast_int64(const rvd<uint64_t,2> r0) {
	return mipp_cast_uint64_int64_m2(r0);
}
inline rvd<int64_t,4> cast_int64(const rvd<uint64_t,4> r0) {
	return mipp_cast_uint64_int64_m4(r0);
}
inline rvd<int64_t,8> cast_int64(const rvd<uint64_t,8> r0) {
	return mipp_cast_uint64_int64_m8(r0);
}
inline rvd<int64_t,1> cast_int64(const rvd<uint32_t,1> r0) {
	return mipp_cast_uint32_int64_m1(r0);
}
inline rvd<int64_t,2> cast_int64(const rvd<uint32_t,2> r0) {
	return mipp_cast_uint32_int64_m2(r0);
}
inline rvd<int64_t,4> cast_int64(const rvd<uint32_t,4> r0) {
	return mipp_cast_uint32_int64_m4(r0);
}
inline rvd<int64_t,8> cast_int64(const rvd<uint32_t,8> r0) {
	return mipp_cast_uint32_int64_m8(r0);
}
inline rvd<int64_t,1> cast_int64(const rvd<uint16_t,1> r0) {
	return mipp_cast_uint16_int64_m1(r0);
}
inline rvd<int64_t,2> cast_int64(const rvd<uint16_t,2> r0) {
	return mipp_cast_uint16_int64_m2(r0);
}
inline rvd<int64_t,4> cast_int64(const rvd<uint16_t,4> r0) {
	return mipp_cast_uint16_int64_m4(r0);
}
inline rvd<int64_t,8> cast_int64(const rvd<uint16_t,8> r0) {
	return mipp_cast_uint16_int64_m8(r0);
}
inline rvd<int64_t,1> cast_int64(const rvd<uint8_t,1> r0) {
	return mipp_cast_uint8_int64_m1(r0);
}
inline rvd<int64_t,2> cast_int64(const rvd<uint8_t,2> r0) {
	return mipp_cast_uint8_int64_m2(r0);
}
inline rvd<int64_t,4> cast_int64(const rvd<uint8_t,4> r0) {
	return mipp_cast_uint8_int64_m4(r0);
}
inline rvd<int64_t,8> cast_int64(const rvd<uint8_t,8> r0) {
	return mipp_cast_uint8_int64_m8(r0);
}
inline rvd<int32_t,1> cast_int32(const rvd<float64_t,1> r0) {
	return mipp_cast_float64_int32_m1(r0);
}
inline rvd<int32_t,2> cast_int32(const rvd<float64_t,2> r0) {
	return mipp_cast_float64_int32_m2(r0);
}
inline rvd<int32_t,4> cast_int32(const rvd<float64_t,4> r0) {
	return mipp_cast_float64_int32_m4(r0);
}
inline rvd<int32_t,8> cast_int32(const rvd<float64_t,8> r0) {
	return mipp_cast_float64_int32_m8(r0);
}
inline rvd<int32_t,1> cast_int32(const rvd<float32_t,1> r0) {
	return mipp_cast_float32_int32_m1(r0);
}
inline rvd<int32_t,2> cast_int32(const rvd<float32_t,2> r0) {
	return mipp_cast_float32_int32_m2(r0);
}
inline rvd<int32_t,4> cast_int32(const rvd<float32_t,4> r0) {
	return mipp_cast_float32_int32_m4(r0);
}
inline rvd<int32_t,8> cast_int32(const rvd<float32_t,8> r0) {
	return mipp_cast_float32_int32_m8(r0);
}
inline rvd<int32_t,1> cast_int32(const rvd<int64_t,1> r0) {
	return mipp_cast_int64_int32_m1(r0);
}
inline rvd<int32_t,2> cast_int32(const rvd<int64_t,2> r0) {
	return mipp_cast_int64_int32_m2(r0);
}
inline rvd<int32_t,4> cast_int32(const rvd<int64_t,4> r0) {
	return mipp_cast_int64_int32_m4(r0);
}
inline rvd<int32_t,8> cast_int32(const rvd<int64_t,8> r0) {
	return mipp_cast_int64_int32_m8(r0);
}
inline rvd<int32_t,1> cast_int32(const rvd<int32_t,1> r0) {
	return mipp_cast_int32_int32_m1(r0);
}
inline rvd<int32_t,2> cast_int32(const rvd<int32_t,2> r0) {
	return mipp_cast_int32_int32_m2(r0);
}
inline rvd<int32_t,4> cast_int32(const rvd<int32_t,4> r0) {
	return mipp_cast_int32_int32_m4(r0);
}
inline rvd<int32_t,8> cast_int32(const rvd<int32_t,8> r0) {
	return mipp_cast_int32_int32_m8(r0);
}
inline rvd<int32_t,1> cast_int32(const rvd<int16_t,1> r0) {
	return mipp_cast_int16_int32_m1(r0);
}
inline rvd<int32_t,2> cast_int32(const rvd<int16_t,2> r0) {
	return mipp_cast_int16_int32_m2(r0);
}
inline rvd<int32_t,4> cast_int32(const rvd<int16_t,4> r0) {
	return mipp_cast_int16_int32_m4(r0);
}
inline rvd<int32_t,8> cast_int32(const rvd<int16_t,8> r0) {
	return mipp_cast_int16_int32_m8(r0);
}
inline rvd<int32_t,1> cast_int32(const rvd<int8_t,1> r0) {
	return mipp_cast_int8_int32_m1(r0);
}
inline rvd<int32_t,2> cast_int32(const rvd<int8_t,2> r0) {
	return mipp_cast_int8_int32_m2(r0);
}
inline rvd<int32_t,4> cast_int32(const rvd<int8_t,4> r0) {
	return mipp_cast_int8_int32_m4(r0);
}
inline rvd<int32_t,8> cast_int32(const rvd<int8_t,8> r0) {
	return mipp_cast_int8_int32_m8(r0);
}
inline rvd<int32_t,1> cast_int32(const rvd<uint64_t,1> r0) {
	return mipp_cast_uint64_int32_m1(r0);
}
inline rvd<int32_t,2> cast_int32(const rvd<uint64_t,2> r0) {
	return mipp_cast_uint64_int32_m2(r0);
}
inline rvd<int32_t,4> cast_int32(const rvd<uint64_t,4> r0) {
	return mipp_cast_uint64_int32_m4(r0);
}
inline rvd<int32_t,8> cast_int32(const rvd<uint64_t,8> r0) {
	return mipp_cast_uint64_int32_m8(r0);
}
inline rvd<int32_t,1> cast_int32(const rvd<uint32_t,1> r0) {
	return mipp_cast_uint32_int32_m1(r0);
}
inline rvd<int32_t,2> cast_int32(const rvd<uint32_t,2> r0) {
	return mipp_cast_uint32_int32_m2(r0);
}
inline rvd<int32_t,4> cast_int32(const rvd<uint32_t,4> r0) {
	return mipp_cast_uint32_int32_m4(r0);
}
inline rvd<int32_t,8> cast_int32(const rvd<uint32_t,8> r0) {
	return mipp_cast_uint32_int32_m8(r0);
}
inline rvd<int32_t,1> cast_int32(const rvd<uint16_t,1> r0) {
	return mipp_cast_uint16_int32_m1(r0);
}
inline rvd<int32_t,2> cast_int32(const rvd<uint16_t,2> r0) {
	return mipp_cast_uint16_int32_m2(r0);
}
inline rvd<int32_t,4> cast_int32(const rvd<uint16_t,4> r0) {
	return mipp_cast_uint16_int32_m4(r0);
}
inline rvd<int32_t,8> cast_int32(const rvd<uint16_t,8> r0) {
	return mipp_cast_uint16_int32_m8(r0);
}
inline rvd<int32_t,1> cast_int32(const rvd<uint8_t,1> r0) {
	return mipp_cast_uint8_int32_m1(r0);
}
inline rvd<int32_t,2> cast_int32(const rvd<uint8_t,2> r0) {
	return mipp_cast_uint8_int32_m2(r0);
}
inline rvd<int32_t,4> cast_int32(const rvd<uint8_t,4> r0) {
	return mipp_cast_uint8_int32_m4(r0);
}
inline rvd<int32_t,8> cast_int32(const rvd<uint8_t,8> r0) {
	return mipp_cast_uint8_int32_m8(r0);
}
inline rvd<int16_t,1> cast_int16(const rvd<float64_t,1> r0) {
	return mipp_cast_float64_int16_m1(r0);
}
inline rvd<int16_t,2> cast_int16(const rvd<float64_t,2> r0) {
	return mipp_cast_float64_int16_m2(r0);
}
inline rvd<int16_t,4> cast_int16(const rvd<float64_t,4> r0) {
	return mipp_cast_float64_int16_m4(r0);
}
inline rvd<int16_t,8> cast_int16(const rvd<float64_t,8> r0) {
	return mipp_cast_float64_int16_m8(r0);
}
inline rvd<int16_t,1> cast_int16(const rvd<float32_t,1> r0) {
	return mipp_cast_float32_int16_m1(r0);
}
inline rvd<int16_t,2> cast_int16(const rvd<float32_t,2> r0) {
	return mipp_cast_float32_int16_m2(r0);
}
inline rvd<int16_t,4> cast_int16(const rvd<float32_t,4> r0) {
	return mipp_cast_float32_int16_m4(r0);
}
inline rvd<int16_t,8> cast_int16(const rvd<float32_t,8> r0) {
	return mipp_cast_float32_int16_m8(r0);
}
inline rvd<int16_t,1> cast_int16(const rvd<int64_t,1> r0) {
	return mipp_cast_int64_int16_m1(r0);
}
inline rvd<int16_t,2> cast_int16(const rvd<int64_t,2> r0) {
	return mipp_cast_int64_int16_m2(r0);
}
inline rvd<int16_t,4> cast_int16(const rvd<int64_t,4> r0) {
	return mipp_cast_int64_int16_m4(r0);
}
inline rvd<int16_t,8> cast_int16(const rvd<int64_t,8> r0) {
	return mipp_cast_int64_int16_m8(r0);
}
inline rvd<int16_t,1> cast_int16(const rvd<int32_t,1> r0) {
	return mipp_cast_int32_int16_m1(r0);
}
inline rvd<int16_t,2> cast_int16(const rvd<int32_t,2> r0) {
	return mipp_cast_int32_int16_m2(r0);
}
inline rvd<int16_t,4> cast_int16(const rvd<int32_t,4> r0) {
	return mipp_cast_int32_int16_m4(r0);
}
inline rvd<int16_t,8> cast_int16(const rvd<int32_t,8> r0) {
	return mipp_cast_int32_int16_m8(r0);
}
inline rvd<int16_t,1> cast_int16(const rvd<int16_t,1> r0) {
	return mipp_cast_int16_int16_m1(r0);
}
inline rvd<int16_t,2> cast_int16(const rvd<int16_t,2> r0) {
	return mipp_cast_int16_int16_m2(r0);
}
inline rvd<int16_t,4> cast_int16(const rvd<int16_t,4> r0) {
	return mipp_cast_int16_int16_m4(r0);
}
inline rvd<int16_t,8> cast_int16(const rvd<int16_t,8> r0) {
	return mipp_cast_int16_int16_m8(r0);
}
inline rvd<int16_t,1> cast_int16(const rvd<int8_t,1> r0) {
	return mipp_cast_int8_int16_m1(r0);
}
inline rvd<int16_t,2> cast_int16(const rvd<int8_t,2> r0) {
	return mipp_cast_int8_int16_m2(r0);
}
inline rvd<int16_t,4> cast_int16(const rvd<int8_t,4> r0) {
	return mipp_cast_int8_int16_m4(r0);
}
inline rvd<int16_t,8> cast_int16(const rvd<int8_t,8> r0) {
	return mipp_cast_int8_int16_m8(r0);
}
inline rvd<int16_t,1> cast_int16(const rvd<uint64_t,1> r0) {
	return mipp_cast_uint64_int16_m1(r0);
}
inline rvd<int16_t,2> cast_int16(const rvd<uint64_t,2> r0) {
	return mipp_cast_uint64_int16_m2(r0);
}
inline rvd<int16_t,4> cast_int16(const rvd<uint64_t,4> r0) {
	return mipp_cast_uint64_int16_m4(r0);
}
inline rvd<int16_t,8> cast_int16(const rvd<uint64_t,8> r0) {
	return mipp_cast_uint64_int16_m8(r0);
}
inline rvd<int16_t,1> cast_int16(const rvd<uint32_t,1> r0) {
	return mipp_cast_uint32_int16_m1(r0);
}
inline rvd<int16_t,2> cast_int16(const rvd<uint32_t,2> r0) {
	return mipp_cast_uint32_int16_m2(r0);
}
inline rvd<int16_t,4> cast_int16(const rvd<uint32_t,4> r0) {
	return mipp_cast_uint32_int16_m4(r0);
}
inline rvd<int16_t,8> cast_int16(const rvd<uint32_t,8> r0) {
	return mipp_cast_uint32_int16_m8(r0);
}
inline rvd<int16_t,1> cast_int16(const rvd<uint16_t,1> r0) {
	return mipp_cast_uint16_int16_m1(r0);
}
inline rvd<int16_t,2> cast_int16(const rvd<uint16_t,2> r0) {
	return mipp_cast_uint16_int16_m2(r0);
}
inline rvd<int16_t,4> cast_int16(const rvd<uint16_t,4> r0) {
	return mipp_cast_uint16_int16_m4(r0);
}
inline rvd<int16_t,8> cast_int16(const rvd<uint16_t,8> r0) {
	return mipp_cast_uint16_int16_m8(r0);
}
inline rvd<int16_t,1> cast_int16(const rvd<uint8_t,1> r0) {
	return mipp_cast_uint8_int16_m1(r0);
}
inline rvd<int16_t,2> cast_int16(const rvd<uint8_t,2> r0) {
	return mipp_cast_uint8_int16_m2(r0);
}
inline rvd<int16_t,4> cast_int16(const rvd<uint8_t,4> r0) {
	return mipp_cast_uint8_int16_m4(r0);
}
inline rvd<int16_t,8> cast_int16(const rvd<uint8_t,8> r0) {
	return mipp_cast_uint8_int16_m8(r0);
}
inline rvd<int8_t,1> cast_int8(const rvd<float64_t,1> r0) {
	return mipp_cast_float64_int8_m1(r0);
}
inline rvd<int8_t,2> cast_int8(const rvd<float64_t,2> r0) {
	return mipp_cast_float64_int8_m2(r0);
}
inline rvd<int8_t,4> cast_int8(const rvd<float64_t,4> r0) {
	return mipp_cast_float64_int8_m4(r0);
}
inline rvd<int8_t,8> cast_int8(const rvd<float64_t,8> r0) {
	return mipp_cast_float64_int8_m8(r0);
}
inline rvd<int8_t,1> cast_int8(const rvd<float32_t,1> r0) {
	return mipp_cast_float32_int8_m1(r0);
}
inline rvd<int8_t,2> cast_int8(const rvd<float32_t,2> r0) {
	return mipp_cast_float32_int8_m2(r0);
}
inline rvd<int8_t,4> cast_int8(const rvd<float32_t,4> r0) {
	return mipp_cast_float32_int8_m4(r0);
}
inline rvd<int8_t,8> cast_int8(const rvd<float32_t,8> r0) {
	return mipp_cast_float32_int8_m8(r0);
}
inline rvd<int8_t,1> cast_int8(const rvd<int64_t,1> r0) {
	return mipp_cast_int64_int8_m1(r0);
}
inline rvd<int8_t,2> cast_int8(const rvd<int64_t,2> r0) {
	return mipp_cast_int64_int8_m2(r0);
}
inline rvd<int8_t,4> cast_int8(const rvd<int64_t,4> r0) {
	return mipp_cast_int64_int8_m4(r0);
}
inline rvd<int8_t,8> cast_int8(const rvd<int64_t,8> r0) {
	return mipp_cast_int64_int8_m8(r0);
}
inline rvd<int8_t,1> cast_int8(const rvd<int32_t,1> r0) {
	return mipp_cast_int32_int8_m1(r0);
}
inline rvd<int8_t,2> cast_int8(const rvd<int32_t,2> r0) {
	return mipp_cast_int32_int8_m2(r0);
}
inline rvd<int8_t,4> cast_int8(const rvd<int32_t,4> r0) {
	return mipp_cast_int32_int8_m4(r0);
}
inline rvd<int8_t,8> cast_int8(const rvd<int32_t,8> r0) {
	return mipp_cast_int32_int8_m8(r0);
}
inline rvd<int8_t,1> cast_int8(const rvd<int16_t,1> r0) {
	return mipp_cast_int16_int8_m1(r0);
}
inline rvd<int8_t,2> cast_int8(const rvd<int16_t,2> r0) {
	return mipp_cast_int16_int8_m2(r0);
}
inline rvd<int8_t,4> cast_int8(const rvd<int16_t,4> r0) {
	return mipp_cast_int16_int8_m4(r0);
}
inline rvd<int8_t,8> cast_int8(const rvd<int16_t,8> r0) {
	return mipp_cast_int16_int8_m8(r0);
}
inline rvd<int8_t,1> cast_int8(const rvd<int8_t,1> r0) {
	return mipp_cast_int8_int8_m1(r0);
}
inline rvd<int8_t,2> cast_int8(const rvd<int8_t,2> r0) {
	return mipp_cast_int8_int8_m2(r0);
}
inline rvd<int8_t,4> cast_int8(const rvd<int8_t,4> r0) {
	return mipp_cast_int8_int8_m4(r0);
}
inline rvd<int8_t,8> cast_int8(const rvd<int8_t,8> r0) {
	return mipp_cast_int8_int8_m8(r0);
}
inline rvd<int8_t,1> cast_int8(const rvd<uint64_t,1> r0) {
	return mipp_cast_uint64_int8_m1(r0);
}
inline rvd<int8_t,2> cast_int8(const rvd<uint64_t,2> r0) {
	return mipp_cast_uint64_int8_m2(r0);
}
inline rvd<int8_t,4> cast_int8(const rvd<uint64_t,4> r0) {
	return mipp_cast_uint64_int8_m4(r0);
}
inline rvd<int8_t,8> cast_int8(const rvd<uint64_t,8> r0) {
	return mipp_cast_uint64_int8_m8(r0);
}
inline rvd<int8_t,1> cast_int8(const rvd<uint32_t,1> r0) {
	return mipp_cast_uint32_int8_m1(r0);
}
inline rvd<int8_t,2> cast_int8(const rvd<uint32_t,2> r0) {
	return mipp_cast_uint32_int8_m2(r0);
}
inline rvd<int8_t,4> cast_int8(const rvd<uint32_t,4> r0) {
	return mipp_cast_uint32_int8_m4(r0);
}
inline rvd<int8_t,8> cast_int8(const rvd<uint32_t,8> r0) {
	return mipp_cast_uint32_int8_m8(r0);
}
inline rvd<int8_t,1> cast_int8(const rvd<uint16_t,1> r0) {
	return mipp_cast_uint16_int8_m1(r0);
}
inline rvd<int8_t,2> cast_int8(const rvd<uint16_t,2> r0) {
	return mipp_cast_uint16_int8_m2(r0);
}
inline rvd<int8_t,4> cast_int8(const rvd<uint16_t,4> r0) {
	return mipp_cast_uint16_int8_m4(r0);
}
inline rvd<int8_t,8> cast_int8(const rvd<uint16_t,8> r0) {
	return mipp_cast_uint16_int8_m8(r0);
}
inline rvd<int8_t,1> cast_int8(const rvd<uint8_t,1> r0) {
	return mipp_cast_uint8_int8_m1(r0);
}
inline rvd<int8_t,2> cast_int8(const rvd<uint8_t,2> r0) {
	return mipp_cast_uint8_int8_m2(r0);
}
inline rvd<int8_t,4> cast_int8(const rvd<uint8_t,4> r0) {
	return mipp_cast_uint8_int8_m4(r0);
}
inline rvd<int8_t,8> cast_int8(const rvd<uint8_t,8> r0) {
	return mipp_cast_uint8_int8_m8(r0);
}
inline rvd<uint64_t,1> cast_uint64(const rvd<float64_t,1> r0) {
	return mipp_cast_float64_uint64_m1(r0);
}
inline rvd<uint64_t,2> cast_uint64(const rvd<float64_t,2> r0) {
	return mipp_cast_float64_uint64_m2(r0);
}
inline rvd<uint64_t,4> cast_uint64(const rvd<float64_t,4> r0) {
	return mipp_cast_float64_uint64_m4(r0);
}
inline rvd<uint64_t,8> cast_uint64(const rvd<float64_t,8> r0) {
	return mipp_cast_float64_uint64_m8(r0);
}
inline rvd<uint64_t,1> cast_uint64(const rvd<float32_t,1> r0) {
	return mipp_cast_float32_uint64_m1(r0);
}
inline rvd<uint64_t,2> cast_uint64(const rvd<float32_t,2> r0) {
	return mipp_cast_float32_uint64_m2(r0);
}
inline rvd<uint64_t,4> cast_uint64(const rvd<float32_t,4> r0) {
	return mipp_cast_float32_uint64_m4(r0);
}
inline rvd<uint64_t,8> cast_uint64(const rvd<float32_t,8> r0) {
	return mipp_cast_float32_uint64_m8(r0);
}
inline rvd<uint64_t,1> cast_uint64(const rvd<int64_t,1> r0) {
	return mipp_cast_int64_uint64_m1(r0);
}
inline rvd<uint64_t,2> cast_uint64(const rvd<int64_t,2> r0) {
	return mipp_cast_int64_uint64_m2(r0);
}
inline rvd<uint64_t,4> cast_uint64(const rvd<int64_t,4> r0) {
	return mipp_cast_int64_uint64_m4(r0);
}
inline rvd<uint64_t,8> cast_uint64(const rvd<int64_t,8> r0) {
	return mipp_cast_int64_uint64_m8(r0);
}
inline rvd<uint64_t,1> cast_uint64(const rvd<int32_t,1> r0) {
	return mipp_cast_int32_uint64_m1(r0);
}
inline rvd<uint64_t,2> cast_uint64(const rvd<int32_t,2> r0) {
	return mipp_cast_int32_uint64_m2(r0);
}
inline rvd<uint64_t,4> cast_uint64(const rvd<int32_t,4> r0) {
	return mipp_cast_int32_uint64_m4(r0);
}
inline rvd<uint64_t,8> cast_uint64(const rvd<int32_t,8> r0) {
	return mipp_cast_int32_uint64_m8(r0);
}
inline rvd<uint64_t,1> cast_uint64(const rvd<int16_t,1> r0) {
	return mipp_cast_int16_uint64_m1(r0);
}
inline rvd<uint64_t,2> cast_uint64(const rvd<int16_t,2> r0) {
	return mipp_cast_int16_uint64_m2(r0);
}
inline rvd<uint64_t,4> cast_uint64(const rvd<int16_t,4> r0) {
	return mipp_cast_int16_uint64_m4(r0);
}
inline rvd<uint64_t,8> cast_uint64(const rvd<int16_t,8> r0) {
	return mipp_cast_int16_uint64_m8(r0);
}
inline rvd<uint64_t,1> cast_uint64(const rvd<int8_t,1> r0) {
	return mipp_cast_int8_uint64_m1(r0);
}
inline rvd<uint64_t,2> cast_uint64(const rvd<int8_t,2> r0) {
	return mipp_cast_int8_uint64_m2(r0);
}
inline rvd<uint64_t,4> cast_uint64(const rvd<int8_t,4> r0) {
	return mipp_cast_int8_uint64_m4(r0);
}
inline rvd<uint64_t,8> cast_uint64(const rvd<int8_t,8> r0) {
	return mipp_cast_int8_uint64_m8(r0);
}
inline rvd<uint64_t,1> cast_uint64(const rvd<uint64_t,1> r0) {
	return mipp_cast_uint64_uint64_m1(r0);
}
inline rvd<uint64_t,2> cast_uint64(const rvd<uint64_t,2> r0) {
	return mipp_cast_uint64_uint64_m2(r0);
}
inline rvd<uint64_t,4> cast_uint64(const rvd<uint64_t,4> r0) {
	return mipp_cast_uint64_uint64_m4(r0);
}
inline rvd<uint64_t,8> cast_uint64(const rvd<uint64_t,8> r0) {
	return mipp_cast_uint64_uint64_m8(r0);
}
inline rvd<uint64_t,1> cast_uint64(const rvd<uint32_t,1> r0) {
	return mipp_cast_uint32_uint64_m1(r0);
}
inline rvd<uint64_t,2> cast_uint64(const rvd<uint32_t,2> r0) {
	return mipp_cast_uint32_uint64_m2(r0);
}
inline rvd<uint64_t,4> cast_uint64(const rvd<uint32_t,4> r0) {
	return mipp_cast_uint32_uint64_m4(r0);
}
inline rvd<uint64_t,8> cast_uint64(const rvd<uint32_t,8> r0) {
	return mipp_cast_uint32_uint64_m8(r0);
}
inline rvd<uint64_t,1> cast_uint64(const rvd<uint16_t,1> r0) {
	return mipp_cast_uint16_uint64_m1(r0);
}
inline rvd<uint64_t,2> cast_uint64(const rvd<uint16_t,2> r0) {
	return mipp_cast_uint16_uint64_m2(r0);
}
inline rvd<uint64_t,4> cast_uint64(const rvd<uint16_t,4> r0) {
	return mipp_cast_uint16_uint64_m4(r0);
}
inline rvd<uint64_t,8> cast_uint64(const rvd<uint16_t,8> r0) {
	return mipp_cast_uint16_uint64_m8(r0);
}
inline rvd<uint64_t,1> cast_uint64(const rvd<uint8_t,1> r0) {
	return mipp_cast_uint8_uint64_m1(r0);
}
inline rvd<uint64_t,2> cast_uint64(const rvd<uint8_t,2> r0) {
	return mipp_cast_uint8_uint64_m2(r0);
}
inline rvd<uint64_t,4> cast_uint64(const rvd<uint8_t,4> r0) {
	return mipp_cast_uint8_uint64_m4(r0);
}
inline rvd<uint64_t,8> cast_uint64(const rvd<uint8_t,8> r0) {
	return mipp_cast_uint8_uint64_m8(r0);
}
inline rvd<uint32_t,1> cast_uint32(const rvd<float64_t,1> r0) {
	return mipp_cast_float64_uint32_m1(r0);
}
inline rvd<uint32_t,2> cast_uint32(const rvd<float64_t,2> r0) {
	return mipp_cast_float64_uint32_m2(r0);
}
inline rvd<uint32_t,4> cast_uint32(const rvd<float64_t,4> r0) {
	return mipp_cast_float64_uint32_m4(r0);
}
inline rvd<uint32_t,8> cast_uint32(const rvd<float64_t,8> r0) {
	return mipp_cast_float64_uint32_m8(r0);
}
inline rvd<uint32_t,1> cast_uint32(const rvd<float32_t,1> r0) {
	return mipp_cast_float32_uint32_m1(r0);
}
inline rvd<uint32_t,2> cast_uint32(const rvd<float32_t,2> r0) {
	return mipp_cast_float32_uint32_m2(r0);
}
inline rvd<uint32_t,4> cast_uint32(const rvd<float32_t,4> r0) {
	return mipp_cast_float32_uint32_m4(r0);
}
inline rvd<uint32_t,8> cast_uint32(const rvd<float32_t,8> r0) {
	return mipp_cast_float32_uint32_m8(r0);
}
inline rvd<uint32_t,1> cast_uint32(const rvd<int64_t,1> r0) {
	return mipp_cast_int64_uint32_m1(r0);
}
inline rvd<uint32_t,2> cast_uint32(const rvd<int64_t,2> r0) {
	return mipp_cast_int64_uint32_m2(r0);
}
inline rvd<uint32_t,4> cast_uint32(const rvd<int64_t,4> r0) {
	return mipp_cast_int64_uint32_m4(r0);
}
inline rvd<uint32_t,8> cast_uint32(const rvd<int64_t,8> r0) {
	return mipp_cast_int64_uint32_m8(r0);
}
inline rvd<uint32_t,1> cast_uint32(const rvd<int32_t,1> r0) {
	return mipp_cast_int32_uint32_m1(r0);
}
inline rvd<uint32_t,2> cast_uint32(const rvd<int32_t,2> r0) {
	return mipp_cast_int32_uint32_m2(r0);
}
inline rvd<uint32_t,4> cast_uint32(const rvd<int32_t,4> r0) {
	return mipp_cast_int32_uint32_m4(r0);
}
inline rvd<uint32_t,8> cast_uint32(const rvd<int32_t,8> r0) {
	return mipp_cast_int32_uint32_m8(r0);
}
inline rvd<uint32_t,1> cast_uint32(const rvd<int16_t,1> r0) {
	return mipp_cast_int16_uint32_m1(r0);
}
inline rvd<uint32_t,2> cast_uint32(const rvd<int16_t,2> r0) {
	return mipp_cast_int16_uint32_m2(r0);
}
inline rvd<uint32_t,4> cast_uint32(const rvd<int16_t,4> r0) {
	return mipp_cast_int16_uint32_m4(r0);
}
inline rvd<uint32_t,8> cast_uint32(const rvd<int16_t,8> r0) {
	return mipp_cast_int16_uint32_m8(r0);
}
inline rvd<uint32_t,1> cast_uint32(const rvd<int8_t,1> r0) {
	return mipp_cast_int8_uint32_m1(r0);
}
inline rvd<uint32_t,2> cast_uint32(const rvd<int8_t,2> r0) {
	return mipp_cast_int8_uint32_m2(r0);
}
inline rvd<uint32_t,4> cast_uint32(const rvd<int8_t,4> r0) {
	return mipp_cast_int8_uint32_m4(r0);
}
inline rvd<uint32_t,8> cast_uint32(const rvd<int8_t,8> r0) {
	return mipp_cast_int8_uint32_m8(r0);
}
inline rvd<uint32_t,1> cast_uint32(const rvd<uint64_t,1> r0) {
	return mipp_cast_uint64_uint32_m1(r0);
}
inline rvd<uint32_t,2> cast_uint32(const rvd<uint64_t,2> r0) {
	return mipp_cast_uint64_uint32_m2(r0);
}
inline rvd<uint32_t,4> cast_uint32(const rvd<uint64_t,4> r0) {
	return mipp_cast_uint64_uint32_m4(r0);
}
inline rvd<uint32_t,8> cast_uint32(const rvd<uint64_t,8> r0) {
	return mipp_cast_uint64_uint32_m8(r0);
}
inline rvd<uint32_t,1> cast_uint32(const rvd<uint32_t,1> r0) {
	return mipp_cast_uint32_uint32_m1(r0);
}
inline rvd<uint32_t,2> cast_uint32(const rvd<uint32_t,2> r0) {
	return mipp_cast_uint32_uint32_m2(r0);
}
inline rvd<uint32_t,4> cast_uint32(const rvd<uint32_t,4> r0) {
	return mipp_cast_uint32_uint32_m4(r0);
}
inline rvd<uint32_t,8> cast_uint32(const rvd<uint32_t,8> r0) {
	return mipp_cast_uint32_uint32_m8(r0);
}
inline rvd<uint32_t,1> cast_uint32(const rvd<uint16_t,1> r0) {
	return mipp_cast_uint16_uint32_m1(r0);
}
inline rvd<uint32_t,2> cast_uint32(const rvd<uint16_t,2> r0) {
	return mipp_cast_uint16_uint32_m2(r0);
}
inline rvd<uint32_t,4> cast_uint32(const rvd<uint16_t,4> r0) {
	return mipp_cast_uint16_uint32_m4(r0);
}
inline rvd<uint32_t,8> cast_uint32(const rvd<uint16_t,8> r0) {
	return mipp_cast_uint16_uint32_m8(r0);
}
inline rvd<uint32_t,1> cast_uint32(const rvd<uint8_t,1> r0) {
	return mipp_cast_uint8_uint32_m1(r0);
}
inline rvd<uint32_t,2> cast_uint32(const rvd<uint8_t,2> r0) {
	return mipp_cast_uint8_uint32_m2(r0);
}
inline rvd<uint32_t,4> cast_uint32(const rvd<uint8_t,4> r0) {
	return mipp_cast_uint8_uint32_m4(r0);
}
inline rvd<uint32_t,8> cast_uint32(const rvd<uint8_t,8> r0) {
	return mipp_cast_uint8_uint32_m8(r0);
}
inline rvd<uint16_t,1> cast_uint16(const rvd<float64_t,1> r0) {
	return mipp_cast_float64_uint16_m1(r0);
}
inline rvd<uint16_t,2> cast_uint16(const rvd<float64_t,2> r0) {
	return mipp_cast_float64_uint16_m2(r0);
}
inline rvd<uint16_t,4> cast_uint16(const rvd<float64_t,4> r0) {
	return mipp_cast_float64_uint16_m4(r0);
}
inline rvd<uint16_t,8> cast_uint16(const rvd<float64_t,8> r0) {
	return mipp_cast_float64_uint16_m8(r0);
}
inline rvd<uint16_t,1> cast_uint16(const rvd<float32_t,1> r0) {
	return mipp_cast_float32_uint16_m1(r0);
}
inline rvd<uint16_t,2> cast_uint16(const rvd<float32_t,2> r0) {
	return mipp_cast_float32_uint16_m2(r0);
}
inline rvd<uint16_t,4> cast_uint16(const rvd<float32_t,4> r0) {
	return mipp_cast_float32_uint16_m4(r0);
}
inline rvd<uint16_t,8> cast_uint16(const rvd<float32_t,8> r0) {
	return mipp_cast_float32_uint16_m8(r0);
}
inline rvd<uint16_t,1> cast_uint16(const rvd<int64_t,1> r0) {
	return mipp_cast_int64_uint16_m1(r0);
}
inline rvd<uint16_t,2> cast_uint16(const rvd<int64_t,2> r0) {
	return mipp_cast_int64_uint16_m2(r0);
}
inline rvd<uint16_t,4> cast_uint16(const rvd<int64_t,4> r0) {
	return mipp_cast_int64_uint16_m4(r0);
}
inline rvd<uint16_t,8> cast_uint16(const rvd<int64_t,8> r0) {
	return mipp_cast_int64_uint16_m8(r0);
}
inline rvd<uint16_t,1> cast_uint16(const rvd<int32_t,1> r0) {
	return mipp_cast_int32_uint16_m1(r0);
}
inline rvd<uint16_t,2> cast_uint16(const rvd<int32_t,2> r0) {
	return mipp_cast_int32_uint16_m2(r0);
}
inline rvd<uint16_t,4> cast_uint16(const rvd<int32_t,4> r0) {
	return mipp_cast_int32_uint16_m4(r0);
}
inline rvd<uint16_t,8> cast_uint16(const rvd<int32_t,8> r0) {
	return mipp_cast_int32_uint16_m8(r0);
}
inline rvd<uint16_t,1> cast_uint16(const rvd<int16_t,1> r0) {
	return mipp_cast_int16_uint16_m1(r0);
}
inline rvd<uint16_t,2> cast_uint16(const rvd<int16_t,2> r0) {
	return mipp_cast_int16_uint16_m2(r0);
}
inline rvd<uint16_t,4> cast_uint16(const rvd<int16_t,4> r0) {
	return mipp_cast_int16_uint16_m4(r0);
}
inline rvd<uint16_t,8> cast_uint16(const rvd<int16_t,8> r0) {
	return mipp_cast_int16_uint16_m8(r0);
}
inline rvd<uint16_t,1> cast_uint16(const rvd<int8_t,1> r0) {
	return mipp_cast_int8_uint16_m1(r0);
}
inline rvd<uint16_t,2> cast_uint16(const rvd<int8_t,2> r0) {
	return mipp_cast_int8_uint16_m2(r0);
}
inline rvd<uint16_t,4> cast_uint16(const rvd<int8_t,4> r0) {
	return mipp_cast_int8_uint16_m4(r0);
}
inline rvd<uint16_t,8> cast_uint16(const rvd<int8_t,8> r0) {
	return mipp_cast_int8_uint16_m8(r0);
}
inline rvd<uint16_t,1> cast_uint16(const rvd<uint64_t,1> r0) {
	return mipp_cast_uint64_uint16_m1(r0);
}
inline rvd<uint16_t,2> cast_uint16(const rvd<uint64_t,2> r0) {
	return mipp_cast_uint64_uint16_m2(r0);
}
inline rvd<uint16_t,4> cast_uint16(const rvd<uint64_t,4> r0) {
	return mipp_cast_uint64_uint16_m4(r0);
}
inline rvd<uint16_t,8> cast_uint16(const rvd<uint64_t,8> r0) {
	return mipp_cast_uint64_uint16_m8(r0);
}
inline rvd<uint16_t,1> cast_uint16(const rvd<uint32_t,1> r0) {
	return mipp_cast_uint32_uint16_m1(r0);
}
inline rvd<uint16_t,2> cast_uint16(const rvd<uint32_t,2> r0) {
	return mipp_cast_uint32_uint16_m2(r0);
}
inline rvd<uint16_t,4> cast_uint16(const rvd<uint32_t,4> r0) {
	return mipp_cast_uint32_uint16_m4(r0);
}
inline rvd<uint16_t,8> cast_uint16(const rvd<uint32_t,8> r0) {
	return mipp_cast_uint32_uint16_m8(r0);
}
inline rvd<uint16_t,1> cast_uint16(const rvd<uint16_t,1> r0) {
	return mipp_cast_uint16_uint16_m1(r0);
}
inline rvd<uint16_t,2> cast_uint16(const rvd<uint16_t,2> r0) {
	return mipp_cast_uint16_uint16_m2(r0);
}
inline rvd<uint16_t,4> cast_uint16(const rvd<uint16_t,4> r0) {
	return mipp_cast_uint16_uint16_m4(r0);
}
inline rvd<uint16_t,8> cast_uint16(const rvd<uint16_t,8> r0) {
	return mipp_cast_uint16_uint16_m8(r0);
}
inline rvd<uint16_t,1> cast_uint16(const rvd<uint8_t,1> r0) {
	return mipp_cast_uint8_uint16_m1(r0);
}
inline rvd<uint16_t,2> cast_uint16(const rvd<uint8_t,2> r0) {
	return mipp_cast_uint8_uint16_m2(r0);
}
inline rvd<uint16_t,4> cast_uint16(const rvd<uint8_t,4> r0) {
	return mipp_cast_uint8_uint16_m4(r0);
}
inline rvd<uint16_t,8> cast_uint16(const rvd<uint8_t,8> r0) {
	return mipp_cast_uint8_uint16_m8(r0);
}
inline rvd<uint8_t,1> cast_uint8(const rvd<float64_t,1> r0) {
	return mipp_cast_float64_uint8_m1(r0);
}
inline rvd<uint8_t,2> cast_uint8(const rvd<float64_t,2> r0) {
	return mipp_cast_float64_uint8_m2(r0);
}
inline rvd<uint8_t,4> cast_uint8(const rvd<float64_t,4> r0) {
	return mipp_cast_float64_uint8_m4(r0);
}
inline rvd<uint8_t,8> cast_uint8(const rvd<float64_t,8> r0) {
	return mipp_cast_float64_uint8_m8(r0);
}
inline rvd<uint8_t,1> cast_uint8(const rvd<float32_t,1> r0) {
	return mipp_cast_float32_uint8_m1(r0);
}
inline rvd<uint8_t,2> cast_uint8(const rvd<float32_t,2> r0) {
	return mipp_cast_float32_uint8_m2(r0);
}
inline rvd<uint8_t,4> cast_uint8(const rvd<float32_t,4> r0) {
	return mipp_cast_float32_uint8_m4(r0);
}
inline rvd<uint8_t,8> cast_uint8(const rvd<float32_t,8> r0) {
	return mipp_cast_float32_uint8_m8(r0);
}
inline rvd<uint8_t,1> cast_uint8(const rvd<int64_t,1> r0) {
	return mipp_cast_int64_uint8_m1(r0);
}
inline rvd<uint8_t,2> cast_uint8(const rvd<int64_t,2> r0) {
	return mipp_cast_int64_uint8_m2(r0);
}
inline rvd<uint8_t,4> cast_uint8(const rvd<int64_t,4> r0) {
	return mipp_cast_int64_uint8_m4(r0);
}
inline rvd<uint8_t,8> cast_uint8(const rvd<int64_t,8> r0) {
	return mipp_cast_int64_uint8_m8(r0);
}
inline rvd<uint8_t,1> cast_uint8(const rvd<int32_t,1> r0) {
	return mipp_cast_int32_uint8_m1(r0);
}
inline rvd<uint8_t,2> cast_uint8(const rvd<int32_t,2> r0) {
	return mipp_cast_int32_uint8_m2(r0);
}
inline rvd<uint8_t,4> cast_uint8(const rvd<int32_t,4> r0) {
	return mipp_cast_int32_uint8_m4(r0);
}
inline rvd<uint8_t,8> cast_uint8(const rvd<int32_t,8> r0) {
	return mipp_cast_int32_uint8_m8(r0);
}
inline rvd<uint8_t,1> cast_uint8(const rvd<int16_t,1> r0) {
	return mipp_cast_int16_uint8_m1(r0);
}
inline rvd<uint8_t,2> cast_uint8(const rvd<int16_t,2> r0) {
	return mipp_cast_int16_uint8_m2(r0);
}
inline rvd<uint8_t,4> cast_uint8(const rvd<int16_t,4> r0) {
	return mipp_cast_int16_uint8_m4(r0);
}
inline rvd<uint8_t,8> cast_uint8(const rvd<int16_t,8> r0) {
	return mipp_cast_int16_uint8_m8(r0);
}
inline rvd<uint8_t,1> cast_uint8(const rvd<int8_t,1> r0) {
	return mipp_cast_int8_uint8_m1(r0);
}
inline rvd<uint8_t,2> cast_uint8(const rvd<int8_t,2> r0) {
	return mipp_cast_int8_uint8_m2(r0);
}
inline rvd<uint8_t,4> cast_uint8(const rvd<int8_t,4> r0) {
	return mipp_cast_int8_uint8_m4(r0);
}
inline rvd<uint8_t,8> cast_uint8(const rvd<int8_t,8> r0) {
	return mipp_cast_int8_uint8_m8(r0);
}
inline rvd<uint8_t,1> cast_uint8(const rvd<uint64_t,1> r0) {
	return mipp_cast_uint64_uint8_m1(r0);
}
inline rvd<uint8_t,2> cast_uint8(const rvd<uint64_t,2> r0) {
	return mipp_cast_uint64_uint8_m2(r0);
}
inline rvd<uint8_t,4> cast_uint8(const rvd<uint64_t,4> r0) {
	return mipp_cast_uint64_uint8_m4(r0);
}
inline rvd<uint8_t,8> cast_uint8(const rvd<uint64_t,8> r0) {
	return mipp_cast_uint64_uint8_m8(r0);
}
inline rvd<uint8_t,1> cast_uint8(const rvd<uint32_t,1> r0) {
	return mipp_cast_uint32_uint8_m1(r0);
}
inline rvd<uint8_t,2> cast_uint8(const rvd<uint32_t,2> r0) {
	return mipp_cast_uint32_uint8_m2(r0);
}
inline rvd<uint8_t,4> cast_uint8(const rvd<uint32_t,4> r0) {
	return mipp_cast_uint32_uint8_m4(r0);
}
inline rvd<uint8_t,8> cast_uint8(const rvd<uint32_t,8> r0) {
	return mipp_cast_uint32_uint8_m8(r0);
}
inline rvd<uint8_t,1> cast_uint8(const rvd<uint16_t,1> r0) {
	return mipp_cast_uint16_uint8_m1(r0);
}
inline rvd<uint8_t,2> cast_uint8(const rvd<uint16_t,2> r0) {
	return mipp_cast_uint16_uint8_m2(r0);
}
inline rvd<uint8_t,4> cast_uint8(const rvd<uint16_t,4> r0) {
	return mipp_cast_uint16_uint8_m4(r0);
}
inline rvd<uint8_t,8> cast_uint8(const rvd<uint16_t,8> r0) {
	return mipp_cast_uint16_uint8_m8(r0);
}
inline rvd<uint8_t,1> cast_uint8(const rvd<uint8_t,1> r0) {
	return mipp_cast_uint8_uint8_m1(r0);
}
inline rvd<uint8_t,2> cast_uint8(const rvd<uint8_t,2> r0) {
	return mipp_cast_uint8_uint8_m2(r0);
}
inline rvd<uint8_t,4> cast_uint8(const rvd<uint8_t,4> r0) {
	return mipp_cast_uint8_uint8_m4(r0);
}
inline rvd<uint8_t,8> cast_uint8(const rvd<uint8_t,8> r0) {
	return mipp_cast_uint8_uint8_m8(r0);
}
inline rvm<float64_t,1> cast_float64(const rvm<float64_t,1> m0) {
	return mipp_cast_k_float64_float64_m1(m0);
}
inline rvm<float64_t,2> cast_float64(const rvm<float64_t,2> m0) {
	return mipp_cast_k_float64_float64_m2(m0);
}
inline rvm<float64_t,4> cast_float64(const rvm<float64_t,4> m0) {
	return mipp_cast_k_float64_float64_m4(m0);
}
inline rvm<float64_t,8> cast_float64(const rvm<float64_t,8> m0) {
	return mipp_cast_k_float64_float64_m8(m0);
}
inline rvm<float64_t,1> cast_float64(const rvm<float32_t,1> m0) {
	return mipp_cast_k_float32_float64_m1(m0);
}
inline rvm<float64_t,2> cast_float64(const rvm<float32_t,2> m0) {
	return mipp_cast_k_float32_float64_m2(m0);
}
inline rvm<float64_t,4> cast_float64(const rvm<float32_t,4> m0) {
	return mipp_cast_k_float32_float64_m4(m0);
}
inline rvm<float64_t,8> cast_float64(const rvm<float32_t,8> m0) {
	return mipp_cast_k_float32_float64_m8(m0);
}
inline rvm<float64_t,1> cast_float64(const rvm<int64_t,1> m0) {
	return mipp_cast_k_int64_float64_m1(m0);
}
inline rvm<float64_t,2> cast_float64(const rvm<int64_t,2> m0) {
	return mipp_cast_k_int64_float64_m2(m0);
}
inline rvm<float64_t,4> cast_float64(const rvm<int64_t,4> m0) {
	return mipp_cast_k_int64_float64_m4(m0);
}
inline rvm<float64_t,8> cast_float64(const rvm<int64_t,8> m0) {
	return mipp_cast_k_int64_float64_m8(m0);
}
inline rvm<float64_t,1> cast_float64(const rvm<int32_t,1> m0) {
	return mipp_cast_k_int32_float64_m1(m0);
}
inline rvm<float64_t,2> cast_float64(const rvm<int32_t,2> m0) {
	return mipp_cast_k_int32_float64_m2(m0);
}
inline rvm<float64_t,4> cast_float64(const rvm<int32_t,4> m0) {
	return mipp_cast_k_int32_float64_m4(m0);
}
inline rvm<float64_t,8> cast_float64(const rvm<int32_t,8> m0) {
	return mipp_cast_k_int32_float64_m8(m0);
}
inline rvm<float64_t,1> cast_float64(const rvm<int16_t,1> m0) {
	return mipp_cast_k_int16_float64_m1(m0);
}
inline rvm<float64_t,2> cast_float64(const rvm<int16_t,2> m0) {
	return mipp_cast_k_int16_float64_m2(m0);
}
inline rvm<float64_t,4> cast_float64(const rvm<int16_t,4> m0) {
	return mipp_cast_k_int16_float64_m4(m0);
}
inline rvm<float64_t,8> cast_float64(const rvm<int16_t,8> m0) {
	return mipp_cast_k_int16_float64_m8(m0);
}
inline rvm<float64_t,1> cast_float64(const rvm<int8_t,1> m0) {
	return mipp_cast_k_int8_float64_m1(m0);
}
inline rvm<float64_t,2> cast_float64(const rvm<int8_t,2> m0) {
	return mipp_cast_k_int8_float64_m2(m0);
}
inline rvm<float64_t,4> cast_float64(const rvm<int8_t,4> m0) {
	return mipp_cast_k_int8_float64_m4(m0);
}
inline rvm<float64_t,8> cast_float64(const rvm<int8_t,8> m0) {
	return mipp_cast_k_int8_float64_m8(m0);
}
inline rvm<float64_t,1> cast_float64(const rvm<uint64_t,1> m0) {
	return mipp_cast_k_uint64_float64_m1(m0);
}
inline rvm<float64_t,2> cast_float64(const rvm<uint64_t,2> m0) {
	return mipp_cast_k_uint64_float64_m2(m0);
}
inline rvm<float64_t,4> cast_float64(const rvm<uint64_t,4> m0) {
	return mipp_cast_k_uint64_float64_m4(m0);
}
inline rvm<float64_t,8> cast_float64(const rvm<uint64_t,8> m0) {
	return mipp_cast_k_uint64_float64_m8(m0);
}
inline rvm<float64_t,1> cast_float64(const rvm<uint32_t,1> m0) {
	return mipp_cast_k_uint32_float64_m1(m0);
}
inline rvm<float64_t,2> cast_float64(const rvm<uint32_t,2> m0) {
	return mipp_cast_k_uint32_float64_m2(m0);
}
inline rvm<float64_t,4> cast_float64(const rvm<uint32_t,4> m0) {
	return mipp_cast_k_uint32_float64_m4(m0);
}
inline rvm<float64_t,8> cast_float64(const rvm<uint32_t,8> m0) {
	return mipp_cast_k_uint32_float64_m8(m0);
}
inline rvm<float64_t,1> cast_float64(const rvm<uint16_t,1> m0) {
	return mipp_cast_k_uint16_float64_m1(m0);
}
inline rvm<float64_t,2> cast_float64(const rvm<uint16_t,2> m0) {
	return mipp_cast_k_uint16_float64_m2(m0);
}
inline rvm<float64_t,4> cast_float64(const rvm<uint16_t,4> m0) {
	return mipp_cast_k_uint16_float64_m4(m0);
}
inline rvm<float64_t,8> cast_float64(const rvm<uint16_t,8> m0) {
	return mipp_cast_k_uint16_float64_m8(m0);
}
inline rvm<float64_t,1> cast_float64(const rvm<uint8_t,1> m0) {
	return mipp_cast_k_uint8_float64_m1(m0);
}
inline rvm<float64_t,2> cast_float64(const rvm<uint8_t,2> m0) {
	return mipp_cast_k_uint8_float64_m2(m0);
}
inline rvm<float64_t,4> cast_float64(const rvm<uint8_t,4> m0) {
	return mipp_cast_k_uint8_float64_m4(m0);
}
inline rvm<float64_t,8> cast_float64(const rvm<uint8_t,8> m0) {
	return mipp_cast_k_uint8_float64_m8(m0);
}
inline rvm<float32_t,1> cast_float32(const rvm<float64_t,1> m0) {
	return mipp_cast_k_float64_float32_m1(m0);
}
inline rvm<float32_t,2> cast_float32(const rvm<float64_t,2> m0) {
	return mipp_cast_k_float64_float32_m2(m0);
}
inline rvm<float32_t,4> cast_float32(const rvm<float64_t,4> m0) {
	return mipp_cast_k_float64_float32_m4(m0);
}
inline rvm<float32_t,8> cast_float32(const rvm<float64_t,8> m0) {
	return mipp_cast_k_float64_float32_m8(m0);
}
inline rvm<float32_t,1> cast_float32(const rvm<float32_t,1> m0) {
	return mipp_cast_k_float32_float32_m1(m0);
}
inline rvm<float32_t,2> cast_float32(const rvm<float32_t,2> m0) {
	return mipp_cast_k_float32_float32_m2(m0);
}
inline rvm<float32_t,4> cast_float32(const rvm<float32_t,4> m0) {
	return mipp_cast_k_float32_float32_m4(m0);
}
inline rvm<float32_t,8> cast_float32(const rvm<float32_t,8> m0) {
	return mipp_cast_k_float32_float32_m8(m0);
}
inline rvm<float32_t,1> cast_float32(const rvm<int64_t,1> m0) {
	return mipp_cast_k_int64_float32_m1(m0);
}
inline rvm<float32_t,2> cast_float32(const rvm<int64_t,2> m0) {
	return mipp_cast_k_int64_float32_m2(m0);
}
inline rvm<float32_t,4> cast_float32(const rvm<int64_t,4> m0) {
	return mipp_cast_k_int64_float32_m4(m0);
}
inline rvm<float32_t,8> cast_float32(const rvm<int64_t,8> m0) {
	return mipp_cast_k_int64_float32_m8(m0);
}
inline rvm<float32_t,1> cast_float32(const rvm<int32_t,1> m0) {
	return mipp_cast_k_int32_float32_m1(m0);
}
inline rvm<float32_t,2> cast_float32(const rvm<int32_t,2> m0) {
	return mipp_cast_k_int32_float32_m2(m0);
}
inline rvm<float32_t,4> cast_float32(const rvm<int32_t,4> m0) {
	return mipp_cast_k_int32_float32_m4(m0);
}
inline rvm<float32_t,8> cast_float32(const rvm<int32_t,8> m0) {
	return mipp_cast_k_int32_float32_m8(m0);
}
inline rvm<float32_t,1> cast_float32(const rvm<int16_t,1> m0) {
	return mipp_cast_k_int16_float32_m1(m0);
}
inline rvm<float32_t,2> cast_float32(const rvm<int16_t,2> m0) {
	return mipp_cast_k_int16_float32_m2(m0);
}
inline rvm<float32_t,4> cast_float32(const rvm<int16_t,4> m0) {
	return mipp_cast_k_int16_float32_m4(m0);
}
inline rvm<float32_t,8> cast_float32(const rvm<int16_t,8> m0) {
	return mipp_cast_k_int16_float32_m8(m0);
}
inline rvm<float32_t,1> cast_float32(const rvm<int8_t,1> m0) {
	return mipp_cast_k_int8_float32_m1(m0);
}
inline rvm<float32_t,2> cast_float32(const rvm<int8_t,2> m0) {
	return mipp_cast_k_int8_float32_m2(m0);
}
inline rvm<float32_t,4> cast_float32(const rvm<int8_t,4> m0) {
	return mipp_cast_k_int8_float32_m4(m0);
}
inline rvm<float32_t,8> cast_float32(const rvm<int8_t,8> m0) {
	return mipp_cast_k_int8_float32_m8(m0);
}
inline rvm<float32_t,1> cast_float32(const rvm<uint64_t,1> m0) {
	return mipp_cast_k_uint64_float32_m1(m0);
}
inline rvm<float32_t,2> cast_float32(const rvm<uint64_t,2> m0) {
	return mipp_cast_k_uint64_float32_m2(m0);
}
inline rvm<float32_t,4> cast_float32(const rvm<uint64_t,4> m0) {
	return mipp_cast_k_uint64_float32_m4(m0);
}
inline rvm<float32_t,8> cast_float32(const rvm<uint64_t,8> m0) {
	return mipp_cast_k_uint64_float32_m8(m0);
}
inline rvm<float32_t,1> cast_float32(const rvm<uint32_t,1> m0) {
	return mipp_cast_k_uint32_float32_m1(m0);
}
inline rvm<float32_t,2> cast_float32(const rvm<uint32_t,2> m0) {
	return mipp_cast_k_uint32_float32_m2(m0);
}
inline rvm<float32_t,4> cast_float32(const rvm<uint32_t,4> m0) {
	return mipp_cast_k_uint32_float32_m4(m0);
}
inline rvm<float32_t,8> cast_float32(const rvm<uint32_t,8> m0) {
	return mipp_cast_k_uint32_float32_m8(m0);
}
inline rvm<float32_t,1> cast_float32(const rvm<uint16_t,1> m0) {
	return mipp_cast_k_uint16_float32_m1(m0);
}
inline rvm<float32_t,2> cast_float32(const rvm<uint16_t,2> m0) {
	return mipp_cast_k_uint16_float32_m2(m0);
}
inline rvm<float32_t,4> cast_float32(const rvm<uint16_t,4> m0) {
	return mipp_cast_k_uint16_float32_m4(m0);
}
inline rvm<float32_t,8> cast_float32(const rvm<uint16_t,8> m0) {
	return mipp_cast_k_uint16_float32_m8(m0);
}
inline rvm<float32_t,1> cast_float32(const rvm<uint8_t,1> m0) {
	return mipp_cast_k_uint8_float32_m1(m0);
}
inline rvm<float32_t,2> cast_float32(const rvm<uint8_t,2> m0) {
	return mipp_cast_k_uint8_float32_m2(m0);
}
inline rvm<float32_t,4> cast_float32(const rvm<uint8_t,4> m0) {
	return mipp_cast_k_uint8_float32_m4(m0);
}
inline rvm<float32_t,8> cast_float32(const rvm<uint8_t,8> m0) {
	return mipp_cast_k_uint8_float32_m8(m0);
}
inline rvm<int64_t,1> cast_int64(const rvm<float64_t,1> m0) {
	return mipp_cast_k_float64_int64_m1(m0);
}
inline rvm<int64_t,2> cast_int64(const rvm<float64_t,2> m0) {
	return mipp_cast_k_float64_int64_m2(m0);
}
inline rvm<int64_t,4> cast_int64(const rvm<float64_t,4> m0) {
	return mipp_cast_k_float64_int64_m4(m0);
}
inline rvm<int64_t,8> cast_int64(const rvm<float64_t,8> m0) {
	return mipp_cast_k_float64_int64_m8(m0);
}
inline rvm<int64_t,1> cast_int64(const rvm<float32_t,1> m0) {
	return mipp_cast_k_float32_int64_m1(m0);
}
inline rvm<int64_t,2> cast_int64(const rvm<float32_t,2> m0) {
	return mipp_cast_k_float32_int64_m2(m0);
}
inline rvm<int64_t,4> cast_int64(const rvm<float32_t,4> m0) {
	return mipp_cast_k_float32_int64_m4(m0);
}
inline rvm<int64_t,8> cast_int64(const rvm<float32_t,8> m0) {
	return mipp_cast_k_float32_int64_m8(m0);
}
inline rvm<int64_t,1> cast_int64(const rvm<int64_t,1> m0) {
	return mipp_cast_k_int64_int64_m1(m0);
}
inline rvm<int64_t,2> cast_int64(const rvm<int64_t,2> m0) {
	return mipp_cast_k_int64_int64_m2(m0);
}
inline rvm<int64_t,4> cast_int64(const rvm<int64_t,4> m0) {
	return mipp_cast_k_int64_int64_m4(m0);
}
inline rvm<int64_t,8> cast_int64(const rvm<int64_t,8> m0) {
	return mipp_cast_k_int64_int64_m8(m0);
}
inline rvm<int64_t,1> cast_int64(const rvm<int32_t,1> m0) {
	return mipp_cast_k_int32_int64_m1(m0);
}
inline rvm<int64_t,2> cast_int64(const rvm<int32_t,2> m0) {
	return mipp_cast_k_int32_int64_m2(m0);
}
inline rvm<int64_t,4> cast_int64(const rvm<int32_t,4> m0) {
	return mipp_cast_k_int32_int64_m4(m0);
}
inline rvm<int64_t,8> cast_int64(const rvm<int32_t,8> m0) {
	return mipp_cast_k_int32_int64_m8(m0);
}
inline rvm<int64_t,1> cast_int64(const rvm<int16_t,1> m0) {
	return mipp_cast_k_int16_int64_m1(m0);
}
inline rvm<int64_t,2> cast_int64(const rvm<int16_t,2> m0) {
	return mipp_cast_k_int16_int64_m2(m0);
}
inline rvm<int64_t,4> cast_int64(const rvm<int16_t,4> m0) {
	return mipp_cast_k_int16_int64_m4(m0);
}
inline rvm<int64_t,8> cast_int64(const rvm<int16_t,8> m0) {
	return mipp_cast_k_int16_int64_m8(m0);
}
inline rvm<int64_t,1> cast_int64(const rvm<int8_t,1> m0) {
	return mipp_cast_k_int8_int64_m1(m0);
}
inline rvm<int64_t,2> cast_int64(const rvm<int8_t,2> m0) {
	return mipp_cast_k_int8_int64_m2(m0);
}
inline rvm<int64_t,4> cast_int64(const rvm<int8_t,4> m0) {
	return mipp_cast_k_int8_int64_m4(m0);
}
inline rvm<int64_t,8> cast_int64(const rvm<int8_t,8> m0) {
	return mipp_cast_k_int8_int64_m8(m0);
}
inline rvm<int64_t,1> cast_int64(const rvm<uint64_t,1> m0) {
	return mipp_cast_k_uint64_int64_m1(m0);
}
inline rvm<int64_t,2> cast_int64(const rvm<uint64_t,2> m0) {
	return mipp_cast_k_uint64_int64_m2(m0);
}
inline rvm<int64_t,4> cast_int64(const rvm<uint64_t,4> m0) {
	return mipp_cast_k_uint64_int64_m4(m0);
}
inline rvm<int64_t,8> cast_int64(const rvm<uint64_t,8> m0) {
	return mipp_cast_k_uint64_int64_m8(m0);
}
inline rvm<int64_t,1> cast_int64(const rvm<uint32_t,1> m0) {
	return mipp_cast_k_uint32_int64_m1(m0);
}
inline rvm<int64_t,2> cast_int64(const rvm<uint32_t,2> m0) {
	return mipp_cast_k_uint32_int64_m2(m0);
}
inline rvm<int64_t,4> cast_int64(const rvm<uint32_t,4> m0) {
	return mipp_cast_k_uint32_int64_m4(m0);
}
inline rvm<int64_t,8> cast_int64(const rvm<uint32_t,8> m0) {
	return mipp_cast_k_uint32_int64_m8(m0);
}
inline rvm<int64_t,1> cast_int64(const rvm<uint16_t,1> m0) {
	return mipp_cast_k_uint16_int64_m1(m0);
}
inline rvm<int64_t,2> cast_int64(const rvm<uint16_t,2> m0) {
	return mipp_cast_k_uint16_int64_m2(m0);
}
inline rvm<int64_t,4> cast_int64(const rvm<uint16_t,4> m0) {
	return mipp_cast_k_uint16_int64_m4(m0);
}
inline rvm<int64_t,8> cast_int64(const rvm<uint16_t,8> m0) {
	return mipp_cast_k_uint16_int64_m8(m0);
}
inline rvm<int64_t,1> cast_int64(const rvm<uint8_t,1> m0) {
	return mipp_cast_k_uint8_int64_m1(m0);
}
inline rvm<int64_t,2> cast_int64(const rvm<uint8_t,2> m0) {
	return mipp_cast_k_uint8_int64_m2(m0);
}
inline rvm<int64_t,4> cast_int64(const rvm<uint8_t,4> m0) {
	return mipp_cast_k_uint8_int64_m4(m0);
}
inline rvm<int64_t,8> cast_int64(const rvm<uint8_t,8> m0) {
	return mipp_cast_k_uint8_int64_m8(m0);
}
inline rvm<int32_t,1> cast_int32(const rvm<float64_t,1> m0) {
	return mipp_cast_k_float64_int32_m1(m0);
}
inline rvm<int32_t,2> cast_int32(const rvm<float64_t,2> m0) {
	return mipp_cast_k_float64_int32_m2(m0);
}
inline rvm<int32_t,4> cast_int32(const rvm<float64_t,4> m0) {
	return mipp_cast_k_float64_int32_m4(m0);
}
inline rvm<int32_t,8> cast_int32(const rvm<float64_t,8> m0) {
	return mipp_cast_k_float64_int32_m8(m0);
}
inline rvm<int32_t,1> cast_int32(const rvm<float32_t,1> m0) {
	return mipp_cast_k_float32_int32_m1(m0);
}
inline rvm<int32_t,2> cast_int32(const rvm<float32_t,2> m0) {
	return mipp_cast_k_float32_int32_m2(m0);
}
inline rvm<int32_t,4> cast_int32(const rvm<float32_t,4> m0) {
	return mipp_cast_k_float32_int32_m4(m0);
}
inline rvm<int32_t,8> cast_int32(const rvm<float32_t,8> m0) {
	return mipp_cast_k_float32_int32_m8(m0);
}
inline rvm<int32_t,1> cast_int32(const rvm<int64_t,1> m0) {
	return mipp_cast_k_int64_int32_m1(m0);
}
inline rvm<int32_t,2> cast_int32(const rvm<int64_t,2> m0) {
	return mipp_cast_k_int64_int32_m2(m0);
}
inline rvm<int32_t,4> cast_int32(const rvm<int64_t,4> m0) {
	return mipp_cast_k_int64_int32_m4(m0);
}
inline rvm<int32_t,8> cast_int32(const rvm<int64_t,8> m0) {
	return mipp_cast_k_int64_int32_m8(m0);
}
inline rvm<int32_t,1> cast_int32(const rvm<int32_t,1> m0) {
	return mipp_cast_k_int32_int32_m1(m0);
}
inline rvm<int32_t,2> cast_int32(const rvm<int32_t,2> m0) {
	return mipp_cast_k_int32_int32_m2(m0);
}
inline rvm<int32_t,4> cast_int32(const rvm<int32_t,4> m0) {
	return mipp_cast_k_int32_int32_m4(m0);
}
inline rvm<int32_t,8> cast_int32(const rvm<int32_t,8> m0) {
	return mipp_cast_k_int32_int32_m8(m0);
}
inline rvm<int32_t,1> cast_int32(const rvm<int16_t,1> m0) {
	return mipp_cast_k_int16_int32_m1(m0);
}
inline rvm<int32_t,2> cast_int32(const rvm<int16_t,2> m0) {
	return mipp_cast_k_int16_int32_m2(m0);
}
inline rvm<int32_t,4> cast_int32(const rvm<int16_t,4> m0) {
	return mipp_cast_k_int16_int32_m4(m0);
}
inline rvm<int32_t,8> cast_int32(const rvm<int16_t,8> m0) {
	return mipp_cast_k_int16_int32_m8(m0);
}
inline rvm<int32_t,1> cast_int32(const rvm<int8_t,1> m0) {
	return mipp_cast_k_int8_int32_m1(m0);
}
inline rvm<int32_t,2> cast_int32(const rvm<int8_t,2> m0) {
	return mipp_cast_k_int8_int32_m2(m0);
}
inline rvm<int32_t,4> cast_int32(const rvm<int8_t,4> m0) {
	return mipp_cast_k_int8_int32_m4(m0);
}
inline rvm<int32_t,8> cast_int32(const rvm<int8_t,8> m0) {
	return mipp_cast_k_int8_int32_m8(m0);
}
inline rvm<int32_t,1> cast_int32(const rvm<uint64_t,1> m0) {
	return mipp_cast_k_uint64_int32_m1(m0);
}
inline rvm<int32_t,2> cast_int32(const rvm<uint64_t,2> m0) {
	return mipp_cast_k_uint64_int32_m2(m0);
}
inline rvm<int32_t,4> cast_int32(const rvm<uint64_t,4> m0) {
	return mipp_cast_k_uint64_int32_m4(m0);
}
inline rvm<int32_t,8> cast_int32(const rvm<uint64_t,8> m0) {
	return mipp_cast_k_uint64_int32_m8(m0);
}
inline rvm<int32_t,1> cast_int32(const rvm<uint32_t,1> m0) {
	return mipp_cast_k_uint32_int32_m1(m0);
}
inline rvm<int32_t,2> cast_int32(const rvm<uint32_t,2> m0) {
	return mipp_cast_k_uint32_int32_m2(m0);
}
inline rvm<int32_t,4> cast_int32(const rvm<uint32_t,4> m0) {
	return mipp_cast_k_uint32_int32_m4(m0);
}
inline rvm<int32_t,8> cast_int32(const rvm<uint32_t,8> m0) {
	return mipp_cast_k_uint32_int32_m8(m0);
}
inline rvm<int32_t,1> cast_int32(const rvm<uint16_t,1> m0) {
	return mipp_cast_k_uint16_int32_m1(m0);
}
inline rvm<int32_t,2> cast_int32(const rvm<uint16_t,2> m0) {
	return mipp_cast_k_uint16_int32_m2(m0);
}
inline rvm<int32_t,4> cast_int32(const rvm<uint16_t,4> m0) {
	return mipp_cast_k_uint16_int32_m4(m0);
}
inline rvm<int32_t,8> cast_int32(const rvm<uint16_t,8> m0) {
	return mipp_cast_k_uint16_int32_m8(m0);
}
inline rvm<int32_t,1> cast_int32(const rvm<uint8_t,1> m0) {
	return mipp_cast_k_uint8_int32_m1(m0);
}
inline rvm<int32_t,2> cast_int32(const rvm<uint8_t,2> m0) {
	return mipp_cast_k_uint8_int32_m2(m0);
}
inline rvm<int32_t,4> cast_int32(const rvm<uint8_t,4> m0) {
	return mipp_cast_k_uint8_int32_m4(m0);
}
inline rvm<int32_t,8> cast_int32(const rvm<uint8_t,8> m0) {
	return mipp_cast_k_uint8_int32_m8(m0);
}
inline rvm<int16_t,1> cast_int16(const rvm<float64_t,1> m0) {
	return mipp_cast_k_float64_int16_m1(m0);
}
inline rvm<int16_t,2> cast_int16(const rvm<float64_t,2> m0) {
	return mipp_cast_k_float64_int16_m2(m0);
}
inline rvm<int16_t,4> cast_int16(const rvm<float64_t,4> m0) {
	return mipp_cast_k_float64_int16_m4(m0);
}
inline rvm<int16_t,8> cast_int16(const rvm<float64_t,8> m0) {
	return mipp_cast_k_float64_int16_m8(m0);
}
inline rvm<int16_t,1> cast_int16(const rvm<float32_t,1> m0) {
	return mipp_cast_k_float32_int16_m1(m0);
}
inline rvm<int16_t,2> cast_int16(const rvm<float32_t,2> m0) {
	return mipp_cast_k_float32_int16_m2(m0);
}
inline rvm<int16_t,4> cast_int16(const rvm<float32_t,4> m0) {
	return mipp_cast_k_float32_int16_m4(m0);
}
inline rvm<int16_t,8> cast_int16(const rvm<float32_t,8> m0) {
	return mipp_cast_k_float32_int16_m8(m0);
}
inline rvm<int16_t,1> cast_int16(const rvm<int64_t,1> m0) {
	return mipp_cast_k_int64_int16_m1(m0);
}
inline rvm<int16_t,2> cast_int16(const rvm<int64_t,2> m0) {
	return mipp_cast_k_int64_int16_m2(m0);
}
inline rvm<int16_t,4> cast_int16(const rvm<int64_t,4> m0) {
	return mipp_cast_k_int64_int16_m4(m0);
}
inline rvm<int16_t,8> cast_int16(const rvm<int64_t,8> m0) {
	return mipp_cast_k_int64_int16_m8(m0);
}
inline rvm<int16_t,1> cast_int16(const rvm<int32_t,1> m0) {
	return mipp_cast_k_int32_int16_m1(m0);
}
inline rvm<int16_t,2> cast_int16(const rvm<int32_t,2> m0) {
	return mipp_cast_k_int32_int16_m2(m0);
}
inline rvm<int16_t,4> cast_int16(const rvm<int32_t,4> m0) {
	return mipp_cast_k_int32_int16_m4(m0);
}
inline rvm<int16_t,8> cast_int16(const rvm<int32_t,8> m0) {
	return mipp_cast_k_int32_int16_m8(m0);
}
inline rvm<int16_t,1> cast_int16(const rvm<int16_t,1> m0) {
	return mipp_cast_k_int16_int16_m1(m0);
}
inline rvm<int16_t,2> cast_int16(const rvm<int16_t,2> m0) {
	return mipp_cast_k_int16_int16_m2(m0);
}
inline rvm<int16_t,4> cast_int16(const rvm<int16_t,4> m0) {
	return mipp_cast_k_int16_int16_m4(m0);
}
inline rvm<int16_t,8> cast_int16(const rvm<int16_t,8> m0) {
	return mipp_cast_k_int16_int16_m8(m0);
}
inline rvm<int16_t,1> cast_int16(const rvm<int8_t,1> m0) {
	return mipp_cast_k_int8_int16_m1(m0);
}
inline rvm<int16_t,2> cast_int16(const rvm<int8_t,2> m0) {
	return mipp_cast_k_int8_int16_m2(m0);
}
inline rvm<int16_t,4> cast_int16(const rvm<int8_t,4> m0) {
	return mipp_cast_k_int8_int16_m4(m0);
}
inline rvm<int16_t,8> cast_int16(const rvm<int8_t,8> m0) {
	return mipp_cast_k_int8_int16_m8(m0);
}
inline rvm<int16_t,1> cast_int16(const rvm<uint64_t,1> m0) {
	return mipp_cast_k_uint64_int16_m1(m0);
}
inline rvm<int16_t,2> cast_int16(const rvm<uint64_t,2> m0) {
	return mipp_cast_k_uint64_int16_m2(m0);
}
inline rvm<int16_t,4> cast_int16(const rvm<uint64_t,4> m0) {
	return mipp_cast_k_uint64_int16_m4(m0);
}
inline rvm<int16_t,8> cast_int16(const rvm<uint64_t,8> m0) {
	return mipp_cast_k_uint64_int16_m8(m0);
}
inline rvm<int16_t,1> cast_int16(const rvm<uint32_t,1> m0) {
	return mipp_cast_k_uint32_int16_m1(m0);
}
inline rvm<int16_t,2> cast_int16(const rvm<uint32_t,2> m0) {
	return mipp_cast_k_uint32_int16_m2(m0);
}
inline rvm<int16_t,4> cast_int16(const rvm<uint32_t,4> m0) {
	return mipp_cast_k_uint32_int16_m4(m0);
}
inline rvm<int16_t,8> cast_int16(const rvm<uint32_t,8> m0) {
	return mipp_cast_k_uint32_int16_m8(m0);
}
inline rvm<int16_t,1> cast_int16(const rvm<uint16_t,1> m0) {
	return mipp_cast_k_uint16_int16_m1(m0);
}
inline rvm<int16_t,2> cast_int16(const rvm<uint16_t,2> m0) {
	return mipp_cast_k_uint16_int16_m2(m0);
}
inline rvm<int16_t,4> cast_int16(const rvm<uint16_t,4> m0) {
	return mipp_cast_k_uint16_int16_m4(m0);
}
inline rvm<int16_t,8> cast_int16(const rvm<uint16_t,8> m0) {
	return mipp_cast_k_uint16_int16_m8(m0);
}
inline rvm<int16_t,1> cast_int16(const rvm<uint8_t,1> m0) {
	return mipp_cast_k_uint8_int16_m1(m0);
}
inline rvm<int16_t,2> cast_int16(const rvm<uint8_t,2> m0) {
	return mipp_cast_k_uint8_int16_m2(m0);
}
inline rvm<int16_t,4> cast_int16(const rvm<uint8_t,4> m0) {
	return mipp_cast_k_uint8_int16_m4(m0);
}
inline rvm<int16_t,8> cast_int16(const rvm<uint8_t,8> m0) {
	return mipp_cast_k_uint8_int16_m8(m0);
}
inline rvm<int8_t,1> cast_int8(const rvm<float64_t,1> m0) {
	return mipp_cast_k_float64_int8_m1(m0);
}
inline rvm<int8_t,2> cast_int8(const rvm<float64_t,2> m0) {
	return mipp_cast_k_float64_int8_m2(m0);
}
inline rvm<int8_t,4> cast_int8(const rvm<float64_t,4> m0) {
	return mipp_cast_k_float64_int8_m4(m0);
}
inline rvm<int8_t,8> cast_int8(const rvm<float64_t,8> m0) {
	return mipp_cast_k_float64_int8_m8(m0);
}
inline rvm<int8_t,1> cast_int8(const rvm<float32_t,1> m0) {
	return mipp_cast_k_float32_int8_m1(m0);
}
inline rvm<int8_t,2> cast_int8(const rvm<float32_t,2> m0) {
	return mipp_cast_k_float32_int8_m2(m0);
}
inline rvm<int8_t,4> cast_int8(const rvm<float32_t,4> m0) {
	return mipp_cast_k_float32_int8_m4(m0);
}
inline rvm<int8_t,8> cast_int8(const rvm<float32_t,8> m0) {
	return mipp_cast_k_float32_int8_m8(m0);
}
inline rvm<int8_t,1> cast_int8(const rvm<int64_t,1> m0) {
	return mipp_cast_k_int64_int8_m1(m0);
}
inline rvm<int8_t,2> cast_int8(const rvm<int64_t,2> m0) {
	return mipp_cast_k_int64_int8_m2(m0);
}
inline rvm<int8_t,4> cast_int8(const rvm<int64_t,4> m0) {
	return mipp_cast_k_int64_int8_m4(m0);
}
inline rvm<int8_t,8> cast_int8(const rvm<int64_t,8> m0) {
	return mipp_cast_k_int64_int8_m8(m0);
}
inline rvm<int8_t,1> cast_int8(const rvm<int32_t,1> m0) {
	return mipp_cast_k_int32_int8_m1(m0);
}
inline rvm<int8_t,2> cast_int8(const rvm<int32_t,2> m0) {
	return mipp_cast_k_int32_int8_m2(m0);
}
inline rvm<int8_t,4> cast_int8(const rvm<int32_t,4> m0) {
	return mipp_cast_k_int32_int8_m4(m0);
}
inline rvm<int8_t,8> cast_int8(const rvm<int32_t,8> m0) {
	return mipp_cast_k_int32_int8_m8(m0);
}
inline rvm<int8_t,1> cast_int8(const rvm<int16_t,1> m0) {
	return mipp_cast_k_int16_int8_m1(m0);
}
inline rvm<int8_t,2> cast_int8(const rvm<int16_t,2> m0) {
	return mipp_cast_k_int16_int8_m2(m0);
}
inline rvm<int8_t,4> cast_int8(const rvm<int16_t,4> m0) {
	return mipp_cast_k_int16_int8_m4(m0);
}
inline rvm<int8_t,8> cast_int8(const rvm<int16_t,8> m0) {
	return mipp_cast_k_int16_int8_m8(m0);
}
inline rvm<int8_t,1> cast_int8(const rvm<int8_t,1> m0) {
	return mipp_cast_k_int8_int8_m1(m0);
}
inline rvm<int8_t,2> cast_int8(const rvm<int8_t,2> m0) {
	return mipp_cast_k_int8_int8_m2(m0);
}
inline rvm<int8_t,4> cast_int8(const rvm<int8_t,4> m0) {
	return mipp_cast_k_int8_int8_m4(m0);
}
inline rvm<int8_t,8> cast_int8(const rvm<int8_t,8> m0) {
	return mipp_cast_k_int8_int8_m8(m0);
}
inline rvm<int8_t,1> cast_int8(const rvm<uint64_t,1> m0) {
	return mipp_cast_k_uint64_int8_m1(m0);
}
inline rvm<int8_t,2> cast_int8(const rvm<uint64_t,2> m0) {
	return mipp_cast_k_uint64_int8_m2(m0);
}
inline rvm<int8_t,4> cast_int8(const rvm<uint64_t,4> m0) {
	return mipp_cast_k_uint64_int8_m4(m0);
}
inline rvm<int8_t,8> cast_int8(const rvm<uint64_t,8> m0) {
	return mipp_cast_k_uint64_int8_m8(m0);
}
inline rvm<int8_t,1> cast_int8(const rvm<uint32_t,1> m0) {
	return mipp_cast_k_uint32_int8_m1(m0);
}
inline rvm<int8_t,2> cast_int8(const rvm<uint32_t,2> m0) {
	return mipp_cast_k_uint32_int8_m2(m0);
}
inline rvm<int8_t,4> cast_int8(const rvm<uint32_t,4> m0) {
	return mipp_cast_k_uint32_int8_m4(m0);
}
inline rvm<int8_t,8> cast_int8(const rvm<uint32_t,8> m0) {
	return mipp_cast_k_uint32_int8_m8(m0);
}
inline rvm<int8_t,1> cast_int8(const rvm<uint16_t,1> m0) {
	return mipp_cast_k_uint16_int8_m1(m0);
}
inline rvm<int8_t,2> cast_int8(const rvm<uint16_t,2> m0) {
	return mipp_cast_k_uint16_int8_m2(m0);
}
inline rvm<int8_t,4> cast_int8(const rvm<uint16_t,4> m0) {
	return mipp_cast_k_uint16_int8_m4(m0);
}
inline rvm<int8_t,8> cast_int8(const rvm<uint16_t,8> m0) {
	return mipp_cast_k_uint16_int8_m8(m0);
}
inline rvm<int8_t,1> cast_int8(const rvm<uint8_t,1> m0) {
	return mipp_cast_k_uint8_int8_m1(m0);
}
inline rvm<int8_t,2> cast_int8(const rvm<uint8_t,2> m0) {
	return mipp_cast_k_uint8_int8_m2(m0);
}
inline rvm<int8_t,4> cast_int8(const rvm<uint8_t,4> m0) {
	return mipp_cast_k_uint8_int8_m4(m0);
}
inline rvm<int8_t,8> cast_int8(const rvm<uint8_t,8> m0) {
	return mipp_cast_k_uint8_int8_m8(m0);
}
inline rvm<uint64_t,1> cast_uint64(const rvm<float64_t,1> m0) {
	return mipp_cast_k_float64_uint64_m1(m0);
}
inline rvm<uint64_t,2> cast_uint64(const rvm<float64_t,2> m0) {
	return mipp_cast_k_float64_uint64_m2(m0);
}
inline rvm<uint64_t,4> cast_uint64(const rvm<float64_t,4> m0) {
	return mipp_cast_k_float64_uint64_m4(m0);
}
inline rvm<uint64_t,8> cast_uint64(const rvm<float64_t,8> m0) {
	return mipp_cast_k_float64_uint64_m8(m0);
}
inline rvm<uint64_t,1> cast_uint64(const rvm<float32_t,1> m0) {
	return mipp_cast_k_float32_uint64_m1(m0);
}
inline rvm<uint64_t,2> cast_uint64(const rvm<float32_t,2> m0) {
	return mipp_cast_k_float32_uint64_m2(m0);
}
inline rvm<uint64_t,4> cast_uint64(const rvm<float32_t,4> m0) {
	return mipp_cast_k_float32_uint64_m4(m0);
}
inline rvm<uint64_t,8> cast_uint64(const rvm<float32_t,8> m0) {
	return mipp_cast_k_float32_uint64_m8(m0);
}
inline rvm<uint64_t,1> cast_uint64(const rvm<int64_t,1> m0) {
	return mipp_cast_k_int64_uint64_m1(m0);
}
inline rvm<uint64_t,2> cast_uint64(const rvm<int64_t,2> m0) {
	return mipp_cast_k_int64_uint64_m2(m0);
}
inline rvm<uint64_t,4> cast_uint64(const rvm<int64_t,4> m0) {
	return mipp_cast_k_int64_uint64_m4(m0);
}
inline rvm<uint64_t,8> cast_uint64(const rvm<int64_t,8> m0) {
	return mipp_cast_k_int64_uint64_m8(m0);
}
inline rvm<uint64_t,1> cast_uint64(const rvm<int32_t,1> m0) {
	return mipp_cast_k_int32_uint64_m1(m0);
}
inline rvm<uint64_t,2> cast_uint64(const rvm<int32_t,2> m0) {
	return mipp_cast_k_int32_uint64_m2(m0);
}
inline rvm<uint64_t,4> cast_uint64(const rvm<int32_t,4> m0) {
	return mipp_cast_k_int32_uint64_m4(m0);
}
inline rvm<uint64_t,8> cast_uint64(const rvm<int32_t,8> m0) {
	return mipp_cast_k_int32_uint64_m8(m0);
}
inline rvm<uint64_t,1> cast_uint64(const rvm<int16_t,1> m0) {
	return mipp_cast_k_int16_uint64_m1(m0);
}
inline rvm<uint64_t,2> cast_uint64(const rvm<int16_t,2> m0) {
	return mipp_cast_k_int16_uint64_m2(m0);
}
inline rvm<uint64_t,4> cast_uint64(const rvm<int16_t,4> m0) {
	return mipp_cast_k_int16_uint64_m4(m0);
}
inline rvm<uint64_t,8> cast_uint64(const rvm<int16_t,8> m0) {
	return mipp_cast_k_int16_uint64_m8(m0);
}
inline rvm<uint64_t,1> cast_uint64(const rvm<int8_t,1> m0) {
	return mipp_cast_k_int8_uint64_m1(m0);
}
inline rvm<uint64_t,2> cast_uint64(const rvm<int8_t,2> m0) {
	return mipp_cast_k_int8_uint64_m2(m0);
}
inline rvm<uint64_t,4> cast_uint64(const rvm<int8_t,4> m0) {
	return mipp_cast_k_int8_uint64_m4(m0);
}
inline rvm<uint64_t,8> cast_uint64(const rvm<int8_t,8> m0) {
	return mipp_cast_k_int8_uint64_m8(m0);
}
inline rvm<uint64_t,1> cast_uint64(const rvm<uint64_t,1> m0) {
	return mipp_cast_k_uint64_uint64_m1(m0);
}
inline rvm<uint64_t,2> cast_uint64(const rvm<uint64_t,2> m0) {
	return mipp_cast_k_uint64_uint64_m2(m0);
}
inline rvm<uint64_t,4> cast_uint64(const rvm<uint64_t,4> m0) {
	return mipp_cast_k_uint64_uint64_m4(m0);
}
inline rvm<uint64_t,8> cast_uint64(const rvm<uint64_t,8> m0) {
	return mipp_cast_k_uint64_uint64_m8(m0);
}
inline rvm<uint64_t,1> cast_uint64(const rvm<uint32_t,1> m0) {
	return mipp_cast_k_uint32_uint64_m1(m0);
}
inline rvm<uint64_t,2> cast_uint64(const rvm<uint32_t,2> m0) {
	return mipp_cast_k_uint32_uint64_m2(m0);
}
inline rvm<uint64_t,4> cast_uint64(const rvm<uint32_t,4> m0) {
	return mipp_cast_k_uint32_uint64_m4(m0);
}
inline rvm<uint64_t,8> cast_uint64(const rvm<uint32_t,8> m0) {
	return mipp_cast_k_uint32_uint64_m8(m0);
}
inline rvm<uint64_t,1> cast_uint64(const rvm<uint16_t,1> m0) {
	return mipp_cast_k_uint16_uint64_m1(m0);
}
inline rvm<uint64_t,2> cast_uint64(const rvm<uint16_t,2> m0) {
	return mipp_cast_k_uint16_uint64_m2(m0);
}
inline rvm<uint64_t,4> cast_uint64(const rvm<uint16_t,4> m0) {
	return mipp_cast_k_uint16_uint64_m4(m0);
}
inline rvm<uint64_t,8> cast_uint64(const rvm<uint16_t,8> m0) {
	return mipp_cast_k_uint16_uint64_m8(m0);
}
inline rvm<uint64_t,1> cast_uint64(const rvm<uint8_t,1> m0) {
	return mipp_cast_k_uint8_uint64_m1(m0);
}
inline rvm<uint64_t,2> cast_uint64(const rvm<uint8_t,2> m0) {
	return mipp_cast_k_uint8_uint64_m2(m0);
}
inline rvm<uint64_t,4> cast_uint64(const rvm<uint8_t,4> m0) {
	return mipp_cast_k_uint8_uint64_m4(m0);
}
inline rvm<uint64_t,8> cast_uint64(const rvm<uint8_t,8> m0) {
	return mipp_cast_k_uint8_uint64_m8(m0);
}
inline rvm<uint32_t,1> cast_uint32(const rvm<float64_t,1> m0) {
	return mipp_cast_k_float64_uint32_m1(m0);
}
inline rvm<uint32_t,2> cast_uint32(const rvm<float64_t,2> m0) {
	return mipp_cast_k_float64_uint32_m2(m0);
}
inline rvm<uint32_t,4> cast_uint32(const rvm<float64_t,4> m0) {
	return mipp_cast_k_float64_uint32_m4(m0);
}
inline rvm<uint32_t,8> cast_uint32(const rvm<float64_t,8> m0) {
	return mipp_cast_k_float64_uint32_m8(m0);
}
inline rvm<uint32_t,1> cast_uint32(const rvm<float32_t,1> m0) {
	return mipp_cast_k_float32_uint32_m1(m0);
}
inline rvm<uint32_t,2> cast_uint32(const rvm<float32_t,2> m0) {
	return mipp_cast_k_float32_uint32_m2(m0);
}
inline rvm<uint32_t,4> cast_uint32(const rvm<float32_t,4> m0) {
	return mipp_cast_k_float32_uint32_m4(m0);
}
inline rvm<uint32_t,8> cast_uint32(const rvm<float32_t,8> m0) {
	return mipp_cast_k_float32_uint32_m8(m0);
}
inline rvm<uint32_t,1> cast_uint32(const rvm<int64_t,1> m0) {
	return mipp_cast_k_int64_uint32_m1(m0);
}
inline rvm<uint32_t,2> cast_uint32(const rvm<int64_t,2> m0) {
	return mipp_cast_k_int64_uint32_m2(m0);
}
inline rvm<uint32_t,4> cast_uint32(const rvm<int64_t,4> m0) {
	return mipp_cast_k_int64_uint32_m4(m0);
}
inline rvm<uint32_t,8> cast_uint32(const rvm<int64_t,8> m0) {
	return mipp_cast_k_int64_uint32_m8(m0);
}
inline rvm<uint32_t,1> cast_uint32(const rvm<int32_t,1> m0) {
	return mipp_cast_k_int32_uint32_m1(m0);
}
inline rvm<uint32_t,2> cast_uint32(const rvm<int32_t,2> m0) {
	return mipp_cast_k_int32_uint32_m2(m0);
}
inline rvm<uint32_t,4> cast_uint32(const rvm<int32_t,4> m0) {
	return mipp_cast_k_int32_uint32_m4(m0);
}
inline rvm<uint32_t,8> cast_uint32(const rvm<int32_t,8> m0) {
	return mipp_cast_k_int32_uint32_m8(m0);
}
inline rvm<uint32_t,1> cast_uint32(const rvm<int16_t,1> m0) {
	return mipp_cast_k_int16_uint32_m1(m0);
}
inline rvm<uint32_t,2> cast_uint32(const rvm<int16_t,2> m0) {
	return mipp_cast_k_int16_uint32_m2(m0);
}
inline rvm<uint32_t,4> cast_uint32(const rvm<int16_t,4> m0) {
	return mipp_cast_k_int16_uint32_m4(m0);
}
inline rvm<uint32_t,8> cast_uint32(const rvm<int16_t,8> m0) {
	return mipp_cast_k_int16_uint32_m8(m0);
}
inline rvm<uint32_t,1> cast_uint32(const rvm<int8_t,1> m0) {
	return mipp_cast_k_int8_uint32_m1(m0);
}
inline rvm<uint32_t,2> cast_uint32(const rvm<int8_t,2> m0) {
	return mipp_cast_k_int8_uint32_m2(m0);
}
inline rvm<uint32_t,4> cast_uint32(const rvm<int8_t,4> m0) {
	return mipp_cast_k_int8_uint32_m4(m0);
}
inline rvm<uint32_t,8> cast_uint32(const rvm<int8_t,8> m0) {
	return mipp_cast_k_int8_uint32_m8(m0);
}
inline rvm<uint32_t,1> cast_uint32(const rvm<uint64_t,1> m0) {
	return mipp_cast_k_uint64_uint32_m1(m0);
}
inline rvm<uint32_t,2> cast_uint32(const rvm<uint64_t,2> m0) {
	return mipp_cast_k_uint64_uint32_m2(m0);
}
inline rvm<uint32_t,4> cast_uint32(const rvm<uint64_t,4> m0) {
	return mipp_cast_k_uint64_uint32_m4(m0);
}
inline rvm<uint32_t,8> cast_uint32(const rvm<uint64_t,8> m0) {
	return mipp_cast_k_uint64_uint32_m8(m0);
}
inline rvm<uint32_t,1> cast_uint32(const rvm<uint32_t,1> m0) {
	return mipp_cast_k_uint32_uint32_m1(m0);
}
inline rvm<uint32_t,2> cast_uint32(const rvm<uint32_t,2> m0) {
	return mipp_cast_k_uint32_uint32_m2(m0);
}
inline rvm<uint32_t,4> cast_uint32(const rvm<uint32_t,4> m0) {
	return mipp_cast_k_uint32_uint32_m4(m0);
}
inline rvm<uint32_t,8> cast_uint32(const rvm<uint32_t,8> m0) {
	return mipp_cast_k_uint32_uint32_m8(m0);
}
inline rvm<uint32_t,1> cast_uint32(const rvm<uint16_t,1> m0) {
	return mipp_cast_k_uint16_uint32_m1(m0);
}
inline rvm<uint32_t,2> cast_uint32(const rvm<uint16_t,2> m0) {
	return mipp_cast_k_uint16_uint32_m2(m0);
}
inline rvm<uint32_t,4> cast_uint32(const rvm<uint16_t,4> m0) {
	return mipp_cast_k_uint16_uint32_m4(m0);
}
inline rvm<uint32_t,8> cast_uint32(const rvm<uint16_t,8> m0) {
	return mipp_cast_k_uint16_uint32_m8(m0);
}
inline rvm<uint32_t,1> cast_uint32(const rvm<uint8_t,1> m0) {
	return mipp_cast_k_uint8_uint32_m1(m0);
}
inline rvm<uint32_t,2> cast_uint32(const rvm<uint8_t,2> m0) {
	return mipp_cast_k_uint8_uint32_m2(m0);
}
inline rvm<uint32_t,4> cast_uint32(const rvm<uint8_t,4> m0) {
	return mipp_cast_k_uint8_uint32_m4(m0);
}
inline rvm<uint32_t,8> cast_uint32(const rvm<uint8_t,8> m0) {
	return mipp_cast_k_uint8_uint32_m8(m0);
}
inline rvm<uint16_t,1> cast_uint16(const rvm<float64_t,1> m0) {
	return mipp_cast_k_float64_uint16_m1(m0);
}
inline rvm<uint16_t,2> cast_uint16(const rvm<float64_t,2> m0) {
	return mipp_cast_k_float64_uint16_m2(m0);
}
inline rvm<uint16_t,4> cast_uint16(const rvm<float64_t,4> m0) {
	return mipp_cast_k_float64_uint16_m4(m0);
}
inline rvm<uint16_t,8> cast_uint16(const rvm<float64_t,8> m0) {
	return mipp_cast_k_float64_uint16_m8(m0);
}
inline rvm<uint16_t,1> cast_uint16(const rvm<float32_t,1> m0) {
	return mipp_cast_k_float32_uint16_m1(m0);
}
inline rvm<uint16_t,2> cast_uint16(const rvm<float32_t,2> m0) {
	return mipp_cast_k_float32_uint16_m2(m0);
}
inline rvm<uint16_t,4> cast_uint16(const rvm<float32_t,4> m0) {
	return mipp_cast_k_float32_uint16_m4(m0);
}
inline rvm<uint16_t,8> cast_uint16(const rvm<float32_t,8> m0) {
	return mipp_cast_k_float32_uint16_m8(m0);
}
inline rvm<uint16_t,1> cast_uint16(const rvm<int64_t,1> m0) {
	return mipp_cast_k_int64_uint16_m1(m0);
}
inline rvm<uint16_t,2> cast_uint16(const rvm<int64_t,2> m0) {
	return mipp_cast_k_int64_uint16_m2(m0);
}
inline rvm<uint16_t,4> cast_uint16(const rvm<int64_t,4> m0) {
	return mipp_cast_k_int64_uint16_m4(m0);
}
inline rvm<uint16_t,8> cast_uint16(const rvm<int64_t,8> m0) {
	return mipp_cast_k_int64_uint16_m8(m0);
}
inline rvm<uint16_t,1> cast_uint16(const rvm<int32_t,1> m0) {
	return mipp_cast_k_int32_uint16_m1(m0);
}
inline rvm<uint16_t,2> cast_uint16(const rvm<int32_t,2> m0) {
	return mipp_cast_k_int32_uint16_m2(m0);
}
inline rvm<uint16_t,4> cast_uint16(const rvm<int32_t,4> m0) {
	return mipp_cast_k_int32_uint16_m4(m0);
}
inline rvm<uint16_t,8> cast_uint16(const rvm<int32_t,8> m0) {
	return mipp_cast_k_int32_uint16_m8(m0);
}
inline rvm<uint16_t,1> cast_uint16(const rvm<int16_t,1> m0) {
	return mipp_cast_k_int16_uint16_m1(m0);
}
inline rvm<uint16_t,2> cast_uint16(const rvm<int16_t,2> m0) {
	return mipp_cast_k_int16_uint16_m2(m0);
}
inline rvm<uint16_t,4> cast_uint16(const rvm<int16_t,4> m0) {
	return mipp_cast_k_int16_uint16_m4(m0);
}
inline rvm<uint16_t,8> cast_uint16(const rvm<int16_t,8> m0) {
	return mipp_cast_k_int16_uint16_m8(m0);
}
inline rvm<uint16_t,1> cast_uint16(const rvm<int8_t,1> m0) {
	return mipp_cast_k_int8_uint16_m1(m0);
}
inline rvm<uint16_t,2> cast_uint16(const rvm<int8_t,2> m0) {
	return mipp_cast_k_int8_uint16_m2(m0);
}
inline rvm<uint16_t,4> cast_uint16(const rvm<int8_t,4> m0) {
	return mipp_cast_k_int8_uint16_m4(m0);
}
inline rvm<uint16_t,8> cast_uint16(const rvm<int8_t,8> m0) {
	return mipp_cast_k_int8_uint16_m8(m0);
}
inline rvm<uint16_t,1> cast_uint16(const rvm<uint64_t,1> m0) {
	return mipp_cast_k_uint64_uint16_m1(m0);
}
inline rvm<uint16_t,2> cast_uint16(const rvm<uint64_t,2> m0) {
	return mipp_cast_k_uint64_uint16_m2(m0);
}
inline rvm<uint16_t,4> cast_uint16(const rvm<uint64_t,4> m0) {
	return mipp_cast_k_uint64_uint16_m4(m0);
}
inline rvm<uint16_t,8> cast_uint16(const rvm<uint64_t,8> m0) {
	return mipp_cast_k_uint64_uint16_m8(m0);
}
inline rvm<uint16_t,1> cast_uint16(const rvm<uint32_t,1> m0) {
	return mipp_cast_k_uint32_uint16_m1(m0);
}
inline rvm<uint16_t,2> cast_uint16(const rvm<uint32_t,2> m0) {
	return mipp_cast_k_uint32_uint16_m2(m0);
}
inline rvm<uint16_t,4> cast_uint16(const rvm<uint32_t,4> m0) {
	return mipp_cast_k_uint32_uint16_m4(m0);
}
inline rvm<uint16_t,8> cast_uint16(const rvm<uint32_t,8> m0) {
	return mipp_cast_k_uint32_uint16_m8(m0);
}
inline rvm<uint16_t,1> cast_uint16(const rvm<uint16_t,1> m0) {
	return mipp_cast_k_uint16_uint16_m1(m0);
}
inline rvm<uint16_t,2> cast_uint16(const rvm<uint16_t,2> m0) {
	return mipp_cast_k_uint16_uint16_m2(m0);
}
inline rvm<uint16_t,4> cast_uint16(const rvm<uint16_t,4> m0) {
	return mipp_cast_k_uint16_uint16_m4(m0);
}
inline rvm<uint16_t,8> cast_uint16(const rvm<uint16_t,8> m0) {
	return mipp_cast_k_uint16_uint16_m8(m0);
}
inline rvm<uint16_t,1> cast_uint16(const rvm<uint8_t,1> m0) {
	return mipp_cast_k_uint8_uint16_m1(m0);
}
inline rvm<uint16_t,2> cast_uint16(const rvm<uint8_t,2> m0) {
	return mipp_cast_k_uint8_uint16_m2(m0);
}
inline rvm<uint16_t,4> cast_uint16(const rvm<uint8_t,4> m0) {
	return mipp_cast_k_uint8_uint16_m4(m0);
}
inline rvm<uint16_t,8> cast_uint16(const rvm<uint8_t,8> m0) {
	return mipp_cast_k_uint8_uint16_m8(m0);
}
inline rvm<uint8_t,1> cast_uint8(const rvm<float64_t,1> m0) {
	return mipp_cast_k_float64_uint8_m1(m0);
}
inline rvm<uint8_t,2> cast_uint8(const rvm<float64_t,2> m0) {
	return mipp_cast_k_float64_uint8_m2(m0);
}
inline rvm<uint8_t,4> cast_uint8(const rvm<float64_t,4> m0) {
	return mipp_cast_k_float64_uint8_m4(m0);
}
inline rvm<uint8_t,8> cast_uint8(const rvm<float64_t,8> m0) {
	return mipp_cast_k_float64_uint8_m8(m0);
}
inline rvm<uint8_t,1> cast_uint8(const rvm<float32_t,1> m0) {
	return mipp_cast_k_float32_uint8_m1(m0);
}
inline rvm<uint8_t,2> cast_uint8(const rvm<float32_t,2> m0) {
	return mipp_cast_k_float32_uint8_m2(m0);
}
inline rvm<uint8_t,4> cast_uint8(const rvm<float32_t,4> m0) {
	return mipp_cast_k_float32_uint8_m4(m0);
}
inline rvm<uint8_t,8> cast_uint8(const rvm<float32_t,8> m0) {
	return mipp_cast_k_float32_uint8_m8(m0);
}
inline rvm<uint8_t,1> cast_uint8(const rvm<int64_t,1> m0) {
	return mipp_cast_k_int64_uint8_m1(m0);
}
inline rvm<uint8_t,2> cast_uint8(const rvm<int64_t,2> m0) {
	return mipp_cast_k_int64_uint8_m2(m0);
}
inline rvm<uint8_t,4> cast_uint8(const rvm<int64_t,4> m0) {
	return mipp_cast_k_int64_uint8_m4(m0);
}
inline rvm<uint8_t,8> cast_uint8(const rvm<int64_t,8> m0) {
	return mipp_cast_k_int64_uint8_m8(m0);
}
inline rvm<uint8_t,1> cast_uint8(const rvm<int32_t,1> m0) {
	return mipp_cast_k_int32_uint8_m1(m0);
}
inline rvm<uint8_t,2> cast_uint8(const rvm<int32_t,2> m0) {
	return mipp_cast_k_int32_uint8_m2(m0);
}
inline rvm<uint8_t,4> cast_uint8(const rvm<int32_t,4> m0) {
	return mipp_cast_k_int32_uint8_m4(m0);
}
inline rvm<uint8_t,8> cast_uint8(const rvm<int32_t,8> m0) {
	return mipp_cast_k_int32_uint8_m8(m0);
}
inline rvm<uint8_t,1> cast_uint8(const rvm<int16_t,1> m0) {
	return mipp_cast_k_int16_uint8_m1(m0);
}
inline rvm<uint8_t,2> cast_uint8(const rvm<int16_t,2> m0) {
	return mipp_cast_k_int16_uint8_m2(m0);
}
inline rvm<uint8_t,4> cast_uint8(const rvm<int16_t,4> m0) {
	return mipp_cast_k_int16_uint8_m4(m0);
}
inline rvm<uint8_t,8> cast_uint8(const rvm<int16_t,8> m0) {
	return mipp_cast_k_int16_uint8_m8(m0);
}
inline rvm<uint8_t,1> cast_uint8(const rvm<int8_t,1> m0) {
	return mipp_cast_k_int8_uint8_m1(m0);
}
inline rvm<uint8_t,2> cast_uint8(const rvm<int8_t,2> m0) {
	return mipp_cast_k_int8_uint8_m2(m0);
}
inline rvm<uint8_t,4> cast_uint8(const rvm<int8_t,4> m0) {
	return mipp_cast_k_int8_uint8_m4(m0);
}
inline rvm<uint8_t,8> cast_uint8(const rvm<int8_t,8> m0) {
	return mipp_cast_k_int8_uint8_m8(m0);
}
inline rvm<uint8_t,1> cast_uint8(const rvm<uint64_t,1> m0) {
	return mipp_cast_k_uint64_uint8_m1(m0);
}
inline rvm<uint8_t,2> cast_uint8(const rvm<uint64_t,2> m0) {
	return mipp_cast_k_uint64_uint8_m2(m0);
}
inline rvm<uint8_t,4> cast_uint8(const rvm<uint64_t,4> m0) {
	return mipp_cast_k_uint64_uint8_m4(m0);
}
inline rvm<uint8_t,8> cast_uint8(const rvm<uint64_t,8> m0) {
	return mipp_cast_k_uint64_uint8_m8(m0);
}
inline rvm<uint8_t,1> cast_uint8(const rvm<uint32_t,1> m0) {
	return mipp_cast_k_uint32_uint8_m1(m0);
}
inline rvm<uint8_t,2> cast_uint8(const rvm<uint32_t,2> m0) {
	return mipp_cast_k_uint32_uint8_m2(m0);
}
inline rvm<uint8_t,4> cast_uint8(const rvm<uint32_t,4> m0) {
	return mipp_cast_k_uint32_uint8_m4(m0);
}
inline rvm<uint8_t,8> cast_uint8(const rvm<uint32_t,8> m0) {
	return mipp_cast_k_uint32_uint8_m8(m0);
}
inline rvm<uint8_t,1> cast_uint8(const rvm<uint16_t,1> m0) {
	return mipp_cast_k_uint16_uint8_m1(m0);
}
inline rvm<uint8_t,2> cast_uint8(const rvm<uint16_t,2> m0) {
	return mipp_cast_k_uint16_uint8_m2(m0);
}
inline rvm<uint8_t,4> cast_uint8(const rvm<uint16_t,4> m0) {
	return mipp_cast_k_uint16_uint8_m4(m0);
}
inline rvm<uint8_t,8> cast_uint8(const rvm<uint16_t,8> m0) {
	return mipp_cast_k_uint16_uint8_m8(m0);
}
inline rvm<uint8_t,1> cast_uint8(const rvm<uint8_t,1> m0) {
	return mipp_cast_k_uint8_uint8_m1(m0);
}
inline rvm<uint8_t,2> cast_uint8(const rvm<uint8_t,2> m0) {
	return mipp_cast_k_uint8_uint8_m2(m0);
}
inline rvm<uint8_t,4> cast_uint8(const rvm<uint8_t,4> m0) {
	return mipp_cast_k_uint8_uint8_m4(m0);
}
inline rvm<uint8_t,8> cast_uint8(const rvm<uint8_t,8> m0) {
	return mipp_cast_k_uint8_uint8_m8(m0);
}
inline rvd<float64_t,1> toreg(const rvm<float64_t,1> m0) {
	return mipp_toreg_float64_m1(m0);
}
inline rvd<float64_t,2> toreg(const rvm<float64_t,2> m0) {
	return mipp_toreg_float64_m2(m0);
}
inline rvd<float64_t,4> toreg(const rvm<float64_t,4> m0) {
	return mipp_toreg_float64_m4(m0);
}
inline rvd<float64_t,8> toreg(const rvm<float64_t,8> m0) {
	return mipp_toreg_float64_m8(m0);
}
inline rvd<float32_t,1> toreg(const rvm<float32_t,1> m0) {
	return mipp_toreg_float32_m1(m0);
}
inline rvd<float32_t,2> toreg(const rvm<float32_t,2> m0) {
	return mipp_toreg_float32_m2(m0);
}
inline rvd<float32_t,4> toreg(const rvm<float32_t,4> m0) {
	return mipp_toreg_float32_m4(m0);
}
inline rvd<float32_t,8> toreg(const rvm<float32_t,8> m0) {
	return mipp_toreg_float32_m8(m0);
}
inline rvd<int64_t,1> toreg(const rvm<int64_t,1> m0) {
	return mipp_toreg_int64_m1(m0);
}
inline rvd<int64_t,2> toreg(const rvm<int64_t,2> m0) {
	return mipp_toreg_int64_m2(m0);
}
inline rvd<int64_t,4> toreg(const rvm<int64_t,4> m0) {
	return mipp_toreg_int64_m4(m0);
}
inline rvd<int64_t,8> toreg(const rvm<int64_t,8> m0) {
	return mipp_toreg_int64_m8(m0);
}
inline rvd<int32_t,1> toreg(const rvm<int32_t,1> m0) {
	return mipp_toreg_int32_m1(m0);
}
inline rvd<int32_t,2> toreg(const rvm<int32_t,2> m0) {
	return mipp_toreg_int32_m2(m0);
}
inline rvd<int32_t,4> toreg(const rvm<int32_t,4> m0) {
	return mipp_toreg_int32_m4(m0);
}
inline rvd<int32_t,8> toreg(const rvm<int32_t,8> m0) {
	return mipp_toreg_int32_m8(m0);
}
inline rvd<int16_t,1> toreg(const rvm<int16_t,1> m0) {
	return mipp_toreg_int16_m1(m0);
}
inline rvd<int16_t,2> toreg(const rvm<int16_t,2> m0) {
	return mipp_toreg_int16_m2(m0);
}
inline rvd<int16_t,4> toreg(const rvm<int16_t,4> m0) {
	return mipp_toreg_int16_m4(m0);
}
inline rvd<int16_t,8> toreg(const rvm<int16_t,8> m0) {
	return mipp_toreg_int16_m8(m0);
}
inline rvd<int8_t,1> toreg(const rvm<int8_t,1> m0) {
	return mipp_toreg_int8_m1(m0);
}
inline rvd<int8_t,2> toreg(const rvm<int8_t,2> m0) {
	return mipp_toreg_int8_m2(m0);
}
inline rvd<int8_t,4> toreg(const rvm<int8_t,4> m0) {
	return mipp_toreg_int8_m4(m0);
}
inline rvd<int8_t,8> toreg(const rvm<int8_t,8> m0) {
	return mipp_toreg_int8_m8(m0);
}
inline rvd<uint64_t,1> toreg(const rvm<uint64_t,1> m0) {
	return mipp_toreg_uint64_m1(m0);
}
inline rvd<uint64_t,2> toreg(const rvm<uint64_t,2> m0) {
	return mipp_toreg_uint64_m2(m0);
}
inline rvd<uint64_t,4> toreg(const rvm<uint64_t,4> m0) {
	return mipp_toreg_uint64_m4(m0);
}
inline rvd<uint64_t,8> toreg(const rvm<uint64_t,8> m0) {
	return mipp_toreg_uint64_m8(m0);
}
inline rvd<uint32_t,1> toreg(const rvm<uint32_t,1> m0) {
	return mipp_toreg_uint32_m1(m0);
}
inline rvd<uint32_t,2> toreg(const rvm<uint32_t,2> m0) {
	return mipp_toreg_uint32_m2(m0);
}
inline rvd<uint32_t,4> toreg(const rvm<uint32_t,4> m0) {
	return mipp_toreg_uint32_m4(m0);
}
inline rvd<uint32_t,8> toreg(const rvm<uint32_t,8> m0) {
	return mipp_toreg_uint32_m8(m0);
}
inline rvd<uint16_t,1> toreg(const rvm<uint16_t,1> m0) {
	return mipp_toreg_uint16_m1(m0);
}
inline rvd<uint16_t,2> toreg(const rvm<uint16_t,2> m0) {
	return mipp_toreg_uint16_m2(m0);
}
inline rvd<uint16_t,4> toreg(const rvm<uint16_t,4> m0) {
	return mipp_toreg_uint16_m4(m0);
}
inline rvd<uint16_t,8> toreg(const rvm<uint16_t,8> m0) {
	return mipp_toreg_uint16_m8(m0);
}
inline rvd<uint8_t,1> toreg(const rvm<uint8_t,1> m0) {
	return mipp_toreg_uint8_m1(m0);
}
inline rvd<uint8_t,2> toreg(const rvm<uint8_t,2> m0) {
	return mipp_toreg_uint8_m2(m0);
}
inline rvd<uint8_t,4> toreg(const rvm<uint8_t,4> m0) {
	return mipp_toreg_uint8_m4(m0);
}
inline rvd<uint8_t,8> toreg(const rvm<uint8_t,8> m0) {
	return mipp_toreg_uint8_m8(m0);
}
inline rvm<float64_t,1> tomsk(const rvd<float64_t,1> r0) {
	return mipp_tomsk_float64_m1(r0);
}
inline rvm<float64_t,2> tomsk(const rvd<float64_t,2> r0) {
	return mipp_tomsk_float64_m2(r0);
}
inline rvm<float64_t,4> tomsk(const rvd<float64_t,4> r0) {
	return mipp_tomsk_float64_m4(r0);
}
inline rvm<float64_t,8> tomsk(const rvd<float64_t,8> r0) {
	return mipp_tomsk_float64_m8(r0);
}
inline rvm<float32_t,1> tomsk(const rvd<float32_t,1> r0) {
	return mipp_tomsk_float32_m1(r0);
}
inline rvm<float32_t,2> tomsk(const rvd<float32_t,2> r0) {
	return mipp_tomsk_float32_m2(r0);
}
inline rvm<float32_t,4> tomsk(const rvd<float32_t,4> r0) {
	return mipp_tomsk_float32_m4(r0);
}
inline rvm<float32_t,8> tomsk(const rvd<float32_t,8> r0) {
	return mipp_tomsk_float32_m8(r0);
}
inline rvm<int64_t,1> tomsk(const rvd<int64_t,1> r0) {
	return mipp_tomsk_int64_m1(r0);
}
inline rvm<int64_t,2> tomsk(const rvd<int64_t,2> r0) {
	return mipp_tomsk_int64_m2(r0);
}
inline rvm<int64_t,4> tomsk(const rvd<int64_t,4> r0) {
	return mipp_tomsk_int64_m4(r0);
}
inline rvm<int64_t,8> tomsk(const rvd<int64_t,8> r0) {
	return mipp_tomsk_int64_m8(r0);
}
inline rvm<int32_t,1> tomsk(const rvd<int32_t,1> r0) {
	return mipp_tomsk_int32_m1(r0);
}
inline rvm<int32_t,2> tomsk(const rvd<int32_t,2> r0) {
	return mipp_tomsk_int32_m2(r0);
}
inline rvm<int32_t,4> tomsk(const rvd<int32_t,4> r0) {
	return mipp_tomsk_int32_m4(r0);
}
inline rvm<int32_t,8> tomsk(const rvd<int32_t,8> r0) {
	return mipp_tomsk_int32_m8(r0);
}
inline rvm<int16_t,1> tomsk(const rvd<int16_t,1> r0) {
	return mipp_tomsk_int16_m1(r0);
}
inline rvm<int16_t,2> tomsk(const rvd<int16_t,2> r0) {
	return mipp_tomsk_int16_m2(r0);
}
inline rvm<int16_t,4> tomsk(const rvd<int16_t,4> r0) {
	return mipp_tomsk_int16_m4(r0);
}
inline rvm<int16_t,8> tomsk(const rvd<int16_t,8> r0) {
	return mipp_tomsk_int16_m8(r0);
}
inline rvm<int8_t,1> tomsk(const rvd<int8_t,1> r0) {
	return mipp_tomsk_int8_m1(r0);
}
inline rvm<int8_t,2> tomsk(const rvd<int8_t,2> r0) {
	return mipp_tomsk_int8_m2(r0);
}
inline rvm<int8_t,4> tomsk(const rvd<int8_t,4> r0) {
	return mipp_tomsk_int8_m4(r0);
}
inline rvm<int8_t,8> tomsk(const rvd<int8_t,8> r0) {
	return mipp_tomsk_int8_m8(r0);
}
inline rvm<uint64_t,1> tomsk(const rvd<uint64_t,1> r0) {
	return mipp_tomsk_uint64_m1(r0);
}
inline rvm<uint64_t,2> tomsk(const rvd<uint64_t,2> r0) {
	return mipp_tomsk_uint64_m2(r0);
}
inline rvm<uint64_t,4> tomsk(const rvd<uint64_t,4> r0) {
	return mipp_tomsk_uint64_m4(r0);
}
inline rvm<uint64_t,8> tomsk(const rvd<uint64_t,8> r0) {
	return mipp_tomsk_uint64_m8(r0);
}
inline rvm<uint32_t,1> tomsk(const rvd<uint32_t,1> r0) {
	return mipp_tomsk_uint32_m1(r0);
}
inline rvm<uint32_t,2> tomsk(const rvd<uint32_t,2> r0) {
	return mipp_tomsk_uint32_m2(r0);
}
inline rvm<uint32_t,4> tomsk(const rvd<uint32_t,4> r0) {
	return mipp_tomsk_uint32_m4(r0);
}
inline rvm<uint32_t,8> tomsk(const rvd<uint32_t,8> r0) {
	return mipp_tomsk_uint32_m8(r0);
}
inline rvm<uint16_t,1> tomsk(const rvd<uint16_t,1> r0) {
	return mipp_tomsk_uint16_m1(r0);
}
inline rvm<uint16_t,2> tomsk(const rvd<uint16_t,2> r0) {
	return mipp_tomsk_uint16_m2(r0);
}
inline rvm<uint16_t,4> tomsk(const rvd<uint16_t,4> r0) {
	return mipp_tomsk_uint16_m4(r0);
}
inline rvm<uint16_t,8> tomsk(const rvd<uint16_t,8> r0) {
	return mipp_tomsk_uint16_m8(r0);
}
inline rvm<uint8_t,1> tomsk(const rvd<uint8_t,1> r0) {
	return mipp_tomsk_uint8_m1(r0);
}
inline rvm<uint8_t,2> tomsk(const rvd<uint8_t,2> r0) {
	return mipp_tomsk_uint8_m2(r0);
}
inline rvm<uint8_t,4> tomsk(const rvd<uint8_t,4> r0) {
	return mipp_tomsk_uint8_m4(r0);
}
inline rvm<uint8_t,8> tomsk(const rvd<uint8_t,8> r0) {
	return mipp_tomsk_uint8_m8(r0);
}
template <typename T, int LMULT=1> inline rvd<T, LMULT> load(const T* p0) { std::cerr << "load" << std::endl; exit(-1);}

template <>
inline rvd<float64_t, 1> load<float64_t, 1>(const float64_t* p0) {
	return mipp_load_float64_m1(p0);
}
template <>
inline rvd<float64_t, 2> load<float64_t, 2>(const float64_t* p0) {
	return mipp_load_float64_m2(p0);
}
template <>
inline rvd<float64_t, 4> load<float64_t, 4>(const float64_t* p0) {
	return mipp_load_float64_m4(p0);
}
template <>
inline rvd<float64_t, 8> load<float64_t, 8>(const float64_t* p0) {
	return mipp_load_float64_m8(p0);
}
template <>
inline rvd<float32_t, 1> load<float32_t, 1>(const float32_t* p0) {
	return mipp_load_float32_m1(p0);
}
template <>
inline rvd<float32_t, 2> load<float32_t, 2>(const float32_t* p0) {
	return mipp_load_float32_m2(p0);
}
template <>
inline rvd<float32_t, 4> load<float32_t, 4>(const float32_t* p0) {
	return mipp_load_float32_m4(p0);
}
template <>
inline rvd<float32_t, 8> load<float32_t, 8>(const float32_t* p0) {
	return mipp_load_float32_m8(p0);
}
template <>
inline rvd<int64_t, 1> load<int64_t, 1>(const int64_t* p0) {
	return mipp_load_int64_m1(p0);
}
template <>
inline rvd<int64_t, 2> load<int64_t, 2>(const int64_t* p0) {
	return mipp_load_int64_m2(p0);
}
template <>
inline rvd<int64_t, 4> load<int64_t, 4>(const int64_t* p0) {
	return mipp_load_int64_m4(p0);
}
template <>
inline rvd<int64_t, 8> load<int64_t, 8>(const int64_t* p0) {
	return mipp_load_int64_m8(p0);
}
template <>
inline rvd<int32_t, 1> load<int32_t, 1>(const int32_t* p0) {
	return mipp_load_int32_m1(p0);
}
template <>
inline rvd<int32_t, 2> load<int32_t, 2>(const int32_t* p0) {
	return mipp_load_int32_m2(p0);
}
template <>
inline rvd<int32_t, 4> load<int32_t, 4>(const int32_t* p0) {
	return mipp_load_int32_m4(p0);
}
template <>
inline rvd<int32_t, 8> load<int32_t, 8>(const int32_t* p0) {
	return mipp_load_int32_m8(p0);
}
template <>
inline rvd<int16_t, 1> load<int16_t, 1>(const int16_t* p0) {
	return mipp_load_int16_m1(p0);
}
template <>
inline rvd<int16_t, 2> load<int16_t, 2>(const int16_t* p0) {
	return mipp_load_int16_m2(p0);
}
template <>
inline rvd<int16_t, 4> load<int16_t, 4>(const int16_t* p0) {
	return mipp_load_int16_m4(p0);
}
template <>
inline rvd<int16_t, 8> load<int16_t, 8>(const int16_t* p0) {
	return mipp_load_int16_m8(p0);
}
template <>
inline rvd<int8_t, 1> load<int8_t, 1>(const int8_t* p0) {
	return mipp_load_int8_m1(p0);
}
template <>
inline rvd<int8_t, 2> load<int8_t, 2>(const int8_t* p0) {
	return mipp_load_int8_m2(p0);
}
template <>
inline rvd<int8_t, 4> load<int8_t, 4>(const int8_t* p0) {
	return mipp_load_int8_m4(p0);
}
template <>
inline rvd<int8_t, 8> load<int8_t, 8>(const int8_t* p0) {
	return mipp_load_int8_m8(p0);
}
template <>
inline rvd<uint64_t, 1> load<uint64_t, 1>(const uint64_t* p0) {
	return mipp_load_uint64_m1(p0);
}
template <>
inline rvd<uint64_t, 2> load<uint64_t, 2>(const uint64_t* p0) {
	return mipp_load_uint64_m2(p0);
}
template <>
inline rvd<uint64_t, 4> load<uint64_t, 4>(const uint64_t* p0) {
	return mipp_load_uint64_m4(p0);
}
template <>
inline rvd<uint64_t, 8> load<uint64_t, 8>(const uint64_t* p0) {
	return mipp_load_uint64_m8(p0);
}
template <>
inline rvd<uint32_t, 1> load<uint32_t, 1>(const uint32_t* p0) {
	return mipp_load_uint32_m1(p0);
}
template <>
inline rvd<uint32_t, 2> load<uint32_t, 2>(const uint32_t* p0) {
	return mipp_load_uint32_m2(p0);
}
template <>
inline rvd<uint32_t, 4> load<uint32_t, 4>(const uint32_t* p0) {
	return mipp_load_uint32_m4(p0);
}
template <>
inline rvd<uint32_t, 8> load<uint32_t, 8>(const uint32_t* p0) {
	return mipp_load_uint32_m8(p0);
}
template <>
inline rvd<uint16_t, 1> load<uint16_t, 1>(const uint16_t* p0) {
	return mipp_load_uint16_m1(p0);
}
template <>
inline rvd<uint16_t, 2> load<uint16_t, 2>(const uint16_t* p0) {
	return mipp_load_uint16_m2(p0);
}
template <>
inline rvd<uint16_t, 4> load<uint16_t, 4>(const uint16_t* p0) {
	return mipp_load_uint16_m4(p0);
}
template <>
inline rvd<uint16_t, 8> load<uint16_t, 8>(const uint16_t* p0) {
	return mipp_load_uint16_m8(p0);
}
template <>
inline rvd<uint8_t, 1> load<uint8_t, 1>(const uint8_t* p0) {
	return mipp_load_uint8_m1(p0);
}
template <>
inline rvd<uint8_t, 2> load<uint8_t, 2>(const uint8_t* p0) {
	return mipp_load_uint8_m2(p0);
}
template <>
inline rvd<uint8_t, 4> load<uint8_t, 4>(const uint8_t* p0) {
	return mipp_load_uint8_m4(p0);
}
template <>
inline rvd<uint8_t, 8> load<uint8_t, 8>(const uint8_t* p0) {
	return mipp_load_uint8_m8(p0);
}
template <typename T, int LMULT=1> inline rvd<T, LMULT> loadu(const T* p0) { std::cerr << "loadu" << std::endl; exit(-1);}

template <>
inline rvd<float64_t, 1> loadu<float64_t, 1>(const float64_t* p0) {
	return mipp_loadu_float64_m1(p0);
}
template <>
inline rvd<float64_t, 2> loadu<float64_t, 2>(const float64_t* p0) {
	return mipp_loadu_float64_m2(p0);
}
template <>
inline rvd<float64_t, 4> loadu<float64_t, 4>(const float64_t* p0) {
	return mipp_loadu_float64_m4(p0);
}
template <>
inline rvd<float64_t, 8> loadu<float64_t, 8>(const float64_t* p0) {
	return mipp_loadu_float64_m8(p0);
}
template <>
inline rvd<float32_t, 1> loadu<float32_t, 1>(const float32_t* p0) {
	return mipp_loadu_float32_m1(p0);
}
template <>
inline rvd<float32_t, 2> loadu<float32_t, 2>(const float32_t* p0) {
	return mipp_loadu_float32_m2(p0);
}
template <>
inline rvd<float32_t, 4> loadu<float32_t, 4>(const float32_t* p0) {
	return mipp_loadu_float32_m4(p0);
}
template <>
inline rvd<float32_t, 8> loadu<float32_t, 8>(const float32_t* p0) {
	return mipp_loadu_float32_m8(p0);
}
template <>
inline rvd<int64_t, 1> loadu<int64_t, 1>(const int64_t* p0) {
	return mipp_loadu_int64_m1(p0);
}
template <>
inline rvd<int64_t, 2> loadu<int64_t, 2>(const int64_t* p0) {
	return mipp_loadu_int64_m2(p0);
}
template <>
inline rvd<int64_t, 4> loadu<int64_t, 4>(const int64_t* p0) {
	return mipp_loadu_int64_m4(p0);
}
template <>
inline rvd<int64_t, 8> loadu<int64_t, 8>(const int64_t* p0) {
	return mipp_loadu_int64_m8(p0);
}
template <>
inline rvd<int32_t, 1> loadu<int32_t, 1>(const int32_t* p0) {
	return mipp_loadu_int32_m1(p0);
}
template <>
inline rvd<int32_t, 2> loadu<int32_t, 2>(const int32_t* p0) {
	return mipp_loadu_int32_m2(p0);
}
template <>
inline rvd<int32_t, 4> loadu<int32_t, 4>(const int32_t* p0) {
	return mipp_loadu_int32_m4(p0);
}
template <>
inline rvd<int32_t, 8> loadu<int32_t, 8>(const int32_t* p0) {
	return mipp_loadu_int32_m8(p0);
}
template <>
inline rvd<int16_t, 1> loadu<int16_t, 1>(const int16_t* p0) {
	return mipp_loadu_int16_m1(p0);
}
template <>
inline rvd<int16_t, 2> loadu<int16_t, 2>(const int16_t* p0) {
	return mipp_loadu_int16_m2(p0);
}
template <>
inline rvd<int16_t, 4> loadu<int16_t, 4>(const int16_t* p0) {
	return mipp_loadu_int16_m4(p0);
}
template <>
inline rvd<int16_t, 8> loadu<int16_t, 8>(const int16_t* p0) {
	return mipp_loadu_int16_m8(p0);
}
template <>
inline rvd<int8_t, 1> loadu<int8_t, 1>(const int8_t* p0) {
	return mipp_loadu_int8_m1(p0);
}
template <>
inline rvd<int8_t, 2> loadu<int8_t, 2>(const int8_t* p0) {
	return mipp_loadu_int8_m2(p0);
}
template <>
inline rvd<int8_t, 4> loadu<int8_t, 4>(const int8_t* p0) {
	return mipp_loadu_int8_m4(p0);
}
template <>
inline rvd<int8_t, 8> loadu<int8_t, 8>(const int8_t* p0) {
	return mipp_loadu_int8_m8(p0);
}
template <>
inline rvd<uint64_t, 1> loadu<uint64_t, 1>(const uint64_t* p0) {
	return mipp_loadu_uint64_m1(p0);
}
template <>
inline rvd<uint64_t, 2> loadu<uint64_t, 2>(const uint64_t* p0) {
	return mipp_loadu_uint64_m2(p0);
}
template <>
inline rvd<uint64_t, 4> loadu<uint64_t, 4>(const uint64_t* p0) {
	return mipp_loadu_uint64_m4(p0);
}
template <>
inline rvd<uint64_t, 8> loadu<uint64_t, 8>(const uint64_t* p0) {
	return mipp_loadu_uint64_m8(p0);
}
template <>
inline rvd<uint32_t, 1> loadu<uint32_t, 1>(const uint32_t* p0) {
	return mipp_loadu_uint32_m1(p0);
}
template <>
inline rvd<uint32_t, 2> loadu<uint32_t, 2>(const uint32_t* p0) {
	return mipp_loadu_uint32_m2(p0);
}
template <>
inline rvd<uint32_t, 4> loadu<uint32_t, 4>(const uint32_t* p0) {
	return mipp_loadu_uint32_m4(p0);
}
template <>
inline rvd<uint32_t, 8> loadu<uint32_t, 8>(const uint32_t* p0) {
	return mipp_loadu_uint32_m8(p0);
}
template <>
inline rvd<uint16_t, 1> loadu<uint16_t, 1>(const uint16_t* p0) {
	return mipp_loadu_uint16_m1(p0);
}
template <>
inline rvd<uint16_t, 2> loadu<uint16_t, 2>(const uint16_t* p0) {
	return mipp_loadu_uint16_m2(p0);
}
template <>
inline rvd<uint16_t, 4> loadu<uint16_t, 4>(const uint16_t* p0) {
	return mipp_loadu_uint16_m4(p0);
}
template <>
inline rvd<uint16_t, 8> loadu<uint16_t, 8>(const uint16_t* p0) {
	return mipp_loadu_uint16_m8(p0);
}
template <>
inline rvd<uint8_t, 1> loadu<uint8_t, 1>(const uint8_t* p0) {
	return mipp_loadu_uint8_m1(p0);
}
template <>
inline rvd<uint8_t, 2> loadu<uint8_t, 2>(const uint8_t* p0) {
	return mipp_loadu_uint8_m2(p0);
}
template <>
inline rvd<uint8_t, 4> loadu<uint8_t, 4>(const uint8_t* p0) {
	return mipp_loadu_uint8_m4(p0);
}
template <>
inline rvd<uint8_t, 8> loadu<uint8_t, 8>(const uint8_t* p0) {
	return mipp_loadu_uint8_m8(p0);
}
inline void store(float64_t* p0, const rvd<float64_t,1> r0) {
	mipp_store_float64_m1(p0, r0);
}
inline void store(float64_t* p0, const rvd<float64_t,2> r0) {
	mipp_store_float64_m2(p0, r0);
}
inline void store(float64_t* p0, const rvd<float64_t,4> r0) {
	mipp_store_float64_m4(p0, r0);
}
inline void store(float64_t* p0, const rvd<float64_t,8> r0) {
	mipp_store_float64_m8(p0, r0);
}
inline void store(float32_t* p0, const rvd<float32_t,1> r0) {
	mipp_store_float32_m1(p0, r0);
}
inline void store(float32_t* p0, const rvd<float32_t,2> r0) {
	mipp_store_float32_m2(p0, r0);
}
inline void store(float32_t* p0, const rvd<float32_t,4> r0) {
	mipp_store_float32_m4(p0, r0);
}
inline void store(float32_t* p0, const rvd<float32_t,8> r0) {
	mipp_store_float32_m8(p0, r0);
}
inline void store(int64_t* p0, const rvd<int64_t,1> r0) {
	mipp_store_int64_m1(p0, r0);
}
inline void store(int64_t* p0, const rvd<int64_t,2> r0) {
	mipp_store_int64_m2(p0, r0);
}
inline void store(int64_t* p0, const rvd<int64_t,4> r0) {
	mipp_store_int64_m4(p0, r0);
}
inline void store(int64_t* p0, const rvd<int64_t,8> r0) {
	mipp_store_int64_m8(p0, r0);
}
inline void store(int32_t* p0, const rvd<int32_t,1> r0) {
	mipp_store_int32_m1(p0, r0);
}
inline void store(int32_t* p0, const rvd<int32_t,2> r0) {
	mipp_store_int32_m2(p0, r0);
}
inline void store(int32_t* p0, const rvd<int32_t,4> r0) {
	mipp_store_int32_m4(p0, r0);
}
inline void store(int32_t* p0, const rvd<int32_t,8> r0) {
	mipp_store_int32_m8(p0, r0);
}
inline void store(int16_t* p0, const rvd<int16_t,1> r0) {
	mipp_store_int16_m1(p0, r0);
}
inline void store(int16_t* p0, const rvd<int16_t,2> r0) {
	mipp_store_int16_m2(p0, r0);
}
inline void store(int16_t* p0, const rvd<int16_t,4> r0) {
	mipp_store_int16_m4(p0, r0);
}
inline void store(int16_t* p0, const rvd<int16_t,8> r0) {
	mipp_store_int16_m8(p0, r0);
}
inline void store(int8_t* p0, const rvd<int8_t,1> r0) {
	mipp_store_int8_m1(p0, r0);
}
inline void store(int8_t* p0, const rvd<int8_t,2> r0) {
	mipp_store_int8_m2(p0, r0);
}
inline void store(int8_t* p0, const rvd<int8_t,4> r0) {
	mipp_store_int8_m4(p0, r0);
}
inline void store(int8_t* p0, const rvd<int8_t,8> r0) {
	mipp_store_int8_m8(p0, r0);
}
inline void store(uint64_t* p0, const rvd<uint64_t,1> r0) {
	mipp_store_uint64_m1(p0, r0);
}
inline void store(uint64_t* p0, const rvd<uint64_t,2> r0) {
	mipp_store_uint64_m2(p0, r0);
}
inline void store(uint64_t* p0, const rvd<uint64_t,4> r0) {
	mipp_store_uint64_m4(p0, r0);
}
inline void store(uint64_t* p0, const rvd<uint64_t,8> r0) {
	mipp_store_uint64_m8(p0, r0);
}
inline void store(uint32_t* p0, const rvd<uint32_t,1> r0) {
	mipp_store_uint32_m1(p0, r0);
}
inline void store(uint32_t* p0, const rvd<uint32_t,2> r0) {
	mipp_store_uint32_m2(p0, r0);
}
inline void store(uint32_t* p0, const rvd<uint32_t,4> r0) {
	mipp_store_uint32_m4(p0, r0);
}
inline void store(uint32_t* p0, const rvd<uint32_t,8> r0) {
	mipp_store_uint32_m8(p0, r0);
}
inline void store(uint16_t* p0, const rvd<uint16_t,1> r0) {
	mipp_store_uint16_m1(p0, r0);
}
inline void store(uint16_t* p0, const rvd<uint16_t,2> r0) {
	mipp_store_uint16_m2(p0, r0);
}
inline void store(uint16_t* p0, const rvd<uint16_t,4> r0) {
	mipp_store_uint16_m4(p0, r0);
}
inline void store(uint16_t* p0, const rvd<uint16_t,8> r0) {
	mipp_store_uint16_m8(p0, r0);
}
inline void store(uint8_t* p0, const rvd<uint8_t,1> r0) {
	mipp_store_uint8_m1(p0, r0);
}
inline void store(uint8_t* p0, const rvd<uint8_t,2> r0) {
	mipp_store_uint8_m2(p0, r0);
}
inline void store(uint8_t* p0, const rvd<uint8_t,4> r0) {
	mipp_store_uint8_m4(p0, r0);
}
inline void store(uint8_t* p0, const rvd<uint8_t,8> r0) {
	mipp_store_uint8_m8(p0, r0);
}
inline void storeu(float64_t* p0, const rvd<float64_t,1> r0) {
	mipp_storeu_float64_m1(p0, r0);
}
inline void storeu(float64_t* p0, const rvd<float64_t,2> r0) {
	mipp_storeu_float64_m2(p0, r0);
}
inline void storeu(float64_t* p0, const rvd<float64_t,4> r0) {
	mipp_storeu_float64_m4(p0, r0);
}
inline void storeu(float64_t* p0, const rvd<float64_t,8> r0) {
	mipp_storeu_float64_m8(p0, r0);
}
inline void storeu(float32_t* p0, const rvd<float32_t,1> r0) {
	mipp_storeu_float32_m1(p0, r0);
}
inline void storeu(float32_t* p0, const rvd<float32_t,2> r0) {
	mipp_storeu_float32_m2(p0, r0);
}
inline void storeu(float32_t* p0, const rvd<float32_t,4> r0) {
	mipp_storeu_float32_m4(p0, r0);
}
inline void storeu(float32_t* p0, const rvd<float32_t,8> r0) {
	mipp_storeu_float32_m8(p0, r0);
}
inline void storeu(int64_t* p0, const rvd<int64_t,1> r0) {
	mipp_storeu_int64_m1(p0, r0);
}
inline void storeu(int64_t* p0, const rvd<int64_t,2> r0) {
	mipp_storeu_int64_m2(p0, r0);
}
inline void storeu(int64_t* p0, const rvd<int64_t,4> r0) {
	mipp_storeu_int64_m4(p0, r0);
}
inline void storeu(int64_t* p0, const rvd<int64_t,8> r0) {
	mipp_storeu_int64_m8(p0, r0);
}
inline void storeu(int32_t* p0, const rvd<int32_t,1> r0) {
	mipp_storeu_int32_m1(p0, r0);
}
inline void storeu(int32_t* p0, const rvd<int32_t,2> r0) {
	mipp_storeu_int32_m2(p0, r0);
}
inline void storeu(int32_t* p0, const rvd<int32_t,4> r0) {
	mipp_storeu_int32_m4(p0, r0);
}
inline void storeu(int32_t* p0, const rvd<int32_t,8> r0) {
	mipp_storeu_int32_m8(p0, r0);
}
inline void storeu(int16_t* p0, const rvd<int16_t,1> r0) {
	mipp_storeu_int16_m1(p0, r0);
}
inline void storeu(int16_t* p0, const rvd<int16_t,2> r0) {
	mipp_storeu_int16_m2(p0, r0);
}
inline void storeu(int16_t* p0, const rvd<int16_t,4> r0) {
	mipp_storeu_int16_m4(p0, r0);
}
inline void storeu(int16_t* p0, const rvd<int16_t,8> r0) {
	mipp_storeu_int16_m8(p0, r0);
}
inline void storeu(int8_t* p0, const rvd<int8_t,1> r0) {
	mipp_storeu_int8_m1(p0, r0);
}
inline void storeu(int8_t* p0, const rvd<int8_t,2> r0) {
	mipp_storeu_int8_m2(p0, r0);
}
inline void storeu(int8_t* p0, const rvd<int8_t,4> r0) {
	mipp_storeu_int8_m4(p0, r0);
}
inline void storeu(int8_t* p0, const rvd<int8_t,8> r0) {
	mipp_storeu_int8_m8(p0, r0);
}
inline void storeu(uint64_t* p0, const rvd<uint64_t,1> r0) {
	mipp_storeu_uint64_m1(p0, r0);
}
inline void storeu(uint64_t* p0, const rvd<uint64_t,2> r0) {
	mipp_storeu_uint64_m2(p0, r0);
}
inline void storeu(uint64_t* p0, const rvd<uint64_t,4> r0) {
	mipp_storeu_uint64_m4(p0, r0);
}
inline void storeu(uint64_t* p0, const rvd<uint64_t,8> r0) {
	mipp_storeu_uint64_m8(p0, r0);
}
inline void storeu(uint32_t* p0, const rvd<uint32_t,1> r0) {
	mipp_storeu_uint32_m1(p0, r0);
}
inline void storeu(uint32_t* p0, const rvd<uint32_t,2> r0) {
	mipp_storeu_uint32_m2(p0, r0);
}
inline void storeu(uint32_t* p0, const rvd<uint32_t,4> r0) {
	mipp_storeu_uint32_m4(p0, r0);
}
inline void storeu(uint32_t* p0, const rvd<uint32_t,8> r0) {
	mipp_storeu_uint32_m8(p0, r0);
}
inline void storeu(uint16_t* p0, const rvd<uint16_t,1> r0) {
	mipp_storeu_uint16_m1(p0, r0);
}
inline void storeu(uint16_t* p0, const rvd<uint16_t,2> r0) {
	mipp_storeu_uint16_m2(p0, r0);
}
inline void storeu(uint16_t* p0, const rvd<uint16_t,4> r0) {
	mipp_storeu_uint16_m4(p0, r0);
}
inline void storeu(uint16_t* p0, const rvd<uint16_t,8> r0) {
	mipp_storeu_uint16_m8(p0, r0);
}
inline void storeu(uint8_t* p0, const rvd<uint8_t,1> r0) {
	mipp_storeu_uint8_m1(p0, r0);
}
inline void storeu(uint8_t* p0, const rvd<uint8_t,2> r0) {
	mipp_storeu_uint8_m2(p0, r0);
}
inline void storeu(uint8_t* p0, const rvd<uint8_t,4> r0) {
	mipp_storeu_uint8_m4(p0, r0);
}
inline void storeu(uint8_t* p0, const rvd<uint8_t,8> r0) {
	mipp_storeu_uint8_m8(p0, r0);
}
template <typename T, int LMULT=1> inline rvd<T, LMULT> set(const T[N<T>()]) { std::cerr << "set" << std::endl; exit(-1);}

template <>
inline rvd<float64_t, 1> set<float64_t, 1>(const float64_t vals[MIPP_N_FLOAT64]) {
	return mipp_set_float64_m1(vals);
}
template <>
inline rvd<float64_t, 2> set<float64_t, 2>(const float64_t vals[MIPP_N_FLOAT64]) {
	return mipp_set_float64_m2(vals);
}
template <>
inline rvd<float64_t, 4> set<float64_t, 4>(const float64_t vals[MIPP_N_FLOAT64]) {
	return mipp_set_float64_m4(vals);
}
template <>
inline rvd<float64_t, 8> set<float64_t, 8>(const float64_t vals[MIPP_N_FLOAT64]) {
	return mipp_set_float64_m8(vals);
}
template <>
inline rvd<float32_t, 1> set<float32_t, 1>(const float32_t vals[MIPP_N_FLOAT32]) {
	return mipp_set_float32_m1(vals);
}
template <>
inline rvd<float32_t, 2> set<float32_t, 2>(const float32_t vals[MIPP_N_FLOAT32]) {
	return mipp_set_float32_m2(vals);
}
template <>
inline rvd<float32_t, 4> set<float32_t, 4>(const float32_t vals[MIPP_N_FLOAT32]) {
	return mipp_set_float32_m4(vals);
}
template <>
inline rvd<float32_t, 8> set<float32_t, 8>(const float32_t vals[MIPP_N_FLOAT32]) {
	return mipp_set_float32_m8(vals);
}
template <>
inline rvd<int64_t, 1> set<int64_t, 1>(const int64_t vals[MIPP_N_INT64]) {
	return mipp_set_int64_m1(vals);
}
template <>
inline rvd<int64_t, 2> set<int64_t, 2>(const int64_t vals[MIPP_N_INT64]) {
	return mipp_set_int64_m2(vals);
}
template <>
inline rvd<int64_t, 4> set<int64_t, 4>(const int64_t vals[MIPP_N_INT64]) {
	return mipp_set_int64_m4(vals);
}
template <>
inline rvd<int64_t, 8> set<int64_t, 8>(const int64_t vals[MIPP_N_INT64]) {
	return mipp_set_int64_m8(vals);
}
template <>
inline rvd<int32_t, 1> set<int32_t, 1>(const int32_t vals[MIPP_N_INT32]) {
	return mipp_set_int32_m1(vals);
}
template <>
inline rvd<int32_t, 2> set<int32_t, 2>(const int32_t vals[MIPP_N_INT32]) {
	return mipp_set_int32_m2(vals);
}
template <>
inline rvd<int32_t, 4> set<int32_t, 4>(const int32_t vals[MIPP_N_INT32]) {
	return mipp_set_int32_m4(vals);
}
template <>
inline rvd<int32_t, 8> set<int32_t, 8>(const int32_t vals[MIPP_N_INT32]) {
	return mipp_set_int32_m8(vals);
}
template <>
inline rvd<int16_t, 1> set<int16_t, 1>(const int16_t vals[MIPP_N_INT16]) {
	return mipp_set_int16_m1(vals);
}
template <>
inline rvd<int16_t, 2> set<int16_t, 2>(const int16_t vals[MIPP_N_INT16]) {
	return mipp_set_int16_m2(vals);
}
template <>
inline rvd<int16_t, 4> set<int16_t, 4>(const int16_t vals[MIPP_N_INT16]) {
	return mipp_set_int16_m4(vals);
}
template <>
inline rvd<int16_t, 8> set<int16_t, 8>(const int16_t vals[MIPP_N_INT16]) {
	return mipp_set_int16_m8(vals);
}
template <>
inline rvd<int8_t, 1> set<int8_t, 1>(const int8_t vals[MIPP_N_INT8]) {
	return mipp_set_int8_m1(vals);
}
template <>
inline rvd<int8_t, 2> set<int8_t, 2>(const int8_t vals[MIPP_N_INT8]) {
	return mipp_set_int8_m2(vals);
}
template <>
inline rvd<int8_t, 4> set<int8_t, 4>(const int8_t vals[MIPP_N_INT8]) {
	return mipp_set_int8_m4(vals);
}
template <>
inline rvd<int8_t, 8> set<int8_t, 8>(const int8_t vals[MIPP_N_INT8]) {
	return mipp_set_int8_m8(vals);
}
template <>
inline rvd<uint64_t, 1> set<uint64_t, 1>(const uint64_t vals[MIPP_N_UINT64]) {
	return mipp_set_uint64_m1(vals);
}
template <>
inline rvd<uint64_t, 2> set<uint64_t, 2>(const uint64_t vals[MIPP_N_UINT64]) {
	return mipp_set_uint64_m2(vals);
}
template <>
inline rvd<uint64_t, 4> set<uint64_t, 4>(const uint64_t vals[MIPP_N_UINT64]) {
	return mipp_set_uint64_m4(vals);
}
template <>
inline rvd<uint64_t, 8> set<uint64_t, 8>(const uint64_t vals[MIPP_N_UINT64]) {
	return mipp_set_uint64_m8(vals);
}
template <>
inline rvd<uint32_t, 1> set<uint32_t, 1>(const uint32_t vals[MIPP_N_UINT32]) {
	return mipp_set_uint32_m1(vals);
}
template <>
inline rvd<uint32_t, 2> set<uint32_t, 2>(const uint32_t vals[MIPP_N_UINT32]) {
	return mipp_set_uint32_m2(vals);
}
template <>
inline rvd<uint32_t, 4> set<uint32_t, 4>(const uint32_t vals[MIPP_N_UINT32]) {
	return mipp_set_uint32_m4(vals);
}
template <>
inline rvd<uint32_t, 8> set<uint32_t, 8>(const uint32_t vals[MIPP_N_UINT32]) {
	return mipp_set_uint32_m8(vals);
}
template <>
inline rvd<uint16_t, 1> set<uint16_t, 1>(const uint16_t vals[MIPP_N_UINT16]) {
	return mipp_set_uint16_m1(vals);
}
template <>
inline rvd<uint16_t, 2> set<uint16_t, 2>(const uint16_t vals[MIPP_N_UINT16]) {
	return mipp_set_uint16_m2(vals);
}
template <>
inline rvd<uint16_t, 4> set<uint16_t, 4>(const uint16_t vals[MIPP_N_UINT16]) {
	return mipp_set_uint16_m4(vals);
}
template <>
inline rvd<uint16_t, 8> set<uint16_t, 8>(const uint16_t vals[MIPP_N_UINT16]) {
	return mipp_set_uint16_m8(vals);
}
template <>
inline rvd<uint8_t, 1> set<uint8_t, 1>(const uint8_t vals[MIPP_N_UINT8]) {
	return mipp_set_uint8_m1(vals);
}
template <>
inline rvd<uint8_t, 2> set<uint8_t, 2>(const uint8_t vals[MIPP_N_UINT8]) {
	return mipp_set_uint8_m2(vals);
}
template <>
inline rvd<uint8_t, 4> set<uint8_t, 4>(const uint8_t vals[MIPP_N_UINT8]) {
	return mipp_set_uint8_m4(vals);
}
template <>
inline rvd<uint8_t, 8> set<uint8_t, 8>(const uint8_t vals[MIPP_N_UINT8]) {
	return mipp_set_uint8_m8(vals);
}
template <typename T, int LMULT=1> inline rvm<T, LMULT> set_k(const int32_t[N<T>()]) { std::cerr << "set_k" << std::endl; exit(-1);}

template <>
inline rvm<float64_t, 1> set_k<float64_t, 1>(const int32_t vals[MIPP_N_FLOAT64]) {
	return mipp_set_k_float64_m1(vals);
}
template <>
inline rvm<float64_t, 2> set_k<float64_t, 2>(const int32_t vals[MIPP_N_FLOAT64]) {
	return mipp_set_k_float64_m2(vals);
}
template <>
inline rvm<float64_t, 4> set_k<float64_t, 4>(const int32_t vals[MIPP_N_FLOAT64]) {
	return mipp_set_k_float64_m4(vals);
}
template <>
inline rvm<float64_t, 8> set_k<float64_t, 8>(const int32_t vals[MIPP_N_FLOAT64]) {
	return mipp_set_k_float64_m8(vals);
}
template <>
inline rvm<float32_t, 1> set_k<float32_t, 1>(const int32_t vals[MIPP_N_FLOAT32]) {
	return mipp_set_k_float32_m1(vals);
}
template <>
inline rvm<float32_t, 2> set_k<float32_t, 2>(const int32_t vals[MIPP_N_FLOAT32]) {
	return mipp_set_k_float32_m2(vals);
}
template <>
inline rvm<float32_t, 4> set_k<float32_t, 4>(const int32_t vals[MIPP_N_FLOAT32]) {
	return mipp_set_k_float32_m4(vals);
}
template <>
inline rvm<float32_t, 8> set_k<float32_t, 8>(const int32_t vals[MIPP_N_FLOAT32]) {
	return mipp_set_k_float32_m8(vals);
}
template <>
inline rvm<int64_t, 1> set_k<int64_t, 1>(const int32_t vals[MIPP_N_INT64]) {
	return mipp_set_k_int64_m1(vals);
}
template <>
inline rvm<int64_t, 2> set_k<int64_t, 2>(const int32_t vals[MIPP_N_INT64]) {
	return mipp_set_k_int64_m2(vals);
}
template <>
inline rvm<int64_t, 4> set_k<int64_t, 4>(const int32_t vals[MIPP_N_INT64]) {
	return mipp_set_k_int64_m4(vals);
}
template <>
inline rvm<int64_t, 8> set_k<int64_t, 8>(const int32_t vals[MIPP_N_INT64]) {
	return mipp_set_k_int64_m8(vals);
}
template <>
inline rvm<int32_t, 1> set_k<int32_t, 1>(const int32_t vals[MIPP_N_INT32]) {
	return mipp_set_k_int32_m1(vals);
}
template <>
inline rvm<int32_t, 2> set_k<int32_t, 2>(const int32_t vals[MIPP_N_INT32]) {
	return mipp_set_k_int32_m2(vals);
}
template <>
inline rvm<int32_t, 4> set_k<int32_t, 4>(const int32_t vals[MIPP_N_INT32]) {
	return mipp_set_k_int32_m4(vals);
}
template <>
inline rvm<int32_t, 8> set_k<int32_t, 8>(const int32_t vals[MIPP_N_INT32]) {
	return mipp_set_k_int32_m8(vals);
}
template <>
inline rvm<int16_t, 1> set_k<int16_t, 1>(const int32_t vals[MIPP_N_INT16]) {
	return mipp_set_k_int16_m1(vals);
}
template <>
inline rvm<int16_t, 2> set_k<int16_t, 2>(const int32_t vals[MIPP_N_INT16]) {
	return mipp_set_k_int16_m2(vals);
}
template <>
inline rvm<int16_t, 4> set_k<int16_t, 4>(const int32_t vals[MIPP_N_INT16]) {
	return mipp_set_k_int16_m4(vals);
}
template <>
inline rvm<int16_t, 8> set_k<int16_t, 8>(const int32_t vals[MIPP_N_INT16]) {
	return mipp_set_k_int16_m8(vals);
}
template <>
inline rvm<int8_t, 1> set_k<int8_t, 1>(const int32_t vals[MIPP_N_INT8]) {
	return mipp_set_k_int8_m1(vals);
}
template <>
inline rvm<int8_t, 2> set_k<int8_t, 2>(const int32_t vals[MIPP_N_INT8]) {
	return mipp_set_k_int8_m2(vals);
}
template <>
inline rvm<int8_t, 4> set_k<int8_t, 4>(const int32_t vals[MIPP_N_INT8]) {
	return mipp_set_k_int8_m4(vals);
}
template <>
inline rvm<int8_t, 8> set_k<int8_t, 8>(const int32_t vals[MIPP_N_INT8]) {
	return mipp_set_k_int8_m8(vals);
}
template <>
inline rvm<uint64_t, 1> set_k<uint64_t, 1>(const int32_t vals[MIPP_N_UINT64]) {
	return mipp_set_k_uint64_m1(vals);
}
template <>
inline rvm<uint64_t, 2> set_k<uint64_t, 2>(const int32_t vals[MIPP_N_UINT64]) {
	return mipp_set_k_uint64_m2(vals);
}
template <>
inline rvm<uint64_t, 4> set_k<uint64_t, 4>(const int32_t vals[MIPP_N_UINT64]) {
	return mipp_set_k_uint64_m4(vals);
}
template <>
inline rvm<uint64_t, 8> set_k<uint64_t, 8>(const int32_t vals[MIPP_N_UINT64]) {
	return mipp_set_k_uint64_m8(vals);
}
template <>
inline rvm<uint32_t, 1> set_k<uint32_t, 1>(const int32_t vals[MIPP_N_UINT32]) {
	return mipp_set_k_uint32_m1(vals);
}
template <>
inline rvm<uint32_t, 2> set_k<uint32_t, 2>(const int32_t vals[MIPP_N_UINT32]) {
	return mipp_set_k_uint32_m2(vals);
}
template <>
inline rvm<uint32_t, 4> set_k<uint32_t, 4>(const int32_t vals[MIPP_N_UINT32]) {
	return mipp_set_k_uint32_m4(vals);
}
template <>
inline rvm<uint32_t, 8> set_k<uint32_t, 8>(const int32_t vals[MIPP_N_UINT32]) {
	return mipp_set_k_uint32_m8(vals);
}
template <>
inline rvm<uint16_t, 1> set_k<uint16_t, 1>(const int32_t vals[MIPP_N_UINT16]) {
	return mipp_set_k_uint16_m1(vals);
}
template <>
inline rvm<uint16_t, 2> set_k<uint16_t, 2>(const int32_t vals[MIPP_N_UINT16]) {
	return mipp_set_k_uint16_m2(vals);
}
template <>
inline rvm<uint16_t, 4> set_k<uint16_t, 4>(const int32_t vals[MIPP_N_UINT16]) {
	return mipp_set_k_uint16_m4(vals);
}
template <>
inline rvm<uint16_t, 8> set_k<uint16_t, 8>(const int32_t vals[MIPP_N_UINT16]) {
	return mipp_set_k_uint16_m8(vals);
}
template <>
inline rvm<uint8_t, 1> set_k<uint8_t, 1>(const int32_t vals[MIPP_N_UINT8]) {
	return mipp_set_k_uint8_m1(vals);
}
template <>
inline rvm<uint8_t, 2> set_k<uint8_t, 2>(const int32_t vals[MIPP_N_UINT8]) {
	return mipp_set_k_uint8_m2(vals);
}
template <>
inline rvm<uint8_t, 4> set_k<uint8_t, 4>(const int32_t vals[MIPP_N_UINT8]) {
	return mipp_set_k_uint8_m4(vals);
}
template <>
inline rvm<uint8_t, 8> set_k<uint8_t, 8>(const int32_t vals[MIPP_N_UINT8]) {
	return mipp_set_k_uint8_m8(vals);
}
template <typename T, int LMULT=1> inline rvd<T, LMULT> set1(const T) { std::cerr << "set1" << std::endl; exit(-1);}

template <>
inline rvd<float64_t, 1> set1<float64_t, 1>(const float64_t v0) {
	return mipp_set1_float64_m1(v0);
}
template <>
inline rvd<float64_t, 2> set1<float64_t, 2>(const float64_t v0) {
	return mipp_set1_float64_m2(v0);
}
template <>
inline rvd<float64_t, 4> set1<float64_t, 4>(const float64_t v0) {
	return mipp_set1_float64_m4(v0);
}
template <>
inline rvd<float64_t, 8> set1<float64_t, 8>(const float64_t v0) {
	return mipp_set1_float64_m8(v0);
}
template <>
inline rvd<float32_t, 1> set1<float32_t, 1>(const float32_t v0) {
	return mipp_set1_float32_m1(v0);
}
template <>
inline rvd<float32_t, 2> set1<float32_t, 2>(const float32_t v0) {
	return mipp_set1_float32_m2(v0);
}
template <>
inline rvd<float32_t, 4> set1<float32_t, 4>(const float32_t v0) {
	return mipp_set1_float32_m4(v0);
}
template <>
inline rvd<float32_t, 8> set1<float32_t, 8>(const float32_t v0) {
	return mipp_set1_float32_m8(v0);
}
template <>
inline rvd<int64_t, 1> set1<int64_t, 1>(const int64_t v0) {
	return mipp_set1_int64_m1(v0);
}
template <>
inline rvd<int64_t, 2> set1<int64_t, 2>(const int64_t v0) {
	return mipp_set1_int64_m2(v0);
}
template <>
inline rvd<int64_t, 4> set1<int64_t, 4>(const int64_t v0) {
	return mipp_set1_int64_m4(v0);
}
template <>
inline rvd<int64_t, 8> set1<int64_t, 8>(const int64_t v0) {
	return mipp_set1_int64_m8(v0);
}
template <>
inline rvd<int32_t, 1> set1<int32_t, 1>(const int32_t v0) {
	return mipp_set1_int32_m1(v0);
}
template <>
inline rvd<int32_t, 2> set1<int32_t, 2>(const int32_t v0) {
	return mipp_set1_int32_m2(v0);
}
template <>
inline rvd<int32_t, 4> set1<int32_t, 4>(const int32_t v0) {
	return mipp_set1_int32_m4(v0);
}
template <>
inline rvd<int32_t, 8> set1<int32_t, 8>(const int32_t v0) {
	return mipp_set1_int32_m8(v0);
}
template <>
inline rvd<int16_t, 1> set1<int16_t, 1>(const int16_t v0) {
	return mipp_set1_int16_m1(v0);
}
template <>
inline rvd<int16_t, 2> set1<int16_t, 2>(const int16_t v0) {
	return mipp_set1_int16_m2(v0);
}
template <>
inline rvd<int16_t, 4> set1<int16_t, 4>(const int16_t v0) {
	return mipp_set1_int16_m4(v0);
}
template <>
inline rvd<int16_t, 8> set1<int16_t, 8>(const int16_t v0) {
	return mipp_set1_int16_m8(v0);
}
template <>
inline rvd<int8_t, 1> set1<int8_t, 1>(const int8_t v0) {
	return mipp_set1_int8_m1(v0);
}
template <>
inline rvd<int8_t, 2> set1<int8_t, 2>(const int8_t v0) {
	return mipp_set1_int8_m2(v0);
}
template <>
inline rvd<int8_t, 4> set1<int8_t, 4>(const int8_t v0) {
	return mipp_set1_int8_m4(v0);
}
template <>
inline rvd<int8_t, 8> set1<int8_t, 8>(const int8_t v0) {
	return mipp_set1_int8_m8(v0);
}
template <>
inline rvd<uint64_t, 1> set1<uint64_t, 1>(const uint64_t v0) {
	return mipp_set1_uint64_m1(v0);
}
template <>
inline rvd<uint64_t, 2> set1<uint64_t, 2>(const uint64_t v0) {
	return mipp_set1_uint64_m2(v0);
}
template <>
inline rvd<uint64_t, 4> set1<uint64_t, 4>(const uint64_t v0) {
	return mipp_set1_uint64_m4(v0);
}
template <>
inline rvd<uint64_t, 8> set1<uint64_t, 8>(const uint64_t v0) {
	return mipp_set1_uint64_m8(v0);
}
template <>
inline rvd<uint32_t, 1> set1<uint32_t, 1>(const uint32_t v0) {
	return mipp_set1_uint32_m1(v0);
}
template <>
inline rvd<uint32_t, 2> set1<uint32_t, 2>(const uint32_t v0) {
	return mipp_set1_uint32_m2(v0);
}
template <>
inline rvd<uint32_t, 4> set1<uint32_t, 4>(const uint32_t v0) {
	return mipp_set1_uint32_m4(v0);
}
template <>
inline rvd<uint32_t, 8> set1<uint32_t, 8>(const uint32_t v0) {
	return mipp_set1_uint32_m8(v0);
}
template <>
inline rvd<uint16_t, 1> set1<uint16_t, 1>(const uint16_t v0) {
	return mipp_set1_uint16_m1(v0);
}
template <>
inline rvd<uint16_t, 2> set1<uint16_t, 2>(const uint16_t v0) {
	return mipp_set1_uint16_m2(v0);
}
template <>
inline rvd<uint16_t, 4> set1<uint16_t, 4>(const uint16_t v0) {
	return mipp_set1_uint16_m4(v0);
}
template <>
inline rvd<uint16_t, 8> set1<uint16_t, 8>(const uint16_t v0) {
	return mipp_set1_uint16_m8(v0);
}
template <>
inline rvd<uint8_t, 1> set1<uint8_t, 1>(const uint8_t v0) {
	return mipp_set1_uint8_m1(v0);
}
template <>
inline rvd<uint8_t, 2> set1<uint8_t, 2>(const uint8_t v0) {
	return mipp_set1_uint8_m2(v0);
}
template <>
inline rvd<uint8_t, 4> set1<uint8_t, 4>(const uint8_t v0) {
	return mipp_set1_uint8_m4(v0);
}
template <>
inline rvd<uint8_t, 8> set1<uint8_t, 8>(const uint8_t v0) {
	return mipp_set1_uint8_m8(v0);
}
template <typename T, int LMULT=1> inline rvm<T, LMULT> set1_k(const int32_t v0) { std::cerr << "set1_k" << std::endl; exit(-1);}

template <>
inline rvm<int64_t, 1> set1_k<int64_t, 1>(const int32_t v0) {
	return mipp_set1_k_int64_m1(v0);
}
template <>
inline rvm<int64_t, 2> set1_k<int64_t, 2>(const int32_t v0) {
	return mipp_set1_k_int64_m2(v0);
}
template <>
inline rvm<int64_t, 4> set1_k<int64_t, 4>(const int32_t v0) {
	return mipp_set1_k_int64_m4(v0);
}
template <>
inline rvm<int64_t, 8> set1_k<int64_t, 8>(const int32_t v0) {
	return mipp_set1_k_int64_m8(v0);
}
template <>
inline rvm<int32_t, 1> set1_k<int32_t, 1>(const int32_t v0) {
	return mipp_set1_k_int32_m1(v0);
}
template <>
inline rvm<int32_t, 2> set1_k<int32_t, 2>(const int32_t v0) {
	return mipp_set1_k_int32_m2(v0);
}
template <>
inline rvm<int32_t, 4> set1_k<int32_t, 4>(const int32_t v0) {
	return mipp_set1_k_int32_m4(v0);
}
template <>
inline rvm<int32_t, 8> set1_k<int32_t, 8>(const int32_t v0) {
	return mipp_set1_k_int32_m8(v0);
}
template <>
inline rvm<int16_t, 1> set1_k<int16_t, 1>(const int32_t v0) {
	return mipp_set1_k_int16_m1(v0);
}
template <>
inline rvm<int16_t, 2> set1_k<int16_t, 2>(const int32_t v0) {
	return mipp_set1_k_int16_m2(v0);
}
template <>
inline rvm<int16_t, 4> set1_k<int16_t, 4>(const int32_t v0) {
	return mipp_set1_k_int16_m4(v0);
}
template <>
inline rvm<int16_t, 8> set1_k<int16_t, 8>(const int32_t v0) {
	return mipp_set1_k_int16_m8(v0);
}
template <>
inline rvm<int8_t, 1> set1_k<int8_t, 1>(const int32_t v0) {
	return mipp_set1_k_int8_m1(v0);
}
template <>
inline rvm<int8_t, 2> set1_k<int8_t, 2>(const int32_t v0) {
	return mipp_set1_k_int8_m2(v0);
}
template <>
inline rvm<int8_t, 4> set1_k<int8_t, 4>(const int32_t v0) {
	return mipp_set1_k_int8_m4(v0);
}
template <>
inline rvm<int8_t, 8> set1_k<int8_t, 8>(const int32_t v0) {
	return mipp_set1_k_int8_m8(v0);
}
template <>
inline rvm<uint64_t, 1> set1_k<uint64_t, 1>(const int32_t v0) {
	return mipp_set1_k_uint64_m1(v0);
}
template <>
inline rvm<uint64_t, 2> set1_k<uint64_t, 2>(const int32_t v0) {
	return mipp_set1_k_uint64_m2(v0);
}
template <>
inline rvm<uint64_t, 4> set1_k<uint64_t, 4>(const int32_t v0) {
	return mipp_set1_k_uint64_m4(v0);
}
template <>
inline rvm<uint64_t, 8> set1_k<uint64_t, 8>(const int32_t v0) {
	return mipp_set1_k_uint64_m8(v0);
}
template <>
inline rvm<uint32_t, 1> set1_k<uint32_t, 1>(const int32_t v0) {
	return mipp_set1_k_uint32_m1(v0);
}
template <>
inline rvm<uint32_t, 2> set1_k<uint32_t, 2>(const int32_t v0) {
	return mipp_set1_k_uint32_m2(v0);
}
template <>
inline rvm<uint32_t, 4> set1_k<uint32_t, 4>(const int32_t v0) {
	return mipp_set1_k_uint32_m4(v0);
}
template <>
inline rvm<uint32_t, 8> set1_k<uint32_t, 8>(const int32_t v0) {
	return mipp_set1_k_uint32_m8(v0);
}
template <>
inline rvm<uint16_t, 1> set1_k<uint16_t, 1>(const int32_t v0) {
	return mipp_set1_k_uint16_m1(v0);
}
template <>
inline rvm<uint16_t, 2> set1_k<uint16_t, 2>(const int32_t v0) {
	return mipp_set1_k_uint16_m2(v0);
}
template <>
inline rvm<uint16_t, 4> set1_k<uint16_t, 4>(const int32_t v0) {
	return mipp_set1_k_uint16_m4(v0);
}
template <>
inline rvm<uint16_t, 8> set1_k<uint16_t, 8>(const int32_t v0) {
	return mipp_set1_k_uint16_m8(v0);
}
template <>
inline rvm<uint8_t, 1> set1_k<uint8_t, 1>(const int32_t v0) {
	return mipp_set1_k_uint8_m1(v0);
}
template <>
inline rvm<uint8_t, 2> set1_k<uint8_t, 2>(const int32_t v0) {
	return mipp_set1_k_uint8_m2(v0);
}
template <>
inline rvm<uint8_t, 4> set1_k<uint8_t, 4>(const int32_t v0) {
	return mipp_set1_k_uint8_m4(v0);
}
template <>
inline rvm<uint8_t, 8> set1_k<uint8_t, 8>(const int32_t v0) {
	return mipp_set1_k_uint8_m8(v0);
}
inline rvd<float64_t,1> maskzld(const rvm<int32_t,1> m0, const float64_t* p0) {
	return mipp_maskzld_float64_m1(m0, p0);
}
inline rvd<float64_t,2> maskzld(const rvm<int32_t,2> m0, const float64_t* p0) {
	return mipp_maskzld_float64_m2(m0, p0);
}
inline rvd<float64_t,4> maskzld(const rvm<int32_t,4> m0, const float64_t* p0) {
	return mipp_maskzld_float64_m4(m0, p0);
}
inline rvd<float64_t,8> maskzld(const rvm<int32_t,8> m0, const float64_t* p0) {
	return mipp_maskzld_float64_m8(m0, p0);
}
inline rvd<float32_t,1> maskzld(const rvm<int32_t,1> m0, const float32_t* p0) {
	return mipp_maskzld_float32_m1(m0, p0);
}
inline rvd<float32_t,2> maskzld(const rvm<int32_t,2> m0, const float32_t* p0) {
	return mipp_maskzld_float32_m2(m0, p0);
}
inline rvd<float32_t,4> maskzld(const rvm<int32_t,4> m0, const float32_t* p0) {
	return mipp_maskzld_float32_m4(m0, p0);
}
inline rvd<float32_t,8> maskzld(const rvm<int32_t,8> m0, const float32_t* p0) {
	return mipp_maskzld_float32_m8(m0, p0);
}
inline rvd<int64_t,1> maskzld(const rvm<int32_t,1> m0, const int64_t* p0) {
	return mipp_maskzld_int64_m1(m0, p0);
}
inline rvd<int64_t,2> maskzld(const rvm<int32_t,2> m0, const int64_t* p0) {
	return mipp_maskzld_int64_m2(m0, p0);
}
inline rvd<int64_t,4> maskzld(const rvm<int32_t,4> m0, const int64_t* p0) {
	return mipp_maskzld_int64_m4(m0, p0);
}
inline rvd<int64_t,8> maskzld(const rvm<int32_t,8> m0, const int64_t* p0) {
	return mipp_maskzld_int64_m8(m0, p0);
}
inline rvd<int32_t,1> maskzld(const rvm<int32_t,1> m0, const int32_t* p0) {
	return mipp_maskzld_int32_m1(m0, p0);
}
inline rvd<int32_t,2> maskzld(const rvm<int32_t,2> m0, const int32_t* p0) {
	return mipp_maskzld_int32_m2(m0, p0);
}
inline rvd<int32_t,4> maskzld(const rvm<int32_t,4> m0, const int32_t* p0) {
	return mipp_maskzld_int32_m4(m0, p0);
}
inline rvd<int32_t,8> maskzld(const rvm<int32_t,8> m0, const int32_t* p0) {
	return mipp_maskzld_int32_m8(m0, p0);
}
inline rvd<int16_t,1> maskzld(const rvm<int32_t,1> m0, const int16_t* p0) {
	return mipp_maskzld_int16_m1(m0, p0);
}
inline rvd<int16_t,2> maskzld(const rvm<int32_t,2> m0, const int16_t* p0) {
	return mipp_maskzld_int16_m2(m0, p0);
}
inline rvd<int16_t,4> maskzld(const rvm<int32_t,4> m0, const int16_t* p0) {
	return mipp_maskzld_int16_m4(m0, p0);
}
inline rvd<int16_t,8> maskzld(const rvm<int32_t,8> m0, const int16_t* p0) {
	return mipp_maskzld_int16_m8(m0, p0);
}
inline rvd<int8_t,1> maskzld(const rvm<int32_t,1> m0, const int8_t* p0) {
	return mipp_maskzld_int8_m1(m0, p0);
}
inline rvd<int8_t,2> maskzld(const rvm<int32_t,2> m0, const int8_t* p0) {
	return mipp_maskzld_int8_m2(m0, p0);
}
inline rvd<int8_t,4> maskzld(const rvm<int32_t,4> m0, const int8_t* p0) {
	return mipp_maskzld_int8_m4(m0, p0);
}
inline rvd<int8_t,8> maskzld(const rvm<int32_t,8> m0, const int8_t* p0) {
	return mipp_maskzld_int8_m8(m0, p0);
}
inline rvd<uint64_t,1> maskzld(const rvm<int32_t,1> m0, const uint64_t* p0) {
	return mipp_maskzld_uint64_m1(m0, p0);
}
inline rvd<uint64_t,2> maskzld(const rvm<int32_t,2> m0, const uint64_t* p0) {
	return mipp_maskzld_uint64_m2(m0, p0);
}
inline rvd<uint64_t,4> maskzld(const rvm<int32_t,4> m0, const uint64_t* p0) {
	return mipp_maskzld_uint64_m4(m0, p0);
}
inline rvd<uint64_t,8> maskzld(const rvm<int32_t,8> m0, const uint64_t* p0) {
	return mipp_maskzld_uint64_m8(m0, p0);
}
inline rvd<uint32_t,1> maskzld(const rvm<int32_t,1> m0, const uint32_t* p0) {
	return mipp_maskzld_uint32_m1(m0, p0);
}
inline rvd<uint32_t,2> maskzld(const rvm<int32_t,2> m0, const uint32_t* p0) {
	return mipp_maskzld_uint32_m2(m0, p0);
}
inline rvd<uint32_t,4> maskzld(const rvm<int32_t,4> m0, const uint32_t* p0) {
	return mipp_maskzld_uint32_m4(m0, p0);
}
inline rvd<uint32_t,8> maskzld(const rvm<int32_t,8> m0, const uint32_t* p0) {
	return mipp_maskzld_uint32_m8(m0, p0);
}
inline rvd<uint16_t,1> maskzld(const rvm<int32_t,1> m0, const uint16_t* p0) {
	return mipp_maskzld_uint16_m1(m0, p0);
}
inline rvd<uint16_t,2> maskzld(const rvm<int32_t,2> m0, const uint16_t* p0) {
	return mipp_maskzld_uint16_m2(m0, p0);
}
inline rvd<uint16_t,4> maskzld(const rvm<int32_t,4> m0, const uint16_t* p0) {
	return mipp_maskzld_uint16_m4(m0, p0);
}
inline rvd<uint16_t,8> maskzld(const rvm<int32_t,8> m0, const uint16_t* p0) {
	return mipp_maskzld_uint16_m8(m0, p0);
}
inline rvd<uint8_t,1> maskzld(const rvm<int32_t,1> m0, const uint8_t* p0) {
	return mipp_maskzld_uint8_m1(m0, p0);
}
inline rvd<uint8_t,2> maskzld(const rvm<int32_t,2> m0, const uint8_t* p0) {
	return mipp_maskzld_uint8_m2(m0, p0);
}
inline rvd<uint8_t,4> maskzld(const rvm<int32_t,4> m0, const uint8_t* p0) {
	return mipp_maskzld_uint8_m4(m0, p0);
}
inline rvd<uint8_t,8> maskzld(const rvm<int32_t,8> m0, const uint8_t* p0) {
	return mipp_maskzld_uint8_m8(m0, p0);
}
inline void maskst(float64_t* p0, const rvm<int32_t,1> m0, const rvd<float64_t,1> r0) {
	mipp_maskst_float64_m1(p0, m0, r0);
}
inline void maskst(float64_t* p0, const rvm<int32_t,2> m0, const rvd<float64_t,2> r0) {
	mipp_maskst_float64_m2(p0, m0, r0);
}
inline void maskst(float64_t* p0, const rvm<int32_t,4> m0, const rvd<float64_t,4> r0) {
	mipp_maskst_float64_m4(p0, m0, r0);
}
inline void maskst(float64_t* p0, const rvm<int32_t,8> m0, const rvd<float64_t,8> r0) {
	mipp_maskst_float64_m8(p0, m0, r0);
}
inline void maskst(float32_t* p0, const rvm<int32_t,1> m0, const rvd<float32_t,1> r0) {
	mipp_maskst_float32_m1(p0, m0, r0);
}
inline void maskst(float32_t* p0, const rvm<int32_t,2> m0, const rvd<float32_t,2> r0) {
	mipp_maskst_float32_m2(p0, m0, r0);
}
inline void maskst(float32_t* p0, const rvm<int32_t,4> m0, const rvd<float32_t,4> r0) {
	mipp_maskst_float32_m4(p0, m0, r0);
}
inline void maskst(float32_t* p0, const rvm<int32_t,8> m0, const rvd<float32_t,8> r0) {
	mipp_maskst_float32_m8(p0, m0, r0);
}
inline void maskst(int64_t* p0, const rvm<int32_t,1> m0, const rvd<int64_t,1> r0) {
	mipp_maskst_int64_m1(p0, m0, r0);
}
inline void maskst(int64_t* p0, const rvm<int32_t,2> m0, const rvd<int64_t,2> r0) {
	mipp_maskst_int64_m2(p0, m0, r0);
}
inline void maskst(int64_t* p0, const rvm<int32_t,4> m0, const rvd<int64_t,4> r0) {
	mipp_maskst_int64_m4(p0, m0, r0);
}
inline void maskst(int64_t* p0, const rvm<int32_t,8> m0, const rvd<int64_t,8> r0) {
	mipp_maskst_int64_m8(p0, m0, r0);
}
inline void maskst(int32_t* p0, const rvm<int32_t,1> m0, const rvd<int32_t,1> r0) {
	mipp_maskst_int32_m1(p0, m0, r0);
}
inline void maskst(int32_t* p0, const rvm<int32_t,2> m0, const rvd<int32_t,2> r0) {
	mipp_maskst_int32_m2(p0, m0, r0);
}
inline void maskst(int32_t* p0, const rvm<int32_t,4> m0, const rvd<int32_t,4> r0) {
	mipp_maskst_int32_m4(p0, m0, r0);
}
inline void maskst(int32_t* p0, const rvm<int32_t,8> m0, const rvd<int32_t,8> r0) {
	mipp_maskst_int32_m8(p0, m0, r0);
}
inline void maskst(int16_t* p0, const rvm<int32_t,1> m0, const rvd<int16_t,1> r0) {
	mipp_maskst_int16_m1(p0, m0, r0);
}
inline void maskst(int16_t* p0, const rvm<int32_t,2> m0, const rvd<int16_t,2> r0) {
	mipp_maskst_int16_m2(p0, m0, r0);
}
inline void maskst(int16_t* p0, const rvm<int32_t,4> m0, const rvd<int16_t,4> r0) {
	mipp_maskst_int16_m4(p0, m0, r0);
}
inline void maskst(int16_t* p0, const rvm<int32_t,8> m0, const rvd<int16_t,8> r0) {
	mipp_maskst_int16_m8(p0, m0, r0);
}
inline void maskst(int8_t* p0, const rvm<int32_t,1> m0, const rvd<int8_t,1> r0) {
	mipp_maskst_int8_m1(p0, m0, r0);
}
inline void maskst(int8_t* p0, const rvm<int32_t,2> m0, const rvd<int8_t,2> r0) {
	mipp_maskst_int8_m2(p0, m0, r0);
}
inline void maskst(int8_t* p0, const rvm<int32_t,4> m0, const rvd<int8_t,4> r0) {
	mipp_maskst_int8_m4(p0, m0, r0);
}
inline void maskst(int8_t* p0, const rvm<int32_t,8> m0, const rvd<int8_t,8> r0) {
	mipp_maskst_int8_m8(p0, m0, r0);
}
inline void maskst(uint64_t* p0, const rvm<int32_t,1> m0, const rvd<uint64_t,1> r0) {
	mipp_maskst_uint64_m1(p0, m0, r0);
}
inline void maskst(uint64_t* p0, const rvm<int32_t,2> m0, const rvd<uint64_t,2> r0) {
	mipp_maskst_uint64_m2(p0, m0, r0);
}
inline void maskst(uint64_t* p0, const rvm<int32_t,4> m0, const rvd<uint64_t,4> r0) {
	mipp_maskst_uint64_m4(p0, m0, r0);
}
inline void maskst(uint64_t* p0, const rvm<int32_t,8> m0, const rvd<uint64_t,8> r0) {
	mipp_maskst_uint64_m8(p0, m0, r0);
}
inline void maskst(uint32_t* p0, const rvm<int32_t,1> m0, const rvd<uint32_t,1> r0) {
	mipp_maskst_uint32_m1(p0, m0, r0);
}
inline void maskst(uint32_t* p0, const rvm<int32_t,2> m0, const rvd<uint32_t,2> r0) {
	mipp_maskst_uint32_m2(p0, m0, r0);
}
inline void maskst(uint32_t* p0, const rvm<int32_t,4> m0, const rvd<uint32_t,4> r0) {
	mipp_maskst_uint32_m4(p0, m0, r0);
}
inline void maskst(uint32_t* p0, const rvm<int32_t,8> m0, const rvd<uint32_t,8> r0) {
	mipp_maskst_uint32_m8(p0, m0, r0);
}
inline void maskst(uint16_t* p0, const rvm<int32_t,1> m0, const rvd<uint16_t,1> r0) {
	mipp_maskst_uint16_m1(p0, m0, r0);
}
inline void maskst(uint16_t* p0, const rvm<int32_t,2> m0, const rvd<uint16_t,2> r0) {
	mipp_maskst_uint16_m2(p0, m0, r0);
}
inline void maskst(uint16_t* p0, const rvm<int32_t,4> m0, const rvd<uint16_t,4> r0) {
	mipp_maskst_uint16_m4(p0, m0, r0);
}
inline void maskst(uint16_t* p0, const rvm<int32_t,8> m0, const rvd<uint16_t,8> r0) {
	mipp_maskst_uint16_m8(p0, m0, r0);
}
inline void maskst(uint8_t* p0, const rvm<int32_t,1> m0, const rvd<uint8_t,1> r0) {
	mipp_maskst_uint8_m1(p0, m0, r0);
}
inline void maskst(uint8_t* p0, const rvm<int32_t,2> m0, const rvd<uint8_t,2> r0) {
	mipp_maskst_uint8_m2(p0, m0, r0);
}
inline void maskst(uint8_t* p0, const rvm<int32_t,4> m0, const rvd<uint8_t,4> r0) {
	mipp_maskst_uint8_m4(p0, m0, r0);
}
inline void maskst(uint8_t* p0, const rvm<int32_t,8> m0, const rvd<uint8_t,8> r0) {
	mipp_maskst_uint8_m8(p0, m0, r0);
}
template <typename T, int LMULT=1> inline rvd<T, LMULT> set0() { std::cerr << "set0" << std::endl; exit(-1);}

template <>
inline rvd<float64_t, 1> set0<float64_t, 1>() {
	return mipp_set0_float64_m1();
}
template <>
inline rvd<float64_t, 2> set0<float64_t, 2>() {
	return mipp_set0_float64_m2();
}
template <>
inline rvd<float64_t, 4> set0<float64_t, 4>() {
	return mipp_set0_float64_m4();
}
template <>
inline rvd<float64_t, 8> set0<float64_t, 8>() {
	return mipp_set0_float64_m8();
}
template <>
inline rvd<float32_t, 1> set0<float32_t, 1>() {
	return mipp_set0_float32_m1();
}
template <>
inline rvd<float32_t, 2> set0<float32_t, 2>() {
	return mipp_set0_float32_m2();
}
template <>
inline rvd<float32_t, 4> set0<float32_t, 4>() {
	return mipp_set0_float32_m4();
}
template <>
inline rvd<float32_t, 8> set0<float32_t, 8>() {
	return mipp_set0_float32_m8();
}
template <>
inline rvd<int64_t, 1> set0<int64_t, 1>() {
	return mipp_set0_int64_m1();
}
template <>
inline rvd<int64_t, 2> set0<int64_t, 2>() {
	return mipp_set0_int64_m2();
}
template <>
inline rvd<int64_t, 4> set0<int64_t, 4>() {
	return mipp_set0_int64_m4();
}
template <>
inline rvd<int64_t, 8> set0<int64_t, 8>() {
	return mipp_set0_int64_m8();
}
template <>
inline rvd<int32_t, 1> set0<int32_t, 1>() {
	return mipp_set0_int32_m1();
}
template <>
inline rvd<int32_t, 2> set0<int32_t, 2>() {
	return mipp_set0_int32_m2();
}
template <>
inline rvd<int32_t, 4> set0<int32_t, 4>() {
	return mipp_set0_int32_m4();
}
template <>
inline rvd<int32_t, 8> set0<int32_t, 8>() {
	return mipp_set0_int32_m8();
}
template <>
inline rvd<int16_t, 1> set0<int16_t, 1>() {
	return mipp_set0_int16_m1();
}
template <>
inline rvd<int16_t, 2> set0<int16_t, 2>() {
	return mipp_set0_int16_m2();
}
template <>
inline rvd<int16_t, 4> set0<int16_t, 4>() {
	return mipp_set0_int16_m4();
}
template <>
inline rvd<int16_t, 8> set0<int16_t, 8>() {
	return mipp_set0_int16_m8();
}
template <>
inline rvd<int8_t, 1> set0<int8_t, 1>() {
	return mipp_set0_int8_m1();
}
template <>
inline rvd<int8_t, 2> set0<int8_t, 2>() {
	return mipp_set0_int8_m2();
}
template <>
inline rvd<int8_t, 4> set0<int8_t, 4>() {
	return mipp_set0_int8_m4();
}
template <>
inline rvd<int8_t, 8> set0<int8_t, 8>() {
	return mipp_set0_int8_m8();
}
template <>
inline rvd<uint64_t, 1> set0<uint64_t, 1>() {
	return mipp_set0_uint64_m1();
}
template <>
inline rvd<uint64_t, 2> set0<uint64_t, 2>() {
	return mipp_set0_uint64_m2();
}
template <>
inline rvd<uint64_t, 4> set0<uint64_t, 4>() {
	return mipp_set0_uint64_m4();
}
template <>
inline rvd<uint64_t, 8> set0<uint64_t, 8>() {
	return mipp_set0_uint64_m8();
}
template <>
inline rvd<uint32_t, 1> set0<uint32_t, 1>() {
	return mipp_set0_uint32_m1();
}
template <>
inline rvd<uint32_t, 2> set0<uint32_t, 2>() {
	return mipp_set0_uint32_m2();
}
template <>
inline rvd<uint32_t, 4> set0<uint32_t, 4>() {
	return mipp_set0_uint32_m4();
}
template <>
inline rvd<uint32_t, 8> set0<uint32_t, 8>() {
	return mipp_set0_uint32_m8();
}
template <>
inline rvd<uint16_t, 1> set0<uint16_t, 1>() {
	return mipp_set0_uint16_m1();
}
template <>
inline rvd<uint16_t, 2> set0<uint16_t, 2>() {
	return mipp_set0_uint16_m2();
}
template <>
inline rvd<uint16_t, 4> set0<uint16_t, 4>() {
	return mipp_set0_uint16_m4();
}
template <>
inline rvd<uint16_t, 8> set0<uint16_t, 8>() {
	return mipp_set0_uint16_m8();
}
template <>
inline rvd<uint8_t, 1> set0<uint8_t, 1>() {
	return mipp_set0_uint8_m1();
}
template <>
inline rvd<uint8_t, 2> set0<uint8_t, 2>() {
	return mipp_set0_uint8_m2();
}
template <>
inline rvd<uint8_t, 4> set0<uint8_t, 4>() {
	return mipp_set0_uint8_m4();
}
template <>
inline rvd<uint8_t, 8> set0<uint8_t, 8>() {
	return mipp_set0_uint8_m8();
}
template <typename T, int LMULT=1> inline rvm<T, LMULT> set0_k() { std::cerr << "set0_k" << std::endl; exit(-1);}

template <>
inline rvm<float64_t, 1> set0_k<float64_t, 1>() {
	return mipp_set0_k_float64_m1();
}
template <>
inline rvm<float64_t, 2> set0_k<float64_t, 2>() {
	return mipp_set0_k_float64_m2();
}
template <>
inline rvm<float64_t, 4> set0_k<float64_t, 4>() {
	return mipp_set0_k_float64_m4();
}
template <>
inline rvm<float64_t, 8> set0_k<float64_t, 8>() {
	return mipp_set0_k_float64_m8();
}
template <>
inline rvm<float32_t, 1> set0_k<float32_t, 1>() {
	return mipp_set0_k_float32_m1();
}
template <>
inline rvm<float32_t, 2> set0_k<float32_t, 2>() {
	return mipp_set0_k_float32_m2();
}
template <>
inline rvm<float32_t, 4> set0_k<float32_t, 4>() {
	return mipp_set0_k_float32_m4();
}
template <>
inline rvm<float32_t, 8> set0_k<float32_t, 8>() {
	return mipp_set0_k_float32_m8();
}
template <>
inline rvm<int64_t, 1> set0_k<int64_t, 1>() {
	return mipp_set0_k_int64_m1();
}
template <>
inline rvm<int64_t, 2> set0_k<int64_t, 2>() {
	return mipp_set0_k_int64_m2();
}
template <>
inline rvm<int64_t, 4> set0_k<int64_t, 4>() {
	return mipp_set0_k_int64_m4();
}
template <>
inline rvm<int64_t, 8> set0_k<int64_t, 8>() {
	return mipp_set0_k_int64_m8();
}
template <>
inline rvm<int32_t, 1> set0_k<int32_t, 1>() {
	return mipp_set0_k_int32_m1();
}
template <>
inline rvm<int32_t, 2> set0_k<int32_t, 2>() {
	return mipp_set0_k_int32_m2();
}
template <>
inline rvm<int32_t, 4> set0_k<int32_t, 4>() {
	return mipp_set0_k_int32_m4();
}
template <>
inline rvm<int32_t, 8> set0_k<int32_t, 8>() {
	return mipp_set0_k_int32_m8();
}
template <>
inline rvm<int16_t, 1> set0_k<int16_t, 1>() {
	return mipp_set0_k_int16_m1();
}
template <>
inline rvm<int16_t, 2> set0_k<int16_t, 2>() {
	return mipp_set0_k_int16_m2();
}
template <>
inline rvm<int16_t, 4> set0_k<int16_t, 4>() {
	return mipp_set0_k_int16_m4();
}
template <>
inline rvm<int16_t, 8> set0_k<int16_t, 8>() {
	return mipp_set0_k_int16_m8();
}
template <>
inline rvm<int8_t, 1> set0_k<int8_t, 1>() {
	return mipp_set0_k_int8_m1();
}
template <>
inline rvm<int8_t, 2> set0_k<int8_t, 2>() {
	return mipp_set0_k_int8_m2();
}
template <>
inline rvm<int8_t, 4> set0_k<int8_t, 4>() {
	return mipp_set0_k_int8_m4();
}
template <>
inline rvm<int8_t, 8> set0_k<int8_t, 8>() {
	return mipp_set0_k_int8_m8();
}
template <>
inline rvm<uint64_t, 1> set0_k<uint64_t, 1>() {
	return mipp_set0_k_uint64_m1();
}
template <>
inline rvm<uint64_t, 2> set0_k<uint64_t, 2>() {
	return mipp_set0_k_uint64_m2();
}
template <>
inline rvm<uint64_t, 4> set0_k<uint64_t, 4>() {
	return mipp_set0_k_uint64_m4();
}
template <>
inline rvm<uint64_t, 8> set0_k<uint64_t, 8>() {
	return mipp_set0_k_uint64_m8();
}
template <>
inline rvm<uint32_t, 1> set0_k<uint32_t, 1>() {
	return mipp_set0_k_uint32_m1();
}
template <>
inline rvm<uint32_t, 2> set0_k<uint32_t, 2>() {
	return mipp_set0_k_uint32_m2();
}
template <>
inline rvm<uint32_t, 4> set0_k<uint32_t, 4>() {
	return mipp_set0_k_uint32_m4();
}
template <>
inline rvm<uint32_t, 8> set0_k<uint32_t, 8>() {
	return mipp_set0_k_uint32_m8();
}
template <>
inline rvm<uint16_t, 1> set0_k<uint16_t, 1>() {
	return mipp_set0_k_uint16_m1();
}
template <>
inline rvm<uint16_t, 2> set0_k<uint16_t, 2>() {
	return mipp_set0_k_uint16_m2();
}
template <>
inline rvm<uint16_t, 4> set0_k<uint16_t, 4>() {
	return mipp_set0_k_uint16_m4();
}
template <>
inline rvm<uint16_t, 8> set0_k<uint16_t, 8>() {
	return mipp_set0_k_uint16_m8();
}
template <>
inline rvm<uint8_t, 1> set0_k<uint8_t, 1>() {
	return mipp_set0_k_uint8_m1();
}
template <>
inline rvm<uint8_t, 2> set0_k<uint8_t, 2>() {
	return mipp_set0_k_uint8_m2();
}
template <>
inline rvm<uint8_t, 4> set0_k<uint8_t, 4>() {
	return mipp_set0_k_uint8_m4();
}
template <>
inline rvm<uint8_t, 8> set0_k<uint8_t, 8>() {
	return mipp_set0_k_uint8_m8();
}
inline float64_t get(const rvd<float64_t,1> r0, const uint32_t v0) {
	return mipp_get_float64_m1(r0, v0);
}
inline float64_t get(const rvd<float64_t,2> r0, const uint32_t v0) {
	return mipp_get_float64_m2(r0, v0);
}
inline float64_t get(const rvd<float64_t,4> r0, const uint32_t v0) {
	return mipp_get_float64_m4(r0, v0);
}
inline float64_t get(const rvd<float64_t,8> r0, const uint32_t v0) {
	return mipp_get_float64_m8(r0, v0);
}
inline float32_t get(const rvd<float32_t,1> r0, const uint32_t v0) {
	return mipp_get_float32_m1(r0, v0);
}
inline float32_t get(const rvd<float32_t,2> r0, const uint32_t v0) {
	return mipp_get_float32_m2(r0, v0);
}
inline float32_t get(const rvd<float32_t,4> r0, const uint32_t v0) {
	return mipp_get_float32_m4(r0, v0);
}
inline float32_t get(const rvd<float32_t,8> r0, const uint32_t v0) {
	return mipp_get_float32_m8(r0, v0);
}
inline int64_t get(const rvd<int64_t,1> r0, const uint32_t v0) {
	return mipp_get_int64_m1(r0, v0);
}
inline int64_t get(const rvd<int64_t,2> r0, const uint32_t v0) {
	return mipp_get_int64_m2(r0, v0);
}
inline int64_t get(const rvd<int64_t,4> r0, const uint32_t v0) {
	return mipp_get_int64_m4(r0, v0);
}
inline int64_t get(const rvd<int64_t,8> r0, const uint32_t v0) {
	return mipp_get_int64_m8(r0, v0);
}
inline int32_t get(const rvd<int32_t,1> r0, const uint32_t v0) {
	return mipp_get_int32_m1(r0, v0);
}
inline int32_t get(const rvd<int32_t,2> r0, const uint32_t v0) {
	return mipp_get_int32_m2(r0, v0);
}
inline int32_t get(const rvd<int32_t,4> r0, const uint32_t v0) {
	return mipp_get_int32_m4(r0, v0);
}
inline int32_t get(const rvd<int32_t,8> r0, const uint32_t v0) {
	return mipp_get_int32_m8(r0, v0);
}
inline int16_t get(const rvd<int16_t,1> r0, const uint32_t v0) {
	return mipp_get_int16_m1(r0, v0);
}
inline int16_t get(const rvd<int16_t,2> r0, const uint32_t v0) {
	return mipp_get_int16_m2(r0, v0);
}
inline int16_t get(const rvd<int16_t,4> r0, const uint32_t v0) {
	return mipp_get_int16_m4(r0, v0);
}
inline int16_t get(const rvd<int16_t,8> r0, const uint32_t v0) {
	return mipp_get_int16_m8(r0, v0);
}
inline int8_t get(const rvd<int8_t,1> r0, const uint32_t v0) {
	return mipp_get_int8_m1(r0, v0);
}
inline int8_t get(const rvd<int8_t,2> r0, const uint32_t v0) {
	return mipp_get_int8_m2(r0, v0);
}
inline int8_t get(const rvd<int8_t,4> r0, const uint32_t v0) {
	return mipp_get_int8_m4(r0, v0);
}
inline int8_t get(const rvd<int8_t,8> r0, const uint32_t v0) {
	return mipp_get_int8_m8(r0, v0);
}
inline uint64_t get(const rvd<uint64_t,1> r0, const uint32_t v0) {
	return mipp_get_uint64_m1(r0, v0);
}
inline uint64_t get(const rvd<uint64_t,2> r0, const uint32_t v0) {
	return mipp_get_uint64_m2(r0, v0);
}
inline uint64_t get(const rvd<uint64_t,4> r0, const uint32_t v0) {
	return mipp_get_uint64_m4(r0, v0);
}
inline uint64_t get(const rvd<uint64_t,8> r0, const uint32_t v0) {
	return mipp_get_uint64_m8(r0, v0);
}
inline uint32_t get(const rvd<uint32_t,1> r0, const uint32_t v0) {
	return mipp_get_uint32_m1(r0, v0);
}
inline uint32_t get(const rvd<uint32_t,2> r0, const uint32_t v0) {
	return mipp_get_uint32_m2(r0, v0);
}
inline uint32_t get(const rvd<uint32_t,4> r0, const uint32_t v0) {
	return mipp_get_uint32_m4(r0, v0);
}
inline uint32_t get(const rvd<uint32_t,8> r0, const uint32_t v0) {
	return mipp_get_uint32_m8(r0, v0);
}
inline uint16_t get(const rvd<uint16_t,1> r0, const uint32_t v0) {
	return mipp_get_uint16_m1(r0, v0);
}
inline uint16_t get(const rvd<uint16_t,2> r0, const uint32_t v0) {
	return mipp_get_uint16_m2(r0, v0);
}
inline uint16_t get(const rvd<uint16_t,4> r0, const uint32_t v0) {
	return mipp_get_uint16_m4(r0, v0);
}
inline uint16_t get(const rvd<uint16_t,8> r0, const uint32_t v0) {
	return mipp_get_uint16_m8(r0, v0);
}
inline uint8_t get(const rvd<uint8_t,1> r0, const uint32_t v0) {
	return mipp_get_uint8_m1(r0, v0);
}
inline uint8_t get(const rvd<uint8_t,2> r0, const uint32_t v0) {
	return mipp_get_uint8_m2(r0, v0);
}
inline uint8_t get(const rvd<uint8_t,4> r0, const uint32_t v0) {
	return mipp_get_uint8_m4(r0, v0);
}
inline uint8_t get(const rvd<uint8_t,8> r0, const uint32_t v0) {
	return mipp_get_uint8_m8(r0, v0);
}
inline float64_t get(const rvm<float64_t,1> m0, const uint32_t v0) {
	return mipp_get_k_float64_m1(m0, v0);
}
inline float64_t get(const rvm<float64_t,2> m0, const uint32_t v0) {
	return mipp_get_k_float64_m2(m0, v0);
}
inline float64_t get(const rvm<float64_t,4> m0, const uint32_t v0) {
	return mipp_get_k_float64_m4(m0, v0);
}
inline float64_t get(const rvm<float64_t,8> m0, const uint32_t v0) {
	return mipp_get_k_float64_m8(m0, v0);
}
inline float32_t get(const rvm<float32_t,1> m0, const uint32_t v0) {
	return mipp_get_k_float32_m1(m0, v0);
}
inline float32_t get(const rvm<float32_t,2> m0, const uint32_t v0) {
	return mipp_get_k_float32_m2(m0, v0);
}
inline float32_t get(const rvm<float32_t,4> m0, const uint32_t v0) {
	return mipp_get_k_float32_m4(m0, v0);
}
inline float32_t get(const rvm<float32_t,8> m0, const uint32_t v0) {
	return mipp_get_k_float32_m8(m0, v0);
}
inline int64_t get(const rvm<int64_t,1> m0, const uint32_t v0) {
	return mipp_get_k_int64_m1(m0, v0);
}
inline int64_t get(const rvm<int64_t,2> m0, const uint32_t v0) {
	return mipp_get_k_int64_m2(m0, v0);
}
inline int64_t get(const rvm<int64_t,4> m0, const uint32_t v0) {
	return mipp_get_k_int64_m4(m0, v0);
}
inline int64_t get(const rvm<int64_t,8> m0, const uint32_t v0) {
	return mipp_get_k_int64_m8(m0, v0);
}
inline int32_t get(const rvm<int32_t,1> m0, const uint32_t v0) {
	return mipp_get_k_int32_m1(m0, v0);
}
inline int32_t get(const rvm<int32_t,2> m0, const uint32_t v0) {
	return mipp_get_k_int32_m2(m0, v0);
}
inline int32_t get(const rvm<int32_t,4> m0, const uint32_t v0) {
	return mipp_get_k_int32_m4(m0, v0);
}
inline int32_t get(const rvm<int32_t,8> m0, const uint32_t v0) {
	return mipp_get_k_int32_m8(m0, v0);
}
inline int16_t get(const rvm<int16_t,1> m0, const uint32_t v0) {
	return mipp_get_k_int16_m1(m0, v0);
}
inline int16_t get(const rvm<int16_t,2> m0, const uint32_t v0) {
	return mipp_get_k_int16_m2(m0, v0);
}
inline int16_t get(const rvm<int16_t,4> m0, const uint32_t v0) {
	return mipp_get_k_int16_m4(m0, v0);
}
inline int16_t get(const rvm<int16_t,8> m0, const uint32_t v0) {
	return mipp_get_k_int16_m8(m0, v0);
}
inline int8_t get(const rvm<int8_t,1> m0, const uint32_t v0) {
	return mipp_get_k_int8_m1(m0, v0);
}
inline int8_t get(const rvm<int8_t,2> m0, const uint32_t v0) {
	return mipp_get_k_int8_m2(m0, v0);
}
inline int8_t get(const rvm<int8_t,4> m0, const uint32_t v0) {
	return mipp_get_k_int8_m4(m0, v0);
}
inline int8_t get(const rvm<int8_t,8> m0, const uint32_t v0) {
	return mipp_get_k_int8_m8(m0, v0);
}
inline uint64_t get(const rvm<uint64_t,1> m0, const uint32_t v0) {
	return mipp_get_k_uint64_m1(m0, v0);
}
inline uint64_t get(const rvm<uint64_t,2> m0, const uint32_t v0) {
	return mipp_get_k_uint64_m2(m0, v0);
}
inline uint64_t get(const rvm<uint64_t,4> m0, const uint32_t v0) {
	return mipp_get_k_uint64_m4(m0, v0);
}
inline uint64_t get(const rvm<uint64_t,8> m0, const uint32_t v0) {
	return mipp_get_k_uint64_m8(m0, v0);
}
inline uint32_t get(const rvm<uint32_t,1> m0, const uint32_t v0) {
	return mipp_get_k_uint32_m1(m0, v0);
}
inline uint32_t get(const rvm<uint32_t,2> m0, const uint32_t v0) {
	return mipp_get_k_uint32_m2(m0, v0);
}
inline uint32_t get(const rvm<uint32_t,4> m0, const uint32_t v0) {
	return mipp_get_k_uint32_m4(m0, v0);
}
inline uint32_t get(const rvm<uint32_t,8> m0, const uint32_t v0) {
	return mipp_get_k_uint32_m8(m0, v0);
}
inline uint16_t get(const rvm<uint16_t,1> m0, const uint32_t v0) {
	return mipp_get_k_uint16_m1(m0, v0);
}
inline uint16_t get(const rvm<uint16_t,2> m0, const uint32_t v0) {
	return mipp_get_k_uint16_m2(m0, v0);
}
inline uint16_t get(const rvm<uint16_t,4> m0, const uint32_t v0) {
	return mipp_get_k_uint16_m4(m0, v0);
}
inline uint16_t get(const rvm<uint16_t,8> m0, const uint32_t v0) {
	return mipp_get_k_uint16_m8(m0, v0);
}
inline uint8_t get(const rvm<uint8_t,1> m0, const uint32_t v0) {
	return mipp_get_k_uint8_m1(m0, v0);
}
inline uint8_t get(const rvm<uint8_t,2> m0, const uint32_t v0) {
	return mipp_get_k_uint8_m2(m0, v0);
}
inline uint8_t get(const rvm<uint8_t,4> m0, const uint32_t v0) {
	return mipp_get_k_uint8_m4(m0, v0);
}
inline uint8_t get(const rvm<uint8_t,8> m0, const uint32_t v0) {
	return mipp_get_k_uint8_m8(m0, v0);
}
inline float64_t getfirst(const rvd<float64_t,1> r0) {
	return mipp_getfirst_float64_m1(r0);
}
inline float64_t getfirst(const rvd<float64_t,2> r0) {
	return mipp_getfirst_float64_m2(r0);
}
inline float64_t getfirst(const rvd<float64_t,4> r0) {
	return mipp_getfirst_float64_m4(r0);
}
inline float64_t getfirst(const rvd<float64_t,8> r0) {
	return mipp_getfirst_float64_m8(r0);
}
inline float32_t getfirst(const rvd<float32_t,1> r0) {
	return mipp_getfirst_float32_m1(r0);
}
inline float32_t getfirst(const rvd<float32_t,2> r0) {
	return mipp_getfirst_float32_m2(r0);
}
inline float32_t getfirst(const rvd<float32_t,4> r0) {
	return mipp_getfirst_float32_m4(r0);
}
inline float32_t getfirst(const rvd<float32_t,8> r0) {
	return mipp_getfirst_float32_m8(r0);
}
inline int64_t getfirst(const rvd<int64_t,1> r0) {
	return mipp_getfirst_int64_m1(r0);
}
inline int64_t getfirst(const rvd<int64_t,2> r0) {
	return mipp_getfirst_int64_m2(r0);
}
inline int64_t getfirst(const rvd<int64_t,4> r0) {
	return mipp_getfirst_int64_m4(r0);
}
inline int64_t getfirst(const rvd<int64_t,8> r0) {
	return mipp_getfirst_int64_m8(r0);
}
inline int32_t getfirst(const rvd<int32_t,1> r0) {
	return mipp_getfirst_int32_m1(r0);
}
inline int32_t getfirst(const rvd<int32_t,2> r0) {
	return mipp_getfirst_int32_m2(r0);
}
inline int32_t getfirst(const rvd<int32_t,4> r0) {
	return mipp_getfirst_int32_m4(r0);
}
inline int32_t getfirst(const rvd<int32_t,8> r0) {
	return mipp_getfirst_int32_m8(r0);
}
inline int16_t getfirst(const rvd<int16_t,1> r0) {
	return mipp_getfirst_int16_m1(r0);
}
inline int16_t getfirst(const rvd<int16_t,2> r0) {
	return mipp_getfirst_int16_m2(r0);
}
inline int16_t getfirst(const rvd<int16_t,4> r0) {
	return mipp_getfirst_int16_m4(r0);
}
inline int16_t getfirst(const rvd<int16_t,8> r0) {
	return mipp_getfirst_int16_m8(r0);
}
inline int8_t getfirst(const rvd<int8_t,1> r0) {
	return mipp_getfirst_int8_m1(r0);
}
inline int8_t getfirst(const rvd<int8_t,2> r0) {
	return mipp_getfirst_int8_m2(r0);
}
inline int8_t getfirst(const rvd<int8_t,4> r0) {
	return mipp_getfirst_int8_m4(r0);
}
inline int8_t getfirst(const rvd<int8_t,8> r0) {
	return mipp_getfirst_int8_m8(r0);
}
inline uint64_t getfirst(const rvd<uint64_t,1> r0) {
	return mipp_getfirst_uint64_m1(r0);
}
inline uint64_t getfirst(const rvd<uint64_t,2> r0) {
	return mipp_getfirst_uint64_m2(r0);
}
inline uint64_t getfirst(const rvd<uint64_t,4> r0) {
	return mipp_getfirst_uint64_m4(r0);
}
inline uint64_t getfirst(const rvd<uint64_t,8> r0) {
	return mipp_getfirst_uint64_m8(r0);
}
inline uint32_t getfirst(const rvd<uint32_t,1> r0) {
	return mipp_getfirst_uint32_m1(r0);
}
inline uint32_t getfirst(const rvd<uint32_t,2> r0) {
	return mipp_getfirst_uint32_m2(r0);
}
inline uint32_t getfirst(const rvd<uint32_t,4> r0) {
	return mipp_getfirst_uint32_m4(r0);
}
inline uint32_t getfirst(const rvd<uint32_t,8> r0) {
	return mipp_getfirst_uint32_m8(r0);
}
inline uint16_t getfirst(const rvd<uint16_t,1> r0) {
	return mipp_getfirst_uint16_m1(r0);
}
inline uint16_t getfirst(const rvd<uint16_t,2> r0) {
	return mipp_getfirst_uint16_m2(r0);
}
inline uint16_t getfirst(const rvd<uint16_t,4> r0) {
	return mipp_getfirst_uint16_m4(r0);
}
inline uint16_t getfirst(const rvd<uint16_t,8> r0) {
	return mipp_getfirst_uint16_m8(r0);
}
inline uint8_t getfirst(const rvd<uint8_t,1> r0) {
	return mipp_getfirst_uint8_m1(r0);
}
inline uint8_t getfirst(const rvd<uint8_t,2> r0) {
	return mipp_getfirst_uint8_m2(r0);
}
inline uint8_t getfirst(const rvd<uint8_t,4> r0) {
	return mipp_getfirst_uint8_m4(r0);
}
inline uint8_t getfirst(const rvd<uint8_t,8> r0) {
	return mipp_getfirst_uint8_m8(r0);
}
inline rvd<float64_t,1> sqrt(const rvd<float64_t,1> r0) {
	return mipp_sqrt_float64_m1(r0);
}
inline rvd<float64_t,2> sqrt(const rvd<float64_t,2> r0) {
	return mipp_sqrt_float64_m2(r0);
}
inline rvd<float64_t,4> sqrt(const rvd<float64_t,4> r0) {
	return mipp_sqrt_float64_m4(r0);
}
inline rvd<float64_t,8> sqrt(const rvd<float64_t,8> r0) {
	return mipp_sqrt_float64_m8(r0);
}
inline rvd<float32_t,1> sqrt(const rvd<float32_t,1> r0) {
	return mipp_sqrt_float32_m1(r0);
}
inline rvd<float32_t,2> sqrt(const rvd<float32_t,2> r0) {
	return mipp_sqrt_float32_m2(r0);
}
inline rvd<float32_t,4> sqrt(const rvd<float32_t,4> r0) {
	return mipp_sqrt_float32_m4(r0);
}
inline rvd<float32_t,8> sqrt(const rvd<float32_t,8> r0) {
	return mipp_sqrt_float32_m8(r0);
}
inline rvd<float64_t,1> rsqrt(const rvd<float64_t,1> r0) {
	return mipp_rsqrt_float64_m1(r0);
}
inline rvd<float64_t,2> rsqrt(const rvd<float64_t,2> r0) {
	return mipp_rsqrt_float64_m2(r0);
}
inline rvd<float64_t,4> rsqrt(const rvd<float64_t,4> r0) {
	return mipp_rsqrt_float64_m4(r0);
}
inline rvd<float64_t,8> rsqrt(const rvd<float64_t,8> r0) {
	return mipp_rsqrt_float64_m8(r0);
}
inline rvd<float32_t,1> rsqrt(const rvd<float32_t,1> r0) {
	return mipp_rsqrt_float32_m1(r0);
}
inline rvd<float32_t,2> rsqrt(const rvd<float32_t,2> r0) {
	return mipp_rsqrt_float32_m2(r0);
}
inline rvd<float32_t,4> rsqrt(const rvd<float32_t,4> r0) {
	return mipp_rsqrt_float32_m4(r0);
}
inline rvd<float32_t,8> rsqrt(const rvd<float32_t,8> r0) {
	return mipp_rsqrt_float32_m8(r0);
}
inline rvd<float64_t,1> add(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_add_float64_m1(r0, r1);
}
inline rvd<float64_t,2> add(const rvd<float64_t,2> r0, const rvd<float64_t,2> r1) {
	return mipp_add_float64_m2(r0, r1);
}
inline rvd<float64_t,4> add(const rvd<float64_t,4> r0, const rvd<float64_t,4> r1) {
	return mipp_add_float64_m4(r0, r1);
}
inline rvd<float64_t,8> add(const rvd<float64_t,8> r0, const rvd<float64_t,8> r1) {
	return mipp_add_float64_m8(r0, r1);
}
inline rvd<float32_t,1> add(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_add_float32_m1(r0, r1);
}
inline rvd<float32_t,2> add(const rvd<float32_t,2> r0, const rvd<float32_t,2> r1) {
	return mipp_add_float32_m2(r0, r1);
}
inline rvd<float32_t,4> add(const rvd<float32_t,4> r0, const rvd<float32_t,4> r1) {
	return mipp_add_float32_m4(r0, r1);
}
inline rvd<float32_t,8> add(const rvd<float32_t,8> r0, const rvd<float32_t,8> r1) {
	return mipp_add_float32_m8(r0, r1);
}
inline rvd<int64_t,1> add(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_add_int64_m1(r0, r1);
}
inline rvd<int64_t,2> add(const rvd<int64_t,2> r0, const rvd<int64_t,2> r1) {
	return mipp_add_int64_m2(r0, r1);
}
inline rvd<int64_t,4> add(const rvd<int64_t,4> r0, const rvd<int64_t,4> r1) {
	return mipp_add_int64_m4(r0, r1);
}
inline rvd<int64_t,8> add(const rvd<int64_t,8> r0, const rvd<int64_t,8> r1) {
	return mipp_add_int64_m8(r0, r1);
}
inline rvd<int32_t,1> add(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_add_int32_m1(r0, r1);
}
inline rvd<int32_t,2> add(const rvd<int32_t,2> r0, const rvd<int32_t,2> r1) {
	return mipp_add_int32_m2(r0, r1);
}
inline rvd<int32_t,4> add(const rvd<int32_t,4> r0, const rvd<int32_t,4> r1) {
	return mipp_add_int32_m4(r0, r1);
}
inline rvd<int32_t,8> add(const rvd<int32_t,8> r0, const rvd<int32_t,8> r1) {
	return mipp_add_int32_m8(r0, r1);
}
inline rvd<int16_t,1> add(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_add_int16_m1(r0, r1);
}
inline rvd<int16_t,2> add(const rvd<int16_t,2> r0, const rvd<int16_t,2> r1) {
	return mipp_add_int16_m2(r0, r1);
}
inline rvd<int16_t,4> add(const rvd<int16_t,4> r0, const rvd<int16_t,4> r1) {
	return mipp_add_int16_m4(r0, r1);
}
inline rvd<int16_t,8> add(const rvd<int16_t,8> r0, const rvd<int16_t,8> r1) {
	return mipp_add_int16_m8(r0, r1);
}
inline rvd<int8_t,1> add(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_add_int8_m1(r0, r1);
}
inline rvd<int8_t,2> add(const rvd<int8_t,2> r0, const rvd<int8_t,2> r1) {
	return mipp_add_int8_m2(r0, r1);
}
inline rvd<int8_t,4> add(const rvd<int8_t,4> r0, const rvd<int8_t,4> r1) {
	return mipp_add_int8_m4(r0, r1);
}
inline rvd<int8_t,8> add(const rvd<int8_t,8> r0, const rvd<int8_t,8> r1) {
	return mipp_add_int8_m8(r0, r1);
}
inline rvd<uint64_t,1> add(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_add_uint64_m1(r0, r1);
}
inline rvd<uint64_t,2> add(const rvd<uint64_t,2> r0, const rvd<uint64_t,2> r1) {
	return mipp_add_uint64_m2(r0, r1);
}
inline rvd<uint64_t,4> add(const rvd<uint64_t,4> r0, const rvd<uint64_t,4> r1) {
	return mipp_add_uint64_m4(r0, r1);
}
inline rvd<uint64_t,8> add(const rvd<uint64_t,8> r0, const rvd<uint64_t,8> r1) {
	return mipp_add_uint64_m8(r0, r1);
}
inline rvd<uint32_t,1> add(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_add_uint32_m1(r0, r1);
}
inline rvd<uint32_t,2> add(const rvd<uint32_t,2> r0, const rvd<uint32_t,2> r1) {
	return mipp_add_uint32_m2(r0, r1);
}
inline rvd<uint32_t,4> add(const rvd<uint32_t,4> r0, const rvd<uint32_t,4> r1) {
	return mipp_add_uint32_m4(r0, r1);
}
inline rvd<uint32_t,8> add(const rvd<uint32_t,8> r0, const rvd<uint32_t,8> r1) {
	return mipp_add_uint32_m8(r0, r1);
}
inline rvd<uint16_t,1> add(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_add_uint16_m1(r0, r1);
}
inline rvd<uint16_t,2> add(const rvd<uint16_t,2> r0, const rvd<uint16_t,2> r1) {
	return mipp_add_uint16_m2(r0, r1);
}
inline rvd<uint16_t,4> add(const rvd<uint16_t,4> r0, const rvd<uint16_t,4> r1) {
	return mipp_add_uint16_m4(r0, r1);
}
inline rvd<uint16_t,8> add(const rvd<uint16_t,8> r0, const rvd<uint16_t,8> r1) {
	return mipp_add_uint16_m8(r0, r1);
}
inline rvd<uint8_t,1> add(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_add_uint8_m1(r0, r1);
}
inline rvd<uint8_t,2> add(const rvd<uint8_t,2> r0, const rvd<uint8_t,2> r1) {
	return mipp_add_uint8_m2(r0, r1);
}
inline rvd<uint8_t,4> add(const rvd<uint8_t,4> r0, const rvd<uint8_t,4> r1) {
	return mipp_add_uint8_m4(r0, r1);
}
inline rvd<uint8_t,8> add(const rvd<uint8_t,8> r0, const rvd<uint8_t,8> r1) {
	return mipp_add_uint8_m8(r0, r1);
}
inline rvd<float64_t,1> sub(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_sub_float64_m1(r0, r1);
}
inline rvd<float64_t,2> sub(const rvd<float64_t,2> r0, const rvd<float64_t,2> r1) {
	return mipp_sub_float64_m2(r0, r1);
}
inline rvd<float64_t,4> sub(const rvd<float64_t,4> r0, const rvd<float64_t,4> r1) {
	return mipp_sub_float64_m4(r0, r1);
}
inline rvd<float64_t,8> sub(const rvd<float64_t,8> r0, const rvd<float64_t,8> r1) {
	return mipp_sub_float64_m8(r0, r1);
}
inline rvd<float32_t,1> sub(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_sub_float32_m1(r0, r1);
}
inline rvd<float32_t,2> sub(const rvd<float32_t,2> r0, const rvd<float32_t,2> r1) {
	return mipp_sub_float32_m2(r0, r1);
}
inline rvd<float32_t,4> sub(const rvd<float32_t,4> r0, const rvd<float32_t,4> r1) {
	return mipp_sub_float32_m4(r0, r1);
}
inline rvd<float32_t,8> sub(const rvd<float32_t,8> r0, const rvd<float32_t,8> r1) {
	return mipp_sub_float32_m8(r0, r1);
}
inline rvd<int64_t,1> sub(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_sub_int64_m1(r0, r1);
}
inline rvd<int64_t,2> sub(const rvd<int64_t,2> r0, const rvd<int64_t,2> r1) {
	return mipp_sub_int64_m2(r0, r1);
}
inline rvd<int64_t,4> sub(const rvd<int64_t,4> r0, const rvd<int64_t,4> r1) {
	return mipp_sub_int64_m4(r0, r1);
}
inline rvd<int64_t,8> sub(const rvd<int64_t,8> r0, const rvd<int64_t,8> r1) {
	return mipp_sub_int64_m8(r0, r1);
}
inline rvd<int32_t,1> sub(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_sub_int32_m1(r0, r1);
}
inline rvd<int32_t,2> sub(const rvd<int32_t,2> r0, const rvd<int32_t,2> r1) {
	return mipp_sub_int32_m2(r0, r1);
}
inline rvd<int32_t,4> sub(const rvd<int32_t,4> r0, const rvd<int32_t,4> r1) {
	return mipp_sub_int32_m4(r0, r1);
}
inline rvd<int32_t,8> sub(const rvd<int32_t,8> r0, const rvd<int32_t,8> r1) {
	return mipp_sub_int32_m8(r0, r1);
}
inline rvd<int16_t,1> sub(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_sub_int16_m1(r0, r1);
}
inline rvd<int16_t,2> sub(const rvd<int16_t,2> r0, const rvd<int16_t,2> r1) {
	return mipp_sub_int16_m2(r0, r1);
}
inline rvd<int16_t,4> sub(const rvd<int16_t,4> r0, const rvd<int16_t,4> r1) {
	return mipp_sub_int16_m4(r0, r1);
}
inline rvd<int16_t,8> sub(const rvd<int16_t,8> r0, const rvd<int16_t,8> r1) {
	return mipp_sub_int16_m8(r0, r1);
}
inline rvd<int8_t,1> sub(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_sub_int8_m1(r0, r1);
}
inline rvd<int8_t,2> sub(const rvd<int8_t,2> r0, const rvd<int8_t,2> r1) {
	return mipp_sub_int8_m2(r0, r1);
}
inline rvd<int8_t,4> sub(const rvd<int8_t,4> r0, const rvd<int8_t,4> r1) {
	return mipp_sub_int8_m4(r0, r1);
}
inline rvd<int8_t,8> sub(const rvd<int8_t,8> r0, const rvd<int8_t,8> r1) {
	return mipp_sub_int8_m8(r0, r1);
}
inline rvd<uint64_t,1> sub(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_sub_uint64_m1(r0, r1);
}
inline rvd<uint64_t,2> sub(const rvd<uint64_t,2> r0, const rvd<uint64_t,2> r1) {
	return mipp_sub_uint64_m2(r0, r1);
}
inline rvd<uint64_t,4> sub(const rvd<uint64_t,4> r0, const rvd<uint64_t,4> r1) {
	return mipp_sub_uint64_m4(r0, r1);
}
inline rvd<uint64_t,8> sub(const rvd<uint64_t,8> r0, const rvd<uint64_t,8> r1) {
	return mipp_sub_uint64_m8(r0, r1);
}
inline rvd<uint32_t,1> sub(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_sub_uint32_m1(r0, r1);
}
inline rvd<uint32_t,2> sub(const rvd<uint32_t,2> r0, const rvd<uint32_t,2> r1) {
	return mipp_sub_uint32_m2(r0, r1);
}
inline rvd<uint32_t,4> sub(const rvd<uint32_t,4> r0, const rvd<uint32_t,4> r1) {
	return mipp_sub_uint32_m4(r0, r1);
}
inline rvd<uint32_t,8> sub(const rvd<uint32_t,8> r0, const rvd<uint32_t,8> r1) {
	return mipp_sub_uint32_m8(r0, r1);
}
inline rvd<uint16_t,1> sub(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_sub_uint16_m1(r0, r1);
}
inline rvd<uint16_t,2> sub(const rvd<uint16_t,2> r0, const rvd<uint16_t,2> r1) {
	return mipp_sub_uint16_m2(r0, r1);
}
inline rvd<uint16_t,4> sub(const rvd<uint16_t,4> r0, const rvd<uint16_t,4> r1) {
	return mipp_sub_uint16_m4(r0, r1);
}
inline rvd<uint16_t,8> sub(const rvd<uint16_t,8> r0, const rvd<uint16_t,8> r1) {
	return mipp_sub_uint16_m8(r0, r1);
}
inline rvd<uint8_t,1> sub(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_sub_uint8_m1(r0, r1);
}
inline rvd<uint8_t,2> sub(const rvd<uint8_t,2> r0, const rvd<uint8_t,2> r1) {
	return mipp_sub_uint8_m2(r0, r1);
}
inline rvd<uint8_t,4> sub(const rvd<uint8_t,4> r0, const rvd<uint8_t,4> r1) {
	return mipp_sub_uint8_m4(r0, r1);
}
inline rvd<uint8_t,8> sub(const rvd<uint8_t,8> r0, const rvd<uint8_t,8> r1) {
	return mipp_sub_uint8_m8(r0, r1);
}
inline rvd<float64_t,1> mul(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_mul_float64_m1(r0, r1);
}
inline rvd<float64_t,2> mul(const rvd<float64_t,2> r0, const rvd<float64_t,2> r1) {
	return mipp_mul_float64_m2(r0, r1);
}
inline rvd<float64_t,4> mul(const rvd<float64_t,4> r0, const rvd<float64_t,4> r1) {
	return mipp_mul_float64_m4(r0, r1);
}
inline rvd<float64_t,8> mul(const rvd<float64_t,8> r0, const rvd<float64_t,8> r1) {
	return mipp_mul_float64_m8(r0, r1);
}
inline rvd<float32_t,1> mul(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_mul_float32_m1(r0, r1);
}
inline rvd<float32_t,2> mul(const rvd<float32_t,2> r0, const rvd<float32_t,2> r1) {
	return mipp_mul_float32_m2(r0, r1);
}
inline rvd<float32_t,4> mul(const rvd<float32_t,4> r0, const rvd<float32_t,4> r1) {
	return mipp_mul_float32_m4(r0, r1);
}
inline rvd<float32_t,8> mul(const rvd<float32_t,8> r0, const rvd<float32_t,8> r1) {
	return mipp_mul_float32_m8(r0, r1);
}
inline rvd<int64_t,1> mul(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_mul_int64_m1(r0, r1);
}
inline rvd<int64_t,2> mul(const rvd<int64_t,2> r0, const rvd<int64_t,2> r1) {
	return mipp_mul_int64_m2(r0, r1);
}
inline rvd<int64_t,4> mul(const rvd<int64_t,4> r0, const rvd<int64_t,4> r1) {
	return mipp_mul_int64_m4(r0, r1);
}
inline rvd<int64_t,8> mul(const rvd<int64_t,8> r0, const rvd<int64_t,8> r1) {
	return mipp_mul_int64_m8(r0, r1);
}
inline rvd<int32_t,1> mul(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_mul_int32_m1(r0, r1);
}
inline rvd<int32_t,2> mul(const rvd<int32_t,2> r0, const rvd<int32_t,2> r1) {
	return mipp_mul_int32_m2(r0, r1);
}
inline rvd<int32_t,4> mul(const rvd<int32_t,4> r0, const rvd<int32_t,4> r1) {
	return mipp_mul_int32_m4(r0, r1);
}
inline rvd<int32_t,8> mul(const rvd<int32_t,8> r0, const rvd<int32_t,8> r1) {
	return mipp_mul_int32_m8(r0, r1);
}
inline rvd<int16_t,1> mul(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_mul_int16_m1(r0, r1);
}
inline rvd<int16_t,2> mul(const rvd<int16_t,2> r0, const rvd<int16_t,2> r1) {
	return mipp_mul_int16_m2(r0, r1);
}
inline rvd<int16_t,4> mul(const rvd<int16_t,4> r0, const rvd<int16_t,4> r1) {
	return mipp_mul_int16_m4(r0, r1);
}
inline rvd<int16_t,8> mul(const rvd<int16_t,8> r0, const rvd<int16_t,8> r1) {
	return mipp_mul_int16_m8(r0, r1);
}
inline rvd<int8_t,1> mul(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_mul_int8_m1(r0, r1);
}
inline rvd<int8_t,2> mul(const rvd<int8_t,2> r0, const rvd<int8_t,2> r1) {
	return mipp_mul_int8_m2(r0, r1);
}
inline rvd<int8_t,4> mul(const rvd<int8_t,4> r0, const rvd<int8_t,4> r1) {
	return mipp_mul_int8_m4(r0, r1);
}
inline rvd<int8_t,8> mul(const rvd<int8_t,8> r0, const rvd<int8_t,8> r1) {
	return mipp_mul_int8_m8(r0, r1);
}
inline rvd<uint64_t,1> mul(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_mul_uint64_m1(r0, r1);
}
inline rvd<uint64_t,2> mul(const rvd<uint64_t,2> r0, const rvd<uint64_t,2> r1) {
	return mipp_mul_uint64_m2(r0, r1);
}
inline rvd<uint64_t,4> mul(const rvd<uint64_t,4> r0, const rvd<uint64_t,4> r1) {
	return mipp_mul_uint64_m4(r0, r1);
}
inline rvd<uint64_t,8> mul(const rvd<uint64_t,8> r0, const rvd<uint64_t,8> r1) {
	return mipp_mul_uint64_m8(r0, r1);
}
inline rvd<uint32_t,1> mul(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_mul_uint32_m1(r0, r1);
}
inline rvd<uint32_t,2> mul(const rvd<uint32_t,2> r0, const rvd<uint32_t,2> r1) {
	return mipp_mul_uint32_m2(r0, r1);
}
inline rvd<uint32_t,4> mul(const rvd<uint32_t,4> r0, const rvd<uint32_t,4> r1) {
	return mipp_mul_uint32_m4(r0, r1);
}
inline rvd<uint32_t,8> mul(const rvd<uint32_t,8> r0, const rvd<uint32_t,8> r1) {
	return mipp_mul_uint32_m8(r0, r1);
}
inline rvd<uint16_t,1> mul(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_mul_uint16_m1(r0, r1);
}
inline rvd<uint16_t,2> mul(const rvd<uint16_t,2> r0, const rvd<uint16_t,2> r1) {
	return mipp_mul_uint16_m2(r0, r1);
}
inline rvd<uint16_t,4> mul(const rvd<uint16_t,4> r0, const rvd<uint16_t,4> r1) {
	return mipp_mul_uint16_m4(r0, r1);
}
inline rvd<uint16_t,8> mul(const rvd<uint16_t,8> r0, const rvd<uint16_t,8> r1) {
	return mipp_mul_uint16_m8(r0, r1);
}
inline rvd<uint8_t,1> mul(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_mul_uint8_m1(r0, r1);
}
inline rvd<uint8_t,2> mul(const rvd<uint8_t,2> r0, const rvd<uint8_t,2> r1) {
	return mipp_mul_uint8_m2(r0, r1);
}
inline rvd<uint8_t,4> mul(const rvd<uint8_t,4> r0, const rvd<uint8_t,4> r1) {
	return mipp_mul_uint8_m4(r0, r1);
}
inline rvd<uint8_t,8> mul(const rvd<uint8_t,8> r0, const rvd<uint8_t,8> r1) {
	return mipp_mul_uint8_m8(r0, r1);
}
inline rvd<float64_t,1> div(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_div_float64_m1(r0, r1);
}
inline rvd<float64_t,2> div(const rvd<float64_t,2> r0, const rvd<float64_t,2> r1) {
	return mipp_div_float64_m2(r0, r1);
}
inline rvd<float64_t,4> div(const rvd<float64_t,4> r0, const rvd<float64_t,4> r1) {
	return mipp_div_float64_m4(r0, r1);
}
inline rvd<float64_t,8> div(const rvd<float64_t,8> r0, const rvd<float64_t,8> r1) {
	return mipp_div_float64_m8(r0, r1);
}
inline rvd<float32_t,1> div(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_div_float32_m1(r0, r1);
}
inline rvd<float32_t,2> div(const rvd<float32_t,2> r0, const rvd<float32_t,2> r1) {
	return mipp_div_float32_m2(r0, r1);
}
inline rvd<float32_t,4> div(const rvd<float32_t,4> r0, const rvd<float32_t,4> r1) {
	return mipp_div_float32_m4(r0, r1);
}
inline rvd<float32_t,8> div(const rvd<float32_t,8> r0, const rvd<float32_t,8> r1) {
	return mipp_div_float32_m8(r0, r1);
}
inline rvd<float64_t,1> min(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_min_float64_m1(r0, r1);
}
inline rvd<float64_t,2> min(const rvd<float64_t,2> r0, const rvd<float64_t,2> r1) {
	return mipp_min_float64_m2(r0, r1);
}
inline rvd<float64_t,4> min(const rvd<float64_t,4> r0, const rvd<float64_t,4> r1) {
	return mipp_min_float64_m4(r0, r1);
}
inline rvd<float64_t,8> min(const rvd<float64_t,8> r0, const rvd<float64_t,8> r1) {
	return mipp_min_float64_m8(r0, r1);
}
inline rvd<float32_t,1> min(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_min_float32_m1(r0, r1);
}
inline rvd<float32_t,2> min(const rvd<float32_t,2> r0, const rvd<float32_t,2> r1) {
	return mipp_min_float32_m2(r0, r1);
}
inline rvd<float32_t,4> min(const rvd<float32_t,4> r0, const rvd<float32_t,4> r1) {
	return mipp_min_float32_m4(r0, r1);
}
inline rvd<float32_t,8> min(const rvd<float32_t,8> r0, const rvd<float32_t,8> r1) {
	return mipp_min_float32_m8(r0, r1);
}
inline rvd<int64_t,1> min(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_min_int64_m1(r0, r1);
}
inline rvd<int64_t,2> min(const rvd<int64_t,2> r0, const rvd<int64_t,2> r1) {
	return mipp_min_int64_m2(r0, r1);
}
inline rvd<int64_t,4> min(const rvd<int64_t,4> r0, const rvd<int64_t,4> r1) {
	return mipp_min_int64_m4(r0, r1);
}
inline rvd<int64_t,8> min(const rvd<int64_t,8> r0, const rvd<int64_t,8> r1) {
	return mipp_min_int64_m8(r0, r1);
}
inline rvd<int32_t,1> min(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_min_int32_m1(r0, r1);
}
inline rvd<int32_t,2> min(const rvd<int32_t,2> r0, const rvd<int32_t,2> r1) {
	return mipp_min_int32_m2(r0, r1);
}
inline rvd<int32_t,4> min(const rvd<int32_t,4> r0, const rvd<int32_t,4> r1) {
	return mipp_min_int32_m4(r0, r1);
}
inline rvd<int32_t,8> min(const rvd<int32_t,8> r0, const rvd<int32_t,8> r1) {
	return mipp_min_int32_m8(r0, r1);
}
inline rvd<int16_t,1> min(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_min_int16_m1(r0, r1);
}
inline rvd<int16_t,2> min(const rvd<int16_t,2> r0, const rvd<int16_t,2> r1) {
	return mipp_min_int16_m2(r0, r1);
}
inline rvd<int16_t,4> min(const rvd<int16_t,4> r0, const rvd<int16_t,4> r1) {
	return mipp_min_int16_m4(r0, r1);
}
inline rvd<int16_t,8> min(const rvd<int16_t,8> r0, const rvd<int16_t,8> r1) {
	return mipp_min_int16_m8(r0, r1);
}
inline rvd<int8_t,1> min(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_min_int8_m1(r0, r1);
}
inline rvd<int8_t,2> min(const rvd<int8_t,2> r0, const rvd<int8_t,2> r1) {
	return mipp_min_int8_m2(r0, r1);
}
inline rvd<int8_t,4> min(const rvd<int8_t,4> r0, const rvd<int8_t,4> r1) {
	return mipp_min_int8_m4(r0, r1);
}
inline rvd<int8_t,8> min(const rvd<int8_t,8> r0, const rvd<int8_t,8> r1) {
	return mipp_min_int8_m8(r0, r1);
}
inline rvd<uint64_t,1> min(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_min_uint64_m1(r0, r1);
}
inline rvd<uint64_t,2> min(const rvd<uint64_t,2> r0, const rvd<uint64_t,2> r1) {
	return mipp_min_uint64_m2(r0, r1);
}
inline rvd<uint64_t,4> min(const rvd<uint64_t,4> r0, const rvd<uint64_t,4> r1) {
	return mipp_min_uint64_m4(r0, r1);
}
inline rvd<uint64_t,8> min(const rvd<uint64_t,8> r0, const rvd<uint64_t,8> r1) {
	return mipp_min_uint64_m8(r0, r1);
}
inline rvd<uint32_t,1> min(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_min_uint32_m1(r0, r1);
}
inline rvd<uint32_t,2> min(const rvd<uint32_t,2> r0, const rvd<uint32_t,2> r1) {
	return mipp_min_uint32_m2(r0, r1);
}
inline rvd<uint32_t,4> min(const rvd<uint32_t,4> r0, const rvd<uint32_t,4> r1) {
	return mipp_min_uint32_m4(r0, r1);
}
inline rvd<uint32_t,8> min(const rvd<uint32_t,8> r0, const rvd<uint32_t,8> r1) {
	return mipp_min_uint32_m8(r0, r1);
}
inline rvd<uint16_t,1> min(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_min_uint16_m1(r0, r1);
}
inline rvd<uint16_t,2> min(const rvd<uint16_t,2> r0, const rvd<uint16_t,2> r1) {
	return mipp_min_uint16_m2(r0, r1);
}
inline rvd<uint16_t,4> min(const rvd<uint16_t,4> r0, const rvd<uint16_t,4> r1) {
	return mipp_min_uint16_m4(r0, r1);
}
inline rvd<uint16_t,8> min(const rvd<uint16_t,8> r0, const rvd<uint16_t,8> r1) {
	return mipp_min_uint16_m8(r0, r1);
}
inline rvd<uint8_t,1> min(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_min_uint8_m1(r0, r1);
}
inline rvd<uint8_t,2> min(const rvd<uint8_t,2> r0, const rvd<uint8_t,2> r1) {
	return mipp_min_uint8_m2(r0, r1);
}
inline rvd<uint8_t,4> min(const rvd<uint8_t,4> r0, const rvd<uint8_t,4> r1) {
	return mipp_min_uint8_m4(r0, r1);
}
inline rvd<uint8_t,8> min(const rvd<uint8_t,8> r0, const rvd<uint8_t,8> r1) {
	return mipp_min_uint8_m8(r0, r1);
}
inline rvd<float64_t,1> max(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_max_float64_m1(r0, r1);
}
inline rvd<float64_t,2> max(const rvd<float64_t,2> r0, const rvd<float64_t,2> r1) {
	return mipp_max_float64_m2(r0, r1);
}
inline rvd<float64_t,4> max(const rvd<float64_t,4> r0, const rvd<float64_t,4> r1) {
	return mipp_max_float64_m4(r0, r1);
}
inline rvd<float64_t,8> max(const rvd<float64_t,8> r0, const rvd<float64_t,8> r1) {
	return mipp_max_float64_m8(r0, r1);
}
inline rvd<float32_t,1> max(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_max_float32_m1(r0, r1);
}
inline rvd<float32_t,2> max(const rvd<float32_t,2> r0, const rvd<float32_t,2> r1) {
	return mipp_max_float32_m2(r0, r1);
}
inline rvd<float32_t,4> max(const rvd<float32_t,4> r0, const rvd<float32_t,4> r1) {
	return mipp_max_float32_m4(r0, r1);
}
inline rvd<float32_t,8> max(const rvd<float32_t,8> r0, const rvd<float32_t,8> r1) {
	return mipp_max_float32_m8(r0, r1);
}
inline rvd<int64_t,1> max(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_max_int64_m1(r0, r1);
}
inline rvd<int64_t,2> max(const rvd<int64_t,2> r0, const rvd<int64_t,2> r1) {
	return mipp_max_int64_m2(r0, r1);
}
inline rvd<int64_t,4> max(const rvd<int64_t,4> r0, const rvd<int64_t,4> r1) {
	return mipp_max_int64_m4(r0, r1);
}
inline rvd<int64_t,8> max(const rvd<int64_t,8> r0, const rvd<int64_t,8> r1) {
	return mipp_max_int64_m8(r0, r1);
}
inline rvd<int32_t,1> max(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_max_int32_m1(r0, r1);
}
inline rvd<int32_t,2> max(const rvd<int32_t,2> r0, const rvd<int32_t,2> r1) {
	return mipp_max_int32_m2(r0, r1);
}
inline rvd<int32_t,4> max(const rvd<int32_t,4> r0, const rvd<int32_t,4> r1) {
	return mipp_max_int32_m4(r0, r1);
}
inline rvd<int32_t,8> max(const rvd<int32_t,8> r0, const rvd<int32_t,8> r1) {
	return mipp_max_int32_m8(r0, r1);
}
inline rvd<int16_t,1> max(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_max_int16_m1(r0, r1);
}
inline rvd<int16_t,2> max(const rvd<int16_t,2> r0, const rvd<int16_t,2> r1) {
	return mipp_max_int16_m2(r0, r1);
}
inline rvd<int16_t,4> max(const rvd<int16_t,4> r0, const rvd<int16_t,4> r1) {
	return mipp_max_int16_m4(r0, r1);
}
inline rvd<int16_t,8> max(const rvd<int16_t,8> r0, const rvd<int16_t,8> r1) {
	return mipp_max_int16_m8(r0, r1);
}
inline rvd<int8_t,1> max(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_max_int8_m1(r0, r1);
}
inline rvd<int8_t,2> max(const rvd<int8_t,2> r0, const rvd<int8_t,2> r1) {
	return mipp_max_int8_m2(r0, r1);
}
inline rvd<int8_t,4> max(const rvd<int8_t,4> r0, const rvd<int8_t,4> r1) {
	return mipp_max_int8_m4(r0, r1);
}
inline rvd<int8_t,8> max(const rvd<int8_t,8> r0, const rvd<int8_t,8> r1) {
	return mipp_max_int8_m8(r0, r1);
}
inline rvd<uint64_t,1> max(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_max_uint64_m1(r0, r1);
}
inline rvd<uint64_t,2> max(const rvd<uint64_t,2> r0, const rvd<uint64_t,2> r1) {
	return mipp_max_uint64_m2(r0, r1);
}
inline rvd<uint64_t,4> max(const rvd<uint64_t,4> r0, const rvd<uint64_t,4> r1) {
	return mipp_max_uint64_m4(r0, r1);
}
inline rvd<uint64_t,8> max(const rvd<uint64_t,8> r0, const rvd<uint64_t,8> r1) {
	return mipp_max_uint64_m8(r0, r1);
}
inline rvd<uint32_t,1> max(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_max_uint32_m1(r0, r1);
}
inline rvd<uint32_t,2> max(const rvd<uint32_t,2> r0, const rvd<uint32_t,2> r1) {
	return mipp_max_uint32_m2(r0, r1);
}
inline rvd<uint32_t,4> max(const rvd<uint32_t,4> r0, const rvd<uint32_t,4> r1) {
	return mipp_max_uint32_m4(r0, r1);
}
inline rvd<uint32_t,8> max(const rvd<uint32_t,8> r0, const rvd<uint32_t,8> r1) {
	return mipp_max_uint32_m8(r0, r1);
}
inline rvd<uint16_t,1> max(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_max_uint16_m1(r0, r1);
}
inline rvd<uint16_t,2> max(const rvd<uint16_t,2> r0, const rvd<uint16_t,2> r1) {
	return mipp_max_uint16_m2(r0, r1);
}
inline rvd<uint16_t,4> max(const rvd<uint16_t,4> r0, const rvd<uint16_t,4> r1) {
	return mipp_max_uint16_m4(r0, r1);
}
inline rvd<uint16_t,8> max(const rvd<uint16_t,8> r0, const rvd<uint16_t,8> r1) {
	return mipp_max_uint16_m8(r0, r1);
}
inline rvd<uint8_t,1> max(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_max_uint8_m1(r0, r1);
}
inline rvd<uint8_t,2> max(const rvd<uint8_t,2> r0, const rvd<uint8_t,2> r1) {
	return mipp_max_uint8_m2(r0, r1);
}
inline rvd<uint8_t,4> max(const rvd<uint8_t,4> r0, const rvd<uint8_t,4> r1) {
	return mipp_max_uint8_m4(r0, r1);
}
inline rvd<uint8_t,8> max(const rvd<uint8_t,8> r0, const rvd<uint8_t,8> r1) {
	return mipp_max_uint8_m8(r0, r1);
}
inline rvd<float64_t,1> fmadd(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1, const rvd<float64_t,1> r2) {
	return mipp_fmadd_float64_m1(r0, r1, r2);
}
inline rvd<float64_t,2> fmadd(const rvd<float64_t,2> r0, const rvd<float64_t,2> r1, const rvd<float64_t,2> r2) {
	return mipp_fmadd_float64_m2(r0, r1, r2);
}
inline rvd<float64_t,4> fmadd(const rvd<float64_t,4> r0, const rvd<float64_t,4> r1, const rvd<float64_t,4> r2) {
	return mipp_fmadd_float64_m4(r0, r1, r2);
}
inline rvd<float64_t,8> fmadd(const rvd<float64_t,8> r0, const rvd<float64_t,8> r1, const rvd<float64_t,8> r2) {
	return mipp_fmadd_float64_m8(r0, r1, r2);
}
inline rvd<float32_t,1> fmadd(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1, const rvd<float32_t,1> r2) {
	return mipp_fmadd_float32_m1(r0, r1, r2);
}
inline rvd<float32_t,2> fmadd(const rvd<float32_t,2> r0, const rvd<float32_t,2> r1, const rvd<float32_t,2> r2) {
	return mipp_fmadd_float32_m2(r0, r1, r2);
}
inline rvd<float32_t,4> fmadd(const rvd<float32_t,4> r0, const rvd<float32_t,4> r1, const rvd<float32_t,4> r2) {
	return mipp_fmadd_float32_m4(r0, r1, r2);
}
inline rvd<float32_t,8> fmadd(const rvd<float32_t,8> r0, const rvd<float32_t,8> r1, const rvd<float32_t,8> r2) {
	return mipp_fmadd_float32_m8(r0, r1, r2);
}
inline rvd<int32_t,1> fmadd(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1, const rvd<int32_t,1> r2) {
	return mipp_fmadd_int32_m1(r0, r1, r2);
}
inline rvd<int32_t,2> fmadd(const rvd<int32_t,2> r0, const rvd<int32_t,2> r1, const rvd<int32_t,2> r2) {
	return mipp_fmadd_int32_m2(r0, r1, r2);
}
inline rvd<int32_t,4> fmadd(const rvd<int32_t,4> r0, const rvd<int32_t,4> r1, const rvd<int32_t,4> r2) {
	return mipp_fmadd_int32_m4(r0, r1, r2);
}
inline rvd<int32_t,8> fmadd(const rvd<int32_t,8> r0, const rvd<int32_t,8> r1, const rvd<int32_t,8> r2) {
	return mipp_fmadd_int32_m8(r0, r1, r2);
}
inline rvd<float64_t,1> fmsub(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1, const rvd<float64_t,1> r2) {
	return mipp_fmsub_float64_m1(r0, r1, r2);
}
inline rvd<float64_t,2> fmsub(const rvd<float64_t,2> r0, const rvd<float64_t,2> r1, const rvd<float64_t,2> r2) {
	return mipp_fmsub_float64_m2(r0, r1, r2);
}
inline rvd<float64_t,4> fmsub(const rvd<float64_t,4> r0, const rvd<float64_t,4> r1, const rvd<float64_t,4> r2) {
	return mipp_fmsub_float64_m4(r0, r1, r2);
}
inline rvd<float64_t,8> fmsub(const rvd<float64_t,8> r0, const rvd<float64_t,8> r1, const rvd<float64_t,8> r2) {
	return mipp_fmsub_float64_m8(r0, r1, r2);
}
inline rvd<float32_t,1> fmsub(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1, const rvd<float32_t,1> r2) {
	return mipp_fmsub_float32_m1(r0, r1, r2);
}
inline rvd<float32_t,2> fmsub(const rvd<float32_t,2> r0, const rvd<float32_t,2> r1, const rvd<float32_t,2> r2) {
	return mipp_fmsub_float32_m2(r0, r1, r2);
}
inline rvd<float32_t,4> fmsub(const rvd<float32_t,4> r0, const rvd<float32_t,4> r1, const rvd<float32_t,4> r2) {
	return mipp_fmsub_float32_m4(r0, r1, r2);
}
inline rvd<float32_t,8> fmsub(const rvd<float32_t,8> r0, const rvd<float32_t,8> r1, const rvd<float32_t,8> r2) {
	return mipp_fmsub_float32_m8(r0, r1, r2);
}
inline rvd<int32_t,1> fmsub(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1, const rvd<int32_t,1> r2) {
	return mipp_fmsub_int32_m1(r0, r1, r2);
}
inline rvd<int32_t,2> fmsub(const rvd<int32_t,2> r0, const rvd<int32_t,2> r1, const rvd<int32_t,2> r2) {
	return mipp_fmsub_int32_m2(r0, r1, r2);
}
inline rvd<int32_t,4> fmsub(const rvd<int32_t,4> r0, const rvd<int32_t,4> r1, const rvd<int32_t,4> r2) {
	return mipp_fmsub_int32_m4(r0, r1, r2);
}
inline rvd<int32_t,8> fmsub(const rvd<int32_t,8> r0, const rvd<int32_t,8> r1, const rvd<int32_t,8> r2) {
	return mipp_fmsub_int32_m8(r0, r1, r2);
}
inline rvd<float64_t,1> andb(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_andb_float64_m1(r0, r1);
}
inline rvd<float64_t,2> andb(const rvd<float64_t,2> r0, const rvd<float64_t,2> r1) {
	return mipp_andb_float64_m2(r0, r1);
}
inline rvd<float64_t,4> andb(const rvd<float64_t,4> r0, const rvd<float64_t,4> r1) {
	return mipp_andb_float64_m4(r0, r1);
}
inline rvd<float64_t,8> andb(const rvd<float64_t,8> r0, const rvd<float64_t,8> r1) {
	return mipp_andb_float64_m8(r0, r1);
}
inline rvd<float32_t,1> andb(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_andb_float32_m1(r0, r1);
}
inline rvd<float32_t,2> andb(const rvd<float32_t,2> r0, const rvd<float32_t,2> r1) {
	return mipp_andb_float32_m2(r0, r1);
}
inline rvd<float32_t,4> andb(const rvd<float32_t,4> r0, const rvd<float32_t,4> r1) {
	return mipp_andb_float32_m4(r0, r1);
}
inline rvd<float32_t,8> andb(const rvd<float32_t,8> r0, const rvd<float32_t,8> r1) {
	return mipp_andb_float32_m8(r0, r1);
}
inline rvd<int64_t,1> andb(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_andb_int64_m1(r0, r1);
}
inline rvd<int64_t,2> andb(const rvd<int64_t,2> r0, const rvd<int64_t,2> r1) {
	return mipp_andb_int64_m2(r0, r1);
}
inline rvd<int64_t,4> andb(const rvd<int64_t,4> r0, const rvd<int64_t,4> r1) {
	return mipp_andb_int64_m4(r0, r1);
}
inline rvd<int64_t,8> andb(const rvd<int64_t,8> r0, const rvd<int64_t,8> r1) {
	return mipp_andb_int64_m8(r0, r1);
}
inline rvd<int32_t,1> andb(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_andb_int32_m1(r0, r1);
}
inline rvd<int32_t,2> andb(const rvd<int32_t,2> r0, const rvd<int32_t,2> r1) {
	return mipp_andb_int32_m2(r0, r1);
}
inline rvd<int32_t,4> andb(const rvd<int32_t,4> r0, const rvd<int32_t,4> r1) {
	return mipp_andb_int32_m4(r0, r1);
}
inline rvd<int32_t,8> andb(const rvd<int32_t,8> r0, const rvd<int32_t,8> r1) {
	return mipp_andb_int32_m8(r0, r1);
}
inline rvd<int16_t,1> andb(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_andb_int16_m1(r0, r1);
}
inline rvd<int16_t,2> andb(const rvd<int16_t,2> r0, const rvd<int16_t,2> r1) {
	return mipp_andb_int16_m2(r0, r1);
}
inline rvd<int16_t,4> andb(const rvd<int16_t,4> r0, const rvd<int16_t,4> r1) {
	return mipp_andb_int16_m4(r0, r1);
}
inline rvd<int16_t,8> andb(const rvd<int16_t,8> r0, const rvd<int16_t,8> r1) {
	return mipp_andb_int16_m8(r0, r1);
}
inline rvd<int8_t,1> andb(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_andb_int8_m1(r0, r1);
}
inline rvd<int8_t,2> andb(const rvd<int8_t,2> r0, const rvd<int8_t,2> r1) {
	return mipp_andb_int8_m2(r0, r1);
}
inline rvd<int8_t,4> andb(const rvd<int8_t,4> r0, const rvd<int8_t,4> r1) {
	return mipp_andb_int8_m4(r0, r1);
}
inline rvd<int8_t,8> andb(const rvd<int8_t,8> r0, const rvd<int8_t,8> r1) {
	return mipp_andb_int8_m8(r0, r1);
}
inline rvd<uint64_t,1> andb(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_andb_uint64_m1(r0, r1);
}
inline rvd<uint64_t,2> andb(const rvd<uint64_t,2> r0, const rvd<uint64_t,2> r1) {
	return mipp_andb_uint64_m2(r0, r1);
}
inline rvd<uint64_t,4> andb(const rvd<uint64_t,4> r0, const rvd<uint64_t,4> r1) {
	return mipp_andb_uint64_m4(r0, r1);
}
inline rvd<uint64_t,8> andb(const rvd<uint64_t,8> r0, const rvd<uint64_t,8> r1) {
	return mipp_andb_uint64_m8(r0, r1);
}
inline rvd<uint32_t,1> andb(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_andb_uint32_m1(r0, r1);
}
inline rvd<uint32_t,2> andb(const rvd<uint32_t,2> r0, const rvd<uint32_t,2> r1) {
	return mipp_andb_uint32_m2(r0, r1);
}
inline rvd<uint32_t,4> andb(const rvd<uint32_t,4> r0, const rvd<uint32_t,4> r1) {
	return mipp_andb_uint32_m4(r0, r1);
}
inline rvd<uint32_t,8> andb(const rvd<uint32_t,8> r0, const rvd<uint32_t,8> r1) {
	return mipp_andb_uint32_m8(r0, r1);
}
inline rvd<uint16_t,1> andb(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_andb_uint16_m1(r0, r1);
}
inline rvd<uint16_t,2> andb(const rvd<uint16_t,2> r0, const rvd<uint16_t,2> r1) {
	return mipp_andb_uint16_m2(r0, r1);
}
inline rvd<uint16_t,4> andb(const rvd<uint16_t,4> r0, const rvd<uint16_t,4> r1) {
	return mipp_andb_uint16_m4(r0, r1);
}
inline rvd<uint16_t,8> andb(const rvd<uint16_t,8> r0, const rvd<uint16_t,8> r1) {
	return mipp_andb_uint16_m8(r0, r1);
}
inline rvd<uint8_t,1> andb(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_andb_uint8_m1(r0, r1);
}
inline rvd<uint8_t,2> andb(const rvd<uint8_t,2> r0, const rvd<uint8_t,2> r1) {
	return mipp_andb_uint8_m2(r0, r1);
}
inline rvd<uint8_t,4> andb(const rvd<uint8_t,4> r0, const rvd<uint8_t,4> r1) {
	return mipp_andb_uint8_m4(r0, r1);
}
inline rvd<uint8_t,8> andb(const rvd<uint8_t,8> r0, const rvd<uint8_t,8> r1) {
	return mipp_andb_uint8_m8(r0, r1);
}
inline rvm<float64_t,1> andb(const rvm<float64_t,1> m0, const rvm<float64_t,1> m1) {
	return mipp_andb_k_float64_m1(m0, m1);
}
inline rvm<float64_t,2> andb(const rvm<float64_t,2> m0, const rvm<float64_t,2> m1) {
	return mipp_andb_k_float64_m2(m0, m1);
}
inline rvm<float64_t,4> andb(const rvm<float64_t,4> m0, const rvm<float64_t,4> m1) {
	return mipp_andb_k_float64_m4(m0, m1);
}
inline rvm<float64_t,8> andb(const rvm<float64_t,8> m0, const rvm<float64_t,8> m1) {
	return mipp_andb_k_float64_m8(m0, m1);
}
inline rvm<float32_t,1> andb(const rvm<float32_t,1> m0, const rvm<float32_t,1> m1) {
	return mipp_andb_k_float32_m1(m0, m1);
}
inline rvm<float32_t,2> andb(const rvm<float32_t,2> m0, const rvm<float32_t,2> m1) {
	return mipp_andb_k_float32_m2(m0, m1);
}
inline rvm<float32_t,4> andb(const rvm<float32_t,4> m0, const rvm<float32_t,4> m1) {
	return mipp_andb_k_float32_m4(m0, m1);
}
inline rvm<float32_t,8> andb(const rvm<float32_t,8> m0, const rvm<float32_t,8> m1) {
	return mipp_andb_k_float32_m8(m0, m1);
}
inline rvm<int64_t,1> andb(const rvm<int64_t,1> m0, const rvm<int64_t,1> m1) {
	return mipp_andb_k_int64_m1(m0, m1);
}
inline rvm<int64_t,2> andb(const rvm<int64_t,2> m0, const rvm<int64_t,2> m1) {
	return mipp_andb_k_int64_m2(m0, m1);
}
inline rvm<int64_t,4> andb(const rvm<int64_t,4> m0, const rvm<int64_t,4> m1) {
	return mipp_andb_k_int64_m4(m0, m1);
}
inline rvm<int64_t,8> andb(const rvm<int64_t,8> m0, const rvm<int64_t,8> m1) {
	return mipp_andb_k_int64_m8(m0, m1);
}
inline rvm<int32_t,1> andb(const rvm<int32_t,1> m0, const rvm<int32_t,1> m1) {
	return mipp_andb_k_int32_m1(m0, m1);
}
inline rvm<int32_t,2> andb(const rvm<int32_t,2> m0, const rvm<int32_t,2> m1) {
	return mipp_andb_k_int32_m2(m0, m1);
}
inline rvm<int32_t,4> andb(const rvm<int32_t,4> m0, const rvm<int32_t,4> m1) {
	return mipp_andb_k_int32_m4(m0, m1);
}
inline rvm<int32_t,8> andb(const rvm<int32_t,8> m0, const rvm<int32_t,8> m1) {
	return mipp_andb_k_int32_m8(m0, m1);
}
inline rvm<int16_t,1> andb(const rvm<int16_t,1> m0, const rvm<int16_t,1> m1) {
	return mipp_andb_k_int16_m1(m0, m1);
}
inline rvm<int16_t,2> andb(const rvm<int16_t,2> m0, const rvm<int16_t,2> m1) {
	return mipp_andb_k_int16_m2(m0, m1);
}
inline rvm<int16_t,4> andb(const rvm<int16_t,4> m0, const rvm<int16_t,4> m1) {
	return mipp_andb_k_int16_m4(m0, m1);
}
inline rvm<int16_t,8> andb(const rvm<int16_t,8> m0, const rvm<int16_t,8> m1) {
	return mipp_andb_k_int16_m8(m0, m1);
}
inline rvm<int8_t,1> andb(const rvm<int8_t,1> m0, const rvm<int8_t,1> m1) {
	return mipp_andb_k_int8_m1(m0, m1);
}
inline rvm<int8_t,2> andb(const rvm<int8_t,2> m0, const rvm<int8_t,2> m1) {
	return mipp_andb_k_int8_m2(m0, m1);
}
inline rvm<int8_t,4> andb(const rvm<int8_t,4> m0, const rvm<int8_t,4> m1) {
	return mipp_andb_k_int8_m4(m0, m1);
}
inline rvm<int8_t,8> andb(const rvm<int8_t,8> m0, const rvm<int8_t,8> m1) {
	return mipp_andb_k_int8_m8(m0, m1);
}
inline rvm<uint64_t,1> andb(const rvm<uint64_t,1> m0, const rvm<uint64_t,1> m1) {
	return mipp_andb_k_uint64_m1(m0, m1);
}
inline rvm<uint64_t,2> andb(const rvm<uint64_t,2> m0, const rvm<uint64_t,2> m1) {
	return mipp_andb_k_uint64_m2(m0, m1);
}
inline rvm<uint64_t,4> andb(const rvm<uint64_t,4> m0, const rvm<uint64_t,4> m1) {
	return mipp_andb_k_uint64_m4(m0, m1);
}
inline rvm<uint64_t,8> andb(const rvm<uint64_t,8> m0, const rvm<uint64_t,8> m1) {
	return mipp_andb_k_uint64_m8(m0, m1);
}
inline rvm<uint32_t,1> andb(const rvm<uint32_t,1> m0, const rvm<uint32_t,1> m1) {
	return mipp_andb_k_uint32_m1(m0, m1);
}
inline rvm<uint32_t,2> andb(const rvm<uint32_t,2> m0, const rvm<uint32_t,2> m1) {
	return mipp_andb_k_uint32_m2(m0, m1);
}
inline rvm<uint32_t,4> andb(const rvm<uint32_t,4> m0, const rvm<uint32_t,4> m1) {
	return mipp_andb_k_uint32_m4(m0, m1);
}
inline rvm<uint32_t,8> andb(const rvm<uint32_t,8> m0, const rvm<uint32_t,8> m1) {
	return mipp_andb_k_uint32_m8(m0, m1);
}
inline rvm<uint16_t,1> andb(const rvm<uint16_t,1> m0, const rvm<uint16_t,1> m1) {
	return mipp_andb_k_uint16_m1(m0, m1);
}
inline rvm<uint16_t,2> andb(const rvm<uint16_t,2> m0, const rvm<uint16_t,2> m1) {
	return mipp_andb_k_uint16_m2(m0, m1);
}
inline rvm<uint16_t,4> andb(const rvm<uint16_t,4> m0, const rvm<uint16_t,4> m1) {
	return mipp_andb_k_uint16_m4(m0, m1);
}
inline rvm<uint16_t,8> andb(const rvm<uint16_t,8> m0, const rvm<uint16_t,8> m1) {
	return mipp_andb_k_uint16_m8(m0, m1);
}
inline rvm<uint8_t,1> andb(const rvm<uint8_t,1> m0, const rvm<uint8_t,1> m1) {
	return mipp_andb_k_uint8_m1(m0, m1);
}
inline rvm<uint8_t,2> andb(const rvm<uint8_t,2> m0, const rvm<uint8_t,2> m1) {
	return mipp_andb_k_uint8_m2(m0, m1);
}
inline rvm<uint8_t,4> andb(const rvm<uint8_t,4> m0, const rvm<uint8_t,4> m1) {
	return mipp_andb_k_uint8_m4(m0, m1);
}
inline rvm<uint8_t,8> andb(const rvm<uint8_t,8> m0, const rvm<uint8_t,8> m1) {
	return mipp_andb_k_uint8_m8(m0, m1);
}
inline rvd<float64_t,1> andnb(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_andnb_float64_m1(r0, r1);
}
inline rvd<float64_t,2> andnb(const rvd<float64_t,2> r0, const rvd<float64_t,2> r1) {
	return mipp_andnb_float64_m2(r0, r1);
}
inline rvd<float64_t,4> andnb(const rvd<float64_t,4> r0, const rvd<float64_t,4> r1) {
	return mipp_andnb_float64_m4(r0, r1);
}
inline rvd<float64_t,8> andnb(const rvd<float64_t,8> r0, const rvd<float64_t,8> r1) {
	return mipp_andnb_float64_m8(r0, r1);
}
inline rvd<float32_t,1> andnb(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_andnb_float32_m1(r0, r1);
}
inline rvd<float32_t,2> andnb(const rvd<float32_t,2> r0, const rvd<float32_t,2> r1) {
	return mipp_andnb_float32_m2(r0, r1);
}
inline rvd<float32_t,4> andnb(const rvd<float32_t,4> r0, const rvd<float32_t,4> r1) {
	return mipp_andnb_float32_m4(r0, r1);
}
inline rvd<float32_t,8> andnb(const rvd<float32_t,8> r0, const rvd<float32_t,8> r1) {
	return mipp_andnb_float32_m8(r0, r1);
}
inline rvd<int64_t,1> andnb(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_andnb_int64_m1(r0, r1);
}
inline rvd<int64_t,2> andnb(const rvd<int64_t,2> r0, const rvd<int64_t,2> r1) {
	return mipp_andnb_int64_m2(r0, r1);
}
inline rvd<int64_t,4> andnb(const rvd<int64_t,4> r0, const rvd<int64_t,4> r1) {
	return mipp_andnb_int64_m4(r0, r1);
}
inline rvd<int64_t,8> andnb(const rvd<int64_t,8> r0, const rvd<int64_t,8> r1) {
	return mipp_andnb_int64_m8(r0, r1);
}
inline rvd<int32_t,1> andnb(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_andnb_int32_m1(r0, r1);
}
inline rvd<int32_t,2> andnb(const rvd<int32_t,2> r0, const rvd<int32_t,2> r1) {
	return mipp_andnb_int32_m2(r0, r1);
}
inline rvd<int32_t,4> andnb(const rvd<int32_t,4> r0, const rvd<int32_t,4> r1) {
	return mipp_andnb_int32_m4(r0, r1);
}
inline rvd<int32_t,8> andnb(const rvd<int32_t,8> r0, const rvd<int32_t,8> r1) {
	return mipp_andnb_int32_m8(r0, r1);
}
inline rvd<int16_t,1> andnb(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_andnb_int16_m1(r0, r1);
}
inline rvd<int16_t,2> andnb(const rvd<int16_t,2> r0, const rvd<int16_t,2> r1) {
	return mipp_andnb_int16_m2(r0, r1);
}
inline rvd<int16_t,4> andnb(const rvd<int16_t,4> r0, const rvd<int16_t,4> r1) {
	return mipp_andnb_int16_m4(r0, r1);
}
inline rvd<int16_t,8> andnb(const rvd<int16_t,8> r0, const rvd<int16_t,8> r1) {
	return mipp_andnb_int16_m8(r0, r1);
}
inline rvd<int8_t,1> andnb(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_andnb_int8_m1(r0, r1);
}
inline rvd<int8_t,2> andnb(const rvd<int8_t,2> r0, const rvd<int8_t,2> r1) {
	return mipp_andnb_int8_m2(r0, r1);
}
inline rvd<int8_t,4> andnb(const rvd<int8_t,4> r0, const rvd<int8_t,4> r1) {
	return mipp_andnb_int8_m4(r0, r1);
}
inline rvd<int8_t,8> andnb(const rvd<int8_t,8> r0, const rvd<int8_t,8> r1) {
	return mipp_andnb_int8_m8(r0, r1);
}
inline rvd<uint64_t,1> andnb(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_andnb_uint64_m1(r0, r1);
}
inline rvd<uint64_t,2> andnb(const rvd<uint64_t,2> r0, const rvd<uint64_t,2> r1) {
	return mipp_andnb_uint64_m2(r0, r1);
}
inline rvd<uint64_t,4> andnb(const rvd<uint64_t,4> r0, const rvd<uint64_t,4> r1) {
	return mipp_andnb_uint64_m4(r0, r1);
}
inline rvd<uint64_t,8> andnb(const rvd<uint64_t,8> r0, const rvd<uint64_t,8> r1) {
	return mipp_andnb_uint64_m8(r0, r1);
}
inline rvd<uint32_t,1> andnb(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_andnb_uint32_m1(r0, r1);
}
inline rvd<uint32_t,2> andnb(const rvd<uint32_t,2> r0, const rvd<uint32_t,2> r1) {
	return mipp_andnb_uint32_m2(r0, r1);
}
inline rvd<uint32_t,4> andnb(const rvd<uint32_t,4> r0, const rvd<uint32_t,4> r1) {
	return mipp_andnb_uint32_m4(r0, r1);
}
inline rvd<uint32_t,8> andnb(const rvd<uint32_t,8> r0, const rvd<uint32_t,8> r1) {
	return mipp_andnb_uint32_m8(r0, r1);
}
inline rvd<uint16_t,1> andnb(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_andnb_uint16_m1(r0, r1);
}
inline rvd<uint16_t,2> andnb(const rvd<uint16_t,2> r0, const rvd<uint16_t,2> r1) {
	return mipp_andnb_uint16_m2(r0, r1);
}
inline rvd<uint16_t,4> andnb(const rvd<uint16_t,4> r0, const rvd<uint16_t,4> r1) {
	return mipp_andnb_uint16_m4(r0, r1);
}
inline rvd<uint16_t,8> andnb(const rvd<uint16_t,8> r0, const rvd<uint16_t,8> r1) {
	return mipp_andnb_uint16_m8(r0, r1);
}
inline rvd<uint8_t,1> andnb(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_andnb_uint8_m1(r0, r1);
}
inline rvd<uint8_t,2> andnb(const rvd<uint8_t,2> r0, const rvd<uint8_t,2> r1) {
	return mipp_andnb_uint8_m2(r0, r1);
}
inline rvd<uint8_t,4> andnb(const rvd<uint8_t,4> r0, const rvd<uint8_t,4> r1) {
	return mipp_andnb_uint8_m4(r0, r1);
}
inline rvd<uint8_t,8> andnb(const rvd<uint8_t,8> r0, const rvd<uint8_t,8> r1) {
	return mipp_andnb_uint8_m8(r0, r1);
}
inline rvm<float64_t,1> andnb(const rvm<float64_t,1> m0, const rvm<float64_t,1> m1) {
	return mipp_andnb_k_float64_m1(m0, m1);
}
inline rvm<float64_t,2> andnb(const rvm<float64_t,2> m0, const rvm<float64_t,2> m1) {
	return mipp_andnb_k_float64_m2(m0, m1);
}
inline rvm<float64_t,4> andnb(const rvm<float64_t,4> m0, const rvm<float64_t,4> m1) {
	return mipp_andnb_k_float64_m4(m0, m1);
}
inline rvm<float64_t,8> andnb(const rvm<float64_t,8> m0, const rvm<float64_t,8> m1) {
	return mipp_andnb_k_float64_m8(m0, m1);
}
inline rvm<float32_t,1> andnb(const rvm<float32_t,1> m0, const rvm<float32_t,1> m1) {
	return mipp_andnb_k_float32_m1(m0, m1);
}
inline rvm<float32_t,2> andnb(const rvm<float32_t,2> m0, const rvm<float32_t,2> m1) {
	return mipp_andnb_k_float32_m2(m0, m1);
}
inline rvm<float32_t,4> andnb(const rvm<float32_t,4> m0, const rvm<float32_t,4> m1) {
	return mipp_andnb_k_float32_m4(m0, m1);
}
inline rvm<float32_t,8> andnb(const rvm<float32_t,8> m0, const rvm<float32_t,8> m1) {
	return mipp_andnb_k_float32_m8(m0, m1);
}
inline rvm<int64_t,1> andnb(const rvm<int64_t,1> m0, const rvm<int64_t,1> m1) {
	return mipp_andnb_k_int64_m1(m0, m1);
}
inline rvm<int64_t,2> andnb(const rvm<int64_t,2> m0, const rvm<int64_t,2> m1) {
	return mipp_andnb_k_int64_m2(m0, m1);
}
inline rvm<int64_t,4> andnb(const rvm<int64_t,4> m0, const rvm<int64_t,4> m1) {
	return mipp_andnb_k_int64_m4(m0, m1);
}
inline rvm<int64_t,8> andnb(const rvm<int64_t,8> m0, const rvm<int64_t,8> m1) {
	return mipp_andnb_k_int64_m8(m0, m1);
}
inline rvm<int32_t,1> andnb(const rvm<int32_t,1> m0, const rvm<int32_t,1> m1) {
	return mipp_andnb_k_int32_m1(m0, m1);
}
inline rvm<int32_t,2> andnb(const rvm<int32_t,2> m0, const rvm<int32_t,2> m1) {
	return mipp_andnb_k_int32_m2(m0, m1);
}
inline rvm<int32_t,4> andnb(const rvm<int32_t,4> m0, const rvm<int32_t,4> m1) {
	return mipp_andnb_k_int32_m4(m0, m1);
}
inline rvm<int32_t,8> andnb(const rvm<int32_t,8> m0, const rvm<int32_t,8> m1) {
	return mipp_andnb_k_int32_m8(m0, m1);
}
inline rvm<int16_t,1> andnb(const rvm<int16_t,1> m0, const rvm<int16_t,1> m1) {
	return mipp_andnb_k_int16_m1(m0, m1);
}
inline rvm<int16_t,2> andnb(const rvm<int16_t,2> m0, const rvm<int16_t,2> m1) {
	return mipp_andnb_k_int16_m2(m0, m1);
}
inline rvm<int16_t,4> andnb(const rvm<int16_t,4> m0, const rvm<int16_t,4> m1) {
	return mipp_andnb_k_int16_m4(m0, m1);
}
inline rvm<int16_t,8> andnb(const rvm<int16_t,8> m0, const rvm<int16_t,8> m1) {
	return mipp_andnb_k_int16_m8(m0, m1);
}
inline rvm<int8_t,1> andnb(const rvm<int8_t,1> m0, const rvm<int8_t,1> m1) {
	return mipp_andnb_k_int8_m1(m0, m1);
}
inline rvm<int8_t,2> andnb(const rvm<int8_t,2> m0, const rvm<int8_t,2> m1) {
	return mipp_andnb_k_int8_m2(m0, m1);
}
inline rvm<int8_t,4> andnb(const rvm<int8_t,4> m0, const rvm<int8_t,4> m1) {
	return mipp_andnb_k_int8_m4(m0, m1);
}
inline rvm<int8_t,8> andnb(const rvm<int8_t,8> m0, const rvm<int8_t,8> m1) {
	return mipp_andnb_k_int8_m8(m0, m1);
}
inline rvm<uint64_t,1> andnb(const rvm<uint64_t,1> m0, const rvm<uint64_t,1> m1) {
	return mipp_andnb_k_uint64_m1(m0, m1);
}
inline rvm<uint64_t,2> andnb(const rvm<uint64_t,2> m0, const rvm<uint64_t,2> m1) {
	return mipp_andnb_k_uint64_m2(m0, m1);
}
inline rvm<uint64_t,4> andnb(const rvm<uint64_t,4> m0, const rvm<uint64_t,4> m1) {
	return mipp_andnb_k_uint64_m4(m0, m1);
}
inline rvm<uint64_t,8> andnb(const rvm<uint64_t,8> m0, const rvm<uint64_t,8> m1) {
	return mipp_andnb_k_uint64_m8(m0, m1);
}
inline rvm<uint32_t,1> andnb(const rvm<uint32_t,1> m0, const rvm<uint32_t,1> m1) {
	return mipp_andnb_k_uint32_m1(m0, m1);
}
inline rvm<uint32_t,2> andnb(const rvm<uint32_t,2> m0, const rvm<uint32_t,2> m1) {
	return mipp_andnb_k_uint32_m2(m0, m1);
}
inline rvm<uint32_t,4> andnb(const rvm<uint32_t,4> m0, const rvm<uint32_t,4> m1) {
	return mipp_andnb_k_uint32_m4(m0, m1);
}
inline rvm<uint32_t,8> andnb(const rvm<uint32_t,8> m0, const rvm<uint32_t,8> m1) {
	return mipp_andnb_k_uint32_m8(m0, m1);
}
inline rvm<uint16_t,1> andnb(const rvm<uint16_t,1> m0, const rvm<uint16_t,1> m1) {
	return mipp_andnb_k_uint16_m1(m0, m1);
}
inline rvm<uint16_t,2> andnb(const rvm<uint16_t,2> m0, const rvm<uint16_t,2> m1) {
	return mipp_andnb_k_uint16_m2(m0, m1);
}
inline rvm<uint16_t,4> andnb(const rvm<uint16_t,4> m0, const rvm<uint16_t,4> m1) {
	return mipp_andnb_k_uint16_m4(m0, m1);
}
inline rvm<uint16_t,8> andnb(const rvm<uint16_t,8> m0, const rvm<uint16_t,8> m1) {
	return mipp_andnb_k_uint16_m8(m0, m1);
}
inline rvm<uint8_t,1> andnb(const rvm<uint8_t,1> m0, const rvm<uint8_t,1> m1) {
	return mipp_andnb_k_uint8_m1(m0, m1);
}
inline rvm<uint8_t,2> andnb(const rvm<uint8_t,2> m0, const rvm<uint8_t,2> m1) {
	return mipp_andnb_k_uint8_m2(m0, m1);
}
inline rvm<uint8_t,4> andnb(const rvm<uint8_t,4> m0, const rvm<uint8_t,4> m1) {
	return mipp_andnb_k_uint8_m4(m0, m1);
}
inline rvm<uint8_t,8> andnb(const rvm<uint8_t,8> m0, const rvm<uint8_t,8> m1) {
	return mipp_andnb_k_uint8_m8(m0, m1);
}
inline rvd<float64_t,1> orb(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_orb_float64_m1(r0, r1);
}
inline rvd<float64_t,2> orb(const rvd<float64_t,2> r0, const rvd<float64_t,2> r1) {
	return mipp_orb_float64_m2(r0, r1);
}
inline rvd<float64_t,4> orb(const rvd<float64_t,4> r0, const rvd<float64_t,4> r1) {
	return mipp_orb_float64_m4(r0, r1);
}
inline rvd<float64_t,8> orb(const rvd<float64_t,8> r0, const rvd<float64_t,8> r1) {
	return mipp_orb_float64_m8(r0, r1);
}
inline rvd<float32_t,1> orb(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_orb_float32_m1(r0, r1);
}
inline rvd<float32_t,2> orb(const rvd<float32_t,2> r0, const rvd<float32_t,2> r1) {
	return mipp_orb_float32_m2(r0, r1);
}
inline rvd<float32_t,4> orb(const rvd<float32_t,4> r0, const rvd<float32_t,4> r1) {
	return mipp_orb_float32_m4(r0, r1);
}
inline rvd<float32_t,8> orb(const rvd<float32_t,8> r0, const rvd<float32_t,8> r1) {
	return mipp_orb_float32_m8(r0, r1);
}
inline rvd<int64_t,1> orb(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_orb_int64_m1(r0, r1);
}
inline rvd<int64_t,2> orb(const rvd<int64_t,2> r0, const rvd<int64_t,2> r1) {
	return mipp_orb_int64_m2(r0, r1);
}
inline rvd<int64_t,4> orb(const rvd<int64_t,4> r0, const rvd<int64_t,4> r1) {
	return mipp_orb_int64_m4(r0, r1);
}
inline rvd<int64_t,8> orb(const rvd<int64_t,8> r0, const rvd<int64_t,8> r1) {
	return mipp_orb_int64_m8(r0, r1);
}
inline rvd<int32_t,1> orb(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_orb_int32_m1(r0, r1);
}
inline rvd<int32_t,2> orb(const rvd<int32_t,2> r0, const rvd<int32_t,2> r1) {
	return mipp_orb_int32_m2(r0, r1);
}
inline rvd<int32_t,4> orb(const rvd<int32_t,4> r0, const rvd<int32_t,4> r1) {
	return mipp_orb_int32_m4(r0, r1);
}
inline rvd<int32_t,8> orb(const rvd<int32_t,8> r0, const rvd<int32_t,8> r1) {
	return mipp_orb_int32_m8(r0, r1);
}
inline rvd<int16_t,1> orb(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_orb_int16_m1(r0, r1);
}
inline rvd<int16_t,2> orb(const rvd<int16_t,2> r0, const rvd<int16_t,2> r1) {
	return mipp_orb_int16_m2(r0, r1);
}
inline rvd<int16_t,4> orb(const rvd<int16_t,4> r0, const rvd<int16_t,4> r1) {
	return mipp_orb_int16_m4(r0, r1);
}
inline rvd<int16_t,8> orb(const rvd<int16_t,8> r0, const rvd<int16_t,8> r1) {
	return mipp_orb_int16_m8(r0, r1);
}
inline rvd<int8_t,1> orb(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_orb_int8_m1(r0, r1);
}
inline rvd<int8_t,2> orb(const rvd<int8_t,2> r0, const rvd<int8_t,2> r1) {
	return mipp_orb_int8_m2(r0, r1);
}
inline rvd<int8_t,4> orb(const rvd<int8_t,4> r0, const rvd<int8_t,4> r1) {
	return mipp_orb_int8_m4(r0, r1);
}
inline rvd<int8_t,8> orb(const rvd<int8_t,8> r0, const rvd<int8_t,8> r1) {
	return mipp_orb_int8_m8(r0, r1);
}
inline rvd<uint64_t,1> orb(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_orb_uint64_m1(r0, r1);
}
inline rvd<uint64_t,2> orb(const rvd<uint64_t,2> r0, const rvd<uint64_t,2> r1) {
	return mipp_orb_uint64_m2(r0, r1);
}
inline rvd<uint64_t,4> orb(const rvd<uint64_t,4> r0, const rvd<uint64_t,4> r1) {
	return mipp_orb_uint64_m4(r0, r1);
}
inline rvd<uint64_t,8> orb(const rvd<uint64_t,8> r0, const rvd<uint64_t,8> r1) {
	return mipp_orb_uint64_m8(r0, r1);
}
inline rvd<uint32_t,1> orb(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_orb_uint32_m1(r0, r1);
}
inline rvd<uint32_t,2> orb(const rvd<uint32_t,2> r0, const rvd<uint32_t,2> r1) {
	return mipp_orb_uint32_m2(r0, r1);
}
inline rvd<uint32_t,4> orb(const rvd<uint32_t,4> r0, const rvd<uint32_t,4> r1) {
	return mipp_orb_uint32_m4(r0, r1);
}
inline rvd<uint32_t,8> orb(const rvd<uint32_t,8> r0, const rvd<uint32_t,8> r1) {
	return mipp_orb_uint32_m8(r0, r1);
}
inline rvd<uint16_t,1> orb(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_orb_uint16_m1(r0, r1);
}
inline rvd<uint16_t,2> orb(const rvd<uint16_t,2> r0, const rvd<uint16_t,2> r1) {
	return mipp_orb_uint16_m2(r0, r1);
}
inline rvd<uint16_t,4> orb(const rvd<uint16_t,4> r0, const rvd<uint16_t,4> r1) {
	return mipp_orb_uint16_m4(r0, r1);
}
inline rvd<uint16_t,8> orb(const rvd<uint16_t,8> r0, const rvd<uint16_t,8> r1) {
	return mipp_orb_uint16_m8(r0, r1);
}
inline rvd<uint8_t,1> orb(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_orb_uint8_m1(r0, r1);
}
inline rvd<uint8_t,2> orb(const rvd<uint8_t,2> r0, const rvd<uint8_t,2> r1) {
	return mipp_orb_uint8_m2(r0, r1);
}
inline rvd<uint8_t,4> orb(const rvd<uint8_t,4> r0, const rvd<uint8_t,4> r1) {
	return mipp_orb_uint8_m4(r0, r1);
}
inline rvd<uint8_t,8> orb(const rvd<uint8_t,8> r0, const rvd<uint8_t,8> r1) {
	return mipp_orb_uint8_m8(r0, r1);
}
inline rvm<float64_t,1> orb(const rvm<float64_t,1> m0, const rvm<float64_t,1> m1) {
	return mipp_orb_k_float64_m1(m0, m1);
}
inline rvm<float64_t,2> orb(const rvm<float64_t,2> m0, const rvm<float64_t,2> m1) {
	return mipp_orb_k_float64_m2(m0, m1);
}
inline rvm<float64_t,4> orb(const rvm<float64_t,4> m0, const rvm<float64_t,4> m1) {
	return mipp_orb_k_float64_m4(m0, m1);
}
inline rvm<float64_t,8> orb(const rvm<float64_t,8> m0, const rvm<float64_t,8> m1) {
	return mipp_orb_k_float64_m8(m0, m1);
}
inline rvm<float32_t,1> orb(const rvm<float32_t,1> m0, const rvm<float32_t,1> m1) {
	return mipp_orb_k_float32_m1(m0, m1);
}
inline rvm<float32_t,2> orb(const rvm<float32_t,2> m0, const rvm<float32_t,2> m1) {
	return mipp_orb_k_float32_m2(m0, m1);
}
inline rvm<float32_t,4> orb(const rvm<float32_t,4> m0, const rvm<float32_t,4> m1) {
	return mipp_orb_k_float32_m4(m0, m1);
}
inline rvm<float32_t,8> orb(const rvm<float32_t,8> m0, const rvm<float32_t,8> m1) {
	return mipp_orb_k_float32_m8(m0, m1);
}
inline rvm<int64_t,1> orb(const rvm<int64_t,1> m0, const rvm<int64_t,1> m1) {
	return mipp_orb_k_int64_m1(m0, m1);
}
inline rvm<int64_t,2> orb(const rvm<int64_t,2> m0, const rvm<int64_t,2> m1) {
	return mipp_orb_k_int64_m2(m0, m1);
}
inline rvm<int64_t,4> orb(const rvm<int64_t,4> m0, const rvm<int64_t,4> m1) {
	return mipp_orb_k_int64_m4(m0, m1);
}
inline rvm<int64_t,8> orb(const rvm<int64_t,8> m0, const rvm<int64_t,8> m1) {
	return mipp_orb_k_int64_m8(m0, m1);
}
inline rvm<int32_t,1> orb(const rvm<int32_t,1> m0, const rvm<int32_t,1> m1) {
	return mipp_orb_k_int32_m1(m0, m1);
}
inline rvm<int32_t,2> orb(const rvm<int32_t,2> m0, const rvm<int32_t,2> m1) {
	return mipp_orb_k_int32_m2(m0, m1);
}
inline rvm<int32_t,4> orb(const rvm<int32_t,4> m0, const rvm<int32_t,4> m1) {
	return mipp_orb_k_int32_m4(m0, m1);
}
inline rvm<int32_t,8> orb(const rvm<int32_t,8> m0, const rvm<int32_t,8> m1) {
	return mipp_orb_k_int32_m8(m0, m1);
}
inline rvm<int16_t,1> orb(const rvm<int16_t,1> m0, const rvm<int16_t,1> m1) {
	return mipp_orb_k_int16_m1(m0, m1);
}
inline rvm<int16_t,2> orb(const rvm<int16_t,2> m0, const rvm<int16_t,2> m1) {
	return mipp_orb_k_int16_m2(m0, m1);
}
inline rvm<int16_t,4> orb(const rvm<int16_t,4> m0, const rvm<int16_t,4> m1) {
	return mipp_orb_k_int16_m4(m0, m1);
}
inline rvm<int16_t,8> orb(const rvm<int16_t,8> m0, const rvm<int16_t,8> m1) {
	return mipp_orb_k_int16_m8(m0, m1);
}
inline rvm<int8_t,1> orb(const rvm<int8_t,1> m0, const rvm<int8_t,1> m1) {
	return mipp_orb_k_int8_m1(m0, m1);
}
inline rvm<int8_t,2> orb(const rvm<int8_t,2> m0, const rvm<int8_t,2> m1) {
	return mipp_orb_k_int8_m2(m0, m1);
}
inline rvm<int8_t,4> orb(const rvm<int8_t,4> m0, const rvm<int8_t,4> m1) {
	return mipp_orb_k_int8_m4(m0, m1);
}
inline rvm<int8_t,8> orb(const rvm<int8_t,8> m0, const rvm<int8_t,8> m1) {
	return mipp_orb_k_int8_m8(m0, m1);
}
inline rvm<uint64_t,1> orb(const rvm<uint64_t,1> m0, const rvm<uint64_t,1> m1) {
	return mipp_orb_k_uint64_m1(m0, m1);
}
inline rvm<uint64_t,2> orb(const rvm<uint64_t,2> m0, const rvm<uint64_t,2> m1) {
	return mipp_orb_k_uint64_m2(m0, m1);
}
inline rvm<uint64_t,4> orb(const rvm<uint64_t,4> m0, const rvm<uint64_t,4> m1) {
	return mipp_orb_k_uint64_m4(m0, m1);
}
inline rvm<uint64_t,8> orb(const rvm<uint64_t,8> m0, const rvm<uint64_t,8> m1) {
	return mipp_orb_k_uint64_m8(m0, m1);
}
inline rvm<uint32_t,1> orb(const rvm<uint32_t,1> m0, const rvm<uint32_t,1> m1) {
	return mipp_orb_k_uint32_m1(m0, m1);
}
inline rvm<uint32_t,2> orb(const rvm<uint32_t,2> m0, const rvm<uint32_t,2> m1) {
	return mipp_orb_k_uint32_m2(m0, m1);
}
inline rvm<uint32_t,4> orb(const rvm<uint32_t,4> m0, const rvm<uint32_t,4> m1) {
	return mipp_orb_k_uint32_m4(m0, m1);
}
inline rvm<uint32_t,8> orb(const rvm<uint32_t,8> m0, const rvm<uint32_t,8> m1) {
	return mipp_orb_k_uint32_m8(m0, m1);
}
inline rvm<uint16_t,1> orb(const rvm<uint16_t,1> m0, const rvm<uint16_t,1> m1) {
	return mipp_orb_k_uint16_m1(m0, m1);
}
inline rvm<uint16_t,2> orb(const rvm<uint16_t,2> m0, const rvm<uint16_t,2> m1) {
	return mipp_orb_k_uint16_m2(m0, m1);
}
inline rvm<uint16_t,4> orb(const rvm<uint16_t,4> m0, const rvm<uint16_t,4> m1) {
	return mipp_orb_k_uint16_m4(m0, m1);
}
inline rvm<uint16_t,8> orb(const rvm<uint16_t,8> m0, const rvm<uint16_t,8> m1) {
	return mipp_orb_k_uint16_m8(m0, m1);
}
inline rvm<uint8_t,1> orb(const rvm<uint8_t,1> m0, const rvm<uint8_t,1> m1) {
	return mipp_orb_k_uint8_m1(m0, m1);
}
inline rvm<uint8_t,2> orb(const rvm<uint8_t,2> m0, const rvm<uint8_t,2> m1) {
	return mipp_orb_k_uint8_m2(m0, m1);
}
inline rvm<uint8_t,4> orb(const rvm<uint8_t,4> m0, const rvm<uint8_t,4> m1) {
	return mipp_orb_k_uint8_m4(m0, m1);
}
inline rvm<uint8_t,8> orb(const rvm<uint8_t,8> m0, const rvm<uint8_t,8> m1) {
	return mipp_orb_k_uint8_m8(m0, m1);
}
inline rvd<float64_t,1> xorb(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_xorb_float64_m1(r0, r1);
}
inline rvd<float64_t,2> xorb(const rvd<float64_t,2> r0, const rvd<float64_t,2> r1) {
	return mipp_xorb_float64_m2(r0, r1);
}
inline rvd<float64_t,4> xorb(const rvd<float64_t,4> r0, const rvd<float64_t,4> r1) {
	return mipp_xorb_float64_m4(r0, r1);
}
inline rvd<float64_t,8> xorb(const rvd<float64_t,8> r0, const rvd<float64_t,8> r1) {
	return mipp_xorb_float64_m8(r0, r1);
}
inline rvd<float32_t,1> xorb(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_xorb_float32_m1(r0, r1);
}
inline rvd<float32_t,2> xorb(const rvd<float32_t,2> r0, const rvd<float32_t,2> r1) {
	return mipp_xorb_float32_m2(r0, r1);
}
inline rvd<float32_t,4> xorb(const rvd<float32_t,4> r0, const rvd<float32_t,4> r1) {
	return mipp_xorb_float32_m4(r0, r1);
}
inline rvd<float32_t,8> xorb(const rvd<float32_t,8> r0, const rvd<float32_t,8> r1) {
	return mipp_xorb_float32_m8(r0, r1);
}
inline rvd<int64_t,1> xorb(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_xorb_int64_m1(r0, r1);
}
inline rvd<int64_t,2> xorb(const rvd<int64_t,2> r0, const rvd<int64_t,2> r1) {
	return mipp_xorb_int64_m2(r0, r1);
}
inline rvd<int64_t,4> xorb(const rvd<int64_t,4> r0, const rvd<int64_t,4> r1) {
	return mipp_xorb_int64_m4(r0, r1);
}
inline rvd<int64_t,8> xorb(const rvd<int64_t,8> r0, const rvd<int64_t,8> r1) {
	return mipp_xorb_int64_m8(r0, r1);
}
inline rvd<int32_t,1> xorb(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_xorb_int32_m1(r0, r1);
}
inline rvd<int32_t,2> xorb(const rvd<int32_t,2> r0, const rvd<int32_t,2> r1) {
	return mipp_xorb_int32_m2(r0, r1);
}
inline rvd<int32_t,4> xorb(const rvd<int32_t,4> r0, const rvd<int32_t,4> r1) {
	return mipp_xorb_int32_m4(r0, r1);
}
inline rvd<int32_t,8> xorb(const rvd<int32_t,8> r0, const rvd<int32_t,8> r1) {
	return mipp_xorb_int32_m8(r0, r1);
}
inline rvd<int16_t,1> xorb(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_xorb_int16_m1(r0, r1);
}
inline rvd<int16_t,2> xorb(const rvd<int16_t,2> r0, const rvd<int16_t,2> r1) {
	return mipp_xorb_int16_m2(r0, r1);
}
inline rvd<int16_t,4> xorb(const rvd<int16_t,4> r0, const rvd<int16_t,4> r1) {
	return mipp_xorb_int16_m4(r0, r1);
}
inline rvd<int16_t,8> xorb(const rvd<int16_t,8> r0, const rvd<int16_t,8> r1) {
	return mipp_xorb_int16_m8(r0, r1);
}
inline rvd<int8_t,1> xorb(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_xorb_int8_m1(r0, r1);
}
inline rvd<int8_t,2> xorb(const rvd<int8_t,2> r0, const rvd<int8_t,2> r1) {
	return mipp_xorb_int8_m2(r0, r1);
}
inline rvd<int8_t,4> xorb(const rvd<int8_t,4> r0, const rvd<int8_t,4> r1) {
	return mipp_xorb_int8_m4(r0, r1);
}
inline rvd<int8_t,8> xorb(const rvd<int8_t,8> r0, const rvd<int8_t,8> r1) {
	return mipp_xorb_int8_m8(r0, r1);
}
inline rvd<uint64_t,1> xorb(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_xorb_uint64_m1(r0, r1);
}
inline rvd<uint64_t,2> xorb(const rvd<uint64_t,2> r0, const rvd<uint64_t,2> r1) {
	return mipp_xorb_uint64_m2(r0, r1);
}
inline rvd<uint64_t,4> xorb(const rvd<uint64_t,4> r0, const rvd<uint64_t,4> r1) {
	return mipp_xorb_uint64_m4(r0, r1);
}
inline rvd<uint64_t,8> xorb(const rvd<uint64_t,8> r0, const rvd<uint64_t,8> r1) {
	return mipp_xorb_uint64_m8(r0, r1);
}
inline rvd<uint32_t,1> xorb(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_xorb_uint32_m1(r0, r1);
}
inline rvd<uint32_t,2> xorb(const rvd<uint32_t,2> r0, const rvd<uint32_t,2> r1) {
	return mipp_xorb_uint32_m2(r0, r1);
}
inline rvd<uint32_t,4> xorb(const rvd<uint32_t,4> r0, const rvd<uint32_t,4> r1) {
	return mipp_xorb_uint32_m4(r0, r1);
}
inline rvd<uint32_t,8> xorb(const rvd<uint32_t,8> r0, const rvd<uint32_t,8> r1) {
	return mipp_xorb_uint32_m8(r0, r1);
}
inline rvd<uint16_t,1> xorb(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_xorb_uint16_m1(r0, r1);
}
inline rvd<uint16_t,2> xorb(const rvd<uint16_t,2> r0, const rvd<uint16_t,2> r1) {
	return mipp_xorb_uint16_m2(r0, r1);
}
inline rvd<uint16_t,4> xorb(const rvd<uint16_t,4> r0, const rvd<uint16_t,4> r1) {
	return mipp_xorb_uint16_m4(r0, r1);
}
inline rvd<uint16_t,8> xorb(const rvd<uint16_t,8> r0, const rvd<uint16_t,8> r1) {
	return mipp_xorb_uint16_m8(r0, r1);
}
inline rvd<uint8_t,1> xorb(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_xorb_uint8_m1(r0, r1);
}
inline rvd<uint8_t,2> xorb(const rvd<uint8_t,2> r0, const rvd<uint8_t,2> r1) {
	return mipp_xorb_uint8_m2(r0, r1);
}
inline rvd<uint8_t,4> xorb(const rvd<uint8_t,4> r0, const rvd<uint8_t,4> r1) {
	return mipp_xorb_uint8_m4(r0, r1);
}
inline rvd<uint8_t,8> xorb(const rvd<uint8_t,8> r0, const rvd<uint8_t,8> r1) {
	return mipp_xorb_uint8_m8(r0, r1);
}
inline rvm<float64_t,1> xorb(const rvm<float64_t,1> m0, const rvm<float64_t,1> m1) {
	return mipp_xorb_k_float64_m1(m0, m1);
}
inline rvm<float64_t,2> xorb(const rvm<float64_t,2> m0, const rvm<float64_t,2> m1) {
	return mipp_xorb_k_float64_m2(m0, m1);
}
inline rvm<float64_t,4> xorb(const rvm<float64_t,4> m0, const rvm<float64_t,4> m1) {
	return mipp_xorb_k_float64_m4(m0, m1);
}
inline rvm<float64_t,8> xorb(const rvm<float64_t,8> m0, const rvm<float64_t,8> m1) {
	return mipp_xorb_k_float64_m8(m0, m1);
}
inline rvm<float32_t,1> xorb(const rvm<float32_t,1> m0, const rvm<float32_t,1> m1) {
	return mipp_xorb_k_float32_m1(m0, m1);
}
inline rvm<float32_t,2> xorb(const rvm<float32_t,2> m0, const rvm<float32_t,2> m1) {
	return mipp_xorb_k_float32_m2(m0, m1);
}
inline rvm<float32_t,4> xorb(const rvm<float32_t,4> m0, const rvm<float32_t,4> m1) {
	return mipp_xorb_k_float32_m4(m0, m1);
}
inline rvm<float32_t,8> xorb(const rvm<float32_t,8> m0, const rvm<float32_t,8> m1) {
	return mipp_xorb_k_float32_m8(m0, m1);
}
inline rvm<int64_t,1> xorb(const rvm<int64_t,1> m0, const rvm<int64_t,1> m1) {
	return mipp_xorb_k_int64_m1(m0, m1);
}
inline rvm<int64_t,2> xorb(const rvm<int64_t,2> m0, const rvm<int64_t,2> m1) {
	return mipp_xorb_k_int64_m2(m0, m1);
}
inline rvm<int64_t,4> xorb(const rvm<int64_t,4> m0, const rvm<int64_t,4> m1) {
	return mipp_xorb_k_int64_m4(m0, m1);
}
inline rvm<int64_t,8> xorb(const rvm<int64_t,8> m0, const rvm<int64_t,8> m1) {
	return mipp_xorb_k_int64_m8(m0, m1);
}
inline rvm<int32_t,1> xorb(const rvm<int32_t,1> m0, const rvm<int32_t,1> m1) {
	return mipp_xorb_k_int32_m1(m0, m1);
}
inline rvm<int32_t,2> xorb(const rvm<int32_t,2> m0, const rvm<int32_t,2> m1) {
	return mipp_xorb_k_int32_m2(m0, m1);
}
inline rvm<int32_t,4> xorb(const rvm<int32_t,4> m0, const rvm<int32_t,4> m1) {
	return mipp_xorb_k_int32_m4(m0, m1);
}
inline rvm<int32_t,8> xorb(const rvm<int32_t,8> m0, const rvm<int32_t,8> m1) {
	return mipp_xorb_k_int32_m8(m0, m1);
}
inline rvm<int16_t,1> xorb(const rvm<int16_t,1> m0, const rvm<int16_t,1> m1) {
	return mipp_xorb_k_int16_m1(m0, m1);
}
inline rvm<int16_t,2> xorb(const rvm<int16_t,2> m0, const rvm<int16_t,2> m1) {
	return mipp_xorb_k_int16_m2(m0, m1);
}
inline rvm<int16_t,4> xorb(const rvm<int16_t,4> m0, const rvm<int16_t,4> m1) {
	return mipp_xorb_k_int16_m4(m0, m1);
}
inline rvm<int16_t,8> xorb(const rvm<int16_t,8> m0, const rvm<int16_t,8> m1) {
	return mipp_xorb_k_int16_m8(m0, m1);
}
inline rvm<int8_t,1> xorb(const rvm<int8_t,1> m0, const rvm<int8_t,1> m1) {
	return mipp_xorb_k_int8_m1(m0, m1);
}
inline rvm<int8_t,2> xorb(const rvm<int8_t,2> m0, const rvm<int8_t,2> m1) {
	return mipp_xorb_k_int8_m2(m0, m1);
}
inline rvm<int8_t,4> xorb(const rvm<int8_t,4> m0, const rvm<int8_t,4> m1) {
	return mipp_xorb_k_int8_m4(m0, m1);
}
inline rvm<int8_t,8> xorb(const rvm<int8_t,8> m0, const rvm<int8_t,8> m1) {
	return mipp_xorb_k_int8_m8(m0, m1);
}
inline rvm<uint64_t,1> xorb(const rvm<uint64_t,1> m0, const rvm<uint64_t,1> m1) {
	return mipp_xorb_k_uint64_m1(m0, m1);
}
inline rvm<uint64_t,2> xorb(const rvm<uint64_t,2> m0, const rvm<uint64_t,2> m1) {
	return mipp_xorb_k_uint64_m2(m0, m1);
}
inline rvm<uint64_t,4> xorb(const rvm<uint64_t,4> m0, const rvm<uint64_t,4> m1) {
	return mipp_xorb_k_uint64_m4(m0, m1);
}
inline rvm<uint64_t,8> xorb(const rvm<uint64_t,8> m0, const rvm<uint64_t,8> m1) {
	return mipp_xorb_k_uint64_m8(m0, m1);
}
inline rvm<uint32_t,1> xorb(const rvm<uint32_t,1> m0, const rvm<uint32_t,1> m1) {
	return mipp_xorb_k_uint32_m1(m0, m1);
}
inline rvm<uint32_t,2> xorb(const rvm<uint32_t,2> m0, const rvm<uint32_t,2> m1) {
	return mipp_xorb_k_uint32_m2(m0, m1);
}
inline rvm<uint32_t,4> xorb(const rvm<uint32_t,4> m0, const rvm<uint32_t,4> m1) {
	return mipp_xorb_k_uint32_m4(m0, m1);
}
inline rvm<uint32_t,8> xorb(const rvm<uint32_t,8> m0, const rvm<uint32_t,8> m1) {
	return mipp_xorb_k_uint32_m8(m0, m1);
}
inline rvm<uint16_t,1> xorb(const rvm<uint16_t,1> m0, const rvm<uint16_t,1> m1) {
	return mipp_xorb_k_uint16_m1(m0, m1);
}
inline rvm<uint16_t,2> xorb(const rvm<uint16_t,2> m0, const rvm<uint16_t,2> m1) {
	return mipp_xorb_k_uint16_m2(m0, m1);
}
inline rvm<uint16_t,4> xorb(const rvm<uint16_t,4> m0, const rvm<uint16_t,4> m1) {
	return mipp_xorb_k_uint16_m4(m0, m1);
}
inline rvm<uint16_t,8> xorb(const rvm<uint16_t,8> m0, const rvm<uint16_t,8> m1) {
	return mipp_xorb_k_uint16_m8(m0, m1);
}
inline rvm<uint8_t,1> xorb(const rvm<uint8_t,1> m0, const rvm<uint8_t,1> m1) {
	return mipp_xorb_k_uint8_m1(m0, m1);
}
inline rvm<uint8_t,2> xorb(const rvm<uint8_t,2> m0, const rvm<uint8_t,2> m1) {
	return mipp_xorb_k_uint8_m2(m0, m1);
}
inline rvm<uint8_t,4> xorb(const rvm<uint8_t,4> m0, const rvm<uint8_t,4> m1) {
	return mipp_xorb_k_uint8_m4(m0, m1);
}
inline rvm<uint8_t,8> xorb(const rvm<uint8_t,8> m0, const rvm<uint8_t,8> m1) {
	return mipp_xorb_k_uint8_m8(m0, m1);
}
inline rvd<float64_t,1> msb(const rvd<float64_t,1> r0) {
	return mipp_msb_float64_m1(r0);
}
inline rvd<float64_t,2> msb(const rvd<float64_t,2> r0) {
	return mipp_msb_float64_m2(r0);
}
inline rvd<float64_t,4> msb(const rvd<float64_t,4> r0) {
	return mipp_msb_float64_m4(r0);
}
inline rvd<float64_t,8> msb(const rvd<float64_t,8> r0) {
	return mipp_msb_float64_m8(r0);
}
inline rvd<float32_t,1> msb(const rvd<float32_t,1> r0) {
	return mipp_msb_float32_m1(r0);
}
inline rvd<float32_t,2> msb(const rvd<float32_t,2> r0) {
	return mipp_msb_float32_m2(r0);
}
inline rvd<float32_t,4> msb(const rvd<float32_t,4> r0) {
	return mipp_msb_float32_m4(r0);
}
inline rvd<float32_t,8> msb(const rvd<float32_t,8> r0) {
	return mipp_msb_float32_m8(r0);
}
inline rvd<int64_t,1> msb(const rvd<int64_t,1> r0) {
	return mipp_msb_int64_m1(r0);
}
inline rvd<int64_t,2> msb(const rvd<int64_t,2> r0) {
	return mipp_msb_int64_m2(r0);
}
inline rvd<int64_t,4> msb(const rvd<int64_t,4> r0) {
	return mipp_msb_int64_m4(r0);
}
inline rvd<int64_t,8> msb(const rvd<int64_t,8> r0) {
	return mipp_msb_int64_m8(r0);
}
inline rvd<int32_t,1> msb(const rvd<int32_t,1> r0) {
	return mipp_msb_int32_m1(r0);
}
inline rvd<int32_t,2> msb(const rvd<int32_t,2> r0) {
	return mipp_msb_int32_m2(r0);
}
inline rvd<int32_t,4> msb(const rvd<int32_t,4> r0) {
	return mipp_msb_int32_m4(r0);
}
inline rvd<int32_t,8> msb(const rvd<int32_t,8> r0) {
	return mipp_msb_int32_m8(r0);
}
inline rvd<int16_t,1> msb(const rvd<int16_t,1> r0) {
	return mipp_msb_int16_m1(r0);
}
inline rvd<int16_t,2> msb(const rvd<int16_t,2> r0) {
	return mipp_msb_int16_m2(r0);
}
inline rvd<int16_t,4> msb(const rvd<int16_t,4> r0) {
	return mipp_msb_int16_m4(r0);
}
inline rvd<int16_t,8> msb(const rvd<int16_t,8> r0) {
	return mipp_msb_int16_m8(r0);
}
inline rvd<int8_t,1> msb(const rvd<int8_t,1> r0) {
	return mipp_msb_int8_m1(r0);
}
inline rvd<int8_t,2> msb(const rvd<int8_t,2> r0) {
	return mipp_msb_int8_m2(r0);
}
inline rvd<int8_t,4> msb(const rvd<int8_t,4> r0) {
	return mipp_msb_int8_m4(r0);
}
inline rvd<int8_t,8> msb(const rvd<int8_t,8> r0) {
	return mipp_msb_int8_m8(r0);
}
inline rvd<uint64_t,1> msb(const rvd<uint64_t,1> r0) {
	return mipp_msb_uint64_m1(r0);
}
inline rvd<uint64_t,2> msb(const rvd<uint64_t,2> r0) {
	return mipp_msb_uint64_m2(r0);
}
inline rvd<uint64_t,4> msb(const rvd<uint64_t,4> r0) {
	return mipp_msb_uint64_m4(r0);
}
inline rvd<uint64_t,8> msb(const rvd<uint64_t,8> r0) {
	return mipp_msb_uint64_m8(r0);
}
inline rvd<uint32_t,1> msb(const rvd<uint32_t,1> r0) {
	return mipp_msb_uint32_m1(r0);
}
inline rvd<uint32_t,2> msb(const rvd<uint32_t,2> r0) {
	return mipp_msb_uint32_m2(r0);
}
inline rvd<uint32_t,4> msb(const rvd<uint32_t,4> r0) {
	return mipp_msb_uint32_m4(r0);
}
inline rvd<uint32_t,8> msb(const rvd<uint32_t,8> r0) {
	return mipp_msb_uint32_m8(r0);
}
inline rvd<uint16_t,1> msb(const rvd<uint16_t,1> r0) {
	return mipp_msb_uint16_m1(r0);
}
inline rvd<uint16_t,2> msb(const rvd<uint16_t,2> r0) {
	return mipp_msb_uint16_m2(r0);
}
inline rvd<uint16_t,4> msb(const rvd<uint16_t,4> r0) {
	return mipp_msb_uint16_m4(r0);
}
inline rvd<uint16_t,8> msb(const rvd<uint16_t,8> r0) {
	return mipp_msb_uint16_m8(r0);
}
inline rvd<uint8_t,1> msb(const rvd<uint8_t,1> r0) {
	return mipp_msb_uint8_m1(r0);
}
inline rvd<uint8_t,2> msb(const rvd<uint8_t,2> r0) {
	return mipp_msb_uint8_m2(r0);
}
inline rvd<uint8_t,4> msb(const rvd<uint8_t,4> r0) {
	return mipp_msb_uint8_m4(r0);
}
inline rvd<uint8_t,8> msb(const rvd<uint8_t,8> r0) {
	return mipp_msb_uint8_m8(r0);
}
inline rvd<float64_t,1> notb(const rvd<float64_t,1> r0) {
	return mipp_notb_float64_m1(r0);
}
inline rvd<float64_t,2> notb(const rvd<float64_t,2> r0) {
	return mipp_notb_float64_m2(r0);
}
inline rvd<float64_t,4> notb(const rvd<float64_t,4> r0) {
	return mipp_notb_float64_m4(r0);
}
inline rvd<float64_t,8> notb(const rvd<float64_t,8> r0) {
	return mipp_notb_float64_m8(r0);
}
inline rvd<float32_t,1> notb(const rvd<float32_t,1> r0) {
	return mipp_notb_float32_m1(r0);
}
inline rvd<float32_t,2> notb(const rvd<float32_t,2> r0) {
	return mipp_notb_float32_m2(r0);
}
inline rvd<float32_t,4> notb(const rvd<float32_t,4> r0) {
	return mipp_notb_float32_m4(r0);
}
inline rvd<float32_t,8> notb(const rvd<float32_t,8> r0) {
	return mipp_notb_float32_m8(r0);
}
inline rvd<int64_t,1> notb(const rvd<int64_t,1> r0) {
	return mipp_notb_int64_m1(r0);
}
inline rvd<int64_t,2> notb(const rvd<int64_t,2> r0) {
	return mipp_notb_int64_m2(r0);
}
inline rvd<int64_t,4> notb(const rvd<int64_t,4> r0) {
	return mipp_notb_int64_m4(r0);
}
inline rvd<int64_t,8> notb(const rvd<int64_t,8> r0) {
	return mipp_notb_int64_m8(r0);
}
inline rvd<int32_t,1> notb(const rvd<int32_t,1> r0) {
	return mipp_notb_int32_m1(r0);
}
inline rvd<int32_t,2> notb(const rvd<int32_t,2> r0) {
	return mipp_notb_int32_m2(r0);
}
inline rvd<int32_t,4> notb(const rvd<int32_t,4> r0) {
	return mipp_notb_int32_m4(r0);
}
inline rvd<int32_t,8> notb(const rvd<int32_t,8> r0) {
	return mipp_notb_int32_m8(r0);
}
inline rvd<int16_t,1> notb(const rvd<int16_t,1> r0) {
	return mipp_notb_int16_m1(r0);
}
inline rvd<int16_t,2> notb(const rvd<int16_t,2> r0) {
	return mipp_notb_int16_m2(r0);
}
inline rvd<int16_t,4> notb(const rvd<int16_t,4> r0) {
	return mipp_notb_int16_m4(r0);
}
inline rvd<int16_t,8> notb(const rvd<int16_t,8> r0) {
	return mipp_notb_int16_m8(r0);
}
inline rvd<int8_t,1> notb(const rvd<int8_t,1> r0) {
	return mipp_notb_int8_m1(r0);
}
inline rvd<int8_t,2> notb(const rvd<int8_t,2> r0) {
	return mipp_notb_int8_m2(r0);
}
inline rvd<int8_t,4> notb(const rvd<int8_t,4> r0) {
	return mipp_notb_int8_m4(r0);
}
inline rvd<int8_t,8> notb(const rvd<int8_t,8> r0) {
	return mipp_notb_int8_m8(r0);
}
inline rvd<uint64_t,1> notb(const rvd<uint64_t,1> r0) {
	return mipp_notb_uint64_m1(r0);
}
inline rvd<uint64_t,2> notb(const rvd<uint64_t,2> r0) {
	return mipp_notb_uint64_m2(r0);
}
inline rvd<uint64_t,4> notb(const rvd<uint64_t,4> r0) {
	return mipp_notb_uint64_m4(r0);
}
inline rvd<uint64_t,8> notb(const rvd<uint64_t,8> r0) {
	return mipp_notb_uint64_m8(r0);
}
inline rvd<uint32_t,1> notb(const rvd<uint32_t,1> r0) {
	return mipp_notb_uint32_m1(r0);
}
inline rvd<uint32_t,2> notb(const rvd<uint32_t,2> r0) {
	return mipp_notb_uint32_m2(r0);
}
inline rvd<uint32_t,4> notb(const rvd<uint32_t,4> r0) {
	return mipp_notb_uint32_m4(r0);
}
inline rvd<uint32_t,8> notb(const rvd<uint32_t,8> r0) {
	return mipp_notb_uint32_m8(r0);
}
inline rvd<uint16_t,1> notb(const rvd<uint16_t,1> r0) {
	return mipp_notb_uint16_m1(r0);
}
inline rvd<uint16_t,2> notb(const rvd<uint16_t,2> r0) {
	return mipp_notb_uint16_m2(r0);
}
inline rvd<uint16_t,4> notb(const rvd<uint16_t,4> r0) {
	return mipp_notb_uint16_m4(r0);
}
inline rvd<uint16_t,8> notb(const rvd<uint16_t,8> r0) {
	return mipp_notb_uint16_m8(r0);
}
inline rvd<uint8_t,1> notb(const rvd<uint8_t,1> r0) {
	return mipp_notb_uint8_m1(r0);
}
inline rvd<uint8_t,2> notb(const rvd<uint8_t,2> r0) {
	return mipp_notb_uint8_m2(r0);
}
inline rvd<uint8_t,4> notb(const rvd<uint8_t,4> r0) {
	return mipp_notb_uint8_m4(r0);
}
inline rvd<uint8_t,8> notb(const rvd<uint8_t,8> r0) {
	return mipp_notb_uint8_m8(r0);
}
inline rvm<float64_t,1> notb(const rvm<float64_t,1> m0) {
	return mipp_notb_k_float64_m1(m0);
}
inline rvm<float64_t,2> notb(const rvm<float64_t,2> m0) {
	return mipp_notb_k_float64_m2(m0);
}
inline rvm<float64_t,4> notb(const rvm<float64_t,4> m0) {
	return mipp_notb_k_float64_m4(m0);
}
inline rvm<float64_t,8> notb(const rvm<float64_t,8> m0) {
	return mipp_notb_k_float64_m8(m0);
}
inline rvm<float32_t,1> notb(const rvm<float32_t,1> m0) {
	return mipp_notb_k_float32_m1(m0);
}
inline rvm<float32_t,2> notb(const rvm<float32_t,2> m0) {
	return mipp_notb_k_float32_m2(m0);
}
inline rvm<float32_t,4> notb(const rvm<float32_t,4> m0) {
	return mipp_notb_k_float32_m4(m0);
}
inline rvm<float32_t,8> notb(const rvm<float32_t,8> m0) {
	return mipp_notb_k_float32_m8(m0);
}
inline rvm<int64_t,1> notb(const rvm<int64_t,1> m0) {
	return mipp_notb_k_int64_m1(m0);
}
inline rvm<int64_t,2> notb(const rvm<int64_t,2> m0) {
	return mipp_notb_k_int64_m2(m0);
}
inline rvm<int64_t,4> notb(const rvm<int64_t,4> m0) {
	return mipp_notb_k_int64_m4(m0);
}
inline rvm<int64_t,8> notb(const rvm<int64_t,8> m0) {
	return mipp_notb_k_int64_m8(m0);
}
inline rvm<int32_t,1> notb(const rvm<int32_t,1> m0) {
	return mipp_notb_k_int32_m1(m0);
}
inline rvm<int32_t,2> notb(const rvm<int32_t,2> m0) {
	return mipp_notb_k_int32_m2(m0);
}
inline rvm<int32_t,4> notb(const rvm<int32_t,4> m0) {
	return mipp_notb_k_int32_m4(m0);
}
inline rvm<int32_t,8> notb(const rvm<int32_t,8> m0) {
	return mipp_notb_k_int32_m8(m0);
}
inline rvm<int16_t,1> notb(const rvm<int16_t,1> m0) {
	return mipp_notb_k_int16_m1(m0);
}
inline rvm<int16_t,2> notb(const rvm<int16_t,2> m0) {
	return mipp_notb_k_int16_m2(m0);
}
inline rvm<int16_t,4> notb(const rvm<int16_t,4> m0) {
	return mipp_notb_k_int16_m4(m0);
}
inline rvm<int16_t,8> notb(const rvm<int16_t,8> m0) {
	return mipp_notb_k_int16_m8(m0);
}
inline rvm<int8_t,1> notb(const rvm<int8_t,1> m0) {
	return mipp_notb_k_int8_m1(m0);
}
inline rvm<int8_t,2> notb(const rvm<int8_t,2> m0) {
	return mipp_notb_k_int8_m2(m0);
}
inline rvm<int8_t,4> notb(const rvm<int8_t,4> m0) {
	return mipp_notb_k_int8_m4(m0);
}
inline rvm<int8_t,8> notb(const rvm<int8_t,8> m0) {
	return mipp_notb_k_int8_m8(m0);
}
inline rvm<uint64_t,1> notb(const rvm<uint64_t,1> m0) {
	return mipp_notb_k_uint64_m1(m0);
}
inline rvm<uint64_t,2> notb(const rvm<uint64_t,2> m0) {
	return mipp_notb_k_uint64_m2(m0);
}
inline rvm<uint64_t,4> notb(const rvm<uint64_t,4> m0) {
	return mipp_notb_k_uint64_m4(m0);
}
inline rvm<uint64_t,8> notb(const rvm<uint64_t,8> m0) {
	return mipp_notb_k_uint64_m8(m0);
}
inline rvm<uint32_t,1> notb(const rvm<uint32_t,1> m0) {
	return mipp_notb_k_uint32_m1(m0);
}
inline rvm<uint32_t,2> notb(const rvm<uint32_t,2> m0) {
	return mipp_notb_k_uint32_m2(m0);
}
inline rvm<uint32_t,4> notb(const rvm<uint32_t,4> m0) {
	return mipp_notb_k_uint32_m4(m0);
}
inline rvm<uint32_t,8> notb(const rvm<uint32_t,8> m0) {
	return mipp_notb_k_uint32_m8(m0);
}
inline rvm<uint16_t,1> notb(const rvm<uint16_t,1> m0) {
	return mipp_notb_k_uint16_m1(m0);
}
inline rvm<uint16_t,2> notb(const rvm<uint16_t,2> m0) {
	return mipp_notb_k_uint16_m2(m0);
}
inline rvm<uint16_t,4> notb(const rvm<uint16_t,4> m0) {
	return mipp_notb_k_uint16_m4(m0);
}
inline rvm<uint16_t,8> notb(const rvm<uint16_t,8> m0) {
	return mipp_notb_k_uint16_m8(m0);
}
inline rvm<uint8_t,1> notb(const rvm<uint8_t,1> m0) {
	return mipp_notb_k_uint8_m1(m0);
}
inline rvm<uint8_t,2> notb(const rvm<uint8_t,2> m0) {
	return mipp_notb_k_uint8_m2(m0);
}
inline rvm<uint8_t,4> notb(const rvm<uint8_t,4> m0) {
	return mipp_notb_k_uint8_m4(m0);
}
inline rvm<uint8_t,8> notb(const rvm<uint8_t,8> m0) {
	return mipp_notb_k_uint8_m8(m0);
}
inline rvm<float64_t,1> cmpeq(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_cmpeq_float64_m1(r0, r1);
}
inline rvm<float64_t,2> cmpeq(const rvd<float64_t,2> r0, const rvd<float64_t,2> r1) {
	return mipp_cmpeq_float64_m2(r0, r1);
}
inline rvm<float64_t,4> cmpeq(const rvd<float64_t,4> r0, const rvd<float64_t,4> r1) {
	return mipp_cmpeq_float64_m4(r0, r1);
}
inline rvm<float64_t,8> cmpeq(const rvd<float64_t,8> r0, const rvd<float64_t,8> r1) {
	return mipp_cmpeq_float64_m8(r0, r1);
}
inline rvm<float32_t,1> cmpeq(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_cmpeq_float32_m1(r0, r1);
}
inline rvm<float32_t,2> cmpeq(const rvd<float32_t,2> r0, const rvd<float32_t,2> r1) {
	return mipp_cmpeq_float32_m2(r0, r1);
}
inline rvm<float32_t,4> cmpeq(const rvd<float32_t,4> r0, const rvd<float32_t,4> r1) {
	return mipp_cmpeq_float32_m4(r0, r1);
}
inline rvm<float32_t,8> cmpeq(const rvd<float32_t,8> r0, const rvd<float32_t,8> r1) {
	return mipp_cmpeq_float32_m8(r0, r1);
}
inline rvm<int64_t,1> cmpeq(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_cmpeq_int64_m1(r0, r1);
}
inline rvm<int64_t,2> cmpeq(const rvd<int64_t,2> r0, const rvd<int64_t,2> r1) {
	return mipp_cmpeq_int64_m2(r0, r1);
}
inline rvm<int64_t,4> cmpeq(const rvd<int64_t,4> r0, const rvd<int64_t,4> r1) {
	return mipp_cmpeq_int64_m4(r0, r1);
}
inline rvm<int64_t,8> cmpeq(const rvd<int64_t,8> r0, const rvd<int64_t,8> r1) {
	return mipp_cmpeq_int64_m8(r0, r1);
}
inline rvm<int32_t,1> cmpeq(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_cmpeq_int32_m1(r0, r1);
}
inline rvm<int32_t,2> cmpeq(const rvd<int32_t,2> r0, const rvd<int32_t,2> r1) {
	return mipp_cmpeq_int32_m2(r0, r1);
}
inline rvm<int32_t,4> cmpeq(const rvd<int32_t,4> r0, const rvd<int32_t,4> r1) {
	return mipp_cmpeq_int32_m4(r0, r1);
}
inline rvm<int32_t,8> cmpeq(const rvd<int32_t,8> r0, const rvd<int32_t,8> r1) {
	return mipp_cmpeq_int32_m8(r0, r1);
}
inline rvm<int16_t,1> cmpeq(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_cmpeq_int16_m1(r0, r1);
}
inline rvm<int16_t,2> cmpeq(const rvd<int16_t,2> r0, const rvd<int16_t,2> r1) {
	return mipp_cmpeq_int16_m2(r0, r1);
}
inline rvm<int16_t,4> cmpeq(const rvd<int16_t,4> r0, const rvd<int16_t,4> r1) {
	return mipp_cmpeq_int16_m4(r0, r1);
}
inline rvm<int16_t,8> cmpeq(const rvd<int16_t,8> r0, const rvd<int16_t,8> r1) {
	return mipp_cmpeq_int16_m8(r0, r1);
}
inline rvm<int8_t,1> cmpeq(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_cmpeq_int8_m1(r0, r1);
}
inline rvm<int8_t,2> cmpeq(const rvd<int8_t,2> r0, const rvd<int8_t,2> r1) {
	return mipp_cmpeq_int8_m2(r0, r1);
}
inline rvm<int8_t,4> cmpeq(const rvd<int8_t,4> r0, const rvd<int8_t,4> r1) {
	return mipp_cmpeq_int8_m4(r0, r1);
}
inline rvm<int8_t,8> cmpeq(const rvd<int8_t,8> r0, const rvd<int8_t,8> r1) {
	return mipp_cmpeq_int8_m8(r0, r1);
}
inline rvm<uint64_t,1> cmpeq(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_cmpeq_uint64_m1(r0, r1);
}
inline rvm<uint64_t,2> cmpeq(const rvd<uint64_t,2> r0, const rvd<uint64_t,2> r1) {
	return mipp_cmpeq_uint64_m2(r0, r1);
}
inline rvm<uint64_t,4> cmpeq(const rvd<uint64_t,4> r0, const rvd<uint64_t,4> r1) {
	return mipp_cmpeq_uint64_m4(r0, r1);
}
inline rvm<uint64_t,8> cmpeq(const rvd<uint64_t,8> r0, const rvd<uint64_t,8> r1) {
	return mipp_cmpeq_uint64_m8(r0, r1);
}
inline rvm<uint32_t,1> cmpeq(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_cmpeq_uint32_m1(r0, r1);
}
inline rvm<uint32_t,2> cmpeq(const rvd<uint32_t,2> r0, const rvd<uint32_t,2> r1) {
	return mipp_cmpeq_uint32_m2(r0, r1);
}
inline rvm<uint32_t,4> cmpeq(const rvd<uint32_t,4> r0, const rvd<uint32_t,4> r1) {
	return mipp_cmpeq_uint32_m4(r0, r1);
}
inline rvm<uint32_t,8> cmpeq(const rvd<uint32_t,8> r0, const rvd<uint32_t,8> r1) {
	return mipp_cmpeq_uint32_m8(r0, r1);
}
inline rvm<uint16_t,1> cmpeq(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_cmpeq_uint16_m1(r0, r1);
}
inline rvm<uint16_t,2> cmpeq(const rvd<uint16_t,2> r0, const rvd<uint16_t,2> r1) {
	return mipp_cmpeq_uint16_m2(r0, r1);
}
inline rvm<uint16_t,4> cmpeq(const rvd<uint16_t,4> r0, const rvd<uint16_t,4> r1) {
	return mipp_cmpeq_uint16_m4(r0, r1);
}
inline rvm<uint16_t,8> cmpeq(const rvd<uint16_t,8> r0, const rvd<uint16_t,8> r1) {
	return mipp_cmpeq_uint16_m8(r0, r1);
}
inline rvm<uint8_t,1> cmpeq(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_cmpeq_uint8_m1(r0, r1);
}
inline rvm<uint8_t,2> cmpeq(const rvd<uint8_t,2> r0, const rvd<uint8_t,2> r1) {
	return mipp_cmpeq_uint8_m2(r0, r1);
}
inline rvm<uint8_t,4> cmpeq(const rvd<uint8_t,4> r0, const rvd<uint8_t,4> r1) {
	return mipp_cmpeq_uint8_m4(r0, r1);
}
inline rvm<uint8_t,8> cmpeq(const rvd<uint8_t,8> r0, const rvd<uint8_t,8> r1) {
	return mipp_cmpeq_uint8_m8(r0, r1);
}
inline rvm<float64_t,1> cmpneq(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_cmpneq_float64_m1(r0, r1);
}
inline rvm<float64_t,2> cmpneq(const rvd<float64_t,2> r0, const rvd<float64_t,2> r1) {
	return mipp_cmpneq_float64_m2(r0, r1);
}
inline rvm<float64_t,4> cmpneq(const rvd<float64_t,4> r0, const rvd<float64_t,4> r1) {
	return mipp_cmpneq_float64_m4(r0, r1);
}
inline rvm<float64_t,8> cmpneq(const rvd<float64_t,8> r0, const rvd<float64_t,8> r1) {
	return mipp_cmpneq_float64_m8(r0, r1);
}
inline rvm<float32_t,1> cmpneq(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_cmpneq_float32_m1(r0, r1);
}
inline rvm<float32_t,2> cmpneq(const rvd<float32_t,2> r0, const rvd<float32_t,2> r1) {
	return mipp_cmpneq_float32_m2(r0, r1);
}
inline rvm<float32_t,4> cmpneq(const rvd<float32_t,4> r0, const rvd<float32_t,4> r1) {
	return mipp_cmpneq_float32_m4(r0, r1);
}
inline rvm<float32_t,8> cmpneq(const rvd<float32_t,8> r0, const rvd<float32_t,8> r1) {
	return mipp_cmpneq_float32_m8(r0, r1);
}
inline rvm<int64_t,1> cmpneq(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_cmpneq_int64_m1(r0, r1);
}
inline rvm<int64_t,2> cmpneq(const rvd<int64_t,2> r0, const rvd<int64_t,2> r1) {
	return mipp_cmpneq_int64_m2(r0, r1);
}
inline rvm<int64_t,4> cmpneq(const rvd<int64_t,4> r0, const rvd<int64_t,4> r1) {
	return mipp_cmpneq_int64_m4(r0, r1);
}
inline rvm<int64_t,8> cmpneq(const rvd<int64_t,8> r0, const rvd<int64_t,8> r1) {
	return mipp_cmpneq_int64_m8(r0, r1);
}
inline rvm<int32_t,1> cmpneq(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_cmpneq_int32_m1(r0, r1);
}
inline rvm<int32_t,2> cmpneq(const rvd<int32_t,2> r0, const rvd<int32_t,2> r1) {
	return mipp_cmpneq_int32_m2(r0, r1);
}
inline rvm<int32_t,4> cmpneq(const rvd<int32_t,4> r0, const rvd<int32_t,4> r1) {
	return mipp_cmpneq_int32_m4(r0, r1);
}
inline rvm<int32_t,8> cmpneq(const rvd<int32_t,8> r0, const rvd<int32_t,8> r1) {
	return mipp_cmpneq_int32_m8(r0, r1);
}
inline rvm<int16_t,1> cmpneq(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_cmpneq_int16_m1(r0, r1);
}
inline rvm<int16_t,2> cmpneq(const rvd<int16_t,2> r0, const rvd<int16_t,2> r1) {
	return mipp_cmpneq_int16_m2(r0, r1);
}
inline rvm<int16_t,4> cmpneq(const rvd<int16_t,4> r0, const rvd<int16_t,4> r1) {
	return mipp_cmpneq_int16_m4(r0, r1);
}
inline rvm<int16_t,8> cmpneq(const rvd<int16_t,8> r0, const rvd<int16_t,8> r1) {
	return mipp_cmpneq_int16_m8(r0, r1);
}
inline rvm<int8_t,1> cmpneq(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_cmpneq_int8_m1(r0, r1);
}
inline rvm<int8_t,2> cmpneq(const rvd<int8_t,2> r0, const rvd<int8_t,2> r1) {
	return mipp_cmpneq_int8_m2(r0, r1);
}
inline rvm<int8_t,4> cmpneq(const rvd<int8_t,4> r0, const rvd<int8_t,4> r1) {
	return mipp_cmpneq_int8_m4(r0, r1);
}
inline rvm<int8_t,8> cmpneq(const rvd<int8_t,8> r0, const rvd<int8_t,8> r1) {
	return mipp_cmpneq_int8_m8(r0, r1);
}
inline rvm<uint64_t,1> cmpneq(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_cmpneq_uint64_m1(r0, r1);
}
inline rvm<uint64_t,2> cmpneq(const rvd<uint64_t,2> r0, const rvd<uint64_t,2> r1) {
	return mipp_cmpneq_uint64_m2(r0, r1);
}
inline rvm<uint64_t,4> cmpneq(const rvd<uint64_t,4> r0, const rvd<uint64_t,4> r1) {
	return mipp_cmpneq_uint64_m4(r0, r1);
}
inline rvm<uint64_t,8> cmpneq(const rvd<uint64_t,8> r0, const rvd<uint64_t,8> r1) {
	return mipp_cmpneq_uint64_m8(r0, r1);
}
inline rvm<uint32_t,1> cmpneq(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_cmpneq_uint32_m1(r0, r1);
}
inline rvm<uint32_t,2> cmpneq(const rvd<uint32_t,2> r0, const rvd<uint32_t,2> r1) {
	return mipp_cmpneq_uint32_m2(r0, r1);
}
inline rvm<uint32_t,4> cmpneq(const rvd<uint32_t,4> r0, const rvd<uint32_t,4> r1) {
	return mipp_cmpneq_uint32_m4(r0, r1);
}
inline rvm<uint32_t,8> cmpneq(const rvd<uint32_t,8> r0, const rvd<uint32_t,8> r1) {
	return mipp_cmpneq_uint32_m8(r0, r1);
}
inline rvm<uint16_t,1> cmpneq(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_cmpneq_uint16_m1(r0, r1);
}
inline rvm<uint16_t,2> cmpneq(const rvd<uint16_t,2> r0, const rvd<uint16_t,2> r1) {
	return mipp_cmpneq_uint16_m2(r0, r1);
}
inline rvm<uint16_t,4> cmpneq(const rvd<uint16_t,4> r0, const rvd<uint16_t,4> r1) {
	return mipp_cmpneq_uint16_m4(r0, r1);
}
inline rvm<uint16_t,8> cmpneq(const rvd<uint16_t,8> r0, const rvd<uint16_t,8> r1) {
	return mipp_cmpneq_uint16_m8(r0, r1);
}
inline rvm<uint8_t,1> cmpneq(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_cmpneq_uint8_m1(r0, r1);
}
inline rvm<uint8_t,2> cmpneq(const rvd<uint8_t,2> r0, const rvd<uint8_t,2> r1) {
	return mipp_cmpneq_uint8_m2(r0, r1);
}
inline rvm<uint8_t,4> cmpneq(const rvd<uint8_t,4> r0, const rvd<uint8_t,4> r1) {
	return mipp_cmpneq_uint8_m4(r0, r1);
}
inline rvm<uint8_t,8> cmpneq(const rvd<uint8_t,8> r0, const rvd<uint8_t,8> r1) {
	return mipp_cmpneq_uint8_m8(r0, r1);
}
inline rvm<float64_t,1> cmplt(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_cmplt_float64_m1(r0, r1);
}
inline rvm<float64_t,2> cmplt(const rvd<float64_t,2> r0, const rvd<float64_t,2> r1) {
	return mipp_cmplt_float64_m2(r0, r1);
}
inline rvm<float64_t,4> cmplt(const rvd<float64_t,4> r0, const rvd<float64_t,4> r1) {
	return mipp_cmplt_float64_m4(r0, r1);
}
inline rvm<float64_t,8> cmplt(const rvd<float64_t,8> r0, const rvd<float64_t,8> r1) {
	return mipp_cmplt_float64_m8(r0, r1);
}
inline rvm<float32_t,1> cmplt(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_cmplt_float32_m1(r0, r1);
}
inline rvm<float32_t,2> cmplt(const rvd<float32_t,2> r0, const rvd<float32_t,2> r1) {
	return mipp_cmplt_float32_m2(r0, r1);
}
inline rvm<float32_t,4> cmplt(const rvd<float32_t,4> r0, const rvd<float32_t,4> r1) {
	return mipp_cmplt_float32_m4(r0, r1);
}
inline rvm<float32_t,8> cmplt(const rvd<float32_t,8> r0, const rvd<float32_t,8> r1) {
	return mipp_cmplt_float32_m8(r0, r1);
}
inline rvm<int64_t,1> cmplt(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_cmplt_int64_m1(r0, r1);
}
inline rvm<int64_t,2> cmplt(const rvd<int64_t,2> r0, const rvd<int64_t,2> r1) {
	return mipp_cmplt_int64_m2(r0, r1);
}
inline rvm<int64_t,4> cmplt(const rvd<int64_t,4> r0, const rvd<int64_t,4> r1) {
	return mipp_cmplt_int64_m4(r0, r1);
}
inline rvm<int64_t,8> cmplt(const rvd<int64_t,8> r0, const rvd<int64_t,8> r1) {
	return mipp_cmplt_int64_m8(r0, r1);
}
inline rvm<int32_t,1> cmplt(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_cmplt_int32_m1(r0, r1);
}
inline rvm<int32_t,2> cmplt(const rvd<int32_t,2> r0, const rvd<int32_t,2> r1) {
	return mipp_cmplt_int32_m2(r0, r1);
}
inline rvm<int32_t,4> cmplt(const rvd<int32_t,4> r0, const rvd<int32_t,4> r1) {
	return mipp_cmplt_int32_m4(r0, r1);
}
inline rvm<int32_t,8> cmplt(const rvd<int32_t,8> r0, const rvd<int32_t,8> r1) {
	return mipp_cmplt_int32_m8(r0, r1);
}
inline rvm<int16_t,1> cmplt(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_cmplt_int16_m1(r0, r1);
}
inline rvm<int16_t,2> cmplt(const rvd<int16_t,2> r0, const rvd<int16_t,2> r1) {
	return mipp_cmplt_int16_m2(r0, r1);
}
inline rvm<int16_t,4> cmplt(const rvd<int16_t,4> r0, const rvd<int16_t,4> r1) {
	return mipp_cmplt_int16_m4(r0, r1);
}
inline rvm<int16_t,8> cmplt(const rvd<int16_t,8> r0, const rvd<int16_t,8> r1) {
	return mipp_cmplt_int16_m8(r0, r1);
}
inline rvm<int8_t,1> cmplt(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_cmplt_int8_m1(r0, r1);
}
inline rvm<int8_t,2> cmplt(const rvd<int8_t,2> r0, const rvd<int8_t,2> r1) {
	return mipp_cmplt_int8_m2(r0, r1);
}
inline rvm<int8_t,4> cmplt(const rvd<int8_t,4> r0, const rvd<int8_t,4> r1) {
	return mipp_cmplt_int8_m4(r0, r1);
}
inline rvm<int8_t,8> cmplt(const rvd<int8_t,8> r0, const rvd<int8_t,8> r1) {
	return mipp_cmplt_int8_m8(r0, r1);
}
inline rvm<uint64_t,1> cmplt(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_cmplt_uint64_m1(r0, r1);
}
inline rvm<uint64_t,2> cmplt(const rvd<uint64_t,2> r0, const rvd<uint64_t,2> r1) {
	return mipp_cmplt_uint64_m2(r0, r1);
}
inline rvm<uint64_t,4> cmplt(const rvd<uint64_t,4> r0, const rvd<uint64_t,4> r1) {
	return mipp_cmplt_uint64_m4(r0, r1);
}
inline rvm<uint64_t,8> cmplt(const rvd<uint64_t,8> r0, const rvd<uint64_t,8> r1) {
	return mipp_cmplt_uint64_m8(r0, r1);
}
inline rvm<uint32_t,1> cmplt(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_cmplt_uint32_m1(r0, r1);
}
inline rvm<uint32_t,2> cmplt(const rvd<uint32_t,2> r0, const rvd<uint32_t,2> r1) {
	return mipp_cmplt_uint32_m2(r0, r1);
}
inline rvm<uint32_t,4> cmplt(const rvd<uint32_t,4> r0, const rvd<uint32_t,4> r1) {
	return mipp_cmplt_uint32_m4(r0, r1);
}
inline rvm<uint32_t,8> cmplt(const rvd<uint32_t,8> r0, const rvd<uint32_t,8> r1) {
	return mipp_cmplt_uint32_m8(r0, r1);
}
inline rvm<uint16_t,1> cmplt(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_cmplt_uint16_m1(r0, r1);
}
inline rvm<uint16_t,2> cmplt(const rvd<uint16_t,2> r0, const rvd<uint16_t,2> r1) {
	return mipp_cmplt_uint16_m2(r0, r1);
}
inline rvm<uint16_t,4> cmplt(const rvd<uint16_t,4> r0, const rvd<uint16_t,4> r1) {
	return mipp_cmplt_uint16_m4(r0, r1);
}
inline rvm<uint16_t,8> cmplt(const rvd<uint16_t,8> r0, const rvd<uint16_t,8> r1) {
	return mipp_cmplt_uint16_m8(r0, r1);
}
inline rvm<uint8_t,1> cmplt(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_cmplt_uint8_m1(r0, r1);
}
inline rvm<uint8_t,2> cmplt(const rvd<uint8_t,2> r0, const rvd<uint8_t,2> r1) {
	return mipp_cmplt_uint8_m2(r0, r1);
}
inline rvm<uint8_t,4> cmplt(const rvd<uint8_t,4> r0, const rvd<uint8_t,4> r1) {
	return mipp_cmplt_uint8_m4(r0, r1);
}
inline rvm<uint8_t,8> cmplt(const rvd<uint8_t,8> r0, const rvd<uint8_t,8> r1) {
	return mipp_cmplt_uint8_m8(r0, r1);
}
inline rvm<float64_t,1> cmple(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_cmple_float64_m1(r0, r1);
}
inline rvm<float64_t,2> cmple(const rvd<float64_t,2> r0, const rvd<float64_t,2> r1) {
	return mipp_cmple_float64_m2(r0, r1);
}
inline rvm<float64_t,4> cmple(const rvd<float64_t,4> r0, const rvd<float64_t,4> r1) {
	return mipp_cmple_float64_m4(r0, r1);
}
inline rvm<float64_t,8> cmple(const rvd<float64_t,8> r0, const rvd<float64_t,8> r1) {
	return mipp_cmple_float64_m8(r0, r1);
}
inline rvm<float32_t,1> cmple(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_cmple_float32_m1(r0, r1);
}
inline rvm<float32_t,2> cmple(const rvd<float32_t,2> r0, const rvd<float32_t,2> r1) {
	return mipp_cmple_float32_m2(r0, r1);
}
inline rvm<float32_t,4> cmple(const rvd<float32_t,4> r0, const rvd<float32_t,4> r1) {
	return mipp_cmple_float32_m4(r0, r1);
}
inline rvm<float32_t,8> cmple(const rvd<float32_t,8> r0, const rvd<float32_t,8> r1) {
	return mipp_cmple_float32_m8(r0, r1);
}
inline rvm<int64_t,1> cmple(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_cmple_int64_m1(r0, r1);
}
inline rvm<int64_t,2> cmple(const rvd<int64_t,2> r0, const rvd<int64_t,2> r1) {
	return mipp_cmple_int64_m2(r0, r1);
}
inline rvm<int64_t,4> cmple(const rvd<int64_t,4> r0, const rvd<int64_t,4> r1) {
	return mipp_cmple_int64_m4(r0, r1);
}
inline rvm<int64_t,8> cmple(const rvd<int64_t,8> r0, const rvd<int64_t,8> r1) {
	return mipp_cmple_int64_m8(r0, r1);
}
inline rvm<int32_t,1> cmple(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_cmple_int32_m1(r0, r1);
}
inline rvm<int32_t,2> cmple(const rvd<int32_t,2> r0, const rvd<int32_t,2> r1) {
	return mipp_cmple_int32_m2(r0, r1);
}
inline rvm<int32_t,4> cmple(const rvd<int32_t,4> r0, const rvd<int32_t,4> r1) {
	return mipp_cmple_int32_m4(r0, r1);
}
inline rvm<int32_t,8> cmple(const rvd<int32_t,8> r0, const rvd<int32_t,8> r1) {
	return mipp_cmple_int32_m8(r0, r1);
}
inline rvm<int16_t,1> cmple(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_cmple_int16_m1(r0, r1);
}
inline rvm<int16_t,2> cmple(const rvd<int16_t,2> r0, const rvd<int16_t,2> r1) {
	return mipp_cmple_int16_m2(r0, r1);
}
inline rvm<int16_t,4> cmple(const rvd<int16_t,4> r0, const rvd<int16_t,4> r1) {
	return mipp_cmple_int16_m4(r0, r1);
}
inline rvm<int16_t,8> cmple(const rvd<int16_t,8> r0, const rvd<int16_t,8> r1) {
	return mipp_cmple_int16_m8(r0, r1);
}
inline rvm<int8_t,1> cmple(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_cmple_int8_m1(r0, r1);
}
inline rvm<int8_t,2> cmple(const rvd<int8_t,2> r0, const rvd<int8_t,2> r1) {
	return mipp_cmple_int8_m2(r0, r1);
}
inline rvm<int8_t,4> cmple(const rvd<int8_t,4> r0, const rvd<int8_t,4> r1) {
	return mipp_cmple_int8_m4(r0, r1);
}
inline rvm<int8_t,8> cmple(const rvd<int8_t,8> r0, const rvd<int8_t,8> r1) {
	return mipp_cmple_int8_m8(r0, r1);
}
inline rvm<uint64_t,1> cmple(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_cmple_uint64_m1(r0, r1);
}
inline rvm<uint64_t,2> cmple(const rvd<uint64_t,2> r0, const rvd<uint64_t,2> r1) {
	return mipp_cmple_uint64_m2(r0, r1);
}
inline rvm<uint64_t,4> cmple(const rvd<uint64_t,4> r0, const rvd<uint64_t,4> r1) {
	return mipp_cmple_uint64_m4(r0, r1);
}
inline rvm<uint64_t,8> cmple(const rvd<uint64_t,8> r0, const rvd<uint64_t,8> r1) {
	return mipp_cmple_uint64_m8(r0, r1);
}
inline rvm<uint32_t,1> cmple(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_cmple_uint32_m1(r0, r1);
}
inline rvm<uint32_t,2> cmple(const rvd<uint32_t,2> r0, const rvd<uint32_t,2> r1) {
	return mipp_cmple_uint32_m2(r0, r1);
}
inline rvm<uint32_t,4> cmple(const rvd<uint32_t,4> r0, const rvd<uint32_t,4> r1) {
	return mipp_cmple_uint32_m4(r0, r1);
}
inline rvm<uint32_t,8> cmple(const rvd<uint32_t,8> r0, const rvd<uint32_t,8> r1) {
	return mipp_cmple_uint32_m8(r0, r1);
}
inline rvm<uint16_t,1> cmple(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_cmple_uint16_m1(r0, r1);
}
inline rvm<uint16_t,2> cmple(const rvd<uint16_t,2> r0, const rvd<uint16_t,2> r1) {
	return mipp_cmple_uint16_m2(r0, r1);
}
inline rvm<uint16_t,4> cmple(const rvd<uint16_t,4> r0, const rvd<uint16_t,4> r1) {
	return mipp_cmple_uint16_m4(r0, r1);
}
inline rvm<uint16_t,8> cmple(const rvd<uint16_t,8> r0, const rvd<uint16_t,8> r1) {
	return mipp_cmple_uint16_m8(r0, r1);
}
inline rvm<uint8_t,1> cmple(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_cmple_uint8_m1(r0, r1);
}
inline rvm<uint8_t,2> cmple(const rvd<uint8_t,2> r0, const rvd<uint8_t,2> r1) {
	return mipp_cmple_uint8_m2(r0, r1);
}
inline rvm<uint8_t,4> cmple(const rvd<uint8_t,4> r0, const rvd<uint8_t,4> r1) {
	return mipp_cmple_uint8_m4(r0, r1);
}
inline rvm<uint8_t,8> cmple(const rvd<uint8_t,8> r0, const rvd<uint8_t,8> r1) {
	return mipp_cmple_uint8_m8(r0, r1);
}
inline rvm<float64_t,1> cmpge(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_cmpge_float64_m1(r0, r1);
}
inline rvm<float64_t,2> cmpge(const rvd<float64_t,2> r0, const rvd<float64_t,2> r1) {
	return mipp_cmpge_float64_m2(r0, r1);
}
inline rvm<float64_t,4> cmpge(const rvd<float64_t,4> r0, const rvd<float64_t,4> r1) {
	return mipp_cmpge_float64_m4(r0, r1);
}
inline rvm<float64_t,8> cmpge(const rvd<float64_t,8> r0, const rvd<float64_t,8> r1) {
	return mipp_cmpge_float64_m8(r0, r1);
}
inline rvm<float32_t,1> cmpge(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_cmpge_float32_m1(r0, r1);
}
inline rvm<float32_t,2> cmpge(const rvd<float32_t,2> r0, const rvd<float32_t,2> r1) {
	return mipp_cmpge_float32_m2(r0, r1);
}
inline rvm<float32_t,4> cmpge(const rvd<float32_t,4> r0, const rvd<float32_t,4> r1) {
	return mipp_cmpge_float32_m4(r0, r1);
}
inline rvm<float32_t,8> cmpge(const rvd<float32_t,8> r0, const rvd<float32_t,8> r1) {
	return mipp_cmpge_float32_m8(r0, r1);
}
inline rvm<int64_t,1> cmpge(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_cmpge_int64_m1(r0, r1);
}
inline rvm<int64_t,2> cmpge(const rvd<int64_t,2> r0, const rvd<int64_t,2> r1) {
	return mipp_cmpge_int64_m2(r0, r1);
}
inline rvm<int64_t,4> cmpge(const rvd<int64_t,4> r0, const rvd<int64_t,4> r1) {
	return mipp_cmpge_int64_m4(r0, r1);
}
inline rvm<int64_t,8> cmpge(const rvd<int64_t,8> r0, const rvd<int64_t,8> r1) {
	return mipp_cmpge_int64_m8(r0, r1);
}
inline rvm<int32_t,1> cmpge(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_cmpge_int32_m1(r0, r1);
}
inline rvm<int32_t,2> cmpge(const rvd<int32_t,2> r0, const rvd<int32_t,2> r1) {
	return mipp_cmpge_int32_m2(r0, r1);
}
inline rvm<int32_t,4> cmpge(const rvd<int32_t,4> r0, const rvd<int32_t,4> r1) {
	return mipp_cmpge_int32_m4(r0, r1);
}
inline rvm<int32_t,8> cmpge(const rvd<int32_t,8> r0, const rvd<int32_t,8> r1) {
	return mipp_cmpge_int32_m8(r0, r1);
}
inline rvm<int16_t,1> cmpge(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_cmpge_int16_m1(r0, r1);
}
inline rvm<int16_t,2> cmpge(const rvd<int16_t,2> r0, const rvd<int16_t,2> r1) {
	return mipp_cmpge_int16_m2(r0, r1);
}
inline rvm<int16_t,4> cmpge(const rvd<int16_t,4> r0, const rvd<int16_t,4> r1) {
	return mipp_cmpge_int16_m4(r0, r1);
}
inline rvm<int16_t,8> cmpge(const rvd<int16_t,8> r0, const rvd<int16_t,8> r1) {
	return mipp_cmpge_int16_m8(r0, r1);
}
inline rvm<int8_t,1> cmpge(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_cmpge_int8_m1(r0, r1);
}
inline rvm<int8_t,2> cmpge(const rvd<int8_t,2> r0, const rvd<int8_t,2> r1) {
	return mipp_cmpge_int8_m2(r0, r1);
}
inline rvm<int8_t,4> cmpge(const rvd<int8_t,4> r0, const rvd<int8_t,4> r1) {
	return mipp_cmpge_int8_m4(r0, r1);
}
inline rvm<int8_t,8> cmpge(const rvd<int8_t,8> r0, const rvd<int8_t,8> r1) {
	return mipp_cmpge_int8_m8(r0, r1);
}
inline rvm<uint64_t,1> cmpge(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_cmpge_uint64_m1(r0, r1);
}
inline rvm<uint64_t,2> cmpge(const rvd<uint64_t,2> r0, const rvd<uint64_t,2> r1) {
	return mipp_cmpge_uint64_m2(r0, r1);
}
inline rvm<uint64_t,4> cmpge(const rvd<uint64_t,4> r0, const rvd<uint64_t,4> r1) {
	return mipp_cmpge_uint64_m4(r0, r1);
}
inline rvm<uint64_t,8> cmpge(const rvd<uint64_t,8> r0, const rvd<uint64_t,8> r1) {
	return mipp_cmpge_uint64_m8(r0, r1);
}
inline rvm<uint32_t,1> cmpge(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_cmpge_uint32_m1(r0, r1);
}
inline rvm<uint32_t,2> cmpge(const rvd<uint32_t,2> r0, const rvd<uint32_t,2> r1) {
	return mipp_cmpge_uint32_m2(r0, r1);
}
inline rvm<uint32_t,4> cmpge(const rvd<uint32_t,4> r0, const rvd<uint32_t,4> r1) {
	return mipp_cmpge_uint32_m4(r0, r1);
}
inline rvm<uint32_t,8> cmpge(const rvd<uint32_t,8> r0, const rvd<uint32_t,8> r1) {
	return mipp_cmpge_uint32_m8(r0, r1);
}
inline rvm<uint16_t,1> cmpge(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_cmpge_uint16_m1(r0, r1);
}
inline rvm<uint16_t,2> cmpge(const rvd<uint16_t,2> r0, const rvd<uint16_t,2> r1) {
	return mipp_cmpge_uint16_m2(r0, r1);
}
inline rvm<uint16_t,4> cmpge(const rvd<uint16_t,4> r0, const rvd<uint16_t,4> r1) {
	return mipp_cmpge_uint16_m4(r0, r1);
}
inline rvm<uint16_t,8> cmpge(const rvd<uint16_t,8> r0, const rvd<uint16_t,8> r1) {
	return mipp_cmpge_uint16_m8(r0, r1);
}
inline rvm<uint8_t,1> cmpge(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_cmpge_uint8_m1(r0, r1);
}
inline rvm<uint8_t,2> cmpge(const rvd<uint8_t,2> r0, const rvd<uint8_t,2> r1) {
	return mipp_cmpge_uint8_m2(r0, r1);
}
inline rvm<uint8_t,4> cmpge(const rvd<uint8_t,4> r0, const rvd<uint8_t,4> r1) {
	return mipp_cmpge_uint8_m4(r0, r1);
}
inline rvm<uint8_t,8> cmpge(const rvd<uint8_t,8> r0, const rvd<uint8_t,8> r1) {
	return mipp_cmpge_uint8_m8(r0, r1);
}
inline rvm<float64_t,1> cmpgt(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_cmpgt_float64_m1(r0, r1);
}
inline rvm<float64_t,2> cmpgt(const rvd<float64_t,2> r0, const rvd<float64_t,2> r1) {
	return mipp_cmpgt_float64_m2(r0, r1);
}
inline rvm<float64_t,4> cmpgt(const rvd<float64_t,4> r0, const rvd<float64_t,4> r1) {
	return mipp_cmpgt_float64_m4(r0, r1);
}
inline rvm<float64_t,8> cmpgt(const rvd<float64_t,8> r0, const rvd<float64_t,8> r1) {
	return mipp_cmpgt_float64_m8(r0, r1);
}
inline rvm<float32_t,1> cmpgt(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_cmpgt_float32_m1(r0, r1);
}
inline rvm<float32_t,2> cmpgt(const rvd<float32_t,2> r0, const rvd<float32_t,2> r1) {
	return mipp_cmpgt_float32_m2(r0, r1);
}
inline rvm<float32_t,4> cmpgt(const rvd<float32_t,4> r0, const rvd<float32_t,4> r1) {
	return mipp_cmpgt_float32_m4(r0, r1);
}
inline rvm<float32_t,8> cmpgt(const rvd<float32_t,8> r0, const rvd<float32_t,8> r1) {
	return mipp_cmpgt_float32_m8(r0, r1);
}
inline rvm<int64_t,1> cmpgt(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_cmpgt_int64_m1(r0, r1);
}
inline rvm<int64_t,2> cmpgt(const rvd<int64_t,2> r0, const rvd<int64_t,2> r1) {
	return mipp_cmpgt_int64_m2(r0, r1);
}
inline rvm<int64_t,4> cmpgt(const rvd<int64_t,4> r0, const rvd<int64_t,4> r1) {
	return mipp_cmpgt_int64_m4(r0, r1);
}
inline rvm<int64_t,8> cmpgt(const rvd<int64_t,8> r0, const rvd<int64_t,8> r1) {
	return mipp_cmpgt_int64_m8(r0, r1);
}
inline rvm<int32_t,1> cmpgt(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_cmpgt_int32_m1(r0, r1);
}
inline rvm<int32_t,2> cmpgt(const rvd<int32_t,2> r0, const rvd<int32_t,2> r1) {
	return mipp_cmpgt_int32_m2(r0, r1);
}
inline rvm<int32_t,4> cmpgt(const rvd<int32_t,4> r0, const rvd<int32_t,4> r1) {
	return mipp_cmpgt_int32_m4(r0, r1);
}
inline rvm<int32_t,8> cmpgt(const rvd<int32_t,8> r0, const rvd<int32_t,8> r1) {
	return mipp_cmpgt_int32_m8(r0, r1);
}
inline rvm<int16_t,1> cmpgt(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_cmpgt_int16_m1(r0, r1);
}
inline rvm<int16_t,2> cmpgt(const rvd<int16_t,2> r0, const rvd<int16_t,2> r1) {
	return mipp_cmpgt_int16_m2(r0, r1);
}
inline rvm<int16_t,4> cmpgt(const rvd<int16_t,4> r0, const rvd<int16_t,4> r1) {
	return mipp_cmpgt_int16_m4(r0, r1);
}
inline rvm<int16_t,8> cmpgt(const rvd<int16_t,8> r0, const rvd<int16_t,8> r1) {
	return mipp_cmpgt_int16_m8(r0, r1);
}
inline rvm<int8_t,1> cmpgt(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_cmpgt_int8_m1(r0, r1);
}
inline rvm<int8_t,2> cmpgt(const rvd<int8_t,2> r0, const rvd<int8_t,2> r1) {
	return mipp_cmpgt_int8_m2(r0, r1);
}
inline rvm<int8_t,4> cmpgt(const rvd<int8_t,4> r0, const rvd<int8_t,4> r1) {
	return mipp_cmpgt_int8_m4(r0, r1);
}
inline rvm<int8_t,8> cmpgt(const rvd<int8_t,8> r0, const rvd<int8_t,8> r1) {
	return mipp_cmpgt_int8_m8(r0, r1);
}
inline rvm<uint64_t,1> cmpgt(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_cmpgt_uint64_m1(r0, r1);
}
inline rvm<uint64_t,2> cmpgt(const rvd<uint64_t,2> r0, const rvd<uint64_t,2> r1) {
	return mipp_cmpgt_uint64_m2(r0, r1);
}
inline rvm<uint64_t,4> cmpgt(const rvd<uint64_t,4> r0, const rvd<uint64_t,4> r1) {
	return mipp_cmpgt_uint64_m4(r0, r1);
}
inline rvm<uint64_t,8> cmpgt(const rvd<uint64_t,8> r0, const rvd<uint64_t,8> r1) {
	return mipp_cmpgt_uint64_m8(r0, r1);
}
inline rvm<uint32_t,1> cmpgt(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_cmpgt_uint32_m1(r0, r1);
}
inline rvm<uint32_t,2> cmpgt(const rvd<uint32_t,2> r0, const rvd<uint32_t,2> r1) {
	return mipp_cmpgt_uint32_m2(r0, r1);
}
inline rvm<uint32_t,4> cmpgt(const rvd<uint32_t,4> r0, const rvd<uint32_t,4> r1) {
	return mipp_cmpgt_uint32_m4(r0, r1);
}
inline rvm<uint32_t,8> cmpgt(const rvd<uint32_t,8> r0, const rvd<uint32_t,8> r1) {
	return mipp_cmpgt_uint32_m8(r0, r1);
}
inline rvm<uint16_t,1> cmpgt(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_cmpgt_uint16_m1(r0, r1);
}
inline rvm<uint16_t,2> cmpgt(const rvd<uint16_t,2> r0, const rvd<uint16_t,2> r1) {
	return mipp_cmpgt_uint16_m2(r0, r1);
}
inline rvm<uint16_t,4> cmpgt(const rvd<uint16_t,4> r0, const rvd<uint16_t,4> r1) {
	return mipp_cmpgt_uint16_m4(r0, r1);
}
inline rvm<uint16_t,8> cmpgt(const rvd<uint16_t,8> r0, const rvd<uint16_t,8> r1) {
	return mipp_cmpgt_uint16_m8(r0, r1);
}
inline rvm<uint8_t,1> cmpgt(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_cmpgt_uint8_m1(r0, r1);
}
inline rvm<uint8_t,2> cmpgt(const rvd<uint8_t,2> r0, const rvd<uint8_t,2> r1) {
	return mipp_cmpgt_uint8_m2(r0, r1);
}
inline rvm<uint8_t,4> cmpgt(const rvd<uint8_t,4> r0, const rvd<uint8_t,4> r1) {
	return mipp_cmpgt_uint8_m4(r0, r1);
}
inline rvm<uint8_t,8> cmpgt(const rvd<uint8_t,8> r0, const rvd<uint8_t,8> r1) {
	return mipp_cmpgt_uint8_m8(r0, r1);
}
inline float64_t round(const rvd<float64_t,1> r0) {
	return mipp_round_float64_m1(r0);
}
inline float64_t round(const rvd<float64_t,2> r0) {
	return mipp_round_float64_m2(r0);
}
inline float64_t round(const rvd<float64_t,4> r0) {
	return mipp_round_float64_m4(r0);
}
inline float64_t round(const rvd<float64_t,8> r0) {
	return mipp_round_float64_m8(r0);
}
inline float32_t round(const rvd<float32_t,1> r0) {
	return mipp_round_float32_m1(r0);
}
inline float32_t round(const rvd<float32_t,2> r0) {
	return mipp_round_float32_m2(r0);
}
inline float32_t round(const rvd<float32_t,4> r0) {
	return mipp_round_float32_m4(r0);
}
inline float32_t round(const rvd<float32_t,8> r0) {
	return mipp_round_float32_m8(r0);
}
inline int64_t round(const rvd<int64_t,1> r0) {
	return mipp_round_int64_m1(r0);
}
inline int64_t round(const rvd<int64_t,2> r0) {
	return mipp_round_int64_m2(r0);
}
inline int64_t round(const rvd<int64_t,4> r0) {
	return mipp_round_int64_m4(r0);
}
inline int64_t round(const rvd<int64_t,8> r0) {
	return mipp_round_int64_m8(r0);
}
inline int32_t round(const rvd<int32_t,1> r0) {
	return mipp_round_int32_m1(r0);
}
inline int32_t round(const rvd<int32_t,2> r0) {
	return mipp_round_int32_m2(r0);
}
inline int32_t round(const rvd<int32_t,4> r0) {
	return mipp_round_int32_m4(r0);
}
inline int32_t round(const rvd<int32_t,8> r0) {
	return mipp_round_int32_m8(r0);
}
inline int16_t round(const rvd<int16_t,1> r0) {
	return mipp_round_int16_m1(r0);
}
inline int16_t round(const rvd<int16_t,2> r0) {
	return mipp_round_int16_m2(r0);
}
inline int16_t round(const rvd<int16_t,4> r0) {
	return mipp_round_int16_m4(r0);
}
inline int16_t round(const rvd<int16_t,8> r0) {
	return mipp_round_int16_m8(r0);
}
inline int8_t round(const rvd<int8_t,1> r0) {
	return mipp_round_int8_m1(r0);
}
inline int8_t round(const rvd<int8_t,2> r0) {
	return mipp_round_int8_m2(r0);
}
inline int8_t round(const rvd<int8_t,4> r0) {
	return mipp_round_int8_m4(r0);
}
inline int8_t round(const rvd<int8_t,8> r0) {
	return mipp_round_int8_m8(r0);
}
inline uint64_t round(const rvd<uint64_t,1> r0) {
	return mipp_round_uint64_m1(r0);
}
inline uint64_t round(const rvd<uint64_t,2> r0) {
	return mipp_round_uint64_m2(r0);
}
inline uint64_t round(const rvd<uint64_t,4> r0) {
	return mipp_round_uint64_m4(r0);
}
inline uint64_t round(const rvd<uint64_t,8> r0) {
	return mipp_round_uint64_m8(r0);
}
inline uint32_t round(const rvd<uint32_t,1> r0) {
	return mipp_round_uint32_m1(r0);
}
inline uint32_t round(const rvd<uint32_t,2> r0) {
	return mipp_round_uint32_m2(r0);
}
inline uint32_t round(const rvd<uint32_t,4> r0) {
	return mipp_round_uint32_m4(r0);
}
inline uint32_t round(const rvd<uint32_t,8> r0) {
	return mipp_round_uint32_m8(r0);
}
inline uint16_t round(const rvd<uint16_t,1> r0) {
	return mipp_round_uint16_m1(r0);
}
inline uint16_t round(const rvd<uint16_t,2> r0) {
	return mipp_round_uint16_m2(r0);
}
inline uint16_t round(const rvd<uint16_t,4> r0) {
	return mipp_round_uint16_m4(r0);
}
inline uint16_t round(const rvd<uint16_t,8> r0) {
	return mipp_round_uint16_m8(r0);
}
inline uint8_t round(const rvd<uint8_t,1> r0) {
	return mipp_round_uint8_m1(r0);
}
inline uint8_t round(const rvd<uint8_t,2> r0) {
	return mipp_round_uint8_m2(r0);
}
inline uint8_t round(const rvd<uint8_t,4> r0) {
	return mipp_round_uint8_m4(r0);
}
inline uint8_t round(const rvd<uint8_t,8> r0) {
	return mipp_round_uint8_m8(r0);
}
inline rvd<float64_t,1> blend(const rvd<float64_t,1> r0, const rvd<float64_t,1> r1, const rvm<float64_t,1> m0) {
	return mipp_blend_float64_m1(r0, r1, m0);
}
inline rvd<float64_t,2> blend(const rvd<float64_t,2> r0, const rvd<float64_t,2> r1, const rvm<float64_t,2> m0) {
	return mipp_blend_float64_m2(r0, r1, m0);
}
inline rvd<float64_t,4> blend(const rvd<float64_t,4> r0, const rvd<float64_t,4> r1, const rvm<float64_t,4> m0) {
	return mipp_blend_float64_m4(r0, r1, m0);
}
inline rvd<float64_t,8> blend(const rvd<float64_t,8> r0, const rvd<float64_t,8> r1, const rvm<float64_t,8> m0) {
	return mipp_blend_float64_m8(r0, r1, m0);
}
inline rvd<float32_t,1> blend(const rvd<float32_t,1> r0, const rvd<float32_t,1> r1, const rvm<float32_t,1> m0) {
	return mipp_blend_float32_m1(r0, r1, m0);
}
inline rvd<float32_t,2> blend(const rvd<float32_t,2> r0, const rvd<float32_t,2> r1, const rvm<float32_t,2> m0) {
	return mipp_blend_float32_m2(r0, r1, m0);
}
inline rvd<float32_t,4> blend(const rvd<float32_t,4> r0, const rvd<float32_t,4> r1, const rvm<float32_t,4> m0) {
	return mipp_blend_float32_m4(r0, r1, m0);
}
inline rvd<float32_t,8> blend(const rvd<float32_t,8> r0, const rvd<float32_t,8> r1, const rvm<float32_t,8> m0) {
	return mipp_blend_float32_m8(r0, r1, m0);
}
inline rvd<int64_t,1> blend(const rvd<int64_t,1> r0, const rvd<int64_t,1> r1, const rvm<int64_t,1> m0) {
	return mipp_blend_int64_m1(r0, r1, m0);
}
inline rvd<int64_t,2> blend(const rvd<int64_t,2> r0, const rvd<int64_t,2> r1, const rvm<int64_t,2> m0) {
	return mipp_blend_int64_m2(r0, r1, m0);
}
inline rvd<int64_t,4> blend(const rvd<int64_t,4> r0, const rvd<int64_t,4> r1, const rvm<int64_t,4> m0) {
	return mipp_blend_int64_m4(r0, r1, m0);
}
inline rvd<int64_t,8> blend(const rvd<int64_t,8> r0, const rvd<int64_t,8> r1, const rvm<int64_t,8> m0) {
	return mipp_blend_int64_m8(r0, r1, m0);
}
inline rvd<int32_t,1> blend(const rvd<int32_t,1> r0, const rvd<int32_t,1> r1, const rvm<int32_t,1> m0) {
	return mipp_blend_int32_m1(r0, r1, m0);
}
inline rvd<int32_t,2> blend(const rvd<int32_t,2> r0, const rvd<int32_t,2> r1, const rvm<int32_t,2> m0) {
	return mipp_blend_int32_m2(r0, r1, m0);
}
inline rvd<int32_t,4> blend(const rvd<int32_t,4> r0, const rvd<int32_t,4> r1, const rvm<int32_t,4> m0) {
	return mipp_blend_int32_m4(r0, r1, m0);
}
inline rvd<int32_t,8> blend(const rvd<int32_t,8> r0, const rvd<int32_t,8> r1, const rvm<int32_t,8> m0) {
	return mipp_blend_int32_m8(r0, r1, m0);
}
inline rvd<int16_t,1> blend(const rvd<int16_t,1> r0, const rvd<int16_t,1> r1, const rvm<int16_t,1> m0) {
	return mipp_blend_int16_m1(r0, r1, m0);
}
inline rvd<int16_t,2> blend(const rvd<int16_t,2> r0, const rvd<int16_t,2> r1, const rvm<int16_t,2> m0) {
	return mipp_blend_int16_m2(r0, r1, m0);
}
inline rvd<int16_t,4> blend(const rvd<int16_t,4> r0, const rvd<int16_t,4> r1, const rvm<int16_t,4> m0) {
	return mipp_blend_int16_m4(r0, r1, m0);
}
inline rvd<int16_t,8> blend(const rvd<int16_t,8> r0, const rvd<int16_t,8> r1, const rvm<int16_t,8> m0) {
	return mipp_blend_int16_m8(r0, r1, m0);
}
inline rvd<int8_t,1> blend(const rvd<int8_t,1> r0, const rvd<int8_t,1> r1, const rvm<int8_t,1> m0) {
	return mipp_blend_int8_m1(r0, r1, m0);
}
inline rvd<int8_t,2> blend(const rvd<int8_t,2> r0, const rvd<int8_t,2> r1, const rvm<int8_t,2> m0) {
	return mipp_blend_int8_m2(r0, r1, m0);
}
inline rvd<int8_t,4> blend(const rvd<int8_t,4> r0, const rvd<int8_t,4> r1, const rvm<int8_t,4> m0) {
	return mipp_blend_int8_m4(r0, r1, m0);
}
inline rvd<int8_t,8> blend(const rvd<int8_t,8> r0, const rvd<int8_t,8> r1, const rvm<int8_t,8> m0) {
	return mipp_blend_int8_m8(r0, r1, m0);
}
inline rvd<uint64_t,1> blend(const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1, const rvm<uint64_t,1> m0) {
	return mipp_blend_uint64_m1(r0, r1, m0);
}
inline rvd<uint64_t,2> blend(const rvd<uint64_t,2> r0, const rvd<uint64_t,2> r1, const rvm<uint64_t,2> m0) {
	return mipp_blend_uint64_m2(r0, r1, m0);
}
inline rvd<uint64_t,4> blend(const rvd<uint64_t,4> r0, const rvd<uint64_t,4> r1, const rvm<uint64_t,4> m0) {
	return mipp_blend_uint64_m4(r0, r1, m0);
}
inline rvd<uint64_t,8> blend(const rvd<uint64_t,8> r0, const rvd<uint64_t,8> r1, const rvm<uint64_t,8> m0) {
	return mipp_blend_uint64_m8(r0, r1, m0);
}
inline rvd<uint32_t,1> blend(const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1, const rvm<uint32_t,1> m0) {
	return mipp_blend_uint32_m1(r0, r1, m0);
}
inline rvd<uint32_t,2> blend(const rvd<uint32_t,2> r0, const rvd<uint32_t,2> r1, const rvm<uint32_t,2> m0) {
	return mipp_blend_uint32_m2(r0, r1, m0);
}
inline rvd<uint32_t,4> blend(const rvd<uint32_t,4> r0, const rvd<uint32_t,4> r1, const rvm<uint32_t,4> m0) {
	return mipp_blend_uint32_m4(r0, r1, m0);
}
inline rvd<uint32_t,8> blend(const rvd<uint32_t,8> r0, const rvd<uint32_t,8> r1, const rvm<uint32_t,8> m0) {
	return mipp_blend_uint32_m8(r0, r1, m0);
}
inline rvd<uint16_t,1> blend(const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1, const rvm<uint16_t,1> m0) {
	return mipp_blend_uint16_m1(r0, r1, m0);
}
inline rvd<uint16_t,2> blend(const rvd<uint16_t,2> r0, const rvd<uint16_t,2> r1, const rvm<uint16_t,2> m0) {
	return mipp_blend_uint16_m2(r0, r1, m0);
}
inline rvd<uint16_t,4> blend(const rvd<uint16_t,4> r0, const rvd<uint16_t,4> r1, const rvm<uint16_t,4> m0) {
	return mipp_blend_uint16_m4(r0, r1, m0);
}
inline rvd<uint16_t,8> blend(const rvd<uint16_t,8> r0, const rvd<uint16_t,8> r1, const rvm<uint16_t,8> m0) {
	return mipp_blend_uint16_m8(r0, r1, m0);
}
inline rvd<uint8_t,1> blend(const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1, const rvm<uint8_t,1> m0) {
	return mipp_blend_uint8_m1(r0, r1, m0);
}
inline rvd<uint8_t,2> blend(const rvd<uint8_t,2> r0, const rvd<uint8_t,2> r1, const rvm<uint8_t,2> m0) {
	return mipp_blend_uint8_m2(r0, r1, m0);
}
inline rvd<uint8_t,4> blend(const rvd<uint8_t,4> r0, const rvd<uint8_t,4> r1, const rvm<uint8_t,4> m0) {
	return mipp_blend_uint8_m4(r0, r1, m0);
}
inline rvd<uint8_t,8> blend(const rvd<uint8_t,8> r0, const rvd<uint8_t,8> r1, const rvm<uint8_t,8> m0) {
	return mipp_blend_uint8_m8(r0, r1, m0);
}
inline int32_t testz(const rvm<float64_t,1> m0, const rvm<float64_t,1> m1) {
	return mipp_testz_float64_m1(m0, m1);
}
inline int32_t testz(const rvm<float64_t,2> m0, const rvm<float64_t,2> m1) {
	return mipp_testz_float64_m2(m0, m1);
}
inline int32_t testz(const rvm<float64_t,4> m0, const rvm<float64_t,4> m1) {
	return mipp_testz_float64_m4(m0, m1);
}
inline int32_t testz(const rvm<float64_t,8> m0, const rvm<float64_t,8> m1) {
	return mipp_testz_float64_m8(m0, m1);
}
inline int32_t testz(const rvm<float32_t,1> m0, const rvm<float32_t,1> m1) {
	return mipp_testz_float32_m1(m0, m1);
}
inline int32_t testz(const rvm<float32_t,2> m0, const rvm<float32_t,2> m1) {
	return mipp_testz_float32_m2(m0, m1);
}
inline int32_t testz(const rvm<float32_t,4> m0, const rvm<float32_t,4> m1) {
	return mipp_testz_float32_m4(m0, m1);
}
inline int32_t testz(const rvm<float32_t,8> m0, const rvm<float32_t,8> m1) {
	return mipp_testz_float32_m8(m0, m1);
}
inline int32_t testz(const rvm<int64_t,1> m0, const rvm<int64_t,1> m1) {
	return mipp_testz_int64_m1(m0, m1);
}
inline int32_t testz(const rvm<int64_t,2> m0, const rvm<int64_t,2> m1) {
	return mipp_testz_int64_m2(m0, m1);
}
inline int32_t testz(const rvm<int64_t,4> m0, const rvm<int64_t,4> m1) {
	return mipp_testz_int64_m4(m0, m1);
}
inline int32_t testz(const rvm<int64_t,8> m0, const rvm<int64_t,8> m1) {
	return mipp_testz_int64_m8(m0, m1);
}
inline int32_t testz(const rvm<int32_t,1> m0, const rvm<int32_t,1> m1) {
	return mipp_testz_int32_m1(m0, m1);
}
inline int32_t testz(const rvm<int32_t,2> m0, const rvm<int32_t,2> m1) {
	return mipp_testz_int32_m2(m0, m1);
}
inline int32_t testz(const rvm<int32_t,4> m0, const rvm<int32_t,4> m1) {
	return mipp_testz_int32_m4(m0, m1);
}
inline int32_t testz(const rvm<int32_t,8> m0, const rvm<int32_t,8> m1) {
	return mipp_testz_int32_m8(m0, m1);
}
inline int32_t testz(const rvm<int16_t,1> m0, const rvm<int16_t,1> m1) {
	return mipp_testz_int16_m1(m0, m1);
}
inline int32_t testz(const rvm<int16_t,2> m0, const rvm<int16_t,2> m1) {
	return mipp_testz_int16_m2(m0, m1);
}
inline int32_t testz(const rvm<int16_t,4> m0, const rvm<int16_t,4> m1) {
	return mipp_testz_int16_m4(m0, m1);
}
inline int32_t testz(const rvm<int16_t,8> m0, const rvm<int16_t,8> m1) {
	return mipp_testz_int16_m8(m0, m1);
}
inline int32_t testz(const rvm<int8_t,1> m0, const rvm<int8_t,1> m1) {
	return mipp_testz_int8_m1(m0, m1);
}
inline int32_t testz(const rvm<int8_t,2> m0, const rvm<int8_t,2> m1) {
	return mipp_testz_int8_m2(m0, m1);
}
inline int32_t testz(const rvm<int8_t,4> m0, const rvm<int8_t,4> m1) {
	return mipp_testz_int8_m4(m0, m1);
}
inline int32_t testz(const rvm<int8_t,8> m0, const rvm<int8_t,8> m1) {
	return mipp_testz_int8_m8(m0, m1);
}
inline int32_t testz(const rvm<uint64_t,1> m0, const rvm<uint64_t,1> m1) {
	return mipp_testz_uint64_m1(m0, m1);
}
inline int32_t testz(const rvm<uint64_t,2> m0, const rvm<uint64_t,2> m1) {
	return mipp_testz_uint64_m2(m0, m1);
}
inline int32_t testz(const rvm<uint64_t,4> m0, const rvm<uint64_t,4> m1) {
	return mipp_testz_uint64_m4(m0, m1);
}
inline int32_t testz(const rvm<uint64_t,8> m0, const rvm<uint64_t,8> m1) {
	return mipp_testz_uint64_m8(m0, m1);
}
inline int32_t testz(const rvm<uint32_t,1> m0, const rvm<uint32_t,1> m1) {
	return mipp_testz_uint32_m1(m0, m1);
}
inline int32_t testz(const rvm<uint32_t,2> m0, const rvm<uint32_t,2> m1) {
	return mipp_testz_uint32_m2(m0, m1);
}
inline int32_t testz(const rvm<uint32_t,4> m0, const rvm<uint32_t,4> m1) {
	return mipp_testz_uint32_m4(m0, m1);
}
inline int32_t testz(const rvm<uint32_t,8> m0, const rvm<uint32_t,8> m1) {
	return mipp_testz_uint32_m8(m0, m1);
}
inline int32_t testz(const rvm<uint16_t,1> m0, const rvm<uint16_t,1> m1) {
	return mipp_testz_uint16_m1(m0, m1);
}
inline int32_t testz(const rvm<uint16_t,2> m0, const rvm<uint16_t,2> m1) {
	return mipp_testz_uint16_m2(m0, m1);
}
inline int32_t testz(const rvm<uint16_t,4> m0, const rvm<uint16_t,4> m1) {
	return mipp_testz_uint16_m4(m0, m1);
}
inline int32_t testz(const rvm<uint16_t,8> m0, const rvm<uint16_t,8> m1) {
	return mipp_testz_uint16_m8(m0, m1);
}
inline int32_t testz(const rvm<uint8_t,1> m0, const rvm<uint8_t,1> m1) {
	return mipp_testz_uint8_m1(m0, m1);
}
inline int32_t testz(const rvm<uint8_t,2> m0, const rvm<uint8_t,2> m1) {
	return mipp_testz_uint8_m2(m0, m1);
}
inline int32_t testz(const rvm<uint8_t,4> m0, const rvm<uint8_t,4> m1) {
	return mipp_testz_uint8_m4(m0, m1);
}
inline int32_t testz(const rvm<uint8_t,8> m0, const rvm<uint8_t,8> m1) {
	return mipp_testz_uint8_m8(m0, m1);
}
inline int32_t testz_2(const rvm<float64_t,1> m0) {
	return mipp_testz_2_float64_m1(m0);
}
inline int32_t testz_2(const rvm<float64_t,2> m0) {
	return mipp_testz_2_float64_m2(m0);
}
inline int32_t testz_2(const rvm<float64_t,4> m0) {
	return mipp_testz_2_float64_m4(m0);
}
inline int32_t testz_2(const rvm<float64_t,8> m0) {
	return mipp_testz_2_float64_m8(m0);
}
inline int32_t testz_2(const rvm<float32_t,1> m0) {
	return mipp_testz_2_float32_m1(m0);
}
inline int32_t testz_2(const rvm<float32_t,2> m0) {
	return mipp_testz_2_float32_m2(m0);
}
inline int32_t testz_2(const rvm<float32_t,4> m0) {
	return mipp_testz_2_float32_m4(m0);
}
inline int32_t testz_2(const rvm<float32_t,8> m0) {
	return mipp_testz_2_float32_m8(m0);
}
inline int32_t testz_2(const rvm<int64_t,1> m0) {
	return mipp_testz_2_int64_m1(m0);
}
inline int32_t testz_2(const rvm<int64_t,2> m0) {
	return mipp_testz_2_int64_m2(m0);
}
inline int32_t testz_2(const rvm<int64_t,4> m0) {
	return mipp_testz_2_int64_m4(m0);
}
inline int32_t testz_2(const rvm<int64_t,8> m0) {
	return mipp_testz_2_int64_m8(m0);
}
inline int32_t testz_2(const rvm<int32_t,1> m0) {
	return mipp_testz_2_int32_m1(m0);
}
inline int32_t testz_2(const rvm<int32_t,2> m0) {
	return mipp_testz_2_int32_m2(m0);
}
inline int32_t testz_2(const rvm<int32_t,4> m0) {
	return mipp_testz_2_int32_m4(m0);
}
inline int32_t testz_2(const rvm<int32_t,8> m0) {
	return mipp_testz_2_int32_m8(m0);
}
inline int32_t testz_2(const rvm<int16_t,1> m0) {
	return mipp_testz_2_int16_m1(m0);
}
inline int32_t testz_2(const rvm<int16_t,2> m0) {
	return mipp_testz_2_int16_m2(m0);
}
inline int32_t testz_2(const rvm<int16_t,4> m0) {
	return mipp_testz_2_int16_m4(m0);
}
inline int32_t testz_2(const rvm<int16_t,8> m0) {
	return mipp_testz_2_int16_m8(m0);
}
inline int32_t testz_2(const rvm<int8_t,1> m0) {
	return mipp_testz_2_int8_m1(m0);
}
inline int32_t testz_2(const rvm<int8_t,2> m0) {
	return mipp_testz_2_int8_m2(m0);
}
inline int32_t testz_2(const rvm<int8_t,4> m0) {
	return mipp_testz_2_int8_m4(m0);
}
inline int32_t testz_2(const rvm<int8_t,8> m0) {
	return mipp_testz_2_int8_m8(m0);
}
inline int32_t testz_2(const rvm<uint64_t,1> m0) {
	return mipp_testz_2_uint64_m1(m0);
}
inline int32_t testz_2(const rvm<uint64_t,2> m0) {
	return mipp_testz_2_uint64_m2(m0);
}
inline int32_t testz_2(const rvm<uint64_t,4> m0) {
	return mipp_testz_2_uint64_m4(m0);
}
inline int32_t testz_2(const rvm<uint64_t,8> m0) {
	return mipp_testz_2_uint64_m8(m0);
}
inline int32_t testz_2(const rvm<uint32_t,1> m0) {
	return mipp_testz_2_uint32_m1(m0);
}
inline int32_t testz_2(const rvm<uint32_t,2> m0) {
	return mipp_testz_2_uint32_m2(m0);
}
inline int32_t testz_2(const rvm<uint32_t,4> m0) {
	return mipp_testz_2_uint32_m4(m0);
}
inline int32_t testz_2(const rvm<uint32_t,8> m0) {
	return mipp_testz_2_uint32_m8(m0);
}
inline int32_t testz_2(const rvm<uint16_t,1> m0) {
	return mipp_testz_2_uint16_m1(m0);
}
inline int32_t testz_2(const rvm<uint16_t,2> m0) {
	return mipp_testz_2_uint16_m2(m0);
}
inline int32_t testz_2(const rvm<uint16_t,4> m0) {
	return mipp_testz_2_uint16_m4(m0);
}
inline int32_t testz_2(const rvm<uint16_t,8> m0) {
	return mipp_testz_2_uint16_m8(m0);
}
inline int32_t testz_2(const rvm<uint8_t,1> m0) {
	return mipp_testz_2_uint8_m1(m0);
}
inline int32_t testz_2(const rvm<uint8_t,2> m0) {
	return mipp_testz_2_uint8_m2(m0);
}
inline int32_t testz_2(const rvm<uint8_t,4> m0) {
	return mipp_testz_2_uint8_m4(m0);
}
inline int32_t testz_2(const rvm<uint8_t,8> m0) {
	return mipp_testz_2_uint8_m8(m0);
}
inline rvd<float64_t,1> hadd(const rvd<float64_t,1> r0) {
	return mipp_hadd_float64_m1(r0);
}
inline rvd<float64_t,2> hadd(const rvd<float64_t,2> r0) {
	return mipp_hadd_float64_m2(r0);
}
inline rvd<float64_t,4> hadd(const rvd<float64_t,4> r0) {
	return mipp_hadd_float64_m4(r0);
}
inline rvd<float64_t,8> hadd(const rvd<float64_t,8> r0) {
	return mipp_hadd_float64_m8(r0);
}
inline rvd<float32_t,1> hadd(const rvd<float32_t,1> r0) {
	return mipp_hadd_float32_m1(r0);
}
inline rvd<float32_t,2> hadd(const rvd<float32_t,2> r0) {
	return mipp_hadd_float32_m2(r0);
}
inline rvd<float32_t,4> hadd(const rvd<float32_t,4> r0) {
	return mipp_hadd_float32_m4(r0);
}
inline rvd<float32_t,8> hadd(const rvd<float32_t,8> r0) {
	return mipp_hadd_float32_m8(r0);
}
inline rvd<int64_t,1> hadd(const rvd<int64_t,1> r0) {
	return mipp_hadd_int64_m1(r0);
}
inline rvd<int64_t,2> hadd(const rvd<int64_t,2> r0) {
	return mipp_hadd_int64_m2(r0);
}
inline rvd<int64_t,4> hadd(const rvd<int64_t,4> r0) {
	return mipp_hadd_int64_m4(r0);
}
inline rvd<int64_t,8> hadd(const rvd<int64_t,8> r0) {
	return mipp_hadd_int64_m8(r0);
}
inline rvd<int32_t,1> hadd(const rvd<int32_t,1> r0) {
	return mipp_hadd_int32_m1(r0);
}
inline rvd<int32_t,2> hadd(const rvd<int32_t,2> r0) {
	return mipp_hadd_int32_m2(r0);
}
inline rvd<int32_t,4> hadd(const rvd<int32_t,4> r0) {
	return mipp_hadd_int32_m4(r0);
}
inline rvd<int32_t,8> hadd(const rvd<int32_t,8> r0) {
	return mipp_hadd_int32_m8(r0);
}
inline rvd<int16_t,1> hadd(const rvd<int16_t,1> r0) {
	return mipp_hadd_int16_m1(r0);
}
inline rvd<int16_t,2> hadd(const rvd<int16_t,2> r0) {
	return mipp_hadd_int16_m2(r0);
}
inline rvd<int16_t,4> hadd(const rvd<int16_t,4> r0) {
	return mipp_hadd_int16_m4(r0);
}
inline rvd<int16_t,8> hadd(const rvd<int16_t,8> r0) {
	return mipp_hadd_int16_m8(r0);
}
inline rvd<int8_t,1> hadd(const rvd<int8_t,1> r0) {
	return mipp_hadd_int8_m1(r0);
}
inline rvd<int8_t,2> hadd(const rvd<int8_t,2> r0) {
	return mipp_hadd_int8_m2(r0);
}
inline rvd<int8_t,4> hadd(const rvd<int8_t,4> r0) {
	return mipp_hadd_int8_m4(r0);
}
inline rvd<int8_t,8> hadd(const rvd<int8_t,8> r0) {
	return mipp_hadd_int8_m8(r0);
}
inline rvd<uint64_t,1> hadd(const rvd<uint64_t,1> r0) {
	return mipp_hadd_uint64_m1(r0);
}
inline rvd<uint64_t,2> hadd(const rvd<uint64_t,2> r0) {
	return mipp_hadd_uint64_m2(r0);
}
inline rvd<uint64_t,4> hadd(const rvd<uint64_t,4> r0) {
	return mipp_hadd_uint64_m4(r0);
}
inline rvd<uint64_t,8> hadd(const rvd<uint64_t,8> r0) {
	return mipp_hadd_uint64_m8(r0);
}
inline rvd<uint32_t,1> hadd(const rvd<uint32_t,1> r0) {
	return mipp_hadd_uint32_m1(r0);
}
inline rvd<uint32_t,2> hadd(const rvd<uint32_t,2> r0) {
	return mipp_hadd_uint32_m2(r0);
}
inline rvd<uint32_t,4> hadd(const rvd<uint32_t,4> r0) {
	return mipp_hadd_uint32_m4(r0);
}
inline rvd<uint32_t,8> hadd(const rvd<uint32_t,8> r0) {
	return mipp_hadd_uint32_m8(r0);
}
inline rvd<uint16_t,1> hadd(const rvd<uint16_t,1> r0) {
	return mipp_hadd_uint16_m1(r0);
}
inline rvd<uint16_t,2> hadd(const rvd<uint16_t,2> r0) {
	return mipp_hadd_uint16_m2(r0);
}
inline rvd<uint16_t,4> hadd(const rvd<uint16_t,4> r0) {
	return mipp_hadd_uint16_m4(r0);
}
inline rvd<uint16_t,8> hadd(const rvd<uint16_t,8> r0) {
	return mipp_hadd_uint16_m8(r0);
}
inline rvd<uint8_t,1> hadd(const rvd<uint8_t,1> r0) {
	return mipp_hadd_uint8_m1(r0);
}
inline rvd<uint8_t,2> hadd(const rvd<uint8_t,2> r0) {
	return mipp_hadd_uint8_m2(r0);
}
inline rvd<uint8_t,4> hadd(const rvd<uint8_t,4> r0) {
	return mipp_hadd_uint8_m4(r0);
}
inline rvd<uint8_t,8> hadd(const rvd<uint8_t,8> r0) {
	return mipp_hadd_uint8_m8(r0);
}
inline rvd<float64_t,1> hmul(const rvd<float64_t,1> r0) {
	return mipp_hmul_float64_m1(r0);
}
inline rvd<float64_t,2> hmul(const rvd<float64_t,2> r0) {
	return mipp_hmul_float64_m2(r0);
}
inline rvd<float64_t,4> hmul(const rvd<float64_t,4> r0) {
	return mipp_hmul_float64_m4(r0);
}
inline rvd<float64_t,8> hmul(const rvd<float64_t,8> r0) {
	return mipp_hmul_float64_m8(r0);
}
inline rvd<float32_t,1> hmul(const rvd<float32_t,1> r0) {
	return mipp_hmul_float32_m1(r0);
}
inline rvd<float32_t,2> hmul(const rvd<float32_t,2> r0) {
	return mipp_hmul_float32_m2(r0);
}
inline rvd<float32_t,4> hmul(const rvd<float32_t,4> r0) {
	return mipp_hmul_float32_m4(r0);
}
inline rvd<float32_t,8> hmul(const rvd<float32_t,8> r0) {
	return mipp_hmul_float32_m8(r0);
}
inline rvd<int64_t,1> hmul(const rvd<int64_t,1> r0) {
	return mipp_hmul_int64_m1(r0);
}
inline rvd<int64_t,2> hmul(const rvd<int64_t,2> r0) {
	return mipp_hmul_int64_m2(r0);
}
inline rvd<int64_t,4> hmul(const rvd<int64_t,4> r0) {
	return mipp_hmul_int64_m4(r0);
}
inline rvd<int64_t,8> hmul(const rvd<int64_t,8> r0) {
	return mipp_hmul_int64_m8(r0);
}
inline rvd<int32_t,1> hmul(const rvd<int32_t,1> r0) {
	return mipp_hmul_int32_m1(r0);
}
inline rvd<int32_t,2> hmul(const rvd<int32_t,2> r0) {
	return mipp_hmul_int32_m2(r0);
}
inline rvd<int32_t,4> hmul(const rvd<int32_t,4> r0) {
	return mipp_hmul_int32_m4(r0);
}
inline rvd<int32_t,8> hmul(const rvd<int32_t,8> r0) {
	return mipp_hmul_int32_m8(r0);
}
inline rvd<int16_t,1> hmul(const rvd<int16_t,1> r0) {
	return mipp_hmul_int16_m1(r0);
}
inline rvd<int16_t,2> hmul(const rvd<int16_t,2> r0) {
	return mipp_hmul_int16_m2(r0);
}
inline rvd<int16_t,4> hmul(const rvd<int16_t,4> r0) {
	return mipp_hmul_int16_m4(r0);
}
inline rvd<int16_t,8> hmul(const rvd<int16_t,8> r0) {
	return mipp_hmul_int16_m8(r0);
}
inline rvd<int8_t,1> hmul(const rvd<int8_t,1> r0) {
	return mipp_hmul_int8_m1(r0);
}
inline rvd<int8_t,2> hmul(const rvd<int8_t,2> r0) {
	return mipp_hmul_int8_m2(r0);
}
inline rvd<int8_t,4> hmul(const rvd<int8_t,4> r0) {
	return mipp_hmul_int8_m4(r0);
}
inline rvd<int8_t,8> hmul(const rvd<int8_t,8> r0) {
	return mipp_hmul_int8_m8(r0);
}
inline rvd<uint64_t,1> hmul(const rvd<uint64_t,1> r0) {
	return mipp_hmul_uint64_m1(r0);
}
inline rvd<uint64_t,2> hmul(const rvd<uint64_t,2> r0) {
	return mipp_hmul_uint64_m2(r0);
}
inline rvd<uint64_t,4> hmul(const rvd<uint64_t,4> r0) {
	return mipp_hmul_uint64_m4(r0);
}
inline rvd<uint64_t,8> hmul(const rvd<uint64_t,8> r0) {
	return mipp_hmul_uint64_m8(r0);
}
inline rvd<uint32_t,1> hmul(const rvd<uint32_t,1> r0) {
	return mipp_hmul_uint32_m1(r0);
}
inline rvd<uint32_t,2> hmul(const rvd<uint32_t,2> r0) {
	return mipp_hmul_uint32_m2(r0);
}
inline rvd<uint32_t,4> hmul(const rvd<uint32_t,4> r0) {
	return mipp_hmul_uint32_m4(r0);
}
inline rvd<uint32_t,8> hmul(const rvd<uint32_t,8> r0) {
	return mipp_hmul_uint32_m8(r0);
}
inline rvd<uint16_t,1> hmul(const rvd<uint16_t,1> r0) {
	return mipp_hmul_uint16_m1(r0);
}
inline rvd<uint16_t,2> hmul(const rvd<uint16_t,2> r0) {
	return mipp_hmul_uint16_m2(r0);
}
inline rvd<uint16_t,4> hmul(const rvd<uint16_t,4> r0) {
	return mipp_hmul_uint16_m4(r0);
}
inline rvd<uint16_t,8> hmul(const rvd<uint16_t,8> r0) {
	return mipp_hmul_uint16_m8(r0);
}
inline rvd<uint8_t,1> hmul(const rvd<uint8_t,1> r0) {
	return mipp_hmul_uint8_m1(r0);
}
inline rvd<uint8_t,2> hmul(const rvd<uint8_t,2> r0) {
	return mipp_hmul_uint8_m2(r0);
}
inline rvd<uint8_t,4> hmul(const rvd<uint8_t,4> r0) {
	return mipp_hmul_uint8_m4(r0);
}
inline rvd<uint8_t,8> hmul(const rvd<uint8_t,8> r0) {
	return mipp_hmul_uint8_m8(r0);
}
inline rvd<float64_t,1> hmin(const rvd<float64_t,1> r0) {
	return mipp_hmin_float64_m1(r0);
}
inline rvd<float64_t,2> hmin(const rvd<float64_t,2> r0) {
	return mipp_hmin_float64_m2(r0);
}
inline rvd<float64_t,4> hmin(const rvd<float64_t,4> r0) {
	return mipp_hmin_float64_m4(r0);
}
inline rvd<float64_t,8> hmin(const rvd<float64_t,8> r0) {
	return mipp_hmin_float64_m8(r0);
}
inline rvd<float32_t,1> hmin(const rvd<float32_t,1> r0) {
	return mipp_hmin_float32_m1(r0);
}
inline rvd<float32_t,2> hmin(const rvd<float32_t,2> r0) {
	return mipp_hmin_float32_m2(r0);
}
inline rvd<float32_t,4> hmin(const rvd<float32_t,4> r0) {
	return mipp_hmin_float32_m4(r0);
}
inline rvd<float32_t,8> hmin(const rvd<float32_t,8> r0) {
	return mipp_hmin_float32_m8(r0);
}
inline rvd<int64_t,1> hmin(const rvd<int64_t,1> r0) {
	return mipp_hmin_int64_m1(r0);
}
inline rvd<int64_t,2> hmin(const rvd<int64_t,2> r0) {
	return mipp_hmin_int64_m2(r0);
}
inline rvd<int64_t,4> hmin(const rvd<int64_t,4> r0) {
	return mipp_hmin_int64_m4(r0);
}
inline rvd<int64_t,8> hmin(const rvd<int64_t,8> r0) {
	return mipp_hmin_int64_m8(r0);
}
inline rvd<int32_t,1> hmin(const rvd<int32_t,1> r0) {
	return mipp_hmin_int32_m1(r0);
}
inline rvd<int32_t,2> hmin(const rvd<int32_t,2> r0) {
	return mipp_hmin_int32_m2(r0);
}
inline rvd<int32_t,4> hmin(const rvd<int32_t,4> r0) {
	return mipp_hmin_int32_m4(r0);
}
inline rvd<int32_t,8> hmin(const rvd<int32_t,8> r0) {
	return mipp_hmin_int32_m8(r0);
}
inline rvd<int16_t,1> hmin(const rvd<int16_t,1> r0) {
	return mipp_hmin_int16_m1(r0);
}
inline rvd<int16_t,2> hmin(const rvd<int16_t,2> r0) {
	return mipp_hmin_int16_m2(r0);
}
inline rvd<int16_t,4> hmin(const rvd<int16_t,4> r0) {
	return mipp_hmin_int16_m4(r0);
}
inline rvd<int16_t,8> hmin(const rvd<int16_t,8> r0) {
	return mipp_hmin_int16_m8(r0);
}
inline rvd<int8_t,1> hmin(const rvd<int8_t,1> r0) {
	return mipp_hmin_int8_m1(r0);
}
inline rvd<int8_t,2> hmin(const rvd<int8_t,2> r0) {
	return mipp_hmin_int8_m2(r0);
}
inline rvd<int8_t,4> hmin(const rvd<int8_t,4> r0) {
	return mipp_hmin_int8_m4(r0);
}
inline rvd<int8_t,8> hmin(const rvd<int8_t,8> r0) {
	return mipp_hmin_int8_m8(r0);
}
inline rvd<uint64_t,1> hmin(const rvd<uint64_t,1> r0) {
	return mipp_hmin_uint64_m1(r0);
}
inline rvd<uint64_t,2> hmin(const rvd<uint64_t,2> r0) {
	return mipp_hmin_uint64_m2(r0);
}
inline rvd<uint64_t,4> hmin(const rvd<uint64_t,4> r0) {
	return mipp_hmin_uint64_m4(r0);
}
inline rvd<uint64_t,8> hmin(const rvd<uint64_t,8> r0) {
	return mipp_hmin_uint64_m8(r0);
}
inline rvd<uint32_t,1> hmin(const rvd<uint32_t,1> r0) {
	return mipp_hmin_uint32_m1(r0);
}
inline rvd<uint32_t,2> hmin(const rvd<uint32_t,2> r0) {
	return mipp_hmin_uint32_m2(r0);
}
inline rvd<uint32_t,4> hmin(const rvd<uint32_t,4> r0) {
	return mipp_hmin_uint32_m4(r0);
}
inline rvd<uint32_t,8> hmin(const rvd<uint32_t,8> r0) {
	return mipp_hmin_uint32_m8(r0);
}
inline rvd<uint16_t,1> hmin(const rvd<uint16_t,1> r0) {
	return mipp_hmin_uint16_m1(r0);
}
inline rvd<uint16_t,2> hmin(const rvd<uint16_t,2> r0) {
	return mipp_hmin_uint16_m2(r0);
}
inline rvd<uint16_t,4> hmin(const rvd<uint16_t,4> r0) {
	return mipp_hmin_uint16_m4(r0);
}
inline rvd<uint16_t,8> hmin(const rvd<uint16_t,8> r0) {
	return mipp_hmin_uint16_m8(r0);
}
inline rvd<uint8_t,1> hmin(const rvd<uint8_t,1> r0) {
	return mipp_hmin_uint8_m1(r0);
}
inline rvd<uint8_t,2> hmin(const rvd<uint8_t,2> r0) {
	return mipp_hmin_uint8_m2(r0);
}
inline rvd<uint8_t,4> hmin(const rvd<uint8_t,4> r0) {
	return mipp_hmin_uint8_m4(r0);
}
inline rvd<uint8_t,8> hmin(const rvd<uint8_t,8> r0) {
	return mipp_hmin_uint8_m8(r0);
}
inline rvd<float64_t,1> hmax(const rvd<float64_t,1> r0) {
	return mipp_hmax_float64_m1(r0);
}
inline rvd<float64_t,2> hmax(const rvd<float64_t,2> r0) {
	return mipp_hmax_float64_m2(r0);
}
inline rvd<float64_t,4> hmax(const rvd<float64_t,4> r0) {
	return mipp_hmax_float64_m4(r0);
}
inline rvd<float64_t,8> hmax(const rvd<float64_t,8> r0) {
	return mipp_hmax_float64_m8(r0);
}
inline rvd<float32_t,1> hmax(const rvd<float32_t,1> r0) {
	return mipp_hmax_float32_m1(r0);
}
inline rvd<float32_t,2> hmax(const rvd<float32_t,2> r0) {
	return mipp_hmax_float32_m2(r0);
}
inline rvd<float32_t,4> hmax(const rvd<float32_t,4> r0) {
	return mipp_hmax_float32_m4(r0);
}
inline rvd<float32_t,8> hmax(const rvd<float32_t,8> r0) {
	return mipp_hmax_float32_m8(r0);
}
inline rvd<int64_t,1> hmax(const rvd<int64_t,1> r0) {
	return mipp_hmax_int64_m1(r0);
}
inline rvd<int64_t,2> hmax(const rvd<int64_t,2> r0) {
	return mipp_hmax_int64_m2(r0);
}
inline rvd<int64_t,4> hmax(const rvd<int64_t,4> r0) {
	return mipp_hmax_int64_m4(r0);
}
inline rvd<int64_t,8> hmax(const rvd<int64_t,8> r0) {
	return mipp_hmax_int64_m8(r0);
}
inline rvd<int32_t,1> hmax(const rvd<int32_t,1> r0) {
	return mipp_hmax_int32_m1(r0);
}
inline rvd<int32_t,2> hmax(const rvd<int32_t,2> r0) {
	return mipp_hmax_int32_m2(r0);
}
inline rvd<int32_t,4> hmax(const rvd<int32_t,4> r0) {
	return mipp_hmax_int32_m4(r0);
}
inline rvd<int32_t,8> hmax(const rvd<int32_t,8> r0) {
	return mipp_hmax_int32_m8(r0);
}
inline rvd<int16_t,1> hmax(const rvd<int16_t,1> r0) {
	return mipp_hmax_int16_m1(r0);
}
inline rvd<int16_t,2> hmax(const rvd<int16_t,2> r0) {
	return mipp_hmax_int16_m2(r0);
}
inline rvd<int16_t,4> hmax(const rvd<int16_t,4> r0) {
	return mipp_hmax_int16_m4(r0);
}
inline rvd<int16_t,8> hmax(const rvd<int16_t,8> r0) {
	return mipp_hmax_int16_m8(r0);
}
inline rvd<int8_t,1> hmax(const rvd<int8_t,1> r0) {
	return mipp_hmax_int8_m1(r0);
}
inline rvd<int8_t,2> hmax(const rvd<int8_t,2> r0) {
	return mipp_hmax_int8_m2(r0);
}
inline rvd<int8_t,4> hmax(const rvd<int8_t,4> r0) {
	return mipp_hmax_int8_m4(r0);
}
inline rvd<int8_t,8> hmax(const rvd<int8_t,8> r0) {
	return mipp_hmax_int8_m8(r0);
}
inline rvd<uint64_t,1> hmax(const rvd<uint64_t,1> r0) {
	return mipp_hmax_uint64_m1(r0);
}
inline rvd<uint64_t,2> hmax(const rvd<uint64_t,2> r0) {
	return mipp_hmax_uint64_m2(r0);
}
inline rvd<uint64_t,4> hmax(const rvd<uint64_t,4> r0) {
	return mipp_hmax_uint64_m4(r0);
}
inline rvd<uint64_t,8> hmax(const rvd<uint64_t,8> r0) {
	return mipp_hmax_uint64_m8(r0);
}
inline rvd<uint32_t,1> hmax(const rvd<uint32_t,1> r0) {
	return mipp_hmax_uint32_m1(r0);
}
inline rvd<uint32_t,2> hmax(const rvd<uint32_t,2> r0) {
	return mipp_hmax_uint32_m2(r0);
}
inline rvd<uint32_t,4> hmax(const rvd<uint32_t,4> r0) {
	return mipp_hmax_uint32_m4(r0);
}
inline rvd<uint32_t,8> hmax(const rvd<uint32_t,8> r0) {
	return mipp_hmax_uint32_m8(r0);
}
inline rvd<uint16_t,1> hmax(const rvd<uint16_t,1> r0) {
	return mipp_hmax_uint16_m1(r0);
}
inline rvd<uint16_t,2> hmax(const rvd<uint16_t,2> r0) {
	return mipp_hmax_uint16_m2(r0);
}
inline rvd<uint16_t,4> hmax(const rvd<uint16_t,4> r0) {
	return mipp_hmax_uint16_m4(r0);
}
inline rvd<uint16_t,8> hmax(const rvd<uint16_t,8> r0) {
	return mipp_hmax_uint16_m8(r0);
}
inline rvd<uint8_t,1> hmax(const rvd<uint8_t,1> r0) {
	return mipp_hmax_uint8_m1(r0);
}
inline rvd<uint8_t,2> hmax(const rvd<uint8_t,2> r0) {
	return mipp_hmax_uint8_m2(r0);
}
inline rvd<uint8_t,4> hmax(const rvd<uint8_t,4> r0) {
	return mipp_hmax_uint8_m4(r0);
}
inline rvd<uint8_t,8> hmax(const rvd<uint8_t,8> r0) {
	return mipp_hmax_uint8_m8(r0);
}
inline float64_t hadd_to_scal(const rvd<float64_t,1> r0) {
	return mipp_hadd_to_scal_float64_m1(r0);
}
inline float64_t hadd_to_scal(const rvd<float64_t,2> r0) {
	return mipp_hadd_to_scal_float64_m2(r0);
}
inline float64_t hadd_to_scal(const rvd<float64_t,4> r0) {
	return mipp_hadd_to_scal_float64_m4(r0);
}
inline float64_t hadd_to_scal(const rvd<float64_t,8> r0) {
	return mipp_hadd_to_scal_float64_m8(r0);
}
inline float32_t hadd_to_scal(const rvd<float32_t,1> r0) {
	return mipp_hadd_to_scal_float32_m1(r0);
}
inline float32_t hadd_to_scal(const rvd<float32_t,2> r0) {
	return mipp_hadd_to_scal_float32_m2(r0);
}
inline float32_t hadd_to_scal(const rvd<float32_t,4> r0) {
	return mipp_hadd_to_scal_float32_m4(r0);
}
inline float32_t hadd_to_scal(const rvd<float32_t,8> r0) {
	return mipp_hadd_to_scal_float32_m8(r0);
}
inline int64_t hadd_to_scal(const rvd<int64_t,1> r0) {
	return mipp_hadd_to_scal_int64_m1(r0);
}
inline int64_t hadd_to_scal(const rvd<int64_t,2> r0) {
	return mipp_hadd_to_scal_int64_m2(r0);
}
inline int64_t hadd_to_scal(const rvd<int64_t,4> r0) {
	return mipp_hadd_to_scal_int64_m4(r0);
}
inline int64_t hadd_to_scal(const rvd<int64_t,8> r0) {
	return mipp_hadd_to_scal_int64_m8(r0);
}
inline int32_t hadd_to_scal(const rvd<int32_t,1> r0) {
	return mipp_hadd_to_scal_int32_m1(r0);
}
inline int32_t hadd_to_scal(const rvd<int32_t,2> r0) {
	return mipp_hadd_to_scal_int32_m2(r0);
}
inline int32_t hadd_to_scal(const rvd<int32_t,4> r0) {
	return mipp_hadd_to_scal_int32_m4(r0);
}
inline int32_t hadd_to_scal(const rvd<int32_t,8> r0) {
	return mipp_hadd_to_scal_int32_m8(r0);
}
inline int16_t hadd_to_scal(const rvd<int16_t,1> r0) {
	return mipp_hadd_to_scal_int16_m1(r0);
}
inline int16_t hadd_to_scal(const rvd<int16_t,2> r0) {
	return mipp_hadd_to_scal_int16_m2(r0);
}
inline int16_t hadd_to_scal(const rvd<int16_t,4> r0) {
	return mipp_hadd_to_scal_int16_m4(r0);
}
inline int16_t hadd_to_scal(const rvd<int16_t,8> r0) {
	return mipp_hadd_to_scal_int16_m8(r0);
}
inline int8_t hadd_to_scal(const rvd<int8_t,1> r0) {
	return mipp_hadd_to_scal_int8_m1(r0);
}
inline int8_t hadd_to_scal(const rvd<int8_t,2> r0) {
	return mipp_hadd_to_scal_int8_m2(r0);
}
inline int8_t hadd_to_scal(const rvd<int8_t,4> r0) {
	return mipp_hadd_to_scal_int8_m4(r0);
}
inline int8_t hadd_to_scal(const rvd<int8_t,8> r0) {
	return mipp_hadd_to_scal_int8_m8(r0);
}
inline uint64_t hadd_to_scal(const rvd<uint64_t,1> r0) {
	return mipp_hadd_to_scal_uint64_m1(r0);
}
inline uint64_t hadd_to_scal(const rvd<uint64_t,2> r0) {
	return mipp_hadd_to_scal_uint64_m2(r0);
}
inline uint64_t hadd_to_scal(const rvd<uint64_t,4> r0) {
	return mipp_hadd_to_scal_uint64_m4(r0);
}
inline uint64_t hadd_to_scal(const rvd<uint64_t,8> r0) {
	return mipp_hadd_to_scal_uint64_m8(r0);
}
inline uint32_t hadd_to_scal(const rvd<uint32_t,1> r0) {
	return mipp_hadd_to_scal_uint32_m1(r0);
}
inline uint32_t hadd_to_scal(const rvd<uint32_t,2> r0) {
	return mipp_hadd_to_scal_uint32_m2(r0);
}
inline uint32_t hadd_to_scal(const rvd<uint32_t,4> r0) {
	return mipp_hadd_to_scal_uint32_m4(r0);
}
inline uint32_t hadd_to_scal(const rvd<uint32_t,8> r0) {
	return mipp_hadd_to_scal_uint32_m8(r0);
}
inline uint16_t hadd_to_scal(const rvd<uint16_t,1> r0) {
	return mipp_hadd_to_scal_uint16_m1(r0);
}
inline uint16_t hadd_to_scal(const rvd<uint16_t,2> r0) {
	return mipp_hadd_to_scal_uint16_m2(r0);
}
inline uint16_t hadd_to_scal(const rvd<uint16_t,4> r0) {
	return mipp_hadd_to_scal_uint16_m4(r0);
}
inline uint16_t hadd_to_scal(const rvd<uint16_t,8> r0) {
	return mipp_hadd_to_scal_uint16_m8(r0);
}
inline uint8_t hadd_to_scal(const rvd<uint8_t,1> r0) {
	return mipp_hadd_to_scal_uint8_m1(r0);
}
inline uint8_t hadd_to_scal(const rvd<uint8_t,2> r0) {
	return mipp_hadd_to_scal_uint8_m2(r0);
}
inline uint8_t hadd_to_scal(const rvd<uint8_t,4> r0) {
	return mipp_hadd_to_scal_uint8_m4(r0);
}
inline uint8_t hadd_to_scal(const rvd<uint8_t,8> r0) {
	return mipp_hadd_to_scal_uint8_m8(r0);
}
inline rvd<float64_t,1> maskz_add(const rvm<float64_t,1> m0, const rvd<float64_t,1> r0, const rvd<float64_t,1> r1) {
	return mipp_maskz_add_float64_m1(m0, r0, r1);
}
inline rvd<float64_t,2> maskz_add(const rvm<float64_t,2> m0, const rvd<float64_t,2> r0, const rvd<float64_t,2> r1) {
	return mipp_maskz_add_float64_m2(m0, r0, r1);
}
inline rvd<float64_t,4> maskz_add(const rvm<float64_t,4> m0, const rvd<float64_t,4> r0, const rvd<float64_t,4> r1) {
	return mipp_maskz_add_float64_m4(m0, r0, r1);
}
inline rvd<float64_t,8> maskz_add(const rvm<float64_t,8> m0, const rvd<float64_t,8> r0, const rvd<float64_t,8> r1) {
	return mipp_maskz_add_float64_m8(m0, r0, r1);
}
inline rvd<float32_t,1> maskz_add(const rvm<float32_t,1> m0, const rvd<float32_t,1> r0, const rvd<float32_t,1> r1) {
	return mipp_maskz_add_float32_m1(m0, r0, r1);
}
inline rvd<float32_t,2> maskz_add(const rvm<float32_t,2> m0, const rvd<float32_t,2> r0, const rvd<float32_t,2> r1) {
	return mipp_maskz_add_float32_m2(m0, r0, r1);
}
inline rvd<float32_t,4> maskz_add(const rvm<float32_t,4> m0, const rvd<float32_t,4> r0, const rvd<float32_t,4> r1) {
	return mipp_maskz_add_float32_m4(m0, r0, r1);
}
inline rvd<float32_t,8> maskz_add(const rvm<float32_t,8> m0, const rvd<float32_t,8> r0, const rvd<float32_t,8> r1) {
	return mipp_maskz_add_float32_m8(m0, r0, r1);
}
inline rvd<int64_t,1> maskz_add(const rvm<int64_t,1> m0, const rvd<int64_t,1> r0, const rvd<int64_t,1> r1) {
	return mipp_maskz_add_int64_m1(m0, r0, r1);
}
inline rvd<int64_t,2> maskz_add(const rvm<int64_t,2> m0, const rvd<int64_t,2> r0, const rvd<int64_t,2> r1) {
	return mipp_maskz_add_int64_m2(m0, r0, r1);
}
inline rvd<int64_t,4> maskz_add(const rvm<int64_t,4> m0, const rvd<int64_t,4> r0, const rvd<int64_t,4> r1) {
	return mipp_maskz_add_int64_m4(m0, r0, r1);
}
inline rvd<int64_t,8> maskz_add(const rvm<int64_t,8> m0, const rvd<int64_t,8> r0, const rvd<int64_t,8> r1) {
	return mipp_maskz_add_int64_m8(m0, r0, r1);
}
inline rvd<int32_t,1> maskz_add(const rvm<int32_t,1> m0, const rvd<int32_t,1> r0, const rvd<int32_t,1> r1) {
	return mipp_maskz_add_int32_m1(m0, r0, r1);
}
inline rvd<int32_t,2> maskz_add(const rvm<int32_t,2> m0, const rvd<int32_t,2> r0, const rvd<int32_t,2> r1) {
	return mipp_maskz_add_int32_m2(m0, r0, r1);
}
inline rvd<int32_t,4> maskz_add(const rvm<int32_t,4> m0, const rvd<int32_t,4> r0, const rvd<int32_t,4> r1) {
	return mipp_maskz_add_int32_m4(m0, r0, r1);
}
inline rvd<int32_t,8> maskz_add(const rvm<int32_t,8> m0, const rvd<int32_t,8> r0, const rvd<int32_t,8> r1) {
	return mipp_maskz_add_int32_m8(m0, r0, r1);
}
inline rvd<int16_t,1> maskz_add(const rvm<int16_t,1> m0, const rvd<int16_t,1> r0, const rvd<int16_t,1> r1) {
	return mipp_maskz_add_int16_m1(m0, r0, r1);
}
inline rvd<int16_t,2> maskz_add(const rvm<int16_t,2> m0, const rvd<int16_t,2> r0, const rvd<int16_t,2> r1) {
	return mipp_maskz_add_int16_m2(m0, r0, r1);
}
inline rvd<int16_t,4> maskz_add(const rvm<int16_t,4> m0, const rvd<int16_t,4> r0, const rvd<int16_t,4> r1) {
	return mipp_maskz_add_int16_m4(m0, r0, r1);
}
inline rvd<int16_t,8> maskz_add(const rvm<int16_t,8> m0, const rvd<int16_t,8> r0, const rvd<int16_t,8> r1) {
	return mipp_maskz_add_int16_m8(m0, r0, r1);
}
inline rvd<int8_t,1> maskz_add(const rvm<int8_t,1> m0, const rvd<int8_t,1> r0, const rvd<int8_t,1> r1) {
	return mipp_maskz_add_int8_m1(m0, r0, r1);
}
inline rvd<int8_t,2> maskz_add(const rvm<int8_t,2> m0, const rvd<int8_t,2> r0, const rvd<int8_t,2> r1) {
	return mipp_maskz_add_int8_m2(m0, r0, r1);
}
inline rvd<int8_t,4> maskz_add(const rvm<int8_t,4> m0, const rvd<int8_t,4> r0, const rvd<int8_t,4> r1) {
	return mipp_maskz_add_int8_m4(m0, r0, r1);
}
inline rvd<int8_t,8> maskz_add(const rvm<int8_t,8> m0, const rvd<int8_t,8> r0, const rvd<int8_t,8> r1) {
	return mipp_maskz_add_int8_m8(m0, r0, r1);
}
inline rvd<uint64_t,1> maskz_add(const rvm<uint64_t,1> m0, const rvd<uint64_t,1> r0, const rvd<uint64_t,1> r1) {
	return mipp_maskz_add_uint64_m1(m0, r0, r1);
}
inline rvd<uint64_t,2> maskz_add(const rvm<uint64_t,2> m0, const rvd<uint64_t,2> r0, const rvd<uint64_t,2> r1) {
	return mipp_maskz_add_uint64_m2(m0, r0, r1);
}
inline rvd<uint64_t,4> maskz_add(const rvm<uint64_t,4> m0, const rvd<uint64_t,4> r0, const rvd<uint64_t,4> r1) {
	return mipp_maskz_add_uint64_m4(m0, r0, r1);
}
inline rvd<uint64_t,8> maskz_add(const rvm<uint64_t,8> m0, const rvd<uint64_t,8> r0, const rvd<uint64_t,8> r1) {
	return mipp_maskz_add_uint64_m8(m0, r0, r1);
}
inline rvd<uint32_t,1> maskz_add(const rvm<uint32_t,1> m0, const rvd<uint32_t,1> r0, const rvd<uint32_t,1> r1) {
	return mipp_maskz_add_uint32_m1(m0, r0, r1);
}
inline rvd<uint32_t,2> maskz_add(const rvm<uint32_t,2> m0, const rvd<uint32_t,2> r0, const rvd<uint32_t,2> r1) {
	return mipp_maskz_add_uint32_m2(m0, r0, r1);
}
inline rvd<uint32_t,4> maskz_add(const rvm<uint32_t,4> m0, const rvd<uint32_t,4> r0, const rvd<uint32_t,4> r1) {
	return mipp_maskz_add_uint32_m4(m0, r0, r1);
}
inline rvd<uint32_t,8> maskz_add(const rvm<uint32_t,8> m0, const rvd<uint32_t,8> r0, const rvd<uint32_t,8> r1) {
	return mipp_maskz_add_uint32_m8(m0, r0, r1);
}
inline rvd<uint16_t,1> maskz_add(const rvm<uint16_t,1> m0, const rvd<uint16_t,1> r0, const rvd<uint16_t,1> r1) {
	return mipp_maskz_add_uint16_m1(m0, r0, r1);
}
inline rvd<uint16_t,2> maskz_add(const rvm<uint16_t,2> m0, const rvd<uint16_t,2> r0, const rvd<uint16_t,2> r1) {
	return mipp_maskz_add_uint16_m2(m0, r0, r1);
}
inline rvd<uint16_t,4> maskz_add(const rvm<uint16_t,4> m0, const rvd<uint16_t,4> r0, const rvd<uint16_t,4> r1) {
	return mipp_maskz_add_uint16_m4(m0, r0, r1);
}
inline rvd<uint16_t,8> maskz_add(const rvm<uint16_t,8> m0, const rvd<uint16_t,8> r0, const rvd<uint16_t,8> r1) {
	return mipp_maskz_add_uint16_m8(m0, r0, r1);
}
inline rvd<uint8_t,1> maskz_add(const rvm<uint8_t,1> m0, const rvd<uint8_t,1> r0, const rvd<uint8_t,1> r1) {
	return mipp_maskz_add_uint8_m1(m0, r0, r1);
}
inline rvd<uint8_t,2> maskz_add(const rvm<uint8_t,2> m0, const rvd<uint8_t,2> r0, const rvd<uint8_t,2> r1) {
	return mipp_maskz_add_uint8_m2(m0, r0, r1);
}
inline rvd<uint8_t,4> maskz_add(const rvm<uint8_t,4> m0, const rvd<uint8_t,4> r0, const rvd<uint8_t,4> r1) {
	return mipp_maskz_add_uint8_m4(m0, r0, r1);
}
inline rvd<uint8_t,8> maskz_add(const rvm<uint8_t,8> m0, const rvd<uint8_t,8> r0, const rvd<uint8_t,8> r1) {
	return mipp_maskz_add_uint8_m8(m0, r0, r1);
}
}

#endif /* MY_INTRINSICS_PLUS_PLUS_HPP_ */
