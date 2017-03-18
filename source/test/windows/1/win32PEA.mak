test.exe:
	asmc -pe -D__PE__ $*.asm
	$@
	del $@

