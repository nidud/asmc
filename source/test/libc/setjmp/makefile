setjmp:
	asmc64 -q $@.asm
ifdef YACC
	./$@
	@pause
	@rm -f $@.o
	@rm -f $@
else
	$@
	asmc -q -coff $@.asm
	$@
	asmc -q -coff -ws $*.asm
	$@
	asmc64 -q -ws $*.asm
	$@
	pause
	del $*.obj
	del $*.exe
endif

