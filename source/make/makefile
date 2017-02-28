make.exe:
	asmc -q -Cs $*.asm
	linkw @<<
name	$@
option	q
option	m
Lib	libc
file	{ ..\..\lib\crt *.obj }
<<
	wrc -q res\$*.res $@
	del *.obj
