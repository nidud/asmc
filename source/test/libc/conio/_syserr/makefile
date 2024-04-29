ifdef YACC

_syserr:
	asmc64 -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	rm -f $@.o
	rm -f $@

else

_syserr.exe:
	asmc64 -ws $*.asm
	linkw system con_64W file $*.obj
	$@
	del $*.obj
	del $*.exe
endif
