signal:
	asmc64 -q $@.asm
ifdef YACC
	./$@
	@pause
	@rm -f $@.o
	@rm -f $@
else
	$@
	asmc -q $*.asm
	$@
	pause
	del $*.obj
	del $*.exe
endif
