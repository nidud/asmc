test.exe:
	asmc -pe -ws -D_UNICODE -D__PE__ $*.asm
	$@
	del $@

