strtok:
	asmc64 -q -Cs -MT $@.asm
ifdef YACC
	./$@ $@.asm
	@pause
	@rm -f $@
	@rm -f $@.o
else
	$@ $@.asm
	pause
	del $@.obj
	del $@.exe
endif
