
all: _gcvt clean

_gcvt:
	asmc64 -q $@.asm
ifdef YACC
	./$@
else
	$@
	asmc -q -8 $*.asm
	$@
	asmc64 -q -pe $*.asm
	$@
endif
	@pause

clean:
ifdef YACC
	rm ./_gcvt.o
	rm ./_gcvt
else
	del _gcvt.exe
	del _gcvt.obj
endif

vs:
	project -p _gcvt

