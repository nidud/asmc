ifdef YACC
test:
	asmc64 $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	echo Press enter to continue; read dummy;
	rm -f $@.o
	rm -f $@
else
test.exe:
	asmc64 -q $*.asm
	linkw system con_64 file $*
	$@
	asmc64 -q -pe $*.asm
	$@
	pause
	del *.obj
	del *.exe
endif
