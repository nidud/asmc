file:
	asmc64 -q -pe -frame $@.asm
	$@
	@pause

clean:
	del file.exe

vs:
	project -p file

install:
	move file.exe ..\..\..\bin
