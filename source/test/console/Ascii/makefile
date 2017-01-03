Ascii.exe:
	iddc DMain.idd
	iddc DHelp.idd
	asmc -q $*.asm
	linkw N $@ F %LIB%\c0, $*.obj, DMain.obj, DHelp.obj
	del *.obj
