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
 "Asmc Macro Assembler" X64 " Version " ASMC_VERSSTR ".15";
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
 "/assert Generate .assert() code            /Sa Maximize source listing\n"
 "/autostack Auto stack space for arguments  /safeseh Assert exception handlers\n"
 "/bin Generate plain binary file            /Sf Generate first pass listing\n"
 "/Cs Push USER registers before prolouge    /Sg Display generated code in listing\n"
 "/coff Generate COFF format object file     /Sn Suppress symbol-table listing\n"
 "/C<p|u|x> Set OPTION CASEMAP               /Sp[n] Set segment alignment\n"
 "/D<name>[=text] Define text macro          /stackalign Align locals to 16-byte\n"
 "/e<number> Set error limit number          /swc C .SWITCH (default)\n"
 "/elf64 Generate 64-bit ELF object file     /swn No table in .SWITCH\n"
 "/EP Output preprocessed listing to stdout  /swp Pascal .SWITCH (auto .break)\n"
 "/eq Don't display error messages           /swr Switch uses R10/R11 (default)\n"
 "/Fd[file] Write import definition file     /swt Use table in .SWITCH (default)\n"
 "/Fi<file> Force <file> to be included      /Sx List false conditionals\n"
 "/Fl[file] Generate listing                 /w Same as /W0 /WX\n"
 "/Fo<file> Name object file                 /W<number> Set warning level\n"
 "/Fw<file> Set errors file name             /win64 Generate 64-bit COFF object\n"
 "/Ge force stack checking for all funcs     /ws Store quoted strings as unicode\n"
 "/Gv Use VECTORCALL calling convention      /WX Treat all warnings as errors\n"
 "/homeparams Copy Reg. parameters to Stack  /X Ignore INCLUDE environment path\n"
 "/I<name> Add include path                  /Zd Add line number debug info\n"
 "/logo Print logo string and exit           /Zf Make all symbols public\n"
 "/nc<name> Set class name of code segment   /Zg Generate code to match Masm\n"
 "/nd<name> Set name of data segment         /Zi[0|1|2|3] Add symbolic debug info\n"
 "/nm<name> Set name of module               /zl<f|p|s> Suppress items in COFF\n"
 "/nt<name> Set name of text segment         /Zne Disable non Masm extensions\n"
 "/pe Generate PE binary file                /Znk Disable non Masm keywords\n"
 " /cui - subsystem:console (default)        /Zp[n] Set structure alignment\n"
 " /gui - subsystem:windows                  /Zs Perform syntax check only\n"
 "/pf Preserve Flags (Epilogue/Invoke)       /zze No export symbol decoration\n"
 "/q, /nologo Suppress copyright message     /zzs Store name of start address\n"
 "/r Recurse subdirectories\n";
#else
 "/<0|1|..|10>[p] Set CPU: 0=8086 (default), 1=80186, 2=80286, 3=80386, 4=80486,\n"
 " 5=Pentium,6=PPro,7=P2,8=P3,9=P4,10=x86-64; <p> allows privileged instructions\n"
 "/assert Generate .assert() code            /safeseh Assert exception handlers\n"
 "/autostack Auto stack space for arguments  /Sf Generate first pass listing\n"
 "/bin Generate plain binary file            /Sg Display generated code in listing\n"
 "/Cs Push USER registers before prolouge    /Sn Suppress symbol-table listing\n"
 "/coff Generate COFF format object file     /Sp[n] Set segment alignment\n"
 "/C<p|u|x> Set OPTION CASEMAP               /stackalign Align locals to 16-byte\n"
 "/D<name>[=text] Define text macro          /swc C .SWITCH (default)\n"
 "/e<number> Set error limit number          /swn No table in .SWITCH\n"
 "/elf Generate 32-bit ELF object file       /swp Pascal .SWITCH (auto.break)\n"
 "/elf64 Generate 64-bit ELF object file     /swr Use reg [R|E]AX in switch code\n"
 "/EP Output preprocessed listing to stdout  /swt Use table in .SWITCH (default)\n"
 "/eq Don't display error messages           /Sx List false conditionals\n"
 "/Fd[file] Write import definition file     /w Same as /W0 /WX\n"
 "/Fi<file> Force <file> to be included      /W<number> Set warning level\n"
 "/Fl[file] Generate listing                 /win64 Generate 64-bit COFF object\n"
 "/Fo<file> Name object file                 /ws Store quoted strings as unicode\n"
 "/Fw<file> Set errors file name             /WX Treat all warnings as errors\n"
 "/FPi Generate 80x87 emulator encoding      /X Ignore INCLUDE environment path\n"
 "/FPi87 80x87 instructions (default)        /zcw No decoration for C symbols\n"
 "/fpc Disallow floating-point instructions  /Zd Add line number debug info\n"
 "/fp<n> Set FPU: 0=8087, 2=80287, 3=80387   /Zf Make all symbols public\n"
 "/Ge force stack checking for all funcs     /zf<0|1> Set FASTCALL type: MS/OW\n"
 "/G<cdzv> Pascal, C, Stdcall or Vectorcall  /Zg Generate code to match Masm\n"
 "/homeparams Copy Reg. parameters to Stack  /Zi[0|1|2|3] Add symbolic debug info\n"
 "/I<name> Add include path                  /zlc No OMF records of data in code\n"
 "/logo Print logo string and exit           /zld No OMF records of far call\n"
 "/m<t|s|c|m|l|h|f> Set memory model         /zl<f|p|s> Suppress items in COFF\n"
 "/mz Generate DOS MZ binary file            /Zm Enable MASM 5.10 compatibility\n"
 "/nc<name> Set class name of code segment   /Zne Disable non Masm extensions\n"
 "/nd<name> Set name of data segment         /Znk Disable non Masm keywords\n"
 "/nm<name> Set name of module               /Zp[n] Set structure alignment\n"
 "/nt<name> Set name of text segment         /Zs Perform syntax check only\n"
 "/pe Generate PE binary file, 32/64-bit     /zt<0|1|2> Set STDCALL decoration\n"
 " /cui - subsystem:console (default)        /Zv8 Enable Masm v8+ PROC visibility\n"
 " /gui - subsystem:windows                  /zze No export symbol decoration\n"
 "/pf Preserve Flags (Epilogue/Invoke)       /zzs Store name of start address\n"
 "/q, /nologo Suppress copyright message     /Sa Maximize source listing\n"
 "/r Recurse subdirectories\n";
#endif

int banner_printed = 0;

void write_logo(void)
{
    if ( !banner_printed ) {
	banner_printed = 1;
	printf( "%s\n%s\n", cp_logo, cp_copyright );
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
