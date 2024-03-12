ifdef YACC
pragma:
	asmc64 -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	asmc -elf -fpic $@.asm
	gcc -m32 -nostdlib -o $@ $@.o -l:x86/libasmc.a
	./$@
	echo Press enter to continue; read dummy;
	rm -f $@.o
	rm -f $@
else
pragma.exe:
	asmc64 $*.asm
	linkw system con_64 file $*
	$@
	pause
	del $*.obj
	del $@
endif
