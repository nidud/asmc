findfirst:
	asmc64 -q $@.asm
ifdef YACC
	./$@ "*.*"
else
	$@ *.*
	asmc -q $@.asm
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
