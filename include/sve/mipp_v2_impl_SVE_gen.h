#if defined(__ARM_FEATURE_SVE)
#if __ARM_FEATURE_SVE_BITS == 2048
#include "../include/sve/mipp_v2_impl_SVE2048_gen.h"
#define MIPP_USE_ARM_SVE_2048
#elif __ARM_FEATURE_SVE_BITS == 1024
#include "../include/sve/mipp_v2_impl_SVE1024_gen.h"
#define MIPP_USE_ARM_SVE_1024
#elif __ARM_FEATURE_SVE_BITS == 512
#include "../include/sve/mipp_v2_impl_SVE512_gen.h"
#define MIPP_USE_ARM_SVE_512
#elif __ARM_FEATURE_SVE_BITS == 256
#include "../include/sve/mipp_v2_impl_SVE256_gen.h"
#define MIPP_USE_ARM_SVE_256
#elif __ARM_FEATURE_SVE_BITS == 128
#include "../include/sve/mipp_v2_impl_SVE128_gen.h"
#define MIPP_USE_ARM_SVE_128
#else
#error Only -msve-vector-bits = [2048, 1024, 512, 256, 128] is supported)
#endif
#endif
