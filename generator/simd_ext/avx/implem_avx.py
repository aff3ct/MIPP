from tools import *
import json
import os

_current_dir = os.path.dirname(os.path.abspath(__file__))
with open(os.path.join(_current_dir, "isa_avx.json"), "r") as f:
    isa_avx = json.load(f)

tpl_implem_avx, implems_avx = load_implem_tables(__file__, "templates_avx.json", "implems_avx.json")
