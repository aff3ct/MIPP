GENERIC_FOR_LOOP = """{{func_decl}}
{{decl}}
{{init}}

{{load}}
{{operation}}

\tfor(int i = 0; i < vectorSize; i++)
\t{
\t{{loop_body}}
\t{{loop_assert}}
\t}
}
"""

GENERIC_NO_LOOP = """{{func_decl}}
{{decl}}
{{init}}
{{load}}
{{operation}}

{{loop_body}}
{{loop_assert}}
}
"""