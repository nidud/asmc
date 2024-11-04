# Makefile for _fltadd
# Mon Nov 04 06:02:30 2024

_fltadd:
	asmc -c -q $@.asm
	asmc64 -c -q $@.asm
	@pause
ifdef YACC
	rm ./_fltadd.o
else
	del _fltadd.obj
endif
