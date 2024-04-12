; LOGO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include asmc.inc

public cp_logo
public banner_printed

.data

 banner_printed db 0

cp_logo \
 char_t "Asmc Macro Assembler"
ifdef ASMC64
 char_t " (x64)"
endif
 char_t " Version ", ASMC_VERSSTR
 char_t 0

cp_copyright \
 char_t "Copyright (C) The Asmc Contributors. All Rights Reserved.",10
 char_t 0

cp_usage \
 char_t "USAGE: ASMC"
ifdef ASMC64
 char_t "64"
endif
 char_t " [ options ] filelist",10
ifdef __UNIX__
 char_t "Use option -h for more info" ,10
else
 char_t "Use option -? for more info" ,10
endif
 char_t 0

cp_options \
 char_t "        ASMC"
ifdef ASMC64
 char_t "64"
endif
 char_t " [ -options ] filelist",10
 char_t 10
ifndef ASMC64
 char_t "-<0|1|..|10>[p] Set CPU: 0=8086 (default), 1=80186, 2=80286, 3=80386, 4=80486,",10
 char_t " 5=Pentium,6=PPro,7=P2,8=P3,9=P4,10=x86-64; <p> allows privileged instructions",10
endif
 char_t "-assert Generate .assert() code            -autostack Auto stack space for arguments",10
 char_t "-bin Generate plain binary file            -Cs Push USER registers before prolouge",10
 char_t "-coff Generate COFF format object file     -C<p|u|x> Set OPTION CASEMAP",10
 char_t "-D<name>[=text] Define text macro          -dotname Allow dot .identifiers",10
 char_t "-e<number> Set error limit number          -elf[64] Generate ELF object file",10
 char_t "-endbr Insert ENDBR at function entry      -EP Output preprocessed listing to stdout",10
 char_t "-eq Don't display error messages           -Fd[file] Write import definition file",10
 char_t "-Fi<file> Force <file> to be included      -Fl[file] Generate listing",10
 char_t "-Fo<file> Name object file                 -Fw<file> Set errors file name",10
 char_t "-fpic, -fno-pic Position Independed Code   -frame Auto generate unwind information",10
ifndef ASMC64
 char_t "-FPi Generate 80x87 emulator encoding      -FPi87 80x87 instructions (default)",10
 char_t "-fpc Disallow floating-point instructions  -fp<n> Set FPU: 0=8087, 2=80287, 3=80387",10
endif
 char_t "-Ge force stack checking for all funcs     -G<cdzvs> Pascal, C, Std/Vector/Sys-call",10
 char_t "-gui, -cui (-pe) Windows/Console           -homeparams Copy Reg. parameters to Stack",10
 char_t "-I<name> Add include path                  -logo Print logo string and exit",10
ifndef ASMC64
 char_t "-m<t|s|c|m|l|h|f> Set memory model         -mz Generate DOS MZ binary file",10
endif
 char_t "-MD[d] (dynamic) Defines _MSVCRT [_DEBUG]  -MT[d] (static) Defines _MT [_DEBUG]",10
 char_t "-nc<name> Set class name of code segment   -nd<name> Set name of data segment",10
 char_t "-nm<name> Set name of module               -nolib Ignore INCLUDELIB directive",10
 char_t "-nt<name> Set name of text segment         -pe Generate PE binary file",10
 char_t "-q, -nologo Suppress copyright message     -r Recurse subdirectories",10
 char_t "-Sa Maximize source listing                -safeseh Assert exception handlers",10
 char_t "-Sf Generate first pass listing            -Sg Display generated code in listing",10
 char_t "-Sn Suppress symbol-table listing          -Sp[n] Set segment alignment",10
 char_t "-stackalign Align locals to 16-byte        -sysvregs Strip RDI/RSI from USES",10
 char_t "-Sx List false conditionals                -w Same as -W0 -WX",10
 char_t "-W<number> Set warning level               -win64 Generate 64-bit COFF object",10
 char_t "-ws Store quoted strings as unicode        -WX Treat all warnings as errors",10
 char_t "-X Ignore INCLUDE environment path         -Z7 Add full symbolic debug info",10
 char_t "-zcw No decoration for C symbols           -Zd Add line number debug info",10
 char_t "-Zf Make all symbols public                -zf<0|1> Set FASTCALL type: MS-OW",10
 char_t "-Zg Generate code to match Masm            -Zi[012348] Add symbolic debug info",10
ifndef ASMC64
 char_t "-zlc No OMF records of data in code        -zld No OMF records of far call",10
 char_t "-Zm Enable MASM 5.10 compatibility         -Zv8 Enable Masm v8+ PROC visibility",10
endif
 char_t "-zl<f|p|s> Suppress items in COFF          -Zp[n] Set structure alignment",10
 char_t "-Zs Perform syntax check only              -zt<0|1|2> Set STDCALL decoration",10
 char_t "-zze No export symbol decoration           -zzs Store name of start address",10
 char_t 0

.code

write_logo proc __ccall

    .if ( !banner_printed )
	mov banner_printed,1
	tprintf( &cp_logo )
	tprintf( "\n%s\n", &cp_copyright )
    .endif
    ret

write_logo endp

write_usage proc __ccall

    write_logo()
    tprintf( &cp_usage )
    ret

write_usage endp

write_options proc __ccall

    write_logo()
    tprintf( &cp_options )
    ret

write_options endp

    end
