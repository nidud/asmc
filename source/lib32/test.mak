debug = 0

regress:
    #if exist *.exe del *.exe
    if exist *.obj del *.obj
    asmc -q -coff -Zi -assert -r *.s
    for %%f in (*.obj) do call :test_file %%f
    exit
    :test_file
!if $(debug)
    link /debug /subsystem:console libc.lib %~n1.obj
!else
    linkw sys con_32 file %~n1.obj
!endif
    if not exist %~n1.exe exit
    %~n1
    if errorlevel 1 exit
    dir > nul
    del %~n1.*

