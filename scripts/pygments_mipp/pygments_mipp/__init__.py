"""Pygments lexers for the MIPP templating DSL.

Two lexers are registered through the ``pygments.lexers`` entry point, so that
MkDocs (pymdownx.highlight) can use them as fenced code languages:

- ``mipp-dsl``: C code containing DSL placeholders (``%r<tp>%``,
  ``%add<tp|v:Z>%(...)``, ``%!pred_cond!%``) and Jinja2 delimiters.
- ``mipp-json``: JSON registries whose string values contain DSL placeholders
  and Jinja2 delimiters (``*_templates.json``, ``registry_scalar_implems.json``).

The DSL itself is described in docs/developer/reference/templating_dsl.md.
"""

from pygments.lexer import RegexLexer, bygroups, include, inherit
from pygments.lexers.c_cpp import CLexer
from pygments.lexers.data import JsonLexer
from pygments.token import (Comment, Keyword, Name, Number, Operator,
                            Punctuation, String, Text)

__all__ = ["MippDslLexer", "MippJsonLexer"]

# Token prefixes that name a type or a constant instead of a MIPP function.
_TYPE_PREFIXES = r"(?:r|m|s|N)"
_IDENT = r"[A-Za-z_][A-Za-z0-9_]*"

# The '%' that open and close a DSL placeholder use the same token (and colour) as the Jinja2
# delimiters, to make the templating zones easy to spot.
# Rules shared by both lexers.
_JINJA = [
    (r"\{\{.*?\}\}", Comment.Preproc),
    (r"\{%.*?%\}", Comment.Preproc),
    (r"\{#.*?#\}", Comment),
]

_DSL = [
    # Predication markers of the scalar reference: %!pred_cond!%, %!pred_alt!%
    (r"(%)(!" + _IDENT + r"!)(%)",
     bygroups(Comment.Preproc, Name.Decorator, Comment.Preproc)),
    # Type and constant placeholders: %r<...>%, %m<...>%, %s<...>%, %N<...>%
    (r"(%)(" + _TYPE_PREFIXES + r")(<)",
     bygroups(Comment.Preproc, Keyword.Type, Punctuation), "mipp-mods"),
    # Function calls: %add<...>%, %{{func_name}}<...>%
    (r"(%)(" + _IDENT + r")(<)",
     bygroups(Comment.Preproc, Name.Function, Punctuation), "mipp-mods"),
    (r"(%)(\{\{.*?\}\})(<)",
     bygroups(Comment.Preproc, Comment.Preproc, Punctuation), "mipp-mods"),
]

_MODS = [
    (r"(>)(%)", bygroups(Punctuation, Comment.Preproc), "#pop"),
    (r"\{\{.*?\}\}", Comment.Preproc),
    (r"(c|b|m|v)(:)", bygroups(Name.Attribute, Punctuation)),
    (r"\b(tp|tr)\b", Name.Builtin),
    (r"\b(int|uint|float|M|Z|S|U)\b", Name.Constant),
    (r"-?\d+", Number.Integer),
    (r"[*/]", Operator),
    (r"[|,]", Punctuation),
    (r"\s+", Text),
    (r".", Text),
]


class MippDslLexer(CLexer):
    """C code with MIPP DSL placeholders and Jinja2 delimiters."""

    name = "MIPP DSL"
    aliases = ["mipp-dsl"]
    filenames = []
    mimetypes = []

    tokens = {
        "mipp": _DSL + _JINJA,
        "mipp-mods": _MODS,
        "root": [include("mipp"), inherit],
        "statement": [include("mipp"), inherit],
        "statements": [include("mipp"), inherit],
    }


class _MippStringLexer(RegexLexer):
    """Content of a JSON string: DSL and Jinja2 tokens, the rest is string."""

    name = "MIPP DSL string"
    aliases = []

    tokens = {
        "root": _DSL + _JINJA + [
            (r'\\.', String.Escape),
            (r'[^%{\\]+', String.Double),
            (r'.', String.Double),
        ],
        "mipp-mods": _MODS,
    }


class MippJsonLexer(JsonLexer):
    """JSON whose string values contain MIPP DSL placeholders."""

    name = "MIPP JSON"
    aliases = ["mipp-json"]
    filenames = []
    mimetypes = []

    def get_tokens_unprocessed(self, text):
        sub = _MippStringLexer()
        for index, token, value in super().get_tokens_unprocessed(text):
            if token is String.Double and len(value) >= 2:
                yield index, token, value[0]
                for i, t, v in sub.get_tokens_unprocessed(value[1:-1]):
                    yield index + 1 + i, t, v
                yield index + len(value) - 1, token, value[-1]
            else:
                yield index, token, value
