
flags = -q

all: mktemp clean

mktemp:
	asmc64 $(flags) $@.asm
ifdef YACC
	./$@
else
	$@
endif
	@pause

clean:
ifdef YACC
	rm ./mktemp.o
	rm ./mktemp
else
	del mktemp.exe
	del mktemp.obj
endif

vs:
	project -p mktemp
