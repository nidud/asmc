ifdef YACC
Inheritance:
	asmc64 -c -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	@pause
	rm -f $@.o
	rm -f $@
else
Inheritance.exe:
	asmc64 -pe $*.asm
	$@
	pause
	del $@
endif
