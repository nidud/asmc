ifdef YACC
_aligned_malloc:
	asmc64 -c -fpic -Fitchar.inc $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	@pause
	rm -f $@.o
	rm -f $@
else
_aligned_malloc.exe:
	asmc -c -q -Fitchar.inc $*.asm
	linkw system con_32 file $*
	$@
	asmc64 -c -q -Fitchar.inc $*.asm
	linkw system con_64 file $*
	$@
	asmc64 -c -q -pe -Fitchar.inc $*.asm
	$@
	pause
	del $*.obj
	del $*.exe
endif
