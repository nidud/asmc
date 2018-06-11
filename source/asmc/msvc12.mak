# Makefile for Asmc using MSVC Version 12

vsdir = \vc12\bin\amd64
incdir = \asmc\include

debug = 0
regress = 0

cflags = /c /Isrc\h /I$(incdir) /GS- /GR- /D_LIBC
!if $(debug)
cflags += /Zi
!else
cflags += /O2 /Ot /Ox
!endif

asmc64.exe:
    if exist *.obj del *.obj
    $(vsdir)\cl $(cflags) src\*.c
    asmc -q -win64 -Fo src\ImageBase\ImageBase.obj src\ImageBase\ImageBase.asm
    asmc -q -win64 -Isrc\h src\x64\*.asm
    linkw system con_64 name $@ file { src\ImageBase\ImageBase.obj *.obj }
    del *.obj
!if $(regress)
    if not exist $@ exit
    cd regress
    runtest ..\..\asmc64.exe
!endif
