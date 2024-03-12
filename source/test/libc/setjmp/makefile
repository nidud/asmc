ifdef YACC
setjmp:
	asmc64 -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	echo Press enter to continue; read dummy;
	rm -f $@.o
	rm -f $@
else
setjmp.exe:
	asmc -q -coff $*.asm
	linkw system con_32 file $*
	$@
	pause
	asmc64 -q $*.asm
	linkw system con_64 file $*
	$@
	pause
	asmc -q -coff -ws $*.asm
	linkw system con_32W file $*
	$@
	pause
	asmc64 -q -ws $*.asm
	linkw system con_64W file $*
	$@
	pause
	del $*.obj
	del $*.exe
endif

