from tools import *

""" "tpl_implem_emu" dictionary:
    - Purpose: to provide a collection of emulation functions for missing SIMD instructions and then provide the operands needed to simulate the behavior of that instruction.
    - Use: it is used to implement emulation for specific SIMD instructions that are not directly available in the AVX architecture.
"""
tpl_implem_emu_avx = {
    "hadd_2":     { "format": "long",  "code": "return %getfirst<tp>%(%hadd<tp>%(r0));" },
    "hmul_2":     { "format": "long",  "code": "return %getfirst<tp>%(%hmul<tp>%(r0));" },
    "hmin_2":     { "format": "long",  "code": "return %getfirst<tp>%(%hmin<tp>%(r0));" },
    "hmax_2":     { "format": "long",  "code": "return %getfirst<tp>%(%hmax<tp>%(r0));" },
    "cmpeq-1":    { "format": "long",  "code": "return %cast_k<c:float,tp>%(%cmpeq<c:float>%(%cast<tp,c:float>%(r0), %cast<tp,c:float>%(r1)));" },
    "cmpeq-2":    { "format": "long",  "code": "return %cast_k<c:int,tp>%(%cmpeq<c:int>%(%cast<tp,c:int>%(r0), %cast<tp,c:int>%(r1)));" },
    "cmpneq":     { "format": "long",  "code": "return %notb_k<tp>%(%cmpeq<tp>%(r0, r1));" },
    "getfirst":   { "format": "long",  "code": "return %get<tp>%(r0, 0);" },
    "set_k-64f":  { "format": "long",  "code": "return %cast_k<c:int,tp>%(mipp_avx_set_k_int64(vals));" },
    "set_k-32f":  { "format": "long",  "code": "return %cast_k<c:int,tp>%(mipp_avx_set_k_int32(vals));" },
    "set-64f":    { "format": "short", "code": "_mm256_set_pd(vals[3], vals[2], vals[1], vals[0]);" },
    "set-32f":    { "format": "short", "code": "_mm256_set_ps(vals[7], vals[6], vals[5], vals[4], vals[3], vals[2], vals[1], vals[0]);" },
    "set-64":     { "format": "short", "code": "_mm256_set_epi64x(vals[3], vals[2], vals[1], vals[0]);" },
    "set-32":     { "format": "short", "code": "_mm256_set_epi32(vals[7], vals[6], vals[5], vals[4], vals[3], vals[2], vals[1], vals[0]);" },
    "set-16":     { "format": "short", "code": """_mm256_set_epi16(
		vals[15], vals[14], vals[13], vals[12],
		vals[11], vals[10], vals[ 9], vals[ 8],
		vals[ 7], vals[ 6], vals[ 5], vals[ 4],
		vals[ 3], vals[ 2], vals[ 1], vals[ 0]);""" },
    "set-8": { "format": "short", "code": """_mm256_set_epi8(
		(int8_t)vals[31], (int8_t)vals[30], (int8_t)vals[29], (int8_t)vals[28],
		(int8_t)vals[27], (int8_t)vals[26], (int8_t)vals[25], (int8_t)vals[24],
		(int8_t)vals[23], (int8_t)vals[22], (int8_t)vals[21], (int8_t)vals[20],
		(int8_t)vals[19], (int8_t)vals[18], (int8_t)vals[17], (int8_t)vals[16],
		(int8_t)vals[15], (int8_t)vals[14], (int8_t)vals[13], (int8_t)vals[12],
		(int8_t)vals[11], (int8_t)vals[10], (int8_t)vals[ 9], (int8_t)vals[ 8],
		(int8_t)vals[ 7], (int8_t)vals[ 6], (int8_t)vals[ 5], (int8_t)vals[ 4],
		(int8_t)vals[ 3], (int8_t)vals[ 2], (int8_t)vals[ 1], (int8_t)vals[ 0]);""" },
    "set_k-64": { "format": "short", "code": """_mm256_set_epi64x(
		vals[3] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0,
		vals[2] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0,
		vals[1] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0,
		vals[0] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0);""" },
    "set_k-32": { "format": "short", "code": """_mm256_set_epi32(
		vals[7] ? 0xFFFFFFFF : 0, vals[6] ? 0xFFFFFFFF : 0,
		vals[5] ? 0xFFFFFFFF : 0, vals[4] ? 0xFFFFFFFF : 0,
		vals[3] ? 0xFFFFFFFF : 0, vals[2] ? 0xFFFFFFFF : 0,
		vals[1] ? 0xFFFFFFFF : 0, vals[0] ? 0xFFFFFFFF : 0);""" },
    "set_k-16": { "format": "short", "code": """_mm256_set_epi16(
		vals[15] ? 0xFFFF : 0, vals[14] ? 0xFFFF : 0,
		vals[13] ? 0xFFFF : 0, vals[12] ? 0xFFFF : 0,
		vals[11] ? 0xFFFF : 0, vals[10] ? 0xFFFF : 0,
		vals[ 9] ? 0xFFFF : 0, vals[ 8] ? 0xFFFF : 0,
		vals[ 7] ? 0xFFFF : 0, vals[ 6] ? 0xFFFF : 0,
		vals[ 5] ? 0xFFFF : 0, vals[ 4] ? 0xFFFF : 0,
		vals[ 3] ? 0xFFFF : 0, vals[ 2] ? 0xFFFF : 0,
		vals[ 1] ? 0xFFFF : 0, vals[ 0] ? 0xFFFF : 0);""" },
    "set_k-8": { "format": "short", "code": """_mm256_set_epi8(
		vals[31] ? 0xFF : 0, vals[30] ? 0xFF : 0, vals[29] ? 0xFF : 0, vals[28] ? 0xFF : 0,
		vals[27] ? 0xFF : 0, vals[26] ? 0xFF : 0, vals[25] ? 0xFF : 0, vals[24] ? 0xFF : 0,
		vals[23] ? 0xFF : 0, vals[22] ? 0xFF : 0, vals[21] ? 0xFF : 0, vals[20] ? 0xFF : 0,
		vals[19] ? 0xFF : 0, vals[18] ? 0xFF : 0, vals[17] ? 0xFF : 0, vals[16] ? 0xFF : 0,
		vals[15] ? 0xFF : 0, vals[14] ? 0xFF : 0, vals[13] ? 0xFF : 0, vals[12] ? 0xFF : 0,
		vals[11] ? 0xFF : 0, vals[10] ? 0xFF : 0, vals[ 9] ? 0xFF : 0, vals[ 8] ? 0xFF : 0,
		vals[ 7] ? 0xFF : 0, vals[ 6] ? 0xFF : 0, vals[ 5] ? 0xFF : 0, vals[ 4] ? 0xFF : 0,
		vals[ 3] ? 0xFF : 0, vals[ 2] ? 0xFF : 0, vals[ 1] ? 0xFF : 0, vals[ 0] ? 0xFF : 0);""" },
    "set1_k-8": { "format": "long", "code":
"""// long format
	%r<c:int>% tmp1;
	tmp1.r = _mm256_set1_epi8(v0 ? (int8_t)0xFF : (int8_t)0);
	%r<tp>% tmp2 = %cast<c:int,tp>%(tmp1);
	return %tomsk<tp>%(tmp2);""" },
    "set1_k-16": { "format": "long", "code":
"""// long format
	%r<c:int>% tmp1;
	tmp1.r = _mm256_set1_epi16(v0 ? (int16_t)0xFFFF : (int16_t)0);
	%r<tp>% tmp2 = %cast<c:int,tp>%(tmp1);
	return %tomsk<tp>%(tmp2);""" },
    "set1_k-32": { "format": "long", "code":
"""// long format
	%r<c:int>% tmp1;
	tmp1.r = _mm256_set1_epi32(v0 ? (int32_t)0xFFFFFFFF : (int32_t)0);
	%r<tp>% tmp2 = %cast<c:int,tp>%(tmp1);
	return %tomsk<tp>%(tmp2);""" },
    "set1_k-64": { "format": "long", "code":
"""// long format
	%r<c:int>% tmp1;
	tmp1.r = _mm256_set1_epi64x(v0 ? (int64_t)0xFFFFFFFFFFFFFFFF : (int64_t)0);
	%r<tp>% tmp2 = %cast<c:int,tp>%(tmp1);
	return %tomsk<tp>%(tmp2);""" },
    "blend-1": { "format": "long", "code":
"""// long format
	%r<c:float|b:tp>% r0f = %cast<tp,c:float|b:tp>%(r0);
	%r<c:float|b:tp>% r1f = %cast<tp,c:float|b:tp>%(r1);
	%m<c:float|b:tp>% m0f = %cast_k<tp,c:float|b:tp>%(m0);
	%r<c:float|b:tp>% resf = %blend<c:float|b:tp>%(r0f, r1f, m0f);
	return %cast<c:float|b:tp,tp>%(resf);""" },
    # use intrinsics for or and andnot 
    "blend-2": { "format": "long", "code":
"""// long format
	%r<c:float|b:32>% rmi = %cast<tp,c:float|b:32>%(%toreg<tp>%(m0));
	%r<c:float|b:32>% r0i = %cast<tp,c:float|b:32>%(r0);
	%r<c:float|b:32>% r1i = %cast<tp,c:float|b:32>%(r1);

	%r<c:float|b:32>% resi;
    resi.r =  _mm256_or_ps(
        _mm256_and_ps(r1i.r, rmi.r),
        _mm256_andnot_ps(rmi.r, r0i.r));
	%r<tr>% res = %cast<c:float|b:32,tr>%(resi);
	return res;""" },
    "fmadd": { "format": "long", "code":
"""// long format
	%r<tp>% rmul = %mul<tp>%(r0, r1);
	%r<tp>% res = %add<tp>%(rmul, r2);
	return res;""" },
    "fnmadd": { "format": "long", "code":
"""// long format
	%r<tp>% rmul = %mul<tp>%(r0, r1);
	%r<tp>% tmp = %set0<tp>%();
	tmp = %sub<tp>%(tmp, rmul);
	%r<tp>% res = %add<tp>%(tmp, r2);
	return res;""" },
    "fmsub": { "format": "long", "code":
"""// long format
	%r<tp>% rmul = %mul<tp>%(r0, r1);
	%r<tp>% res = %sub<tp>%(rmul, r2);
	return res;""" },
    "fnmsub": { "format": "long", "code":
"""//long format
	%r<tp>% rmul = %mul<tp>%(r0, r1);
	%r<tp>% tmp = %set0<tp>%();
	tmp = %sub<tp>%(tmp, rmul);
	%r<tp>% res = %sub<tp>%(tmp, r2);
	return res;""" },
    "arith_2args_1msk": { "format": "long", "code":
"""// long format
	%r<tp>% res = %{{ instr_name }}<tp>%(r0, r1);
	return %blend<tp>%(res, r2, m0);""" },
    "arith_2args_1msk_1reg": { "format": "long", "code":
"""// long format
	%r<tp>% rz = %set0<tp>%();
	return %{{ instr_name }}<tp>%(r0, r1, m0, rz);""" },
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
    "notb-64": { "format": "long", "code":
"""// long format
	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%((int64_t)0xFFFFFFFFFFFFFFFF));
	return %andnb<tp>%(r0, rm);""" },
    "notb-32": { "format": "long", "code":
"""// long format
	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%((int32_t)0xFFFFFFFF));
	return %andnb<tp>%(r0, rm);""" },
    "notb-16": { "format": "long", "code":
"""// long format
	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%((int16_t)0xFFFF));
	return %andnb<tp>%(r0, rm);""" },
    "notb-8": { "format": "long", "code":
"""// long format
	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%((int8_t)0xFF));
	return %andnb<tp>%(r0, rm);""" },
    "notb_k-64": { "format": "long", "code":
"""// long format
	%m<tp>% mm = %cast_k<c:int|b:tp,tp>%(%tomsk<c:int|b:tp>%(%set1<c:int|b:tp>%((int64_t)0xFFFFFFFFFFFFFFFF)));
	return %andnb_k<tp>%(m0, mm);""" },
    "notb_k-32": { "format": "long", "code":
"""// long format
	%m<tp>% mm = %cast_k<c:int|b:tp,tp>%(%tomsk<c:int|b:tp>%(%set1<c:int|b:tp>%((int32_t)0xFFFFFFFF)));
	return %andnb_k<tp>%(m0, mm);""" },
    "notb_k-16": { "format": "long", "code":
"""// long format
	%m<tp>% mm = %cast_k<c:int|b:tp,tp>%(%tomsk<c:int|b:tp>%(%set1<c:int|b:tp>%((int16_t)0xFFFF)));
	return %andnb_k<tp>%(m0, mm);""" },
    "notb_k-8": { "format": "long", "code":
"""// long format
	%m<tp>% mm = %cast_k<c:int|b:tp,tp>%(%tomsk<c:int|b:tp>%(%set1<c:int|b:tp>%((int8_t)0xFF)));
	return %andnb_k<tp>%(m0, mm);""" },
    "testz_2": { "format": "long", "code":
"""// long format
	%r<c:int|b:32>% r32 = %set1<c:int|b:32>%(-1);
	%m<c:int|b:32>% m32 = %tomsk<c:int|b:32>%(r32);
	return %testz<tp>%(m0, %cast_k<c:int|b:32,tp>%(m32));""" },
    "get": { "format": "long", "code":
"""// long format
	%v<tp>% t[%N<tp>%];
	%storeu<tp>%(t, r0);
	return t[v0];""" },
    "get_k": { "format": "long", "code":
"""// long format
	%v<tp>% tmp[%N<tp>%];
	%r<tp>% rmsk =%toreg<tp>%(m0);
	%storeu<tp>%(tmp, rmsk);
	return (int32_t) tmp[v0];""" },
    "maskz_add": { "format": "long", "code":
"""// long format
	%r<tp>% radd = %add<tp>%(r0, r1);
	%r<tp>% rmsk =%toreg<tp>%(m0);
	return %andb<tp>%(rmsk, radd);""" },
    "gather_seq": { "format": "long", "code":
 """// long format
	%v<tp>% t[%N<tp>%];
	%storeu<tp>%(t, vi);
	%v<tp>% data[%N<tp>%];
	for (int i = 0; i < %N<tp>%; i++)
		data[i] = p0[t[i]];
	return %loadu<tp>%(data);""" },
    "maskz_gather": { "format": "long", "code":
 """// long format
	%r<tp>% rgather = %gather<tp>%(p0,vi);
	%r<tp>% rmsk =%toreg<tp>%(m0);
	return %andb<tp>%(rmsk, rgather);""" },
    "hadd_to_scal": { "format": "long", "code":
"""// long format
	return  %hadd<tp>%(r0);""" },


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
    
    %r<tp>% x = %min<tp>%(r0, exp_hi);
    x = %max<tp>%(x, exp_lo);
    
    x = %mul<tp>%(x, cephes_LOG2EF);
	fx = %add<tp>%(x, %set1<tp>%(0.5f));
    
    tmp.r =  _mm256_floor_ps(fx.r);
    
    %r<tp>% mask; 
    mask.r = %cmpgt<tp>%(tmp, fx).m; // hack
    mask = %andb<tp>%(mask, one);
    fx = %sub<tp>%(tmp, mask);
    
    tmp = %mul<tp>%(fx, cephes_exp_C1);
    %r<tp>% z = %mul<tp>%(x, cephes_exp_C2);
    
    %r<tp>% y = cephes_exp_p0;
	y = %fmadd<tp>%(y, x, cephes_exp_p1);
	y = %fmadd<tp>%(y, x, cephes_exp_p2);
	y = %fmadd<tp>%(y, x, cephes_exp_p3);
	y = %fmadd<tp>%(y, x, cephes_exp_p4);
	y = %fmadd<tp>%(y, x, cephes_exp_p5);

	y = %fmadd<tp>%(y, z, x);
	y = %add<tp>%(y, one);
    
    imm0.r = _mm256_cvttps_epi32(fx.r);

    imm0 = %add<c:int|b:tp>%(imm0, %set1<c:int|b:tp>%((int32_t)0x7f));
    imm0.r = _mm256_slli_epi32(imm0.r, 23);
    %r<tp>% pow2n = %cast<c:int|b:tp,tp>%(imm0);
	y = %mul<tp>%(y, pow2n);
    
    return y;
"""},


	"log_f32_nofma": { "format": "long", "code":
"""
	%r<c:int|b:tp>% imm0;
    %r<tp>% one = %set1<tp>%(1.0f);
    
    %r<tp>% min_norm_pos = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%((int32_t)0x00800000));
    %r<tp>% inv_mant_mask = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%((int32_t)~0x7f800000));
    %r<tp>% mant_mask = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%((int32_t)0x7f800000));
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
    
    imm0.r = _mm256_srli_epi32(x.r, 23);
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
    y = %mul<tp>%(y,x);
	y = %add<tp>%(y, cephes_log_p1);
    y = %mul<tp>%(y,x);
	y = %add<tp>%(y, cephes_log_p2);
    y = %mul<tp>%(y,x);
	y = %add<tp>%(y, cephes_log_p3);
    y = %mul<tp>%(y,x);
	y = %add<tp>%(y, cephes_log_p4);
    y = %mul<tp>%(y,x);
	y = %add<tp>%(y, cephes_log_p5);
    y = %mul<tp>%(y,x);
	y = %add<tp>%(y, cephes_log_p6);
    y = %mul<tp>%(y,x);
	y = %add<tp>%(y, cephes_log_p7);
    y = %mul<tp>%(y,x);
	y = %add<tp>%(y, cephes_log_p8);
    
    y = %mul<tp>%(y, z);
    
    tmp = %mul<tp>%(e, cephes_log_q1);
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

	"exp_f64": { "format": "long", "code":
"""// long format"""},

	"log_f64": { "format": "long", "code":
"""// long format"""},
}

