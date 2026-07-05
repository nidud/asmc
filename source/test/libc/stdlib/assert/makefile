assert:
	asmc64 -q -MT $@.asm
ifdef YACC
	./$@
	asmc -q -elf -MT $@.asm
	./$@
else
	$@
	asmc -q -coff -MT $@.asm
	$@
endif
	@pause
ifdef YACC
	rm ./assert.o
	rm ./assert
else
	del assert.exe
	del assert.obj
endif
