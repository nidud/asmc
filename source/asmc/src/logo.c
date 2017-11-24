#include <stdio.h>
#include <globals.h>

char cp_logo[] =
 "Asmc Macro Assembler Version " ASMC_VERSSTR "L\n"
 "Portions Copyright (c) 1992-2002 Sybase, Inc. All Rights Reserved.\n\n";

static char cp_usage[] =
 "USAGE: ASMC [ options ] filelist\n"
 "Use option /? for more info\n";

static char cp_options[] =

 "         ASMC [ /options ] filelist\n"
 "\n"
 "/<0|1|..|10>[p] Set CPU: 0=8086 (default), 1=80186, 2=80286, 3=80386, 4=80486,\n"
 " 5=Pentium,6=PPro,7=P2,8=P3,9=P4,10=x86-64; <p> allows privileged instructions\n"
 "/bin Generate plain binary file            /Sf Generate first pass listing\n"
 "/Cs C stack: push USER regs first          /Sg Display generated code in listing\n"
 "/coff Generate COFF format object file     /Sn Suppress symbol-table listing\n"
 "/C<p|u|x> Set OPTION CASEMAP               /Sp[n] Set segment alignment\n"
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
 "/FPi87 80x87 instructions (default)        /Xc Disable ASMC extensions\n"
 "/fpc Disallow floating-point instructions  /zcw No decoration for C symbols\n"
 "/fp<n> Set FPU: 0=8087, 2=80287, 3=80387   /Zd Add line number debug info\n"
 "/G<c|d|z> Use Pascal, C, or Stdcall calls  /Zf Make all symbols public\n"
 "/I<name> Add include path                  /zf<0|1> Set FASTCALL type: MS/OW\n"
 "/m<t|s|c|m|l|h|f> Set memory model         /Zg Generate code to match Masm\n"
 "/mz Generate DOS MZ binary file            /Zi[0|1|2|3] Add symbolic debug info\n"
 "/nc<name> Set class name of code segment   /zlc No OMF records of data in code\n"
 "/nd<name> Set name of data segment         /zld No OMF records of far call\n"
 "/nm<name> Set name of module               /zl<f|p|s> Suppress items in COFF\n"
 "/nt<name> Set name of text segment         /Zm Enable MASM 5.10 compatibility\n"
 "/pe Generate PE binary file, 32/64-bit     /Zne Disable non Masm extensions\n"
 " /cui - subsystem:console (default)        /Zp[n] Set structure alignment\n"
 " /gui - subsystem:windows		     /Zs Perform syntax check only\n"
 "/pf Preserve Flags (Epilogue/Invoke)       /zt<0|1|2> Set STDCALL decoration\n"
 "/q, /nologo Suppress copyright message     /Zv8 Enable Masm v8+ PROC visibility\n"
 "/r Recurse subdirectories                  /zze No export symbol decoration\n"
 "/Sa Maximize source listing                /zzs Store name of start address\n"
 "/safeseh Assert exception handlers\n";

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
