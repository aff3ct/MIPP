"""
Include Generator Module
Manages output directories and file creation, tracking preprocessor wrappers,
headers formatting, and dependency generation structures.
"""
import os, tempfile, shutil, io

from tools import *
from registry import *

# WIP : This is not actually implemented **YET**
# dependencies mode in : 
# function_header -> each function lives in it's own header, dependencies are included in that header.
# category_header -> each category (category) lives in a header, functions are defined in that header, dependencies are included in that header.
#   for instance, all functions in the "arithmetic" category would be defined in arithmetic.h and include their dependencies.
# single_header -> all functions live in a single header, dependencies are included in that header.

# The helpers 
def normalize_variant(variant):
    if not variant or variant in ("no_mask", "u"):
        return "u"
    if variant in ("mask", "m"):
        return "m"
    if variant in ("maskz", "z"):
        return "z"
    if variant in ("masks", "s"):
        return "s"
    return "u"

def normalize_lmul(lmul):
    if lmul in (0, 1, "0", "1", "m1"):
        return "m1"
    if isinstance(lmul, int):
        if lmul > 1:
            return f"m{lmul}"
        elif lmul < 0:
            return f"d{abs(lmul)}"
    if isinstance(lmul, str):
        if lmul.startswith(("m", "d")):
            return lmul
        try:
            val = int(lmul)
            return normalize_lmul(val)
        except ValueError:
            pass
    return "m1"

def _get_include_name(func, layer=""):
    if layer in ("cpp", "templates") or layer.endswith("_cpp"):
        return f"{func}.hpp"
    else:
        return f"{func}.h"

def _get_include_path(func, layer):
    category = _match_category(func)
    include_name = _get_include_name(func, layer)
    
    if func == "common":
        if layer == "c":
            return "mipp/internal/interfaces/c/common.h"
        elif layer == "cpp":
            return "mipp/internal/interfaces/cpp/common.hpp"
        elif layer == "templates":
            return "mipp/internal/templates/cpp/common.hpp"
        elif layer.endswith("_cpp"):
            isa = layer[:-4]
            return f"mipp/internal/simd_ext/{isa}/cpp/common.hpp"
        elif layer != "":
            return f"mipp/internal/simd_ext/{layer}/c/common.h"
        else:
            return "common.h"

    if layer == "c":
        return f"mipp/internal/interfaces/c/functions/{category}/{include_name}"
    elif layer == "cpp":
        return f"mipp/internal/interfaces/cpp/functions/{category}/{include_name}"
    elif layer == "templates":
        return f"mipp/internal/templates/cpp/functions/{category}/{include_name}"
    elif layer.endswith("_cpp"):
        isa = layer[:-4]
        return f"mipp/internal/simd_ext/{isa}/cpp/functions/{category}/{include_name}"
    elif layer != "":
        return f"mipp/internal/simd_ext/{layer}/c/functions/{category}/{include_name}"
    else:
        return f"functions/{category}/{include_name}"


#copied from gen_mipp_tests, should prolly move all to tools.py
def _match_category(func):
    """
    helper to match a func to an entry in categories.
    This is used to write files in the relevant subdir for their category.
    """
    if func == "common":
        return "common"
    
    for category in categories:
        if func in categories[category]:
            if category == "a_trier":
                return "miscellaneous"
            return category
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


def _get_dependencies_regular_category_header(func, interfaces, layer="c"):
    
    requirements = _get_implem_status_requirements_all_dt_keys(interfaces, func)
    for req in requirements:
        if req in interfaces:
            req_concept = _match_category(req)
            req_include_name = _get_include_name(req_concept, layer)
            requirements[req] = req_include_name
    return requirements
    
def _get_dependencies_mask_category_header(func, interfaces, mask_kind, layer="c"):
    requirements = _get_implem_status_requirements_mask_dt_keys(interfaces, func, mask_kind)
    for req in requirements:
        if req in interfaces:
            req_concept = _match_category(req)
            req_include_name = _get_include_name(req_concept, layer)
            requirements[req] = req_include_name
    return requirements


def _get_dependencies_regular_single_header(func, interfaces, layer="c"):
    print("Stub, not done :(")
    return

def _get_dependencies_mask_single_header(func, interfaces, mask_kind, layer="c"):
    print("Stub, not done :(")
    return   

def _get_dependencies_regular(func, interfaces, layer="c", mode="function_header"):
    # path is functions/func.h and dependencies are in the requirements key of interfaces[func]["implem_status"] for all dt_keys.
    
    if mode == "category_header":
        return _get_dependencies_regular_category_header(func, interfaces, layer=layer)
    elif mode == "single_header":
        return _get_dependencies_regular_single_header(func, interfaces, layer=layer)
    
    if func not in interfaces:
        return {}
    requirements = _get_implem_status_requirements_all_dt_keys(interfaces, func)
    
    for req in requirements:
        if req in interfaces:
            req_concept = _match_category(req)
            req_include_name = _get_include_path(req, layer)
            requirements[req] = req_include_name
    return requirements

