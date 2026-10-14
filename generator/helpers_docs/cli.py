"""
Command-line reference of the MIPP generators.

The generators build their parser in a `build_arg_parser()` function, with
`MippHelpFormatter` and `set_examples()`. `render_cli_page()` turns these parsers
into the Markdown page `docs/developer/reference/cli.md`, so that `--help` and the
documentation always agree.

Conventions for the help strings (they are shown both in a terminal and in Markdown):
- literal values, paths and file names are written between single quotes:
  'all', '../include/'; they become code spans in Markdown;
- defaults are not written in the help strings: the formatter appends them in the
  terminal, and the Markdown page has a "Default" column;
- option names (--no-clean) also become code spans in Markdown;
- paragraphs of a description are separated by a blank line; a paragraph whose
  lines all start with "- " is a bullet list (one item per line).
"""
import argparse
import contextlib
import copy
import os
import re
import textwrap

# 'value' -> `value` (not for apostrophes: "don't", "ISA's"), --option -> `--option`
_RE_LITERAL = re.compile(r"(?<![A-Za-z0-9])'(?P<quoted>[^'\n]+?)'(?![A-Za-z0-9])"
                         r"|(?<![\w`-])(?P<option>--?[a-z][a-z0-9-]*)(?![\w-])")


def _is_list(para):
    return all(line.lstrip().startswith("- ") for line in para.strip().splitlines())


def _plain_default(default):
    if isinstance(default, (list, tuple)):
        return " ".join(str(d) for d in default)
    return str(default)


class MippHelpFormatter(argparse.HelpFormatter):
    """Wraps each paragraph separately, keeps indented blocks (examples) verbatim,
    and appends the default value of the options that have a meaningful one."""

    def _fill_text(self, text, width, indent):
        paragraphs = []
        for para in text.strip("\n").split("\n\n"):
            if _is_list(para):
                paragraphs.append("\n".join(
                    textwrap.fill(" ".join(line.split()), width, initial_indent=indent,
                                  subsequent_indent=indent + "  ")
                    for line in para.strip().splitlines()))
            elif para.startswith("  ") or "\n  " in para:
                paragraphs.append("\n".join(indent + line for line in para.splitlines()))
            else:
                paragraphs.append(textwrap.fill(" ".join(para.split()), width,
                                                initial_indent=indent, subsequent_indent=indent))
        return "\n\n".join(paragraphs)

    def _get_help_string(self, action):
        text = action.help or ""
        default = action.default
        if default is None or default is False or default is argparse.SUPPRESS or "%(default)" in text:
            return text
        if not action.option_strings and action.nargs not in ("?", "*"):
            return text
        return f"{text} (default: {_plain_default(default)})"


def set_examples(parser, examples):
    """Attaches usage examples to a parser: a list of (command, comment) pairs.
    They are printed at the end of --help and rendered in the CLI reference."""
    parser.mipp_examples = list(examples)
    width = max(len(cmd) for cmd, _ in examples)
    lines = [f"  {cmd:<{width}}  # {comment}" if comment else f"  {cmd}" for cmd, comment in examples]
    parser.epilog = "examples:\n\n" + "\n".join(lines)


# ---------------------------------------------------------------------------
# Markdown rendering
# ---------------------------------------------------------------------------

def _md_text(text, in_table=False):
    """Plain help text -> Markdown: quoted literals become code spans, the rest is escaped."""
    out = []
    pos = 0
    for m in _RE_LITERAL.finditer(text):
        out.append(_md_escape(text[pos:m.start()], in_table))
        out.append(f"`{m.group('quoted') or m.group('option')}`")
        pos = m.end()
    out.append(_md_escape(text[pos:], in_table))
    return "".join(out)


def _md_escape(text, in_table):
    text = text.replace("&", "&amp;").replace("<", "&lt;").replace(">", "&gt;").replace("*", "\\*")
    if in_table:
        text = text.replace("|", "\\|")
    return text


def _md_paragraphs(text):
    blocks = []
    for p in text.strip().split("\n\n"):
        if _is_list(p):
            blocks.append("\n".join("- " + _md_text(" ".join(line.split()[1:]))
                                    for line in p.strip().splitlines()))
        else:
            blocks.append(_md_text(" ".join(p.split())))
    return "\n\n".join(blocks)


