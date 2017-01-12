_getch.exe:
	asmc -q -win64 -D_WIN64 $*.asm
	linkw N $@ LibP %AsmcDir%\lib\x64 F %AsmcDir%\lib\x64\c0, $*
	del $*.obj
	$@
	pause


