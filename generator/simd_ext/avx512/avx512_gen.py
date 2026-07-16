#!/usr/bin/env python3
import sys
sys.path.insert(1, '.')

from tools import load_isa_config
from c_generator import generate_c_layer

avx512_isa, avx512_native_implems, avx512_emu_implems = load_isa_config("avx512")

def avx512_gen(include_manager):
    generate_c_layer(avx512_isa, include_manager, avx512_native_implems, avx512_emu_implems)
