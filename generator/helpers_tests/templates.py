GENERIC_FOR_LOOP = """{{func_decl}}
for(unsigned n = 0; n < N_ITER; n++){
{{decl}}
{{init}}

{{load}}
{{operation}}
\tfor(unsigned i = 0; i < {{size}}; i++)
\t{
{{loop_body}}
{{loop_assert}}
\t}
}
}\n
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