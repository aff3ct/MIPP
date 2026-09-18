"""
Name and Prototype Builder Module
Constructs standard function names, C++ signatures, templates, and call arguments
for the MIPP generators.
"""
import sys
import os

# Import tools module to avoid circular dependency at load-time
import tools

def build_reg(datatype, isa, lmul=0, isa_name=True, cpp=False):
    if cpp:
        str_reg = "rvd"
        str_reg += "<" + datatype["cstd"]
        if lmul:
            str_reg += "," + str(int(lmul))
        if isa_name:
            str_reg += "," + isa["name"].upper()
        else:
            str_reg += ",DEFAULT_ISA"
        str_reg += ">"
        return str_reg
    else:
        str_reg = "rvd_"
        if isa_name:
            str_reg += isa["name"] + "_"
        str_reg += datatype["category"] + str(datatype["n_bits"])
        if lmul:
            if int(lmul) > 0:
                str_reg += "_m" + str(int(lmul))
            if int(lmul) < 0:
                ldiv = -int(lmul)
                str_reg += "_d" + str(ldiv)
        str_reg += "_t"
        return str_reg

def build_msk(datatype, isa, lmul=0, isa_name=True, cpp=False):
    if cpp:
        str_msk = "rvm"
        str_msk += "<" + datatype["cstd"]
        if lmul:
            str_msk += "," + str(int(lmul))
        if isa_name:
            str_msk += "," + isa["name"].upper()
        else:
            str_msk += ",DEFAULT_ISA"
        str_msk += ">"
        return str_msk
    else:
        str_msk = "rvm_"
        if isa_name:
            str_msk += isa["name"] + "_"
        str_msk += datatype["category"] + str(datatype["n_bits"])
        if lmul:
            if int(lmul) > 0:
                str_msk += "_m" + str(int(lmul))
            if int(lmul) < 0:
                ldiv = -int(lmul)
                str_msk += "_d" + str(ldiv)
        str_msk += "_t"
        return str_msk

# build class Rvd and Rvm
def build_Reg(datatype, isa, lmul=0, isa_name=True, cpp=True):
    if cpp:
        str_reg = "Rvd <T "
        if lmul:
            str_reg += "," + str(int(lmul))
        str_reg += ">"
        return str_reg
    else:
        str_reg = "Rvd_"
        if isa_name:
            str_reg += isa["name"] + "_"
        str_reg += datatype["category"] + str(datatype["n_bits"])
        if lmul:
            str_reg += "_m" + str(int(lmul))
        str_reg += "_t"
        return str_reg

def build_Msk(datatype, isa, lmul=0, isa_name=True, cpp=False):
    if cpp:
        str_msk = "Rvm"
        if isa_name:
            str_msk += "_"+isa["name"]
        str_msk += "<T " 
        if lmul:
            str_msk += "," + str(int(lmul))
        str_msk += ">"
        return str_msk
    else:
        str_msk = "Rvm_"
        if isa_name:
            str_msk += isa["name"] + "_"
        str_msk += datatype["category"] + str(datatype["n_bits"])
        if lmul:
            str_msk += "_m" + str(int(lmul))
        str_msk += "_t"
        return str_msk
        
def build_val(datatype, isa, lmul=0):
    return datatype["category"] + str(datatype["n_bits"]) + "_t"

def build_ptr(datatype, isa, lmul=0):
    return datatype["category"] + str(datatype["n_bits"]) + "_t*"

def build_N(datatype, isa, lmul=0, isa_name=True):
    if isa_name:
        isa_name_upper = isa["name"].upper()+"_"
    else:
        isa_name_upper=""
    
    str_N = "MIPP_"+isa_name_upper+"N_" + datatype["category"].upper() + str(datatype["n_bits"]).upper()
    if lmul:
        str_N += tools.lmul_to_str(lmul).upper()
    return str_N

