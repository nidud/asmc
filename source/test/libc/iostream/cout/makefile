cout:
	asmc64 -q -MT $@.asm
	asmc64 -q -MT stdio.asm
ifdef YACC
	./$@
	./stdio
	@pause
	@rm -f *.o
	@rm -f ./$@
	@rm -f ./stdio
else
	$@
	stdio
	pause
	del *.obj
	del *.exe
endif
