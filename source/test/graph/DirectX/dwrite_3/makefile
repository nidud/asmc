
flags = -q -Zp8 -ws

all: dwrite_3 clean

dwrite_3:
	asmc64 $(flags) $@.asm
	$@
	@pause

clean:
	del dwrite_3.exe
	del dwrite_3.obj

vs:
	project -p -u dwrite_3
