all: dzip clean

dzip:
	asmc64 -q -MT $@.asm

clean:
ifdef YACC
	rm ./dzip.o
else
	del dzip.obj
endif

vs:
	project -p dzip

install:
ifdef YACC
	sudo install ./dzip /usr/bin
else
	move dzip.exe ..\..\..\bin
endif
