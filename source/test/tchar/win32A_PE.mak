test.exe:
	asmc -pe -D__PE__ $*.asm
	$@ /pe WIN32 ASCII
	pause
	del $*.exe

