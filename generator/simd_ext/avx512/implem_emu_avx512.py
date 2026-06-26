from tools import *

tpl_implem_emu_avx512 = {
    "toreg": { "format": "long", "code":
"""// long format
	%r<tr>% res;
	%r<c:int>% zero = %set1<c:int>%(0);
	%r<c:int>% one = %set1<c:int>%(~0);
	res = %cast<c:int,tr>%(%blend<c:int>%(one, zero, %cast_k<tp,c:int>%(m0)));
	return res;""" },
    "tomsk": { "format": "long", "code":
"""// long format
	%m<tr>% res;
	%r<c:int>% zero = %set0<c:int>%();
	res = %cast_k<c:int,tr>%(%cmpneq<c:int>%(%cast<tp,c:int>%(r0), zero));
	return res;""" },
    "get": { "format": "long", "code":
"""// long format
	%v<tp>% t[%N<tp>%];
	%storeu<tp>%(t, r0);
	return t[v0];""" },
    "get_k": { "format": "long", "code":
"""// long format
	%v<tp>% tmp[%N<tp>%];
	%r<tp>% rmsk = %toreg<tp>%(m0);
	%storeu<tp>%(tmp, rmsk);
	return (int32_t) tmp[v0];""" },
    "set1_k-8": { "format": "long", "code":
"""// long format
	%r<c:int|b:tp>% r0_32 = %set1<c:int|b:tp>%(v0 ? (int64_t)0xFFFFFFFFFFFFFFFF : 0);
	%r<c:int|b:tp>% r1_32 = %set1<c:int|b:tp>%(     (int64_t)0xFFFFFFFFFFFFFFFF    );
	return %cast_k<c:int|b:tp,tp>%(%cmpeq<c:int|b:tp>%(r0_32, r1_32));""" },
    "set1_k-16": { "format": "long", "code":
"""// long format
	%r<c:int|b:tp>% r0_32 = %set1<c:int|b:tp>%(v0 ? (int32_t)0xFFFFFFFF : 0);
	%r<c:int|b:tp>% r1_32 = %set1<c:int|b:tp>%(     (int32_t)0xFFFFFFFF    );
	return %cast_k<c:int|b:tp,tp>%(%cmpeq<c:int|b:tp>%(r0_32, r1_32));""" },
    "set1_k-32": { "format": "long", "code":
"""// long format
	%r<c:int|b:tp>% r0_32 = %set1<c:int|b:tp>%(v0 ? (int16_t)0xFFFF : 0);
	%r<c:int|b:tp>% r1_32 = %set1<c:int|b:tp>%(     (int16_t)0xFFFF    );
	return %cast_k<c:int|b:tp,tp>%(%cmpeq<c:int|b:tp>%(r0_32, r1_32));""" },
    "set1_k-64": { "format": "long", "code":
"""// long format
	%r<c:int|b:tp>% r0_32 = %set1<c:int|b:tp>%(v0 ? (int8_t)0xFF : 0);
	%r<c:int|b:tp>% r1_32 = %set1<c:int|b:tp>%(     (int8_t)0xFF    );
	return %cast_k<c:int|b:tp,tp>%(%cmpeq<c:int|b:tp>%(r0_32, r1_32)); """ },
    "set_k-64": { "format": "long", "code":
"""// long format
	%v<c:int|b:tp>% t[%N<tp>%] = {
		(int64_t)(vals[0] ? 0xFFFFFFFFFFFFFFFF : 0),
		(int64_t)(vals[1] ? 0xFFFFFFFFFFFFFFFF : 0),
		(int64_t)(vals[2] ? 0xFFFFFFFFFFFFFFFF : 0),
		(int64_t)(vals[3] ? 0xFFFFFFFFFFFFFFFF : 0),
		(int64_t)(vals[4] ? 0xFFFFFFFFFFFFFFFF : 0),
		(int64_t)(vals[5] ? 0xFFFFFFFFFFFFFFFF : 0),
		(int64_t)(vals[6] ? 0xFFFFFFFFFFFFFFFF : 0),
		(int64_t)(vals[7] ? 0xFFFFFFFFFFFFFFFF : 0) };
	%r<c:int|b:tp>% r0_32 = %set<c:int|b:tp>%(t);
	%r<c:int|b:tp>% r1_32 = %set1<c:int|b:tp>%((int64_t)0xFFFFFFFFFFFFFFFF);
	return %cast_k<c:int|b:tp,tp>%(%cmpeq<c:int|b:tp>%(r0_32, r1_32));""" },
    "set_k-32": { "format": "long", "code":
"""// long format
	%v<c:int|b:tp>% t[%N<tp>%] = {
		(int32_t)(vals[ 0] ? 0xFFFFFFFF : 0), (int32_t)(vals[ 1] ? 0xFFFFFFFF : 0),
		(int32_t)(vals[ 2] ? 0xFFFFFFFF : 0), (int32_t)(vals[ 3] ? 0xFFFFFFFF : 0),
		(int32_t)(vals[ 4] ? 0xFFFFFFFF : 0), (int32_t)(vals[ 5] ? 0xFFFFFFFF : 0),
		(int32_t)(vals[ 6] ? 0xFFFFFFFF : 0), (int32_t)(vals[ 7] ? 0xFFFFFFFF : 0),
		(int32_t)(vals[ 8] ? 0xFFFFFFFF : 0), (int32_t)(vals[ 9] ? 0xFFFFFFFF : 0),
		(int32_t)(vals[10] ? 0xFFFFFFFF : 0), (int32_t)(vals[11] ? 0xFFFFFFFF : 0),
		(int32_t)(vals[12] ? 0xFFFFFFFF : 0), (int32_t)(vals[13] ? 0xFFFFFFFF : 0),
		(int32_t)(vals[14] ? 0xFFFFFFFF : 0), (int32_t)(vals[15] ? 0xFFFFFFFF : 0) };
	%r<c:int|b:tp>% r0_32 = %set<c:int|b:tp>%(t);
	%r<c:int|b:tp>% r1_32 = %set1<c:int|b:tp>%((int32_t)0xFFFFFFFF);
	return %cast_k<c:int|b:tp,tp>%(%cmpeq<c:int|b:tp>%(r0_32, r1_32));""" },
    "set_k-16": { "format": "long", "code":
"""// long format
	%v<c:int|b:tp>% t[%N<tp>%] = {
		(int16_t)(vals[ 0] ? 0xFFFF : 0), (int16_t)(vals[ 1] ? 0xFFFF : 0),
		(int16_t)(vals[ 2] ? 0xFFFF : 0), (int16_t)(vals[ 3] ? 0xFFFF : 0),
		(int16_t)(vals[ 4] ? 0xFFFF : 0), (int16_t)(vals[ 5] ? 0xFFFF : 0),
		(int16_t)(vals[ 6] ? 0xFFFF : 0), (int16_t)(vals[ 7] ? 0xFFFF : 0),
		(int16_t)(vals[ 8] ? 0xFFFF : 0), (int16_t)(vals[ 9] ? 0xFFFF : 0),
		(int16_t)(vals[10] ? 0xFFFF : 0), (int16_t)(vals[11] ? 0xFFFF : 0),
		(int16_t)(vals[12] ? 0xFFFF : 0), (int16_t)(vals[13] ? 0xFFFF : 0),
		(int16_t)(vals[14] ? 0xFFFF : 0), (int16_t)(vals[15] ? 0xFFFF : 0),
		(int16_t)(vals[16] ? 0xFFFF : 0), (int16_t)(vals[17] ? 0xFFFF : 0),
		(int16_t)(vals[18] ? 0xFFFF : 0), (int16_t)(vals[19] ? 0xFFFF : 0),
		(int16_t)(vals[20] ? 0xFFFF : 0), (int16_t)(vals[21] ? 0xFFFF : 0),
		(int16_t)(vals[22] ? 0xFFFF : 0), (int16_t)(vals[23] ? 0xFFFF : 0),
		(int16_t)(vals[24] ? 0xFFFF : 0), (int16_t)(vals[25] ? 0xFFFF : 0),
		(int16_t)(vals[26] ? 0xFFFF : 0), (int16_t)(vals[27] ? 0xFFFF : 0),
		(int16_t)(vals[28] ? 0xFFFF : 0), (int16_t)(vals[29] ? 0xFFFF : 0),
		(int16_t)(vals[30] ? 0xFFFF : 0), (int16_t)(vals[31] ? 0xFFFF : 0) };
	%r<c:int|b:tp>% r0_32 = %set<c:int|b:tp>%(t);
	%r<c:int|b:tp>% r1_32 = %set1<c:int|b:tp>%((int16_t)0xFFFF);
	return %cast_k<c:int|b:tp,tp>%(%cmpeq<c:int|b:tp>%(r0_32, r1_32));""" },
    "set_k-8": {"format": "long", "code":
"""// long format
	%v<c:int|b:tp>% t[%N<tp>%] = {
		(int8_t)(vals[ 0] ? 0xFF : 0), (int8_t)(vals[ 1] ? 0xFF : 0), (int8_t)(vals[ 2] ? 0xFF : 0), (int8_t)(vals[ 3] ? 0xFF : 0),
		(int8_t)(vals[ 4] ? 0xFF : 0), (int8_t)(vals[ 5] ? 0xFF : 0), (int8_t)(vals[ 6] ? 0xFF : 0), (int8_t)(vals[ 7] ? 0xFF : 0),
		(int8_t)(vals[ 8] ? 0xFF : 0), (int8_t)(vals[ 9] ? 0xFF : 0), (int8_t)(vals[10] ? 0xFF : 0), (int8_t)(vals[11] ? 0xFF : 0),
		(int8_t)(vals[12] ? 0xFF : 0), (int8_t)(vals[13] ? 0xFF : 0), (int8_t)(vals[14] ? 0xFF : 0), (int8_t)(vals[15] ? 0xFF : 0),
		(int8_t)(vals[16] ? 0xFF : 0), (int8_t)(vals[17] ? 0xFF : 0), (int8_t)(vals[18] ? 0xFF : 0), (int8_t)(vals[19] ? 0xFF : 0),
		(int8_t)(vals[20] ? 0xFF : 0), (int8_t)(vals[21] ? 0xFF : 0), (int8_t)(vals[22] ? 0xFF : 0), (int8_t)(vals[23] ? 0xFF : 0),
		(int8_t)(vals[24] ? 0xFF : 0), (int8_t)(vals[25] ? 0xFF : 0), (int8_t)(vals[26] ? 0xFF : 0), (int8_t)(vals[27] ? 0xFF : 0),
		(int8_t)(vals[28] ? 0xFF : 0), (int8_t)(vals[29] ? 0xFF : 0), (int8_t)(vals[30] ? 0xFF : 0), (int8_t)(vals[31] ? 0xFF : 0),
		(int8_t)(vals[32] ? 0xFF : 0), (int8_t)(vals[33] ? 0xFF : 0), (int8_t)(vals[34] ? 0xFF : 0), (int8_t)(vals[35] ? 0xFF : 0),
		(int8_t)(vals[36] ? 0xFF : 0), (int8_t)(vals[37] ? 0xFF : 0), (int8_t)(vals[38] ? 0xFF : 0), (int8_t)(vals[39] ? 0xFF : 0),
		(int8_t)(vals[40] ? 0xFF : 0), (int8_t)(vals[41] ? 0xFF : 0), (int8_t)(vals[42] ? 0xFF : 0), (int8_t)(vals[43] ? 0xFF : 0),
		(int8_t)(vals[44] ? 0xFF : 0), (int8_t)(vals[45] ? 0xFF : 0), (int8_t)(vals[46] ? 0xFF : 0), (int8_t)(vals[47] ? 0xFF : 0),
		(int8_t)(vals[48] ? 0xFF : 0), (int8_t)(vals[49] ? 0xFF : 0), (int8_t)(vals[50] ? 0xFF : 0), (int8_t)(vals[51] ? 0xFF : 0),
		(int8_t)(vals[52] ? 0xFF : 0), (int8_t)(vals[53] ? 0xFF : 0), (int8_t)(vals[54] ? 0xFF : 0), (int8_t)(vals[55] ? 0xFF : 0),
		(int8_t)(vals[56] ? 0xFF : 0), (int8_t)(vals[57] ? 0xFF : 0), (int8_t)(vals[58] ? 0xFF : 0), (int8_t)(vals[59] ? 0xFF : 0),
		(int8_t)(vals[60] ? 0xFF : 0), (int8_t)(vals[61] ? 0xFF : 0), (int8_t)(vals[62] ? 0xFF : 0), (int8_t)(vals[63] ? 0xFF : 0) };
	%r<c:int|b:tp>% r0_32 = %set<c:int|b:tp>%(t);
	%r<c:int|b:tp>% r1_32 = %set1<c:int|b:tp>%((int8_t)0xFF);
	return %cast_k<c:int|b:tp,tp>%(%cmpeq<c:int|b:tp>%(r0_32, r1_32));""" },
    "andb_k" : { "format": "long",  "code":
"""// long format
	return (m0 & m1);""" },
    "andnb_k" : { "format": "long",  "code":
"""// long format
	return ((~m0) & m1);""" },
    "xorb_k": { "format": "long",  "code":
"""// long format
	return (m0 ^ m1);""" },
    "orb_k": { "format": "long",  "code":
"""// long format
	return (m0 | m1);""" },
    "msb-64": { "format": "long", "code":
"""// long format
	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%((int64_t)0x8000000000000000));
	return %andb<tp>%(r0, rm);""" },
    "msb-32": { "format": "long", "code":
"""// long format
	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%((int32_t)0x80000000));
	return %andb<tp>%(r0, rm);""" },
    "msb-16": { "format": "long", "code":
"""// long format
	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%((int16_t)0x8000));
	return %andb<tp>%(r0, rm);""" },
    "msb-8": { "format": "long", "code":
"""// long format
	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%((int8_t)0x80));
	return %andb<tp>%(r0, rm);""" },
    "notb": { "format": "long", "code":
"""// long format
	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%(~0));
	return %andnb<tp>%(r0, rm);""" },
    "notb_k": { "format": "long", "code":
"""// long format
	return ~(m0);""" },
    "testz-8": { "format": "long", "code":
"""// long format
	%r<c:int|b:tp>% r32 = %set0<c:int|b:tp>%();
	%m<c:int|b:tp>% msk = %cmpneq<c:int|b:tp>%(r0, r32);
	return %cast<c:uint|b:64,tp>%(msk == 0);""" },
    "maskz_add": { "format": "long", "code":
"""// long format
	%r<tp>% radd = %add<tp>%(r0, r1);
	%r<tp>% rmsk = %toreg<tp>%(m0);
	return %andb<tp>%(rmsk, radd);""" },

    "hadd_to_scal": { "format": "long", "code":
"""// long format
	return %hadd<tp>%(r0);""" },

	"andb_k_emu": { "format": "long", "code":
"""// long format
	%m<tp>% ret; 
	ret.m = m0.m & m1.m;
	return ret;""" },
    

# algorithm re-used from MIPPv1 
# taken from 
# https://github.com/reyoung/avx_mathfun/blob/master/avx_mathfun.h

# License :
#    AVX implementation of sin, cos, sincos, exp and log

#    Based on "sse_mathfun.h", by Julien Pommier
#    http://gruntthepeon.free.fr/ssemath/

#    Copyright (C) 2012 Giovanni Garberoglio
#    Interdisciplinary Laboratory for Computational Science (LISC)
#    Fondazione Bruno Kessler and University of Trento
#    via Sommarive, 18
#    I-38123 Trento (Italy)

#   This software is provided 'as-is', without any express or implied
#   warranty.  In no event will the authors be held liable for any damages
#   arising from the use of this software.

#   Permission is granted to anyone to use this software for any purpose,
#   including commercial applications, and to alter it and redistribute it
#   freely, subject to the following restrictions:

#   1. The origin of this software must not be misrepresented; you must not
#      claim that you wrote the original software. If you use this software
#      in a product, an acknowledgment in the product documentation would be
#      appreciated but is not required.
#   2. Altered source versions must be plainly marked as such, and must not be
#      misrepresented as being the original software.
#   3. This notice may not be removed or altered from any source distribution.

#   (this is the zlib license)
	"exp_f32": { "format": "long", "code":
"""
    __m512 x = r0.r;
    __m512 tmp, fx;

    __m512i imm0;

    __m512 one = _mm512_set1_ps(1.0f);

    __m512 exp_hi = _mm512_set1_ps(88.3762626647949f);
    __m512 exp_lo = _mm512_set1_ps(-88.3762626647949f);

    __m512 cephes_LOG2EF = _mm512_set1_ps(1.44269504088896341f);
    __m512 cephes_exp_C1 = _mm512_set1_ps(0.693359375f);
    __m512 cephes_exp_C2 = _mm512_set1_ps(-2.12194440e-4f);

    __m512 cephes_exp_p0 = _mm512_set1_ps(1.9875691500E-4f);
    __m512 cephes_exp_p1 = _mm512_set1_ps(1.3981999507E-3f);
    __m512 cephes_exp_p2 = _mm512_set1_ps(8.3334519073E-3f);
    __m512 cephes_exp_p3 = _mm512_set1_ps(4.1665795894E-2f);
    __m512 cephes_exp_p4 = _mm512_set1_ps(1.6666665459E-1f);
    __m512 cephes_exp_p5 = _mm512_set1_ps(5.0000001201E-1f);

    __m512i i0 = _mm512_set1_epi32(0);
    __m512i i0xffffffff = _mm512_set1_epi32(0xFFFFFFFF);
    __m512i i0x7f = _mm512_set1_epi32(0x7F);

    x = _mm512_min_ps(x, exp_hi);
    x = _mm512_max_ps(x, exp_lo);

    fx = _mm512_mul_ps(x, cephes_LOG2EF);
    fx = _mm512_add_ps(fx, _mm512_set1_ps(0.5f));

    tmp = _mm512_floor_ps(fx);

    // if greater, substract 1
    __mmask16 mask2 = _mm512_cmp_ps_mask(tmp, fx, _CMP_GT_OS);
    _mm512 mask = _mm512_mask_blend_ps(mask2, _mm512_castsi512_ps(i0), _mm512_castsi512_ps(i0xffffffff));
    mask =  _mm512_castsi512_ps(_mm512_and_si512(_mm512_castps_si512(mask), _mm512_castps_si512(one)));
    fx = _mm512_sub_ps(tmp, mask);

    tmp = _mm512_mul_ps(fx, cephes_exp_C1);
    __m512 z = _mm512_mul_ps(fx, cephes_exp_C2);
    x = _mm512_sub_ps(x, tmp);
    x = _mm512_sub_ps(x, z);

    z = _mm512_mul_ps(x, x);

    __m512 y = cephes_exp_p0;
    y = _mm512_mul_ps(y, x);
    y = _mm512_add_ps(y, cephes_exp_p1);
    y = _mm512_mul_ps(y, x);
    y = _mm512_add_ps(y, cephes_exp_p2);
    y = _mm512_mul_ps(y, x);
    y = _mm512_add_ps(y, cephes_exp_p3);
    y = _mm512_mul_ps(y, x);
    y = _mm512_add_ps(y, cephes_exp_p4);
    y = _mm512_mul_ps(y, x);
    y = _mm512_add_ps(y, cephes_exp_p5);
    y = _mm512_mul_ps(y, z);
    y = _mm512_add_ps(y, x);
    y = _mm512_add_ps(y, one);

    imm0 = _mm512_cvttps_epi32(fx);
    imm0 = _mm512_add_epi32(imm0, i0x7f);
    imm0 = _mm512_slli_epi32(imm0, 23);
    __m512 pow2n = _mm512_castsi512_ps(imm0);
    y = _mm512_mul_ps(y, pow2n);
    rvd_avx512_float32_t res;
    res.r = y;
    return res;
"""},


	"log_f32": { "format": "long", "code":
"""
    __m512 x = r0.r;
    __m512i imm0;
    __m512 one = _mm512_set1_ps(1.0f);
    __m512 half = _mm512_set1_ps(0.5f);

    __m512i i0 = _mm512_set1_epi32(0);
    __m512i i0xffffffff = _mm512_set1_epi32(0xFFFFFFFF);
    __m512i i0x7f = _mm512_set1_epi32(0x7F);
    
    __m512i min_norm_pos = _mm512_set1_epi32(0x00800000);
    __m512i inv_mant_mask = _mm512_set1_epi32(~0x7f800000);

    __m512 cephes_SQRTHF = _mm512_set1_ps(0.707106781186547524f);
    __m512 cephes_log_p0 = _mm512_set1_ps(7.0376836292E-2f);
    __m512 cephes_log_p1 = _mm512_set1_ps(-1.1514610310E-1f);
    __m512 cephes_log_p2 = _mm512_set1_ps(1.1676998740E-1f);
    __m512 cephes_log_p3 = _mm512_set1_ps(-1.2420140846E-1f);
    __m512 cephes_log_p4 = _mm512_set1_ps(+1.4249322787E-1f);
    __m512 cephes_log_p5 = _mm512_set1_ps(-1.6668057665E-1f);
    __m512 cephes_log_p6 = _mm512_set1_ps(+2.0000714765E-1f);
    __m512 cephes_log_p7 = _mm512_set1_ps(-2.4999993993E-1f);
    __m512 cephes_log_p8 = _mm512_set1_ps(+3.3333331174E-1f);
    __m512 cephes_log_q1 = _mm512_set1_ps(-2.12194440e-4f);
    __m512 cephes_log_q2 = _mm512_set1_ps(0.693359375f);

    __mmask16 invalid_mask2 = _mm512_cmp_ps_mask(x, _mm512_setzero_ps(), _CMP_LE_OS);
    __mm512 invalid_mask = _mm512_mask_blend(invalid_mask2, _mm512_castsi512_ps(i0), _mm512_castsi512_ps(i0xffffffff));

    x = _mm512_max_ps(x, _mm512_castsi512_ps(min_norm_pos));

    imm0 = _mm512_srli_epi32(_mm512_castps_si512(x), 23);

    x = _mm512_castsi512_ps(_mm512_and_si512(_mm512_castps_si512(x), _mm512_castps_si512(inv_mant_mask)));
    x = _mm512_castsi512_ps(_mm512_or_si512(_mm512_castps_si512(x), half));

    imm0 = _mm512_sub_epi32(imm0, i0x7f);
    __m512 e = _mm512_cvtepi32_ps(imm0);

    e = _mm512_add_ps(e, one);

    __mmask16 mask2 = _mm512_cmp_ps_mask(x, cephes_SQRTHF, _CMP_LT_OS);
    __mm512 mask = _mm512_mask_blend_ps(mask2, _mm512_castsi512_ps(i0), _mm512_castsi512_ps(i0xffffffff));
    
    __mm512 tmp = _mm512_castsi512_ps(_mm512_and_si512(_mm512_castps_si512(x), _mm512_castps_si512(mask)));
    x = _mm512_sub_ps(x, one);

    e = _mm512_sub_ps(e, _mm512_castsi512_ps(_mm512_and_si512(_mm512_castps_si512(one), _mm512_castps_si512(mask))));
    x = _mm512_add_ps(x, tmp);

    __m512 z = _mm512_mul_ps(x, x);

    __m512 y = cephes_log_p0;
    y = _mm512_mul_ps(y, x);
    y = _mm512_add_ps(y, cephes_log_p1);
    y = _mm512_mul_ps(y, x);
    y = _mm512_add_ps(y, cephes_log_p2);
    y = _mm512_mul_ps(y, x);
    y = _mm512_add_ps(y, cephes_log_p3);
    y = _mm512_mul_ps(y, x);
    y = _mm512_add_ps(y, cephes_log_p4);
    y = _mm512_mul_ps(y, x);
    y = _mm512_add_ps(y, cephes_log_p5);
    y = _mm512_mul_ps(y, x);
    y = _mm512_add_ps(y, cephes_log_p6);
    y = _mm512_mul_ps(y, x);
    y = _mm512_add_ps(y, cephes_log_p7);
    y = _mm512_mul_ps(y, x);
    y = _mm512_add_ps(y, cephes_log_p8);
    y = _mm512_mul_ps(y, z);

    y = _mm512_mul_ps(y, z);

    tmp = _mm512_mul_ps(e, cephes_log_q1);
    y = _mm512_add_ps(y, tmp);

    tmp = _mm512_mul_ps(z, half);
    y = _mm512_sub_ps(y, tmp);

    tmp = _mm512_mul_ps(e, cephes_log_q2);
    x = _mm512_add_ps(x, y);
    x = _mm512_add_ps(x, tmp);
    x = _mm512_castsi512_ps(_mm512_or_si512(_mm512_castps_si512(x), _mm512_castps_si512(invalid_mask)));

    rvd_avx512_float32_t res;
    res.r = x;
    return res;
"""},

	# finally :)
    "pow_f32": { "format": "long", "code":
"""// long format
    %r<tp>% logx = %log<tp>%(r0);
    %r<tp>% ylogx = %mul<tp>%(r1, logx);
    %r<tp>% res = %exp<tp>%(ylogx);
    return res;
"""},

}

