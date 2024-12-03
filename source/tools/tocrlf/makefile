flags = -q
ifndef YACC
flags += -pe
endif

tocrlf:
	asmc64 $(flags) $@.asm
clean:
ifdef YACC
	rm -f tocrlf
	rm -f tocrlf.o
else
#	del tocrlf.obj
	del tocrlf.exe
endif
