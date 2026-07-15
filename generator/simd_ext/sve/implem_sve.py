from tools import *
import json
import os

_current_dir = os.path.dirname(os.path.abspath(__file__))
with open(os.path.join(_current_dir, "isa_sve.json"), "r") as f:
    isa_sve = json.load(f)
if "size" in isa_sve:
    isa_sve["size"] = set(isa_sve["size"])

tpl_implem_sve, implems_sve = load_implem_tables(__file__, "templates_sve.json", "implems_sve.json")
