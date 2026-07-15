from tools import *
import json
import os

_current_dir = os.path.dirname(os.path.abspath(__file__))
with open(os.path.join(_current_dir, "isa_rvv.json"), "r") as f:
    isa_rvv = json.load(f)

tpl_implem_rvv, implems_rvv = load_implem_tables(__file__, "templates_rvv.json", "implems_rvv.json")