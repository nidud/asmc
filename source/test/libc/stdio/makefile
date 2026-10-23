.SUFFIXES: .asm .exe

.asm.exe:
	asmc64 -q -MT -Fe $*.exe $<

targets = \
	assert.exe \
	fgetb.exe \
	fopen.exe \
	format_b.exe \
	hello.exe \
	popen.exe \
	quadmath.exe \
	scanf.exe \
	vscanf.exe

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
