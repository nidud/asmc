include srcpath

Direct2DHelloWorld.exe:
	asmc64 -q -peg -ws -frame -I$(inc_dir) $*.asm
	$@
	pause
	del $@

vs:
	project -p -u Direct2DHelloWorld

