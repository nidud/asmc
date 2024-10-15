system:
	asmc64 -q $@.asm
ifdef YACC
	./$@
	asmc -q -elf $@.asm
	./$@
	@pause
	@rm -f $@.o
	@rm -f $@
else
	$@
	asmc -q $@.asm
	$@
	asmc -q -ws -Cs $@.asm
	$@
	asmc64 -q -Zp8 -ws -Cs $@.asm
	$@
	pause
	del $@.obj
	del $@.exe
endif
