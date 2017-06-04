# Makefile for Asmc using MSVC Version 12

vcdir = \vc12

amd64 = 1
debug = 0
regress = 0

!if $(amd64)
target = asmc64
libdir = $(vcdir)\lib\amd64
bindir = $(vcdir)\bin\amd64
!else
target = asmc32
libdir = $(vcdir)\lib
bindir = $(vcdir)\bin
!endif
incdir = $(vcdir)\include
lflags = /subsystem:console /libpath:$(libdir)
cflags = /c /Isrc\h /I$(incdir) /MT /GS- /GR-
!if $(debug)
cflags += /Zi
lflags += /debug
!else
cflags += /O2 /Ot /Ox /Og
!endif

$(target).exe:
 $(bindir)\cl $(cflags) src\*.c
 $(bindir)\link /out:$@ $(lflags) *.obj
 del *.obj
!if $(regress)
 if not exist $@ exit
 cd regress
 runtest ..\..\$@
!endif
