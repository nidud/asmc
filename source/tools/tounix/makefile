flags = -q
ifndef YACC
flags += -pe
endif

tounix:
	asmc64 $(flags) $@.asm
clean:
ifdef YACC
	rm -f tounix
	rm -f tounix.o
else
#	del tounix.obj
	del tounix.exe
endif
