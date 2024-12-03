# Makefile for searchenv
# Tue Dec 03 18:17:14 2024

flags = -q

searchenv:
	asmc64 $(flags) $@.asm
ifdef YACC
	./$@
	asmc -elf $(flags) $@.asm
	./$@
else
	$@
	asmc $(flags) $@.asm
	$@
endif
	@pause
ifdef YACC
	rm ./searchenv.o
	rm ./searchenv
else
	del searchenv.exe
	del searchenv.obj
endif
