ifdef YACC
fopen:
	asmc64 -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	echo Press enter to continue; read dummy;
	rm -f $@.o
	rm -f $@
else
fopen.exe:
	asmc64 $*.asm
	linkw sys con_64 file $*
	$@
	pause
	del *.obj
	del $@
endif
