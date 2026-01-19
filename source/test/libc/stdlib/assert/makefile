# Makefile for assert
# Sat Nov 30 16:14:59 2024

assert:
	asmc64 -q $@.asm
ifdef YACC
	./$@
	asmc -q -elf -fno-pic $@.asm
	./$@
else
	$@
	asmc -q -coff $@.asm
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
