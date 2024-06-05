include srcpath

DesktopDuplication.exe:
if 1
	asmc -8 -I$(inc_dir) *.asm
	linkw op map name $@ system gui_32 file { *.obj }
else
	asmc64 -I$(inc_dir) *.asm
	linkw name $@ system gui_64 file { *.obj }
endif
	del *.obj
	$@
