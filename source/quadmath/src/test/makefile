
all: regress32 regress64

regress32:
    if exist *.exe del *.exe
    if exist *.obj del *.obj
    asmc -q -assert D:\asmc\source\quadmath\src\test\x86\*.asm
    for %%f in (*.obj) do call :test32 %%f
    exit
    :test32
    linkw op q system con_32 file %~n1.obj
    if not exist %~n1.exe exit
    .\%~n1.exe
    if errorlevel 1 exit
    dir > nul
    del %~n1.obj
    del %~n1.exe

regress64:
    if exist *.exe del *.exe
    if exist *.obj del *.obj
    asmc -q -assert -win64 x64\*.asm
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

