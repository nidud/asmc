LIBDIR = %AsmcDir%\lib\x64

Exception.exe:
	asmc -q -D_WIN64 -win64 $*.asm
	linkw Name $@ @<<
Option	q
LibPath $(LIBDIR)
Lib	libc, kernel32
File	$(LIBDIR)\crt, $*.obj
<<
	del $*.obj
	$@
	pause
