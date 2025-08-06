from tools import *

""" "tpl_implem_emu" dictionary:
	-Purpose: to provide a collection of emulation functions for missing SIMD instructions and then provide the operands needed to simulate the behavior of that instruction.
	-Use: it is used to implement emulation for specific SIMD instructions that are not directly available in the AVX architecture.
"""
tpl_implem_emu_avx = {
	"set-64f"   : { "format": "short", "code": 
"""	_mm256_set_pd(vals[3], vals[2], vals[1], vals[0]);"""
    },
    "set-32f"   : { "format": "short", "code": 
"""	_mm256_set_ps(vals[7], vals[6], vals[5], vals[4], vals[3], vals[2], vals[1], vals[0]);"""
    },
    "set-64"   : { "format": "short", "code": 
"""	_mm256_set_epi64x(vals[3], vals[2], vals[1], vals[0]);"""
	},
	"set-32"   : { "format": "short", "code": 
"""	_mm256_set_epi32(vals[7], vals[6], vals[5], vals[4],
												 vals[3], vals[2], vals[1], vals[0]);"""
	},
	"set-16"   : { "format": "short", "code": 
"""	_mm256_set_epi16(vals[15], vals[14], vals[13], vals[12],
		                                         vals[11], vals[10], vals[ 9], vals[ 8],
		                                         vals[ 7], vals[ 6], vals[ 5], vals[ 4],
		                                         vals[ 3], vals[ 2], vals[ 1], vals[ 0]);"""
	},
	"set-8"   : { "format": "short", "code": 
""" _mm256_set_epi8((int8_t)vals[31], (int8_t)vals[30], (int8_t)vals[29], (int8_t)vals[28],
		                                           (int8_t)vals[27], (int8_t)vals[26], (int8_t)vals[25], (int8_t)vals[24],
		                                           (int8_t)vals[23], (int8_t)vals[22], (int8_t)vals[21], (int8_t)vals[20],
		                                           (int8_t)vals[19], (int8_t)vals[18], (int8_t)vals[17], (int8_t)vals[16],
		                                           (int8_t)vals[15], (int8_t)vals[14], (int8_t)vals[13], (int8_t)vals[12],
		                                           (int8_t)vals[11], (int8_t)vals[10], (int8_t)vals[ 9], (int8_t)vals[ 8],
		                                           (int8_t)vals[ 7], (int8_t)vals[ 6], (int8_t)vals[ 5], (int8_t)vals[ 4],
		                                           (int8_t)vals[ 3], (int8_t)vals[ 2], (int8_t)vals[ 1], (int8_t)vals[ 0]);"""
	},
	"set_k-64f": { "format": "long", "code":
""" return mipp_avx_cast_k_int64_float64(mipp_avx_set_k_int64(vals));"""
    },
    "set_k-32f": { "format": "long", "code": 
""" return mipp_avx_cast_k_int32_float32(mipp_avx_set_k_int32(vals));"""
	},
	"set_k-64": { "format": "short", "code":
""" _mm256_set_epi64x(vals[3] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0,
		                     vals[2] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0,
		                     vals[1] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0,
		                     vals[0] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0);"""
    },
    "set_k-32": { "format": "short", "code": 
""" _mm256_set_epi32(vals[7] ? 0xFFFFFFFF : 0, vals[6] ? 0xFFFFFFFF : 0,
		                        vals[5] ? 0xFFFFFFFF : 0, vals[4] ? 0xFFFFFFFF : 0,
		                        vals[3] ? 0xFFFFFFFF : 0, vals[2] ? 0xFFFFFFFF : 0,
		                        vals[1] ? 0xFFFFFFFF : 0, vals[0] ? 0xFFFFFFFF : 0);"""
	},
	"set_k-16": { "format": "short", "code":
"""	_mm256_set_epi16(vals[15] ? 0xFFFF : 0, vals[14] ? 0xFFFF : 0,
		                        vals[13] ? 0xFFFF : 0, vals[12] ? 0xFFFF : 0,
		                        vals[11] ? 0xFFFF : 0, vals[10] ? 0xFFFF : 0,
		                        vals[ 9] ? 0xFFFF : 0, vals[ 8] ? 0xFFFF : 0,
		                        vals[ 7] ? 0xFFFF : 0, vals[ 6] ? 0xFFFF : 0,
		                        vals[ 5] ? 0xFFFF : 0, vals[ 4] ? 0xFFFF : 0,
		                        vals[ 3] ? 0xFFFF : 0, vals[ 2] ? 0xFFFF : 0,
		                        vals[ 1] ? 0xFFFF : 0, vals[ 0] ? 0xFFFF : 0);"""
	}, 
    "set_k-8": { "format": "short", "code":	                        
""" _mm256_set_epi8(vals[31] ? 0xFF : 0, vals[30] ? 0xFF : 0, vals[29] ? 0xFF : 0, vals[28] ? 0xFF : 0,
		                       vals[27] ? 0xFF : 0, vals[26] ? 0xFF : 0, vals[25] ? 0xFF : 0, vals[24] ? 0xFF : 0,
		                       vals[23] ? 0xFF : 0, vals[22] ? 0xFF : 0, vals[21] ? 0xFF : 0, vals[20] ? 0xFF : 0,
		                       vals[19] ? 0xFF : 0, vals[18] ? 0xFF : 0, vals[17] ? 0xFF : 0, vals[16] ? 0xFF : 0,
		                       vals[15] ? 0xFF : 0, vals[14] ? 0xFF : 0, vals[13] ? 0xFF : 0, vals[12] ? 0xFF : 0,
		                       vals[11] ? 0xFF : 0, vals[10] ? 0xFF : 0, vals[ 9] ? 0xFF : 0, vals[ 8] ? 0xFF : 0,
		                       vals[ 7] ? 0xFF : 0, vals[ 6] ? 0xFF : 0, vals[ 5] ? 0xFF : 0, vals[ 4] ? 0xFF : 0,
		                       vals[ 3] ? 0xFF : 0, vals[ 2] ? 0xFF : 0, vals[ 1] ? 0xFF : 0, vals[ 0] ? 0xFF : 0);"""                       
	},
	"set1_k-8": { "format": "short", "code":
"""  _mm256_set1_epi8(v0 ? 0xFF : 0); """		
	},
	"set1_k-16": { "format": "short", "code":
"""  _mm256_set1_epi16(v0 ? 0xFFFF : 0); """				
	 },
	"set1_k-32": { "format": "short", "code":
"""  _mm256_set1_epi32(v0 ? 0xFFFFFFFF : 0); """
	 },
	"set1_k-64": { "format": "short", "code":
"""  _mm256_set1_epi64x(v0 ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0); """
	 },
	"blend-1": { "format": "long", "code":
"""	%r<c:float|b:tp>% r0f = %cast<tp,c:float|b:tp>%(r0);
	%r<c:float|b:tp>% r1f = %cast<tp,c:float|b:tp>%(r1);
	%m<c:float|b:tp>% m0f = %cast_k<tp,c:float|b:tp>%(m0);
	%r<c:float|b:tp>% resf = %blend<c:float|b:tp>%(r0f, r1f, m0f);
	return %cast<c:float|b:tp,tp>%(resf); """
	},
	"blend-2": { "format": "long", "code":
"""	%r<c:int|b:tp>% rmi = %cast<tp,c:int|b:tp>%(%toreg<tp>%(m0));
	%r<c:int|b:tp>% r0i = %cast<tp,c:int|b:tp>%(r0);
	%r<c:int|b:tp>% r1i = %cast<tp,c:int|b:tp>%(r1);
	%r<c:int|b:tp>% r_0i = %andb<c:int|b:tp>%(rmi, r0i);
	%r<c:int|b:tp>% r_1i = %andnb<c:int|b:tp>%(rmi, r1i);
	%r<c:int|b:tp>% resi = %xorb<c:int|b:tp>%(r_0i, r_1i);
	%r<tr>% res = %cast<c:int|b:tr,tr>%(resi);
	return res;"""
	},
	"fmadd": { "format": "long", "code":
"""	%r<tp>% rmul = %mul<tp>%(r0, r1);
	%r<tp>% res = %add<tp>%(rmul, r2);
	return res;"""
	},
	"fmsub": { "format": "long", "code":
"""	%r<tp>% rmul = %mul<tp>%(r0, r1);
	%r<tp>% res = %sub<tp>%(rmul, r2);
	return res;"""
	},
	"arith_2args_1msk": { "format": "long", "code":
"""	%r<tp>% res = %{{ instr_name }}<tp>%(r0, r1);
	return %blend<tp>%(res, r2, m0);"""
	},
	"arith_2args_1msk_1reg": { "format": "long", "code":
"""	%r<tp>% rz = %set0<tp>%();
	return %{{ instr_name }}<tp>%(r0, r1, m0, rz);"""
	},
	"msb-64": { "format": "long", "code":
"""	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%(0x8000000000000000));
	return %andb<tp>%(r0, rm);"""
	},
	"msb-32": { "format": "long", "code":
"""	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%(0x80000000));
	return %andb<tp>%(r0, rm);"""
	},
	"msb-16": { "format": "long", "code":
"""	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%(0x8000));
	return %andb<tp>%(r0, rm);"""
	},
	"msb-8": { "format": "long", "code":
"""	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%(0x80));
	return %andb<tp>%(r0, rm);"""
	},
	"notb-64": { "format": "long", "code":
"""	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%(0xFFFFFFFFFFFFFFFF));
	return %andnb<tp>%(r0, rm);"""
	},
	"notb-32": { "format": "long", "code":
"""	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%(0xFFFFFFFF));
	return %andnb<tp>%(r0, rm);"""
	},
	"notb-16": { "format": "long", "code":
"""	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%(0xFFFF));
	return %andnb<tp>%(r0, rm);"""
	},
	"notb-8": { "format": "long", "code":
"""	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%(0xFF));
	return %andnb<tp>%(r0, rm);"""
	},
	"notb_k-64": { "format": "long", "code":
"""	%m<tp>% mm = %cast_k<c:int|b:tp,tp>%(%tomsk<c:int|b:tp>%(%set1<c:int|b:tp>%(0xFFFFFFFFFFFFFFFF)));
	return %andnb_k<tp>%(m0, mm);"""
	},
	"notb_k-32": { "format": "long", "code":
"""	%m<tp>% mm = %cast_k<c:int|b:tp,tp>%(%tomsk<c:int|b:tp>%(%set1<c:int|b:tp>%(0xFFFFFFFF)));
	return %andnb_k<tp>%(m0, mm);"""
	},
	"notb_k-16": { "format": "long", "code":
"""	%m<tp>% mm = %cast_k<c:int|b:tp,tp>%(%tomsk<c:int|b:tp>%(%set1<c:int|b:tp>%(0xFFFF)));
	return %andnb_k<tp>%(m0, mm);"""
	},
	"notb_k-8": { "format": "long", "code":
"""	%m<tp>% mm = %cast_k<c:int|b:tp,tp>%(%tomsk<c:int|b:tp>%(%set1<c:int|b:tp>%(0xFF)));
	return %andnb_k<tp>%(m0, mm);"""
	},
	"cmpeq-1": { "format": "long", "code":
"""	return %cast_k<c:float,tp>%(%cmpeq<c:float>%(%cast<tp,c:float>%(r0), %cast<tp,c:float>%(r1)));"""
	},
	"cmpeq-2": { "format": "long", "code":
"""	return %cast_k<c:int,tp>%(%cmpeq<c:int>%(%cast<tp,c:int>%(r0), %cast<tp,c:int>%(r1)));"""
	},
	"cmpneq": { "format": "long", "code":
"""	return %notb_k<tp>%(%cmpeq<tp>%(r0, r1));"""
	},
	"testz_2": { "format": "long", "code":
"""	%r<c:int|b:32>% r32 = %set1<c:int|b:32>%(-1);
	%m<c:int|b:32>% m32 = %tomsk<c:int|b:32>%(r32);
	return %testz<tp>%(m0, %cast_k<c:int|b:32,tp>%(m32));""" },
	"get": { "format": "long", "code":
"""	%v<tp>% t[%N<tp>%];
	%storeu<tp>%(t, r0);
	return t[v0];""" },
	"getfirst": { "format": "long", "code":
"""	return %get<tp>%(r0, 0);""" },
	"get_k": { "format": "long", "code":
"""	%v<tp>% tmp[%N<tp>%];
	%r<tp>% rmsk =%toreg<tp>%(m0);
	%storeu<tp>%(tmp, rmsk);
	return (int32_t) tmp[v0];""" },
	"hadd_2": { "format": "long", "code":
"""	return %getfirst<tp>%(%hadd<tp>%(r0));""" },
	"hmul_2": { "format": "long", "code":
"""	return %getfirst<tp>%(%hmul<tp>%(r0));""" },
	"hmin_2": { "format": "long", "code":
"""	return %getfirst<tp>%(%hmin<tp>%(r0));""" },
	"hmax_2": { "format": "long", "code":
"""	return %getfirst<tp>%(%hmax<tp>%(r0));""" },
	"maskz_add": { "format": "long", "code":
"""	%r<tp>% radd = %add<tp>%(r0, r1);
    %r<tp>% rmsk =%toreg<tp>%(m0);
	return %andb<tp>%(rmsk, radd);"""
	},
    "gather_seq": { "format": "long", "code":
 """ %v<tp>% t[%N<tp>%];
     %storeu<tp>%(t, vi);
     %v<tp>% data[%N<tp>%];
     for (int i = 0; i < %N<tp>%; i++)
 		data[i] = p0[t[i]];
 	return %loadu<tp>%(data);"""
	},
    "maskz_gather": { "format": "long", "code":
 """ %r<tp>% rgather = %gather<tp>%(p0,vi);
     %r<tp>% rmsk =%toreg<tp>%(m0);
     return %andb<tp>%(rmsk, rgather);"""
	},
}
""" "implems_emu" dictionary:
    -Purpose: This dictionary contains implementation models for various emulated functions.
    -Use: During the generation phase, this dictionary is used to select the appropriate implementation model for a specific emulated function and the datatypes .
    
"""

