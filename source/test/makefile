regress:
	echo.
	echo.
	if exist *.exe del *.exe
	if exist *.obj del *.obj
	for %%f in (src\*.asm) do call :testasm %%f
	echo.
	del *.exe
	exit
	:testasm
	asmc -q -DDEBUG -I..\..\include %1
	linkw op q symt _cstart file %~n1.obj
	if not exist %~n1.exe exit
	%~n1
	if errorlevel 1 exit
	echo.
	del %~n1.obj

