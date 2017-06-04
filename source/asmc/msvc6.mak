# Makefile for Asmc using MSVC Version 6

vcdir = \vc

debug = 0
regress = 0

libdir = $(vcdir)\lib
bindir = $(vcdir)\bin
incdir = $(vcdir)\include

lflags = /subsystem:console /libpath:$(libdir)
cflags = /c /Isrc\h /I$(incdir) /MT /GS- /GR-

!if $(debug)
cflags += /Zi
lflags += /debug
!else
cflags += /O2 /Ot /Ox /Og
!endif

asmc32.exe:
 $(bindir)\cl $(cflags) src\*.c
 $(bindir)\link /out:$@ $(lflags) *.obj
 del *.obj
!if $(regress)
 if not exist $@ exit
 cd regress
 runtest ..\..\$@
!endif

