regress:
    if exist *.obj del *.obj
    asmc -q -assert -win64 -r *.regress
    for %%f in (*.obj) do call :make %%f
    exit
    :make
    linkw op q sys con_64 f %~n1
    if not exist %~n1.exe exit
    %~n1.exe
    if errorlevel 1 exit
    cmd /C del %~n1.obj %~n1.exe

