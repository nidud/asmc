# Makefile for deflate
# Sun Dec 15 22:21:46 2024

deflate:
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
	project -p deflate

