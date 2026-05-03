imgconv:
	asmc64 -q -pe -ws -frame $@.asm

clean:
	del imgconv.exe

vs:
	project -p -u imgconv

install:
	move imgconv.exe ..\..\..\..\bin
