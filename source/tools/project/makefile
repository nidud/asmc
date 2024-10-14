static = 0

project.exe:
if $(static)
	asmc64 -q $*.asm
else
	asmc64 -pe -Fo $@ $*.asm
endif
	$@
	pause