def _get_all_dt_keys_masked(funcs, f, mask_kind):
    """
    returns all dt_keys for a given function and mask kind. 
    
    """
    dt_keys = []
    if "mask_support" in funcs[f] and is_supported_mask_kind(funcs[f]["mask_support"], mask_kind):
        #dt keys live in implem_status_masked
        # print(f"Function {f} supports mask kind {mask_kind}, checking implem_status_masked for dt_keys")
        if "implem_status_masked" in funcs[f] :
            for dt_key in funcs[f]["implem_status_masked"]:
                
                dt_keys.append(dt_key)
    # print(f"Function {f} supports mask kind {mask_kind}, dt_keys found: {dt_keys}")
    return dt_keys

def _get_implem_status_requirements_mask_dt_keys(funcs, f, mask_kind, mode="function_header"):
    """
    returns the list of func that are required by the implementations of f for a given mask_kind for every dt_key. 
    Simple getter, doesn't modify anything.
    """
    requirements = {}

    for dt_key in _get_all_dt_keys_masked(funcs, f, mask_kind):
        bucket = get_masked_bucket(funcs, f, dt_key, mask_kind)

        if bucket is not None:
            for implem in bucket:
                if "requirements" in implem and implem["requirements"]:
                    for req in implem["requirements"]:
                        requirements[req] = implem["requirements"][req]
    return requirements

def _get_dependencies_mask(func, interfaces, mask_kind, layer="c", mode="function_header"):
    
    # path is functions/func.h and dependencies are in the requirements key of interfaces[func]["implem_status"] for all dt_keys and mask_kind.
    if func not in interfaces:
        return {}

    if mode == "category_header":
        return _get_dependencies_mask_category_header(func, interfaces, mask_kind, layer=layer)
    elif mode == "single_header":
        return _get_dependencies_mask_single_header(func, interfaces, mask_kind, layer=layer)

    requirements = _get_implem_status_requirements_mask_dt_keys(interfaces, func, mask_kind)
    for req in requirements:
        if req in interfaces:
            req_include_name = _get_include_path(req, layer)
            requirements[req] = req_include_name
    return requirements
                             


def _get_dependencies(func, interfaces, lmul=0, mask_kind="", layer="", mode="function_header"):
    """
    using the requirements key in interfaces, get the list of dependencies for a given func.
    
    n.b if the func is masked requirements are stored differently. 
    We will also assume that lmul functions additionnaly require lmul/2 versions of 
    the function (even though this is not the case for RVV)
    
    no support for ldiv atm
    """
    
    if func == "common":
        return set()
    
    dependencies = set()
    
    common_include = _get_include_path("common", layer)
    dependencies.add(common_include)
    
    #print(f"Getting dependencies for {func} in layer {layer} with lmul {lmul} and mask kind {mask_kind}")

    regular_deps = _get_dependencies_regular(func, interfaces, layer=layer, mode=mode)
    # remove duplicates
    # set_regular_deps = set(regular_deps.values())
    for dep in regular_deps:
        if dep == func:
            continue
        dependencies.add(regular_deps[dep])
    
    masked_deps = _get_dependencies_mask(func, interfaces, mask_kind, layer=layer, mode=mode)
    # remove duplicates
    # set_regular_deps = set(regular_deps.values())

    for dep in masked_deps:
        if dep == func:
            continue
        dependencies.add(masked_deps[dep])

    if mode == "function_header":
        if func in dependencies:
            dependencies.remove(func)
    elif mode == "category_header":
        category = _match_category(func)
        include_name = _get_include_name(category, layer)
        if include_name in dependencies:
            dependencies.remove(include_name)

    return dependencies
    

