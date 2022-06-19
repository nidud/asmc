#
# Makefile for Asmc
#
# Libraries used:
#  ../libs/import/ - kernel32.lib
#  ../libs/lib32/  - libc.lib
#

NAME = asmc
LIBD = x86
FLAG = -Zp4 -coff

!ifdef x64
LIBD = x64
FLAG = -frame -Zp8 -win64
!endif

!ifdef ASMC64
NAME = asmc64
FLAG += -DASMC64
!endif

OBJS =  asmc.obj        \
        asmerr.obj      \
        assemble.obj    \
        assert.obj      \
        assume.obj      \
        backptch.obj    \
        bin.obj         \
        branch.obj      \
        class.obj       \
        cmdline.obj     \
        codegen.obj     \
        coff.obj        \
        com.obj         \
        condasm.obj     \
        context.obj     \
        cpumodel.obj    \
        data.obj        \
        dbgcv.obj       \
        directiv.obj    \
        elf.obj         \
        end.obj         \
        enum.obj        \
        equate.obj      \
        expans.obj      \
        expreval.obj    \
        extern.obj      \
        fastcall.obj    \
        fastpass.obj    \
        fixup.obj       \
        for.obj         \
        fpfixup.obj     \
        hll.obj         \
        Indirection.obj \
        input.obj       \
        invoke.obj      \
        label.obj       \
        linnum.obj      \
        listing.obj     \
        logo.obj        \
        loop.obj        \
        lqueue.obj      \
        ltype.obj       \
        macro.obj       \
        mangle.obj      \
        mem2mem.obj     \
        memalloc.obj    \
        namespace.obj   \
        new.obj         \
        omf.obj         \
        omffixup.obj    \
        omfint.obj      \
        operator.obj    \
        option.obj      \
        parser.obj      \
        posndir.obj     \
        pragma.obj      \
        preproc.obj     \
        proc.obj        \
        qfloat.obj      \
        reswords.obj    \
        return.obj      \
        safeseh.obj     \
        segment.obj     \
        simsegm.obj     \
        string.obj      \
        switch.obj      \
        symbols.obj     \
        tokenize.obj    \
        typeid.obj      \
        types.obj       \
        undef.obj

{src}.asm.obj:
        ..\..\bin\asmc $(FLAG) -q -Cs -Iinc -I..\..\include $<

$(NAME).exe: $(OBJS)
        ..\..\bin\linkw @<<
libpath ..\..\lib\$(LIBD)
name    $@
symt    _cstart
option  q, stack=0x300000 com stack=0x200000
file    { *.obj }
<<
        del *.obj

