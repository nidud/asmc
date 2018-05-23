# Makefile for Microsoft (R) C/C++ Optimizing Compiler Version 18 and LIB64

bindir = \vc12\bin\amd64
incdir = \asmc\include
cflags = /c /I$(incdir) /GS- /GR- /O2 /Ot /Ox

test.exe:
    $(bindir)\cl $(cflags) $*.c
    asmc -q -win64 base.asm
    linkw name $@ op map system con_64 file base, $*
