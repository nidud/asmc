make.exe:
	asmc -q $*.asm
	linkw @<<
name	$@
option	q
option	m
file	{ ..\..\lib\c0 *.obj }
<<
	del *.obj
