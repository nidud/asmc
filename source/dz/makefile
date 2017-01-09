AFLAGS = -D__W95__ -D__CI__ -D__BMP__

dz.exe:
	iddc -r res\*.idd
	asmc -Cs $(AFLAGS) -Iinc -r src\*.asm
	libw $*.lib *.obj
	linkw N $@ Op M, stub=res\dz.bin L dz F ..\..\lib\C0
	wrc -q res\dz.res $@
	del dz.lib
	del *.obj

