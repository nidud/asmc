quadmath:
	asmc64 -q $@.asm
ifdef YACC
	./$@
	@pause
	@rm -f $@.o
	@rm -f $@
else
	$@
	asmc64 -q -ws $*.asm
	$@
	pause
	asmc -q $*.asm
	$@
	asmc -q -ws $*.asm
	$@
	pause
	del *.obj
	del *.exe
endif
