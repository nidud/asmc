
flags = -q

all: scanf clean

scanf:
	asmc64 $(flags) $@.asm
ifdef YACC
	./$@
else
	$@
endif
	@pause

clean:
ifdef YACC
	rm ./scanf.o
	rm ./scanf
else
	del scanf.exe
	del scanf.obj
endif

vs:
	project -p scanf
