from tools import *

isa_neon = {
    "name": "neon",
    "prefix": "v",
    "size": 128,
    "define": "defined(__ARM_NEON__) || defined(__ARM_NEON)",
    "architecture": "arm",
    "hw_lmul": False,
    "datatypes": {
        float64: { "data_ext": "f64", "data_ext_logi": "u64", "data_ext_msk": "u64", "reg": "float64x2_t", "msk": "uint64x2_t", "to_ptr": "float64_t", "if": "defined(__aarch64__)" },
        float32: { "data_ext": "f32", "data_ext_logi": "u32", "data_ext_msk": "u32", "reg": "float32x4_t", "msk": "uint32x4_t", "to_ptr": "float32_t"                               },
        int64:   { "data_ext": "s64", "data_ext_logi": "u64", "data_ext_msk": "u64", "reg": "int64x2_t",   "msk": "uint64x2_t", "to_ptr": "int64_t"                                 },
        int32:   { "data_ext": "s32", "data_ext_logi": "u32", "data_ext_msk": "u32", "reg": "int32x4_t",   "msk": "uint32x4_t", "to_ptr": "int32_t"                                 },
        int16:   { "data_ext": "s16", "data_ext_logi": "u16", "data_ext_msk": "u16", "reg": "int16x8_t",   "msk": "uint16x8_t", "to_ptr": "int16_t"                                 },
        int8:    { "data_ext": "s8",  "data_ext_logi": "u8",  "data_ext_msk": "u8",  "reg": "int8x16_t",   "msk": "uint8x16_t", "to_ptr": "int8_t"                                  },
        uint64:  { "data_ext": "u64", "data_ext_logi": "u64", "data_ext_msk": "u64", "reg": "uint64x2_t",  "msk": "uint64x2_t", "to_ptr": "uint64_t"                                },
        uint32:  { "data_ext": "u32", "data_ext_logi": "u32", "data_ext_msk": "u32", "reg": "uint32x4_t",  "msk": "uint32x4_t", "to_ptr": "uint32_t"                                },
        uint16:  { "data_ext": "u16", "data_ext_logi": "u16", "data_ext_msk": "u16", "reg": "uint16x8_t",  "msk": "uint16x8_t", "to_ptr": "uint16_t"                                },
        uint8:   { "data_ext": "u8",  "data_ext_logi": "u8",  "data_ext_msk": "u8",  "reg": "uint8x16_t",  "msk": "uint8x16_t", "to_ptr": "uint8_t"                                 },
    },
}

