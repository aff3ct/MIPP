#ifndef MY_INTRINSICS_PLUS_PLUS_HPP_
#define MY_INTRINSICS_PLUS_PLUS_HPP_

#include "mipp_v2.h"

namespace mipp
{

// should throw an exception
template<typename T, int LMUL=1> struct rvd_type{};

template<> struct rvd_type<float64_t, 1>{ using type = rvd_float64_m1_t; };
template<> struct rvd_type<float32_t, 1>{ using type = rvd_float32_m1_t; };
template<> struct rvd_type<  int64_t, 1>{ using type =   rvd_int64_m1_t; };
template<> struct rvd_type<  int32_t, 1>{ using type =   rvd_int32_m1_t; };
template<> struct rvd_type<  int16_t, 1>{ using type =   rvd_int16_m1_t; };
template<> struct rvd_type<   int8_t, 1>{ using type =    rvd_int8_m1_t; };
template<> struct rvd_type< uint64_t, 1>{ using type =  rvd_uint64_m1_t; };
template<> struct rvd_type< uint32_t, 1>{ using type =  rvd_uint32_m1_t; };
template<> struct rvd_type< uint16_t, 1>{ using type =  rvd_uint16_m1_t; };
template<> struct rvd_type<  uint8_t, 1>{ using type =   rvd_uint8_m1_t; };

template<> struct rvd_type<float64_t, 2>{ using type = rvd_float64_m2_t; };
template<> struct rvd_type<float32_t, 2>{ using type = rvd_float32_m2_t; };
template<> struct rvd_type<  int64_t, 2>{ using type =   rvd_int64_m2_t; };
template<> struct rvd_type<  int32_t, 2>{ using type =   rvd_int32_m2_t; };
template<> struct rvd_type<  int16_t, 2>{ using type =   rvd_int16_m2_t; };
template<> struct rvd_type<   int8_t, 2>{ using type =    rvd_int8_m2_t; };
template<> struct rvd_type< uint64_t, 2>{ using type =  rvd_uint64_m2_t; };
template<> struct rvd_type< uint32_t, 2>{ using type =  rvd_uint32_m2_t; };
template<> struct rvd_type< uint16_t, 2>{ using type =  rvd_uint16_m2_t; };
template<> struct rvd_type<  uint8_t, 2>{ using type =   rvd_uint8_m2_t; };

template<> struct rvd_type<float64_t, 4>{ using type = rvd_float64_m4_t; };
template<> struct rvd_type<float32_t, 4>{ using type = rvd_float32_m4_t; };
template<> struct rvd_type<  int64_t, 4>{ using type =   rvd_int64_m4_t; };
template<> struct rvd_type<  int32_t, 4>{ using type =   rvd_int32_m4_t; };
template<> struct rvd_type<  int16_t, 4>{ using type =   rvd_int16_m4_t; };
template<> struct rvd_type<   int8_t, 4>{ using type =    rvd_int8_m4_t; };
template<> struct rvd_type< uint64_t, 4>{ using type =  rvd_uint64_m4_t; };
template<> struct rvd_type< uint32_t, 4>{ using type =  rvd_uint32_m4_t; };
template<> struct rvd_type< uint16_t, 4>{ using type =  rvd_uint16_m4_t; };
template<> struct rvd_type<  uint8_t, 4>{ using type =   rvd_uint8_m4_t; };

template<> struct rvd_type<float64_t, 8>{ using type = rvd_float64_m8_t; };
template<> struct rvd_type<float32_t, 8>{ using type = rvd_float32_m8_t; };
template<> struct rvd_type<  int64_t, 8>{ using type =   rvd_int64_m8_t; };
template<> struct rvd_type<  int32_t, 8>{ using type =   rvd_int32_m8_t; };
template<> struct rvd_type<  int16_t, 8>{ using type =   rvd_int16_m8_t; };
template<> struct rvd_type<   int8_t, 8>{ using type =    rvd_int8_m8_t; };
template<> struct rvd_type< uint64_t, 8>{ using type =  rvd_uint64_m8_t; };
template<> struct rvd_type< uint32_t, 8>{ using type =  rvd_uint32_m8_t; };
template<> struct rvd_type< uint16_t, 8>{ using type =  rvd_uint16_m8_t; };
template<> struct rvd_type<  uint8_t, 8>{ using type =   rvd_uint8_m8_t; };

template <typename T, int LMUL=1> using rvd = typename rvd_type<T,LMUL>::type;

// should throw an exception
template<typename T, int LMUL=1> constexpr uint32_t N(){ return 0; }

template<> constexpr uint32_t N<float64_t, 1>(){ return MIPP_N_FLOAT64_M1; }
template<> constexpr uint32_t N<float32_t, 1>(){ return MIPP_N_FLOAT32_M1; }
template<> constexpr uint32_t N<  int64_t, 1>(){ return   MIPP_N_INT64_M1; }
template<> constexpr uint32_t N<  int32_t, 1>(){ return   MIPP_N_INT32_M1; }
template<> constexpr uint32_t N<  int16_t, 1>(){ return   MIPP_N_INT16_M1; }
template<> constexpr uint32_t N<   int8_t, 1>(){ return    MIPP_N_INT8_M1; }
template<> constexpr uint32_t N< uint64_t, 1>(){ return  MIPP_N_UINT64_M1; }
template<> constexpr uint32_t N< uint32_t, 1>(){ return  MIPP_N_UINT32_M1; }
template<> constexpr uint32_t N< uint16_t, 1>(){ return  MIPP_N_UINT16_M1; }
template<> constexpr uint32_t N<  uint8_t, 1>(){ return   MIPP_N_UINT8_M1; }

template<> constexpr uint32_t N<float64_t, 2>(){ return MIPP_N_FLOAT64_M2; }
template<> constexpr uint32_t N<float32_t, 2>(){ return MIPP_N_FLOAT32_M2; }
template<> constexpr uint32_t N<  int64_t, 2>(){ return   MIPP_N_INT64_M2; }
template<> constexpr uint32_t N<  int32_t, 2>(){ return   MIPP_N_INT32_M2; }
template<> constexpr uint32_t N<  int16_t, 2>(){ return   MIPP_N_INT16_M2; }
template<> constexpr uint32_t N<   int8_t, 2>(){ return    MIPP_N_INT8_M2; }
template<> constexpr uint32_t N< uint64_t, 2>(){ return  MIPP_N_UINT64_M2; }
template<> constexpr uint32_t N< uint32_t, 2>(){ return  MIPP_N_UINT32_M2; }
template<> constexpr uint32_t N< uint16_t, 2>(){ return  MIPP_N_UINT16_M2; }
template<> constexpr uint32_t N<  uint8_t, 2>(){ return   MIPP_N_UINT8_M2; }

template<> constexpr uint32_t N<float64_t, 4>(){ return MIPP_N_FLOAT64_M4; }
template<> constexpr uint32_t N<float32_t, 4>(){ return MIPP_N_FLOAT32_M4; }
template<> constexpr uint32_t N<  int64_t, 4>(){ return   MIPP_N_INT64_M4; }
template<> constexpr uint32_t N<  int32_t, 4>(){ return   MIPP_N_INT32_M4; }
template<> constexpr uint32_t N<  int16_t, 4>(){ return   MIPP_N_INT16_M4; }
template<> constexpr uint32_t N<   int8_t, 4>(){ return    MIPP_N_INT8_M4; }
template<> constexpr uint32_t N< uint64_t, 4>(){ return  MIPP_N_UINT64_M4; }
template<> constexpr uint32_t N< uint32_t, 4>(){ return  MIPP_N_UINT32_M4; }
template<> constexpr uint32_t N< uint16_t, 4>(){ return  MIPP_N_UINT16_M4; }
template<> constexpr uint32_t N<  uint8_t, 4>(){ return   MIPP_N_UINT8_M4; }

template<> constexpr uint32_t N<float64_t, 8>(){ return MIPP_N_FLOAT64_M8; }
template<> constexpr uint32_t N<float32_t, 8>(){ return MIPP_N_FLOAT32_M8; }
template<> constexpr uint32_t N<  int64_t, 8>(){ return   MIPP_N_INT64_M8; }
template<> constexpr uint32_t N<  int32_t, 8>(){ return   MIPP_N_INT32_M8; }
template<> constexpr uint32_t N<  int16_t, 8>(){ return   MIPP_N_INT16_M8; }
template<> constexpr uint32_t N<   int8_t, 8>(){ return    MIPP_N_INT8_M8; }
template<> constexpr uint32_t N< uint64_t, 8>(){ return  MIPP_N_UINT64_M8; }
template<> constexpr uint32_t N< uint32_t, 8>(){ return  MIPP_N_UINT32_M8; }
template<> constexpr uint32_t N< uint16_t, 8>(){ return  MIPP_N_UINT16_M8; }
template<> constexpr uint32_t N<  uint8_t, 8>(){ return   MIPP_N_UINT8_M8; }

void loadu(const float64_t *mem_addr, rvd<float64_t,1>& rvd) { rvd = mipp_loadu_float64_m1(const_cast<float64_t*>(mem_addr)); }
void loadu(const float32_t *mem_addr, rvd<float32_t,1>& rvd) { rvd = mipp_loadu_float32_m1(const_cast<float32_t*>(mem_addr)); }
void loadu(const   int64_t *mem_addr, rvd<  int64_t,1>& rvd) { rvd =   mipp_loadu_int64_m1(const_cast<  int64_t*>(mem_addr)); }
void loadu(const   int32_t *mem_addr, rvd<  int32_t,1>& rvd) { rvd =   mipp_loadu_int32_m1(const_cast<  int32_t*>(mem_addr)); }
void loadu(const   int16_t *mem_addr, rvd<  int16_t,1>& rvd) { rvd =   mipp_loadu_int16_m1(const_cast<  int16_t*>(mem_addr)); }
void loadu(const    int8_t *mem_addr, rvd<   int8_t,1>& rvd) { rvd =    mipp_loadu_int8_m1(const_cast<   int8_t*>(mem_addr)); }
void loadu(const  uint64_t *mem_addr, rvd< uint64_t,1>& rvd) { rvd =  mipp_loadu_uint64_m1(const_cast< uint64_t*>(mem_addr)); }
void loadu(const  uint32_t *mem_addr, rvd< uint32_t,1>& rvd) { rvd =  mipp_loadu_uint32_m1(const_cast< uint32_t*>(mem_addr)); }
void loadu(const  uint16_t *mem_addr, rvd< uint16_t,1>& rvd) { rvd =  mipp_loadu_uint16_m1(const_cast< uint16_t*>(mem_addr)); }
void loadu(const   uint8_t *mem_addr, rvd<  uint8_t,1>& rvd) { rvd =   mipp_loadu_uint8_m1(const_cast<  uint8_t*>(mem_addr)); }

void loadu(const float64_t *mem_addr, rvd<float64_t,2>& rvd) { rvd = mipp_loadu_float64_m2(const_cast<float64_t*>(mem_addr)); }
void loadu(const float32_t *mem_addr, rvd<float32_t,2>& rvd) { rvd = mipp_loadu_float32_m2(const_cast<float32_t*>(mem_addr)); }
void loadu(const   int64_t *mem_addr, rvd<  int64_t,2>& rvd) { rvd =   mipp_loadu_int64_m2(const_cast<  int64_t*>(mem_addr)); }
void loadu(const   int32_t *mem_addr, rvd<  int32_t,2>& rvd) { rvd =   mipp_loadu_int32_m2(const_cast<  int32_t*>(mem_addr)); }
void loadu(const   int16_t *mem_addr, rvd<  int16_t,2>& rvd) { rvd =   mipp_loadu_int16_m2(const_cast<  int16_t*>(mem_addr)); }
void loadu(const    int8_t *mem_addr, rvd<   int8_t,2>& rvd) { rvd =    mipp_loadu_int8_m2(const_cast<   int8_t*>(mem_addr)); }
void loadu(const  uint64_t *mem_addr, rvd< uint64_t,2>& rvd) { rvd =  mipp_loadu_uint64_m2(const_cast< uint64_t*>(mem_addr)); }
void loadu(const  uint32_t *mem_addr, rvd< uint32_t,2>& rvd) { rvd =  mipp_loadu_uint32_m2(const_cast< uint32_t*>(mem_addr)); }
void loadu(const  uint16_t *mem_addr, rvd< uint16_t,2>& rvd) { rvd =  mipp_loadu_uint16_m2(const_cast< uint16_t*>(mem_addr)); }
void loadu(const   uint8_t *mem_addr, rvd<  uint8_t,2>& rvd) { rvd =   mipp_loadu_uint8_m2(const_cast<  uint8_t*>(mem_addr)); }

void loadu(const float64_t *mem_addr, rvd<float64_t,4>& rvd) { rvd = mipp_loadu_float64_m4(const_cast<float64_t*>(mem_addr)); }
void loadu(const float32_t *mem_addr, rvd<float32_t,4>& rvd) { rvd = mipp_loadu_float32_m4(const_cast<float32_t*>(mem_addr)); }
void loadu(const   int64_t *mem_addr, rvd<  int64_t,4>& rvd) { rvd =   mipp_loadu_int64_m4(const_cast<  int64_t*>(mem_addr)); }
void loadu(const   int32_t *mem_addr, rvd<  int32_t,4>& rvd) { rvd =   mipp_loadu_int32_m4(const_cast<  int32_t*>(mem_addr)); }
void loadu(const   int16_t *mem_addr, rvd<  int16_t,4>& rvd) { rvd =   mipp_loadu_int16_m4(const_cast<  int16_t*>(mem_addr)); }
void loadu(const    int8_t *mem_addr, rvd<   int8_t,4>& rvd) { rvd =    mipp_loadu_int8_m4(const_cast<   int8_t*>(mem_addr)); }
void loadu(const  uint64_t *mem_addr, rvd< uint64_t,4>& rvd) { rvd =  mipp_loadu_uint64_m4(const_cast< uint64_t*>(mem_addr)); }
void loadu(const  uint32_t *mem_addr, rvd< uint32_t,4>& rvd) { rvd =  mipp_loadu_uint32_m4(const_cast< uint32_t*>(mem_addr)); }
void loadu(const  uint16_t *mem_addr, rvd< uint16_t,4>& rvd) { rvd =  mipp_loadu_uint16_m4(const_cast< uint16_t*>(mem_addr)); }
void loadu(const   uint8_t *mem_addr, rvd<  uint8_t,4>& rvd) { rvd =   mipp_loadu_uint8_m4(const_cast<  uint8_t*>(mem_addr)); }

void loadu(const float64_t *mem_addr, rvd<float64_t,8>& rvd) { rvd = mipp_loadu_float64_m8(const_cast<float64_t*>(mem_addr)); }
void loadu(const float32_t *mem_addr, rvd<float32_t,8>& rvd) { rvd = mipp_loadu_float32_m8(const_cast<float32_t*>(mem_addr)); }
void loadu(const   int64_t *mem_addr, rvd<  int64_t,8>& rvd) { rvd =   mipp_loadu_int64_m8(const_cast<  int64_t*>(mem_addr)); }
void loadu(const   int32_t *mem_addr, rvd<  int32_t,8>& rvd) { rvd =   mipp_loadu_int32_m8(const_cast<  int32_t*>(mem_addr)); }
void loadu(const   int16_t *mem_addr, rvd<  int16_t,8>& rvd) { rvd =   mipp_loadu_int16_m8(const_cast<  int16_t*>(mem_addr)); }
void loadu(const    int8_t *mem_addr, rvd<   int8_t,8>& rvd) { rvd =    mipp_loadu_int8_m8(const_cast<   int8_t*>(mem_addr)); }
void loadu(const  uint64_t *mem_addr, rvd< uint64_t,8>& rvd) { rvd =  mipp_loadu_uint64_m8(const_cast< uint64_t*>(mem_addr)); }
void loadu(const  uint32_t *mem_addr, rvd< uint32_t,8>& rvd) { rvd =  mipp_loadu_uint32_m8(const_cast< uint32_t*>(mem_addr)); }
void loadu(const  uint16_t *mem_addr, rvd< uint16_t,8>& rvd) { rvd =  mipp_loadu_uint16_m8(const_cast< uint16_t*>(mem_addr)); }
void loadu(const   uint8_t *mem_addr, rvd<  uint8_t,8>& rvd) { rvd =   mipp_loadu_uint8_m8(const_cast<  uint8_t*>(mem_addr)); }

void storeu(float64_t *mem_addr, const rvd<float64_t,1> rvd) { mipp_storeu_float64_m1(mem_addr, rvd); }
void storeu(float32_t *mem_addr, const rvd<float32_t,1> rvd) { mipp_storeu_float32_m1(mem_addr, rvd); }
void storeu(  int64_t *mem_addr, const rvd<  int64_t,1> rvd) {   mipp_storeu_int64_m1(mem_addr, rvd); }
void storeu(  int32_t *mem_addr, const rvd<  int32_t,1> rvd) {   mipp_storeu_int32_m1(mem_addr, rvd); }
void storeu(  int16_t *mem_addr, const rvd<  int16_t,1> rvd) {   mipp_storeu_int16_m1(mem_addr, rvd); }
void storeu(   int8_t *mem_addr, const rvd<   int8_t,1> rvd) {    mipp_storeu_int8_m1(mem_addr, rvd); }
void storeu( uint64_t *mem_addr, const rvd< uint64_t,1> rvd) {  mipp_storeu_uint64_m1(mem_addr, rvd); }
void storeu( uint32_t *mem_addr, const rvd< uint32_t,1> rvd) {  mipp_storeu_uint32_m1(mem_addr, rvd); }
void storeu( uint16_t *mem_addr, const rvd< uint16_t,1> rvd) {  mipp_storeu_uint16_m1(mem_addr, rvd); }
void storeu(  uint8_t *mem_addr, const rvd<  uint8_t,1> rvd) {   mipp_storeu_uint8_m1(mem_addr, rvd); }

void storeu(float64_t *mem_addr, const rvd<float64_t,2> rvd) { mipp_storeu_float64_m2(mem_addr, rvd); }
void storeu(float32_t *mem_addr, const rvd<float32_t,2> rvd) { mipp_storeu_float32_m2(mem_addr, rvd); }
void storeu(  int64_t *mem_addr, const rvd<  int64_t,2> rvd) {   mipp_storeu_int64_m2(mem_addr, rvd); }
void storeu(  int32_t *mem_addr, const rvd<  int32_t,2> rvd) {   mipp_storeu_int32_m2(mem_addr, rvd); }
void storeu(  int16_t *mem_addr, const rvd<  int16_t,2> rvd) {   mipp_storeu_int16_m2(mem_addr, rvd); }
void storeu(   int8_t *mem_addr, const rvd<   int8_t,2> rvd) {    mipp_storeu_int8_m2(mem_addr, rvd); }
void storeu( uint64_t *mem_addr, const rvd< uint64_t,2> rvd) {  mipp_storeu_uint64_m2(mem_addr, rvd); }
void storeu( uint32_t *mem_addr, const rvd< uint32_t,2> rvd) {  mipp_storeu_uint32_m2(mem_addr, rvd); }
void storeu( uint16_t *mem_addr, const rvd< uint16_t,2> rvd) {  mipp_storeu_uint16_m2(mem_addr, rvd); }
void storeu(  uint8_t *mem_addr, const rvd<  uint8_t,2> rvd) {   mipp_storeu_uint8_m2(mem_addr, rvd); }

void storeu(float64_t *mem_addr, const rvd<float64_t,4> rvd) { mipp_storeu_float64_m4(mem_addr, rvd); }
void storeu(float32_t *mem_addr, const rvd<float32_t,4> rvd) { mipp_storeu_float32_m4(mem_addr, rvd); }
void storeu(  int64_t *mem_addr, const rvd<  int64_t,4> rvd) {   mipp_storeu_int64_m4(mem_addr, rvd); }
void storeu(  int32_t *mem_addr, const rvd<  int32_t,4> rvd) {   mipp_storeu_int32_m4(mem_addr, rvd); }
void storeu(  int16_t *mem_addr, const rvd<  int16_t,4> rvd) {   mipp_storeu_int16_m4(mem_addr, rvd); }
void storeu(   int8_t *mem_addr, const rvd<   int8_t,4> rvd) {    mipp_storeu_int8_m4(mem_addr, rvd); }
void storeu( uint64_t *mem_addr, const rvd< uint64_t,4> rvd) {  mipp_storeu_uint64_m4(mem_addr, rvd); }
void storeu( uint32_t *mem_addr, const rvd< uint32_t,4> rvd) {  mipp_storeu_uint32_m4(mem_addr, rvd); }
void storeu( uint16_t *mem_addr, const rvd< uint16_t,4> rvd) {  mipp_storeu_uint16_m4(mem_addr, rvd); }
void storeu(  uint8_t *mem_addr, const rvd<  uint8_t,4> rvd) {   mipp_storeu_uint8_m4(mem_addr, rvd); }

void storeu(float64_t *mem_addr, const rvd<float64_t,8> rvd) { mipp_storeu_float64_m8(mem_addr, rvd); }
void storeu(float32_t *mem_addr, const rvd<float32_t,8> rvd) { mipp_storeu_float32_m8(mem_addr, rvd); }
void storeu(  int64_t *mem_addr, const rvd<  int64_t,8> rvd) {   mipp_storeu_int64_m8(mem_addr, rvd); }
void storeu(  int32_t *mem_addr, const rvd<  int32_t,8> rvd) {   mipp_storeu_int32_m8(mem_addr, rvd); }
void storeu(  int16_t *mem_addr, const rvd<  int16_t,8> rvd) {   mipp_storeu_int16_m8(mem_addr, rvd); }
void storeu(   int8_t *mem_addr, const rvd<   int8_t,8> rvd) {    mipp_storeu_int8_m8(mem_addr, rvd); }
void storeu( uint64_t *mem_addr, const rvd< uint64_t,8> rvd) {  mipp_storeu_uint64_m8(mem_addr, rvd); }
void storeu( uint32_t *mem_addr, const rvd< uint32_t,8> rvd) {  mipp_storeu_uint32_m8(mem_addr, rvd); }
void storeu( uint16_t *mem_addr, const rvd< uint16_t,8> rvd) {  mipp_storeu_uint16_m8(mem_addr, rvd); }
void storeu(  uint8_t *mem_addr, const rvd<  uint8_t,8> rvd) {   mipp_storeu_uint8_m8(mem_addr, rvd); }

rvd<float64_t,1> add(const rvd<float64_t,1> rvd1, const rvd<float64_t,1> rvd2) { return mipp_add_float64_m1(rvd1, rvd2); }
rvd<float32_t,1> add(const rvd<float32_t,1> rvd1, const rvd<float32_t,1> rvd2) { return mipp_add_float32_m1(rvd1, rvd2); }
rvd<  int64_t,1> add(const rvd<  int64_t,1> rvd1, const rvd<  int64_t,1> rvd2) { return   mipp_add_int64_m1(rvd1, rvd2); }
rvd<  int32_t,1> add(const rvd<  int32_t,1> rvd1, const rvd<  int32_t,1> rvd2) { return   mipp_add_int32_m1(rvd1, rvd2); }
rvd<  int16_t,1> add(const rvd<  int16_t,1> rvd1, const rvd<  int16_t,1> rvd2) { return   mipp_add_int16_m1(rvd1, rvd2); }
rvd<   int8_t,1> add(const rvd<   int8_t,1> rvd1, const rvd<   int8_t,1> rvd2) { return    mipp_add_int8_m1(rvd1, rvd2); }
rvd< uint64_t,1> add(const rvd< uint64_t,1> rvd1, const rvd< uint64_t,1> rvd2) { return  mipp_add_uint64_m1(rvd1, rvd2); }
rvd< uint32_t,1> add(const rvd< uint32_t,1> rvd1, const rvd< uint32_t,1> rvd2) { return  mipp_add_uint32_m1(rvd1, rvd2); }
rvd< uint16_t,1> add(const rvd< uint16_t,1> rvd1, const rvd< uint16_t,1> rvd2) { return  mipp_add_uint16_m1(rvd1, rvd2); }
rvd<  uint8_t,1> add(const rvd<  uint8_t,1> rvd1, const rvd<  uint8_t,1> rvd2) { return   mipp_add_uint8_m1(rvd1, rvd2); }

rvd<float64_t,2> add(const rvd<float64_t,2> rvd1, const rvd<float64_t,2> rvd2) { return mipp_add_float64_m2(rvd1, rvd2); }
rvd<float32_t,2> add(const rvd<float32_t,2> rvd1, const rvd<float32_t,2> rvd2) { return mipp_add_float32_m2(rvd1, rvd2); }
rvd<  int64_t,2> add(const rvd<  int64_t,2> rvd1, const rvd<  int64_t,2> rvd2) { return   mipp_add_int64_m2(rvd1, rvd2); }
rvd<  int32_t,2> add(const rvd<  int32_t,2> rvd1, const rvd<  int32_t,2> rvd2) { return   mipp_add_int32_m2(rvd1, rvd2); }
rvd<  int16_t,2> add(const rvd<  int16_t,2> rvd1, const rvd<  int16_t,2> rvd2) { return   mipp_add_int16_m2(rvd1, rvd2); }
rvd<   int8_t,2> add(const rvd<   int8_t,2> rvd1, const rvd<   int8_t,2> rvd2) { return    mipp_add_int8_m2(rvd1, rvd2); }
rvd< uint64_t,2> add(const rvd< uint64_t,2> rvd1, const rvd< uint64_t,2> rvd2) { return  mipp_add_uint64_m2(rvd1, rvd2); }
rvd< uint32_t,2> add(const rvd< uint32_t,2> rvd1, const rvd< uint32_t,2> rvd2) { return  mipp_add_uint32_m2(rvd1, rvd2); }
rvd< uint16_t,2> add(const rvd< uint16_t,2> rvd1, const rvd< uint16_t,2> rvd2) { return  mipp_add_uint16_m2(rvd1, rvd2); }
rvd<  uint8_t,2> add(const rvd<  uint8_t,2> rvd1, const rvd<  uint8_t,2> rvd2) { return   mipp_add_uint8_m2(rvd1, rvd2); }

rvd<float64_t,4> add(const rvd<float64_t,4> rvd1, const rvd<float64_t,4> rvd2) { return mipp_add_float64_m4(rvd1, rvd2); }
rvd<float32_t,4> add(const rvd<float32_t,4> rvd1, const rvd<float32_t,4> rvd2) { return mipp_add_float32_m4(rvd1, rvd2); }
rvd<  int64_t,4> add(const rvd<  int64_t,4> rvd1, const rvd<  int64_t,4> rvd2) { return   mipp_add_int64_m4(rvd1, rvd2); }
rvd<  int32_t,4> add(const rvd<  int32_t,4> rvd1, const rvd<  int32_t,4> rvd2) { return   mipp_add_int32_m4(rvd1, rvd2); }
rvd<  int16_t,4> add(const rvd<  int16_t,4> rvd1, const rvd<  int16_t,4> rvd2) { return   mipp_add_int16_m4(rvd1, rvd2); }
rvd<   int8_t,4> add(const rvd<   int8_t,4> rvd1, const rvd<   int8_t,4> rvd2) { return    mipp_add_int8_m4(rvd1, rvd2); }
rvd< uint64_t,4> add(const rvd< uint64_t,4> rvd1, const rvd< uint64_t,4> rvd2) { return  mipp_add_uint64_m4(rvd1, rvd2); }
rvd< uint32_t,4> add(const rvd< uint32_t,4> rvd1, const rvd< uint32_t,4> rvd2) { return  mipp_add_uint32_m4(rvd1, rvd2); }
rvd< uint16_t,4> add(const rvd< uint16_t,4> rvd1, const rvd< uint16_t,4> rvd2) { return  mipp_add_uint16_m4(rvd1, rvd2); }
rvd<  uint8_t,4> add(const rvd<  uint8_t,4> rvd1, const rvd<  uint8_t,4> rvd2) { return   mipp_add_uint8_m4(rvd1, rvd2); }

rvd<float64_t,8> add(const rvd<float64_t,8> rvd1, const rvd<float64_t,8> rvd2) { return mipp_add_float64_m8(rvd1, rvd2); }
rvd<float32_t,8> add(const rvd<float32_t,8> rvd1, const rvd<float32_t,8> rvd2) { return mipp_add_float32_m8(rvd1, rvd2); }
rvd<  int64_t,8> add(const rvd<  int64_t,8> rvd1, const rvd<  int64_t,8> rvd2) { return   mipp_add_int64_m8(rvd1, rvd2); }
rvd<  int32_t,8> add(const rvd<  int32_t,8> rvd1, const rvd<  int32_t,8> rvd2) { return   mipp_add_int32_m8(rvd1, rvd2); }
rvd<  int16_t,8> add(const rvd<  int16_t,8> rvd1, const rvd<  int16_t,8> rvd2) { return   mipp_add_int16_m8(rvd1, rvd2); }
rvd<   int8_t,8> add(const rvd<   int8_t,8> rvd1, const rvd<   int8_t,8> rvd2) { return    mipp_add_int8_m8(rvd1, rvd2); }
rvd< uint64_t,8> add(const rvd< uint64_t,8> rvd1, const rvd< uint64_t,8> rvd2) { return  mipp_add_uint64_m8(rvd1, rvd2); }
rvd< uint32_t,8> add(const rvd< uint32_t,8> rvd1, const rvd< uint32_t,8> rvd2) { return  mipp_add_uint32_m8(rvd1, rvd2); }
rvd< uint16_t,8> add(const rvd< uint16_t,8> rvd1, const rvd< uint16_t,8> rvd2) { return  mipp_add_uint16_m8(rvd1, rvd2); }
rvd<  uint8_t,8> add(const rvd<  uint8_t,8> rvd1, const rvd<  uint8_t,8> rvd2) { return   mipp_add_uint8_m8(rvd1, rvd2); }

}

#endif /* MY_INTRINSICS_PLUS_PLUS_HPP_ */