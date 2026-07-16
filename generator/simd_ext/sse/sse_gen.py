#!/usr/bin/env python3
import sys
sys.path.insert(1, '.')

from tools import load_isa_config
from c_generator import generate_c_layer

sse_isa, sse_native_implems, sse_emu_implems = load_isa_config("sse")

def sse_gen(include_manager):
    generate_c_layer(sse_isa, include_manager, sse_native_implems, sse_emu_implems)
