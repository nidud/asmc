test.exe:
	asmc64 -q $*.asm
	linkw sys con_64 file $*
	$@
	pause
	asmc64 -q -pe $*.asm
	$@
	pause
	del *.obj
	del *.exe

