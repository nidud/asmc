LIBDIR = %AsmcDir%\lib\x64

test.exe:
	asmc /win64 /D_WIN64 $*.asm
	linkw @<<
Name	$@
LibPath $(LIBDIR)
Lib	kernel32.lib, user32.lib
Format	win pe ru win
File	$*.obj
Option	start=start
<<
	$@

