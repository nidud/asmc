test.exe:
	asmc -pe -ws -D_UNICODE -D__PE__ $*.asm
	$@ /pe WIN32 UNICODE
	pause
	del $*.exe

