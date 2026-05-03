flags = -q
ifdef YACC
flags += -MT
else
flags += -pe -frame
endif

tounix:
	asmc64 $(flags) $@.asm

clean:
ifdef YACC
	rm ./tounix.o
	rm ./tounix
else
	del tounix.exe
endif

vs:
	project -p tounix

install:
ifdef YACC
	sudo install ./tounix /usr/bin
else
	move tounix.exe ..\..\..\bin
endif
