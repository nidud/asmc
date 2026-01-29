
watcom = 1

SetDesktopWallpaper.exe:
	asmc64 -c -q -ws -Cs -Zp8 *.asm
!if $(watcom)
	wrc -q -r $*.rc
	linkw system gui_64W file { *.obj } option RESource=$*.res
!else
	rc $*.rc
	link *.obj $*.res
!endif
	del $*.res
	del *.obj
