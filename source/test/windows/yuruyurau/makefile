flags = -q -ws
ifdef x86
flags += -9
else
flags += -win64 -frame
endif
flags += -peg

yuruyurau:
	asmc $(flags) $*?.asm
	$*2

clean:
	del yuruyurau?.exe
	del yuruyurau?.exe.manifest
