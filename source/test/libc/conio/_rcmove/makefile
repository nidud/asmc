ifdef YACC
_rcmove:
	asmc64 -c -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	rm -f $@.o
	rm -f $@
else
_rcmove.exe:
	asmc -q -ws $*.asm
	$@
	del *.obj
	del *.exe
endif
