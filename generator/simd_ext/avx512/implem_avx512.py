from tools import *
import json
import os

_current_dir = os.path.dirname(os.path.abspath(__file__))
with open(os.path.join(_current_dir, "isa_avx512.json"), "r") as f:
    isa_avx512 = json.load(f)

tpl_implem_avx512, implems_avx512 = load_implem_tables(__file__, "templates_avx512.json", "implems_avx512.json")
