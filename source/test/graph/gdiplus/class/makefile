test:
	if not exist x86\*.obj make build
	for %%f in (src\*.asm) do call :cmpx86 %%f
	for %%f in (src\*.asm) do call :cmpx64 %%f
	exit
	:cmpx86
	asmc -c -q -8 -coff %1
	if errorlevel 1 goto end
	fcmp -coff %~n1.OBJ x86\%~n1.OBJ
	if errorlevel 1 goto end
	del %~n1.OBJ
	goto end
	:cmpx64
	asmc64 -c -q %1
	if errorlevel 1 goto end
	fcmp -coff %~n1.OBJ x64\%~n1.OBJ
	if errorlevel 1 goto end
	del %~n1.OBJ
	goto end
	:end

build:
	md x86
	md x64
	asmc64 -c -Fo x64\* src\*.asm
	asmc -c -coff -8 -Fo x86\* src\*.asm
