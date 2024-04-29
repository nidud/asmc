ifdef YACC
_rcxchg:
	asmc64 -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	rm -f $@.o
	rm -f $@
else
_rcxchg.exe:
	asmc64 -q $*.asm
	linkw sys con_64 file $*
	$@
	del *.obj
	del *.exe
endif
