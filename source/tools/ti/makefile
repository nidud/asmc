flags = -q
ifndef YACC
flags += -pe
endif

ti:
	asmc64 $(flags) $@.asm

clean:
ifdef YACC
	rm ./ti.o
	rm ./ti
else
	del ti.exe
endif

vs:
	project -p ti

install:
ifdef YACC
	sudo install ./ti /usr/bin
else
	move ti.exe ..\..\..\bin
endif

