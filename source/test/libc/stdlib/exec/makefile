
all: exec clean

exec:
	asmc64 -q -MT $@.asm
	asmc64 -q -MT args.asm
ifdef YACC
	./$@ ./args 2
else
	$@ args.exe 2
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
	project -p exec
