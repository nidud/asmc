Timer.exe:
	iddc -r *.idd
	asmc -q $*.asm
	linkw N $@ F %lib%\c0, *.obj
	del *.obj

