ifdef YACC
operator:
	asmc64 $@.asm
	gcc -nostdlib -o $@ $@.o /lib/alibc.a
	./$@
	echo Press enter to continue; read dummy;
	rm -f $@.o
	rm -f $@
else
operator.exe:
	asmc64 -pe $*.asm
	$@
	pause
	del $@
endif
