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
	"exp_f32_fma": { "format": "long", "code":
"""
	%r<tp>% tmp = %set0<tp>%(), fx;
    %r<c:int|b:tp>% imm0;
    %r<tp>% one = %set1<tp>%(1.0f);
    
    %r<tp>% exp_hi = %set1<tp>%(88.3762626647949f),
			exp_lo = %set1<tp>%(-88.3762626647949f);
            
    
	%r<tp>% cephes_LOG2EF = %set1<tp>%(1.44269504088896341f),
			cephes_exp_C1 = %set1<tp>%(0.693359375f),
            cephes_exp_C2 = %set1<tp>%(-2.12194440e-4f);

    %r<tp>% cephes_exp_p0 = %set1<tp>%(1.9875691500E-4f),
			cephes_exp_p1 = %set1<tp>%(1.3981999507E-3f),
			cephes_exp_p2 = %set1<tp>%(8.3334519073E-3f),
			cephes_exp_p3 = %set1<tp>%(4.1665795894E-2f),
			cephes_exp_p4 = %set1<tp>%(1.6666665459E-1f),
			cephes_exp_p5 = %set1<tp>%(5.0000001201E-1f);
    
    %r<c:uint|b:tp>% r_0x0 = %set1<c:uint|b:tp>%((uint32_t)0);
    %r<c:uint|b:tp>% r_0xffffffff = %set1<c:uint|b:tp>%((uint32_t)0xffffffff);
    
    %r<tp>% x = %min<tp>%(r0, exp_hi);
    x = %max<tp>%(x, exp_lo);
    
    fx = %fmadd<tp>%(x, cephes_LOG2EF, %set1<tp>%(0.5f));
    
    tmp.r =  _mm512_floor_ps(fx.r);
    
    %m<tp>% mask2;
    mask2 = %cmpgt<tp>%(tmp, fx); // hack
    
    %r<tp>% mask;
    mask =  %blend<tp>%(%cast<c:uint|b:tp,tp>%(r_0xffffffff), %cast<c:uint|b:tp,tp>%(r_0x0), mask2);
    mask.r = _mm512_castsi512_ps(_mm512_and_si512(_mm512_castps_si512(mask.r), _mm512_castps_si512(one.r)));
    
    fx = %sub<tp>%(tmp, mask);
    
    tmp = %mul<tp>%(fx, cephes_exp_C1);
    %r<tp>% z = %mul<tp>%(x, cephes_exp_C2);
    
    x = %sub<tp>%(x, tmp);
    x = %sub<tp>%(x, z);
    
    z = %mul<tp>%(x, x);
    
    %r<tp>% y = cephes_exp_p0;
	y = %fmadd<tp>%(y, x, cephes_exp_p1);
	y = %fmadd<tp>%(y, x, cephes_exp_p2);
	y = %fmadd<tp>%(y, x, cephes_exp_p3);
	y = %fmadd<tp>%(y, x, cephes_exp_p4);
	y = %fmadd<tp>%(y, x, cephes_exp_p5);

	y = %fmadd<tp>%(y, z, x);
	y = %add<tp>%(y, one);
    
    imm0.r = _mm512_cvttps_epi32(fx.r);

	%r<c:uint|b:tp>% r_0x7f = %set1<c:uint|b:tp>%((uint32_t)0x7f);
	imm0.r = _mm512_add_epi32(imm0.r, _mm512_castps_si512(_mm512_castsi512_ps(r_0x7f.r)));
    imm0.r =  _mm512_slli_epi32(imm0.r, 23);
    %r<tp>% pow2n = %cast<c:int|b:tp,tp>%(imm0);
	y = %mul<tp>%(y, pow2n);
    
    return y;
"""},


	"log_f32_fma": { "format": "long", "code":
"""
	%r<c:int|b:tp>% imm0;
    %r<tp>% one = %set1<tp>%(1.0f);
    
    %r<tp>% min_norm_pos = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%((int32_t)0x00800000));
    %r<tp>% inv_mant_mask = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%((int32_t)~0x7f800000));
    // %r<tp>% mant_mask = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%((int32_t)0x7f800000));
    %r<tp>% cephes_SQRTHF = %set1<tp>%(0.707106781186547524f);
    %r<tp>% cephes_log_p0 = %set1<tp>%(7.0376836292E-2f);
	%r<tp>% cephes_log_p1 = %set1<tp>%(- 1.1514610310E-1f);
	%r<tp>% cephes_log_p2 = %set1<tp>%(1.1676998740E-1f);
	%r<tp>% cephes_log_p3 = %set1<tp>%(- 1.2420140846E-1f);
	%r<tp>% cephes_log_p4 = %set1<tp>%(+ 1.4249322787E-1f);
	%r<tp>% cephes_log_p5 = %set1<tp>%(- 1.6668057665E-1f);
	%r<tp>% cephes_log_p6 = %set1<tp>%(+ 2.0000714765E-1f);
	%r<tp>% cephes_log_p7 = %set1<tp>%(- 2.4999993993E-1f);
	%r<tp>% cephes_log_p8 = %set1<tp>%(+ 3.3333331174E-1f);
	%r<tp>% cephes_log_q1 = %set1<tp>%(-2.12194440e-4f);
	%r<tp>% cephes_log_q2 = %set1<tp>%(0.693359375f);

    %r<tp>% invalid_mask; 
    invalid_mask.r = %cmple<tp>%(r0, %set0<tp>%()).m; // hack
    
    %r<tp>% x = %max<tp>%(r0, min_norm_pos);
    
    imm0.r = _mm256_srli_epi32(_mm256_castps_si256(x.r), 23);
    x.r = _mm256_and_ps(x.r, inv_mant_mask.r);
	x.r = _mm256_or_ps(x.r, %set1<tp>%((float)0.5).r);
    
    imm0 = %sub<c:int|b:tp>%(imm0, %set1<c:int|b:tp>%((int32_t)0x7f));
    
    %r<tp>% e;
    e.r = _mm256_cvtepi32_ps(imm0.r);
    e = %add<tp>%(e, one);
    
    %r<tp>% mask;
    mask.r = %cmplt<tp>%(x, cephes_SQRTHF).m; // hack
	%r<tp>% tmp = %andb<tp>%(x, mask);
    x = %sub<tp>%(x, one);
    e = %sub<tp>%(e, %andb<tp>%(one, mask));
    
    x = %add<tp>%(x, tmp);
    %r<tp>% z = %mul<tp>%(x, x);

    %r<tp>% y = cephes_log_p0;

    y = %fmadd<tp>%(y, x, cephes_log_p1);
    y = %fmadd<tp>%(y, x, cephes_log_p2);
    y = %fmadd<tp>%(y, x, cephes_log_p3);
    y = %fmadd<tp>%(y, x, cephes_log_p4);
    y = %fmadd<tp>%(y, x, cephes_log_p5);
    y = %fmadd<tp>%(y, x, cephes_log_p6);
    y = %fmadd<tp>%(y, x, cephes_log_p7);
    y = %fmadd<tp>%(y, x, cephes_log_p8);

    y = %mul<tp>%(y, z);

    y = %fmadd<tp>%(e, cephes_log_q1, y);

    tmp = %mul<tp>%(z, %set1<tp>%(0.5f));
    y = %sub<tp>%(y, tmp);
    
    tmp = %mul<tp>%(e, cephes_log_q2);
    x = %add<tp>%(x, y);
    x = %add<tp>%(x, tmp);
    x = %orb<tp>%(x, invalid_mask);
	return x;
"""},

	"log_f32_fma": { "format": "long", "code":
"""
	%r<c:int|b:tp>% imm0;
    %r<tp>% one = %set1<tp>%(1.0f);
    
    %r<tp>% min_norm_pos = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%((int32_t)0x00800000));
    %r<tp>% inv_mant_mask = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%((int32_t)~0x7f800000));
    %r<tp>% cephes_SQRTHF = %set1<tp>%(0.707106781186547524f);
    %r<tp>% cephes_log_p0 = %set1<tp>%(7.0376836292E-2f);
	%r<tp>% cephes_log_p1 = %set1<tp>%(- 1.1514610310E-1f);
	%r<tp>% cephes_log_p2 = %set1<tp>%(1.1676998740E-1f);
	%r<tp>% cephes_log_p3 = %set1<tp>%(- 1.2420140846E-1f);
	%r<tp>% cephes_log_p4 = %set1<tp>%(+ 1.4249322787E-1f);
	%r<tp>% cephes_log_p5 = %set1<tp>%(- 1.6668057665E-1f);
	%r<tp>% cephes_log_p6 = %set1<tp>%(+ 2.0000714765E-1f);
	%r<tp>% cephes_log_p7 = %set1<tp>%(- 2.4999993993E-1f);
	%r<tp>% cephes_log_p8 = %set1<tp>%(+ 3.3333331174E-1f);
	%r<tp>% cephes_log_q1 = %set1<tp>%(-2.12194440e-4f);
	%r<tp>% cephes_log_q2 = %set1<tp>%(0.693359375f);
    
    // define as uint to avoid implicit cast to float bc set1 argument is type of returned register
    %r<c:uint|b:tp>% r_0xffffffff = %set1<c:uint|b:tp>%((uint32_t)0xffffffff);
    %r<c:uint|b:tp>% r_0x0 = %set1<c:uint|b:tp>%((uint32_t)0x0);
	%r<c:int|b:tp>% r_0x7f = %set1<c:int|b:tp>%((uint32_t)0x7f);

    %m<tp>% invalid_mask2 = %cmple<tp>%(r0, cephes_SQRTHF); // hack
    %r<tp>% invalid_mask = %blend<tp>%(%cast<c:uint|b:tp,tp>%(r_0xffffffff), %cast<c:uint|b:tp,tp>%(r_0x0), invalid_mask2);
    
    %r<tp>% x = %max<tp>%(r0, min_norm_pos);
    
    imm0.r = _mm512_srli_epi32(_mm512_castps_si512(x.r), 23);
    // todo : make mipp-like
    x.r = _mm512_castsi512_ps(_mm512_and_si512(_mm512_castps_si512(x.r), _mm512_castps_si512(inv_mant_mask.r)));
	x.r = _mm512_castsi512_ps(_mm512_or_si512(_mm512_castps_si512(x.r), _mm512_castps_si512(%set1<tp>%((float)0.5).r)));
    
    imm0 = %sub<c:int|b:tp>%(imm0, r_0x7f);
    
    %r<tp>% e;
    e.r = _mm512_cvtepi32_ps(imm0.r);
    e = %add<tp>%(e, one);
    
    %m<tp>% mask2 = %cmplt<tp>%(x, cephes_SQRTHF);
    %r<tp>% mask = %blend<tp>%(%cast<c:uint|b:tp,tp>%(r_0xffffffff), %cast<c:uint|b:tp,tp>%(r_0x0), mask2);
    
    // MIPP andb should be defined for floats as well
	%r<tp>% tmp = %andb<tp>%(x, mask);
    x = %sub<tp>%(x, one);
    e = %sub<tp>%(e, %andb<tp>%(one, mask));
    
    x = %add<tp>%(x, tmp);
    %r<tp>% z = %mul<tp>%(x, x);

    %r<tp>% y = cephes_log_p0;

    y = %fmadd<tp>%(y, x, cephes_log_p1);
    y = %fmadd<tp>%(y, x, cephes_log_p2);
    y = %fmadd<tp>%(y, x, cephes_log_p3);
    y = %fmadd<tp>%(y, x, cephes_log_p4);
    y = %fmadd<tp>%(y, x, cephes_log_p5);
    y = %fmadd<tp>%(y, x, cephes_log_p6);
    y = %fmadd<tp>%(y, x, cephes_log_p7);
    y = %fmadd<tp>%(y, x, cephes_log_p8);

    y = %mul<tp>%(y, z);

    y = %fmadd<tp>%(e, cephes_log_q1, y);

    tmp = %mul<tp>%(z, %set1<tp>%(0.5f));
    y = %sub<tp>%(y, tmp);
    
    tmp = %mul<tp>%(e, cephes_log_q2);
    x = %add<tp>%(x, y);
    x = %add<tp>%(x, tmp);
    x = %orb<tp>%(x, invalid_mask);
	return x;
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
        
	# "exp": [
	# 	{ "datatypes": [float32],                    "template": tpl_implem_emu_avx512["exp_f32_fma"]								  } ],
    # "log": [
	# 	{ "datatypes": [float32],                    "template": tpl_implem_emu_avx512["log_f32_fma"]								  } ],
    # "pow": [
	# 	{ "datatypes": [float32],                    "template": tpl_implem_emu_avx512["pow_f32"]									  } ],
}
