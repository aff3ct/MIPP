from tools import *
import json
import os

_current_dir = os.path.dirname(os.path.abspath(__file__))
with open(os.path.join(_current_dir, "isa_neon.json"), "r") as f:
    isa_neon = json.load(f)

tpl_implem_neon, implems_neon = load_implem_tables(__file__, "templates_neon.json", "implems_neon.json")
