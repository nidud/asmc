_aligned_rbp:
	asmc64 -q $@.asm
ifdef YACC
	./$@
else
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
	project -p _aligned_rbp
