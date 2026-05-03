stat:
	asmc64 -q -MT $@.asm
ifdef YACC
	./$@
	asmc -elf -MT $@.asm
	./$@
	@pause
	@rm -f $@.o
	@rm -f $@
else
	$@
	asmc -q -coff -MT $*.asm
	asmc -q -coff -MT -ws $*.asm
	$@
	asmc64 -q -ws -MT $*.asm
	asmc64 -q -pe $*.asm
	$@
	pause
	del *.obj
	del *.exe
endif

vs:
	project -p stat
