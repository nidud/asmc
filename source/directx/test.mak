regress:
    if exist *.exe del *.exe
    if exist *.obj del *.obj
    asmc64 -q -assert -r *.s
    for %%f in (*.obj) do call :test64 %%f
    exit
    :test64
    linkw op q system con_64 file %~n1.obj
    if not exist %~n1.exe exit
    .\%~n1.exe
    if errorlevel 1 exit
    dir > nul
    del %~n1.obj
    del %~n1.exe

