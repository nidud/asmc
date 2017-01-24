LIBDIR = %AsmcDir%\lib

Exception.exe:
	asmc -q $*.asm
	linkw @<<
Name	$@
Option	q
LibPath $(LIBDIR)
Lib	libo, kernel32
File	$(LIBDIR)\c0, $*.obj
<<
	del $*.obj
	$@
	pause

