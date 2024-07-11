ifdef YACC

fireworks:
	asmc64 -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a

else
msvcrt = 1
fireworks.exe:
ifdef msvcrt
	asmc64 -Cs -pe -gui $*.asm
else
	asmc64 -Cs $*.asm
	linkw system gui_64 file $*.obj
endif
	$@
endif
