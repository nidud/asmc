LIBDIR = %AsmcDir%\lib\x64
INCDIR = %AsmcDir%\include

$(LIBDIR)\c0.obj:
	asmc -nologo -I$(INCDIR) -win64 -D_WIN64 -Fo $(LIBDIR)\c0.obj crt.asm
	asmc -nologo -I$(INCDIR) -win64 -D_WIN64 -Fo $(LIBDIR)\c0c.obj crtc.asm
	asmc -nologo -I$(INCDIR) -win64 -D_WIN64 -Fo $(LIBDIR)\c0dll.obj crtdll.asm
	asmc -nologo -I$(INCDIR) -win64 -D_WIN64 -DDEBUG -Zi -Fo $(LIBDIR)\c0d.obj crt.asm
	asmc -nologo -I$(INCDIR) -win64 -D_WIN64 -DDEBUG -Zi -Fo $(LIBDIR)\c0cd.obj crtc.asm
	asmc -nologo -I$(INCDIR) -win64 -D_WIN64 -DDEBUG -Zi -Fo $(LIBDIR)\c0dlld.obj crtdll.asm
	libw -q -t -s -b -n -c -fac $(LIBDIR)\crt.lib $(LIBDIR)\c0.obj

