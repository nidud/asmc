# Makefile for searchenv
# Tue Dec 03 18:17:14 2024

all: searchenv clean

searchenv:
	asmc64 -q $@.asm
ifdef YACC
	./$@
	asmc -elf $@.asm
	./$@
else
	$@
	asmc -q $@.asm
	$@
endif
	@pause

clean:
ifdef YACC
	rm ./searchenv.o
	rm ./searchenv
else
	del searchenv.exe
	del searchenv.obj
endif

vs:
	project -p searchenv

