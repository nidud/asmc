class:
	asmc64 -q $@.asm
ifdef YACC
	./$@
	asmc -q -elf $@.asm
	./$@
else
	$@
	asmc64 -q -ws $@.asm
	$@
	asmc -q $@.asm
	$@
	asmc -q -ws -Cs $@.asm
	$@
endif
	@pause
ifdef YACC
	rm ./$@.o
	rm ./$@
else
	del $@.exe
	del $@.obj
endif

vs:
	project -p class