""" "implems_emu" dictionary:
    -Purpose: This dictionary contains implementation models for various emulated functions.
    -Use: During the generation phase, this dictionary is used to select the appropriate implementation model for a specific emulated function and the datatypes.
"""
implems_emu_avx = {
    "set" :[
        { "datatypes": [float64],                      "template": tpl_implem_emu_avx["set-64f"],                                },
        { "datatypes": [float32],                      "template": tpl_implem_emu_avx["set-32f"],                                },
        { "datatypes": [int32, uint32],                "template": tpl_implem_emu_avx["set-32"],                                 },
        { "datatypes": [int64, uint64],                "template": tpl_implem_emu_avx["set-64"],                                 },
        { "datatypes": [int16, uint16],                "template": tpl_implem_emu_avx["set-16"],                                 },
        { "datatypes": [int8, uint8],                  "template": tpl_implem_emu_avx["set-8"],                                  } ], # set
    "set_k" : [
        { "datatypes": [int8, uint8],                  "template": tpl_implem_emu_avx["set_k-8"],                                },
        { "datatypes": [int16, uint16],                "template": tpl_implem_emu_avx["set_k-16"],                               },
        { "datatypes": [int32, uint32],                "template": tpl_implem_emu_avx["set_k-32"],                               },
        { "datatypes": [int64, uint64],                "template": tpl_implem_emu_avx["set_k-64"],                               },
        { "datatypes": [float64],                      "template": tpl_implem_emu_avx["set_k-64f"],                              },
        { "datatypes": [float32],                      "template": tpl_implem_emu_avx["set_k-32f"],                              } ], # set_k
    "set1_k":[
        { "datatypes": [int8, uint8],                  "template": tpl_implem_emu_avx["set1_k-8"],                               },
        { "datatypes": [int16, uint16],                "template": tpl_implem_emu_avx["set1_k-16"],                              },
        { "datatypes": [int32, uint32, float32],       "template": tpl_implem_emu_avx["set1_k-32"],                              },
        { "datatypes": [int64, uint64, float64],       "template": tpl_implem_emu_avx["set1_k-64"],                              } ], # set1_k
    "blend": [
        { "datatypes": [int64, int32, uint64, uint32], "template": tpl_implem_emu_avx["blend-1"],                                },
        { "datatypes": [int16, int8, uint16, uint8],   "template": tpl_implem_emu_avx["blend-2"],                                } ], # blend
    "fmadd": [
       { "datatypes": all_float,                      "template": tpl_implem_emu_avx["fmadd"],                                  } ], # fmadd
    "fnmadd": [
		{ "datatypes": all_float,                      "template": tpl_implem_emu_avx["fnmadd"],                                  } ], # fnmadd (same as fmadd but with negation of the result, which can be done by blending with zero)
    "fmsub": [
        { "datatypes": all_float,                      "template": tpl_implem_emu_avx["fmsub"],                                  } ], # fmsub
    "fnmsub": [
		{ "datatypes": all_float,                      "template": tpl_implem_emu_avx["fnmsub"],                                  } ], # fnmsub (same as fms
    "msb": [
        { "datatypes": [float64, int64, uint64],       "template": tpl_implem_emu_avx["msb-64"],                                 },
        { "datatypes": [float32, int32, uint32],       "template": tpl_implem_emu_avx["msb-32"],                                 },
        { "datatypes": [int16, uint16],                "template": tpl_implem_emu_avx["msb-16"],                                 },
        { "datatypes": [int8, uint8],                  "template": tpl_implem_emu_avx["msb-8"],                                  } ], # msb
    "notb": [
        { "datatypes": [float64, int64, uint64],       "template": tpl_implem_emu_avx["notb-64"],                                },
        { "datatypes": [float32, int32, uint32],       "template": tpl_implem_emu_avx["notb-32"],                                },
        { "datatypes": [int16, uint16],                "template": tpl_implem_emu_avx["notb-16"],                                },
        { "datatypes": [int8, uint8],                  "template": tpl_implem_emu_avx["notb-8"],                                 } ], # notb
    "notb_k": [
        { "datatypes": [float64, int64, uint64],       "template": tpl_implem_emu_avx["notb_k-64"],                              },
        { "datatypes": [float32, int32, uint32],       "template": tpl_implem_emu_avx["notb_k-32"],                              },
        { "datatypes": [int16, uint16],                "template": tpl_implem_emu_avx["notb_k-16"],                              },
        { "datatypes": [int8, uint8],                  "template": tpl_implem_emu_avx["notb_k-8"],                               } ], # notb_k
    "cmpeq": [
        { "datatypes": [int64, int32, uint64, uint32], "template": tpl_implem_emu_avx["cmpeq-1"],                                },
        { "datatypes": [uint16, uint8],                "template": tpl_implem_emu_avx["cmpeq-2"],                                } ], # cmpeq
    "cmpneq": [
        { "datatypes": all_datatypes,                  "template": tpl_implem_emu_avx["cmpneq"],                                 } ], # cmpneq
    "testz_2": [
        { "datatypes": all_datatypes,                  "template": tpl_implem_emu_avx["testz_2"],                                } ], # testz_2
    "get": [
        { "datatypes": all_datatypes,                  "template": tpl_implem_emu_avx["get"],                                    } ], # get
    "get_k": [
        { "datatypes": all_datatypes,                  "template": tpl_implem_emu_avx["get_k"],                                  } ], # get_k
    "getfirst": [
        { "datatypes": all_datatypes,                  "template": tpl_implem_emu_avx["getfirst"],                               } ], # getfirst
    "maskz_add": [
        { "datatypes": all_float,                      "template": tpl_implem_emu_avx["maskz_add"],                              },
        { "datatypes": [int64, int32],                 "template": tpl_implem_emu_avx["maskz_add"],    "if": "defined(__AVX2__)" },
        { "datatypes": [int16, int8, uint16, uint8],   "template": tpl_implem_emu_avx["maskz_add"],    "if": "defined(__AVX2__)" },
        { "datatypes": [uint64, uint32],               "template": tpl_implem_emu_avx["maskz_add"],    "if": "defined(__AVX2__)" } ], # maskz_add
    "hadd_to_scal": [
        { "datatypes": all_float,                      "template": tpl_implem_emu_avx["hadd_to_scal"],                           },
        { "datatypes": [int64, int32],                 "template": tpl_implem_emu_avx["hadd_to_scal"], "if": "defined(__AVX2__)" },
        { "datatypes": [int16, int8, uint16, uint8],   "template": tpl_implem_emu_avx["hadd_to_scal"], "if": "defined(__AVX2__)" },
        { "datatypes": [uint64, uint32],               "template": tpl_implem_emu_avx["hadd_to_scal"], "if": "defined(__AVX2__)" } ], # hadd_to_scal
        
	# "pow2": [
	# 	{ "datatypes": [float32],                      "template": tpl_implem_emu_avx["pow2_f32"],                                },
	# 	{ "datatypes": [float64],                      "template": tpl_implem_emu_avx["pow2_f64"],                                } ], # pow2
	
	"exp": [
		{ "datatypes": [float32],                      "template": tpl_implem_emu_avx["exp_f32_fma"], "if": "defined(__AVX2__)" },],
		# { "datatypes": [float32],                      "template": tpl_implem_emu_avx["exp_f32_fma"],   "if": "defined(__FMA__)"} ], # exp
    "log": [
		{ "datatypes": [float32],                      "template": tpl_implem_emu_avx["log_f32_fma"],  "if": "defined(__AVX2__)" },],
	# 	{ "datatypes": [float64],                      "template": tpl_implem_emu_avx["log_f64"],								} ], # log
}
