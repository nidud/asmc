!include x64/srcpath

_getch.exe:
	asmc -q -win64 -D_WIN64 $*.asm
	linkw @<<
Name	$@
LibPath $(lib_dir)
Lib	kernel32, libc
File	$(lib_dir)\crt, $*
<<
	del $*.obj
	$@
	pause