def build_type(type_str, datatype, isa, lmul=0, isa_name=True, cpp=False):
    if type_str:
        if type_str == "reg":
            return build_reg(datatype, isa, lmul, isa_name, cpp)
        elif type_str == "msk":
            return build_msk(datatype, isa, lmul, isa_name, cpp)
        elif type_str == "val":
            return build_val(datatype, isa)
        elif type_str == "ptr":
            return build_ptr(datatype, isa)
        elif type_str == "Nele":
            return datatype["cstd"]
        elif type_str == "vindex":
            same_size_integer_datatype = tools.find_one_data_types_from({"n_bits": datatype["n_bits"], "category": "int"})
            return build_reg(same_size_integer_datatype, isa, lmul, isa_name, cpp)
        else:
            print("error: type should be reg, msk, val, ptr, Nele or vindex")
            exit(-1)
    else:
        return "void"

# for object layer
def build_class_type(type_str, datatype, isa, lmul=0, isa_name=True, cpp=False):
    if type_str:
        if type_str == "reg":
            return build_Reg(datatype, isa, lmul, isa_name, cpp)
        elif type_str == "msk":
            return build_Msk(datatype, isa, lmul, isa_name, cpp)
        elif type_str == "val":
            return build_val(datatype, isa)
        elif type_str == "ptr":
            return build_ptr(datatype, isa, {}, isa_name)
    else:
        return "void"

def lmul_specialized(proto):
    n_lmul_spe = 0
    for arg in proto["args"]:
        if (arg["type"] == "reg" or arg["type"] == "msk") and not arg["fixeddatatype"]:
            n_lmul_spe = n_lmul_spe + 1
    return n_lmul_spe

def type_specialized(proto):
    n_type_spe = 0
    for arg in proto["args"]:
        if not arg["fixeddatatype"]:
            n_type_spe = n_type_spe + 1
    return n_type_spe

def get_dt_par_size(dt_par):
    if dt_par in tools.datatypes:
        return tools.datatypes[dt_par]["n_bits"]
    else:
        print(f"error: data type {dt_par} not found in datatypes")
        exit(-1)

# Build prototype of set0
def build_proto_set0(dt_ret, isa, func_name, lmul=0, isa_name=True, cpp=False, masked_version=False):
    func_name = func_name.replace("_masks", "").replace("_maskz", "").replace("_mask", "")
    isa_type = "DEFAULT_ISA"
    if isa_name:
        isa_type = isa["name"].upper()
    template = f"<{dt_ret}_t, {lmul}, {isa_type}>"
    if func_name == "set0":
        reg_type = "rvd"
    elif func_name == "set0_k":
        reg_type = "rvm"
    else:
        reg_type = "rvd"

    # masked template form (no template<>)
    if masked_version:
        if masked_version == "mask":
            template = f"<M, {dt_ret}_t, {lmul}, {isa_type}>"
        elif masked_version == "maskz":
            template = f"<Z, {dt_ret}_t, {lmul}, {isa_type}>"
        elif masked_version == "masks":
            template = f"<S, {dt_ret}_t, {lmul}, {isa_type}>"
        else:
            print("error: masked_version should be mask, maskz or masks")
            exit(-1)

        # set0 has no other args, but masked forms still take m0 (and maybe rsrc)
        if masked_version in ("mask", "maskz"):
            return f"inline {reg_type}<{dt_ret}_t, {lmul}, {isa_type}> {func_name}{template}(const rvm<{dt_ret}_t,{lmul}, {isa_type}> m0"
        elif masked_version == "masks":
            return f"inline {reg_type}<{dt_ret}_t, {lmul}, {isa_type}> {func_name}{template}(const rvm<{dt_ret}_t,{lmul}, {isa_type}> m0, const {reg_type}<{dt_ret}_t,{lmul}, {isa_type}> rsrc"

    # unmasked (unchanged)
    return f"template <>\ninline {reg_type}<{dt_ret}_t, {lmul}, {isa_type}> {func_name}{template}("


