CApplication.exe:
	asmc64 -q -ws $*.asm
	$@
	del $@
	del $*.obj

vs:
	project -p -w -u CApplication
