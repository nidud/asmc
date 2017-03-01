#AFLAGS = -D__W95__ -D__CI__ -D__BMP__
AFLAGS = -D__W95__

dz.exe:
	iddc -r res\*.idd
	asmc -Cs $(AFLAGS) -Iinc -r src\*.asm
	libw $*.lib *.obj
	linkw N $@ Op M, stub=res\dz.bin L libc, dz F ..\..\lib\crt
	wrc -q res\dz.res $@
	del dz.lib
	del *.obj

