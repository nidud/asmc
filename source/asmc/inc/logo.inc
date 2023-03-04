; LOGO.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

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
 char_t "Use option -? for more info" ,10
 char_t 0

cp_options \
 char_t "        ASMC"
ifdef ASMC64
 char_t "64"
endif
 char_t " [ -options ] filelist",10
 char_t 10
ifdef ASMC64
 char_t "-assert Generate .assert() code            -pe Generate PE binary file",10
 char_t "-autostack Auto stack space for arguments  -pf Preserve Flags (Epilogue-Invoke)",10
 char_t "-bin Generate plain binary file            -q, -nologo Suppress copyright message",10
 char_t "-Cs Push USER registers before prolouge    -r Recurse subdirectories",10
 char_t "-coff Generate COFF format object file     -Sa Maximize source listing",10
 char_t "-C<p|u|x> Set OPTION CASEMAP               -safeseh Assert exception handlers",10
 char_t "-D<name>[=text] Define text macro          -Sf Generate first pass listing",10
 char_t "-cui (-pe) SUBSYSTEM:CONSOLE (default)     -Sg Display generated code in listing",10
 char_t "-dotname Allow dot .identifiers            -Sn Suppress symbol-table listing",10
 char_t "-e<number> Set error limit number          -Sp[n] Set segment alignment",10
 char_t "-elf64 Generate 64-bit ELF object file     -stackalign Align locals to 16-byte",10
 char_t "-endbr Insert ENDBR at function entry      -swc C .SWITCH (default)",10
 char_t "-EP Output preprocessed listing to stdout  -swn No table in .SWITCH",10
 char_t "-eq Don't display error messages           -swp Pascal .SWITCH (auto .break)",10
 char_t "-Fd[file] Write import definition file     -swr Switch uses R11 (default)",10
 char_t "-Fi<file> Force <file> to be included      -swt Use table in .SWITCH (default)",10
 char_t "-Fl[file] Generate listing                 -Sx List false conditionals",10
 char_t "-fno-pic No position ind. code (default)   -w Same as -W0 -WX",10
 char_t "-Fo<file> Name object file                 -W<number> Set warning level",10
 char_t "-fpic Generate position independed code    -ws Store quoted strings as unicode",10
 char_t "-frame Auto generate unwind information    -WX Treat all warnings as errors",10
 char_t "-Fw<file> Set errors file name             -X Ignore INCLUDE environment path",10
 char_t "-Ge force stack checking for all funcs     -Zd Add line number debug info",10
 char_t "-gui (-pe) SUBSYSTEM:WINDOWS               -Zf Make all symbols public",10
 char_t "-Gv Use VECTORCALL calling convention      -Zg Generate code to match Masm",10
 char_t "-homeparams Copy Reg. parameters to Stack  -Zi[012348] Add symbolic debug info",10
 char_t "-I<name> Add include path                  -zl<f|p|s> Suppress items in COFF",10
 char_t "-logo Print logo string and exit           -Zne Disable non Masm extensions",10
 char_t "-nc<name> Set class name of code segment   -Znk Disable non Masm keywords",10
 char_t "-nd<name> Set name of data segment         -Zp[n] Set structure alignment",10
 char_t "-nm<name> Set name of module               -Zs Perform syntax check only",10
 char_t "-nolib Ignore INCLUDELIB directive.        -zze No export symbol decoration",10
 char_t "-nt<name> Set name of text segment         -zzs Store name of start address",10
else
 char_t "-<0|1|..|10>[p] Set CPU: 0=8086 (default), 1=80186, 2=80286, 3=80386, 4=80486,",10
 char_t " 5=Pentium,6=PPro,7=P2,8=P3,9=P4,10=x86-64; <p> allows privileged instructions",10
 char_t "-assert Generate .assert() code            -q, -nologo Suppress copyright message",10
 char_t "-autostack Auto stack space for arguments  -r Recurse subdirectories",10
 char_t "-bin Generate plain binary file            -Sa Maximize source listing",10
 char_t "-Cs Push USER registers before prolouge    -safeseh Assert exception handlers",10
 char_t "-coff Generate COFF format object file     -Sf Generate first pass listing",10
 char_t "-C<p|u|x> Set OPTION CASEMAP               -Sg Display generated code in listing",10
 char_t "-cui (-pe) SUBSYSTEM:CONSOLE (default)     -Sn Suppress symbol-table listing",10
 char_t "-D<name>[=text] Define text macro          -Sp[n] Set segment alignment",10
 char_t "-dotname Allow dot .identifiers            -stackalign Align locals to 16-byte",10
 char_t "-e<number> Set error limit number          -swc C .SWITCH (default)",10
 char_t "-elf Generate 32-bit ELF object file       -swn No table in .SWITCH",10
 char_t "-elf64 Generate 64-bit ELF object file     -swp Pascal .SWITCH (auto.break)",10
 char_t "-endbr Insert ENDBR at function entry      -swr Use reg [R|E]AX in switch code",10
 char_t "-EP Output preprocessed listing to stdout  -swt Use table in .SWITCH (default)",10
 char_t "-eq Don't display error messages           -Sx List false conditionals",10
 char_t "-Fd[file] Write import definition file     -w Same as -W0 -WX",10
 char_t "-Fi<file> Force <file> to be included      -W<number> Set warning level",10
 char_t "-Fl[file] Generate listing                 -win64 Generate 64-bit COFF object",10
 char_t "-Fo<file> Name object file                 -ws Store quoted strings as unicode",10
 char_t "-Fw<file> Set errors file name             -WX Treat all warnings as errors",10
 char_t "-FPi Generate 80x87 emulator encoding      -X Ignore INCLUDE environment path",10
 char_t "-FPi87 80x87 instructions (default)        -zcw No decoration for C symbols",10
 char_t "-fpc Disallow floating-point instructions  -Zd Add line number debug info",10
 char_t "-fp<n> Set FPU: 0=8087, 2=80287, 3=80387   -Zf Make all symbols public",10
 char_t "-Ge force stack checking for all funcs     -zf<0|1> Set FASTCALL type: MS-OW",10
 char_t "-G<cdzvs> Pascal, C, Std/Vector/Sys-call   -Zg Generate code to match Masm",10
 char_t "-gui (-pe) SUBSYSTEM:WINDOWS               -Zi[012358] Add symbolic debug info",10
 char_t "-homeparams Copy Reg. parameters to Stack  -zlc No OMF records of data in code",10
 char_t "-I<name> Add include path                  -zld No OMF records of far call",10
 char_t "-logo Print logo string and exit           -zl<f|p|s> Suppress items in COFF",10
 char_t "-m<t|s|c|m|l|h|f> Set memory model         -Zm Enable MASM 5.10 compatibility",10
 char_t "-mz Generate DOS MZ binary file            -Zne Disable non Masm extensions",10
 char_t "-nc<name> Set class name of code segment   -Znk Disable non Masm keywords",10
 char_t "-nd<name> Set name of data segment         -Zp[n] Set structure alignment",10
 char_t "-nm<name> Set name of module               -Zs Perform syntax check only",10
 char_t "-nolib Ignore INCLUDELIB directive.        -zt<0|1|2> Set STDCALL decoration",10
 char_t "-nt<name> Set name of text segment         -Zv8 Enable Masm v8+ PROC visibility",10
 char_t "-pe Generate PE binary file, 32/64-bit     -zze No export symbol decoration",10
 char_t "-pf Preserve Flags (Epilogue-Invoke)       -zzs Store name of start address",10
endif
 char_t 0

