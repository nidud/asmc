Win64 = 1

MagnifierSample.exe:
if $(Win64)
	asmc64 -frame -peg $*.asm
else
	asmc -peg -arch:SSE $*.asm
endif
	$@
	del $@

vs:
	project -p -w MagnifierSample
