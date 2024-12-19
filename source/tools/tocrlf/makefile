flags = -q
ifndef YACC
flags += -pe -frame
endif

tocrlf:
	asmc64 $(flags) $@.asm

clean:
ifdef YACC
	rm ./tocrlf.o
	rm ./tocrlf
else
	del tocrlf.exe
endif

vs:
	project -p tocrlf

install:
ifdef YACC
	sudo install ./tocrlf /usr/bin
else
	move tocrlf.exe ..\..\..\bin
endif

