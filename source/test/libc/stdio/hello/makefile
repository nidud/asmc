ifdef YACC
hello:
	asmc64 $@.asm
	gcc -nostdlib -o $@ $@.o /lib/alibc.a
	./$@
	echo Press enter to continue; read dummy;
	rm -f $@.o
	rm -f $@
else
hello.exe:
	asmc64 $*.asm
	linkw sys con_64 file $*
	$@
	pause
	del $*.obj
	del $*.exe
endif