# Build prototype of set
def build_proto_set(dt_ret, isa, func_name, lmul=0, isa_name=True, cpp=False, masked_version=False):
    func_name = func_name.replace("_masks", "").replace("_maskz", "").replace("_mask", "")
    isa_type = "DEFAULT_ISA"
    if isa_name:
        isa_type = isa["name"].upper()
    dt_par = None
    template = f"<{dt_ret}_t, {lmul}, {isa_type}>"
    if func_name == "set":
        dt_par = f"{dt_ret}_t"
        reg_type = "rvd"
    elif func_name == "set_k":
        dt_par = "int32_t"
        reg_type = "rvm"
    else:
        # keep fallback sane
        dt_par = f"{dt_ret}_t"
        reg_type = "rvd"

    if masked_version:
        if masked_version == "mask":
            template = f"<M, {dt_ret}_t, {lmul}, {isa_type}>"
        elif masked_version == "maskz":
            template = f"<Z, {dt_ret}_t, {lmul}, {isa_type}>"
        elif masked_version == "masks":
            template = f"<S, {dt_ret}_t, {lmul}, {isa_type}>"
        else:
            print("error: masked_version should be mask, maskz or masks")
            exit(-1)


        if masked_version in ("mask", "maskz"):
            return (
                f"inline {reg_type}<{dt_ret}_t, {lmul}, {isa_type}> {func_name}{template}("
                f"const rvm<{dt_par},{lmul}, {isa_type}> m0, "
                f"const {dt_par} vals[N<{dt_ret}_t, {lmul}, {isa_type}>()]"
            )
        elif masked_version == "masks":
            return (
                f"inline {reg_type}<{dt_ret}_t, {lmul}, {isa_type}> {func_name}{template}("
                f"const rvm<{dt_par},{lmul}, {isa_type}> m0, "
                f"const rvd<{dt_par},{lmul}, {isa_type}> rsrc, "
                f"const {dt_par} vals[N<{dt_ret}_t, {lmul}, {isa_type}>()]"
            )

    # unmasked (unchanged)
    return f"template <>\ninline {reg_type}<{dt_ret}_t, {lmul}, {isa_type}> {func_name}{template}(const {dt_par} vals[N<{dt_ret}_t, {lmul}, {isa_type}>()]"


def build_proto_set1(dt_ret, isa, func_name, lmul=0, isa_name=True, cpp=False, masked_version=False):
    func_name = func_name.replace("_masks", "").replace("_maskz", "").replace("_mask", "")
    isa_type = "DEFAULT_ISA"
    if isa_name:
        isa_type = isa["name"].upper()
    template = f"<{dt_ret}_t, {lmul}, {isa_type}>"
    if func_name == "set1":
        dt_par = f"{dt_ret}_t"
        reg_type = "rvd"
    elif func_name == "set1_k":
        dt_par = "int32_t"
        reg_type = "rvm"
    else:
        dt_par = f"{dt_ret}_t"
        reg_type = "rvd"

    if masked_version:
        if masked_version == "mask":
            template = f"<M, {dt_ret}_t, {lmul}, {isa_type}>"
        elif masked_version == "maskz":
            template = f"<Z, {dt_ret}_t, {lmul}, {isa_type}>"
        elif masked_version == "masks":
            template = f"<S, {dt_ret}_t, {lmul}, {isa_type}>"
        else:
            print("error: masked_version should be mask, maskz or masks")
            exit(-1)

        if masked_version in ("mask", "maskz"):
            return (
                f"inline {reg_type}<{dt_ret}_t, {lmul}, {isa_type}> {func_name}{template}("
                f"const rvm<{dt_par},{lmul}, {isa_type}> m0, "
                f"const {dt_par} v0"
            )
        elif masked_version == "masks":
            return (
                f"inline {reg_type}<{dt_ret}_t, {lmul}, {isa_type}> {func_name}{template}("
                f"const rvm<{dt_par},{lmul}, {isa_type}> m0, "
                f"const rvd<{dt_par},{lmul}, {isa_type}> rsrc, "
                f"const {dt_par} v0"
            )

    # unmasked (unchanged)
    return f"template <>\ninline {reg_type}<{dt_ret}_t, {lmul}, {isa_type}> {func_name}{template}(const {dt_par} v0"

