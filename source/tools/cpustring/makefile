# Makefile for cpustring - Apr 17 2026

ifndef YACC
flags += -pe
endif

cpustring:
	asmc64 $(flags) $@.asm
ifdef YACC
	./$@
else
	$@
endif
	@pause

clean:
ifdef YACC
	rm ./cpustring.o
	rm ./cpustring
else
	del cpustring.exe
endif

vs:
	project -p cpustring
