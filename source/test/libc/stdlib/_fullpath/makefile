# Makefile for _fullpath
# Thu Dec 05 20:33:21 2024

all: _fullpath clean

_fullpath:
	asmc64 -q $@.asm
ifdef YACC
	./$@ ../_fullpath
else
	$@ ..\_fullpath
endif
	@pause

clean:
ifdef YACC
	rm ./_fullpath.o
	rm ./_fullpath
else
	del _fullpath.exe
	del _fullpath.obj
endif

vs:
	project -p _fullpath
