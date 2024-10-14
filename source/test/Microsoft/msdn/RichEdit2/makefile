win64	= 1
static	= 0
unicode = 0

flags = -q
if $(win64)
flags += -win64
endif
if $(unicode)
flags += -ws
endif
ifeq 0 $(static)
flags += -peg
endif
test:
	asmc $(flags) $@.asm
	$@
	pause
	del $@.obj
	del $@.exe
