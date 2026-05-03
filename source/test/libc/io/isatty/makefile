isatty:
	asmc64 -q -MT $@.asm
ifdef YACC
	./$@
	@pause
	rm -f $@.o
	rm -f $@
else
	$@
	asmc -q -coff -MT $*.asm
	asmc -q -coff -ws -MT $*.asm
	asmc64 -q -ws -MT $*.asm
	asmc64 -q -ws -pe $*.asm
	$@
	pause
	del *.obj
	del *.exe
endif

vs:
	project -p isatty
