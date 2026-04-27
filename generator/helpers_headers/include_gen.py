import os, tempfile, shutil

from tools import *
from headers_def import *

# The helpers 
def get_include_name(func, layer=""):
    if layer == "":
        return f"{func}.h"
    else : 
        return f"{layer}_{func}.h"

def get_include_path(func, layer):
    if func == "common":
        return f"{layer}/common.h"
    include_name = get_include_name(func)
    
    if layer == "" :
        return include_name
    return f"{layer}/functions/{include_name}"


#copied from gen_mipp_tests, should prolly move all to tools.py
def match_concept(func):
    """
    helper to match a func to an 
    entry in mipp_funcs_concepts. 
    This is used to write files in the relevant 
    subdir for their concept.
    """
    if func == "common":
        return "common"
    
    for concept in mipp_funcs_concepts:
        if func in mipp_funcs_concepts[concept]:
            if concept == "a_trier":
                return "miscellaneous"
            return concept
    return "miscellaneous"

def _get_implem_status_requirements_all_dt_keys(funcs, f):
    """
    gets the union of all requirements for all dt_keys in implem_status for a given function. 
    no side effects on funcs[f]["implem_status"].
    """
    requirements = {}
    if "implem_status" in funcs[f]:
        for dt_key in funcs[f]["implem_status"]:
            for implem in funcs[f]["implem_status"][dt_key]:
                if "requirements" in implem and implem["requirements"]:
                    for req in implem["requirements"]:
                        requirements[req] = implem["requirements"][req]
    return requirements

def _get_dependencies_regular(func, mipp_funcs, layer="c"):
    # path is functions/func.h and dependencies are in the requirements key of mipp_funcs[func]["implem_status"] for all dt_keys.
    if func not in mipp_funcs:
        return {}
    requirements = _get_implem_status_requirements_all_dt_keys(mipp_funcs, func)
    for req in requirements:
        if req in mipp_funcs:
            req_concept = match_concept(req)
            req_include_name = get_include_name(req, layer)
            requirements[req] = req_include_name
    return requirements

def _get_dependencies_mask(func, mipp_funcs, mask_kind):
    # bucket = get_masked_bucket(mipp_funcs, func, "", mask_kind)
    # if bucket is None:
    #     return []
    # if "requirements" not in bucket:
    #     return []
    # requirements = bucket["requirements"]
    # for req in requirements:
    #     if req in mipp_funcs:
    #         req_concept = match_concept(req)
    #         req_include_name = get_include_name(req, mipp_funcs_concepts)
    #         req_include_path = get_include_path(req, mipp_funcs_concepts)
    #         requirements[req] = req_include_path
    # return requirements
    return []
                             
    
def _get_dependencies_lmul(func, mipp_funcs, lmul, isa_name):
    # currently empty but will be used to add lmul/2 dependencies for lmul functions.
    if isa_name == "rvv": 
        return []
    return []

def get_dependencies(func, mipp_funcs, lmul=0, mask_kind="", layer=""):
    """
    using the requirements key in mipp_funcs, get the list of dependencies for a given func.
    
    n.b if the func is masked requirements are stored differently. 
    We will also assume that lmul functions additionnaly require lmul/2 versions of 
    the function (even though this is not the case for RVV)
    
    no support for ldiv atm
    """
    
    if func == "common":
        return set()
    
    dependencies = set()
    if layer != "" :
        dependencies.add(f"../{layer}_common.h")
    else :
        dependencies.add("common.h")
    
    #print(f"Getting dependencies for {func} in layer {layer} with lmul {lmul} and mask kind {mask_kind}")
    print(f"Getting dependencies for {func} in layer {layer} with lmul {lmul} and mask kind {mask_kind}")
    regular_deps = _get_dependencies_regular(func, mipp_funcs, layer=layer)
    for dep in regular_deps:
        dependencies.add(regular_deps[dep])
    
    masked_deps = _get_dependencies_mask(func, mipp_funcs, mask_kind)
    for dep in masked_deps:
        dependencies.add(masked_deps[dep])
    
    lmul_deps = _get_dependencies_lmul(func, mipp_funcs, lmul, "")
    for dep in lmul_deps:
        dependencies.add(dep)
    
    print(f"Dependencies for {func} in layer {layer} with lmul {lmul} and mask kind {mask_kind}: {dependencies}")
    return dependencies
    

