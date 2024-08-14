ifdef YACC
tounix:
	asmc64 $@.asm
	gcc -nostdlib -o $@ $@.o -l:libasmc.a
clean:
	rm -f tounix
	rm -f tounix.o
else
tounix.exe:
	asmc64 $*.asm
	linkw system con_64 file $*
clean:
	del tounix.obj
	del tounix.exe
endif
