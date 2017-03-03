test.exe:
	asmc -pe -D_WIN64 -D__PE__ $*.asm
	$@ /pe WIN64 ASCII
	pause
	del $*.exe

