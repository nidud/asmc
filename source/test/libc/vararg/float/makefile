float:
	asmc64 -nologo -MD $@.asm
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

vs:
	project -p float
