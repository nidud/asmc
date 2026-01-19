stat:
	asmc64 -q $@.asm
ifdef YACC
	./$@
	asmc -elf -fno-pic $@.asm
	./$@
	@pause
	@rm -f $@.o
	@rm -f $@
else
	$@
	asmc -q $*.asm
	asmc -q -ws $*.asm
	$@
	asmc64 -q -ws $*.asm
	asmc64 -q -pe $*.asm
	$@
	pause
	del *.obj
	del *.exe
endif

vs:
	project -p stat
