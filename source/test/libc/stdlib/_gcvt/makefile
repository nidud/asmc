_gcvt:
	asmc64 -q $@.asm
ifdef YACC
	./$@
	@pause
	@rm -f $@.o
	@rm -f $@
else
	$@
	asmc -q -8 $*.asm
	$@
	asmc64 -q -pe $*.asm
	$@
	pause
	del *.obj
	del *.exe
endif
