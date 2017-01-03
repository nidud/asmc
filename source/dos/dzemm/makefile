
LIBDIR = %AsmcDir%\lib

dzemm.sys: dzemm.dll
	asmc -bin -Fo dzemm.sys dzemm.asm
dzemm.dll:
	asmc -Fo dzemm.obj dzemmd.asm
	linkw format win pe dll libp $(LIBDIR) file dzemm.obj
	del $*.obj

