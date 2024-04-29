ifdef YACC
_rcmove:
	asmc64 -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	rm -f $@.o
	rm -f $@
else
_rcmove.exe:
	asmc -q -ws $*.asm
	linkw sys con_32W file $*
	$@
	del *.obj
	del *.exe
endif
