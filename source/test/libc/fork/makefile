ifdef YACC

fork:
	asmc64 -fpic $@.asm
	gcc -o $@ $@.o
	./$@
	gcc -nostdlib -o a$@ $@.o -l:libasmc.a
	./a$@

else

fork.exe:
	asmc64 $*.asm
	linkw system con_64 file $*.obj
	$@
	pause
endif
