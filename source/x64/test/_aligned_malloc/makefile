LIBDIR = %AsmcDir%\lib\x64

_aligned_malloc.exe:
	asmc -q -DDEBUG -D_WIN64 -win64 $*.asm
	linkw @<<
Option	q
SYMT	mainCRTStartup
LibPath $(LIBDIR)
Lib	crt, libc, kernel32
File	$*.obj
<<
	del $*.obj
	$@
