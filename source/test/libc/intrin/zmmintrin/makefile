flags = -q -Gw -MT
ifdef YACC
flags += -fpic
else
#flags += -Bllink
endif

all: zmmintrin clean

zmmintrin:
	asmc64 $(flags) $@.asm
ifdef YACC
	./$@
else
	$@
#	objconv -v0 -fasm $@.obj disassembly.asm
endif
	@pause

clean:
ifdef YACC
	rm ./zmmintrin.o
	rm ./zmmintrin
else
	del zmmintrin.exe
	del zmmintrin.obj
endif

vs:
	project -p zmmintrin
