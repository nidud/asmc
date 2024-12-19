include srcpath

XmlLiteReaderWriter.exe:
	asmc64 -q -Cs -ws -frame -I$(inc_dir) $*.asm
	$@ books.xml result.xml
	pause
	del $@
	del $*.obj

vs:
	project -p -u XmlLiteReaderWriter