def build_proto_load(dt_ret, isa, func_name, lmul=0, isa_name=True, cpp=False, masked_version=False):
    func_name = func_name.replace("_masks", "").replace("_maskz", "").replace("_mask", "")
    isa_type = "DEFAULT_ISA"
    if isa_name:
        isa_type = isa["name"].upper()
    if func_name == "load" or func_name == "loadu":
        dt_par = f"{dt_ret}_t"
        template = f"<{dt_ret}_t, {lmul}, {isa_type}>"
        if masked_version:
            if masked_version == "mask" :
                template = f"<M, {dt_ret}_t, {lmul}, {isa_type}>"
            elif masked_version == "maskz" :
                template = f"<Z, {dt_ret}_t, {lmul}, {isa_type}>"
            elif masked_version == "masks" :
                template = f"<S, {dt_ret}_t, {lmul}, {isa_type}>"
            else :
                print("error: masked_version should be mask, maskz or masks")
                exit(-1)
        reg_type = "rvd"
  
    if masked_version:
        if masked_version == "mask" :
            ret = f"inline {reg_type}<{dt_ret}_t, {lmul}, {isa_type}> {func_name}{template}(const rvm<{dt_par},{lmul}, {isa_type}> m0, const {dt_par}* p0"
        elif masked_version == "maskz" :
            ret = f"inline {reg_type}<{dt_ret}_t, {lmul}, {isa_type}> {func_name}{template}(const rvm<{dt_par},{lmul}, {isa_type}> m0, const {dt_par}* p0"
        elif masked_version == "masks" :
            ret = f"inline {reg_type}<{dt_ret}_t, {lmul}, {isa_type}> {func_name}{template}(const rvm<{dt_par},{lmul}, {isa_type}> m0, const rvd<{dt_par},{lmul}, {isa_type}> rsrc, const {dt_par}* p0"
        else : 
            print("error: masked_version should be mask, maskz or masks")
            exit(-1)
    else :
        ret = f"template <>\ninline {reg_type}<{dt_ret}_t, {lmul}, {isa_type}> {func_name}{template}(const {dt_par}* p0"
    return  ret

def build_proto_gather(dt_par, dt_ret, isa, func_name, lmul=1, isa_name=False, cpp=False, masked_version=False):
    func_name = func_name.replace("_masks", "").replace("_maskz", "").replace("_mask", "")
    isa_type = "DEFAULT_ISA"
    msk_dt = tools.datatypes["uint" + str(get_dt_par_size(dt_par))]["name"]+ "_t"
    if isa_name:
        isa_type = isa["name"].upper()
    template = f"<{dt_ret}_t, {dt_par}_t, {lmul}, {isa_type}>"
    if masked_version:
        if masked_version == "mask" :
            template = f"<M, {dt_ret}_t, {msk_dt}, {lmul}, {isa_type}>"
        elif masked_version == "maskz" :
            template = f"<Z, {dt_ret}_t, {msk_dt}, {lmul}, {isa_type}>"
        elif masked_version == "masks" :
            template = f"<S, {dt_ret}_t, {msk_dt}, {lmul}, {isa_type}>"
        else :
            print("error: masked_version should be mask, maskz or masks")
            exit(-1)
    reg_type = "rvd"
    if masked_version:
        if masked_version == "mask" :
            return f"inline {reg_type}<{dt_ret}_t, {lmul}, {isa_type}> {func_name}{template}(const rvm<{msk_dt},{lmul}, {isa_type}> m0, const {dt_par}_t* p0, const rvd<{msk_dt},{lmul}, {isa_type}> r0"
        elif masked_version == "maskz" :
            return f"inline {reg_type}<{dt_ret}_t, {lmul}, {isa_type}> {func_name}{template}(const rvm<{msk_dt},{lmul}, {isa_type}> m0, const {dt_par}_t* p0, const rvd<{msk_dt},{lmul}, {isa_type}> r0"
        elif masked_version == "masks" :
            return f"inline {reg_type}<{dt_ret}_t, {lmul}, {isa_type}> {func_name}{template}(const rvm<{msk_dt},{lmul}, {isa_type}> m0, const rvd<{dt_par}_t,{lmul}, {isa_type}> rsrc, const {dt_par}_t* p0, const rvd<{msk_dt},{lmul}, {isa_type}> r0"
        else : 
            print("error: masked_version should be mask, maskz or masks")
            exit(-1)
    else :
        print("error: Unmasked gather proto should be built by build_proto.")
        exit(-1)

