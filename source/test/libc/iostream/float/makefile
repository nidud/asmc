ifdef YACC
float:
	asmc64 $@.asm
	gcc -nostdlib -o $@ $@.o /lib/alibc.a
	./$@
	echo Press enter to continue; read dummy;
	rm -f $@.o
	rm -f $@
else
float.exe:
	asmc64 -pe $*.asm
	$@
	pause
	del $@
endif
