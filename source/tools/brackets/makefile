ifndef YACC
flags = -pe -frame
endif
brackets:
	asmc64 -q -Cs $(flags) $@.asm

clean:
ifdef YACC
	rm ./brackets.o
	rm ./brackets
else
	del brackets.exe
endif

vs:
	project -p brackets

install:
ifdef YACC
	sudo install ./brackets /usr/bin
else
	move brackets.exe ..\..\..\bin
endif

test:
	brackets -l test.inc
	pause
