#!/usr/bin/env python3
import sys
sys.path.insert(1, '.')

from tools import load_isa_config
from c_generator import generate_c_layer

sve_isa, sve_native_implems, sve_emu_implems = load_isa_config("sve")

def sve_gen(include_manager):
    generate_c_layer(sve_isa, include_manager, sve_native_implems, sve_emu_implems)
