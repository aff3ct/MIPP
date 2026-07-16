#!/usr/bin/env python3
import sys
sys.path.insert(1, '.')

from tools import load_isa_config
from c_generator import generate_c_layer

rvv_isa, rvv_native_implems, rvv_emu_implems = load_isa_config("rvv")

def rvv_gen(include_manager):
    generate_c_layer(rvv_isa, include_manager, rvv_native_implems, rvv_emu_implems)