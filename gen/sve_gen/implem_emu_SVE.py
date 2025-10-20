from tools import *


tpl_implem_emu_sve = {
    "toreg-64" : { "format": "long", "code":
 """%r<tp>% one  = %set1<tp>%(0xFFFFFFFFFFFFFFFF);
    %r<tp>% zero = %set1<tp>%(0);
    return %blend<tp>%(one, zero, m0);"""
    },
    "toreg-32" : { "format": "long", "code":
 """%r<tp>% one  = %set1<tp>%(0xFFFFFFFF);
    %r<tp>% zero = %set1<tp>%(0);
    return %blend<tp>%(one, zero, m0);"""
    },
    "and_all_float" : { "format": "long", "code":
 """%r<c:int>% a = %cast<tp,c:int|b:tp>%(r0);
    %r<c:int>% b = %cast<tp,c:int|b:tp>%(r1);
    %r<c:int>% res = %andb<c:int>%(a,b);
    return %cast<c:int|b:tp,tp>%(res);"""
    },
    "set_by_load" : { "format": "long", "code":
 """return %load<tp>%(vals);"""
    },
    # From enu avx512 multalized common template
    "set_k-64": { "format": "long", "code":
"""%v<c:uint>% t[%N<tp>%] = { {% set nb_item = (isa.size/64)|int -1 %} {% for item in range(nb_item) %}
        t[{{ item }}] = vals[{{ item }}] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0, {% endfor %}
        t[{{ nb_item}}] = vals[{{ nb_item }}] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0 };
    %r<c:uint>% r0_32 = %set<c:uint>%((%v<c:uint>%*) t);
    %r<c:uint>% r1_32 = %set1<c:uint>%((%v<c:uint>%) 0xFFFFFFFFFFFFFFFF);
    return %cast_k<c:uint|b:tp,tp>%(%cmpeq<c:uint|b:tp>%(r0_32, r1_32));"""
    },
    "set_k-32": { "format": "long", "code":
"""%v<c:uint>% t[%N<tp>%] = { {% set nb_item = (isa.size/32)|int - 1 %} {% for item in range(nb_item) %}
        t[{{ item }}] = vals[{{ item }}] ? 0xFFFFFFFF : 0, {% endfor %}
        t[{{ nb_item}}] = vals[{{ nb_item }}] ? 0xFFFFFFFF : 0 };
    %r<c:uint>% r0_32 = %set<c:uint>%((%v<c:uint>%*) t);
    %r<c:uint>% r1_32 = %set1<c:uint>%(0xFFFFFFFF);
    return %cast_k<c:uint|b:tp,tp>%(%cmpeq<c:uint|b:tp>%(r0_32, r1_32));"""        
    },
    "hadd" : { "format": "long", "code":
 """const %v<tp>% val = %hadd_to_scal<tp>%(r0);
    return %set1<tp>%(val);"""
    },
    "get": { "format": "long", "code":
"""%v<tp>% t[%N<tp>%];
    %storeu<tp>%(t, r0);
    return t[v0];""" 
    },
    "getfirst": { "format": "long", "code":
"""  return %get<tp>%(r0, 0);""" 
    },
    "get_k": { "format": "long", "code":
""" %v<tp>% tmp[%N<tp>%];
    %r<tp>% rmsk =%toreg<tp>%(m0);
    %storeu<tp>%(tmp, rmsk);
    return (int32_t) tmp[v0];"""
    },
}

# attention certain emu sont commun entre different isa descendre un impl_emu_common.py pour mutualiser
implems_emu_sve = {
    "toreg":[ 
        # verifier genaralisation autres types
        { "datatypes":  [uint64, int64, float64], "template": tpl_implem_emu_sve["toreg-64"]  } ,
        { "datatypes":  [uint32, int32, float32], "template": tpl_implem_emu_sve["toreg-32"]  } ,
    ],
    "andb":[ 
        { "datatypes":  all_float, "template": tpl_implem_emu_sve["and_all_float"]  } ,
    ],
    "set":[ 
        { "datatypes":  all_datatypes, "template": tpl_implem_emu_sve["set_by_load"]  } ,
    ],
    # tres lourd pour initialiser des predicats
    "set_k" :[
        { "datatypes":  [uint64, int64, float64], "template": tpl_implem_emu_sve["set_k-64"]  } ,
        { "datatypes":  [uint32, int32, float32], "template": tpl_implem_emu_sve["set_k-32"]  } ,
        #{ "datatypes":  [float64, float32]      , "template": tpl_implem_emu_avx["set_k-64f"] } ,
    ],
    "hadd":[ 
        { "datatypes":  all_datatypes, "template": tpl_implem_emu_sve["hadd"]  } ,
    ],
    "get": [
        { "datatypes": all_datatypes, "template": tpl_implem_emu_sve["get"] }, 
    ],
    "getfirst": [
        { "datatypes": all_datatypes, "template": tpl_implem_emu_sve["getfirst"] }, 
    ],
    "get_k": [
        { "datatypes": all_datatypes, "template": tpl_implem_emu_sve["get_k"] }, 
    ],
}
