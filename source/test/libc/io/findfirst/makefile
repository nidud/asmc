findfirst:
	asmc64 -q -MT $@.asm
ifdef YACC
	./$@ "*.*"
	asmc -elf -MT $@.asm
	./$@ "*.*"
else
	$@ *.*
	asmc64 -q -ws -MT $@.asm
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
