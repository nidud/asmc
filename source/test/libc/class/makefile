class:
	asmc64 -q -MT $@.asm
ifdef YACC
	./$@
	asmc -q -elf -fno-pic $@.asm
	./$@
else
	$@
	asmc64 -q -MT -ws $@.asm
	$@
	asmc -q -MT -coff $@.asm
	$@
	asmc -q -MT -coff -ws -Cs $@.asm
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
	project -p class

