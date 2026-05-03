pragma:
	asmc64 -q -MT $@.asm
ifdef YACC
	./$@
	asmc -q -elf -MT $@.asm
	./$@
	@pause
	@rm -f $@.o
	@rm -f $@
else
	$@
	asmc -q -coff -MT $@.asm
	$@
	pause
	del $@.obj
	del $@.exe
endif
