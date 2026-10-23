.SUFFIXES: .asm .exe

.asm.exe:
	asmc64 -q -MT -Fe $*.exe $<

targets = \
	difftime.exe \
	ftime.exe \
	gmtime.exe \
	localtime.exe

build: $(targets)
ifdef YACC
	rm -f *.o
else
	del *.obj
endif

clean:
ifdef YACC
	rm -f *.exe *.o
else
	del *.exe *.obj
endif
