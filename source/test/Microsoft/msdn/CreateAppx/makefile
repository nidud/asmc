CreateAppx.exe:
	asmc64 -q -ws $*.asm
	$@
	pause
	del $*.obj
	del $@

vs:
	project -p -u CreateAppx

