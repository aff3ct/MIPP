from jinja2 import Template, StrictUndefined

from include_gen import IncludeManager
from headers_def import mipp_funcs

def generate_mipp_h(include_manager=None):

	file = open("../include/mipp.h", "w")

	template_file = """#ifndef MY_INTRINSICS_PLUS_PLUS_H_
#define MY_INTRINSICS_PLUS_PLUS_H_

#include "c/common.h"
"""

	include_list = ""
	for func in mipp_funcs:
		include_list += "#include \"c/functions/" +  func + ".h\"\n"
	postfix = """#endif /* MY_INTRINSICS_PLUS_PLUS_H_ */"""
 
	template_file += include_list + "\n" + postfix

	j2_template = Template(template_file, undefined=StrictUndefined)
	print(j2_template.render(), file=file)
	file.close()