from tools import *

tpl_implem_emu = {
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
	"hadd_2": { "format": "long", "code":
"""	return %getfirst<tp>%(%hadd<tp>%(r0));""" },
	"hmul_2": { "format": "long", "code":
"""	return %getfirst<tp>%(%hmul<tp>%(r0));""" },
	"hmin_2": { "format": "long", "code":
"""	return %getfirst<tp>%(%hmin<tp>%(r0));""" },
	"hmax_2": { "format": "long", "code":
"""	return %getfirst<tp>%(%hmax<tp>%(r0));""" },
}

implems_emu = {
	"blend": [
		{ "datatypes": [int64, int32, uint64, uint32], "template": tpl_implem_emu["blend-1"]},
		{ "datatypes": all_datatypes, "template": tpl_implem_emu["blend-2"]}, ],
	"fmadd": [
		{ "datatypes": all_float, "template": tpl_implem_emu["fmadd"] }, ],
	"fmsub": [
		{ "datatypes": all_float, "template": tpl_implem_emu["fmsub"] }, ],
	"msb": [
		{ "datatypes": [float64, int64, uint64], "template": tpl_implem_emu["msb-64"] },
		{ "datatypes": [float32, int32, uint32], "template": tpl_implem_emu["msb-32"] },
		{ "datatypes": [int16, uint16], "template": tpl_implem_emu["msb-16"] },
		{ "datatypes": [int8, uint8], "template": tpl_implem_emu["msb-8"] }, ],
	"notb": [
		{ "datatypes": [float64, int64, uint64], "template": tpl_implem_emu["notb-64"] },
		{ "datatypes": [float32, int32, uint32], "template": tpl_implem_emu["notb-32"] },
		{ "datatypes": [int16, uint16], "template": tpl_implem_emu["notb-16"] },
		{ "datatypes": [int8, uint8], "template": tpl_implem_emu["notb-8"] }, ],
	"notb_k": [
		{ "datatypes": [float64, int64, uint64], "template": tpl_implem_emu["notb_k-64"] },
		{ "datatypes": [float32, int32, uint32], "template": tpl_implem_emu["notb_k-32"] },
		{ "datatypes": [int16, uint16], "template": tpl_implem_emu["notb_k-16"] },
		{ "datatypes": [int8, uint8], "template": tpl_implem_emu["notb_k-8"] }, ],
	"cmpeq": [
		{ "datatypes": [int64, int32, uint64, uint32], "template": tpl_implem_emu["cmpeq-1"] },
		{ "datatypes": [uint16, uint8], "template": tpl_implem_emu["cmpeq-2"] } ],
	"cmpneq": [
		{ "datatypes": all_datatypes, "template": tpl_implem_emu["cmpneq"] } ],
	"testz_2": [
		{ "datatypes": all_datatypes, "template": tpl_implem_emu["testz_2"] }, ],
	"get": [
		{ "datatypes": all_datatypes, "template": tpl_implem_emu["get"] }, ],
	"getfirst": [
		{ "datatypes": all_datatypes, "template": tpl_implem_emu["getfirst"] }, ],
	
}
