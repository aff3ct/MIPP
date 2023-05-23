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
""" %r<c:int|b:tp>% r32 = 0;
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
""" return %cast_k<c:float,tp>%(_mm512_castsi512_ps(_mm512_set_epi32(vals[15], vals[14], vals[13], vals[12], vals[11], vals[10], vals[ 9], vals[ 8],                                            					
																	 vals[ 7], vals[ 6], vals[ 5], vals[ 4],vals[ 3], vals[ 2], vals[ 1], vals[ 0]));"""
  	}, 
  	"set-16"   : { "format": "short", "code": 
""" return %cast_k<c:float,tp>%(_mm512_castsi512_ps(_mm512_set_epi16((%cast<c:int|b:tp,tp>%)vals[31], (%cast<c:int|b:tp,tp>%)vals[30], (%cast<c:int|b:tp,tp>%)vals[29], (%cast<c:int|b:tp,tp>%)vals[28],
		                                            (%cast<c:int|b:tp,tp>%)vals[27], (%cast<c:int|b:tp,tp>%)vals[26], (%cast<c:int|b:tp,tp>%)vals[25], (%cast<c:int|b:tp,tp>%)vals[24],
		                                            (%cast<c:int|b:tp,tp>%)vals[23], (%cast<c:int|b:tp,tp>%)vals[22], (%cast<c:int|b:tp,tp>%)vals[21], (%cast<c:int|b:tp,tp>%)vals[20],
		                                            (%cast<c:int|b:tp,tp>%)vals[19], (%cast<c:int|b:tp,tp>%)vals[18], (%cast<c:int|b:tp,tp>%)vals[17], (%cast<c:int|b:tp,tp>%)vals[16],
		                                            (%cast<c:int|b:tp,tp>%)vals[15], (%cast<c:int|b:tp,tp>%)vals[14], (%cast<c:int|b:tp,tp>%)vals[13], (%cast<c:int|b:tp,tp>%)vals[12],
		                                            (%cast<c:int|b:tp,tp>%)vals[11], (%cast<c:int|b:tp,tp>%)vals[10], (%cast<c:int|b:tp,tp>%)vals[ 9], (%cast<c:int|b:tp,tp>%)vals[ 8],
		                                            (%cast<c:int|b:tp,tp>%)vals[ 7], (%cast<c:int|b:tp,tp>%)vals[ 6], (%cast<c:int|b:tp,tp>%)vals[ 5], (%cast<c:int|b:tp,tp>%)vals[ 4],
		                                            (%cast<c:int|b:tp,tp>%)vals[ 3], (%cast<c:int|b:tp,tp>%)vals[ 2], (%cast<c:int|b:tp,tp>%)vals[ 1], (%cast<c:int|b:tp,tp>%)vals[ 0]));"""
    },
    "set-8"   : { "format": "short", "code": 
""" return %cast_k<c:float,tp>%(_mm512_castsi512_ps(_mm512_set_epi8((%cast<c:int|b:tp,tp>%)vals[63], (%cast<c:int|b:tp,tp>%)vals[62], (%cast<c:int|b:tp,tp>%)vals[61], (%cast<c:int|b:tp,tp>%)vals[60],
		                                           (%cast<c:int|b:tp,tp>%)vals[59], (%cast<c:int|b:tp,tp>%)vals[58], (%cast<c:int|b:tp,tp>%)vals[57], (%cast<c:int|b:tp,tp>%)vals[56],
		                                           (%cast<c:int|b:tp,tp>%)vals[55], (%cast<c:int|b:tp,tp>%)vals[54], (%cast<c:int|b:tp,tp>%)vals[53], (%cast<c:int|b:tp,tp>%)vals[52],
		                                           (%cast<c:int|b:tp,tp>%)vals[51], (%cast<c:int|b:tp,tp>%)vals[50], (%cast<c:int|b:tp,tp>%)vals[49], (%cast<c:int|b:tp,tp>%)vals[48],
		                                           (%cast<c:int|b:tp,tp>%)vals[47], (%cast<c:int|b:tp,tp>%)vals[46], (%cast<c:int|b:tp,tp>%)vals[45], (%cast<c:int|b:tp,tp>%)vals[44],
		                                           (%cast<c:int|b:tp,tp>%)vals[43], (%cast<c:int|b:tp,tp>%)vals[42], (%cast<c:int|b:tp,tp>%)vals[41], (%cast<c:int|b:tp,tp>%)vals[40],
		                                           (%cast<c:int|b:tp,tp>%)vals[39], (%cast<c:int|b:tp,tp>%)vals[38], (%cast<c:int|b:tp,tp>%)vals[37], (%cast<c:int|b:tp,tp>%)vals[36],
		                                           (%cast<c:int|b:tp,tp>%)vals[35], (%cast<c:int|b:tp,tp>%)vals[34], (%cast<c:int|b:tp,tp>%)vals[33], (%cast<c:int|b:tp,tp>%)vals[32],
		                                           (%cast<c:int|b:tp,tp>%)vals[31], (%cast<c:int|b:tp,tp>%)vals[30], (%cast<c:int|b:tp,tp>%)vals[29], (%cast<c:int|b:tp,tp>%)vals[28],
		                                           (%cast<c:int|b:tp,tp>%)vals[27], (%cast<c:int|b:tp,tp>%)vals[26], (%cast<c:int|b:tp,tp>%)vals[25], (%cast<c:int|b:tp,tp>%)vals[24],
		                                           (%cast<c:int|b:tp,tp>%)vals[23], (%cast<c:int|b:tp,tp>%)vals[22], (%cast<c:int|b:tp,tp>%)vals[21], (%cast<c:int|b:tp,tp>%)vals[20],
		                                           (%cast<c:int|b:tp,tp>%)vals[19], (%cast<c:int|b:tp,tp>%)vals[18], (%cast<c:int|b:tp,tp>%)vals[17], (%cast<c:int|b:tp,tp>%)vals[16],
		                                           (%cast<c:int|b:tp,tp>%)vals[15], (%cast<c:int|b:tp,tp>%)vals[14], (%cast<c:int|b:tp,tp>%)vals[13], (%cast<c:int|b:tp,tp>%)vals[12],
		                                           (%cast<c:int|b:tp,tp>%)vals[11], (%cast<c:int|b:tp,tp>%)vals[10], (%cast<c:int|b:tp,tp>%)vals[ 9], (%cast<c:int|b:tp,tp>%)vals[ 8],
		                                           (%cast<c:int|b:tp,tp>%)vals[ 7], (%cast<c:int|b:tp,tp>%)vals[ 6], (%cast<c:int|b:tp,tp>%)vals[ 5], (%cast<c:int|b:tp,tp>%)vals[ 4],
		                                           (%cast<c:int|b:tp,tp>%)vals[ 3], (%cast<c:int|b:tp,tp>%)vals[ 2], (%cast<c:int|b:tp,tp>%)vals[ 1], (%cast<c:int|b:tp,tp>%)vals[ 0]));"""
	},
	"set_k-8": { "format": "long", "code":
"""	%v<tp>% t[%N<tp>%] = {vals[0] ? (%cast<c:int|b:tp,tp>%)0xFFFFFFFFFFFFFFFF : (%cast<c:int|b:tp,tp>%)0,
		                 vals[1] ? (%cast<c:int|b:tp,tp>%)0xFFFFFFFFFFFFFFFF : (%cast<c:int|b:tp,tp>%)0,
		                 vals[2] ? (%cast<c:int|b:tp,tp>%)0xFFFFFFFFFFFFFFFF : (%cast<c:int|b:tp,tp>%)0,
		                 vals[3] ? (%cast<c:int|b:tp,tp>%)0xFFFFFFFFFFFFFFFF : (%cast<c:int|b:tp,tp>%)0,
		                 vals[4] ? (%cast<c:int|b:tp,tp>%)0xFFFFFFFFFFFFFFFF : (%cast<c:int|b:tp,tp>%)0,
		                 vals[5] ? (%cast<c:int|b:tp,tp>%)0xFFFFFFFFFFFFFFFF : (%cast<c:int|b:tp,tp>%)0,
		                 vals[6] ? (%cast<c:int|b:tp,tp>%)0xFFFFFFFFFFFFFFFF : (%cast<c:int|b:tp,tp>%)0,
		                 vals[7] ? (%cast<c:int|b:tp,tp>%)0xFFFFFFFFFFFFFFFF : (%cast<c:int|b:tp,tp>%)0};
    %r<c:int|b:tp>% r0_32 = %set<c:int|b:tp>%((%cast<c:int|b:tp,tp>%)*)t);
    %r<c:int|b:tp>% r1_32 = %set1<c:int|b:tp>%((%cast<c:int|b:tp,tp>%)0xFFFFFFFFFFFFFFFF);
	%r<c:int|b:tp>% msk   = %cmpneq<c:int|b:tp>%(r0_32, r1_32)
    %m<c:int|b:tp>% res   = %tomsk<c:int|b:tp>%(msk);
	return res;""" },
	"set_k-16": { "format": "long", "code":
"""	%v<tp>% t[%N<tp>%] = {vals[ 0] ? 0xFFFFFFFF : 0, vals[ 1] ? 0xFFFFFFFF : 0,
		                  vals[ 2] ? 0xFFFFFFFF : 0, vals[ 3] ? 0xFFFFFFFF : 0,
		                  vals[ 4] ? 0xFFFFFFFF : 0, vals[ 5] ? 0xFFFFFFFF : 0,
		                  vals[ 6] ? 0xFFFFFFFF : 0, vals[ 7] ? 0xFFFFFFFF : 0,
		                  vals[ 8] ? 0xFFFFFFFF : 0, vals[ 9] ? 0xFFFFFFFF : 0,
		                  vals[10] ? 0xFFFFFFFF : 0, vals[11] ? 0xFFFFFFFF : 0,
		                  vals[12] ? 0xFFFFFFFF : 0, vals[13] ? 0xFFFFFFFF : 0,
		                  vals[14] ? 0xFFFFFFFF : 0, vals[15] ? 0xFFFFFFFF : 0};
    %r<c:int|b:tp>% r0_32 = %set<c:int|b:tp>%((%cast<c:int|b:tp,tp>%)*)t);
    %r<c:int|b:tp>% r1_32 = %set1<c:int|b:tp>%(0xFFFFFFFF);
	%r<c:int|b:tp>% msk   = %cmpneq<c:int|b:tp>%(r0_32, r1_32)
    %m<c:int|b:tp>% res   = %tomsk<c:int|b:tp>%(msk);
	return res;""" },
	"set_k-32": { "format": "long", "code":
"""	%v<tp>% t[%N<tp>%] = {vals[ 0] ? (%cast<c:int|b:tp,tp>%)0xFFFF : (%cast<c:int|b:tp,tp>%)0, vals[ 1] ? (%cast<c:int|b:tp,tp>%)0xFFFF : (%cast<c:int|b:tp,tp>%)0,
		                  vals[ 2] ? (%cast<c:int|b:tp,tp>%)0xFFFF : (%cast<c:int|b:tp,tp>%)0, vals[ 3] ? (%cast<c:int|b:tp,tp>%)0xFFFF : (%cast<c:int|b:tp,tp>%)0,
		                  vals[ 4] ? (%cast<c:int|b:tp,tp>%)0xFFFF : (%cast<c:int|b:tp,tp>%)0, vals[ 5] ? (%cast<c:int|b:tp,tp>%)0xFFFF : (%cast<c:int|b:tp,tp>%)0,
		                  vals[ 6] ? (%cast<c:int|b:tp,tp>%)0xFFFF : (%cast<c:int|b:tp,tp>%)0, vals[ 7] ? (%cast<c:int|b:tp,tp>%)0xFFFF : (%cast<c:int|b:tp,tp>%)0,
		                  vals[ 8] ? (%cast<c:int|b:tp,tp>%)0xFFFF : (%cast<c:int|b:tp,tp>%)0, vals[ 9] ? (%cast<c:int|b:tp,tp>%)0xFFFF : (%cast<c:int|b:tp,tp>%)0,
		                  vals[10] ? (%cast<c:int|b:tp,tp>%)0xFFFF : (%cast<c:int|b:tp,tp>%)0, vals[11] ? (%cast<c:int|b:tp,tp>%)0xFFFF : (%cast<c:int|b:tp,tp>%)0,
		                  vals[12] ? (%cast<c:int|b:tp,tp>%)0xFFFF : (%cast<c:int|b:tp,tp>%)0, vals[13] ? (%cast<c:int|b:tp,tp>%)0xFFFF : (%cast<c:int|b:tp,tp>%)0,
		                  vals[14] ? (%cast<c:int|b:tp,tp>%)0xFFFF : (%cast<c:int|b:tp,tp>%)0, vals[15] ? (%cast<c:int|b:tp,tp>%)0xFFFF : (%cast<c:int|b:tp,tp>%)0,
		                  vals[16] ? (%cast<c:int|b:tp,tp>%)0xFFFF : (%cast<c:int|b:tp,tp>%)0, vals[17] ? (%cast<c:int|b:tp,tp>%)0xFFFF : (%cast<c:int|b:tp,tp>%)0,
		                  vals[18] ? (%cast<c:int|b:tp,tp>%)0xFFFF : (%cast<c:int|b:tp,tp>%)0, vals[19] ? (%cast<c:int|b:tp,tp>%)0xFFFF : (%cast<c:int|b:tp,tp>%)0,
		                  vals[20] ? (%cast<c:int|b:tp,tp>%)0xFFFF : (%cast<c:int|b:tp,tp>%)0, vals[21] ? (%cast<c:int|b:tp,tp>%)0xFFFF : (%cast<c:int|b:tp,tp>%)0,
		                  vals[22] ? (%cast<c:int|b:tp,tp>%)0xFFFF : (%cast<c:int|b:tp,tp>%)0, vals[23] ? (%cast<c:int|b:tp,tp>%)0xFFFF : (%cast<c:int|b:tp,tp>%)0,
		                  vals[24] ? (%cast<c:int|b:tp,tp>%)0xFFFF : (%cast<c:int|b:tp,tp>%)0, vals[25] ? (%cast<c:int|b:tp,tp>%)0xFFFF : (%cast<c:int|b:tp,tp>%)0,
		                  vals[26] ? (%cast<c:int|b:tp,tp>%)0xFFFF : (%cast<c:int|b:tp,tp>%)0, vals[27] ? (%cast<c:int|b:tp,tp>%)0xFFFF : (%cast<c:int|b:tp,tp>%)0,
		                  vals[28] ? (%cast<c:int|b:tp,tp>%)0xFFFF : (%cast<c:int|b:tp,tp>%)0, vals[29] ? (%cast<c:int|b:tp,tp>%)0xFFFF : (%cast<c:int|b:tp,tp>%)0,
		                  vals[30] ? (%cast<c:int|b:tp,tp>%)0xFFFF : (%cast<c:int|b:tp,tp>%)0, vals[31] ? (%cast<c:int|b:tp,tp>%)0xFFFF : (%cast<c:int|b:tp,tp>%)0};
    %r<c:int|b:tp>% r0_32 = %set<c:int|b:tp>%((%cast<c:int|b:tp,tp>%)*)t);
    %r<c:int|b:tp>% r1_32 = %set1<c:int|b:tp>%(0xFFFF);
	%r<c:int|b:tp>% msk   = %cmpneq<c:int|b:tp>%(r0_32, r1_32)
    %m<c:int|b:tp>% res   = %tomsk<c:int|b:tp>%(msk);
	return res;""" },
	"set_k-64": { "format": "long", "code":
"""	%v<tp>% t[%N<tp>%] = {vals[ 0] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[ 1] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[ 2] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[ 3] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0,
		                 vals[ 4] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[ 5] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[ 6] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[ 7] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0,
		                 vals[ 8] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[ 9] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[10] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[11] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0,
		                 vals[12] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[13] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[14] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[15] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0,
		                 vals[16] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[17] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[18] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[19] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0,
		                 vals[20] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[21] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[22] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[23] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0,
		                 vals[24] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[25] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[26] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[27] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0,
		                 vals[28] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[29] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[30] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[31] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0,
		                 vals[32] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[33] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[34] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[35] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0,
		                 vals[36] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[37] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[38] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[39] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0,
		                 vals[40] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[41] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[42] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[43] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0,
		                 vals[44] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[45] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[46] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[47] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0,
		                 vals[48] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[49] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[50] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[51] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0,
		                 vals[52] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[53] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[54] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[55] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0,
		                 vals[56] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[57] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[58] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[59] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0,
		                 vals[60] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[61] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[62] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0, vals[63] ? (%cast<c:int|b:tp,tp>%)0xFF : (%cast<c:int|b:tp,tp>%)0};
    %r<c:int|b:tp>% r0_32 = %set<c:int|b:tp>%((%cast<c:int|b:tp,tp>%)*)t);
    %r<c:int|b:tp>% r1_32 = %set1<c:int|b:tp>%(0xFFFF);
	%r<c:int|b:tp>% msk   = %cmpneq<c:int|b:tp>%(r0_32, r1_32)
    %m<c:int|b:tp>% res   = %tomsk<c:int|b:tp>%(msk);
	return res;""" },
		                                           
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
	return %cast<c:int|b:tp,tp>%(m32 == 0);"""
	},
    "testz-32-64": { "format": "long", "code":
"""	%r<c:int|b:tp>% r32 = %set0<c:int|b:tp>%()
	%m<c:int|b:32>% m32 = %tomsk<c:int|b:32>%(r32);
	%r<c:int|b:tp>% rz    = %set0<c:int|b:tp>%();
	%m<c:int|b:tp>% mz    = %tomsk<c:int|b:tp>%(rz);
	%r<c:int|b:tp>% msk = %cmpneq<c:int|b:tp>%(r0, m32)					
	return  _mm512_kortestz(msk, mz);"""},
	
	 "testz-16-8": { "format": "long", "code":
"""	%r<c:int|b:tp>% r32 = %set0<c:int|b:tp>%()
	%m<c:int|b:32>% m32 = %tomsk<c:int|b:32>%(r32);
	%r<c:int|b:tp>% msk = %cmpneq<c:int|b:tp>%(r0, m32)					
	return %cast<c:int|b:tp,tp>%(msk == 0);"""},

}
tpl_implem_emu512 = {
		"set" :[
			{ "datatypes": [float64] , "template": tpl_implem_emu512["set-64f"] , "if": "defined(__AVX512F__)"} ,
			{ "datatypes": [float32] , "template": tpl_implem_emu512["set-32f"] , "if": "defined(__AVX512F__)"} ,
			{ "datatypes": [int32] , "template": tpl_implem_emu512["set-32"] , "if": "defined(__AVX512F__)"} ,
			{ "datatypes": [int64] , "template": tpl_implem_emu512["set-64"] , "if": "defined(__AVX512F__)"} ,
			{ "datatypes": [int16] , "template": tpl_implem_emu512["set-16"] , "if": "defined(__AVX512BW__)"} ,
			{ "datatypes": [int8] , "template": tpl_implem_emu512["set-8"] , "if": "defined(__AVX512BW__)"} ,

		],
		"set_k" : [
			{ "datatypes": [int8] , "template": tpl_implem_emu512["set_k-8"] , "if": "defined(__AVX512F__)"} ,
			{ "datatypes": [int16] , "template": tpl_implem_emu512["set_k-16"] , "if": "defined(__AVX512F__)"} ,
			{ "datatypes": [int32] , "template": tpl_implem_emu512["set_k-32"] , "if": "defined(__AVX512BW__)"} ,

		],
		"set0":[
			{ "datatypes": [float64] , "template": tpl_implem_emu512["set0-f64"] , "if": "defined(__MIC__) || defined(__KNCNI__)"} ,
			{ "datatypes": [float32] , "template": tpl_implem_emu512["set0-f32"] , "if": "defined(__MIC__) || defined(__KNCNI__)"} ,
			{ "datatypes": [int32]   , "template": tpl_implem_emu512["set0-32"]  , "if": "defined(__MIC__) || defined(__KNCNI__)"} , ] ,
			
		"set0_k": [
			{ "datatypes": [all_float, all_int]   , "template": tpl_implem_emu512["set0_k"]} , ] ,
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
		"testz_2args": [
			{ "datatypes": [int32, int64,uint32,uint64], "template": tpl_implem_emu512["testz_2-32-64"], "if": "defined (__AVX512F__) || defined(__MIC__) || defined(__KNCNI__)" },
			{ "datatypes": [int16, int8, uint16,uint8], "template": tpl_implem_emu512["testz_2-16-8"], "if": "defined (__AVX512BW__)" },],
		"testz_1arg": [
			{ "datatypes": [int32, int64,uint32,uint64], "template": tpl_implem_emu512["testz-32-64"], "if": "defined (__AVX512F__) || defined(__MIC__) || defined(__KNCNI__)" },
			{ "datatypes": [int16, int8, uint16,uint8], "template": tpl_implem_emu512["testz-16-8"], "if": "defined (__AVX512BW__)" },],

	}

