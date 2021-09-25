#
# Makefile for Asmc
#
# Libraries used:
#  ../libs/import/ - kernel32.lib
#  ../libs/lib32/  - libc.lib
#  ../libs/crypt/  - crypt.lib
#

!include srcpath

ASMC = ..\..\bin\asmc
LINK = ..\..\bin\linkw
LFLAGS = op map libp $(lib_dir) symt _cstart lib crypt
AFLAGS = -q -Zp4 -coff -Cs -I$(srcpath)\src\h -I$(inc_dir)
!ifdef ASMC64
AFLAGS += -D__ASMC64__
!endif

srcpath = $(src_dir)\asmc
objects = \
    src\asmc.obj \
    src\asmerr.obj \
    src\assemble.obj \
    src\assert.obj \
    src\assume.obj \
    src\atofloat.obj \
    src\backptch.obj \
    src\bin.obj \
    src\branch.obj \
    src\class.obj \
    src\cmdline.obj \
    src\codegen.obj \
    src\coff.obj \
    src\com.obj \
    src\condasm.obj \
    src\context.obj \
    src\cpumodel.obj \
    src\data.obj \
    src\dbgcv.obj \
    src\directiv.obj \
    src\elf.obj \
    src\end.obj \
    src\enum.obj \
    src\equate.obj \
    src\expans.obj \
    src\expreval.obj \
    src\extern.obj \
    src\fastcall.obj \
    src\fastpass.obj \
    src\fixup.obj \
    src\for.obj \
    src\fpfixup.obj \
    src\hll.obj \
    src\Indirection.obj \
    src\input.obj \
    src\invoke.obj \
    src\label.obj \
    src\linnum.obj \
    src\listing.obj \
    src\logo.obj \
    src\loop.obj \
    src\lqueue.obj \
    src\ltype.obj \
    src\macro.obj \
    src\mangle.obj \
    src\mem2mem.obj \
    src\memalloc.obj \
    src\namespace.obj \
    src\new.obj \
    src\omf.obj \
    src\omffixup.obj \
    src\omfint.obj \
    src\operator.obj \
    src\option.obj \
    src\parser.obj \
    src\posndir.obj \
    src\pragma.obj \
    src\preproc.obj \
    src\proc.obj \
    src\regno.obj \
    src\reswords.obj \
    src\return.obj \
    src\safeseh.obj \
    src\segment.obj \
    src\simsegm.obj \
    src\string.obj \
    src\switch.obj \
    src\symbols.obj \
    src\tokenize.obj \
    src\typeid.obj \
    src\types.obj \
    src\undef.obj

all: targets

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
