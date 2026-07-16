#!/usr/bin/env python3
import sys
sys.path.insert(1, '.')

from tools import load_isa_config
from c_generator import generate_c_layer

neon_isa, neon_native_implems, neon_emu_implems = load_isa_config("neon")

def neon_gen(include_manager):
    generate_c_layer(neon_isa, include_manager, neon_native_implems, neon_emu_implems)