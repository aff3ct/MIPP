from tools import *
import json
import os

_current_dir = os.path.dirname(os.path.abspath(__file__))
with open(os.path.join(_current_dir, "isa_sse.json"), "r") as f:
    isa_sse = json.load(f)

tpl_implem_sse, implems_sse = load_implem_tables(__file__, "templates_sse.json", "implems_sse.json")
