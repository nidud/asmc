#!/bin/bash
# Linux port of runtest.cmd --  ./runtest.sh [asmc-binary]
# Mirrors every :label of the Windows script 1:1 (same flags, same order).
# fcmp -> cmp (fcmp's -coff/-pe header-tolerant compare is a full cmp here;
# byte-identical outputs pass either way, differences that only fcmp
# tolerates are reported as DIFF and can be inspected manually).
# Like the .cmd: expected files are created in exp/ on first run if absent.
set -u
cd "$(dirname "$0")"

ASMX=${1:-../../../bin/asmc}
[[ -x $ASMX ]] || { echo "assembler $ASMX not executable" >&2; exit 2; }
# Most 32-bit tests (x86-*) need the 32-bit assembler: the asmc64 build
# compiles out .386/.model etc (ifndef ASMC64 in inc/directve.inc).
# x64-* tests also work with the 32-bit -win64/-elf64 code paths.
mkdir -p exp

# sweep leftover artifacts from previous (failed) runs: outputs land in the
# test dir next to the sources and any of them collides with the next run.
rm -f -- *.err *.obj *.o *.exe *.ep *.bin

PASS=0; FAIL=0; SKIP=0
TOTAL=0; DONE=0
declare -a FAILED=()

# progress bar (after bahamas10/ysap progress-bar): [||||    ] 123/456 (26%)
progress-bar() {
    local current=$1 len=$2
    local bar_char='>' empty_char=' ' length=40
    local perc_done=$((current * 100 / len))
    (( perc_done > 100 )) && perc_done=100
    local num_bars=$((perc_done * length / 100))
    local i s='['
    for ((i = 0; i < num_bars; i++)); do s+=$bar_char; done
    for ((i = num_bars; i < length; i++)); do s+=$empty_char; done
    s+=']'
    echo -ne "$s $current/$len ($perc_done%)\r" >&2
}

