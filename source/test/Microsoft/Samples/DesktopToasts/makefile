include srcpath

DesktopToastsSample.exe:
	asmc64 -q -peg -ws -frame -I$(inc_dir) $*.asm
	asmc64 -q -pe -ws -frame uninstall.asm
	pause

vs:
	project -p -w -u DesktopToastsSample
