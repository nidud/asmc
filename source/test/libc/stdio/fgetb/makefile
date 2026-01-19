# Makefile for fgetb
# Fri Nov 15 21:20:25 2024

fgetb:
	asmc64 -q $@.asm
ifdef YACC
	./$@
	asmc -q -elf -fno-pic $@.asm
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
	project -p fgetb
