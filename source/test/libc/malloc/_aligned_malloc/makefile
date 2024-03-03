ifdef YACC
_aligned_malloc:
	asmc64 -Fitchar.inc $@.asm
	gcc -nostdlib -o $@ $@.o /lib/alibc.a
	./$@
	echo Press enter to continue; read dummy;
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
