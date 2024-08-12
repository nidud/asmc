ifdef YACC
signal:
	asmc64 -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	@pause
	rm -f $@.o
	rm -f $@
else
signal.exe:
	asmc $*.asm
	linkw system con_32 file $*
	$@
	pause
	asmc64 $*.asm
	linkw system con_64 file $*
	$@
	pause
	del $*.obj
	del $*.exe
endif