tpl_implem_neon = {
    "cast":             { "format": "short", "code": "{% if isa_dt_par.data_ext != isa_dt_ret.data_ext -%}{{ isa.prefix }}{{ instr_name }}_{{isa_dt_ret.data_ext}}_{{isa_dt_par.data_ext}}(r0.r);{% else -%} r0.r;{% endif %}" },
    "cast_k":           { "format": "short", "code": "{% if isa_dt_par.data_ext_msk != isa_dt_ret.data_ext_msk -%}{{ isa.prefix }}{{ instr_name }}_{{ isa_dt_ret.data_ext_msk }}_{{ isa_dt_par.data_ext_msk }}(m0.m);{% else -%} m0.m;{% endif %}" },
    "toreg":            { "format": "short", "code": "{% if isa_dt_par.data_ext_msk != isa_dt_ret.data_ext -%}{{ isa.prefix }}{{ instr_name }}_{{ isa_dt_ret.data_ext }}_{{ isa_dt_par.data_ext_msk }}(m0.m);{% else -%} m0.m;{% endif %}" },
    "tomsk":            { "format": "short", "code": "{% if isa_dt_par.data_ext != isa_dt_ret.data_ext_msk -%}{{ isa.prefix }}{{ instr_name }}_{{ isa_dt_ret.data_ext_msk }}_{{ isa_dt_par.data_ext }}(r0.r);{% else -%} r0.r;{% endif %}" },
    "load":             { "format": "short", "code": "{{ isa.prefix }}{{ instr_name }}_{{ isa_dt_par.data_ext }}(p0);" },
    "store":            { "format": "short", "code": "\t{{ isa.prefix }}{{ instr_name }}_{{ isa_dt_par.data_ext }}(p0, r0.r);" },
    "set1":             { "format": "short", "code": "{{ isa.prefix }}{{ instr_name }}_{{ isa_dt_par.data_ext }}(v0);"},
    "arith_1arg":       { "format": "short", "code": "{{ isa.prefix }}{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r);" },
    "arith_2args":      { "format": "short", "code": "{{ isa.prefix }}{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r);" },
    "logi_2args":       { "format": "short", "code": "{{ isa.prefix }}{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r);" },
    "logi_m_2args":     { "format": "short", "code": "{{ isa.prefix }}{{ instr_name }}_{{ isa_dt_par.data_ext_msk }}(m0.m, m1.m);" },
    "logi_m_2args_rev": { "format": "short", "code": "{{ isa.prefix }}{{ instr_name }}_{{ isa_dt_par.data_ext_msk }}(m1.m, m0.m);" },
    "compare":          { "format": "short", "code": "{{ isa.prefix }}{{ instr_name }}_{{ isa_dt_par.data_ext }}(r0.r, r1.r);" },
    "logi_2args_rev":   { "format": "short", "code": "{{ isa.prefix }}{{ instr_name }}_{{ isa_dt_par.data_ext }}(r1.r, r0.r);" },
    "blend":            { "format": "short", "code": "{{ isa.prefix }}{{ instr_name }}_{{ isa_dt_par.data_ext }}(m0.m, r0.r, r1.r);" },
    "round_float":      { "format": "short", "code": "{{ isa.prefix }}rndnq_{{ isa_dt_par.data_ext }}(r0.r);" },
    "round_int":        { "format": "short", "code": "r0.r;" },
    "lshift":           { "format": "short", "code": "{% if isa_dt_par.to_ptr == 'int64_t' or isa_dt_par.to_ptr == 'uint64_t' -%}{{ isa.prefix }}shlq_{{ isa_dt_par.data_ext }}(r0.r, vdupq_n_s64(v0));{% elif isa_dt_par.to_ptr == 'int32_t' or isa_dt_par.to_ptr == 'uint32_t' -%}{{ isa.prefix }}shlq_{{ isa_dt_par.data_ext }}(r0.r, vdupq_n_s32(v0));{% elif isa_dt_par.to_ptr == 'int16_t' or isa_dt_par.to_ptr == 'uint16_t' -%}{{ isa.prefix }}shlq_{{ isa_dt_par.data_ext }}(r0.r, vdupq_n_s16(v0));{% else -%}{{ isa.prefix }}shlq_{{ isa_dt_par.data_ext }}(r0.r, vdupq_n_s8(v0));{% endif %}" },
    "sqrt":             { "format": "short", "code": "{{ isa.prefix }}sqrtq_{{ isa_dt_par.data_ext }}(r0.r);" },
    "rsqrt":            { "format": "short", "code": "{{ isa.prefix }}rsqrteq_{{ isa_dt_par.data_ext }}(r0.r);" },
    "arith_2args_recp": { "format": "long", "code":
"""// long format
	%r<tp>% recp;
	recp.r = {{ isa.prefix }}{{ instr_name }}_{{ isa_dt_par.data_ext }}(r1.r);
	%r<tp>% res = %mul<tp>%(r0, recp);
	return res;""" },
    "logi_2args_fxx": { "format": "long", "code":
"""// long format
	%r<c:uint>% r0i = %cast<tp,c:uint>%(r0);
	%r<c:uint>% r1i = %cast<tp,c:uint>%(r1);
	%r<c:uint>% resi;
	resi.r = {{ isa.prefix }}{{ instr_name }}_{{ isa_dt_par.data_ext_logi }}(r0i.r, r1i.r);
	return %cast<c:uint,tp>%(resi);""" },
    "logi_2args_rev_fxx": { "format": "long", "code":
"""// long format
	%r<c:uint>% r0i = %cast<tp,c:uint>%(r0);
	%r<c:uint>% r1i = %cast<tp,c:uint>%(r1);
	%r<c:uint>% resi;
	resi.r = {{ isa.prefix }}{{ instr_name }}_{{ isa_dt_par.data_ext_logi }}(r1i.r, r0i.r);
	return %cast<c:uint,tp>%(resi);""" },
    "blend_f32-emu": { "format": "long", "code":
"""// long format
	%r<c:uint>% m0i = %cast_k<tp,c:uint>%(m0);
	%r<c:uint>% r0i = %cast<tp,c:uint>%(r0);
	%r<c:uint>% r1i = %cast<tp,c:uint>%(r1);
	%r<c:uint>% resi;
	resi = %blend<c:uint>%(r0i, r1i, m0i);
	return %cast<c:uint,tp>%(resi);""" },
}

