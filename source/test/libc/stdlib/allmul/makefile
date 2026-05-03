
all: allmul clean

allmul:
	asmc64 -q -MT $@.asm
ifdef YACC
	./$@
else
	$@
	asmc -q -coff -MT $*.asm
	$@
	asmc64 -q -ws -MT $*.asm
	$@
endif
	@pause

clean:
ifdef YACC
	rm ./allmul.o
	rm ./allmul
else
	del allmul.exe
	del allmul.obj
endif

vs:
	project -p allmul
