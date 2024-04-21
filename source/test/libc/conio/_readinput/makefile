ifdef YACC

_readinput:
	asmc64 -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a

else

_readinput.exe:
	asmc64 -ws $*.asm
	linkw sys con_64W file $*.obj
	del $*.obj
endif
