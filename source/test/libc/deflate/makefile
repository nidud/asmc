# Makefile for deflate
# Sun Dec 15 22:21:46 2024

flags = -q

deflate:
	asmc64 $(flags) $@.asm
ifdef YACC
	./$@
else
	$@
endif
	@pause

clean:
ifdef YACC
	rm ./deflate.o
	rm ./deflate
else
	del deflate.exe
	del deflate.obj
endif