implems_emu_avx = {
	"set" :[
		{ "datatypes": [float64] , "template": tpl_implem_emu_avx["set-64f"] } ,
		{ "datatypes": [float32] , "template": tpl_implem_emu_avx["set-32f"] } ,
		{ "datatypes": [int32] , "template": tpl_implem_emu_avx["set-32"] } ,
		{ "datatypes": [int64] , "template": tpl_implem_emu_avx["set-64"] } ,
		{ "datatypes": [int16] , "template": tpl_implem_emu_avx["set-16"] ,} ,
		{ "datatypes": [int8] , "template": tpl_implem_emu_avx["set-8"] ,} ,],
	"set_k" : [
		{ "datatypes": [int8] , "template": tpl_implem_emu_avx["set_k-8"] } ,
		{ "datatypes": [int16]  , "template": tpl_implem_emu_avx["set_k-16"] } ,
		{ "datatypes": [int32] , "template": tpl_implem_emu_avx["set_k-32"] ,} ,
		{ "datatypes": [int64] , "template": tpl_implem_emu_avx["set_k-64"] ,} ,
		{ "datatypes": [float64] , "template": tpl_implem_emu_avx["set_k-64f"] } ,
		{ "datatypes": [float32] , "template": tpl_implem_emu_avx["set_k-32f"] } ,],
	"set1_k":[
		{ "datatypes": [int8] , "template": tpl_implem_emu_avx["set1_k-8"] } ,
		{ "datatypes": [int16] , "template": tpl_implem_emu_avx["set1_k-16"] } ,
		{ "datatypes": [int32] , "template": tpl_implem_emu_avx["set1_k-32"]} ,
		{ "datatypes": [int64] , "template": tpl_implem_emu_avx["set1_k-64"] } ,
		#{ "datatypes": [float64] , "template": tpl_implem_emu_avx["set1_k-64f"] } ,
		#{ "datatypes": [float32] , "template": tpl_implem_emu_avx["set1_k-32f"] } ,
		],
	"blend": [
		{ "datatypes": [int64, int32, uint64, uint32], "template": tpl_implem_emu_avx["blend-1"]},
		{ "datatypes": [int16, int8, uint16, uint8], "template": tpl_implem_emu_avx["blend-2"]}, ], # must be other data type
	"fmadd": [
		{ "datatypes": all_float, "template": tpl_implem_emu_avx["fmadd"] }, ],
	"fmsub": [
		{ "datatypes": all_float, "template": tpl_implem_emu_avx["fmsub"] }, ],
	"msb": [
		{ "datatypes": [float64, int64, uint64], "template": tpl_implem_emu_avx["msb-64"] },
		{ "datatypes": [float32, int32, uint32], "template": tpl_implem_emu_avx["msb-32"] },
		{ "datatypes": [int16, uint16], "template": tpl_implem_emu_avx["msb-16"] },
		{ "datatypes": [int8, uint8], "template": tpl_implem_emu_avx["msb-8"] }, ],
	"notb": [
		{ "datatypes": [float64, int64, uint64], "template": tpl_implem_emu_avx["notb-64"] },
		{ "datatypes": [float32, int32, uint32], "template": tpl_implem_emu_avx["notb-32"] },
		{ "datatypes": [int16, uint16], "template": tpl_implem_emu_avx["notb-16"] },
		{ "datatypes": [int8, uint8], "template": tpl_implem_emu_avx["notb-8"] }, ],
	"notb_k": [
		{ "datatypes": [float64, int64, uint64], "template": tpl_implem_emu_avx["notb_k-64"] },
		{ "datatypes": [float32, int32, uint32], "template": tpl_implem_emu_avx["notb_k-32"] },
		{ "datatypes": [int16, uint16], "template": tpl_implem_emu_avx["notb_k-16"] },
		{ "datatypes": [int8, uint8], "template": tpl_implem_emu_avx["notb_k-8"] }, ],
	"cmpeq": [
		{ "datatypes": [int64, int32, uint64, uint32], "template": tpl_implem_emu_avx["cmpeq-1"] },
		{ "datatypes": [uint16, uint8], "template": tpl_implem_emu_avx["cmpeq-2"] } ],
	"cmpneq": [
		{ "datatypes": all_datatypes, "template": tpl_implem_emu_avx["cmpneq"] } ],
	"testz_2": [
		{ "datatypes": all_datatypes, "template": tpl_implem_emu_avx["testz_2"] }, ],
	"get": [
		{ "datatypes": all_datatypes, "template": tpl_implem_emu_avx["get"] }, ],
	"get_k": [
		{ "datatypes": all_datatypes, "template": tpl_implem_emu_avx["get_k"] }, ],
	"getfirst": [
		{ "datatypes": all_datatypes, "template": tpl_implem_emu_avx["getfirst"] }, ],
	"maskz_add": [
        { "datatypes" : all_datatypes, "template" : tpl_implem_emu_avx["maskz_add"] } ],
 #    "gather": [
 #        { "datatypes" : all_datatypes, "template" : tpl_implem_emu_avx["gather_seq"] } ],
 # "mask_gather": [
 #        { "datatypes" : all_datatypes, "template" : tpl_implem_emu_avx["maskz_gather"] } ],
 # "gather_seq": [
 # 	{ "datatypes": all_int_uint, "template": tpl_implem_emu["gather_seq"] }, ],
}
