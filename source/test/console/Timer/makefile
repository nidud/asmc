Timer.exe:
	iddc -r *.idd
	asmc -q $*.asm
	linkw N $@ F %AsmcDir%\lib\c0, *.obj
	del *.obj

