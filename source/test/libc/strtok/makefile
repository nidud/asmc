ifdef YACC

strtok:
	asmc64 -q -Cs -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@ *.asm
	@pause
	rm -f $@
	rm -f $@.o
else
strtok.exe:
	asmc64 $*.asm
	linkw sys con_64 file $*
	$@ *.asm
	pause
	del $*.obj
endif
