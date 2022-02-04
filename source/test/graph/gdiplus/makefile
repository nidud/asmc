
build_samples:
    if not exist x86\NUL md x86
    if not exist x64\NUL md x64
    for %%q in (*.asm) do call :build %%q
    exit
    :build
    asmc -nologo -8 -ws -pe -gui -Fo x86\%~n1.exe %1
    asmc -q -win64  -ws -pe -gui -Fo x64\%~n1.exe %1

