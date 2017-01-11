_getch.exe:
	asmc -q $*.asm
	linkw N $@ F %AsmcDir%\lib\c0, $*
	del $*.obj
	$@
	pause


