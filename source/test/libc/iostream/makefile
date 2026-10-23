.SUFFIXES: .asm .exe

.asm.exe:
	asmc64 -q -MT -Fe $*.exe $<

targets = \
	cout.exe \
	float.exe \
	float2.exe \
	float3.exe \
	Inheritance.exe \
	namespace.exe \
	operator.exe \
	stdio.exe

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
