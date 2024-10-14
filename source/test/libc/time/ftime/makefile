ifdef YACC

_ftime:
	asmc64 -c -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	gcc -o $@ $@.o
	./$@
	rm $@.o
	rm $@
else

_ftime.exe:

	asmc64 -c -pe $*.asm
	$@
	asmc64 -c -q $*.asm
	linkw system con_64 file $*.obj
	$@
	pause
endif
