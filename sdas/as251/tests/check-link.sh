#!/bin/sh

set -eu

if test "$#" -ne 2; then
    echo "usage: $0 /path/to/sdas251 /path/to/sdld" >&2
    exit 2
fi

absolute_program()
{
    case $1 in
        /*) printf '%s\n' "$1" ;;
        *)
            program_dir=$(CDPATH= cd -- "$(dirname -- "$1")" && pwd)
            printf '%s/%s\n' "$program_dir" "$(basename -- "$1")"
            ;;
    esac
}

assembler=$(absolute_program "$1")
linker=$(absolute_program "$2")
test_dir=$(CDPATH= cd -- "$(dirname -- "$0")/link" && pwd)
work_dir=$(mktemp -d "${TMPDIR:-/tmp}/sdas251-link.XXXXXX")

cleanup()
{
    rm -rf "$work_dir"
}
trap cleanup 0 HUP INT TERM

cp "$test_dir/reloc-a.asm" "$work_dir/"
cp "$test_dir/reloc-b.asm" "$work_dir/"
cp "$test_dir/link.lk" "$work_dir/"
cp "$test_dir/imm-a.asm" "$test_dir/imm-b.asm" "$test_dir/imm.lk" "$work_dir/"

(
    cd "$work_dir"
    "$assembler" -plosg reloc-a.asm
    "$assembler" -plosg reloc-b.asm
    "$linker" -nf link.lk
    "$assembler" -plosg imm-a.asm
    "$assembler" -plosg imm-b.asm
    "$linker" -nf imm.lk
)

if ! cmp -s "$test_dir/linked.expected.ihx" "$work_dir/linked.ihx"; then
    echo "24-bit relocation/Intel HEX mismatch" >&2
    diff -u "$test_dir/linked.expected.ihx" "$work_dir/linked.ihx" >&2 || true
    exit 1
fi

if ! grep -q '00FF0018  target' "$work_dir/linked.map"; then
    echo "linked target does not have the expected 24-bit address" >&2
    exit 1
fi

# MOV/CMP DRk,#imm with a relocatable value take the zero-extending forms:
# "mov dr60,#stack_top - 1" must not become 7E FC (DR60 = FFFF003F).
imm_expected=7EF8003F7E180040BE18003F7EFC00407E1CFFFF7E181234BE1CFFFF
if ! grep -q "^:1C000000${imm_expected}" "$work_dir/imm.ihx"; then
    echo "MOV/CMP DRk,#imm: wrong immediate form for a relocatable value" >&2
    echo "expected ${imm_expected}" >&2
    cat "$work_dir/imm.ihx" >&2
    exit 1
fi
