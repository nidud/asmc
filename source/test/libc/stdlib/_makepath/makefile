_makepath:
	asmc64 -q $@.asm
ifdef YACC
	./$@
	@pause
	@rm -f $@.o
	@rm -f $@
else
	$@
	asmc -q $@.asm
	$@
	asmc64 -q -pe $@.asm
	$@
	pause
	del $@.obj
	del $@.exe
endif
