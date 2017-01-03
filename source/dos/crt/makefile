LIBDIR = %AsmcDir%\lib

$(LIBDIR)\C0l.obj:
	asmc -nologo -Fo $(LIBDIR)\c0l.obj -D__l__ crt.asm
	asmc -nologo -Fo $(LIBDIR)\w0l.obj -D__l__ -D__WCC__ crt.asm
	asmc -nologo -Fo $(LIBDIR)\c0fl.obj -DDEBUG -D__l__ -Zd crt.asm
