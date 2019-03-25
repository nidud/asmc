test.exe:
	asmc -chkstk $*.asm
	linkw system con_32 file $*
	$@
	asmc64 -chkstk $*.asm
	linkw system con_64 file $*
	$@
	pause


