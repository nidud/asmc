@echo off

%~d0
cd %~dp0

if not exist %~dp0bin\envars32.bat %~dp0bin\make.exe -install

call %~dp0bin\envars32.bat

echo.
asmc -logo
echo.
echo AsmcDir: %AsmcDir%

if not exist %~dp0lib\x86\libc.lib (
    choice /c YN /M "Runtime Library Missing: Build it now"
    if not errorlevel 2 (
        make -fsource\libc\makefile
        make -fsource\libc\makefile x86=1
        make -fsource\libc\makefile linux
    )
)

if not exist %~dp0lib\x86\user32.lib (
    echo.
    choice /c YN /M "32-bit Import Libraries Missing: Build them now"
    if not errorlevel 2 make -flib\x86\makefile
)

if not exist %~dp0lib\x64\user32.lib (
    echo.
    choice /c YN /M "64-bit Import Libraries Missing: Build them now"
    if not errorlevel 2 make -flib\x64\makefile
)

cls
if exist %AsmcDir%\bin\dz.ini (
    dz -nologo
) else (
    echo Esc toggles panels
    echo.
    dz -cmd -nologo
)
