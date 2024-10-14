ifdef YACC
float:
	asmc64 -c -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	@pause
	rm -f $@.o
	rm -f $@
else
float.exe:
	asmc64 -pe $*.asm
	$@
	pause
	del $@
endif
