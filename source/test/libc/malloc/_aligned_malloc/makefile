_aligned_malloc:
	asmc64 -q -Fitchar.inc $@.asm
ifdef YACC
	./$@
	@pause
	@rm -f $@.o
	@rm -f $@
else
	$@
	asmc -q -Fitchar.inc $*.asm
	$@
	asmc64 -q -pe -Fitchar.inc $*.asm
	$@
	pause
	del $*.obj
	del $*.exe
endif
