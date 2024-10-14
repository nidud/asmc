static = 0
mslink = 0
incdir = %AsmcDir%\include\winrt

wrl.exe:
if $(static)
if $(mslink)
	asmc64 -q -Bl link -I$(incdir) -ws -frame $*.asm
else
	asmc64 -q -I$(incdir) -ws -frame $*.asm
endif
else
	asmc64 -q -I$(incdir) -ws -peg $*.asm
endif
	$@
