all: _makepath clean

_makepath:
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
	rm ./_makepath.o
	rm ./_makepath
else
	del _makepath.exe
	del _makepath.obj
endif

vs:
	project -p _makepath

