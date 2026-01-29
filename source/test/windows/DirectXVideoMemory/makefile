msvcrt = 1

VideoMemory.exe:
ifdef msvcrt
	asmc -pe $*.asm
else
	asmc64 -q $*.asm
endif
	$@
	pause
	del $@

vs:
	project -p -w VideoMemory
