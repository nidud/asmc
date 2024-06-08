include srcpath

winrt.exe:
	asmc64 -pe -ws -I$(inc_dir) winrt.asm
	winrt
	asmc64 -pe -ws -I$(inc_dir) win32.asm
	win32
	pause
