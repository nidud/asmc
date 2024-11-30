# Makefile for fgetb
# Fri Nov 15 21:20:25 2024

flags = -q

fgetb:
	asmc64 $(flags) $@.asm
ifdef YACC
	./$@
	asmc $(flags) -elf $@.asm
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