def build_proto_scatter(dt_par, dt_ret, isa, func_name, lmul=1, isa_name=False, cpp=False, masked_version=False):
    func_name = func_name.replace("_masks", "").replace("_maskz", "").replace("_mask", "")
    isa_type = "DEFAULT_ISA"
    msk_dt = tools.datatypes["uint" + str(get_dt_par_size(dt_par))]["name"]+ "_t"
    if isa_name:
        isa_type = isa["name"].upper()
    template = f"<{dt_ret}_t, {msk_dt}, {lmul}, {isa_type}>"
    if masked_version:
        if masked_version == "mask" :
            template = f"<M, {dt_ret}_t, {msk_dt}, {lmul}, {isa_type}>"
        elif masked_version == "maskz" :
            template = f"<Z, {dt_ret}_t, {msk_dt}, {lmul}, {isa_type}>"
        elif masked_version == "masks" :
            template = f"<S, {dt_ret}_t, {msk_dt}, {lmul}, {isa_type}>"
        else :
            print("error: masked_version should be mask, maskz or masks")
            exit(-1)
    reg_type = "rvd"
    if masked_version:
        if masked_version == "mask" :
            return f"inline void {func_name}{template}(const rvm<{msk_dt},{lmul}, {isa_type}> m0, {dt_par}_t* p0, const rvd<{msk_dt},{lmul}, {isa_type}> r0, const rvd<{dt_ret}_t,{lmul}, {isa_type}> r1"
        elif masked_version == "maskz" :
            return f"inline void {func_name}{template}(const rvm<{msk_dt},{lmul}, {isa_type}> m0, {dt_par}_t* p0, const rvd<{msk_dt},{lmul}, {isa_type}> r0, const rvd<{dt_ret}_t,{lmul}, {isa_type}> r1"
        elif masked_version == "masks" :
            return f"inline void {func_name}{template}(const rvm<{msk_dt},{lmul}, {isa_type}> m0, const rvd<{msk_dt},{lmul}, {isa_type}> rsrc, const {dt_par}_t* p0, const rvd<{msk_dt},{lmul}, {isa_type}> r0, const rvd<{dt_ret}_t,{lmul}, {isa_type}> r1"
        else : 
            print("error: masked_version should be mask, maskz or masks")
            exit(-1)
    else :
        print("error: Unmasked scatter proto should be built by build_proto.")
        exit(-1)

#function message error set functions
def gen_set_func_error(func_name, file):
    if func_name == "set":
        print(f"template <typename T, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA> inline rvd<T, LMUL, ISA_TYPE> {func_name}(const T[N<T, LMUL, ISA_TYPE>()]);", file=file)
    if func_name == "set1":
        print(f"template <typename T, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA> inline rvd<T, LMUL, ISA_TYPE> {func_name}(const T);", file=file)
    if func_name == "set0":
        print(f"template <typename T, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA> inline rvd<T, LMUL, ISA_TYPE> {func_name}();", file=file)
    if func_name == "set_k":
        print(f"template <typename T, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA> inline rvm<T, LMUL, ISA_TYPE> {func_name}(const int32_t[N<T, LMUL, ISA_TYPE>()]);", file=file)
    if func_name == "set0_k":
        print(f"template <typename T, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA> inline rvm<T, LMUL, ISA_TYPE> {func_name}();", file=file)
    if func_name == "set1_k":
        print(f"template <typename T, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA> inline rvm<T, LMUL, ISA_TYPE> {func_name}(const int32_t v0);", file=file)
    if func_name == "load" or func_name == "loadu":
        print(f"template <typename T, int LMUL=1, ISA ISA_TYPE=DEFAULT_ISA> inline rvd<T, LMUL, ISA_TYPE> {func_name}(const T* p0);", file=file)

