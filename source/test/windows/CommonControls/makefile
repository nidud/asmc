CommonControls.exe:
	if not exist res\error.ico (
		md res
		asmc64 -ws -pe resource.asm
		resource.exe
		del resource.exe
	)
	rc $*.rc
	asmc64 -q -ws -Cs -Zp8 $*.asm -link -res:$*.res
	$@
	del $*.res
	del $*.obj
	del $*.exe
	del $*.exe.manifest
vs:
	project -p -w -u CommonControls
