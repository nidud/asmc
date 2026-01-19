
all: system clean

system:
	asmc64 -q $@.asm
ifdef YACC
	./$@
	asmc -q -elf -fno-pic $@.asm
	./$@
else
	$@
	asmc -q $@.asm
	$@
	asmc -q -ws -Cs $@.asm
	$@
	asmc64 -q -Zp8 -ws -Cs $@.asm
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

