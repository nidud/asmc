ifdef YACC

fork:
	asmc64 -c -fpic $@.asm
	gcc -o $@ $@.o
	./$@
	gcc -nostdlib -o a$@ $@.o -l:libasmc.a
	./a$@

else

fork.exe:
	asmc64 $*.asm
	$@
	pause
endif
