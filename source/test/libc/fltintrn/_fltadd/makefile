# Makefile for _fltadd
# Mon Nov 04 06:02:30 2024

_fltadd:
ifdef YACC
	asmc -c -q -elf -fno-pic $@.asm
else
	asmc -c -q $@.asm
endif
	asmc64 -c -q $@.asm
	@pause
ifdef YACC
	rm ./_fltadd.o
else
	del _fltadd.obj
endif
