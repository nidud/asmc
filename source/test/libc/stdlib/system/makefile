
all: system clean

system:
	asmc64 -q -MT $@.asm
ifdef YACC
	./$@
	asmc -q -elf -MT $@.asm
	./$@
else
	$@
	asmc -q -coff -MT $@.asm
	$@
	asmc -q -coff -ws -Cs -MT $@.asm
	$@
	asmc64 -q -Zp8 -ws -Cs -MT $@.asm
	$@
endif
	@pause

clean:
ifdef YACC
	rm ./system.o
	rm ./system
else
	del system.exe
	del system.obj
endif

vs:
	project -p system

