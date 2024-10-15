allmul:
	asmc64 -q -fpic $@.asm
ifdef YACC
	./$@
	@pause
	@rm -f $@.o
	@rm -f $@
else
	$@
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
