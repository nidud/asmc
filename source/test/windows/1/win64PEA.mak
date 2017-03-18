test.exe:
	asmc -pe -D_WIN64 -D__PE__ $*.asm
	$@
	del $@

