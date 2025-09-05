include srcpath

$(lib_dir)\x64\directxmath.lib:
	asmc -win64 -I$(inc_dir) -BlLIBW -Cs -Zi -frame -r $(src_dir)\libs\directx\*.asm -link -q -b -n -c -fac $@
	del *.obj

regress:
	asmc -win64 -q -I$(inc_dir) $(src_dir)\libs\directx\directx.regress
	if not exist directx.exe exit
	directx.exe
	if errorlevel 1 exit
	cmd /C del directx.obj directx.exe
