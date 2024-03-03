ifdef YACC
signal:
	asmc64 $@.asm
	gcc -nostdlib -o $@ $@.o /lib/alibc.a
	./$@
	echo Press enter to continue; read dummy;
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