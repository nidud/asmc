ifdef YACC
_aligned_malloc:
	asmc64 -fpic -Fitchar.inc $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	@pause
	rm -f $@.o
	rm -f $@
else
_aligned_malloc.exe:
	asmc -q -Fitchar.inc $*.asm
	linkw system con_32 file $*
	$@
	asmc64 -q -Fitchar.inc $*.asm
	linkw system con_64 file $*
	$@
	asmc64 -q -pe -Fitchar.inc $*.asm
	$@
	pause
	del $*.obj
	del $*.exe
endif
