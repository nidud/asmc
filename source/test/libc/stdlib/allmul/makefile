
all: allmul clean

allmul:
	asmc64 -q $@.asm
ifdef YACC
	./$@
else
	$@
	asmc -q $*.asm
	$@
	asmc64 -q -ws $*.asm
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
