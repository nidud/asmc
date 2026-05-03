
flags = -q

all: _pipe clean

_pipe:
	asmc64 $(flags) $@.asm
	$@
	@pause

clean:
	del _pipe.exe
	del _pipe.obj

vs:
	project -p _pipe
