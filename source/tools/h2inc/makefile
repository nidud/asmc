flags = -q -Cs
ifndef YACC
flags += -pe -frame
endif

h2inc:
	asmc64 $(flags) $@.asm

clean:
ifdef YACC
	rm ./h2inc.o
	rm ./h2inc
else
	del h2inc.exe
endif

vs:
	project -p h2inc

install:
ifdef YACC
	sudo install ./h2inc /usr/bin
else
	move h2inc.exe ..\..\..\bin
endif

