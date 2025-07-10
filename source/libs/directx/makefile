include srcpath

$(lib_dir)\x64\directxmath.lib:
	asmc64 -I$(inc_dir) -BlLIBW -Cs -Zi -frame -r *.asm -link -q -b -n -c -fac $@
	del *.obj

regress:
	asmc64 -q -I$(inc_dir) directx.regress
	if not exist directx.exe exit
	directx.exe
	if errorlevel 1 exit
	cmd /C del directx.obj directx.exe
