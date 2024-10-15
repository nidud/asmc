spawn:
	asmc64 -q $@.asm
ifdef YACC
	asmc64 -q -fpic ../exec/args.asm
	./$@ 2 ./args
	@pause
	@rm -f *.o
	@rm -f ./$@
	@rm -f ./args
else
	asmc64 -q -pe ../exec/args.asm
	$@ 2 args.exe
	pause
	del $@.obj
	del $@.exe
	del args.exe
endif