def build_proto(proto, dt_par, dt_ret, isa, func_name, lmul=0, isa_name=True, cpp=False, masked_version=False):
    #build proto for set functions
    if func_name == "set0" or func_name =="set0_k":
        return  build_proto_set0(dt_ret, isa, func_name, lmul=lmul, isa_name=isa_name, cpp=cpp, masked_version=masked_version) +')'
    if func_name == "set" or func_name =="set_k":
        return  build_proto_set(dt_ret, isa, func_name, lmul=lmul, isa_name=isa_name, cpp=cpp, masked_version=masked_version) +')'
    if func_name =="set1_k" or func_name =="set1":
        return  build_proto_set1(dt_ret, isa, func_name, lmul=lmul, isa_name=isa_name, cpp=cpp, masked_version=masked_version) +')'
    if func_name =="load" or func_name =="loadu":
        return  build_proto_load(dt_ret, isa, func_name, lmul=lmul, isa_name=isa_name, cpp=cpp, masked_version=masked_version) +')'
    if "gather" in func_name and masked_version and cpp:
        return  build_proto_gather(dt_par, dt_ret, isa, func_name, lmul=lmul, isa_name=isa_name, cpp=cpp, masked_version=masked_version) +')'
    if "scatter" in func_name and masked_version and cpp:
        return  build_proto_scatter(dt_par, dt_ret, isa, func_name, lmul=lmul, isa_name=isa_name, cpp=cpp, masked_version=masked_version) +')'

    realdatatype = tools.datatypes[dt_ret]
    if (proto["ret"]["fixeddatatype"]):
        realdatatype = tools.datatypes[proto["ret"]["fixeddatatype"]]
    
    p = "inline " + build_type(proto["ret"]["type"], realdatatype, isa, lmul, isa_name, cpp) + " " + func_name + "("
    cnt_reg = 0
    cnt_msk = 0
    cnt_val = 0
    cnt_ptr = 0
    is_first = True
    
    #add m0 as first argument for masked version of function
    if masked_version:
        msk_dt = tools.datatypes[dt_par]
        if "gather" in func_name or "scatter" in func_name:
            msk_dt = tools.datatypes["uint" + str(get_dt_par_size(dt_par))]

        if masked_version == "mask" or masked_version == "maskz":
            p += "const " + build_msk(msk_dt, isa, lmul, isa_name, cpp) + " m0"
        elif masked_version == "masks" :
            p += "const " + build_msk(msk_dt, isa, lmul, isa_name, cpp) + " m0"
            p += ", const " + build_reg(tools.datatypes[dt_par], isa, lmul, isa_name, cpp) + " rsrc"
        cnt_msk = cnt_msk + 1		
        is_first = False

    for arg in proto["args"]:
        if not is_first:
            p += ", "
        realdatatype = tools.datatypes[dt_par]
        if (arg["fixeddatatype"]):
            if arg["fixeddatatype"] not in tools.datatypes and arg["fixeddatatype"] in tools.all_categories:
                dt_str =  arg["fixeddatatype"] + str(get_dt_par_size(dt_par))
                realdatatype = tools.datatypes[dt_str]
            elif arg["fixeddatatype"] in tools.datatypes:
                realdatatype = tools.datatypes[arg["fixeddatatype"]]
        if arg["charac"] == "RO":
            p += "const "
        p += build_type(arg["type"], realdatatype, isa, lmul, isa_name, cpp)
        if arg["type"] == "reg":
            p += " r" + str(cnt_reg)
            cnt_reg = cnt_reg + 1
        elif arg["type"] == "msk":
            p += " m" + str(cnt_msk)
            cnt_msk = cnt_msk + 1
        elif arg["type"] == "val":
            p += " v" + str(cnt_val)
            cnt_val = cnt_val + 1
        elif arg["type"] == "ptr":
            p += " p" + str(cnt_ptr)
            cnt_ptr = cnt_ptr + 1
        elif arg["type"] == "Nele":
            p += " vals["+build_N(tools.datatypes[dt_par],isa,lmul,isa_name)+"]"
        elif arg["type"] == "vindex":
            p += " vi"
        is_first = False

    return p + ")"

