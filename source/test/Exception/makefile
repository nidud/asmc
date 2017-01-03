
Exception.exe:
	asmc -q $*.asm
	linkw @<<
Name	$@
Option	q
LibPath \Asmc\lib
Lib	libo, kernel32
File	\Asmc\lib\c0, $*.obj
<<
	del $*.obj
	$@
	pause

