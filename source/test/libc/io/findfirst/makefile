findfirst:
	asmc64 -q $@.asm
ifdef YACC
	./$@ "*.*"
	asmc -elf -fno-pic $@.asm
	./$@ "*.*"
else
	$@ *.*
	asmc64 -q -ws $@.asm
	$@ *.*
	asmc64 -q -pe $@.asm
	$@ *.*
endif
	@pause
ifdef YACC
	@rm -f $@.o
	@rm -f $@
else
	del $@.obj
	del $@.exe
endif

vs:
	project -p findfirst