# For layer object
def build_proto_object(proto, dt_par, dt_ret, isa, func_name, lmul=0, isa_name=False, cpp=False):
    realdatatype = tools.datatypes[dt_ret]
    if (proto["ret"]["fixeddatatype"]):
        realdatatype = tools.datatypes[proto["ret"]["fixeddatatype"]]
    p = build_class_type(proto["ret"]["type"], realdatatype, isa, lmul, isa_name, cpp) + " " + func_name + "(" 
    
    cnt_reg = 0
    cnt_msk = 0
    cnt_val = 0
    cnt_ptr = 0
    is_first = True
    for arg in proto["args"]:
        if not is_first:
            p += ","

        realdatatype = tools.datatypes[dt_par]
        if (arg["fixeddatatype"]):
            realdatatype = tools.datatypes[arg["fixeddatatype"]]
        if arg["charac"] == "RO":
            p += " const "

        p += build_class_type(arg["type"], realdatatype, isa, lmul, isa_name, cpp)
        if arg["type"] == "reg":
            p += " r" + str(cnt_reg)
            cnt_reg = cnt_reg + 1
        elif arg["type"] == "msk":
            p += " m" + str(cnt_msk)
            cnt_msk = cnt_msk + 1
        elif arg["type"] == "val":
            p += " v" + str(cnt_val)
            cnt_val = cnt_val + 1
        elif arg["type"] == "ptr":
            p += " p" + str(cnt_ptr)
            cnt_ptr = cnt_ptr + 1
        elif arg["type"] == "vindex":
            p += " vi"
        is_first = False

    return p + ")"

def build_call(proto, dt_par, dt_ret, isa, func_name, lmul=0, isa_name=True, masked_version=False):
    p = ""
    if (proto["ret"]["type"]):
        p += "return "
    p += func_name + "("
    cnt_reg = 0
    cnt_msk = 0
    cnt_val = 0
    cnt_ptr = 0
    is_first = True
 
    if masked_version:
        if masked_version == "mask" or masked_version == "maskz":
            p += "m0"
        elif masked_version == "masks" :
            p += "m0, rsrc"
        cnt_msk = cnt_msk + 1		
        is_first = False
    for arg in proto["args"]:
        if not is_first:
            p += ", "
        if arg["type"] == "reg":
            p += "r" + str(cnt_reg)
            cnt_reg = cnt_reg + 1
        elif arg["type"] == "msk":
            p += "m" + str(cnt_msk)
            cnt_msk = cnt_msk + 1
        elif arg["type"] == "val":
            p += "v" + str(cnt_val)
            cnt_val = cnt_val + 1
        elif arg["type"] == "ptr":
            p += "p" + str(cnt_ptr)
            cnt_ptr = cnt_ptr + 1
        elif arg["type"] == "Nele":
            p += "vals"
        elif arg["type"] == "vindex":
            p += " vi"
        is_first = False
    return p + ")"

# build call function  
def _build_call_lmul(proto, dt_par, dt_ret, isa, func_name, lmul, part, masked_version=False):
    p = ""
    if proto["ret"]["type"] == "reg":
        p += "res.r" + str(int(part)) + " = "
    elif proto["ret"]["type"] == "msk":
        p += "msk.m"  + str(int(part))+ " = "
  
    p += func_name + "("
    cnt_reg = 0
    cnt_msk = 0
    cnt_val = 0
    cnt_ptr = 0
    is_first = True
 
    if masked_version:
        if masked_version == "mask" or masked_version == "maskz":
            p += "m0.m" + str(int(part))
        elif masked_version == "masks" :
            p += "m0.m" + str(int(part)) + ", rsrc.r" + str(int(part))
        cnt_msk = cnt_msk + 1		
        is_first = False

    for arg in proto["args"]:
        if not is_first:
            p += ", "
        if arg["type"] == "reg":
            p += "r" + str(cnt_reg) + ".r" + str(int(part))
            cnt_reg = cnt_reg + 1
        elif arg["type"] == "msk":
            p += "m" + str(cnt_msk) + ".m" + str(int(part))
            cnt_msk = cnt_msk + 1
        elif arg["type"] == "val":
            p += "v" + str(cnt_val)
            cnt_val = cnt_val + 1
        elif arg["type"] == "ptr":
            if "offset_lmul" not in arg or arg["offset_lmul"] == True:
                p += "p" + str(cnt_ptr) + " + " + str(int(part-1)) + "*MIPP_LMUL_STRIDE(sizeof(*p" + str(cnt_ptr) + "), " + str(int(lmul)) +")"
            elif "offset_lmul" in arg and arg["offset_lmul"] == False:
                p += "p" + str(cnt_ptr)
            cnt_ptr = cnt_ptr + 1
        elif arg["type"] == "Nele":
            p += "vals"
        is_first = False
    return p + ")"

