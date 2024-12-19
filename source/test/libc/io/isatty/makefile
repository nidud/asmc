isatty:
	asmc64 -q $@.asm
ifdef YACC
	./$@
	@pause
	rm -f $@.o
	rm -f $@
else
	$@
	asmc -q $*.asm
	asmc -q -ws $*.asm
	asmc64 -q -ws $*.asm
	asmc64 -q -ws -pe $*.asm
	$@
	pause
	del *.obj
	del *.exe
endif

vs:
	project -p isatty
