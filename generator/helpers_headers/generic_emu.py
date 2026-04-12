
from headers_def import *
from tools import *

tpl_generic_emu = {
    
    
  "div_scalar" : { "format" :"long", "code" :"""
    {{isa_dt_par.to_ptr}} ptr1[%N<tp>%];
    {{isa_dt_par.to_ptr}} ptr2[%N<tp>%];
    %storeu<tp>%(ptr1, r0);
    for(unsigned i = 0; i < %N<tp>%; i++)
        ptr2[i] = ptr1[i] / 2;
    return %loadu<tp>%(ptr2);
   """},
  
  "div2" : { "format" :"long", "code" :"""
            %r<tp>% tmp = %set1<tp>%(2);
            %r<tp>% res = %div<tp>%(r0, tmp);
            return res;
    """},
  "div2_scalar" : { "format" :"long", "code" :"""
            %v<tp>% ptr[%N<tp>%];
            %store<tp>%(ptr, r0);        
            for(unsigned i = 0; i < %N<tp>%; i++)
                ptr[i] /= 2;
            return %load<tp>%(ptr);
    """},
  
    "set1_scalar" : { "format" :"long", "code" :"""
            %v<tp>% ptr[%N<tp>%];
            for(unsigned i = 0; i < %N<tp>%; i++)
                ptr[i] = v0;
            return %load<tp>%(ptr);
    """},
}

implems_generic_emu = {
    
    "set1" : [
        { "instr_name": "set1",  "datatypes" : all_datatypes, "template" : tpl_generic_emu["set1_scalar"]}],
    
    "div" : [
        { "instr_name": "div",  "datatypes" : all_float, "template" : tpl_generic_emu["div_scalar"]}],
    
    "div2" : [
        { "instr_name": "div2",  "datatypes" : all_float, "template" : tpl_generic_emu["div2"]},
        { "instr_name": "div2",  "datatypes" : all_float, "template" : tpl_generic_emu["div2_scalar"]}],
}

#for functions with conditition, we want a way to generate the global not of the condition to be used 
#let's we have function :
#if defined(__SSE2__) && defined(__AVX__)
#void my_func() {
#}
#we want to generate the global condition for the generic function to be
#if !(defined(__SSE2__) && defined(__AVX__))
#void my_func() {
#}

def gen_isdef_neg(funcs, f, dt_key):
    guard = "#if "
    if "implem_status" in funcs[f] and dt_key in funcs[f]["implem_status"] :
        for implem in funcs[f]["implem_status"][dt_key]:
            if "if" in implem and implem["if"]:
                guard = guard + "!(" + implem["if"] + ") && "
    #remove last " && "
    guard = guard[:-4]
    return guard

def add_guard_if_isdef(funcs, f, dt_key, file):
    if is_ifdef(funcs, f, dt_key):
        guard = gen_isdef_neg(funcs, f, dt_key)
        print(guard, file=file)

def add_endif_if_isdef(funcs, f, dt_key, file):
    if is_ifdef(funcs, f, dt_key):
        print("#endif", file=file)
        
        
#to prevent gen_c_missing_functions to generate the missing prototypes
def remove_cond_implem_status(funcs, f, dt_key):
    if "implem_status" in funcs[f] and dt_key in funcs[f]["implem_status"] :
        for implem in funcs[f]["implem_status"][dt_key]:
            if "if" in implem and implem["if"]:
                implem["if"] = ""

#same...
def mark_as_implemented(funcs, f, dt_key):
    done_implem_status = { "if": "", "requirements": {} }
    if "implem_status" in funcs[f] and dt_key in funcs[f]["implem_status"] :
        for implem in funcs[f]["implem_status"][dt_key]:
            if "if" in implem and implem["if"]:
                done_implem_status["if"] = implem["if"]
            if "requirements" in implem and implem["requirements"]:
                done_implem_status["requirements"] = implem["requirements"]
    if "implem_status" not in funcs[f]:
        funcs[f]["implem_status"] = {}
    funcs[f]["implem_status"][dt_key] = [done_implem_status]


