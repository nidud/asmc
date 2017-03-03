test.exe:
	asmc -pe -ws -D_UNICODE -D_WIN64 -D__PE__ $*.asm
	$@ /pe WIN64 UNICODE
	pause
	del $*.exe

