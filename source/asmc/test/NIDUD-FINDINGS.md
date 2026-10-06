# asmc 2.39.18 — Linux test-run findings (runtest.sh port of runtest.cmd)

Context: ported runtest.cmd to bash (test/runtest.sh) to run the full suite on
Ubuntu against the Linux ELF binaries. 984 tests pass; the items below are what
the run surfaced. All findings reproduced on freshly built 2.39.18 binaries
(both bin/asmc and bin/asmc64 rebuilt from source, no bootstrap needed).

## 1. CRASH: SIGSEGV in GetSegRelocs on -mz (32-bit binary regression)

Minimal reproducer (crashes ~50% of runs, 0-byte output, A1901):

    .386
    .model small
    .stack 400h
    .code
s:  mov ah,4Ch
    int 21h
    push seg s          ; this line alone triggers it
    END s

Command:  asmc -q -mz -Fo out.exe repro.asm

Faulting code src/bin.asm:2289 (bin_write_module, MZ path):

    mov [rdi].e_lfarlc,MODULE.mz_ofs_fixups
    add rax,hdrbuf          ; rax is NOT initialized on this path
    GetSegRelocs( rax )     ; writes fixups through garbage pointer -> SIGSEGV

rax is a leftover from the preceding entry-point checks; nothing assigns it
before add rax,hdrbuf. Intermittency is explained by register residue/ASLR.
Crash site confirmed in gdb: RIP 0x404678, mov %cx,(%rdx) with pDst unmapped,
GetSegRelocs (src/bin.asm:296) fixup-writing block.

Bisect (30 runs each):
- shipped 2.39.16 ELF binary: 0/30 crashes
- freshly built 2.39.18 32-bit: 10-15/30 crashes
- freshly built 2.39.18 asmc64: 0/30 (MZ path differs, ifndef ASMC64)

Suspect for the trigger: 2.39.18 moved `mov esi,segm` to the top of SetSimSeg
(src/simsegm.asm) - a register-allocation change that newly exposes the
latent uninitialized-rax on the MZ write path.

Fix direction: initialize rax explicitly before add rax,hdrbuf
(e.g. mov eax,MODULE.mz_ofs_fixups / xor eax,eax per header layout).

Test that catches it: test/src/x86-mz-offset.asm (push seg _start line).

## 2. -win64 on the __UNIX__ build defaults to ELF, breaking SEH tests

init_win64() (src/cmdline.asm:109) under ifdef __UNIX__ sets
OFORMAT_ELF + LANG_SYSCALL; the Windows build sets OFORMAT_COFF +
LANG_FASTCALL. Consequence: proc frame / .allocstack / .setframe /
.endprolog on Linux fail with

    error A2248: not supported with current output format : frame

because SEH (.pdata/.xdata) requires COFF. All 8 x64-coff-proc/seh/
extcstack tests fail on Linux for this reason; with an explicit -coff
they all assemble and pass:

    asmc -c -win64 -coff -Fo t.obj src/x64-coff-seh.1.asm   ; ok
    asmc -c -win64        -Fo t.obj src/x64-coff-seh.1.asm   ; A2248

Two possible resolutions (either fine from the Linux side):
  a) runtest.cmd passes -coff explicitly for the x64-coff family
     (host-independent by definition), or
  b) -win64 implies COFF on both hosts and -elf64 stays the Linux
     container (breaking default change for existing Linux users).

runtest.sh now does (a) locally, documented in the script.

## 3. CSTACK-era test sources cannot generate goldens with defaults

8 x64-bin-* tests (2.39.15/17 era: x64-bin-cstack, x64-bin-vararg.2,
x64-bin-invoke.3, x64-bin-class.7, ...) plus x64-err-invoke.3 fail at
golden-generation time on both 2.39.16 and 2.39.18 with

    error A2008: syntax error : User registers inside frame: use -Cs or OPTION CSTACK:ON

The sources use `proc uses xmm6 ...` style frames. They assemble with -Cs.
runtest.cmd has no -Cs, so on Windows these presumably fail the same way
unless the Windows binary defaults differ.

## 4. x64-coff-proc.3/4: A2133 register value overwritten by INVOKE

    src/x64-coff-proc.3.asm(23): error A2133: register value overwritten by INVOKE

Genuine assembler errors on those two sources (not format-related;
they fail even with explicit -coff).

## 5. runtest.cmd portability notes (what runtest.sh had to handle)

For reference if runtest.cmd is ever touched:
- Windows asmc writes .obj for -win64/-coff; the Linux build writes .o
  when no -Fo is given. runtest.cmd's compare run relies on the Windows
  default; runtest.sh passes -Fo explicitly (also in the err tests -Fw).
- COFF/PE outputs embed time(&ifh.TimeDateStamp) (src/coff.asm:1429) and
  CodeView embeds the object filename, so byte-compare between runs fails
  on those bytes. runtest.sh normalizes both sides before cmp (zero the
  timestamp, scrub the objname). fcmp presumably tolerates this on Windows.
- x86-ext-1 needs linkw; skipped on Linux (no PE linker).

## Environment

- Ubuntu 26.04, bin/asmc + bin/asmc64 rebuilt at 2.39.18 (make YACC=1)
- suite: 984 goldens generated, PASS=984 FAIL=12 after the -coff workaround:
  8 x64-bin CSTACK + x64-err-invoke.3 + 2 A2133 + 1 linkw skip
- repro scripts and logs available on request.