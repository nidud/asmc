ifdef YACC
mixed:
	asmc64 -c -fpic $@.asm
	gcc -c main.cpp
	gcc -o $@ main.o $@.o
	./$@
	@pause
	rm -f *.o
	rm -f $@
else
mixed.exe:
	asmc64 -c $*.asm
	cl -c main.cpp
	linkw system con_64 file $*, main
	$@
	pause
	del *.obj
	del $@
endif