def _invocation(action, formatter):
    if action.choices is not None and action.metavar is None:
        # the choices are listed in the description: show a placeholder instead of {a,b,c}
        action = copy.copy(action)
        action.metavar = action.dest.upper()
    if not action.option_strings:
        return f"`{formatter._format_args(action, action.dest)}`"
    names = [f"`{s}`" for s in action.option_strings]
    if action.nargs != 0:
        args = formatter._format_args(action, formatter._get_default_metavar_for_optional(action))
        names[-1] = f"`{action.option_strings[-1]} {args}`"
    return ", ".join(names)


def _md_default(action):
    if isinstance(action, argparse._StoreTrueAction):
        return "off"
    if action.default is None or action.default is argparse.SUPPRESS:
        return "—"
    return f"`{_plain_default(action.default)}`"


def _md_description(action):
    parts = [_md_text(" ".join((action.help or "").split()), in_table=True)]
    if action.choices is not None:
        parts.append("Choices: " + ", ".join(f"`{c}`" for c in action.choices) + ".")
    return " ".join(p for p in parts if p)


def _md_table(header, actions, formatter):
    lines = [f"| {header} | Default | Description |", "| :--- | :--- | :--- |"]
    for a in actions:
        lines.append(f"| {_invocation(a, formatter)} | {_md_default(a)} | {_md_description(a)} |")
    return "\n".join(lines)


@contextlib.contextmanager
def _stable_terminal(columns=88):
    """Deterministic help output: fixed width, no colors."""
    saved = {k: os.environ.get(k) for k in ("COLUMNS", "NO_COLOR", "FORCE_COLOR", "PYTHON_COLORS")}
    os.environ["COLUMNS"] = str(columns)
    os.environ["NO_COLOR"] = "1"
    os.environ["PYTHON_COLORS"] = "0"
    os.environ.pop("FORCE_COLOR", None)
    try:
        yield
    finally:
        for k, v in saved.items():
            if v is None:
                os.environ.pop(k, None)
            else:
                os.environ[k] = v


def _render_script(script, parser, anchor, see_also):
    with _stable_terminal():
        formatter = parser._get_formatter()
        usage = parser.format_usage().strip()

    positionals = [a for a in parser._actions if not a.option_strings]
    optionals = [a for a in parser._actions
                 if a.option_strings and not isinstance(a, argparse._HelpAction)]

    md = [f"## `{script}` {{ #{anchor} }}", ""]
    if parser.description:
        md += [_md_paragraphs(parser.description), ""]
    md += ["```text", usage, "```", ""]
    if positionals:
        md += ["### Arguments", "", _md_table("Argument", positionals, formatter), ""]
    if optionals:
        md += ["### Options", "", _md_table("Option", optionals, formatter), ""]
    examples = getattr(parser, "mipp_examples", [])
    if examples:
        width = max(len(cmd) for cmd, _ in examples)
        md += ["### Examples", "", "```bash"]
        md += [f"{cmd:<{width}}  # {comment}" if comment else cmd for cmd, comment in examples]
        md += ["```", ""]
    if see_also:
        md += ["See also: " + ", ".join(f"[{label}]({link})" for label, link in see_also) + ".", ""]
    return "\n".join(md)


def render_cli_page(entries):
    """entries: list of dicts with keys 'script', 'parser', 'anchor' and optionally 'see_also'
    (list of (label, relative link) pairs). Returns the Markdown page."""
    md = [
        "# Command-Line Reference",
        "",
        '!!! info "Generated page"',
        "    This page is generated by `gen_mipp_docs.py` from the argparse parsers of the generators "
        "(`build_arg_parser()`): `--help` prints the same information. To change it, edit the help "
        "strings in the scripts, not this page.",
        "",
        "All the generators run from `generator/`, in the virtual environment of the generator "
        "(see [Setup](../setup.md)). They take their inputs in `generator/` and write their outputs "
        "next to it, in the repository.",
        "",
        "| Script | Role |",
        "| :--- | :--- |",
    ]
    for e in entries:
        summary = (e["parser"].description or "").strip().split("\n\n")[0]
        md.append(f"| [`{e['script']}`](#{e['anchor']}) | {_md_text(' '.join(summary.split()), in_table=True)} |")
    md.append("")
    for e in entries:
        md += ["---", "", _render_script(e["script"], e["parser"], e["anchor"], e.get("see_also", []))]
    return "\n".join(md).rstrip() + "\n"
