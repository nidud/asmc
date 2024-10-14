ifdef YACC
setjmp:
	asmc64 -c -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	rm -f $@.o
	rm -f $@
else
setjmp.exe:
	asmc -c -q -coff $*.asm
	linkw system con_32 file $*
	$@
	pause
	asmc64 -c -q $*.asm
	linkw system con_64 file $*
	$@
	pause
	asmc -q -c -coff -ws $*.asm
	linkw system con_32W file $*
	$@
	pause
	asmc64 -c -q -ws $*.asm
	linkw system con_64W file $*
	$@
	pause
	del $*.obj
	del $*.exe
endif

