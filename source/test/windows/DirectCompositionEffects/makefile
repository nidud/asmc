include srcpath

CApplication.exe:
	asmc64 -ws -peg -frame -I$(inc_dir) $*.asm
	$@

vs:
	project -p -w -u CApplication

