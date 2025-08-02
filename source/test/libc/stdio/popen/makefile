
flags = -q

all: popen clean

popen:
	asmc64 $(flags) $@.asm
	$@ asmc
	@pause

clean:
	del popen.exe
	del popen.obj

vs:
	project -p popen
