
_aligned_malloc.exe:
	asmc -q -DDEBUG -D_WIN64 -win64 $*.asm
	linkw @<<
Option	q
SYMT	mainCRTStartup
LibPath \Asmc\lib\x64
Lib	crt, libc, kernel32
File	$*.obj
<<
	del $*.obj
	$@
