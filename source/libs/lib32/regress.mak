regress:
    if exist *.obj del *.obj
    asmc -q -coff -Zi -assert -r *.regress
    for %%f in (*.obj) do call :test_file %%f
    exit
    :test_file
    #\vc\bin\link /debug /subsystem:console /libpath:\Asmc\lib %~n1.obj
    linkw sys con_32 file %~n1.obj
    if not exist %~n1.exe exit
    %~n1
    if errorlevel 1 exit
    cmd /C del %~n1.obj %~n1.exe

