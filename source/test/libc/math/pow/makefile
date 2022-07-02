test.exe:
	asmc64 -q -pe $*.asm
	$@
	asmc64 -q $*.asm
	linkw sys con_64 file $*
	$@
	asmc -q $*.asm
	linkw sys con_32 file $*
	$@
	pause
	del *.obj
	del *.exe

