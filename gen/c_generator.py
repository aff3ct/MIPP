from jinja2 import Template, StrictUndefined
import json
import re

from tools import *

def gen_c_defines(isa, file):
	template = """#define MIPP_MACRO_{{ type_category_upper }}{{ datatype.n_bits }}(MACRO, ...) MACRO(__VA_ARGS__, {{ datatype.n_bits }}, {{ datatype.category }}, {{ isa_datatype.data_ext }}, {{ isa_datatype.data_ext_logi }}, {{ isa_datatype.to_ptr }})"""
	j2_template = Template(template, undefined=StrictUndefined)

	for dt in isa["datatypes"]:
		print(j2_template.render(isa=isa, type_category_upper=datatypes[dt]["category"].upper(), isa_datatype=isa["datatypes"][dt], datatype=datatypes[dt]), file=file)

	print("#define MIPP_" + isa["name"].upper() + "_RVD_SIZE_BIT " + str(isa["size"]), file=file)
	print("#define MIPP_" + isa["name"].upper() + "_RVD_SIZE_BYTE " + str(int(isa["size"] / 8)), file=file)

	template = """#define MIPP_{{isa_name_upper}}_N_{{type_category_upper}}{{n_bits}} {{n_elmts}}"""
	j2_template = Template(template, undefined=StrictUndefined)

	for dt in isa["datatypes"]:
		n_elmts = int(isa["size"] / datatypes[dt]["n_bits"])
		print(j2_template.render(isa_name_upper=isa["name"].upper(), type_category_upper=datatypes[dt]["category"].upper(), n_bits=datatypes[dt]["n_bits"], n_elmts=n_elmts), file=file)

def gen_c_structures(isa, file):
	template = """typedef struct { {{ isa_datatype.reg }} m; } rvd_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t;"""
	j2_template = Template(template, undefined=StrictUndefined)

	for dt in isa["datatypes"]:
		print(j2_template.render(isa=isa, isa_datatype=isa["datatypes"][dt], datatype=datatypes[dt]), file=file)

	template = """typedef struct { {{ isa_datatype.msk }} m; } rvm_{{ isa.name }}_{{ datatype.category }}{{ datatype.n_bits }}_t;"""
	j2_template = Template(template, undefined=StrictUndefined)

	for dt in isa["datatypes"]:
		print(j2_template.render(isa=isa, isa_datatype=isa["datatypes"][dt], datatype=datatypes[dt]), file=file)

def gen_c_functions(isa, file, funcs, implems):
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

					if is_missing_func(funcs, f, dt_key):
						j2_template = Template(ff["template"]["code"], undefined=StrictUndefined)
						instr_name = ""
						if "instr_name" in ff:
							instr_name = ff["instr_name"]
						pre_rendering = j2_template.render(isa=isa, instr_name=instr_name, dt_par=datatypes[dt_par], dt_ret=datatypes[dt_ret], isa_dt_par=isa["datatypes"][dt_par], isa_dt_ret=isa["datatypes"][dt_ret], cstdint_ret=datatypes[dt_ret]["cstd"])

						try:
							ph_ret = parse_placeholders(pre_rendering, isa, funcs, f, dt_par, dt_ret)
						except Exception as err:
							print(" -> '" + f + "<" + dt_key + ">' has been skipped (reason: \"{0}\").".format(err))
							continue

						ifd = ""
						if "type" in ff and ff["type"] == "emulated":
							if "implem_status" in funcs[f] and dt_key in funcs[f]["implem_status"]:
								is_first = True
								i = 0
								for implem in funcs[f]["implem_status"][dt_key]:
									ifd_sub = build_ifdef(funcs, f, dt_key, i)
									if ifd_sub:
										if not is_first:
											ifd = ifd + " && "
										ifd = ifd + "!( "
										ifd = ifd + ifd_sub
										ifd = ifd + " )"
										is_first = False
									i = i +1

						cur_implem_status = { "if": "", "requirements": {} }
						if "if" in ff:
							cur_implem_status["if"] = ff["if"]
						cur_implem_status["requirements"] = ph_ret["requirements"]

						if "implem_status" not in funcs[f]:
						 	funcs[f]["implem_status"] = {}
						if dt_key not in funcs[f]["implem_status"]:
						 	funcs[f]["implem_status"][dt_key] = []
						funcs[f]["implem_status"][dt_key].append(cur_implem_status)

						post_rendering = ph_ret["converted_ir"]

						ifd_cur = build_ifdef(funcs, f, dt_key, len(funcs[f]["implem_status"][dt_key])-1)
						if ifd and ifd_cur:
							ifd = ifd + " && ( " + ifd_cur + " )"
						elif ifd_cur:
							ifd = ifd_cur
						if ifd:
							print("#if " + ifd, file=file)
							if "type" in ff and ff["type"] == "emulated":
								funcs[f]["implem_status"][dt_key][len(funcs[f]["implem_status"][dt_key])-1]["if"] = ifd

						if len(dt.split(',')) <= 1:
							func_name = build_func_name_short(isa, dt_par, f);
						else:
							func_name = build_func_name(isa, dt_par, dt_ret, f);
						print(build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, func_name) + " {", file=file)

						if ff["template"]["format"] == "short":
							if funcs[f]["proto"]["ret"]["type"]:
								print("\t" + build_type(funcs[f]["proto"]["ret"]["type"], datatypes[dt_ret], isa) + " res;", file=file);
								print("\tres.m = ", end='', file=file)
							else:
								print("\t", end='', file=file)
						print(post_rendering, file=file)
						if ff["template"]["format"] == "short":
							if funcs[f]["proto"]["ret"]["type"]:
								print("\treturn res;", file=file);
						print("}", file=file)
						if ifd:
							print("#endif", file=file)

						if "type" in ff and ff["type"] == "emulated":
							print(" -> '" + f + "<" + dt_key + ">' has been implemented.")
		else:
			print("Panic: '" + f + "' function does not exist.")
			exit(-1)

def gen_c_missing_functions(isa, file, funcs):
	for f in funcs:
		for dt in funcs[f]["datatypes"]:
			if len(dt.split(',')) <= 1:
				dt_par = dt.split(',')[0]
				dt_ret = dt.split(',')[0]
			else:
				dt_par = dt.split(',')[0]
				dt_ret = dt.split(',')[1]
			dt_key = dt_par + "," + dt_ret
			defines = []

			if is_missing_func(funcs, f, dt_key):
				ifd = ""
				if "implem_status" in funcs[f] and dt_key in funcs[f]["implem_status"]:
					is_first = True
					i = 0
					for implem in funcs[f]["implem_status"][dt_key]:
						ifd_sub = build_ifdef(funcs, f, dt_key, i)
						if ifd_sub:
							if not is_first:
								ifd = ifd + " && "
							ifd = ifd + "!( "
							ifd = ifd + ifd_sub
							ifd = ifd + " )"
							is_first = False
						i = i +1
				if ifd:
					print("#if " + ifd, file=file)

				if len(dt.split(',')) <= 1:
					func_name = build_func_name_short(isa, dt_par, f)
				else:
					func_name = build_func_name(isa, dt_par, dt_ret, f)
				print(build_proto(funcs[f]["proto"], dt_par, dt_ret, isa, func_name) + " {", file=file)
				print("\tprintf(\"MIPP panic: '%s' is unimplemented.\\n\", \""+func_name+"\");", file=file);
				print("\texit(-1);", file=file);
				print("}", file=file);

				if ifd:
					print("#endif", file=file)
