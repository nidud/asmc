
all: directxmath clean

directxmath:
	asmc64 -q $@.asm
	$@
	@pause
clean:
	del directxmath.exe
	del directxmath.obj
vs:
	project -p directxmath
