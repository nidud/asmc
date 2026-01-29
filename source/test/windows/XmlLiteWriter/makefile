include srcpath

XmlLiteWriter.exe:
	asmc64 -q -Cs -ws -frame -I$(inc_dir) $*.asm
	$@ test.xml
	pause
	del $@
	del $*.obj

vs:
	project -p -u XmlLiteWriter
