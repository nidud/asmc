all: _atodbl clean

_atodbl:
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
	rm ./_atodbl.o
	rm ./_atodbl
else
	del _atodbl.exe
	del _atodbl.obj
endif

vs:
	project -p _atodbl
