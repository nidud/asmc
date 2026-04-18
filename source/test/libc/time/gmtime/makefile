gmtime:
	asmc64 -q -MT $@.asm
ifdef YACC
	./$@
	asmc64 -q -MD $@.asm
	./$@
else
	$@
	asmc64 -q -pe $*.asm
	$@
endif
	@pause
ifdef YACC
	rm ./$@.o
	rm ./$@
else
	del $@.exe
	del $@.obj
endif

vs:
	project -p gmtime

