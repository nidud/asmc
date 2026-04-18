
all: spawn clean

spawn:
	asmc64 -q -MT $@.asm
	asmc64 -q -MT ../exec/args.asm
ifdef YACC
	./$@ 2 ./args
else
	$@ 2 args.exe
endif
	@pause

clean:
ifdef YACC
	rm ./*.o
	rm ./spawn
	rm ./args
else
	del *.exe
	del *.obj
endif

vs:
	project -p spawn

