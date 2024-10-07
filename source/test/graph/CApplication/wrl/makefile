static = 0
mslink = 0
incdir = %AsmcDir%\include\winrt

wrl.exe:
if $(static)
	asmc64 -I$(incdir) -ws -frame $*.asm
if $(mslink)
	link /libpath:%AsmcDir%\lib\x64 /machine:x64 $*.obj
else
	linkw system gui_64W file $*.obj
endif
else
	asmc64 -I$(incdir) -ws -peg $*.asm
endif
	$@
