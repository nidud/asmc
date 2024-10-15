fork:
	asmc64 -q $@.asm
ifdef YACC
	./$@
	asmc64 -q -fpic $@.asm
	./$@
	@rm ./$@.o
	@rm ./$@
else
	$@
	del $@.obj
	del $@.exe
endif
	@pause
