msvcrt = 1

VideoMemory.exe:
ifdef msvcrt
	asmc -pe $*.asm
else
	asmc64 $*.asm
endif
	$@
	pause
