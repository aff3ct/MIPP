#ifndef MY_INTRINSICS_PLUS_PLUS_OBJECT_H_
#define MY_INTRINSICS_PLUS_PLUS_OBJECT_H_
#include "mipp_v2.h" 
void storeu(float64_t *mem_addr, const rvd<float64,1> rvd) { mipp_storeu_float64_m1(mem_addr, rvd); }
void storeu(float64_t *mem_addr, const rvd<float64,2> rvd) { mipp_storeu_float64_m2(mem_addr, rvd); }
void storeu(float64_t *mem_addr, const rvd<float64,4> rvd) { mipp_storeu_float64_m4(mem_addr, rvd); }
void storeu(float64_t *mem_addr, const rvd<float64,8> rvd) { mipp_storeu_float64_m8(mem_addr, rvd); }
void storeu(float32_t *mem_addr, const rvd<float32,1> rvd) { mipp_storeu_float32_m1(mem_addr, rvd); }
void storeu(float32_t *mem_addr, const rvd<float32,2> rvd) { mipp_storeu_float32_m2(mem_addr, rvd); }
void storeu(float32_t *mem_addr, const rvd<float32,4> rvd) { mipp_storeu_float32_m4(mem_addr, rvd); }
void storeu(float32_t *mem_addr, const rvd<float32,8> rvd) { mipp_storeu_float32_m8(mem_addr, rvd); }
void storeu(int64_t *mem_addr, const rvd<int64,1> rvd) { mipp_storeu_int64_m1(mem_addr, rvd); }
void storeu(int64_t *mem_addr, const rvd<int64,2> rvd) { mipp_storeu_int64_m2(mem_addr, rvd); }
void storeu(int64_t *mem_addr, const rvd<int64,4> rvd) { mipp_storeu_int64_m4(mem_addr, rvd); }
void storeu(int64_t *mem_addr, const rvd<int64,8> rvd) { mipp_storeu_int64_m8(mem_addr, rvd); }
void storeu(int32_t *mem_addr, const rvd<int32,1> rvd) { mipp_storeu_int32_m1(mem_addr, rvd); }
void storeu(int32_t *mem_addr, const rvd<int32,2> rvd) { mipp_storeu_int32_m2(mem_addr, rvd); }
void storeu(int32_t *mem_addr, const rvd<int32,4> rvd) { mipp_storeu_int32_m4(mem_addr, rvd); }
void storeu(int32_t *mem_addr, const rvd<int32,8> rvd) { mipp_storeu_int32_m8(mem_addr, rvd); }
void storeu(int16_t *mem_addr, const rvd<int16,1> rvd) { mipp_storeu_int16_m1(mem_addr, rvd); }
void storeu(int16_t *mem_addr, const rvd<int16,2> rvd) { mipp_storeu_int16_m2(mem_addr, rvd); }
void storeu(int16_t *mem_addr, const rvd<int16,4> rvd) { mipp_storeu_int16_m4(mem_addr, rvd); }
void storeu(int16_t *mem_addr, const rvd<int16,8> rvd) { mipp_storeu_int16_m8(mem_addr, rvd); }
void storeu(int8_t *mem_addr, const rvd<int8,1> rvd) { mipp_storeu_int8_m1(mem_addr, rvd); }
void storeu(int8_t *mem_addr, const rvd<int8,2> rvd) { mipp_storeu_int8_m2(mem_addr, rvd); }
void storeu(int8_t *mem_addr, const rvd<int8,4> rvd) { mipp_storeu_int8_m4(mem_addr, rvd); }
void storeu(int8_t *mem_addr, const rvd<int8,8> rvd) { mipp_storeu_int8_m8(mem_addr, rvd); }
void storeu(uint64_t *mem_addr, const rvd<uint64,1> rvd) { mipp_storeu_uint64_m1(mem_addr, rvd); }
void storeu(uint64_t *mem_addr, const rvd<uint64,2> rvd) { mipp_storeu_uint64_m2(mem_addr, rvd); }
void storeu(uint64_t *mem_addr, const rvd<uint64,4> rvd) { mipp_storeu_uint64_m4(mem_addr, rvd); }
void storeu(uint64_t *mem_addr, const rvd<uint64,8> rvd) { mipp_storeu_uint64_m8(mem_addr, rvd); }
void storeu(uint32_t *mem_addr, const rvd<uint32,1> rvd) { mipp_storeu_uint32_m1(mem_addr, rvd); }
void storeu(uint32_t *mem_addr, const rvd<uint32,2> rvd) { mipp_storeu_uint32_m2(mem_addr, rvd); }
void storeu(uint32_t *mem_addr, const rvd<uint32,4> rvd) { mipp_storeu_uint32_m4(mem_addr, rvd); }
void storeu(uint32_t *mem_addr, const rvd<uint32,8> rvd) { mipp_storeu_uint32_m8(mem_addr, rvd); }
void storeu(uint16_t *mem_addr, const rvd<uint16,1> rvd) { mipp_storeu_uint16_m1(mem_addr, rvd); }
void storeu(uint16_t *mem_addr, const rvd<uint16,2> rvd) { mipp_storeu_uint16_m2(mem_addr, rvd); }
void storeu(uint16_t *mem_addr, const rvd<uint16,4> rvd) { mipp_storeu_uint16_m4(mem_addr, rvd); }
void storeu(uint16_t *mem_addr, const rvd<uint16,8> rvd) { mipp_storeu_uint16_m8(mem_addr, rvd); }
void storeu(uint8_t *mem_addr, const rvd<uint8,1> rvd) { mipp_storeu_uint8_m1(mem_addr, rvd); }
void storeu(uint8_t *mem_addr, const rvd<uint8,2> rvd) { mipp_storeu_uint8_m2(mem_addr, rvd); }
void storeu(uint8_t *mem_addr, const rvd<uint8,4> rvd) { mipp_storeu_uint8_m4(mem_addr, rvd); }
void storeu(uint8_t *mem_addr, const rvd<uint8,8> rvd) { mipp_storeu_uint8_m8(mem_addr, rvd); }
#endif /* MY_INTRINSICS_PLUS_PLUS_OBJECT_H_*/
