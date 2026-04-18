quadmath:
	asmc64 -q -MT $@.asm
ifdef YACC
	./$@
	@pause
	@rm -f $@.o
	@rm -f $@
else
	$@
	asmc64 -q -ws -MT $*.asm
	$@
	pause
	asmc -q -coff -MT $*.asm
	$@
	asmc -q -coff -ws -MT $*.asm
	$@
	pause
	del *.obj
	del *.exe
endif
