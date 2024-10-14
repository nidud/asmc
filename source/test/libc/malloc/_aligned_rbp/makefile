ifdef YACC
_aligned_rbp:
	asmc64 -c -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	@pause
	rm -f $@.o
	rm -f $@
else
_aligned_rbp.exe:
	asmc64 $*.asm
	$@
	pause
	del $*.obj
	del $*.exe
endif