
all: regress32 regress64

regress:
    make -s regress32
    make -s regress64

regress32:
    echo regress32
    if exist *.obj del *.obj
    asmc -q -coff -Zi -assert -r *.regress
    for %%f in (*.obj) do call :test_file %%f
    exit
    :test_file
    linkw sys con_32 file %~n1.obj
    if not exist %~n1.exe exit
    %~n1.exe
    if errorlevel 1 exit
    cmd /C del %~n1.obj %~n1.exe

regress64:
    echo regress64
    if exist *.obj del *.obj
    asmc64 -q -assert -r *.regress
    for %%f in (*.obj) do call :make %%f
    exit
    :make
    linkw op q sys con_64 f %~n1
    if not exist %~n1.exe exit
    %~n1.exe
    if errorlevel 1 exit
    cmd /C del %~n1.obj %~n1.exe

