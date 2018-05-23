# Makefile for Asmc using Open Watcom

debug	= 0
regress = 0

watcom	= \watcom

!if $(debug)
CFLAG = -q -bc -bt=nt -3r -fpi87 -zc -od -d2 -w3 -hc
LOPTD = debug c op cvp, symfile lib user32.lib
!else
CFLAG = -q -bc -bt=nt -3s -fpi87 -zc -oxa -s
!endif

wasmc.exe:
 if exist *.obj del *.obj
 for %%q in (src\*.c) do $(watcom)\binnt\wcc386 -I$(watcom)\h -Isrc\h $(CFLAG) %%q
 $(watcom)\binnt\wcc386 -I$(watcom)\h -Isrc\h $(CFLAG) src\quadmath\atoquad.c
 $(watcom)\binnt\wlink @<<
format	windows pe runtime console
name	$@
Libpath $(watcom)\lib386\nt;$(watcom)\lib386
$(LOPTD)
op	quiet, stack=0x40000, heapsize=0x100000, map, norelocs
com	stack=0x1000
disable 171
sort	global
op	statics
Library kernel32.lib
file	{ *.obj }
<<
 del *.obj
!if $(regress)
 if not exist .\$*.exe exit
 cd regress
 runtest ..\..\$*.exe
!endif
