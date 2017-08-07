#include <stdio.h>
#include <globals.h>

char cp_logo[] =
 "Asmc Macro Assembler Version " ASMC_VERSSTR "G\n"
 "Portions Copyright (c) 1992-2002 Sybase, Inc. All Rights Reserved.\n\n";

static char cp_usage[] =
 "USAGE: ASMC [ options ] filelist\n"
 "Use option /? for more info\n";

static char cp_options[] =

 "         ASMC [ /options ] filelist\n"
 "\n"
 "/<0|1|..|10>[p] Set CPU: 0=8086 (default), 1=80186, 2=80286, 3=80386, 4=80486,\n"
 " 5=Pentium,6=PPro,7=P2,8=P3,9=P4,10=x86-64; <p> allows privileged instructions\n"
 "/bin Generate plain binary file            /Sg Display generated code in listing\n"
 "/Cs C stack: push USER regs first          /Sn Suppress symbol-table listing\n"
 "/coff Generate COFF format object file     /Sp[n] Set segment alignment\n"
 "/C<p|u|x> Set OPTION CASEMAP               /swc C .SWITCH (default)\n"
 "/D<name>[=text] Define text macro          /swn No table in .SWITCH (default)\n"
 "/e<number> Set error limit number          /swp Pascal .SWITCH (auto.break)\n"
 "/elf Generate 32-bit ELF object file       /swr Use reg [R|E]AX in switch code\n"
 "/elf64 Generate 64-bit ELF object file     /swt Use table in .SWITCH\n"
 "/EP Output preprocessed listing to stdout  /Sx List false conditionals\n"
 "/eq Don't display error messages           /w Same as /W0 /WX\n"
 "/Fd[file] Write import definition file     /W<number> Set warning level\n"
 "/Fi<file> Force <file> to be included      /win64 Generate 64-bit COFF object\n"
 "/Fl[file] Generate listing                 /ws Store quoted strings as unicode\n"
 "/Fo<file> Name object file                 /WX Treat all warnings as errors\n"
 "/Fw<file> Set errors file name             /X Ignore INCLUDE environment path\n"
 "/FPi Generate 80x87 emulator encoding      /Xc Disable ASMC extensions\n"
 "/FPi87 80x87 instructions (default)        /zcw No decoration for C symbols\n"
 "/fpc Disallow floating-point instructions  /Zd Add line number debug info\n"
 "/fp<n> Set FPU: 0=8087, 2=80287, 3=80387   /Zf Make all symbols public\n"
 "/G<c|d|z> Use Pascal, C, or Stdcall calls  /zf<0|1> Set FASTCALL type: MS/OW\n"
 "/I<name> Add include path                  /Zg Generate code to match Masm\n"
 "/m<t|s|c|m|l|h|f> Set memory model         /Zi[0|1|2|3] Add symbolic debug info\n"
 "/mz Generate DOS MZ binary file            /zlc No OMF records of data in code\n"
 "/nc<name> Set class name of code segment   /zld No OMF records of far call\n"
 "/nd<name> Set name of data segment         /zl<f|p|s> Suppress items in COFF\n"
 "/nm<name> Set name of module               /Zm Enable MASM 5.10 compatibility\n"
 "/nt<name> Set name of text segment         /Zne Disable non Masm extensions\n"
 "/pe Generate PE binary file, 32/64-bit     /Zp[n] Set structure alignment\n"
 "/pf Preserve Flags (Epilogue/Invoke)       /Zs Perform syntax check only\n"
 "/q, /nologo Suppress copyright message     /zt<0|1|2> Set STDCALL decoration\n"
 "/r Recurse subdirectories                  /Zv8 Enable Masm v8+ PROC visibility\n"
 "/Sa Maximize source listing                /zze No export symbol decoration\n"
 "/safeseh Assert exception handlers         /zzs Store name of start address\n"
 "/Sf Generate first pass listing";

int banner_printed = 0;

void write_logo(void)
{
    if ( !banner_printed ) {
	banner_printed = 1;
	printf( cp_logo );
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
