!include srcpath

$(lib_x64)\libc.lib:
	asmc /win64 /D_WIN64 /Cs /Zi /I$(inc_dir) /r $(src_x64)\libc\*.asm
	libw /q /b /n /c /fac $@ *.obj
	del *.obj