class IncludePath:
    # ONE include path and it's dependencies
    # is_common used to specify if it's not a func header for instance w macros / struct definitions that are shared.
    def __init__(self, func, layer):
        self.func = func
        self.name = get_include_name(func, layer)
        self.dependencies = set()
        self.file = None
        self._is_prefixed = False
        
    def resolve_dependencies(self, mipp_funcs,  lmul, mask_kind, layer):
        #get regular dependencies
        deps = get_dependencies(self.func, mipp_funcs, lmul=lmul, mask_kind=mask_kind, layer=layer)
        for dep in deps:
            self.dependencies.add(dep)
    
    def get_fd(self, base_dir):
        full_path = f"{base_dir}/{self.name}"
        os.makedirs(os.path.dirname(full_path), exist_ok=True)

        if self.file is None:
        # DO NOT use "w+" here; it truncates and will remove any prefix you wrote.
            self.file = open(full_path, "a+", encoding="utf-8", newline="")

        return self.file

    def close_fd(self):
        if self.file is not None:
            self.file.close()
            self.file = None
            
    def write_prefix(self, base_dir):
        if self._is_prefixed:
            return

        full_path = f"{base_dir}/{self.name}"
        os.makedirs(os.path.dirname(full_path), exist_ok=True)

        # Ensure current generated body is on disk
        if self.file is not None:
            self.file.flush()
            self.file.seek(0)

        # Read current contents (from the same handle if present, otherwise from disk)
        if self.file is not None:
            old = self.file.read()
            self.file.close()
            self.file = None
        else:
            try:
                with open(full_path, "r", encoding="utf-8", newline="") as f:
                    old = f.read()
            except FileNotFoundError:
                old = ""

        # Build prefix
        prefix = "#pragma once\n"
        for dep in self.dependencies:
            prefix += f'#include "{dep}"\n'
        prefix += "\n"

        # Rewrite file from scratch with prefix + old
        with open(full_path, "w", encoding="utf-8", newline="") as f:
            f.write(prefix)
            f.write(old)
        # Reopen for further appends
        self.file = open(full_path, "a+", encoding="utf-8", newline="")
        self._is_prefixed = True
        
    # def write(self, content, base_dir):
    #     fd = self.get_fd(base_dir)
    #     print(content, file=fd)
    #     self.close_fd()
        
class IncludeLayer:
    # all the includes path for 1 layer (simd_ext, c, cpp, obj) and their dependencies.
    def __init__(self, layer_name=""):
        self.layer_name = layer_name
        self.includes = {} #key is func name, value is IncludePath object
        self.dir = None
    
    def add_includes(self, func, mipp_funcs, concepts):
        if func not in self.includes:
            include_path = IncludePath(func, self.layer_name)
            include_path.resolve_dependencies(mipp_funcs, lmul=0, mask_kind="", layer=self.layer_name)
            self.includes[func] = include_path
    
    def set_fd(self, base_dir):
        # get file descriptor for each include path. We will need it to write the files later.
        # also add common.h in the layer and common.h as a dependency for all the other includes in the layer.
        for func in self.includes:
            if func != "common":
                self.includes[func].dependencies.add(f"{self.layer_name}/common.h")
            self.includes[func].get_fd(base_dir)
            
    def get_sorted_includes(self):
        # returns the include paths sorted by dependencies order. 
        # we can then write the files in this order to ensure that dependencies are written before the files that depend on them.
        sorted_includes = []
        visited = set()

        def visit(func):
            if func in visited:
                return
            visited.add(func)
            for dep in self.includes[func].dependencies:
                dep_func = dep.split("/")[-1].split(".")[0] # get func name from path
                if dep_func in self.includes:
                    visit(dep_func)
            sorted_includes.append(func)

        for func in self.includes:
            visit(func)

        return sorted_includes
        

class IncludeManager:
    # all the include layers
    def __init__(self, isa_list, base_dir="../include"):
        self.layers = {} #key is layer name, value is IncludeLayer object
        self.base_dir = base_dir
        for layer in ["c", "cpp", "obj"]:
            self.layers[layer] = IncludeLayer(layer)
        for isa in isa_list:
            self.layers[isa] = IncludeLayer(isa)
        
        for layer in self.layers:
            for func in ["common"] + list(mipp_funcs.keys()):
                self.layers[layer].add_includes(func, mipp_funcs, mipp_funcs_concepts)
        #generate fd for each include path
        # for layer in self.layers:
        #     self.layers[layer].get_fd("../include")
            
    def get_fd(self, layer_name, func):
        if layer_name in self.layers:
            layer = self.layers[layer_name]
            if func in layer.includes:
                base_dir = f"{self.base_dir}/{layer_name}"
                if func != "common" : 
                    base_dir = f"{self.base_dir}/{layer_name}/functions"
                return layer.includes[func].get_fd(base_dir)
        return None
    
    def resolve_all_dependencies(self, layer_name, funcs):
        # resolve deps for all funcs, all lmul, all mask kinds 
        # appends pragma once and includes to each file
        # also includes common.h. 
        
        for func in self.layers[layer_name].includes:
            if func == "common":
                continue

            include_path = self.layers[layer_name].includes[func]
            include_path.resolve_dependencies(funcs, lmul=0, mask_kind="", layer=layer_name)
            include_path.write_prefix(f"{self.base_dir}/{layer_name}/functions")
    
    def close_fd(self, layer_name, func):
        if layer_name in self.layers:
            layer = self.layers[layer_name]
            if func in layer.includes:
                layer.includes[func].close_fd()

    def get_layer(self, layer_name):
        if layer_name in self.layers:
            return self.layers[layer_name]
        return None

    def create_glue_file(self, layer_name, file_path):
        # include all the headers in a layer in a glue file
        if layer_name in self.layers:
            layer = self.layers[layer_name]
            with open(file_path, "w", encoding="utf-8", newline="") as f:
                f.write("#pragma once\n")
                for func in layer.includes:
                    include_path = layer.includes[func]
                    if func != "common":
                        f.write(f'#include "functions/{include_path.name}"\n')
                    else :
                        f.write(f'#include "{include_path.name}"\n')