ifdef YACC

localtime:
	asmc64 -fpic $@.asm
	gcc -o $@ $@.o
	./$@
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	rm $@.o
	rm $@
else

localtime.exe:
	asmc64 -pe -Zp8 $*.asm
	$@
	asmc64 -q $*.asm
	linkw system con_64 file $*.obj
	$@
	pause
endif
