from tools import *
from headers_def import *

# The helpers will contain logic for very "small" granularity of header generation.
# At first, we'll make things simpler by separating headers in concepts only. 
# i.e every func from a concept (regardless of lmul, mask, etc) will be in the same header.
# for instance airthm_op will be in a header called airthm_op.h, and every versions of the functions from that concept (add,sub,mul,div)
# will live in that header. 
# The headers will still be separated in subdirs by layer (specific/c/cpp/obj) with specific being isa specific headers.

#copied from gen_mipp_tests, should prolly move all to tools.py
def lmul_to_str(lmul, mkind=""):
    #1-> m1 
	#2-> m2
	#4-> m4
	#8-> m8
	#1/2 -> d2
	#1/4 -> d4
	#1/8 -> d8
	
	#temporary fix. Every generator will be handled by 
	#layer_X_mask at some point. But we'll keep it that way for now.
	if mkind == "":
		match lmul:
			case 0 : return ""
			case 1 : return "m1"
			case 2 : return "m2"
			case 4 : return "m4"
			case 8 : return "m8"
			case 0.5 : return "d2"
			case 0.25 : return "d4"
			case 0.125 : return "d8"
	else:
		match lmul:
			case 0 : return ""
			case 1 : return "_m1"
			case 2 : return "_m2"
			case 4 : return "_m4"
			case 8 : return "_m8"
			case 0.5 : return "_d2"
			case 0.25 : return "_d4"
			case 0.125 : return "_d8"

#not the same as gen_mipp_tests
def mask_to_str(mkind):
	if mkind == "mask": 
        return "mask"
    elif mkind == "maskz":
        return "maskz"
    elif mkind == "masks":
        return "masks"
    else:
        return ""

#copied from gen_mipp_tests, should prolly move all to tools.py
def match_concept(func):
	"""
	helper to match a func to an 
	entry in mipp_funcs_concepts. 
	This is used to write files in the relevant 
	subdir for their concept.
	"""
	for concept in mipp_funcs_concepts:
		if func in mipp_funcs_concepts[concept]:
			if concept == "a_trier":
				return "miscellaneous"
			return concept
	return "miscellaneous"

def get_include_name(func, concepts, lmul=0, mask_kind="", layer="c", isa_name=""):
    
    concept = match_concept(func)
    lmul_str = lmul_to_str(lmul, mask_kind)
    mask_str = mask_to_str(mask_kind, layer)
    isa_str = f"_{isa_name}" if isa_name != "" else ""
    return f"{concept}{lmul_str}{mask_str}{isa_str}.h"

def get_include_path(func, concepts, lmul=0, mask_kind="", layer="c"):
    """
    include path is 
    
    layer/concept/lmul/mask_kind/include_name.h
    
    "layer" can either refer to a mipp layer 
    i.e c, cpp, obj or 
    to an isa layer i.e avx2, avx512, etc.

    if lmul == 0, then lmul is not included in the path
    if mask_kind == "", then mask_kind is not included in the path
    """
    include_name = get_include_name(func, concepts, lmul, mask_kind, layer)
    concept = match_concept(func)
    lmul_str = lmul_to_str(lmul, mask_kind)
    mask_str = mask_to_str(mask_kind, layer)
    path = f"{layer}/{concept}"
    if lmul_str != "":
        path += f"/{lmul_str}"
    if mask_str != "":
        path += f"/{mask_str}"
    path += f"/{include_name}"
    return path

def _get_dependencien_regular(func, mipp_funcs):
    
    if func not in mipp_funcs:
        return []
    if "requirements" not in mipp_funcs[func]:
        return []
    requirements = mipp_funcs[func]["requirements"]
    
    for req in requirements:
        #keys are func names, resolve them to include paths
        # we assume each requirements include it's own dependencies, so we don't need to resolve them.
        if req in mipp_funcs:
            req_concept = match_concept(req)
            req_include_name = get_include_name(req, mipp_funcs_concepts)
            req_include_path = get_include_path(req, mipp_funcs_concepts)
            requirements[req] = req_include_path
    return requirements

def _get_dependencies_mask(func, mipp_funcs, mask_kind):
    bucket = get_mask_bucket(mipp_funcs, func, mask_kind)
    if bucket is None:
        return []
    if "requirements" not in bucket:
        return []
    requirements = bucket["requirements"]
    for req in requirements:
        if req in mipp_funcs:
            req_concept = match_concept(req)
            req_include_name = get_include_name(req, mipp_funcs_concepts)
            req_include_path = get_include_path(req, mipp_funcs_concepts)
            requirements[req] = req_include_path
    return requirements
                             
    
