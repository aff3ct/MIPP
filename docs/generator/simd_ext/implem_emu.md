`implem_emu_isa.py` is similar to `implem_isa.py`. It defines two dictionnaries, `tpl_implem_emu_isa` which defines templates that are 
used to create the bodies of MIPP function for a specific ISA and `implems_emu_isa`. 

`implems_emu_isa` which is a dictionnary where the keys are MIPP functions and the values are a list of dictionnaries. Each dictionnary contains 
a list of datatypes and a template in `tpl_implem_emu_isa`.