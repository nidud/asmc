#
# Makefile for LIBW using Open Watcom
#

OW    = \WATCOM

OBJS  = wlib.obj     libio.obj	  symtable.obj omfproc.obj  writelib.obj convert.obj &
	wlibutil.obj libwalk.obj  symlist.obj  proclib.obj  cmdline.obj	 error.obj &
	implib.obj   elfobjs.obj  orlrtns.obj  memfuncs.obj ideentry.obj idedrv.obj &
	idemsgfm.obj idemsgpr.obj maindrv.obj  demangle.obj omfutil.obj	 coffwrt.obj &
	inlib.obj    debug.obj

OWOBJ = orlentry.obj orlflhnd.obj orlhash.obj &
	coffentr.obj coffflhn.obj coffimpl.obj coffload.obj cofflwlv.obj &
	elfentr.obj  elfflhn.obj  elfload.obj  elflwlv.obj &
	omfdrctv.obj omfentr.obj  omfflhn.obj  omfload.obj  omfmunge.obj

$(BIN)libw.exe: $(OBJS)
	wlink format win pe ru console name $@ @<<
OP q, norelocs, map=$*, stack=0x100000, heapsize=0x100000 com stack=0x1000
LIBP $(OW)\lib386
LIBP $(OW)\lib386\nt
L { ..\lib\ow kernel32 user32 clib3r }
F { $(OBJS) }
<<
	@del *.obj

{src}.c.obj:
	wcc386 -q -zc -bc -bt=nt -ox -s -DNDEBUG -DIDE_PGM -I$(OW)\h;src\h;..\lib\src\h $<

