# Makefile for fgetb
# Fri Nov 15 21:20:25 2024

flags = -q
ifdef YACC
flags += -fpic
else
endif

fgetb:
	asmc64 $(flags) $@.asm
ifdef YACC
	./$@
else
	$@
endif
	@pause

clean:
ifdef YACC
	rm ./fgetb.o
	rm ./fgetb
else
	del fgetb.exe
	del fgetb.obj
endif
