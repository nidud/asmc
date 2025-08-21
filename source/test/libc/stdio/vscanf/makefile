
flags = -q

all: vscanf clean

vscanf:
	asmc64 $(flags) $@.asm
ifdef YACC
	./$@
else
	$@
endif
	@pause

clean:
ifdef YACC
	rm ./vscanf.o
	rm ./vscanf
else
	del vscanf.exe
	del vscanf.obj
endif

vs:
	project -p vscanf