def _get_dependencies_lmul(func, mipp_funcs, lmul, isa_name):
    # currently empty but will be used to add lmul/2 dependencies for lmul functions.
    if isa_name == "rvv": 
        return []
    return []

def get_dependencies(func, mipp_funcs, lmul=0, mask_kind=""):
    """
    using the requirements key in mipp_funcs, get the list of dependencies for a given func.
    
    n.b if the func is masked requirements are stored differently. 
    We will also assume that lmul functions additionnaly require lmul/2 versions of 
    the function (even though this is not the case for RVV)
    
    no support for ldiv atm
    """
    dependencies = set()
    regular_deps = _get_dependencien_regular(func, mipp_funcs)
    for dep in regular_deps:
        dependencies.add(regular_deps[dep])
    
    masked_deps = _get_dependencies_mask(func, mipp_funcs, mask_kind)
    for dep in masked_deps:
        dependencies.add(masked_deps[dep])
    
    lmul_deps = _get_dependencies_lmul(func, mipp_funcs, lmul, "")
    for dep in lmul_deps:
        dependencies.add(dep)
    
    return dependencies
    
def tmp_get_include_name(func, concepts, lmul=0, mask_kind="", layer="c", isa_name=""):
    concept = match_concept(func)
    isa_str = f"_{isa_name}" if isa_name != "" else ""
    return f"{concept}{isa_str}.h"

def tmp_get_include_path(func, concepts, lmul=0, mask_kind="", layer="c", isa_name=""):
    """
    layer in simd_ext,c,cpp,obj
    isa_name in avx2,avx512, etc. if isa_name == "" it's a non specific header.
    """
    include_name = tmp_get_include_name(func, concepts, lmul, mask_kind, layer, isa_name)
    concept = match_concept(func)
    
    isa_str = f"{isa_name}/" if isa_name != "" else ""
    return f"{layer}/{isa_str}{concept}/{include_name}"
    
class IncludePath:
    #ONE include path and it's dependencies
    def __init__(self, func):
        self.func = func
        self.path = tmp_get_include_path(func, mipp_funcs_concepts)
        self.dependencies = set()
        self.file = None
        
    def resolve_dependencies(self, mipp_funcs, concepts):
        #get regular dependencies
        deps = get_dependencies(self.func, mipp_funcs, 0, "")
        for dep in deps:
            self.dependencies.add(dep)
    
    def get_fd(self, base_dir):
        full_path = f"{base_dir}/{self.path}"
        dir = os.path.dirname(full_path)
        if not os.path.exists(dir):
            os.makedirs(dir)
        self.file = open(full_path, "w")
        return self.file
        
class IncludeLayer:
    # all the includes path for 1 layer (simd_ext, c, cpp, obj) and their dependencies.
    def __init__(self, layer_name=""):
        self.layer_name = layer_name
        self.includes = {} #key is func name, value is IncludePath object
        self.dir = None
    
    def add_includes(self, func, mipp_funcs, concepts):
        if func not in self.includes:
            include_path = IncludePath(func)
            include_path.resolve_dependencies(mipp_funcs, concepts)
            self.includes[func] = include_path
    
    def get_fd(self, base_dir):
        #get file descriptor for each include path. We will need it to write the files later.
        for func in self.includes:
            include_path = self.includes[func].path
            full_path = f"{base_dir}/{include_path}"
            dir = os.path.dirname(full_path)
            if not os.path.exists(dir):
                os.makedirs(dir)
            self.includes[func].file = open(full_path, "w")

class IncludeManager:
    # all the include layers
    def __init__(self, isa_list):
        self.layers = {} #key is layer name, value is IncludeLayer object
        for layer in ["c", "cpp", "obj"]:
            self.layers[layer] = IncludeLayer(layer)
        for isa in isa_list:
            self.layers[isa] = IncludeLayer(isa)
        
        for layer in self.layers:
            for func in mipp_funcs_concepts:
                self.layers[layer].add_includes(func, mipp_funcs, mipp_funcs_concepts)
        #generate fd for each include path
        for layer in self.layers:
            self.layers[layer].get_fd("../include")
            
    def get_fd(self, layer_name, func):
        if layer_name in self.layers:
            layer = self.layers[layer_name]
            if func in layer.includes:
                return layer.includes[func].file
        return None

    def get_layer(self, layer_name):
        if layer_name in self.layers:
            return self.layers[layer_name]
        return None
    