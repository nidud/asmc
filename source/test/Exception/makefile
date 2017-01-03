
LIB = %LIB%

Exception.exe:
	asmc -q $*.asm
	linkw @<<
Name	$@
Option	q
LibPath $(LIB)
Lib	libo, kernel32
File	$(LIB)\c0, $*.obj
<<
	del $*.obj
	$@
	pause

