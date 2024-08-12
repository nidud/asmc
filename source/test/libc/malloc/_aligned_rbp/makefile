ifdef YACC
_aligned_rbp:
	asmc64 -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	@pause
	rm -f $@.o
	rm -f $@
else
_aligned_rbp.exe:
	asmc64 $*.asm
	linkw system con_64 file $*
	$@
	pause
	del $*.obj
	del $*.exe
endif