def gen_c_generic_functions(isa, file, funcs, implems):
    	for f in implems:
            if f in funcs:
                for ff in implems[f]:
                    for dt in ff["datatypes"]:
                        print("// ----------------------------------------------------------------------------------------------------------------------------------------------", f ,file=file)
                        if len(dt.split(',')) <= 1:
                            dt_par = dt.split(',')[0]
                            dt_ret = dt.split(',')[0]
                            if dt_par not in funcs[f]["datatypes"]:
                                print("Panic: unsupported type for '" + f + "<" + dt_par + "," + dt_par + ">' function.")
                                exit(-1)
                        else:
                            dt_par = dt.split(',')[0]
                            dt_ret = dt.split(',')[1]

                            dtk = dt_par + "," + dt_ret
                            if dtk not in funcs[f]["datatypes"]:
                                print("Panic: unsupported type for '" + f + "<" + dt_par + "," + dt_ret + ">' function.")
                                exit(-1)
                        dt_key = dt_par + "," + dt_ret

                        if not is_missing_func(funcs, f, dt_key):
                            print("// Generic '" + f + "<" + dt_key + ">' has been skipped (reason: \"Info: It has been implemented before.\").",file=file)
                       
                        else:
                            #if implementation is guarded by conditions, generic implmentation should be guarded by the negation of these conditions
                            add_guard_if_isdef(funcs, f, dt_key, file)

                            j2_template = Template(ff["template"]["code"], undefined=StrictUndefined)
                            instr_name = ""
                            if "instr_name" in ff:
                                instr_name = ff["instr_name"]
                            pre_rendering = j2_template.render(isa=isa, instr_name=instr_name, dt_par=datatypes[dt_par], dt_ret=datatypes[dt_ret], isa_dt_par=isa["datatypes"][dt_par], isa_dt_ret=isa["datatypes"][dt_ret], cstdint_ret=datatypes[dt_ret]["cstd"])

                            try:
                                ph_ret = parse_placeholders(pre_rendering, isa, funcs, f, dt_par, dt_ret)
                            except Exception as err:
                                err_message = "'" + f + "<" + dt_key + ">' has been skipped (reason: \"{0}\").".format(err)
                                print(" -> " + err_message)
                                print("// " + err_message,file=file)
                                continue
                            
                            post_rendering = ph_ret["converted_ir"]
                            if len(dt.split(',')) <= 1:
                                func_name = build_func_name_short(isa, dt_par, f,True);
                            else:
                                func_name = build_func_name(isa, dt_par, dt_ret, f,True);

                            print("static " + build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, func_name) + " {", file=file)

                            if ff["template"]["format"] == "short":
                                if funcs[f]["proto"]["args"]:
                                # Toreg 
                                    if funcs[f]["proto"]["ret"]["type"] == "reg":
                                        print("\t" + build_type(funcs[f]["proto"]["ret"]["type"], datatypes[dt_ret], isa) + " res;", file=file)
                                        print("\tres.r = ", end='', file=file)

                                    # Tomsk
                                    elif (funcs[f]["proto"]["ret"]["type"] == "msk"):
                                        print("\t" + build_type(funcs[f]["proto"]["ret"]["type"], datatypes[dt_ret], isa) + " res;", file=file);
                                        print("\tres.m = ", end='', file=file)

                                #Other functions
                                else:
                                    if (funcs[f]["proto"]["ret"]["type"] == "reg"):
                                    	print("\t" + build_type(funcs[f]["proto"]["ret"]["type"], datatypes[dt_ret], isa) + " res;", file=file);
                                    	print("\tres.r = ", end='', file=file)

                                    elif (funcs[f]["proto"]["ret"]["type"] == "msk"):
                                    	print("\t" + build_type(funcs[f]["proto"]["ret"]["type"], datatypes[dt_ret], isa) + " res;", file=file);
                                    	print("\tres.m = ", end='', file=file)

                            else:
                                print("\t", end='', file=file)
                            
                            print(post_rendering, file=file)
                            if ff["template"]["format"] == "short":
	                            if funcs[f]["proto"]["ret"]["type"]:
		                            print("\treturn res;", file=file);
                            print("}", file=file)

                            add_endif_if_isdef(funcs, f, dt_key, file)

                            remove_cond_implem_status(funcs, f, dt_key)
                            mark_as_implemented(funcs, f, dt_key)
                
            else:
                print("Panic: '" + f + "' function does not exist.")
                exit(-1)
