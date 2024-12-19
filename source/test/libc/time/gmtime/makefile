gmtime:
	asmc64 -q $@.asm
ifdef YACC
	./$@
	asmc64 -q -fpic $@.asm
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

