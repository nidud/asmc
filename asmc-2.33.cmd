@echo off

%~d0
cd %~dp0

if not exist %~dp0bin\envars32.bat %~dp0bin\make.exe -install

call %~dp0bin\envars32.bat

echo.
asmc -logo
echo.
echo AsmcDir: %AsmcDir%

if not exist %~dp0lib\x86\user32.lib (
    choice /c YN /M "32-bit Import Libraries Missing: Build them now"
    if not errorlevel 2 call :ImportLibraries32
)
if not exist %~dp0lib\x86\libc.lib (
    choice /c YN /M "32-bit Runtime Library Missing: Build it now"
    if not errorlevel 2 call :BuildCRT32
)
if not exist %~dp0lib\x64\user32.lib (
    choice /c YN /M "64-bit Import Libraries Missing: Build them now"
    if not errorlevel 2 call :ImportLibraries64
)
if not exist %~dp0lib\x64\libc.lib (
    choice /c YN /M "64-bit Runtime Library Missing: Build it now"
    if not errorlevel 2 call :BuildCRT64
)

echo.
if exist %AsmcDir%\bin\dz.ini (
dz -nologo
) else (
echo Esc toggles panels
echo.
dz -cmd -nologo
)
goto end

:BuildCRT32
cd %AsmcDir%\source\libs\lib32
make
cd %AsmcDir%
echo.
goto end

:BuildCRT64
cd %AsmcDir%\source\libs\lib64
make
cd %AsmcDir%
echo.
goto end

:BuildUUID
cd %AsmcDir%\source\libs\uuid
make
cd %AsmcDir%
echo.
goto end

:ImportLibraries32
cd %AsmcDir%\lib\x86
make
cd %AsmcDir%
echo.
goto end

:ImportLibraries64
cd %AsmcDir%\lib\x64
make
cd %AsmcDir%
echo.

:end
