#
# Makefile for LIBC using Visual C
#
VC = \VC

objs = \
    wlib.obj	 libio.obj    symtable.obj omfproc.obj  writelib.obj convert.obj \
    wlibutil.obj libwalk.obj  symlist.obj  proclib.obj  cmdline.obj  error.obj	 \
    implib.obj	 elfobjs.obj  orlrtns.obj  memfuncs.obj ideentry.obj idedrv.obj  \
    idemsgfm.obj idemsgpr.obj maindrv.obj  demangle.obj omfutil.obj  coffwrt.obj \
    inlib.obj	 debug.obj

libw.exe: $(objs)
	link /out:$@ /debug /libpath:$(VC)\lib /subsystem:console ..\lib\owd.lib *.obj
	@del *.obj

{src}.c.obj:
	cl -D__NT__ -c -nologo -I..\lib\src\h -Isrc\h -I$(VC)\include -Zi -Od -DIDE_PGM -DDEBUG_OUT $<

{src}.asm.obj:
	asmc -q -coff $<
