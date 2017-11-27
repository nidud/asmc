Exception.exe:
	asmc -q -D_WIN64 -win64 $*.asm
	linkw system con_64 file $*
	$@
	pause
	del $@
	del $*.obj