class IncludePath:
    # ONE include path and it's dependencies
    # is_common used to specify if it's not a func header for instance w macros / struct definitions that are shared.
    def __init__(self, func, layer,mode="function_header"):
        self.func = func
        if mode == "function_header":
            self.name = _get_include_name(func, layer)
        elif mode == "category_header":
            category = _match_category(func)
            self.name = _get_include_name(category, layer)
            print(f"IncludePath for func {func} in layer {layer} with mode {mode} has name {self.name}")
        elif mode == "single_header":
            print("Stub, not done :(")
        self.dependencies = set()
        self.file = None
        self._is_prefixed = False
        self.mode = mode
        
    def resolve_dependencies(self, interfaces,  lmul, mask_kind, layer):
        #get regular dependencies
        deps = _get_dependencies(self.func, interfaces, lmul=lmul, mask_kind=mask_kind, layer=layer, mode=self.mode)
        for dep in deps:
            self.dependencies.add(dep)
    
    def _get_full_path(self, base_dir):
        if self.func == "common":
            return f"{base_dir}/{self.name}"
        category = _match_category(self.func)
        return f"{base_dir}/functions/{category}/{self.name}"

    def get_fd(self, base_dir):
        if self.mode == "function_header":
            full_path = self._get_full_path(base_dir)
            os.makedirs(os.path.dirname(full_path), exist_ok=True)

            if self.file is None:
                self.file = open(full_path, "a+", encoding="utf-8", newline="")

            return self.file
        elif self.mode == "category_header":
            full_path = f"{base_dir}/{self.name}"
            os.makedirs(os.path.dirname(full_path), exist_ok=True)

            if self.file is None:
                self.file = open(full_path, "a+", encoding="utf-8", newline="")

            return self.file
        elif self.mode == "single_header":
            print("Stub, not done :(")

    def close_fd(self):
        if self.file is not None:
            self.file.close()
            self.file = None
            
    def write_prefix(self, base_dir):
        if self._is_prefixed:
            return

        full_path = self._get_full_path(base_dir)
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

        # Extract forward declarations (lines like "static inline ... ;")
        # and move them before the #include directives to break circular deps.
        fwd_decls = []
        body_lines = []
        for line in old.split("\n"):
            stripped = line.strip()
            if (stripped.startswith("static inline ") and stripped.endswith(";")
                    and "{" not in stripped):
                fwd_decls.append(line)
            else:
                body_lines.append(line)

        # Remove any leading empty lines from body_lines to prevent double blank lines after includes
        while body_lines and body_lines[0].strip() == "":
            body_lines.pop(0)

        # sort dependencies to ensure deterministic order in includes
        dep_list = list(self.dependencies)
        dep_list.sort()

        common_deps = [dep for dep in dep_list if dep.endswith("common.h") or dep.endswith("common.hpp")]
        other_deps = [dep for dep in dep_list if not (dep.endswith("common.h") or dep.endswith("common.hpp"))]

        # Build prefix
        prefix = "#pragma once\n\n"
        for dep in common_deps:
            prefix += f'#include "{dep}"\n'
        if common_deps:
            prefix += "\n"

        # Forward declarations first (before other includes to break circular deps)
        if fwd_decls:
            for decl in fwd_decls:
                prefix += decl + "\n"
            prefix += "\n"

        for dep in other_deps:
            prefix += f'#include "{dep}"\n'

        # Rewrite file from scratch with prefix + remaining body
        with open(full_path, "w", encoding="utf-8", newline="") as f:
            f.write(prefix)
            if body_lines:
                f.write("\n" + "\n".join(body_lines))
        # Reopen for further appends
        self.file = open(full_path, "a+", encoding="utf-8", newline="")
        self._is_prefixed = True

    
    def write_custom_prefix(self, custom_prefix, base_dir, mode="function_header"):
        if mode == "function_header":
            full_path = self._get_full_path(base_dir)
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
            prefix = custom_prefix + "\n"

            # Rewrite file from scratch with prefix + old
            with open(full_path, "w", encoding="utf-8", newline="") as f:
                f.write(prefix)
                f.write(old)
            # Reopen for further appends
            self.file = open(full_path, "a+", encoding="utf-8", newline="")
        elif mode == "category_header":
            category = _match_category(self.func)
            full_path = f"{base_dir}/{category}.h"
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
            prefix = custom_prefix + "\n"

            # Rewrite file from scratch with prefix + old
            with open(full_path, "w", encoding="utf-8", newline="") as f:
                f.write(prefix)
                f.write(old)
            # Reopen for further appends
            self.file = open(full_path, "a+", encoding="utf-8", newline="")
            self._is_prefixed = True

class IncludeCategory:
    # a category of includes for a given category. For instance, all functions in the "arithmetic" category would be in the same category.
    def __init__(self, category, layer):
        self.category = category
        self.name = _get_include_name(category, layer)
        self.includes = {} #key is func name, value is IncludePath object
        self.file = None
        self.dependencies = set()
        self.functions = set()
        self._is_prefixed = False
    def get_functions(self, interfaces):
        for func in interfaces:
            if _match_category(func) == self.category:
                self.functions.add(func)
    
    def add_includes(self, interfaces, layer):
        self.get_functions(interfaces)
        for func in self.functions:
            include_path = IncludePath(func, layer, mode="category_header")
            include_path.resolve_dependencies(interfaces, lmul=0, mask_kind="", layer=layer)
            self.includes[func] = include_path
            for dep in include_path.dependencies:
                self.dependencies.add(dep)
    
    def get_sorted_includes(self):
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
    
    def get_fd(self, base_dir):
        full_path = f"{base_dir}/{self.name}"
        os.makedirs(os.path.dirname(full_path), exist_ok=True)

        if self.file is None:
            self.file = open(full_path, "a+", encoding="utf-8", newline="")
        return self.file

    def resolve_dependencies(self, interfaces, lmul=0, mask_kind="", layer=""):
        for func in self.includes:
            include_path = self.includes[func]
            include_path.resolve_dependencies(interfaces, lmul=lmul, mask_kind=mask_kind, layer=layer)
            for dep in include_path.dependencies:
                self.dependencies.add(dep)

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
    def close_fd(self):
        if self.file is not None:
            self.file.close()
            self.file = None
    
    def write_custom_prefix(self, custom_prefix, base_dir):
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
        prefix = custom_prefix + "\n"

        # Rewrite file from scratch with prefix + old
        with open(full_path, "w", encoding="utf-8", newline="") as f:
            f.write(prefix)
            f.write(old)
        # Reopen for further appends
        self.file = open(full_path, "a+", encoding="utf-8", newline="")
        self._is_prefixed = True
    
