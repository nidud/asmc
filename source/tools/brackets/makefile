ifdef YACC
brackets:
	asmc64 -Cs $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	./$@ -l test.inc
	@pause
	rm -f $@.o
else
brackets.exe:
	asmc64 -q -Cs $*.asm
	linkw system con_64 file $*
	$@ -l test.inc
	pause
	del $*.obj
endif
