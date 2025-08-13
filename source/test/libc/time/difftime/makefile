
flags = -q

all: difftime clean

difftime:
	asmc64 $(flags) $@.asm
ifdef YACC
	./$@
else
	$@
endif
	@pause

clean:
ifdef YACC
	rm ./difftime.o
	rm ./difftime
else
	del difftime.exe
	del difftime.obj
endif

vs:
	project -p difftime
