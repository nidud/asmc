
flags = -q -MT

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
	rm ./fn*
else
	del mktemp.exe
	del mktemp.obj
	del fn*
endif

vs:
	project -p mktemp
