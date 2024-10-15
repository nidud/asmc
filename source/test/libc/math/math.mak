test:
	asmc64 -q $@.asm
ifdef YACC
	./$@
	@pause
	@rm -f $@.o
	@rm -f $@
else
	$@
	asmc64 -q -pe $@.asm
	$@
	pause
	del $@.obj
	del $@.exe
endif
