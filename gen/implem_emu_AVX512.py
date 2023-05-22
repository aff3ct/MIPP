from tools import *

tpl_implem_emu512 = {
	
	"set0-f64" : { "format": "long", "code":
""" return %set1<c:float|b:tp,tp>%(0.0); """
	},
	"set0-f32" : { "format": "long", "code":
""" return %set1<c:float|b:tp,tp>%(0.f); """
	},
	"set0-32" : { "format": "long", "code":
""" return %set1<c:float|b:tp,tp>%(0); """
	},
	"set0_k"   : { "format": "short", "code": 
""" %r<c:int|b:32>% r32 = %set1<c:int|b:32>%(0);
    %m<c:int|b:32>% m32 = %tomsk<c:int|b:32>%(r32);
    return _mm512_kxor(m32, m32);""" 
    },
	"set-64f"   : { "format": "short", "code": 
"""	return %cast_k<c:float,tp>%(_mm512_set_pd(vals[7], vals[6], vals[5], vals[4], vals[3], vals[2], vals[1], vals[0]));"""
    },
    "set-32f"   : { "format": "short", "code": 
"""	return _mm512_set_ps(vals[15], vals[14], vals[13], vals[12],vals[11], vals[10], vals[ 9], vals[ 8],
	                     vals[ 7], vals[ 6], vals[ 5], vals[ 4],vals[ 3], vals[ 2], vals[ 1], vals[ 0]));"""
    },
    "set-64"   : { "format": "short", "code": 
"""	return %cast_k<c:float,tp>%(_mm512_set_epi64((vals[15], vals[14], vals[13], vals[12],
	                     					  	  vals[11], vals[10], vals[ 9], vals[ 8],
	                     					  	  vals[ 7], vals[ 6], vals[ 5], vals[ 4],
	                     					 	  vals[ 3], vals[ 2], vals[ 1], vals[ 0]));"""
	},
    "set-32"   : { "format": "short", "code": 
""" return %cast_k<c:float,tp>%(_mm512_castsi512_ps(_mm512_set_epi32(vals[15], vals[14], vals[13], vals[12], vals[11], vals[10], vals[ 9], vals[ 8],                                            					 vals[ 7], vals[ 6], vals[ 5], vals[ 4],vals[ 3], vals[ 2], vals[ 1], vals[ 0]));"""
  	}, 
  	"andb_fk"             : { "format": "long",  "code":
""""return (m0.m & m1.m);""" }, 
    "andnb_fk"            : { "format": "long",  "code":
""""return ((~m0.m) & m1.m);""" }, 
    "xorb_k"              : { "format": "long",  "code":
""""return (m0.m ^ m1.m);""" }, 
    "orb_k"              : { "format": "long",  "code":
""""return (m0.m | m1.m);""" }, 
	"msb-64": { "format": "long", "code":
"""	%r<tp>% rm = %cast<c:int|b:tp,tp>%(%set1<c:int|b:tp>%(0x8000000000000000);
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
	"notb_k-8": { "format": "long", "code":
"""	return _mm512_knot(m0.m);"""
	},
	"notb_k-16": { "format": "long", "code":
"""	return _mm512_knot(m0.m);"""
	},
	"notb_k-32": { "format": "long", "code":
"""	return ~(m0, mm);"""
	},
	"notb_k-64": { "format": "long", "code":
"""	return ~(m0, mm);"""
	},
	"testz_2-32-64": {
"""	%r<c:int|b:tp>% r0_32 = %andb<c:int|b:tp>%(r0, rm)
	%r<c:int|b:tp>% r1_32 = %set0<c:int|b:tp>%()
	%r<c:int|b:tp>% msk   = %cmpneq<c:int|b:tp>%(r0_32, r1_32)
	%m<c:int|b:tp>% m32   = %tomsk<c:int|b:tp>%(msk);
	%r<c:int|b:tp>% rz    = %set0<c:int|b:tp>%();
	%m<c:int|b:tp>% mz    = %tomsk<c:int|b:tp>%(rz);
	return _mm512_kortestz(m32, mz);"""
	},
	"testz_2-16-8": {
"""	%r<c:int|b:tp>% r0_32 = %andb<c:int|b:tp>%(r0, rm)
	%r<c:int|b:tp>% r1_32 = %set0<c:int|b:tp>%()
	%r<c:int|b:tp>% msk   = %cmpneq<c:int|b:tp>%(r0_32, r1_32)
	%m<c:int|b:tp>% m32   = %tomsk<c:int|b:tp>%(msk);
	%r<c:int|b:tp>% rz    = %set0<c:int|b:tp>%();
	%m<c:int|b:tp>% mz    = %tomsk<c:int|b:tp>%(rz);
	return %cast<c:int|b:tp,tp>%(msk == 0);"""
	},
    "testz-32-64": { "format": "long", "code":
"""	%r<c:int|b:tp>% r32 = %set0<c:int|b:tp>%()
	%m<c:int|b:32>% m32 = %tomsk<c:int|b:32>%(r32);
	%r<c:int|b:tp>% msk = %cmpneq<c:int|b:tp>%(msk, r32)					
	return %testz<c:int|b:32>%(m32, mz);"""},
}
tpl_implem_emu512 = {
		"set0":[
			{ "datatypes": [float64] , "template": tpl_implem_emu512["set0-f64"] , "if": "defined(__MIC__) || defined(__KNCNI__)"} ,
			{ "datatypes": [float32] , "template": tpl_implem_emu512["set0-f32"] , "if": "defined(__MIC__) || defined(__KNCNI__)"} ,
			{ "datatypes": [int32]   , "template": tpl_implem_emu512["set0-32"]  , "if": "defined(__MIC__) || defined(__KNCNI__)"} , ] ,
			
		"set0_k": [
			{ "datatypes": [int32]   , "template": tpl_implem_emu512["set0_k"]} , ] ,
    	"andb_k": [
        	{ "datatypes": all_float, "template": tpl_implem_emu512["andb_fk"], "if": "defined(__AVX512BW__)" } ],
    	"andnb_k": [
        	{ "datatypes": all_float, "template": tpl_implem_emu512["andnb_fk"], "if": "defined(__AVX512BW__)" } ],
		"xorb_k": [
        	{ "datatypes": all_float, "template": tpl_implem_emu512["xorb_k"], "if": "defined(__AVX512BW__)" } ],
   		"orb_k": [
        	{ "datatypes": all_float, "template": tpl_implem_emu512["orb_k"], "if": "defined(__AVX512BW__)" } ],
		"msb": [
			{ "datatypes": [float64, int64, uint64], "template": tpl_implem_emu512["msb-64"] },
			{ "datatypes": [float32, int32, uint32], "template": tpl_implem_emu512["msb-32"] },
			{ "datatypes": [int16, uint16], "template": tpl_implem_emu512["msb-16"] },
			{ "datatypes": [int8, uint8], "template": tpl_implem_emu512["msb-8"] }, ],
		"notb": [
			{ "datatypes": [float64, int64], "template": tpl_implem_emu512["notb-64"] },
			{ "datatypes": [float32, int32], "template": tpl_implem_emu512["notb-32"] },
			{ "datatypes": [int16], "template": tpl_implem_emu512["notb-16"] },
			{ "datatypes": [int8], "template": tpl_implem_emu512["notb-8"] }, ],
		"notb_k": [
			{ "datatypes": [float64, int64], "template": tpl_implem_emu512["notb_k-64"] },
			{ "datatypes": [float32, int32], "template": tpl_implem_emu512["notb_k-32"] },
			{ "datatypes": [int16], "template": tpl_implem_emu512["notb_k-16"] },
			{ "datatypes": [int8], "template": tpl_implem_emu512["notb_k-8"] }, ],	
		"testz_2": [
			{ "datatypes": [int32, int64], "template": tpl_implem_emu512["testz_2-32-64"], "if": "defined (__AVX512F__) || defined(__MIC__) || defined(__KNCNI__)" },
			{ "datatypes": [int16, int8], "template": tpl_implem_emu512["testz_2-16-8"], "if": "defined (__AVX512BW__)" },],
		"testz_2": [
			{ "datatypes": [int32, int64], "template": tpl_implem_emu512["testz-32-64"], "if": "defined (__AVX512F__) || defined(__MIC__) || defined(__KNCNI__)" },
			{ "datatypes": [int16, int8], "template": tpl_implem_emu512["testz_2-16-8"], "if": "defined (__AVX512BW__)" },],

	}

