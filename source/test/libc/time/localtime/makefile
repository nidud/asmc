localtime:
	asmc64 -q -MT $@.asm
ifdef YACC
	./$@
	asmc64 -q -MD $@.asm
	./$@
	@pause
	@rm $@.o
	@rm $@
else
	$@
	asmc64 -q -MD $@.asm
	$@
	pause
	del $@.obj
	del $@.exe
endif