def build_call_lmul(proto, dt_par, dt_ret, isa, func_name, lmul=2, isa_name=True, masked_version=False):
    lmul_2 = int(lmul / 2)
    str_code = ""
    realdatatype = tools.datatypes[dt_ret]
    if proto["ret"]["fixeddatatype"]:
        realdatatype = tools.datatypes[proto["ret"]["fixeddatatype"]]
    if proto["ret"]["type"] == "reg":
        str_code += "\t" + build_type(proto["ret"]["type"], realdatatype, isa, lmul, isa_name) + " res;\n"
    elif proto["ret"]["type"] == "msk":
        str_code += "\t" + build_type(proto["ret"]["type"], realdatatype, isa, lmul, isa_name) + " msk;\n"
    
    str_code += "\t" + _build_call_lmul(proto, dt_par, dt_ret, isa, func_name, lmul_2, 1, masked_version=masked_version) + ";\n"
    str_code += "\t" + _build_call_lmul(proto, dt_par, dt_ret, isa, func_name, lmul_2, 2, masked_version=masked_version) + ";"
    if proto["ret"]["type"] == "reg":
        str_code += "\n\t" + "return res;"
    elif proto["ret"]["type"] == "msk":
        str_code += "\n\t" + "return msk;"
    return str_code

# Build other functions build_func_name_short & build_cpp_func_name_short
def build_func_name_short(isa, dt, mipp_name, isa_name=True, lmul=0, masked_version=False):
    param_type = tools.datatypes[dt]["category"] + str(tools.datatypes[dt]["n_bits"])
    lmul_str = ""
    if lmul > 0:
        lmul_str = "_m" + str(int(lmul))
    if lmul < 0 :
        lmul_str = "_d" + str(int(-lmul))

    mask_str = ""
    if masked_version:
        mask_str = "_" + masked_version

    if isa_name:
        return "mipp_" + isa["name"] + "_" + mipp_name + "_" +  param_type + mask_str + lmul_str
    else:
        return "mipp_" + mipp_name + "_" +  param_type + mask_str + lmul_str

def build_cpp_func_name_short(proto, dt_ret, mipp_name, masked_version=False):
    if type_specialized(proto):
        mipp_name = mipp_name.replace("_mz", "")
        mipp_name = mipp_name.replace("_m", "")
        mipp_name = mipp_name.replace("_k", "")
        return mipp_name
    else:
        return mipp_name 

# Build cast's functions build_func_name & build_cpp_func_name
def build_func_name(isa, dt_par, dt_ret, mipp_name, isa_name=True, lmul=0, masked_version=False):
    param_type = tools.datatypes[dt_par]["category"] + str(tools.datatypes[dt_par]["n_bits"])
    return_type = tools.datatypes[dt_ret]["category"] + str(tools.datatypes[dt_ret]["n_bits"])
    lmul_str = ""
    if lmul > 0:
        lmul_str = "_m" + str(int(lmul))
    if lmul < 0 : 
        lmul_str = "_d" + str(int(-lmul))
    mask_str = ""
    if masked_version:
        mask_str = "_" + masked_version

    if isa_name:
        return "mipp_" + isa["name"] + "_" + mipp_name + "_" + param_type + "_" + return_type + mask_str + lmul_str
    else:
        return "mipp_" + mipp_name + "_" + param_type + "_" + return_type + mask_str + lmul_str

def build_cpp_func_name(dt_ret, mipp_name, masked_version=False):
    mipp_name = mipp_name.replace("_mz", "")
    mipp_name = mipp_name.replace("_m", "")
    mipp_name = mipp_name.replace("_k", "")
    return_type = tools.datatypes[dt_ret]["category"] + str(tools.datatypes[dt_ret]["n_bits"])
    return mipp_name + "_" + return_type

def build_func_name_internal(isa, dt, dt_par, dt_ret, f, masked_version=False, lmul=0):
    if len(dt.split(',')) <= 1:
        return build_func_name_short(isa, dt_par, f, True, masked_version=masked_version, lmul=lmul)
    else:
        return build_func_name(isa, dt_par, dt_ret, f, True, masked_version=masked_version, lmul=lmul)
