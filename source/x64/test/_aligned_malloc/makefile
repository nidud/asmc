!include x64/srcpath

_aligned_malloc.exe:
	asmc -q -DDEBUG -D_WIN64 -win64 $*.asm
	linkw @<<
Name	$@
Option	q
LibPath $(lib_dir)
Lib	libc, kernel32
File	$(lib_dir)\crt, $*.obj
<<
	$@
	del $*.obj
#	del $*.exe
