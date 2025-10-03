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
    "set_k-64" : { "format": "long", "code":
 """%v<tp>% v[%N<tp>%];
    for (int i = 0; i < %N<tp>%; i++)
        v[i] = vals[i] ? (uint64_t)0xFFFFFFFFFFFFFFFF : (uint64_t)0;
    %r<tp>% r1 = %set<tp>%(v);
    %r<tp>% r2 = %set1<tp>%(0);
    return %cmpeq<tp>%(r1, r2);"""
    },
    "set_k-32" : { "format": "long", "code":
 """%v<tp>% v[%N<tp>%];
    for (int i = 0; i < %N<tp>%; i++)
        v[i] = vals[i] ? 0xFFFFFFFF : 0;
    %r<tp>% r1 = %set<tp>%(v);
    %r<tp>% r2 = %set1<tp>%(0);
    return %cmpeq<tp>%(r1, r2);"""
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
}

# attention certain emu sont commun entre different isa descendre un impl_emu_common.py pour mutualiser
implems_emu_sve = {
    "toreg":[ 
        # verifier genaralisation autres types
        { "datatypes":  [uint64, int64], "template": tpl_implem_emu_sve["toreg-64"]  } ,
        { "datatypes":  [uint32, int32], "template": tpl_implem_emu_sve["toreg-32"]  } ,
    ],
    "andb":[ 
        { "datatypes":  all_float, "template": tpl_implem_emu_sve["and_all_float"]  } ,
    ],
    "set":[ 
        { "datatypes":  all_datatypes, "template": tpl_implem_emu_sve["set_by_load"]  } ,
    ],
    "set_k" :[
        { "datatypes":  [uint64, int64], "template": tpl_implem_emu_sve["set_k-64"]  } ,
        { "datatypes":  [uint32, int32], "template": tpl_implem_emu_sve["set_k-32"]  } ,
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
}
