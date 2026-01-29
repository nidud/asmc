
include srcpath

SaveAsImageFileSample.exe:
	asmc64 -q -Cs -pe -ws -frame -I$(inc_dir) $*.asm
	$@
	pause
	del $@

vs:
	project -p -u SaveAsImageFileSample


