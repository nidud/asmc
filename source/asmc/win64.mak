# Makefile for Asmc64 using Visual C Version 18 (VS 12)

vsdir = \vc12\bin\amd64
incdir = \asmc\include

cflags = /c /Isrc\h /I$(incdir) /GS- /GR- /D_LIBC /D__ASMC64__ /O2 /Ot /Ox

asmc64.exe:
    if exist *.obj del *.obj
    $(vsdir)\cl $(cflags) src\*.c
    asmc -q -win64 -Fo src\ImageBase\ImageBase.obj src\ImageBase\ImageBase.asm
    asmc -q -win64 -Isrc\h src\x64\*.asm
    linkw system con_64 name $@ file { src\ImageBase\ImageBase.obj *.obj }
    del *.obj
