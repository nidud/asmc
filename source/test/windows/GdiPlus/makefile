
build_samples:
	if not exist x86\NUL md x86
	if not exist x64\NUL md x64
	asmc -8 -ws -peg -Fo x86\* *.asm
	asmc -Zp8 -win64 -ws -peg -Fo x64\* *.asm

clean:
	if exist x86\NUL del /Q x86\*.*
	if exist x64\NUL del /Q x64\*.*
	if exist x86\NUL rd x86
	if exist x64\NUL rd x64

