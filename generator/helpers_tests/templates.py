GENERIC_FOR_LOOP = """{{func_decl}}
for(unsigned n = 0; n < N_ITER; n++){
{{decl}}
{{init}}

{{load}}
{{operation}}
for(int i = 0; i < vectorSize; i++)
{
{{loop_body}}
{{loop_assert}}
}
}
}
"""

GENERIC_NO_LOOP = """{{func_decl}}

for(unsigned n = 0; n < N_ITER; n++){
{{decl}}
{{init}}
{{load}}
{{operation}}

{{loop_body}}
{{loop_assert}}
}
}
"""