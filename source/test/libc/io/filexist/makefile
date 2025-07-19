
all: filexist clean

filexist:
	asmc64 -MT $@.asm
ifdef YACC
	./$@
else
	$@
	asmc64 -ws -MT $@.asm
	$@
endif
	@pause

clean:
ifdef YACC
	rm ./filexist.o
	rm ./filexist
else
	del filexist.exe
	del filexist.obj
endif

vs:
	project -p filexist
