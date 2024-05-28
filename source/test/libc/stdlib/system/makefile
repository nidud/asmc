ifdef YACC
system:
	asmc64 -q $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	asmc -q -elf $@.asm
	gcc -m32 -nostdlib -o $@ $@.o -l:x86/libasmc.a
	./$@
	rm -f $@.o
	rm -f $@
else

system.exe:
	asmc -q $*.asm
	linkw system con_32 file $*
	$@
	asmc64 -q -Zp8 -Cs $*.asm
	linkw system con_64 file $*
	$@
	asmc -q -ws -Cs $*.asm
	linkw system con_32W file $*
	$@
	asmc64 -q -Zp8 -ws -Cs $*.asm
	linkw system con_64W file $*
	$@
	pause
	del $*.obj
	del $@
endif
