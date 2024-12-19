include srcpath

GeometryRealizationSample.exe:
	asmc64 -q -Cs -peg -ws -frame -I$(inc_dir) $*.asm
	$@
	del $@

vs:
	project -p -w -u GeometryRealizationSample

