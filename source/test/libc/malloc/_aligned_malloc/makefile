_aligned_malloc:
	asmc64 -q $@.asm
ifdef YACC
	./$@
	@pause
	asmc -q -elf -fno-pic $@.asm
	./$@
else
	$@
	asmc -q -coff $*.asm
	$@
	asmc64 -q -pe $*.asm
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
	project -p _aligned_malloc
