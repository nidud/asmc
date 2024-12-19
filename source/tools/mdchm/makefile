ifndef YACC
flags = -pe -frame
endif
mdchm:
	asmc64 -q $(flags) $@.asm

clean:
ifdef YACC
	rm ./mdchm.o
	rm ./mdchm
else
	del mdchm.exe
endif

vs:
	project -p mdchm

install:
ifdef YACC
	sudo install ./mdchm /usr/bin
else
	move mdchm.exe ..\..\..\bin
endif
