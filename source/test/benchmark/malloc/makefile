ifdef YACC

malloc:
	asmc64 -fpic $@.asm
	gcc -o $@ $@.o
	@./$@
	@rm -f ./$@
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	@./$@
	@pause
	@rm -f ./$@
	@rm -f ./$@.o

else

malloc.exe:
	asmc64 -q -pe $*.asm
	$@
	asmc64 -q $*.asm
	linkw system con_64 file $*.obj
	$@
	pause
endif
