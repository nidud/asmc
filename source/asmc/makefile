#
# Makefile for Asmc
#

NAME = asmc
FLAG = -Zp8 -win64 -frame
LIBP = x64
!ifdef x86
FLAG = -Zp4 -coff
LIBP = x86
!endif
!ifdef ASMC64
NAME = asmc64
FLAG += -DASMC64
!endif
!ifndef OUTP
OUTP = .
!endif

$(OUTP)\$(NAME).exe:
        del *.obj
        ..\..\bin\$(NAME) $(FLAG) -Cs -Iinc -I..\..\include src\*.asm
        ..\..\bin\linkw @<<
libpath ..\..\lib\$(LIBP)
name    $@
symt    _cstart
option  stack=0x300000 com stack=0x200000
file    { *.obj }
<<
        del *.obj
