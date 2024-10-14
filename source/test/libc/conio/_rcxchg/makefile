ifdef YACC
_rcxchg:
	asmc64 -c -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	rm -f $@.o
	rm -f $@
else
_rcxchg.exe:
	asmc64 -q $*.asm
	$@
	del *.obj
	del *.exe
endif
