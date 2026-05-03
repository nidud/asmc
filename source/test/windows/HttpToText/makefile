include srcpath

HttpToText.exe:
	asmc64 -ws -pe -I$(inc_dir) $*.asm
	$@ https://github.com/nidud/asmc/tree/master/source/test/Microsoft/msdn/HttpToText
	pause
	del $@

vs:
	project -p -u HttpToText

