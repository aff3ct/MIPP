
from headers_def import *
from tools import *
from c_generator import *

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
	
	"fmadd" : { "format" :"long", "code" :"""
			%r<tp>% res = %mul<tp>%(r0, r1);
			res = %add<tp>%(res, r2);
			return res;
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
	
	"fmadd" : [
		{ "instr_name": "fmadd",  "datatypes" : all_float, "template" : tpl_generic_emu["fmadd"]}],
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


# def gen_c_generic_functions(isa, file, funcs, implems):
# 		for f in implems:
# 			if f in funcs:
# 				for ff in implems[f]:
# 					for dt in ff["datatypes"]:
# 						print("// ------------------------------------------------------------------------------------------------------------------", f ,file=file)
# 						if len(dt.split(',')) <= 1:
# 							dt_par = dt.split(',')[0]
# 							dt_ret = dt.split(',')[0]
# 							if dt_par not in funcs[f]["datatypes"]:
# 								print("Panic: unsupported type for '" + f + "<" + dt_par + "," + dt_par + ">' function.")
# 								exit(-1)
# 						else:
# 							dt_par = dt.split(',')[0]
# 							dt_ret = dt.split(',')[1]

# 							dtk = dt_par + "," + dt_ret
# 							if dtk not in funcs[f]["datatypes"]:
# 								print("Panic: unsupported type for '" + f + "<" + dt_par + "," + dt_ret + ">' function.")
# 								exit(-1)
# 						dt_key = dt_par + "," + dt_ret

# 						if not is_missing_func(funcs, f, dt_key):
# 							print("// Generic '" + f + "<" + dt_key + ">' has been skipped (reason: \"Info: It has been implemented before.\").",file=file)
					   
# 						else:
# 							#if implementation is guarded by conditions, generic implmentation should be guarded by the negation of these conditions
# 							add_guard_if_isdef(funcs, f, dt_key, file)

# 							j2_template = Template(ff["template"]["code"], undefined=StrictUndefined)
# 							instr_name = ""
# 							if "instr_name" in ff:
# 								instr_name = ff["instr_name"]
# 							pre_rendering = j2_template.render(isa=isa, instr_name=instr_name, dt_par=datatypes[dt_par], dt_ret=datatypes[dt_ret], isa_dt_par=isa["datatypes"][dt_par], isa_dt_ret=isa["datatypes"][dt_ret], cstdint_ret=datatypes[dt_ret]["cstd"])

# 							try:
# 								ph_ret = parse_placeholders(pre_rendering, isa, funcs, f, dt_par, dt_ret)
# 							except Exception as err:
# 								err_message = "'" + f + "<" + dt_key + ">' has been skipped (reason: \"{0}\").".format(err)
# 								print(" -> " + err_message)
# 								print("// " + err_message,file=file)
# 								continue
							
# 							post_rendering = ph_ret["converted_ir"]
# 							if len(dt.split(',')) <= 1:
# 								func_name = build_func_name_short(isa, dt_par, f,True);
# 							else:
# 								func_name = build_func_name(isa, dt_par, dt_ret, f,True);

# 							print("static " + build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, func_name) + " {", file=file)

# 							if ff["template"]["format"] == "short":
# 								if funcs[f]["proto"]["args"]:
# 									# Toreg 
# 									if funcs[f]["proto"]["ret"]["type"] == "reg":
# 										print("\t" + build_type(funcs[f]["proto"]["ret"]["type"], datatypes[dt_ret], isa) + " res;", file=file)
# 										print("\tres.r = ", end='', file=file)

# 									# Tomsk
# 									elif (funcs[f]["proto"]["ret"]["type"] == "msk"):
# 										print("\t" + build_type(funcs[f]["proto"]["ret"]["type"], datatypes[dt_ret], isa) + " res;", file=file);
# 										print("\tres.m = ", end='', file=file)

# 								#Other functions
# 								else:
# 									if (funcs[f]["proto"]["ret"]["type"] == "reg"):
# 										print("\t" + build_type(funcs[f]["proto"]["ret"]["type"], datatypes[dt_ret], isa) + " res;", file=file);
# 										print("\tres.r = ", end='', file=file)

# 									elif (funcs[f]["proto"]["ret"]["type"] == "msk"):
# 										print("\t" + build_type(funcs[f]["proto"]["ret"]["type"], datatypes[dt_ret], isa) + " res;", file=file);
# 										print("\tres.m = ", end='', file=file)

# 							else:
# 								print("\t", end='', file=file)
							
# 							print(post_rendering, file=file)
# 							if ff["template"]["format"] == "short":
# 								if funcs[f]["proto"]["ret"]["type"]:
# 									print("\treturn res;", file=file);
# 							print("}", file=file)

# 							add_endif_if_isdef(funcs, f, dt_key, file)

# 							remove_cond_implem_status(funcs, f, dt_key)
# 							mark_as_implemented(funcs, f, dt_key)
				
# 			else:
# 				print("Panic: '" + f + "' function does not exist.")
# 				exit(-1)


################################# MASKED FUNCTION ############################################

## We want to emulate a blend with only andb and set0 
SNIPPET_END_MSK = """
	%r<tp>% res = %blend<tp>%(op, r0, m0);
	return res;
"""       

SNIPPET_END_MSKZ = """
	%r<tp>% tmp = %toreg<tp>%(m0);
	%r<tp>% res = %andb<tp>%(op, tmp);
	return res;
"""
	
				
tpl_mask_generic_emu = {
	"ret_reg_2args_reg" : { "format" :"long", "code" :"""
		%r<tp>% op = %{{func_name}}<tp>%(m0, r0, r1);
	"""},
	
	"ret_reg_3args_reg" : { "format" :"long", "code" :"""
		%r<tp>% op = %{{func_name}}<tp>%(m0, r0, r1, r2);
	"""},
	
	"ret_reg_1arg_reg" : { "format" :"long", "code" :"""
		%r<tp>% op = %{{func_name}}<tp>%(m0,r0);
	"""},
	
	"load" : { "format" :"long", "code" :"""
		%r<tp>% op = %load<tp>%(m0,p0);
	"""},
	
	"set" : { "format" :"long", "code" :"""
		%r<tp>% op = %set<tp>%(vals);
	"""},
	
	"set1" : { "format" :"long", "code" :"""
		%r<tp>% op = %set1<tp>%(v0);
	"""},
	
		
	"ret_msk_2args_reg" : { "format" :"long", "code" :"""
		%m<tp>% op = %{{func_name}}<tp>%(r0, r1);
	"""},
	
	#will need a custom thing
	"store" : { "format" :"long", "code" :"""
		exit(-1); //huuuuh idk
	"""},
	

	"reductions" : { "format" :"long", "code" :"""
		exit(-1); //huuuuh idk
	"""},
   
}

implem_mask_generic_emu = {
	"add" : [
		#add SNIPPEt_END_MSK to the template code
		{ "instr_name": "add",  "datatypes" : all_datatypes, "version" : "mask", "template" : { "format" :"long", "code" : tpl_mask_generic_emu["ret_reg_2args_reg"]["code"] + SNIPPET_END_MSK}},
		#{ "instr_name": "add",  "datatypes" : all_datatypes, "template" : tpl_mask_generic_emu["ret_reg_3args_reg"], "version" : "maskz"}
	],
}


#can be added to c_generator at some point.
def add_mask_to_implem_status(funcs, f, dt_key, mask_proto, ph_ret):
	"""
	In implem status[dt_key], adds new keys for mask, maskz, masks. 
	These keys are used to prevent gen_c_generic_masked_functions to generate masked functions when the non-masked version has been implemented. 
	The key can contain requirements or if conditions. (like the non-masked version is implemented only for some types, so the masked version can be implemented
	for these types without being skipped).
	
	For compatibility, the "if" and "requirements" keys are KEPT for the non-masked versions. 
	
	The new structure will be 
	funcs[f]["implem_status"][dt_key] = [
		{
			"if" : "some condition",
			"requirements" : {"some_requirements" : "some values"},
			"mask" : {
				"if" : "some condition for the masked version",
				"requirements" : {"some_requirements for the masked version" : "some values"}
			},
			"maskz" : {
				"if" : "some condition for the maskz version",
				"requirements" : {"some_requirements for the maskz version" : "some values"}
			},
			"masks" : {
				"if" : "some condition for the masks version",
				"requirements" : {"some_requirements for the masks version" : "some values"}
			}
		},
		...
	]
	
	"if" and "requirements" top level 
	are NOT generated and NOT modified by this function.
	
	ph_ret is used to get the requirements for masked version
	"""
	
	if "implem_status" not in funcs[f]:
		funcs[f]["implem_status"] = {}
	if dt_key not in funcs[f]["implem_status"]:
		funcs[f]["implem_status"][dt_key] = []
	mask_implem_status = {"if": "", "requirements": {}}
	maskz_implem_status = {"if": "", "requirements": {}}
	masks_implem_status = {"if": "", "requirements": {}}
	if "mask" in mask_proto:
		mask_implem_status["if"] = mask_proto["mask"]["if"]
		mask_implem_status["requirements"] = ph_ret["mask_requirements"]
		
	if "maskz" in mask_proto:   
		maskz_implem_status["if"] = mask_proto["maskz"]["if"]
		maskz_implem_status["requirements"] = ph_ret["maskz_requirements"]
	if "masks" in mask_proto:
		masks_implem_status["if"] = mask_proto["masks"]["if"]
		masks_implem_status["requirements"] = ph_ret["masks_requirements"]
	new_implem_status = {"if": "", "requirements": {}, "mask": mask_implem_status, "maskz": maskz_implem_status, "masks": masks_implem_status}
	funcs[f]["implem_status"][dt_key].append(new_implem_status)
		
	
	
def is_fully_missing_masked_func(funcs, f, dt_key, mask_type):
	"""
	Checks if the masked version of the function is fully missing. 
	It checks if in implem_status[dt_key], there is a dict with a key "mask" (or "maskz", "masks" depending on mask_type) and if this key has an "if" condition or some requirements. 
	If there is such dict, it means that the masked version is not fully missing, but it is missing under certain conditions. 
	If there is no such dict, it means that the masked version is fully missing.
	"""
	if "implem_status" in funcs[f] and dt_key in funcs[f]["implem_status"] :
		for implem in funcs[f]["implem_status"][dt_key]:
			if mask_type in implem and implem[mask_type]:
				if "if" in implem[mask_type] and implem[mask_type]["if"]:
					return False
				if "requirements" in implem[mask_type] and implem[mask_type]["requirements"]:
					return False
		return True
	else:
		return True


def mask_in_implem_status(funcs, f, dt_key, mask_type):
	"""
	Checks if in implem_status[dt_key], there is a dict with a key "mask" (or "maskz", "masks" depending on mask_type) and if this key has an "if" condition or some requirements. 
	If there is such dict, it means that the masked version is not fully missing, but it is missing under certain conditions. 
	If there is no such dict, it means that the masked version is fully missing.
	"""
	if "implem_status" in funcs[f] and dt_key in funcs[f]["implem_status"] :
		for implem in funcs[f]["implem_status"][dt_key]:
			if mask_type in implem and implem[mask_type]:
				return True
		return False
	else:
		return False
def get_mask_conditions(funcs, f, dt_key, mask_type):
	"""
	Gets the conditions for the masked version of the function. 
	It checks if in implem_status[dt_key], there is a dict with a key "mask" (or "maskz", "masks" depending on mask_type) and if this key has an "if" condition or some requirements. 
	If there is such dict, it returns the conditions for the masked version. 
	If there is no such dict, it returns an empty string.
	"""
	conditions = ""
	if "implem_status" in funcs[f] and dt_key in funcs[f]["implem_status"] :
		for implem in funcs[f]["implem_status"][dt_key]:
			if mask_type in implem and implem[mask_type]:
				if "if" in implem[mask_type] and implem[mask_type]["if"]:
					conditions += "(" + implem[mask_type]["if"] + ")"
				if "requirements" in implem[mask_type] and implem[mask_type]["requirements"]:
					reqs = []
					for req, val in implem[mask_type]["requirements"].items():
						reqs.append(req + "=" + val)
					conditions += "(" + " && ".join(reqs) + ")"
	return conditions
	
def build_ifdef_masked_rec(funcs, func_name, dt_key, mask_type):
	#similar to build_ifdef_rec but for masked version. It looks for conditions in the "mask", "maskz", "masks" keys of implem_status[dt_key]
	#mask_type is "mask", "maskz" or "masks" so the function can be used for all the masked versions.
	str_ifdef = ""
	if "implem_status" in funcs[func_name]:
		if dt_key in funcs[func_name]["implem_status"]:
			is_first_or = True
			str_ifdef_sub = ""
			str_end_sub_token = ""
			if not mask_in_implem_status(funcs, func_name, dt_key, mask_type):
				return ""
			
			for i, implem in enumerate(funcs[func_name]["implem_status"][dt_key]):
				if mask_type in implem and implem[mask_type]:
					if "if" in implem[mask_type] and implem[mask_type]["if"]:
						if not is_first_or:
							str_ifdef_sub += " || "
							str_end_sub_token += " || "
						str_ifdef_sub += "(" + implem[mask_type]["if"] + ")"
						str_end_sub_token += "!(" + implem[mask_type]["if"] + ")"
						is_first_or = False
					if "requirements" in implem[mask_type] and implem[mask_type]["requirements"]:
						reqs = []
						end_sub_reqs = []
						for req, val in implem[mask_type]["requirements"].items():
							reqs.append(req + "=" + val)
							end_sub_reqs.append(req + "!=" + val)
						if not is_first_or:
							str_ifdef_sub += " || "
							str_end_sub_token += " || "
						str_ifdef_sub += "(" + " && ".join(reqs) + ")"
						str_end_sub_token += "(" + " || ".join(end_sub_reqs) + ")"
						is_first_or = False
			if str_ifdef_sub:
				str_ifdef += "(" + str_ifdef_sub + ")"
			if str_end_sub_token:
				if str_ifdef:
					str_ifdef += " && "
				str_ifdef += "(" + str_end_sub_token + ")"
	return str_ifdef

def is_ifdef_missing_masked_func(funcs, f, dt_key, mask_type):
	ifdef = build_ifdef_masked_rec(funcs, func_name, dt_key)
	if ifdef:
		return True
	else:
		return False
	
	
def is_missing_masked_func(funcs, f, dt_key, mask_type):
	"""
	Checks if the masked version of the function is missing. 
	It checks if in implem_status[dt_key], there is a dict with a key "mask" (or "maskz", "masks" depending on mask_type) and if the conditions in this key are satisfied. 
	"""
	return is_fully_missing_masked_func(funcs, f, dt_key, mask_type) or is_ifdef_missing_masked_func(funcs, f, dt_key, mask_type)


def get_func_name(isa, dt_par, dt_ret, f):
	if dt_par == dt_ret:
		return build_func_name_short(isa, dt_par, f,True);
	else:
		return build_func_name(isa, dt_par, dt_ret, f,True);

def gen_c_generic_masked_functions(isa, file, funcs, implems, lmul=0):
	for f in implems:
		if f in funcs:
			print(f)
			
			for ff in implems[f]:
				for dt in ff["datatypes"]:
					print("// --------------------------------------------------------------------------------------", f ,file=file)
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
					
					missing_mask = is_missing_masked_func(funcs, f, dt_key, "mask")
					missing_maskz = is_missing_masked_func(funcs, f, dt_key, "maskz")
					missing_masks = is_missing_masked_func(funcs, f, dt_key, "masks")

					print("missing_mask:", missing_mask, "missing_maskz:", missing_maskz, "missing_masks:", missing_masks)
					
					if not missing_mask :
						print("// Generic masked '" + f + "<" + dt_key + ">' has been skipped (reason: \"Info: It has been implemented before.\").",file=file)
					else:
						j2_template = Template(ff["template"]["code"], undefined=StrictUndefined)
						instr_name = ""
						if "instr_name" in ff:
							instr_name = ff["instr_name"]
						pre_rendering = j2_template.render(func_name = f)

						try:
							ph_ret = parse_placeholders(pre_rendering, isa, funcs, f, dt_par, dt_ret)
						except Exception as err:
							err_message = "Masked '" + f + "<" + dt_key + ">' has been skipped (reason: \"{0}\").".format(err)
							print(" -> " + err_message)
							print("// " + err_message,file=file)
							continue
						#print("ph_ret:", ph_ret)
						add_mask_to_implem_status(funcs, f, dt_key, ff["template"], ph_ret)
						post_rendering = ph_ret["converted_ir"]
						
						func_name = get_func_name(isa, dt_par, dt_ret, f)
						print("static " + build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, func_name, 
													  lmul=lmul, isa_name=True, cpp=False, masked_version="mask") 
										+ " {", file=file)

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
	return 