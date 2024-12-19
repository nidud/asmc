include srcpath

EnumClipboard.exe:
	asmc64 -q -pe -ws -frame -I$(inc_dir) $*.asm
	$@
	pause
	del $@

vs:
	project -p -u EnumClipboard
