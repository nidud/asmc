#include <stdio.h>
#include <globals.h>

#ifdef __ASMC64__
#define X64 " (x64)"
#define ASMC64 "ASMC64"
#else
#define X64
#define ASMC64 "ASMC"
#endif

char cp_logo[] =
 "Asmc Macro Assembler" X64 " Version %d.%d"
#if ASMC_SUBMINOR_VER
 ".%02d"
#endif
 ;
char cp_copyright[] =
 "Copyright (C) The Asmc Contributors. All Rights Reserved.\n"
 "Portions Copyright (C) 1984-2002 Sybase, Inc. All Rights Reserved.\n";

static char cp_usage[] =
 "USAGE: " ASMC64 " [ options ] filelist\n"
 "Use option /? for more info\n";

static char cp_options[] =

 "        " ASMC64 " [ /options ] filelist\n"
 "\n"

#ifdef __ASMC64__
 "/assert Generate .assert() code            /q, /nologo Suppress copyright message\n"
 "/autostack Auto stack space for arguments  /r Recurse subdirectories\n"
 "/bin Generate plain binary file            /Sa Maximize source listing\n"
 "/Cs Push USER registers before prolouge    /safeseh Assert exception handlers\n"
 "/coff Generate COFF format object file     /Sf Generate first pass listing\n"
 "/C<p|u|x> Set OPTION CASEMAP               /Sg Display generated code in listing\n"
 "/D<name>[=text] Define text macro          /Sn Suppress symbol-table listing\n"
 "/e<number> Set error limit number          /Sp[n] Set segment alignment\n"
 "/elf64 Generate 64-bit ELF object file     /stackalign Align locals to 16-byte\n"
 "/EP Output preprocessed listing to stdout  /swc C .SWITCH (default)\n"
 "/eq Don't display error messages           /swn No table in .SWITCH\n"
 "/Fd[file] Write import definition file     /swp Pascal .SWITCH (auto .break)\n"
 "/Fi<file> Force <file> to be included      /swr Switch uses R10/R11 (default)\n"
 "/Fl[file] Generate listing                 /swt Use table in .SWITCH (default)\n"
 "/Fo<file> Name object file                 /Sx List false conditionals\n"
 "/frame Auto generate unwind information    /w Same as /W0 /WX\n"
 "/Fw<file> Set errors file name             /W<number> Set warning level\n"
 "/Ge force stack checking for all funcs     /ws Store quoted strings as unicode\n"
 "/Gv Use VECTORCALL calling convention      /WX Treat all warnings as errors\n"
 "/homeparams Copy Reg. parameters to Stack  /X Ignore INCLUDE environment path\n"
 "/I<name> Add include path                  /Zd Add line number debug info\n"
 "/logo Print logo string and exit           /Zf Make all symbols public\n"
 "/nc<name> Set class name of code segment   /Zg Generate code to match Masm\n"
 "/nd<name> Set name of data segment         /Zi[012348] Add symbolic debug info\n"
 "/nm<name> Set name of module               /zl<f|p|s> Suppress items in COFF\n"
 "/nolib Ignore INCLUDELIB directive.        /Zne Disable non Masm extensions\n"
 "/nt<name> Set name of text segment         /Znk Disable non Masm keywords\n"
 "/pe Generate PE binary file                /Zp[n] Set structure alignment\n"
 " /cui - subsystem:console (default)        /Zs Perform syntax check only\n"
 " /gui - subsystem:windows                  /zze No export symbol decoration\n"
 "/pf Preserve Flags (Epilogue/Invoke)       /zzs Store name of start address\n";
