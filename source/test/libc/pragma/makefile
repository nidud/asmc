ifdef YACC
pragma:
	asmc64 -c -q -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	asmc -c -q -elf -fpic $@.asm
	gcc -m32 -nostdlib -o $@ $@.o -l:x86/libasmc.a
	./$@
	rm -f $@.o
	rm -f $@
else
pragma.exe:
	asmc64 -c $*.asm
	linkw system con_64 file $*
	$@
	pause
	del $*.obj
	del $@
endif
