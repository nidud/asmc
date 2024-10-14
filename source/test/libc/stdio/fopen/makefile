ifdef YACC
fopen:
	asmc64 -c -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	@pause
	rm -f $@.o
	rm -f $@
else
fopen.exe:
	asmc64 -c $*.asm
	linkw sys con_64 file $*
	$@
	pause
	del *.obj
	del $@
endif
