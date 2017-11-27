#
# Makefile for LINKW
#
WATCOM  = \WATCOM
MSVC	= \VC
!ifdef CXX
debug	= 1
!endif

OUTP	= .

!ifdef debug
#OUTP	= .
OWLIB	= ..\lib\owd
CC	= $(MSVC)\bin\cl
CFLAGS  = -c -q -Zi -Od -DINSIDE_WLINK -DIDE_PGM -Isrc\h -I..\lib\src\h -I$(MSVC)\include
LINK	= link
LFLAGS  = /out:$@ /debug /libpath:$(MSVC)\lib /subsystem:console
!else
#OUTP	= \dz\bin
OWLIB	= ..\lib\ow
CC	= $(WATCOM)\binnt\wcc386
CFLAGS  = -q -zc -bc -bt=nt -ox -s -DINSIDE_WLINK -DNDEBUG -DIDE_PGM -I..\lib\src\h -I$(WATCOM)\h;src\h
LINK	= wlink
LFLAGS  = format win pe ru console name $@
!endif

linkw_objs = \
	autogrp.obj	carve.obj	wcomdef.obj	cmd16m.obj   \
	cmdall.obj	cmddos.obj	cmdelf.obj	cmdline.obj  \
	cmdnov.obj	cmdos2.obj	cmdphar.obj	cmdtable.obj \
	cmdutils.obj	cmdqnx.obj	dbgall.obj	dbgcv.obj    \
	dbgdwarf.obj	dbginfo.obj	debug.obj	distrib.obj  \
	global.obj	hash.obj	impexp.obj	libr.obj     \
	libsupp.obj	linkutil.obj	load16m.obj	loaddos.obj  \
	loadelf.obj	loadelf2.obj	loadfile.obj	loadflat.obj \
	loadnov.obj	loados2.obj	loadpe.obj	loadphar.obj \
	loadqnx.obj	loadraw.obj	lsymtab.obj	mapio.obj    \
	mem.obj		mixcache.obj	msg.obj		objio.obj    \
	obj2supp.obj	objcalc.obj	objfree.obj	objnode.obj  \
	objomf.obj	objorl.obj	objpass1.obj	objpass2.obj \
	objstrip.obj	omfreloc.obj	overlays.obj	ovlsupp.obj  \
	permdata.obj	procfile.obj	reloc.obj	ring.obj     \
	ring2.obj	salloc.obj	spillio.obj	strtab.obj   \
	symmem.obj	symtrace.obj	toc.obj		wlink.obj    \
	wlnkmsg.obj	cmdraw.obj	demangle.obj	exerespe.obj \
	sharedio.obj	rcstr.obj	ntio.obj	virtpage.obj	

$(OUTP)\linkw.exe: $(linkw_objs)
	$(LINK) $(LFLAGS) @<<
!ifdef debug
$(linkw_objs)
$(OWLIB).lib
!else
LIBP $(WATCOM)\lib386\nt
OP q, norelocs, map, stack=0x100000, heapsize=0x100000 com stack=0x1000
L { $(OWLIB) kernel32 user32 clib3r }
F { $(linkw_objs) }
!endif
<<
	@del *.obj

{src}.c.obj:
	$(CC) $(CFLAGS) $<


