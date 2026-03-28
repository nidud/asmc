# Makefile for inflate
# Mon Dec 16 17:05:42 2024

flags = -q

inflate:
	asmc64 $(flags) $@.asm
ifdef YACC
	./$@
else
	$@
endif
	@pause

clean:
ifdef YACC
	rm ./inflate.o
	rm ./inflate
else
	del inflate.exe
	del inflate.obj
endif
