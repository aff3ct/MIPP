#!/usr/bin/env bash
# Compiles and runs the code snippets of the documentation.
#
#   - examples/doc/**/*.{c,cpp}: complete programs whose named sections are
#     included in the pages by pymdownx.snippets (--8<-- "file:section").
#     Each program checks its results (DOC_CHECK) and returns a non-zero exit
#     code on failure.
#   - README.md: the C++ example is extracted, compiled and run.
#   - docs/user/*.md: every C / C++ code block must come from examples/doc/
#     (a --8<-- line) or be marked as not compiled with the HTML comment
#     <!-- not-compiled: reason --> on the line before the opening fence.
#     Content tabs use the labels "C API", "C++ Functional API" and
#     "C++ Object API" (same as the generated funcs_support/ pages, so that
#     content.tabs.link keeps them in sync), and include c.c, fun.cpp and
#     obj.cpp files respectively. The tabs of a set do the same thing: the
#     named sections included at the top level of each tab have the same
#     number of non-blank lines. The included code does not use 'auto' (the
#     type is written), except in the sections listed in AUTO_ALLOWED.
#
# Usage: scripts/check_doc_snippets.sh [--build-only | --run-only] [--out DIR]
#
# Environment:
#   CC, CXX     compilers, possibly with options (default: cc, c++)
#   SIMD_EXT    target flags (e.g. "-mavx2 -mfma"; default: none)
#   SKIP_C      "true" to skip the C programs (the C API does not compile on RVV yet)
#   INCLUDE_DIR generated headers (default: include/ at the root of the repository)

set -u

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
CC="${CC:-cc}"
CXX="${CXX:-c++}"
SIMD_EXT="${SIMD_EXT:-}"
SKIP_C="${SKIP_C:-false}"
INCLUDE_DIR="${INCLUDE_DIR:-$ROOT/include}"
OUT="$ROOT/examples/doc/bin"
DO_BUILD=true
DO_RUN=true

while [ $# -gt 0 ]; do
    case "$1" in
        --build-only) DO_RUN=false ;;
        --run-only)   DO_BUILD=false ;;
        --out)        shift; OUT="$1" ;;
        -h|--help)    sed -n '2,26p' "$0" | sed 's/^# \{0,1\}//'; exit 0 ;;
        *)            echo "Unknown option: $1" >&2; exit 2 ;;
    esac
    shift
done

WARN_FLAGS="-Wall -Wextra -Wpedantic -Werror -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable"
C_FLAGS="-std=c99 $WARN_FLAGS -Wno-strict-prototypes -O2"
CXX_FLAGS="-std=c++11 $WARN_FLAGS -O2"

errors=0
fail() { echo "FAIL: $*" >&2; errors=$((errors + 1)); }

# Binary name of a source file: examples/doc/<page>/<file>.<ext> -> <page>__<file>
bin_name() {
    local rel="${1#$ROOT/examples/doc/}"
    rel="${rel%.*}"
    echo "${rel//\//__}"
}

