ifndef YACC
flags = -pe -frame
endif
fcmp:
	asmc64 -q $(flags) $@.asm

clean:
ifdef YACC
	rm ./fcmp.o
	rm ./fcmp
else
	del fcmp.exe
endif

vs:
	project -p fcmp

install:
ifdef YACC
	sudo install ./fcmp /usr/bin
else
	move fcmp.exe ..\..\..\bin
endif
