flags = -q
ifdef YACC
flags += -MT
else
flags += -pe -frame
endif

project:
	asmc64 $(flags) $@.asm

clean:
ifdef YACC
	rm ./project.o
	rm ./project
else
	del project.exe
endif

vs:
	project -p project

install:
ifdef YACC
	sudo install ./project /usr/bin
else
	move project.exe ..\..\..\bin
endif
