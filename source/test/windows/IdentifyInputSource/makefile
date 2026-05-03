InputSource.exe:
	asmc64 -q -peg -ws -frame -I$(inc_dir) $*.asm
	$@
	pause
	del $@

vs:
	project -p -w -u InputSource
