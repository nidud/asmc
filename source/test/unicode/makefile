!include srcpath

regress:
	echo.
	echo.
	if exist *.exe del *.exe
	if exist *.obj del *.obj
	for %%f in (src\*.asm) do call :testasm %%f
	echo.
	exit
	:testasm
	asmc -q -ws -D_UNICODE -DDEBUG -I$(inc_dir) %1
	linkw op q N %~n1.exe L $(lib_dir)\libcw F $(lib_dir)\crtw, %~n1
	if not exist %~n1.exe exit
	%~n1
	if errorlevel 1 exit
	del %~n1.obj
	del %~n1.exe

