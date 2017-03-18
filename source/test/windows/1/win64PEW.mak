test.exe:
	asmc -pe -ws -D_WIN64 -D_UNICODE -D__PE__ $*.asm
	$@
	del $@