class IncludeLayer:
    # all the includes path for 1 layer (simd_ext, c, cpp, obj) and their dependencies.
    def __init__(self, layer_name="", mode="function_header"):
        self.layer_name = layer_name
        self.includes = {} #key is func name, value is IncludePath object
        self.dir = None
        self.mode = mode

        if mode == "category_header":
            self.categories = {} #key is category name, value is IncludeCategory object
    
    def add_includes(self, func, interfaces, categories):
        if self.mode == "function_header" :
            if func not in self.includes:
                include_path = IncludePath(func, self.layer_name, mode=self.mode)
                include_path.resolve_dependencies(interfaces, lmul=0, mask_kind="", layer=self.layer_name)
                self.includes[func] = include_path
        elif self.mode == "category_header": # code not checked, just a stub for now
            category = _match_category(func)
            if category not in self.categories:
                include_category = IncludeCategory(category, self.layer_name)
                include_category.add_includes(interfaces, self.layer_name)
                self.categories[category] = include_category
                for dep in include_category.dependencies:
                    self.includes[dep] = IncludePath(dep.split("/")[-1].split(".")[0], self.layer_name, mode=self.mode)
                    self.includes[dep].dependencies = set() #
    
    def set_fd(self, base_dir):
        # get file descriptor for each include path. We will need it to write the files later.
        # also add common.h in the layer and common.h as a dependency for all the other includes in the layer.
        for func in self.includes:
            if func != "common":
                self.includes[func].dependencies.add(f"{self.layer_name}/common.h")
            self.includes[func].get_fd(base_dir, mode=self.mode)
            
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
    def __init__(self, isa_list, base_dir="../include", mode="function_header", granularity="coarse"):
        self.layers = {} #key is layer name, value is IncludeLayer object
        self.base_dir = base_dir
        self.mode = mode
        self.granularity = granularity
        self.isa_list = isa_list
        self.atomic_files = {} # (layer_name, func, variant, lmul) -> dict
        self.emitted_atomics = {} # layer_name -> dict(func -> set((variant, lmul)))

        for layer in ["c", "cpp", "obj", "scalar", "templates"]:
            self.layers[layer] = IncludeLayer(layer, mode=mode)
        for isa in isa_list:
            self.layers[isa] = IncludeLayer(isa, mode=mode)
        for isa in isa_list:
            name = isa + "_cpp"
            self.layers[name] = IncludeLayer(name, mode=mode)
        
        for layer in self.layers:
            for func in ["common"] + list(interfaces.keys()):
                self.layers[layer].add_includes(func, interfaces, categories)

    def set_isa_configs(self, isas_dict):
        if not hasattr(self, "_isa_configs"):
            self._isa_configs = {}
        for name, cfg in isas_dict.items():
            self._isa_configs[name] = cfg
            self._isa_configs[f"{name}_cpp"] = cfg

    def get_isa_config(self, isa_name):
        if not hasattr(self, "_isa_configs"):
            self._isa_configs = {}
        if isa_name not in self._isa_configs:
            if isa_name in ("scalar", "scalar_cpp"):
                from registry import scalar_isa
                self._isa_configs[isa_name] = scalar_isa
            else:
                clean_name = isa_name[:-4] if isa_name.endswith("_cpp") else isa_name
                try:
                    from tools import load_isa_config
                    self._isa_configs[isa_name] = load_isa_config(clean_name)[0]
                except Exception:
                    self._isa_configs[isa_name] = {}
        return self._isa_configs[isa_name]

    def _get_layer_dir(self, layer_name):
        internal_dir = f"{self.base_dir}/mipp/internal"
        if layer_name == "c":
            return f"{internal_dir}/interfaces/c"
        elif layer_name == "cpp":
            return f"{internal_dir}/interfaces/cpp"
        elif layer_name == "templates":
            return f"{internal_dir}/templates/cpp"
        elif layer_name.endswith("_cpp"):
            isa = layer_name[:-4]
            return f"{internal_dir}/simd_ext/{isa}/cpp"
        else:
            return f"{internal_dir}/simd_ext/{layer_name}/c"

    def get_fd(self, layer_name, func, variant=None, lmul=None):
        if self.granularity == "coarse" or func == "common" or layer_name == "templates":
            if self.mode == "function_header":
                if layer_name in self.layers:
                    layer = self.layers[layer_name]
                    target_dir = self._get_layer_dir(layer_name)
                    if func in layer.includes:
                        return layer.includes[func].get_fd(target_dir)
            elif self.mode == "category_header":
                if layer_name in self.layers:
                    layer = self.layers[layer_name]
                    category = _match_category(func)
                    target_dir = self._get_layer_dir(layer_name)

                    if category in layer.categories:
                        return layer.categories[category].get_fd(target_dir)
            return None
        elif self.granularity == "fine":
            v = normalize_variant(variant)
            l = normalize_lmul(lmul)
            return self._get_atomic_fd(layer_name, func, v, l)

    def _get_atomic_fd(self, layer_name, func, v, l):
        key = (layer_name, func, v, l)
        if key in self.atomic_files and self.atomic_files[key]["file"] is not None:
            return self.atomic_files[key]["file"]

        category = _match_category(func)
        target_dir = self._get_layer_dir(layer_name)
        ext = ".hpp" if (layer_name in ("cpp", "templates") or layer_name.endswith("_cpp")) else ".h"
        full_path = f"{target_dir}/functions/{category}/{v}/{l}/{func}{ext}"

        buf = io.StringIO()
        if key not in self.atomic_files:
            self.atomic_files[key] = {
                "file": buf,
                "full_path": full_path,
                "layer": layer_name,
                "func": func,
                "variant": v,
                "lmul": l,
                "category": category,
                "ext": ext,
                "dependencies": set(),
                "_is_prefixed": False
            }
        else:
            self.atomic_files[key]["file"] = buf

        if layer_name not in self.emitted_atomics:
            self.emitted_atomics[layer_name] = {}
        if func not in self.emitted_atomics[layer_name]:
            self.emitted_atomics[layer_name][func] = set()
        self.emitted_atomics[layer_name][func].add((v, l))

        return buf

    def resolve_all_dependencies(self, layer_name, funcs):
        target_dir = self._get_layer_dir(layer_name)
        if self.granularity == "coarse":
            if self.mode == "function_header":
                for func in self.layers[layer_name].includes:
                    if func == "common":
                        continue

                    category = _match_category(func)
                    include_path = self.layers[layer_name].includes[func]
                    include_path.resolve_dependencies(funcs, lmul=0, mask_kind="", layer=layer_name)
                    for mask in ["mask", "maskz", "masks"]:
                        include_path.resolve_dependencies(funcs, lmul=0, mask_kind=mask, layer=layer_name)

                    # Sub-ISA dependency (for ldiv wrappers) based on sub_isa in JSON
                    sub_isa = self.get_isa_config(layer_name).get("sub_isa")
                    if sub_isa:
                        include_path.dependencies.add(f"mipp/internal/simd_ext/{sub_isa}/c/functions/{category}/{func}.h")

                    # Auto-scalar fallback requires the scalar variant to be included
                    if not self.get_isa_config(layer_name).get("is_scalar", False) and layer_name not in ("c", "cpp"):
                        include_path.dependencies.add(f"mipp/internal/simd_ext/scalar/c/functions/{category}/{func}.h")
                        isa_cfg = self.get_isa_config(layer_name)
                        proto = funcs[func].get("proto", {}) if funcs and func in funcs else {}
                        has_msk_arg = (
                            (funcs[func]["mask_support"].is_any_mask() if "mask_support" in funcs[func] else False) if funcs and func in funcs else False
                            or any(arg.get("type") == "msk" for arg in proto.get("args", []))
                        )
                        ret_is_msk = (proto.get("ret", {}).get("type") == "msk")

                        needs_scalar_tomsk = (
                            func == "tomsk"
                            or (isa_cfg.get("hw_mask", False) and not isa_cfg.get("hw_mask_is_bitfield", False) and has_msk_arg)
                        )
                        needs_scalar_toreg = (
                            func == "toreg"
                            or (isa_cfg.get("hw_mask", False) and ret_is_msk and not (isa_cfg.get("hw_mask_is_bitfield", False) and func in ("toreg", "tomsk", "cast_k")))
                        )

                        if needs_scalar_tomsk:
                            include_path.dependencies.add("mipp/internal/simd_ext/scalar/c/functions/reinterpret/tomsk.h")
                        if needs_scalar_toreg:
                            include_path.dependencies.add("mipp/internal/simd_ext/scalar/c/functions/reinterpret/toreg.h")
                    include_path.write_prefix(target_dir)

            elif self.mode == "category_header":
                for category in self.layers[layer_name].categories:
                    include_category = self.layers[layer_name].categories[category]
                    include_category.resolve_dependencies(funcs, lmul=0, mask_kind="", layer=layer_name)
                    for mask in ["mask", "maskz", "masks"]:
                        include_category.resolve_dependencies(funcs, lmul=0, mask_kind=mask, layer=layer_name)
                    include_category.write_prefix(target_dir)

        elif self.granularity == "fine":
            ext = ".hpp" if (layer_name in ("cpp", "templates") or layer_name.endswith("_cpp")) else ".h"
            common_include = _get_include_path("common", layer_name)

            for key, item in list(self.atomic_files.items()):
                if key[0] != layer_name:
                    continue
                func = item["func"]
                v = item["variant"]
                l = item["lmul"]
                category = item["category"]

                item["dependencies"].add(common_include)

                if layer_name.endswith("_cpp"):
                    isa = layer_name[:-4]
                    # Corresponding C atomic header
                    item["dependencies"].add(f"mipp/internal/simd_ext/{isa}/c/functions/{category}/{v}/{l}/{func}.h")
                    # Generic template if masked or set
                    if v in ("m", "z", "s") or func in ["set0", "set0_k", "set", "set_k", "set1", "set1_k", "load", "loadu"]:
                        item["dependencies"].add(f"mipp/internal/templates/cpp/functions/{category}/{func}.hpp")
                elif layer_name not in ("c", "cpp"):
                    # C SIMD / Scalar ISA layer
                    isa_cfg = self.get_isa_config(layer_name)
                    is_scalar = bool(isa_cfg.get("is_scalar", False))
                    sw_lmuls = [int(x) for x in isa_cfg.get("sw_lmul", []) if int(x) > 0]
                    sub_isa = isa_cfg.get("sub_isa")
                    has_hw_mask = bool(isa_cfg.get("hw_mask", False))

                    # Determine if this file is a pure software LMUL wrapper or sub-ISA wrapper
                    l_val = int(l[1:]) if l.startswith("m") else 0
                    is_sw_lmul = (l_val in sw_lmuls and l_val > 1)
                    is_sub_isa_wrapper = (l == "d2" and bool(sub_isa))
                    is_horizontal = funcs[func].get("horizontal", False) if funcs and func in funcs else False
                    is_sw_wrapper = (is_sw_lmul and not is_horizontal) or is_sub_isa_wrapper

                    # Rule 1: Software LMUL hierarchy (only if this LMUL is software-emulated)
                    if 8 in sw_lmuls and l == "m8":
                        item["dependencies"].add(f"mipp/internal/simd_ext/{layer_name}/c/functions/{category}/{v}/m4/{func}{ext}")
                    if 4 in sw_lmuls and l == "m4":
                        item["dependencies"].add(f"mipp/internal/simd_ext/{layer_name}/c/functions/{category}/{v}/m2/{func}{ext}")
                    if 2 in sw_lmuls and l == "m2":
                        item["dependencies"].add(f"mipp/internal/simd_ext/{layer_name}/c/functions/{category}/{v}/m1/{func}{ext}")

                    # Sub-ISA ldiv wrapper dependency (governed by sub_isa from JSON)
                    if l == "d2" and sub_isa:
                        item["dependencies"].add(f"mipp/internal/simd_ext/{sub_isa}/c/functions/{category}/{v}/m1/{func}{ext}")

                    if not is_sw_wrapper:
                        # Rule 2: Mask dependencies (derived generically from JSON templates via candidate resolver)
                        if v in ("m", "z", "s"):
                            mkind = "mask" if v == "m" else ("maskz" if v == "z" else "masks")
                            m_deps = _get_dependencies_mask(func, funcs, mkind, layer=layer_name) if funcs else {}
                            for req in m_deps:
                                req_cat = _match_category(req)
                                item["dependencies"].add(f"mipp/internal/simd_ext/{layer_name}/c/functions/{req_cat}/u/{l}/{req}{ext}")
                        else:
                            # Regular dependencies from funcs (only for unmasked variant "u")
                            reg_deps = _get_dependencies_regular(func, funcs, layer=layer_name) if funcs else {}
                            for req in reg_deps:
                                if req != func:
                                    req_cat = _match_category(req)
                                    item["dependencies"].add(f"mipp/internal/simd_ext/{layer_name}/c/functions/{req_cat}/u/{l}/{req}{ext}")

                        # Rule 3: Auto-scalar fallback (governed by is_scalar from JSON)
                        if not is_scalar:
                            item["dependencies"].add(f"mipp/internal/simd_ext/scalar/c/functions/{category}/{v}/{l}/{func}.h")
                            super_isa = isa_cfg.get("super_isa")
                            has_super_d2 = bool(super_isa and -2 in super_isa.get("sw_lmul", []))
                            if has_super_d2:
                                item["dependencies"].add(f"mipp/internal/simd_ext/scalar/c/functions/{category}/{v}/d2/{func}.h")

                            proto = funcs[func].get("proto", {}) if funcs and func in funcs else {}
                            has_msk_arg = (
                                v in ("m", "z", "s")
                                or any(arg.get("type") == "msk" for arg in proto.get("args", []))
                            )
                            ret_is_msk = (proto.get("ret", {}).get("type") == "msk")

                            needs_scalar_tomsk = (
                                func == "tomsk"
                                or (isa_cfg.get("hw_mask", False) and not isa_cfg.get("hw_mask_is_bitfield", False) and has_msk_arg)
                            )
                            needs_scalar_toreg = (
                                func == "toreg"
                                or (isa_cfg.get("hw_mask", False) and ret_is_msk and not (isa_cfg.get("hw_mask_is_bitfield", False) and func in ("toreg", "tomsk", "cast_k")))
                            )

                            if needs_scalar_tomsk:
                                item["dependencies"].add(f"mipp/internal/simd_ext/scalar/c/functions/reinterpret/u/{l}/tomsk.h")
                                if has_super_d2:
                                    item["dependencies"].add("mipp/internal/simd_ext/scalar/c/functions/reinterpret/u/d2/tomsk.h")
                            if needs_scalar_toreg:
                                item["dependencies"].add(f"mipp/internal/simd_ext/scalar/c/functions/reinterpret/u/{l}/toreg.h")
                                if has_super_d2:
                                    item["dependencies"].add("mipp/internal/simd_ext/scalar/c/functions/reinterpret/u/d2/toreg.h")

                self._write_atomic_prefix(item)

            self.generate_umbrella_headers(layer_name)

    def _write_atomic_prefix(self, item):
        if item.get("_is_prefixed", False):
            return
        full_path = item["full_path"]
        if item["file"] is not None:
            if hasattr(item["file"], "getvalue"):
                old = item["file"].getvalue()
            else:
                item["file"].flush()
                item["file"].seek(0)
                old = item["file"].read()
            item["file"].close()
            item["file"] = None
        else:
            try:
                with open(full_path, "r", encoding="utf-8", newline="") as f:
                    old = f.read()
            except FileNotFoundError:
                old = ""

        # Separate forward declarations and body lines
        fwd_decls = []
        body_lines = []
        for line in old.split("\n"):
            stripped = line.strip()
            if (stripped.startswith("static inline ") or stripped.startswith("static ")) and stripped.endswith(";") and "{" not in stripped:
                fwd_decls.append(line)
            else:
                body_lines.append(line)

        while body_lines and body_lines[0].strip() == "":
            body_lines.pop(0)

        dep_list = sorted(list(item["dependencies"]))
        common_deps = [dep for dep in dep_list if dep.endswith("common.h") or dep.endswith("common.hpp")]
        other_deps = [dep for dep in dep_list if not (dep.endswith("common.h") or dep.endswith("common.hpp"))]

        prefix = f"#pragma once\n// MIPP atomic: {item['func']} [{item['layer']}/{item['variant']}/{item['lmul']}]\n\n"
        for dep in common_deps:
            prefix += f'#include "{dep}"\n'
        if common_deps:
            prefix += "\n"

        if fwd_decls:
            for decl in fwd_decls:
                prefix += decl + "\n"
            prefix += "\n"

        for dep in other_deps:
            prefix += f'#include "{dep}"\n'
        if other_deps:
            prefix += "\n"

        if item["layer"].endswith("_cpp"):
            prefix += "namespace mipp {\n\n"

        os.makedirs(os.path.dirname(full_path), exist_ok=True)
        with open(full_path, "w", encoding="utf-8", newline="") as f:
            f.write(prefix)
            if body_lines:
                f.write("\n".join(body_lines))
            if item["layer"].endswith("_cpp"):
                f.write("\n}\n")

        item["file"] = None
        item["_is_prefixed"] = True

    def generate_umbrella_headers(self, layer_name):
        target_dir = self._get_layer_dir(layer_name)
        ext = ".hpp" if (layer_name in ("cpp", "templates") or layer_name.endswith("_cpp")) else ".h"
        funcs_map = self.emitted_atomics.get(layer_name, {})
        common_include = _get_include_path("common", layer_name)

        if layer_name == "c":
            base_inc = "mipp/internal/interfaces/c"
        elif layer_name == "cpp":
            base_inc = "mipp/internal/interfaces/cpp"
        elif layer_name == "templates":
            base_inc = "mipp/internal/templates/cpp"
        elif layer_name.endswith("_cpp"):
            isa = layer_name[:-4]
            base_inc = f"mipp/internal/simd_ext/{isa}/cpp"
        elif layer_name != "":
            base_inc = f"mipp/internal/simd_ext/{layer_name}/c"
        else:
            base_inc = ""

        for func, vl_pairs in funcs_map.items():
            category = _match_category(func)
            emitted_variants = sorted(list(set(v for v, l in vl_pairs)))
            emitted_lmuls = sorted(list(set(l for v, l in vl_pairs)))

            # 1. Variant umbrellas: functions/<cat>/<v>/<func>
            for v in emitted_variants:
                v_path = f"{target_dir}/functions/{category}/{v}/{func}{ext}"
                os.makedirs(os.path.dirname(v_path), exist_ok=True)
                with open(v_path, "w", encoding="utf-8", newline="") as f:
                    f.write(f"#pragma once\n// MIPP variant umbrella: {func} [{v}]\n\n")
                    f.write(f'#include "{common_include}"\n\n')
                    lmuls_for_v = [l for ev, l in vl_pairs if ev == v]
                    for l in ["m1", "m2", "m4", "m8", "d2"]:
                        if l in lmuls_for_v:
                            f.write(f'#include "{base_inc}/functions/{category}/{v}/{l}/{func}{ext}"\n')

            # 2. LMUL umbrellas: functions/<cat>/<l>/<func>
            for l in emitted_lmuls:
                l_path = f"{target_dir}/functions/{category}/{l}/{func}{ext}"
                os.makedirs(os.path.dirname(l_path), exist_ok=True)
                with open(l_path, "w", encoding="utf-8", newline="") as f:
                    f.write(f"#pragma once\n// MIPP LMUL umbrella: {func} [{l}]\n\n")
                    f.write(f'#include "{common_include}"\n\n')
                    vars_for_l = [v for v, el in vl_pairs if el == l]
                    for v in ["u", "m", "z", "s"]:
                        if v in vars_for_l:
                            f.write(f'#include "{base_inc}/functions/{category}/{v}/{l}/{func}{ext}"\n')

            # 3. Top-level function umbrella: functions/<cat>/<func>
            top_path = f"{target_dir}/functions/{category}/{func}{ext}"
            os.makedirs(os.path.dirname(top_path), exist_ok=True)
            with open(top_path, "w", encoding="utf-8", newline="") as f:
                f.write(f"#pragma once\n// MIPP function umbrella: {func}\n\n")
                f.write(f'#include "{common_include}"\n\n')
                for v in ["u", "m", "z", "s"]:
                    if v in emitted_variants:
                        f.write(f'#include "{base_inc}/functions/{category}/{v}/{func}{ext}"\n')

    def close_fd(self, layer_name, func):
        if layer_name in self.layers:
            layer = self.layers[layer_name]
            if func in layer.includes:
                layer.includes[func].close_fd()

    def close_layer_fds(self, layer_name):
        if layer_name in self.layers:
            layer = self.layers[layer_name]
            for func in layer.includes:
                layer.includes[func].close_fd()
        for key, item in list(self.atomic_files.items()):
            if key[0] == layer_name:
                if item["file"] is not None:
                    if hasattr(item["file"], "getvalue"):
                        content = item["file"].getvalue()
                        if content and not item.get("_is_prefixed", False):
                            os.makedirs(os.path.dirname(item["full_path"]), exist_ok=True)
                            with open(item["full_path"], "w", encoding="utf-8", newline="") as f:
                                f.write(content)
                    item["file"].close()
                    item["file"] = None

    def get_layer(self, layer_name):
        if layer_name in self.layers:
            return self.layers[layer_name]
        return None


    def create_glue_file(self, layer_name, file_path):
        target_dir = self._get_layer_dir(layer_name)
        target_path = f"{target_dir}/{os.path.basename(file_path)}"
        os.makedirs(target_dir, exist_ok=True)

        if self.mode == "function_header":
            if layer_name in self.layers:
                layer = self.layers[layer_name]
                with open(target_path, "w", encoding="utf-8", newline="") as f:
                    f.write("#pragma once\n")
                    for func in layer.includes:
                        include_path = layer.includes[func]
                        if func != "common":
                            category = _match_category(func)
                            f.write(f'#include "functions/{category}/{include_path.name}"\n')
                        else :
                            f.write(f'#include "{include_path.name}"\n')
        elif self.mode == "category_header":
            if layer_name in self.layers:
                layer = self.layers[layer_name]
                with open(target_path, "w", encoding="utf-8", newline="") as f:
                    f.write("#pragma once\n")
                    for category in layer.categories:
                        include_category = layer.categories[category]
                        if category != "common":
                            f.write(f'#include "functions/{include_category.name}"\n')
                        else :
                            f.write(f'#include "{include_category.name}"\n')
    
    def write_custom_prefix(self, layer_name, func, custom_prefix):
        target_dir = self._get_layer_dir(layer_name)
        if self.mode == "function_header":
            if layer_name in self.layers:
                layer = self.layers[layer_name]
                if func in layer.includes:
                    layer.includes[func].write_custom_prefix(custom_prefix, target_dir, mode=self.mode)
        elif self.mode == "category_header":
            if layer_name in self.layers:
                layer = self.layers[layer_name]
                category = func
                if category in layer.categories:
                    layer.categories[category].write_custom_prefix(custom_prefix, target_dir)
                    layer.categories[category].write_custom_prefix(custom_prefix, f"{target_dir}/functions")

def generate_mipp_h(include_manager=None):
    from jinja2 import Template, StrictUndefined
    from registry import interfaces

    file = open("../include/mipp.h", "w")

    template_file = """#ifndef MY_INTRINSICS_PLUS_PLUS_H_
#define MY_INTRINSICS_PLUS_PLUS_H_
#include "mipp/internal/simd_ext/scalar/c/common.h"
#include "mipp/internal/interfaces/c/common.h"
"""

    include_list = ""
    for func in interfaces:
        category = _match_category(func)
        include_list += f'#include "mipp/internal/interfaces/c/functions/{category}/{func}.h"\n'
    postfix = """#endif /* MY_INTRINSICS_PLUS_PLUS_H_ */"""

    template_file += include_list + "\n" + postfix

    j2_template = Template(template_file, undefined=StrictUndefined)
    print(j2_template.render(), file=file)
    file.close()
