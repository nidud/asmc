Timer.exe:
	iddc -r *.idd
	asmc -q $*.asm
	linkw N $@ F \Asmc\lib\c0, *.obj
	del *.obj

