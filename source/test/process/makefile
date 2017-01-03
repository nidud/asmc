system.exe:
	asmc -q $*.asm
	linkw OP q N $@ F ..\..\..\lib\c0, $*.obj
	del $*.obj
	$@
	pause


