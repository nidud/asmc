HashComputation.exe:
	asmc64 -q -ws -frame $*.asm
	$@
	pause
	del $*.obj
	del $@

vs:
	project -p -u HashComputation

