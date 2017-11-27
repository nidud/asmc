regress:
    if exist *.exe del *.exe
    if exist *.obj del *.obj
    asmc -q -assert -I..\..\..\include -r *.r32
    for %%f in (*.obj) do call :test32 %%f
    asmc -q -assert -I..\..\..\include -win64 -r *.r64
    for %%f in (*.obj) do call :test64 %%f
    exit
    :test64
    linkw op q system con_64 file %~n1.obj
    goto test_exe
    :test32
    linkw op q system con_32 file %~n1.obj
    :test_exe
    if not exist %~n1.exe exit
    %~n1
    if errorlevel 1 exit
    dir > nul
    del %~n1.obj
    del %~n1.exe

