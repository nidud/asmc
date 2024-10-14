ifdef YACC

gmtime:
	asmc64 -c -fpic $@.asm
	gcc -o $@ $@.o
	./$@
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	rm $@.o
	rm $@

else

gmtime.exe:
	asmc64 -pe $*.asm
	$@
	asmc64 -c -q $*.asm
	linkw system con_64 file $*.obj
	$@
	pause
endif
