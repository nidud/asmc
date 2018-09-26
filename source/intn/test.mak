
all: test32 test64

test32:
    if exist *.obj del *.obj
    asmc -q -coff -Zi -assert -r x86\*.s
    for %%f in (*.obj) do call :test_32 %%f
    exit
    :test_32
    linkw sys con_32 file %~n1.obj
    if not exist %~n1.exe exit
    %~n1
    if errorlevel 1 exit
    dir > nul
    del %~n1.*

test64:
    if exist *.exe del *.exe
    if exist *.obj del *.obj
    asmc64 -q -assert -r x64\*.s
    for %%f in (*.obj) do call :test_64 %%f
    exit
    :test_64
    linkw op q system con_64 file %~n1.obj
    if not exist %~n1.exe exit
    .\%~n1.exe
    if errorlevel 1 exit
    dir > nul
    del %~n1.obj
    del %~n1.exe