# --- 1. Lint: no inline C / C++ block in the user guide, canonical tabs --------
lint_pages() {
    local page
    for page in "$ROOT"/docs/user/*.md; do
        awk -v page="${page#$ROOT/}" '
            function flush() {
                if (in_block && !has_snippet && !marked)
                    printf "%s:%d: inline C/C++ block (include it from examples/doc/ or mark it <!-- not-compiled: reason -->)\n", page, start
            }
            {
                line = $0
                # Content tabs: canonical labels, matching included files
                if (line ~ /^[ \t]*=== "/) {
                    tab = line; sub(/^[ \t]*=== "/, "", tab); sub(/".*$/, "", tab)
                    tab_indent = match(line, /[^ \t]/) - 1
                    if (tab == "C API") want = "/c[a-z_]*\\.c[:\"]"
                    else if (tab == "C++ Functional API") want = "/fun\\.cpp[:\"]"
                    else if (tab == "C++ Object API") want = "/obj\\.cpp[:\"]"
                    else {
                        printf "%s:%d: tab label \"%s\" (use \"C API\", \"C++ Functional API\" or \"C++ Object API\")\n", page, NR, tab
                        want = ""
                    }
                    next
                }
                if (tab != "" && line !~ /^[ \t]*$/ && match(line, /[^ \t]/) - 1 <= tab_indent) tab = ""
                if (tab != "" && want != "" && line ~ /--8<-- "/ && line !~ want)
                    printf "%s:%d: tab \"%s\" includes another API: %s\n", page, NR, tab, line
                if (!in_block && line ~ /^[ \t]*```(c|cpp)[ \t]*$/) {
                    in_block = 1; start = NR; has_snippet = 0
                    marked = (prev ~ /<!-- not-compiled:/)
                    next
                }
                if (in_block && line ~ /^[ \t]*```[ \t]*$/) { flush(); in_block = 0; next }
                if (in_block && line ~ /--8<--/) has_snippet = 1
                if (line !~ /^[ \t]*$/) prev = line
            }
        ' "$page"
    done
}

# --- 1b. Lint: equivalent tabs, no 'auto' ---------------------------------------
# Sections that present the deduction of types with 'auto'
AUTO_ALLOWED="examples/doc/programming_model/fun.cpp:auto_deduction examples/doc/programming_model/fun.cpp:explicit_params"

# Non-blank lines of a named section (whole file without section), without the
# section markers
section_lines() {
    awk -v s="$2" '
        s != "" && index($0, "[start:" s "]") { f = 1; next }
        s != "" && index($0, "[end:" s "]") { f = 0 }
        (f || s == "") && $0 !~ /--8<-- \[/ && $0 !~ /^[ \t]*$/ { print }
    ' "$1"
}

lint_snippets() {
    local page set tab main line inc file sec body
    for page in "$ROOT"/docs/user/*.md; do
        # One record per inclusion: tab set (0 outside tabs), tab, top-level code
        # of the tab (not in an admonition of the tab), line, file[:section]
        awk '
            /^[ \t]*=== "/ {
                ind = match($0, /[^ \t]/) - 1
                if (!open || ind != tab_indent) set_id++
                open = 1; tab_indent = ind; tab_no++; next
            }
            open && $0 !~ /^[ \t]*$/ && match($0, /[^ \t]/) - 1 <= tab_indent { open = 0 }
            /--8<-- "/ {
                inc = $0; sub(/^.*--8<-- "/, "", inc); sub(/".*$/, "", inc)
                if (open) print set_id "\t" tab_no "\t" (match($0, /[^ \t]/) - 1 == tab_indent + 4) "\t" NR "\t" inc
                else print "0\t0\t0\t" NR "\t" inc
            }
        ' "$page" | while IFS=$'\t' read -r set tab main line inc; do
            file="${inc%%:*}"; sec="${inc#"$file"}"; sec="${sec#:}"
            case "$file" in examples/doc/*) ;; *) continue ;; esac # generated tables
            [ -f "$ROOT/$file" ] || continue # reported by mkdocs (check_paths)
            body="$(section_lines "$ROOT/$file" "$sec")"
            if printf '%s\n' "$body" | grep -qw auto; then
                case " $AUTO_ALLOWED " in
                    *" $inc "*) ;;
                    *) echo "${page#$ROOT/}:$line: 'auto' in $inc (write the type)" ;;
                esac
            fi
            # Lengths compared for named sections only: complete programs differ in
            # their boilerplate (headers, allocation, output) from one language to another
            if [ "$set" -gt 0 ] && [ "$main" = 1 ] && [ -n "$sec" ]; then
                printf '%s\t%s\t%s\t%s\t%s\n' "$set" "$tab" "$line" "$inc" "$(printf '%s\n' "$body" | grep -c .)"
            fi
        done | awk -F'\t' -v page="${page#$ROOT/}" '
            # Number of lines per tab (sum of its inclusions), compared within a tab set
            function report(   i, diff) {
                for (i = 2; i <= n; i++) if (cnt[tabs[i]] != cnt[tabs[1]]) diff = 1
                if (diff) printf "%s:%d: the tabs do not have the same number of lines: %s\n", page, first_line, desc
            }
            NF == 5 {
                if ($1 != cur) { report(); cur = $1; n = 0; desc = ""; first_line = $3; split("", cnt) }
                if (!($2 in cnt)) tabs[++n] = $2
                cnt[$2] += $5; desc = desc (desc == "" ? "" : ", ") $4 " = " $5
                next
            }
            { print }
            END { report() }
        '
    done
}

if $DO_BUILD; then
    lint_out="$(lint_pages; lint_snippets)"
    if [ -n "$lint_out" ]; then
        echo "$lint_out" >&2
        fail "lint of docs/user/"
    fi
fi

# --- 2. Build -------------------------------------------------------------------
mkdir -p "$OUT"

sources() {
    find "$ROOT/examples/doc" -path "$OUT" -prune -o -type f \( -name '*.c' -o -name '*.cpp' \) -print | sort
}

build_one() {
    local src="$1" bin="$2" std_override flags
    std_override="$(sed -n 's|^// doc-std: *\([a-z0-9+]*\).*|\1|p' "$src" | head -n 1)"
    case "$src" in
        *.c)
            flags="$C_FLAGS"
            [ -n "$std_override" ] && flags="$flags -std=$std_override"
            # shellcheck disable=SC2086
            $CC $flags $SIMD_EXT -I"$INCLUDE_DIR" -I"$ROOT/examples/doc" "$src" -o "$bin" -lm
            ;;
        *)
            flags="$CXX_FLAGS"
            [ -n "$std_override" ] && flags="$flags -std=$std_override"
            # shellcheck disable=SC2086
            $CXX $flags $SIMD_EXT -I"$INCLUDE_DIR" -I"$ROOT/examples/doc" "$src" -o "$bin"
            ;;
    esac
}

if $DO_BUILD; then
    for src in $(sources); do
        case "$src" in *.c) [ "$SKIP_C" = "true" ] && { echo "skip  ${src#$ROOT/}"; continue; } ;; esac
        echo "build ${src#$ROOT/}"
        build_one "$src" "$OUT/$(bin_name "$src")" || fail "build ${src#$ROOT/}"
    done

    # README.md: first ```cpp block
    awk '/^```cpp[ \t]*$/ { inb = 1; next } inb && /^```/ { exit } inb { print }' "$ROOT/README.md" > "$OUT/readme.cpp"
    if [ -s "$OUT/readme.cpp" ]; then
        echo "build README.md"
        build_one "$OUT/readme.cpp" "$OUT/readme" || fail "build README.md"
    else
        fail "no C++ block found in README.md"
    fi
fi

# --- 3. Run ---------------------------------------------------------------------
if $DO_RUN; then
    for bin in $(find "$OUT" -type f -perm -u+x ! -name '*.*' | sort); do
        echo "run   ${bin#$ROOT/}"
        "$bin" > "$bin.log" 2>&1 || { cat "$bin.log" >&2; fail "run ${bin#$ROOT/}"; }
    done
fi

if [ "$errors" -ne 0 ]; then
    echo "$errors error(s)" >&2
    exit 1
fi
echo "OK"
