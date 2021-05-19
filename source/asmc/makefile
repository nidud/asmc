#
# Makefile for Asmc using Open Watcom v1.9.
#
# Libraries used (MAKE):
#  ../libs/import/makefile - kernel32.lib
#  ../libs/lib32/makefile  - libc.lib
#  ../libs/crypt/makefile  - crypt.lib
#

# Open Watcom root directory

!ifndef WATCOM
!ifeq [] [%WATCOM%]
WATCOM = \watcom
!else
WATCOM = %WATCOM%
!endif
!endif

!include srcpath

ASMC = ..\..\bin\asmc
LINK = ..\..\bin\linkw
LFLAGS = op map libp $(lib_dir) symt _cstart lib crypt
AFLAGS = -q -Zp4 -coff -Cs -I$(srcpath)\src\h -I$(inc_dir)
CFLAGS = -q -ez -D_LIBC -D_ASMC -I$(srcpath)\src\h -I$(inc_dir) -d2 -bt=nt -bc -ecc -3r -ox -s
!ifdef ASMC64
AFLAGS += -D__ASMC64__
CFLAGS += -D__ASMC64__
!endif

srcpath = $(src_dir)\asmc
objects = \
    src\X86\asmc.obj \
    src\X86\asmerr.obj \
    src\X86\assemble.obj \
    src\X86\assert.obj \
    src\X86\assume.obj \
    src\X86\atofloat.obj \
    src\X86\backptch.obj \
    src\X86\bin.obj \
    src\X86\branch.obj \
    src\X86\class.obj \
    src\X86\cmdline.obj \
    src\X86\codegen.obj \
    src\X86\coff.obj \
    src\X86\condasm.obj \
    src\X86\context.obj \
    src\X86\cpumodel.obj \
    src\X86\data.obj \
    src\X86\dbgcv.obj \
    src\X86\directiv.obj \
    src\elf.obj \
    src\X86\end.obj \
    src\X86\enum.obj \
    src\X86\equate.obj \
    src\X86\expans.obj \
    src\X86\expreval.obj \
    src\extern.obj \
    src\X86\fastcall.obj \
    src\X86\fastpass.obj \
    src\X86\fixup.obj \
    src\X86\for.obj \
    src\X86\fpfixup.obj \
    src\X86\hll.obj \
    src\X86\input.obj \
    src\X86\invoke.obj \
    src\X86\label.obj \
    src\X86\linnum.obj \
    src\listing.obj \
    src\X86\logo.obj \
    src\X86\loop.obj \
    src\X86\lqueue.obj \
    src\X86\ltype.obj \
    src\X86\macro.obj \
    src\X86\mangle.obj \
    src\X86\mem2mem.obj \
    src\X86\memalloc.obj \
    src\X86\new.obj \
    src\omf.obj \
    src\X86\omffixup.obj \
    src\X86\omfint.obj \
    src\X86\option.obj \
    src\X86\parser.obj \
    src\X86\posndir.obj \
    src\X86\pragma.obj \
    src\X86\preproc.obj \
    src\proc.obj \
    src\X86\regno.obj \
    src\X86\reswords.obj \
    src\X86\return.obj \
    src\X86\safeseh.obj \
    src\segment.obj \
    src\X86\simsegm.obj \
    src\X86\string.obj \
    src\X86\switch.obj \
    src\X86\symbols.obj \
    src\X86\tokenize.obj \
    src\X86\types.obj \
    src\X86\undef.obj

all: targets

{$(srcpath)}.c.obj:
    $(WATCOM)\binnt\wcc386 $(CFLAGS) $<

{$(srcpath)}.asm.obj:
    $(ASMC) $(AFLAGS) $<

asmc.exe: $(objects)
    $(LINK) name $@ $(LFLAGS) file { *.obj }
    del *.obj

asmc64.exe: $(objects)
    $(LINK) name $@ $(LFLAGS) file { *.obj }
    del *.obj

targets:
    echo output:
    echo asmc.exe
    make asmc.exe
    echo asmc64.exe
    make ASMC64=1 asmc64.exe
