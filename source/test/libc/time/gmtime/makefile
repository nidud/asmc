gmtime:
	asmc64 -q $@.asm
ifdef YACC
	./$@
	asmc64 -q -fpic $@.asm
	./$@
	@pause
	@rm $@.o
	@rm $@
else
	$@
	asmc64 -q -pe $*.asm
	$@
	pause
	del $@.obj
	del $@.exe
endif
