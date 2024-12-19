# Makefile for inflate
# Mon Dec 16 17:05:42 2024

inflate:
	asmc64 -q $@.asm
ifdef YACC
	./$@
else
	$@
endif
	@pause
ifdef YACC
	rm ./$@.o
	rm ./$@
else
	del $@.exe
	del $@.obj
endif

vs:
	project -p inflate