implems_emu_avx512 = {
    "toreg"  : [
        { "datatypes": all_datatypes,                "template": tpl_implem_emu_avx512["toreg"]                                       } ], # toreg
    "tomsk": [
        { "datatypes": all_datatypes,                "template": tpl_implem_emu_avx512["tomsk"]                                       } ], # tomsk
    "get": [
        { "datatypes": all_datatypes,                "template": tpl_implem_emu_avx512["get"]                                         } ], # get
    "get_k": [
        { "datatypes": all_datatypes,                "template": tpl_implem_emu_avx512["get_k"]                                       } ], # get_k
    "set1_k":[
        { "datatypes": all_64bit,                    "template": tpl_implem_emu_avx512["set1_k-8"]                                    },
        { "datatypes": all_32bit,                    "template": tpl_implem_emu_avx512["set1_k-16"]                                   },
        { "datatypes": all_16bit,                    "template": tpl_implem_emu_avx512["set1_k-32"]                                   },
        { "datatypes": all_8bit,                     "template": tpl_implem_emu_avx512["set1_k-64"]                                   } ], # set1_k
    "set_k" : [
        { "datatypes": all_64bit,                    "template": tpl_implem_emu_avx512["set_k-64"],                                   },
        { "datatypes": all_32bit,                    "template": tpl_implem_emu_avx512["set_k-32"],                                   },
        { "datatypes": all_16bit,                    "template": tpl_implem_emu_avx512["set_k-16"],                                   },
        { "datatypes": all_8bit,                     "template": tpl_implem_emu_avx512["set_k-8"],                                    } ], # set_k

#   "andnb_k": [
#       { "datatypes": all_datatypes,                "template": tpl_implem_emu_avx512["andnb_k"],      "if": "defined(__AVX512BW__)" } ], # andnb_k
#   "xorb_k": [
#       { "datatypes": all_datatypes,                "template": tpl_implem_emu_avx512["xorb_k"],       "if": "defined(__AVX512BW__)" } ], # xorb_k
#   "orb_k": [
#       { "datatypes": all_datatypes,                "template": tpl_implem_emu_avx512["orb_k"],        "if": "defined(__AVX512BW__)" } ], # orb_k
#   "notb_k": [
#       { "datatypes": all_datatypes,                "template": tpl_implem_emu_avx512["notb_k"]                                      } ], # notb_k

	"andb_k": [
        { "datatypes": all_64bit,                    "template": tpl_implem_emu_avx512["andb_k_emu"],   "if": "!defined(__AVX512DQ__)"},
        { "datatypes": all_16bit + all_8bit,         "template": tpl_implem_emu_avx512["andb_k_emu"],   "if": "!defined(__AVX512BW__)"} ], # andb_k
    "msb": [
        { "datatypes": [float64],                    "template": tpl_implem_emu_avx512["msb-64"],       "if": "defined(__AVX512DQ__)" },
        { "datatypes": [int64, uint64],              "template": tpl_implem_emu_avx512["msb-64"],                                     },
        { "datatypes": [float32],                    "template": tpl_implem_emu_avx512["msb-32"],       "if": "defined(__AVX512DQ__)" },
        { "datatypes": [int32, uint32],              "template": tpl_implem_emu_avx512["msb-32"],                                     },
        { "datatypes": [int16, uint16],              "template": tpl_implem_emu_avx512["msb-16"],       "if": "defined(__AVX512BW__)" },
        { "datatypes": [int8, uint8],                "template": tpl_implem_emu_avx512["msb-8"],        "if": "defined(__AVX512BW__)" } ], # msb
    "notb": [
        { "datatypes": all_float,                    "template": tpl_implem_emu_avx512["notb"],         "if": "defined(__AVX512DQ__)" },
        { "datatypes": [int64, uint64],              "template": tpl_implem_emu_avx512["notb"],                                       },
        { "datatypes": [int32, uint32],              "template": tpl_implem_emu_avx512["notb"],                                       },
        { "datatypes": [int16, uint16],              "template": tpl_implem_emu_avx512["notb"],         "if": "defined(__AVX512BW__)" },
        { "datatypes": [int8, uint8],                "template": tpl_implem_emu_avx512["notb"],         "if": "defined(__AVX512BW__)" } ], # notb
    "maskz_add": [
        { "datatypes": all_int,                      "template": tpl_implem_emu_avx512["maskz_add"]                                   } ], # maskz_add

    "hadd_to_scal": [
        { "datatypes": [float64, int64],             "template": tpl_implem_emu_avx512["hadd_to_scal"]                                },
        { "datatypes": [float32, int32],             "template": tpl_implem_emu_avx512["hadd_to_scal"]                                },
        { "datatypes": [int16, uint16],              "template": tpl_implem_emu_avx512["hadd_to_scal"]                                },
        { "datatypes": [int8, uint8],                "template": tpl_implem_emu_avx512["hadd_to_scal"]                                } ], # hadd_to_scal
        
	"exp": [
		{ "datatypes": [float32],                    "template": tpl_implem_emu_avx512["exp_f32"]								  } ],
    "log": [
		{ "datatypes": [float32],                    "template": tpl_implem_emu_avx512["log_f32"]								  } ],
    "pow": [
		{ "datatypes": [float32],                    "template": tpl_implem_emu_avx512["pow_f32"]									  } ],
}
