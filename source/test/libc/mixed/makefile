mixed:
	asmc64 -nologo -c -fpic $@.asm
ifdef YACC
	gcc -c main.cpp
	gcc -o $@ main.o $@.o
	./$@
	@pause
	rm -f *.o
	rm -f $@
else
	cl -c -nologo main.cpp
	linkw /nologo $@ main
	$@
	pause
	del *.obj
	del $@.exe
endif
