
flags = -q

all: dup clean

dup:
	asmc64 $(flags) $@.asm
ifdef YACC
	./$@
else
	$@
endif
	@pause

clean:
ifdef YACC
	rm ./dup.o
	rm ./dup
else
	del dup.exe
	del dup.obj
endif

vs:
	project -p dup
