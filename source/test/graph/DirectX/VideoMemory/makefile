msvcrt = 1

VideoMemory.exe:
ifdef msvcrt
	asmc -pe $*.asm
else
	asmc64 $*.asm
	linkw system con_64 file $*.obj
endif
	$@
	pause
