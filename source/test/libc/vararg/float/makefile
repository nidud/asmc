float:
ifdef YACC
	asmc64 -q -fpic $@.asm
	./$@
	@pause
	@rm -f $@.o
	@rm -f $@
else
	asmc64 -q -pe $@.asm
	$@
	pause
	del $@.obj
	del $@.exe
endif
