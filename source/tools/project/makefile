# Makefile for project
# Mon Oct 21 19:31:07 2024

flags = -q
ifdef YACC
else
flags += -pe
endif

project:
	asmc64 $(flags) $@.asm
ifdef YACC
	./$@
else
	$@
endif
	@pause

clean:
ifdef YACC
	rm ./project.o
	rm ./project
else
	del project.exe
endif
