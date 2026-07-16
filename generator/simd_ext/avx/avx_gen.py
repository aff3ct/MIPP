#!/usr/bin/env python3
import sys
sys.path.insert(1, '.')

from tools import load_isa_config
from c_generator import generate_c_layer

avx_isa, avx_native_implems, avx_emu_implems = load_isa_config("avx")

def avx_gen(include_manager):
    generate_c_layer(avx_isa, include_manager, avx_native_implems, avx_emu_implems)
