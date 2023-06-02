#include <limits>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <algorithm>

#include "mipp_scalar_op.h"

namespace mipp_scop
{
template <typename T> inline T       add(const T       val1, const T       val2) { return val1 + val2; }
template <          > inline int16_t add(const int16_t val1, const int16_t val2) { return (int16_t)std::min(std::max((int32_t)((int32_t)val1 + (int32_t)val2),(int32_t)std::numeric_limits<int16_t>::min()),(int32_t)std::numeric_limits<int16_t>::max()); }
template <          > inline int8_t  add(const int8_t  val1, const int8_t  val2) { return (int8_t )std::min(std::max((int16_t)((int16_t)val1 + (int16_t)val2),(int16_t)std::numeric_limits<int8_t >::min()),(int16_t)std::numeric_limits<int8_t >::max()); }

template <typename T> inline T       sub(const T       val1, const T       val2) { return val1 - val2; }
template <          > inline int16_t sub(const int16_t val1, const int16_t val2) { return (int16_t)std::min(std::max((int32_t)((int32_t)val1 - (int32_t)val2),(int32_t)std::numeric_limits<int16_t>::min()),(int32_t)std::numeric_limits<int16_t>::max()); }
template <          > inline int8_t  sub(const int8_t  val1, const int8_t  val2) { return (int8_t )std::min(std::max((int16_t)((int16_t)val1 - (int16_t)val2),(int16_t)std::numeric_limits<int8_t >::min()),(int16_t)std::numeric_limits<int8_t >::max()); }

template <typename T> inline T      andb(const T      val1, const T      val2) { return                                          val1  &                      val2;   }
template <          > inline double andb(const double val1, const double val2) { return static_cast<double>(static_cast<int64_t>(val1) & static_cast<int64_t>(val2)); }
template <          > inline float  andb(const float  val1, const float  val2) { return static_cast<float >(static_cast<int32_t>(val1) & static_cast<int32_t>(val2)); }

template <typename T> inline T      xorb(const T      val1, const T      val2) { return                                          val1  ^                      val2;   }
template <          > inline double xorb(const double val1, const double val2) { return static_cast<double>(static_cast<int64_t>(val1) ^ static_cast<int64_t>(val2)); }
template <          > inline float  xorb(const float  val1, const float  val2) { return static_cast<float >(static_cast<int32_t>(val1) ^ static_cast<int32_t>(val2)); }

template <typename T> inline T       msb(const T       val) { return (val >> (sizeof(T) * 8 -1)) << (sizeof(T) * 8 -1);              }
template <          > inline double  msb(const double  val) { return static_cast<double >((static_cast<uint64_t>(val) >> 63) << 63); }
template <          > inline float   msb(const float   val) { return static_cast<float  >((static_cast<uint32_t>(val) >> 31) << 31); }
template <          > inline int64_t msb(const int64_t val) { return static_cast<int64_t>((static_cast<uint64_t>(val) >> 63) << 63); }
template <          > inline int32_t msb(const int32_t val) { return static_cast<int32_t>((static_cast<uint32_t>(val) >> 31) << 31); }
template <          > inline int16_t msb(const int16_t val) { return static_cast<int16_t>((static_cast<uint16_t>(val) >> 15) << 15); }
template <          > inline int8_t  msb(const int8_t  val) { return static_cast<int8_t >((static_cast<uint8_t >(val) >>  7) <<  7); }
}
