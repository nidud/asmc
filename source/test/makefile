regress:
	echo.
	echo.
	if exist *.exe del *.exe
	if exist *.obj del *.obj
	for %%f in (src\*.asm) do call :testasm %%f
	echo.
	exit
	:testasm
	asmc -q -DDEBUG -I..\..\include %1
	linkw op q N %~n1.exe L libc F ..\..\lib\crt.obj, %~n1.obj
	if not exist %~n1.exe exit
	%~n1
	if errorlevel 1 exit
	del %~n1.obj
	del %~n1.exe