implems_neon = {
    "cast": [
        { "instr_name": "reinterpretq", "datatypes": all_datatypes_cart_prod_inc_f64,    "template": tpl_implem_neon["cast"],               "if": "defined(__aarch64__)"  },
        { "instr_name": "reinterpretq", "datatypes": all_datatypes_cart_prod_except_f64, "template": tpl_implem_neon["cast"],                                             } ], # cast
    "cast_k": [
        { "instr_name": "reinterpretq", "datatypes": all_datatypes_cart_prod_inc_f64,    "template": tpl_implem_neon["cast_k"],             "if": "defined(__aarch64__)"  },
        { "instr_name": "reinterpretq", "datatypes": all_datatypes_cart_prod_except_f64, "template": tpl_implem_neon["cast_k"],                                           } ], # cast_k
    "toreg": [
        { "instr_name": "reinterpretq", "datatypes": [float64],                          "template": tpl_implem_neon["toreg"],              "if": "defined(__aarch64__)"  },
        { "instr_name": "reinterpretq", "datatypes": all_int + all_uint + [float32],     "template": tpl_implem_neon["toreg"],                                            } ], # toreg
    "tomsk": [
        { "instr_name": "reinterpretq", "datatypes": [float64],                          "template": tpl_implem_neon["tomsk"],              "if": "defined(__aarch64__)"  },
        { "instr_name": "reinterpretq", "datatypes": all_int + all_uint + [float32],     "template": tpl_implem_neon["tomsk"],                                            } ], # tomsk
    "load": [
        { "instr_name": "ld1q",         "datatypes": all_64bit,                          "template": tpl_implem_neon["load"],               "if": "defined(__aarch64__)"  },
        { "instr_name": "ld1q",         "datatypes": all_32bit + all_16bit + all_8bit,   "template": tpl_implem_neon["load"],                                             } ], # load
    "loadu": [
        { "instr_name": "ld1q",         "datatypes": all_64bit,                          "template": tpl_implem_neon["load"],               "if": "defined(__aarch64__)"  },
        { "instr_name": "ld1q",         "datatypes": all_32bit + all_16bit + all_8bit,   "template": tpl_implem_neon["load"],                                             } ], # loadu
    "store": [
        { "instr_name": "st1q",         "datatypes": all_64bit,                          "template": tpl_implem_neon["store"],              "if": "defined(__aarch64__)"  },
        { "instr_name": "st1q",         "datatypes": all_32bit + all_16bit + all_8bit,   "template": tpl_implem_neon["store"],                                            } ], # store
    "storeu": [
        { "instr_name": "st1q",         "datatypes": all_64bit,                          "template": tpl_implem_neon["store"],              "if": "defined(__aarch64__)"  },
        { "instr_name": "st1q",         "datatypes": all_32bit + all_16bit + all_8bit,   "template": tpl_implem_neon["store"],                                            } ], # storeu
    "set1": [
        { "instr_name": "dupq_n",       "datatypes": all_64bit,                          "template": tpl_implem_neon["set1"],               "if": "defined(__aarch64__)"  },
        { "instr_name": "dupq_n",       "datatypes": all_32bit + all_16bit + all_8bit,   "template": tpl_implem_neon["set1"],                                             } ], # set1
    "add": [
        { "instr_name": "addq",         "datatypes": [float64],                          "template": tpl_implem_neon["arith_2args"],        "if": "defined(__aarch64__)"  },
        { "instr_name": "addq",         "datatypes": all_int + all_uint + [float32],     "template": tpl_implem_neon["arith_2args"],                                      } ], # add
    "sub": [
        { "instr_name": "subq",         "datatypes": [float64],                          "template": tpl_implem_neon["arith_2args"],        "if": "defined(__aarch64__)"  },
        { "instr_name": "subq",         "datatypes": all_int + all_uint + [float32],     "template": tpl_implem_neon["arith_2args"],                                      } ], # sub
    "mul": [
        { "instr_name": "mulq",         "datatypes": [float64],                          "template": tpl_implem_neon["arith_2args"],        "if": "defined(__aarch64__)"  },
        { "instr_name": "mulq",         "datatypes": all_32bit + all_16bit + all_8bit,   "template": tpl_implem_neon["arith_2args"],                                      } ], # mul
    "div": [
        { "instr_name": "divq",         "datatypes": all_float,                          "template": tpl_implem_neon["arith_2args"],        "if": "defined(__aarch64__)"  },
#       { "instr_name": "recpeq",       "datatypes": [uint32],                           "template": tpl_implem_neon["arith_2args_recp"],                                 },
        { "instr_name": "recpeq",       "datatypes": [float32],                          "template": tpl_implem_neon["arith_2args_recp"],   "if": "!defined(__aarch64__)" } ], # div
    "andb": [
        { "instr_name": "andq",         "datatypes": all_uint + all_int,                 "template": tpl_implem_neon["logi_2args"],                                       },
        { "instr_name": "andq",         "datatypes": all_float,                          "template": tpl_implem_neon["logi_2args_fxx"],                                   } ], # andb
    "andb_k": [
        { "instr_name": "andq",         "datatypes": all_datatypes,                      "template": tpl_implem_neon["logi_m_2args"]                                      } ], # andb_k
    "andnb": [
        { "instr_name": "bicq",         "datatypes": all_uint + all_int,                 "template": tpl_implem_neon["logi_2args_rev"],                                   },
        { "instr_name": "bicq",         "datatypes": all_float,                          "template": tpl_implem_neon["logi_2args_rev_fxx"],                               } ], # andnb
    "andnb_k": [
        { "instr_name": "bicq",         "datatypes": all_datatypes,                      "template": tpl_implem_neon["logi_m_2args_rev"]                                  } ], # andnb_k
    "orb": [
        { "instr_name": "orrq",         "datatypes": all_uint + all_int,                 "template": tpl_implem_neon["logi_2args"],                                       },
        { "instr_name": "orrq",         "datatypes": all_float,                          "template": tpl_implem_neon["logi_2args_fxx"],                                   } ], # orb
    "orb_k": [
        { "instr_name": "orrq",         "datatypes": all_datatypes,                      "template": tpl_implem_neon["logi_m_2args"]                                      } ], # orb_k
    "xorb": [
        { "instr_name": "eorq",         "datatypes": all_uint + all_int,                 "template": tpl_implem_neon["logi_2args"],                                       },
        { "instr_name": "eorq",         "datatypes": all_float,                          "template": tpl_implem_neon["logi_2args_fxx"],                                   } ], # xorb
    "xorb_k": [
        { "instr_name": "eorq",         "datatypes": all_datatypes,                      "template": tpl_implem_neon["logi_m_2args"]                                      } ], # xorb_k
    "cmpeq": [
        { "instr_name": "ceqq",         "datatypes": all_64bit,                          "template": tpl_implem_neon["compare"],            "if": "defined(__aarch64__)"  },
        { "instr_name": "ceqq",         "datatypes": all_32bit + all_16bit + all_8bit,   "template": tpl_implem_neon["compare"],                                          } ], # cmpeq
    "cmplt": [
        { "instr_name": "cltq",         "datatypes": all_64bit,                          "template": tpl_implem_neon["compare"],            "if": "defined(__aarch64__)"  },
        { "instr_name": "cltq",         "datatypes": all_32bit + all_16bit + all_8bit,   "template": tpl_implem_neon["compare"],                                          } ], # cmplt
    "cmpgt": [
        { "instr_name": "cgtq",         "datatypes": all_64bit,                          "template": tpl_implem_neon["compare"],            "if": "defined(__aarch64__)"  },
        { "instr_name": "cgtq",         "datatypes": all_32bit + all_16bit + all_8bit,   "template": tpl_implem_neon["compare"],                                          } ], # cmpgt
    "cmple": [
        { "instr_name": "cleq",         "datatypes": all_64bit,                          "template": tpl_implem_neon["compare"],            "if": "defined(__aarch64__)"  },
        { "instr_name": "cleq",         "datatypes": all_32bit + all_16bit + all_8bit,   "template": tpl_implem_neon["compare"],                                          } ], # cmple
    "cmpge": [
        { "instr_name": "cgeq",         "datatypes": all_64bit,                          "template": tpl_implem_neon["compare"],            "if": "defined(__aarch64__)"  },
        { "instr_name": "cgeq",         "datatypes": all_32bit + all_16bit + all_8bit,   "template": tpl_implem_neon["compare"],                                          } ], # cmpge
    "blend": [
        { "instr_name": "bslq",         "datatypes": all_int_uint+ [float32],            "template": tpl_implem_neon["blend"],                                            }, 
        { "instr_name": "bslq",         "datatypes": [float64],                          "template": tpl_implem_neon["blend"],              "if": "defined(__aarch64__)"  },], # blend
    "min": [
        { "instr_name": "minq",         "datatypes": [float64],                          "template": tpl_implem_neon["arith_2args"],        "if": "defined(__aarch64__)"  },
        { "instr_name": "minq",         "datatypes": [float32, int32, int16, int8],      "template": tpl_implem_neon["arith_2args"]                                       },
    	{ "instr_name": "minq",         "datatypes": [uint32, uint16, uint8],            "template": tpl_implem_neon["arith_2args"]                                       } ], # min
    "max": [
        { "instr_name": "maxq",         "datatypes": [float64],                          "template": tpl_implem_neon["arith_2args"],        "if": "defined(__aarch64__)"  },
        { "instr_name": "maxq",         "datatypes": [float32, int32, int16, int8],      "template": tpl_implem_neon["arith_2args"]                                       },
        { "instr_name": "maxq",         "datatypes": [uint32, uint16, uint8],            "template": tpl_implem_neon["arith_2args"]                                       } ], # max
    "lshift": [
        { "instr_name": "",             "datatypes": all_int + all_uint,                 "template": tpl_implem_neon["lshift"]                                            } ], # lshift
    "round": [
        { "instr_name": "",             "datatypes": [float64],                          "template": tpl_implem_neon["round_float"],        "if": "defined(__aarch64__)"  },
        { "instr_name": "",             "datatypes": [float32],                          "template": tpl_implem_neon["round_float"]                                       },
        { "instr_name": "",             "datatypes": all_int + all_uint,                 "template": tpl_implem_neon["round_int"]                                         } ], # round
    "sqrt": [
        { "instr_name": "",             "datatypes": [float64],                          "template": tpl_implem_neon["sqrt"],               "if": "defined(__aarch64__)"  },
        { "instr_name": "",             "datatypes": [float32],                          "template": tpl_implem_neon["sqrt"]                                              } ], # sqrt
    "rsqrt": [
        { "instr_name": "",             "datatypes": [float64],                          "template": tpl_implem_neon["rsqrt"],              "if": "defined(__aarch64__)"  },
        { "instr_name": "",             "datatypes": [float32],                          "template": tpl_implem_neon["rsqrt"]                                             } ], # rsqrt
}
