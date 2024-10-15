getenv:
	asmc64 -q $@.asm
ifdef YACC
	./$@
	asmc -q -elf $@.asm
	./$@
	@pause
	@rm $@.o
	@rm $@
else
	asmc64 -q -ws $@.asm
	$@
	asmc -q $@.asm
	$@
	asmc -q -ws $@.asm
	$@
	pause
	del $@.obj
	del $@.exe
endif
