malloc:
ifdef YACC
	asmc64 -fpic $@.asm
	@./$@
	@rm -f ./$@
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
	@./$@
	@pause
	@rm -f ./$@
	@rm -f ./$@.o
else
	asmc64 -q -pe $@.asm
	$@
	asmc64 -q $@.asm
	$@
	pause
endif
