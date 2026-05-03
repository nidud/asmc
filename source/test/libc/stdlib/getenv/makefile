
all: getenv clean

getenv:
	asmc64 -q -MT $@.asm
ifdef YACC
	./$@
	asmc -q -elf -MT $@.asm
	./$@
else
	$@
	asmc64 -q -ws -MT $@.asm
	$@
	asmc -q -coff -MT $@.asm
	$@
	asmc -q -ws -coff -MT $@.asm
	$@
endif
	@pause

clean:
ifdef YACC
	rm ./getenv.o
	rm ./getenv
else
	del getenv.exe
	del getenv.obj
endif

vs:
	project -p getenv
