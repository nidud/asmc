Ascii.exe:
	iddc DMain.idd
	iddc DHelp.idd
	asmc -q $*.asm
	linkw N $@ F %AsmcDir%\lib\c0, $*, DMain, DHelp
	del *.obj
