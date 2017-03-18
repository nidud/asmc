!include srcpath

.all:
	asmc -pe -D__PE__ -Fo win32Ape.exe test.asm
	asmc -ws -pe -D__PE__ -D_UNICODE -Fo win32Wpe.exe test.asm
	asmc -pe -D__PE__ -D_WIN64 -Fo win64Ape.exe test.asm
	asmc -ws -pe -D__PE__ -D_WIN64 -D_UNICODE -Fo win64Wpe.exe test.asm

	asmc test.asm
	linkw N win32A.exe L libc F $(lib_dir)\crt, test
	asmc -ws -D_UNICODE test.asm
	linkw N win32W.exe L libcw F $(lib_dir)\crtw, test
	asmc -win64 -D_WIN64 test.asm
	linkw N win64A.exe LibP $(lib_dir)\x64 L kernel32, user32, libc F $(lib_dir)\x64\crt, test
	asmc -win64 -ws -D_WIN64 -D_UNICODE test.asm
	linkw N win64W.exe LibP $(lib_dir)\x64 L kernel32, user32, libcw F $(lib_dir)\x64\crtw, test

	del test.obj
	pause

