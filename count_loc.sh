#!/usr/bin/env bash
set -euo pipefail

count_loc() {
  local label="$1"
  shift

  local total=0
  local file_count=0
  local file

  while IFS= read -r -d '' file; do
    total=$((total + $(wc -l < "$file")))
    file_count=$((file_count + 1))
  done < <(
    find "$@" -type f \( \
      -name '*.h' -o -name '*.hpp' -o -name '*.c' -o -name '*.cpp' \
    \) -print0
  )

  printf "%s: %d files, %d lines\n" "$label" "$file_count" "$total" >&2
  printf '%s\n' "$total"
}

count_py_loc() {
  local label="$1"
  shift

  local total=0
  local file_count=0
  local file

  while IFS= read -r -d '' file; do
    total=$((total + $(wc -l < "$file")))
    file_count=$((file_count + 1))
  done < <(
    find "$@" -type f -name '*.py' -print0
  )

  printf "%s: %d files, %d lines\n" "$label" "$file_count" "$total" >&2
  printf '%s\n' "$total"
}

cpp_total=$(count_loc "C/C++" include tests/src)
py_total=$(count_py_loc "Python" generator)

sum=$((cpp_total + py_total))

printf "CPP loc : %d\n" "$cpp_total"
printf "PY loc   : %d\n" "$py_total"
printf "Total LoC: %d\n" "$sum"

if [ "$py_total" -gt 0 ]; then
  ratio=$(awk -v c="$cpp_total" -v p="$py_total" 'BEGIN { printf "%.3f", c / p }')
else
  ratio="inf"
fi

printf "CPP/PY ratio: %s\n" "$ratio"