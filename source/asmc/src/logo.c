#include <stdio.h>
#include <globals.h>

char cp_logo[] =
 "Asmc Macro Assembler Version " ASMC_VERSSTR ".27\n"
 "Portions Copyright (c) 1992-2002 Sybase, Inc. All Rights Reserved.\n\n";

static char cp_usage[] =
 "USAGE: ASMC [ options ] filelist\n"
 "Use option /? for more info\n";

static char cp_options[] =

 "         ASMC [ /options ] filelist\n"
 "\n"
 "/<0|1|..|10>[p] Set CPU: 0=8086 (default), 1=80186, 2=80286, 3=80386, 4=80486,\n"
 " 5=Pentium,6=PPro,7=P2,8=P3,9=P4,10=x86-64; <p> allows privileged instructions\n"
 "/assert Generate .assert() code            /safeseh Assert exception handlers\n"
 "/autostack Auto stack space for arguments  /Sf Generate first pass listing\n"
 "/bin Generate plain binary file            /Sg Display generated code in listing\n"
 "/Cs C stack: push USER regs first          /Sn Suppress symbol-table listing\n"
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
 "/FPi87 80x87 instructions (default)        /Xc Disable ASMC extensions\n"
 "/fpc Disallow floating-point instructions  /zcw No decoration for C symbols\n"
 "/fp<n> Set FPU: 0=8087, 2=80287, 3=80387   /Zd Add line number debug info\n"
 "/G<cdzv> Pascal, C, Stdcall or Vectorcall  /Zf Make all symbols public\n"
 "/homeparams Copy Reg. parameters to Stack  /zf<0|1> Set FASTCALL type: MS/OW\n"
 "/I<name> Add include path                  /Zg Generate code to match Masm\n"
 "/m<t|s|c|m|l|h|f> Set memory model         /Zi[0|1|2|3] Add symbolic debug info\n"
 "/mz Generate DOS MZ binary file            /zlc No OMF records of data in code\n"
 "/nc<name> Set class name of code segment   /zld No OMF records of far call\n"
 "/nd<name> Set name of data segment         /zl<f|p|s> Suppress items in COFF\n"
 "/nm<name> Set name of module               /Zm Enable MASM 5.10 compatibility\n"
 "/nt<name> Set name of text segment         /Zne Disable non Masm extensions\n"
 "/pe Generate PE binary file, 32/64-bit     /Zp[n] Set structure alignment\n"
 " /cui - subsystem:console (default)        /Zs Perform syntax check only\n"
 " /gui - subsystem:windows                  /zt<0|1|2> Set STDCALL decoration\n"
 "/pf Preserve Flags (Epilogue/Invoke)       /Zv8 Enable Masm v8+ PROC visibility\n"
 "/q, /nologo Suppress copyright message     /zze No export symbol decoration\n"
 "/r Recurse subdirectories                  /zzs Store name of start address\n"
 "/Sa Maximize source listing\n";

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
