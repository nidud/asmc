ifdef YACC
hello:
	asmc64 -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	@pause
	rm -f $@.o
	rm -f $@
else
hello.exe:
	asmc64 $*.asm
	linkw sys con_64 file $*
	$@
	pause
	del $*.obj
	del $*.exe
endif
