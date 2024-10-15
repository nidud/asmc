float3:
	asmc64 -q -fpic $@.asm
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
