# Makefile for cpuid
# Thu Oct 24 23:18:12 2024

flags = -q
ifdef YACC
flags += -fpic
else
flags += -pe
endif

cpuid:
	asmc64 $(flags) $@.asm
ifdef YACC
	./$@
else
	$@
endif
	@pause

clean:
ifdef YACC
	rm ./cpuid.o
	rm ./cpuid
else
	del cpuid.exe
	del cpuid.obj
endif
