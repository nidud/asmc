
test:
	asmc64 -q $@.asm
ifdef YACC
	./$@
else
	$@
endif
	@pause
ifdef YACC
	rm $@.o
	rm $@
else
	del $@.obj
	del $@.exe
endif
