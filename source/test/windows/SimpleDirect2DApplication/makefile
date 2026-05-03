include srcpath

SimpleDirect2dApplication.exe:
	asmc64 -q -Cs -peg -ws -frame -I$(inc_dir) $*.asm
	$@
	del $@
	del sampleImage.jpg

vs:
	project -p -w -u SimpleDirect2dApplication

