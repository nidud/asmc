UiaSimpleProvider.exe:
	rc UiaSimpleProvider.rc
	asmc -coff -ws -Cs -Fe$* *.asm -link -res:$*.res
	asmc -win6 -ws -Cs -Fe$*64 *.asm -link -res:$*.res
	$@
	del *.res
	del *.obj
vs:
	project -p -w -u -rUiaSimpleProvider UiaSimpleProvider
