all: ..\..\lib\intn.lib ..\..\lib\amd64\intn.lib

..\..\lib\intn.lib:
	asmc -coff -Cs -Zi x86\*.asm
	libw -q -b -n -c -fac $@ *.obj
	del *.obj

..\..\lib\amd64\intn.lib:
	asmc64 -Cs -Zi x64\*.asm
	libw /q /b /n /c /fac $@ *.obj
	del *.obj
