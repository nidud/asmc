pragma:
	asmc64 -q $@.asm
ifdef YACC
	./$@
	asmc -q -elf -fno-pic $@.asm
	./$@
	@pause
	@rm -f $@.o
	@rm -f $@
else
	$@
	asmc -coff -q $@.asm
	$@
	pause
	del $@.obj
	del $@.exe
endif
