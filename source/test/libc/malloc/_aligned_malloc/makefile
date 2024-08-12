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
	asmc -Fitchar.inc $*.asm
	linkw system con_32 file $*
	$@
	pause
	del $*.obj
	del $*.exe
endif
