
all: getenv clean

getenv:
	asmc64 -q $@.asm
ifdef YACC
	./$@
	asmc -q -elf $@.asm
	./$@
else
	$@
	asmc64 -q -ws $@.asm
	$@
	asmc -q $@.asm
	$@
	asmc -q -ws $@.asm
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
