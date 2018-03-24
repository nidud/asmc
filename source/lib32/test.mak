regress:
    if exist *.exe del *.exe
    if exist *.obj del *.obj
    asmc -q -assert -r *.s
    for %%f in (*.obj) do call :test_file %%f
    exit
    :test_file
    linkw op q system con_32 file %~n1.obj
    if not exist %~n1.exe exit
    %~n1
    if errorlevel 1 exit
    dir > nul
    del %~n1.obj
    del %~n1.exe

