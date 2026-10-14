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
        -h|--help)    sed -n '2,22p' "$0" | sed 's/^# \{0,1\}//'; exit 0 ;;
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

# --- 1. Lint: no inline C / C++ block in the user guide ----------------------
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

if $DO_BUILD; then
    lint_out="$(lint_pages)"
    if [ -n "$lint_out" ]; then
        echo "$lint_out" >&2
        fail "inline code blocks in docs/user/"
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
