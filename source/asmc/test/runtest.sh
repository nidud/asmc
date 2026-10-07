#!/bin/bash

# Changes in v2.39.19
# - the version to be tested is the new build: ../asmc
# - files produced by the test should not be altered
# - erroneous files should not be deleted

set -u
cd "$(dirname "$0")"

ASMX=${1:-../asmc}
[[ -x $ASMX ]] || { echo "assembler $ASMX not executable" >&2; exit 2; }
mkdir -p exp
rm -f -- *.err *.obj *.o *.exe *.ep *.bin

PASS=0; FAIL=0; SKIP=0
TOTAL=0; DONE=0
declare -a FAILED=()

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

do_test() {
    local skip=$1 src=$2 ext=$3; shift 3
    local base out expf
    base=$(basename "$src" .asm)
    out="$base$ext"
    expf="exp/$out"
    if [[ ! -f $expf ]]; then
        "$ASMX" -q "$@" -Fo "$expf" "$src" >/dev/null 2>&1
        if [[ ! -f $expf ]]; then
            report "NOEXP $base$ext"; return
        fi
        report "NEWEXP $base$ext"; return
    fi
    rm -f "$out"
    "$ASMX" -q "$@" -Fo "$out" "$src" >/dev/null 2>&1
    if [[ ! -f $out ]]; then report "NOOUT $base$ext"; return; fi
    if cmp -s "$out" "$expf" "$skip" "$skip"; then
        rm -f "$out"
        report PASS
    else
        report "DIFF $base$ext"
    fi
}
for f in src/x86-bin-*.asm;  do [[ -e $f ]] && do_test 0 "$f" .bin -bin -DBIN; done
for f in src/x64-bin-*.asm;  do [[ -e $f ]] && do_test 0 "$f" .bin -win64 -bin -DBIN; done
for f in src/x86-elf-*.asm;  do [[ -e $f ]] && do_test 0 "$f" .o -c -elf; done
for f in src/x64-elf-*.asm;  do [[ -e $f ]] && do_test 0 "$f" .o -c -elf64; done
for f in src/x64-dwarf*.asm; do [[ -e $f ]] && do_test 0 "$f" .o -c -elf64 -Zd; done
for f in src/x86-zg-*.asm;   do [[ -e $f ]] && do_test 0 "$f" .bin -Zg -bin; done
for f in src/x86-zd-*.asm;   do [[ -e $f ]] && do_test 0 "$f" .obj -Zd -omf; done
for f in src/x86-mz-*.asm;   do [[ -e $f ]] && do_test 0 "$f" .exe -mz; done
for f in src/x86-omf-*.asm;  do [[ -e $f ]] && do_test 0 "$f" .obj -c -omf; done
for f in src/x86-omf2-*.asm; do [[ -e $f ]] && do_test 0 "$f" .obj -c; done
for f in src/x86-cu-*.asm;   do [[ -e $f ]] && do_test 0 "$f" .obj -c -Cu; done
for f in src/x64-coff-*.asm; do [[ -e $f ]] && do_test 8 "$f" .obj -c -win64; done
for f in src/x86-coff-*.asm; do [[ -e $f ]] && do_test 8 "$f" .obj -c -coff; done
for f in src/x86-cv-*.asm;   do [[ -e $f ]] && do_test 8 "$f" .obj -c -coff -Zi4; done
for f in src/x86-pe-*.asm;   do [[ -e $f ]] && do_test 115 "$f" .exe -pe; done
for f in src/x64-pe-*.asm;   do [[ -e $f ]] && do_test 115 "$f" .exe -win64 -pe; done

err_test() { # src flags-that-produce-expected...
    local src=$1; shift
    local base expf out
    base=$(basename "$src" .asm)
    expf="exp/$base.err"; out="$base.err"
    if [[ ! -f $expf ]]; then
        "$ASMX" -c -q -W3 "$@" -Fw "$expf" "$src" >/dev/null 2>&1
        [[ -f $expf ]] || { report "NOEXP $base.err"; return; }
        rm -f "$base.obj"
        report "NEWEXP $base.err"; return
    fi
    rm -f "$out"
    "$ASMX" -c -q -W3 "$@" -Fw "$out" "$src" >/dev/null 2>&1
    if [[ ! -f $out ]]; then report "NOOUT $base.err"; return; fi
    if cmp -s "$out" "$expf"; then
        rm -f "$out" "$base.obj"
        report PASS
    else
        report "DIFF $base.err"
    fi
}
for f in src/x86-err-*.asm; do [[ -e $f ]] && err_test "$f" -omf; done
for f in src/x64-err-*.asm; do [[ -e $f ]] && err_test "$f" -win64; done

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
    if cmp -s "$out" "$expf"; then
        rm -f "$out"
        report PASS
    else
        report "DIFF $base.err"
    fi
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

# :x86-got, :x64-got (three variants: default, -fpic, -fPIC)
got_test() { # src ext flags...
    local src=$1 ext=$2; shift 2
    do_test 0 "$src" "$ext" "$@"
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
        if cmp -s "$out" "$expf"; then
            rm -f "$out"
            report PASS
        else
            report "DIFF $base$tag$ext"
        fi
    done
}
for f in src/x86-got-*.asm; do [[ -e $f ]] && got_test "$f" .o -c -elf; done
for f in src/x64-got-*.asm; do [[ -e $f ]] && got_test "$f" .o -c -elf64; done

# :x86-ep (preprocessed listing)
ep_test() {
    local src=$1
    local base expf out
    base=$(basename "$src" .asm)
    expf="exp/$base.ep"; out="$base.ep"
    if [[ ! -f $expf ]]; then
        "$ASMX" -q -EP "$src" >"$expf" 2>/dev/null
        rm -f "$base.obj"
        report "NEWEXP $base.ep"; return
    fi
    "$ASMX" -q -EP "$src" >"$out" 2>/dev/null
    if cmp -s "$out" "$expf"; then
        rm -f "$out" "$base.obj"
        report PASS
    else
        report "DIFF $base.ep"
    fi
}
for f in src/x86-ep-*.asm; do [[ -e $f ]] && ep_test "$f"; done

ext_test() {
    local src=$1
    local base expf out
    base=$(basename "$src" .asm)
    expf="exp/$base.exe"; out="$base.exe"
    if [[ ! -f $expf ]]; then
        "$ASMX" -q -elf -MT -Fe "$expf" "$src" >/dev/null 2>&1
        [[ -f $expf ]] || { report "NOEXP $base.exe (link)"; return; }
        rm -f "$base.o"
        report "NEWEXP $base.exe"; return
    fi
    rm -f "$out"
    "$ASMX" -q -elf -MT -Fe "$out" "$src" >/dev/null 2>&1
    if [[ ! -f $out ]]; then SKIP=$((SKIP+1)); DONE=$((DONE+1)); progress-bar "$DONE" "$TOTAL"; return; fi
    if cmp -s "$out" "$expf"; then
        rm -f "$out" "$base.o"
        report PASS
    else
        report "DIFF $base.exe"
    fi
}
for f in src/x86-ext-*.asm; do [[ -e $f ]] && ext_test "$f"; done

progress-bar "$TOTAL" "$TOTAL"; echo >&2
echo
echo "PASS=$PASS FAIL=$FAIL SKIP=$SKIP"
if (( FAIL )); then
    printf '%s\n' "${FAILED[@]}"
    exit 1
fi
exit 0
