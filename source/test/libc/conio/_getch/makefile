_getch:
ifdef YACC
	asmc64 $@.asm
	./$@
	@pause
	rm -f $@.o
	rm -f $@
else
	asmc -q $*.asm
	$@
	asmc -q -ws $*.asm
	$@
	asmc64 -q $*.asm
	$@
	asmc64 -q -ws $*.asm
	$@
	pause
	del $@.obj
	del $@.exe
endif
