float2:
	asmc64 -q -MT $@.asm
ifdef YACC
	./$@
	@pause
	@rm -f $@.o
	@rm -f $@
else
	$@
	pause
	del $@.obj
	del $@.exe
endif