#else
 "/<0|1|..|10>[p] Set CPU: 0=8086 (default), 1=80186, 2=80286, 3=80386, 4=80486,\n"
 " 5=Pentium,6=PPro,7=P2,8=P3,9=P4,10=x86-64; <p> allows privileged instructions\n"
 "/assert Generate .assert() code            /r Recurse subdirectories\n"
 "/autostack Auto stack space for arguments  /Sa Maximize source listing\n"
 "/bin Generate plain binary file            /safeseh Assert exception handlers\n"
 "/Cs Push USER registers before prolouge    /Sf Generate first pass listing\n"
 "/coff Generate COFF format object file     /Sg Display generated code in listing\n"
 "/C<p|u|x> Set OPTION CASEMAP               /Sn Suppress symbol-table listing\n"
 "/D<name>[=text] Define text macro          /Sp[n] Set segment alignment\n"
 "/e<number> Set error limit number          /stackalign Align locals to 16-byte\n"
 "/elf Generate 32-bit ELF object file       /swc C .SWITCH (default)\n"
 "/elf64 Generate 64-bit ELF object file     /swn No table in .SWITCH\n"
 "/EP Output preprocessed listing to stdout  /swp Pascal .SWITCH (auto.break)\n"
 "/eq Don't display error messages           /swr Use reg [R|E]AX in switch code\n"
 "/Fd[file] Write import definition file     /swt Use table in .SWITCH (default)\n"
 "/Fi<file> Force <file> to be included      /Sx List false conditionals\n"
 "/Fl[file] Generate listing                 /w Same as /W0 /WX\n"
 "/Fo<file> Name object file                 /W<number> Set warning level\n"
 "/Fw<file> Set errors file name             /win64 Generate 64-bit COFF object\n"
 "/FPi Generate 80x87 emulator encoding      /ws Store quoted strings as unicode\n"
 "/FPi87 80x87 instructions (default)        /WX Treat all warnings as errors\n"
 "/fpc Disallow floating-point instructions  /X Ignore INCLUDE environment path\n"
 "/fp<n> Set FPU: 0=8087, 2=80287, 3=80387   /zcw No decoration for C symbols\n"
 "/Ge force stack checking for all funcs     /Zd Add line number debug info\n"
 "/G<cdzv> Pascal, C, Stdcall or Vectorcall  /Zf Make all symbols public\n"
 "/homeparams Copy Reg. parameters to Stack  /zf<0|1> Set FASTCALL type: MS/OW\n"
 "/I<name> Add include path                  /Zg Generate code to match Masm\n"
 "/logo Print logo string and exit           /Zi[012358] Add symbolic debug info\n"
 "/m<t|s|c|m|l|h|f> Set memory model         /zlc No OMF records of data in code\n"
 "/mz Generate DOS MZ binary file            /zld No OMF records of far call\n"
 "/nc<name> Set class name of code segment   /zl<f|p|s> Suppress items in COFF\n"
 "/nd<name> Set name of data segment         /Zm Enable MASM 5.10 compatibility\n"
 "/nm<name> Set name of module               /Zne Disable non Masm extensions\n"
 "/nolib Ignore INCLUDELIB directive.        /Znk Disable non Masm keywords\n"
 "/nt<name> Set name of text segment         /Zp[n] Set structure alignment\n"
 "/pe Generate PE binary file, 32/64-bit     /Zs Perform syntax check only\n"
 " /cui - subsystem:console (default)        /zt<0|1|2> Set STDCALL decoration\n"
 " /gui - subsystem:windows                  /Zv8 Enable Masm v8+ PROC visibility\n"
 "/pf Preserve Flags (Epilogue/Invoke)       /zze No export symbol decoration\n"
 "/q, /nologo Suppress copyright message     /zzs Store name of start address\n";
#endif

int banner_printed = 0;

void write_logo(void)
{
    if ( !banner_printed ) {
	banner_printed = 1;
	printf( cp_logo, ASMC_MAJOR_VER, ASMC_MINOR_VER, ASMC_SUBMINOR_VER );
	printf( "\n%s\n", cp_copyright );
    }
}

void write_usage(void)
{
    write_logo();
    printf( cp_usage );
}

void write_options(void)
{
    write_logo();
    printf( cp_options );
}
