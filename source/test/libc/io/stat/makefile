stat:
	asmc64 $@.asm
ifdef YACC
	./$@
	asmc64 -fpic $@.asm
	./$@
	@pause
	@rm -f $@.o
	@rm -f $@
else
	$@
	asmc -q $*.asm
	asmc -q -ws $*.asm
	asmc64 -q -ws $*.asm
	asmc64 -q -pe $*.asm
	$@
	pause
	del *.obj
	del *.exe
endif
