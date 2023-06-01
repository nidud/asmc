signal.exe:
	asmc $*.asm
	linkw system con_32 file $*
	$@
	pause
	asmc64 $*.asm
	linkw system con_64 file $*
	$@
	pause
	del $*.obj
	del $*.exe
