test.exe:
	asmc -q $*.asm
	linkw sys con_32 file $*
	$@
	asmc64 -q $*.asm
	linkw sys con_64 file $*
	$@
	asmc64 -q -pe $*.asm
	$@
	pause
	del *.exe
	del *.obj

