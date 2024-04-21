ifdef YACC

_syserr:
	asmc64 -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a

else

_syserr.exe:
ifdef msvcrt
	asmc64 -pe $*.asm
else
	asmc64 -ws $*.asm
	linkw system con_64W file $*.obj
endif
	$@
endif
