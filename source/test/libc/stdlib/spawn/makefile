
all: spawn clean

spawn:
	asmc64 -q $@.asm
	asmc64 -q ../exec/args.asm
ifdef YACC
	./$@ 2 ./args
else
	$@ 2 args.exe
endif
	@pause

clean:
ifdef YACC
	rm ./*.o
	rm ./exec
	rm ./args
else
	del *.exe
	del *.obj
endif

vs:
	project -p spawn

