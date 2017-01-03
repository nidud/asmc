regress:
	echo.
	echo.
	if exist *.exe del *.exe
	if exist *.obj del *.obj
	for %%f in (src\*.asm) do call :testasm %%f
	del *.exe
	echo.
	exit
	:error
	pause
	exit
	:testasm
	asmc -q -DDEBUG -I..\..\include %1
	linkw op q N %~n1.exe F ..\..\lib\c0.obj, %~n1.obj
	if not exist %~n1.exe goto end
	%~n1
	if errorlevel 1 goto error
	del %~n1.obj
	:end
