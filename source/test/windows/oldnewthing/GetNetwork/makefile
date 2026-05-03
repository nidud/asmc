include srcpath

winrt.exe:
	asmc64 -nologo -pe -ws -I$(inc_dir) winrt.asm
	winrt
	asmc64 -nologo -pe -ws -I$(inc_dir) win32.asm
	win32
	pause
	del *.exe
