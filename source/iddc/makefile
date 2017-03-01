iddc.exe:
	asmc -q $*.asm
	linkw @<<
name	$@
option	q
option	m
lib	libc
file	{ ..\..\lib\crt *.obj }
<<

	del *.obj
