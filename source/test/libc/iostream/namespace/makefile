namespace:
	asmc64 -q $@.asm
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
