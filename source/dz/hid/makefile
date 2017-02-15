#
# Creates helpid.inc from dz.txt
#
helpid.exe:
	asmc -q $*.asm
	linkw @<<
name	$@
option	q
option	m
file	{ ..\..\..\lib\c0 *.obj }
<<
	$@
	del $@
	del $*.map
	del $*.obj

