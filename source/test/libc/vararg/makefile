ifdef YACC
vararg:
	asmc64 -c -fpic $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@
	@pause
	rm -f $@.o
	rm -f $@
else
vararg.exe:
	asmc64 $*.asm
	$@
	pause
	del *.obj
	del $@
endif