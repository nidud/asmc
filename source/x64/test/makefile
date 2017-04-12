LIBDIR = %AsmcDir%\lib\x64

regress:
	if exist *.exe del *.exe
	if exist *.obj del *.obj
	for %%f in (src\*.asm) do call :testasm %%f
	exit
	:error
	pause
	exit
	:testasm
	asmc -q -coff -Zi -win64 -D_WIN64 -DDEBUG %1
	linkw op q N %~n1.exe LibP $(LIBDIR) L libcd, kernel32 F $(LIBDIR)\crtd.obj, %~n1.obj
	if not exist %~n1.exe goto end
	%~n1
	if errorlevel 1 goto error
	del %~n1.obj
	del %~n1.exe
	:end