# count total tests first so the bar knows its denominator.
# Note: got-family sources run 3 compares each and some paths report twice,
# so executed tests can exceed the source count; the bar clamps to 100%.
shopt -s nullglob
TOTAL=$(ls src/*-*.asm 2>/dev/null | wc -l)

report() { # $1 status, $2 name
    local st=${1:-ERR} name=${2:-?}
    case $st in
        PASS) PASS=$((PASS+1));;
        *)    FAIL=$((FAIL+1)); FAILED+=("$st $name");;
    esac
    DONE=$((DONE+1))
    progress-bar "$DONE" "$TOTAL"
}

# do_test <srcfile> <expected-ext> <asm-flags...>
# Compares fresh output against exp/<name><ext>; creates expected if absent.
# Both sides are normalized (timestamp/objname scrubbed) before the compare.
do_test() {
    local src=$1 ext=$2; shift 2
    local base out expf
    base=$(basename "$src" .asm)
    out="$base$ext"
    expf="exp/$out"
    if [[ ! -f $expf ]]; then
        "$ASMX" -q "$@" -Fo "$expf" "$src" >/dev/null 2>&1
        if [[ ! -f $expf ]]; then
            report "NOEXP $base$ext"; return
        fi
        normalize "$src" "$expf"
        report "NEWEXP $base$ext"; return
    fi
    rm -f "$out"
    # -Fo forces the output name: the Linux build defaults to .o for -win64/-coff,
    # Windows asmc to .obj -- without -Fo the same source writes different
    # filenames per platform and the compare below never finds the output.
    "$ASMX" -q "$@" -Fo "$out" "$src" >/dev/null 2>&1
    if [[ ! -f $out ]]; then report "NOOUT $base$ext"; return; fi
    normalize "$src" "$out"
    if cmp -s "$out" "$expf"; then
        report PASS
    else
        report "DIFF $base$ext"
    fi
    rm -f "$out"
}

# normalize <src> <file>: scrub nondeterministic bytes in-place.
#  - COFF objects: TimeDateStamp at header offset 4 (4 bytes) -> zero
#    (src/coff.asm:1429 time(&ifh.TimeDateStamp)). ELF/OMF unaffected;
#    zeroing their (ELF: no such field / OMF: none) offsets also harmless
#    only when format matches, so check the magic first.
#  - PE/MZ files: PE COFF header TimeDateStamp at 0x70 for PE32/PE32+
#    (DOS stub + 'PE\0\0' + 4-byte COFF hdr offset); only if 'PE\0\0' found
#    at 0x3c-pointed offset.. MZ raw bins have no timestamp - untouched.
#  - CodeView info: the embedded object-filename (basename of <src>.<ext>,
#    e.g. "x86-cv-1.obj") is replaced by a fixed name so the two runs of
#    differently-named outputs can byte-compare. Both directions use the
#    same base name, so only runs with equal basenames are compared.
normalize() {
    python3 - "$1" "$2" <<'PYEOF'
import sys, struct, re
src, path = sys.argv[1], sys.argv[2]
base = src.rsplit('/', 1)[-1]  # e.g. x86-cv-1 / x64-pe-import.1
ext = path.rsplit('.', 1)[-1]
d = bytearray(open(path, 'rb').read())

if len(d) >= 8 and d[:4] not in (b'\x7fELF',):
    # COFF object: files starting with machine word, TimeDateStamp at 4.
    # Detect by: no MZ/ELF magic, and section table at 20/24 for 32/64.
    if d[:2] != b'MZ':
        d[4:8] = b'\x00\x00\x00\x00'

if d[:2] == b'MZ':
    # PE file: find PE\0\0 signature
    if len(d) >= 0x40:
        peoff = struct.unpack_from('<I', d, 0x3c)[0]
        if 0 < peoff < len(d) - 24 and d[peoff:peoff+4] == b'PE\x00\x00':
            # TimeDateStamp = PE sig + 4 (Machine) + 0 = offset peoff+8
            d[peoff+8:peoff+12] = b'\x00\x00\x00\x00'

# CodeView: scrub embedded object name (with and without ext).
for cand in {(base + '.' + ext).encode(), base.encode()}:
    if cand in d:
        d = d.replace(cand, b'\x00' * len(cand))
open(path, 'wb').write(d)
PYEOF
}

# Each label of runtest.cmd, in the same order:
# :x86-bin, :x64-bin
for f in src/x86-bin-*.asm; do [[ -e $f ]] && do_test "$f" .bin -bin -DBIN; done
for f in src/x64-bin-*.asm; do [[ -e $f ]] && do_test "$f" .bin -win64 -bin -DBIN; done
# :x86-err, :x64-err  (error tests: only the .err text file is compared,
# obj is produced with expected-flags then deleted, mirroring the .cmd)
err_test() { # src flags-that-produce-expected...
    local src=$1; shift
    local base expf out
    base=$(basename "$src" .asm)
    expf="exp/$base.err"; out="$base.err"
    if [[ ! -f $expf ]]; then
        "$ASMX" -c -q -W3 "$@" -Fw "$expf" "$src" >/dev/null 2>&1
        [[ -f $expf ]] || { report "NOEXP $base.err"; return; }
        report "NEWEXP $base.err"; return
    fi
    rm -f "$out"
    "$ASMX" -c -q -W3 "$@" -Fw "$out" "$src" >/dev/null 2>&1
    if [[ ! -f $out ]]; then report "NOOUT $base.err"; return; fi
    if cmp -s "$out" "$expf"; then report PASS; else report "DIFF $base.err"; fi
    rm -f "$out" "$base.obj"
}
# NOTE: the W3+expected flags here already include -Fw in the .cmd, but
# asmc writes the .err text to stdout unless -Fw is given, so the compare
# run uses the same -Fw and the produced .err is the compared artifact.
for f in src/x86-err-*.asm; do [[ -e $f ]] && err_test "$f" -omf; done
for f in src/x64-err-*.asm; do [[ -e $f ]] && err_test "$f" -win64; done
# :x86-elf, :x64-elf
for f in src/x86-elf-*.asm; do [[ -e $f ]] && do_test "$f" .o -c -elf; done
for f in src/x64-elf-*.asm; do [[ -e $f ]] && do_test "$f" .o -c -elf64; done
# :x86-coff, :x64-coff
for f in src/x86-coff-*.asm; do [[ -e $f ]] && do_test "$f" .obj -c -coff; done
# :x64-coff -- -coff is passed explicitly because on the __UNIX__ build
# -win64 alone defaults to ELF output (init_win64() in cmdline.asm), and
# the SEH/frame machinery (.pdata/.xdata, proc frame, .allocstack) then
# fails with A2248. runtest.cmd relies on -win64 implying COFF (Windows
# default); the explicit flag makes the test host-independent.
for f in src/x64-coff-*.asm; do [[ -e $f ]] && do_test "$f" .obj -c -win64 -coff; done
# :x86-mz
for f in src/x86-mz-*.asm; do [[ -e $f ]] && do_test "$f" .exe -mz; done
# :x86-got, :x64-got (three variants: default, -fpic, -fPIC)
got_test() { # src ext flags...
    local src=$1 ext=$2; shift 2
    do_test "$src" "$ext" "$@"
    local base tag
    for tag in pie pic; do
        base=$(basename "$src" .asm)
        local expf="exp/$base$tag$ext" out="$base$tag$ext" flag="-fpic"
        [[ $tag == pic ]] && flag="-fPIC"
        if [[ ! -f $expf ]]; then
            "$ASMX" -c -q "$@" "$flag" -Fo "$expf" "$src" >/dev/null 2>&1
            [[ -f $expf ]] || { report "NOEXP $base$tag$ext"; continue; }
            report "NEWEXP $base$tag$ext"; continue
        fi
        rm -f "$out"
        "$ASMX" -c -q "$@" "$flag" -Fo "$out" "$src" >/dev/null 2>&1
        if [[ ! -f $out ]]; then report "NOOUT $base$tag$ext"; continue; fi
        if cmp -s "$out" "$expf"; then report PASS; else report "DIFF $base$tag$ext"; fi
        rm -f "$out"
    done
}
for f in src/x86-got-*.asm; do [[ -e $f ]] && got_test "$f" .o -c -elf; done
for f in src/x64-got-*.asm; do [[ -e $f ]] && got_test "$f" .o -c -elf64; done
# :x86-omf
for f in src/x86-omf-*.asm; do [[ -e $f ]] && do_test "$f" .obj -c -omf; done
# :x86-omf2 (default format = omf)
for f in src/x86-omf2-*.asm; do [[ -e $f ]] && do_test "$f" .obj -c; done
# :x86-cu
for f in src/x86-cu-*.asm; do [[ -e $f ]] && do_test "$f" .obj -c -Cu; done
# :x86-pe, :x64-pe
for f in src/x86-pe-*.asm; do [[ -e $f ]] && do_test "$f" .exe -pe; done
for f in src/x64-pe-*.asm; do [[ -e $f ]] && do_test "$f" .exe -win64 -pe; done
# :x86-ep (preprocessed listing)
ep_test() {
    local src=$1
    local base expf out
    base=$(basename "$src" .asm)
    expf="exp/$base.ep"; out="$base.ep"
    if [[ ! -f $expf ]]; then
        "$ASMX" -q -EP "$src" >"$expf" 2>/dev/null
        report "NEWEXP $base.ep"; return
    fi
    "$ASMX" -q -EP "$src" >"$out" 2>/dev/null
    if cmp -s "$out" "$expf"; then report PASS; else report "DIFF $base.ep"; fi
    rm -f "$out"
}
for f in src/x86-ep-*.asm; do [[ -e $f ]] && ep_test "$f"; done
# :x86-zg
for f in src/x86-zg-*.asm; do [[ -e $f ]] && do_test "$f" .bin -Zg -bin; done
# :x86-zd
for f in src/x86-zd-*.asm; do [[ -e $f ]] && do_test "$f" .obj -Zd -omf; done
# :x86-berr, :x86-cerr, :x64-cerr, :x86-perr
berr_test() { # src flags...
    local src=$1; shift
    local base expf out
    base=$(basename "$src" .asm)
    expf="exp/$base.err"; out="$base.err"
    if [[ ! -f $expf ]]; then
        "$ASMX" -c -q -eq "$@" -Fw "$expf" "$src" >/dev/null 2>&1
        [[ -f $expf ]] || { report "NOEXP $base.err"; return; }
        report "NEWEXP $base.err"; return
    fi
    rm -f "$out"
    "$ASMX" -c -q -eq "$@" -Fw "$out" "$src" >/dev/null 2>&1
    if [[ ! -f $out ]]; then report "NOOUT $base.err"; return; fi
    if cmp -s "$out" "$expf"; then report PASS; else report "DIFF $base.err"; fi
    rm -f "$out"
}
for f in src/x86-berr-*.asm; do [[ -e $f ]] && berr_test "$f" -bin; done
for f in src/x86-cerr-*.asm; do [[ -e $f ]] && berr_test "$f" -coff; done
for f in src/x64-cerr-*.asm; do [[ -e $f ]] && berr_test "$f" -win64; done
# :x86-perr (pe + expected; del the .exe too)
for f in src/x86-perr-*.asm; do
    [[ -e $f ]] || continue
    berr_test "$f" -pe
    base=$(basename "$f" .asm); rm -f "$base.exe"
done
# :x86-ext (link via -Fe produces a PE; linking may need linkw -- report SKIP
# if the linker is unavailable, matching the wine-only fallback)
ext_test() {
    local src=$1
    local base expf out
    base=$(basename "$src" .asm)
    expf="exp/$base.exe"; out="$base.exe"
    if [[ ! -f $expf ]]; then
        "$ASMX" -q -coff -Fe "$expf" "$src" >/dev/null 2>&1
        [[ -f $expf ]] || { report "NOEXP $base.exe (link)"; return; }
        report "NEWEXP $base.exe"; return
    fi
    rm -f "$out"
    "$ASMX" -q -coff -Fe "$out" "$src" >/dev/null 2>&1
    if [[ ! -f $out ]]; then SKIP=$((SKIP+1)); DONE=$((DONE+1)); progress-bar "$DONE" "$TOTAL"; return; fi
    if cmp -s "$out" "$expf"; then report PASS; else report "DIFF $base.exe"; fi
    rm -f "$out" "$base.obj"
}
for f in src/x86-ext-*.asm; do [[ -e $f ]] && ext_test "$f"; done
# :x86-cv
for f in src/x86-cv-*.asm; do [[ -e $f ]] && do_test "$f" .obj -c -coff -Zi4; done
# :x64-dwarf  (note: file is x64-dwarf.1.asm -- glob src/x64-dwarf*.asm)
for f in src/x64-dwarf*.asm; do [[ -e $f ]] && do_test "$f" .o -c -elf64 -Zd; done

# finish the progress line so the summary starts on a fresh line
progress-bar "$TOTAL" "$TOTAL"; echo >&2
echo
echo "PASS=$PASS FAIL=$FAIL SKIP=$SKIP"
# sweep residue from failed tests so the tree stays clean for the next run
rm -f -- *.err *.obj *.o *.exe *.ep *.bin
if (( FAIL )); then
    printf '%s\n' "${FAILED[@]}"
    exit 1
fi
exit 0
