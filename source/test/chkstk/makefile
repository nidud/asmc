test.exe:
	asmc /Ge $*.asm
	linkw system con_32 file $*
	$@
	asmc64 /Ge $*.asm
	linkw system con_64 file $*
	$@
	pause


