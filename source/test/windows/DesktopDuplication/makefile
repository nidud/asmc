include srcpath

DesktopDuplication.exe:
if 1
	asmc -q -coff -8 -I$(inc_dir) *.asm
else
	asmc64 -q -I$(inc_dir) *.asm
endif
	del *.obj
	$@

vs:
	project -p -w DesktopDuplication
