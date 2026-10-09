#!/bin/sh
# A plain MCS251 compile and link must not print anything: no preprocessor
# warnings about predefined macros, no code generator debug output and no
# linker option echo.
set -eu

if test "$#" -ne 4; then
    echo "usage: $0 SDCC DEVICE_INCLUDE LIBRARY_DIR SOURCE" >&2
    exit 2
fi

sdcc=$1
device_include=$2
library_dir=$3
source=$4
test_dir=${TMPDIR:-/tmp}/sdcc-mcs251-quiet.$$
trap 'rm -rf "$test_dir"' 0 HUP INT TERM
mkdir -p "$test_dir"

# --nostdlib with explicit libraries: an installed copy of the libraries
# must not be picked up next to LIBRARY_DIR.
output=$("$sdcc" -mmcs251 --model-large -I"$device_include" -I"$device_include/mcs51" \
    --code-loc 0xff0000 --nostdlib -L"$library_dir" -lmcs251 -llibsdcc \
    -o "$test_dir/quiet.ihx" "$source" 2>&1)
test -s "$test_dir/quiet.ihx"
if test -n "$output"; then
    echo "MCS251 compile and link printed output:" >&2
    echo "$output" >&2
    exit 1
fi
echo "PASS: MCS251 compile and link are quiet"
