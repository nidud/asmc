.SUFFIXES: .asm .exe

.asm.exe:
	asmc64 -q -MT -Fe $*.exe $<

targets = \
	assert.exe \
	creat.exe \
	dup.exe \
	filexist.exe \
	findfirst.exe \
	findfirst64.exe \
	isatty.exe \
	mktemp.exe \
	stat.exe

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
