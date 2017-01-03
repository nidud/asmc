LIBDIR = %AsmcDir%\lib\x64

Exception.exe:
	asmc -q -D_WIN64 -win64 $*.asm
	linkw @<<
Option	q
SYMT	mainCRTStartup
LibPath $(LIBDIR)
Lib	crt, libc, kernel32
File	$*.obj
<<
	del $*.obj
	$@
	pause
