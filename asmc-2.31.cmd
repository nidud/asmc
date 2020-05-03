@echo off

%~d0
cd %~dp0

if not exist %~dp0bin\envars32.bat %~dp0bin\make.exe -install

call %~dp0bin\envars32.bat

echo.
asmc -logo
echo.
echo AsmcDir: %AsmcDir%

if not exist %~dp0lib\user32.lib (
    choice /c YN /M "32-bit Import Libraries Missing: Build them now"
    if not errorlevel 2 call :ImportLibraries32
)
if not exist %~dp0lib\libc.lib (
    choice /c YN /M "32-bit Runtime Library Missing: Build it now"
    if not errorlevel 2 call :BuildCRT32
)
if not exist %~dp0lib\amd64\user32.lib (
    choice /c YN /M "64-bit Import Libraries Missing: Build them now"
    if not errorlevel 2 call :ImportLibraries64
)
if not exist %~dp0lib\amd64\libc.lib (
    choice /c YN /M "64-bit Runtime Library Missing: Build it now"
    if not errorlevel 2 call :BuildCRT64
)
if not exist %~dp0lib\amd64\uuid.lib echo Missing: lib\amd64\uuid.lib
if not exist %~dp0lib\amd64\quadmath.lib echo Missing: lib\amd64\quadmath.lib
if not exist %~dp0lib\amd64\directxmath.lib echo Missing: lib\amd64\directxmath.lib

echo.
echo Esc toggles panels
echo.
dz -cmd -nologo
goto end

:BuildCRT32
cd %~dp0source\lib32
make
cd ..\..
echo.
goto end

:BuildCRT64
cd %~dp0source\lib64
make
cd ..\..
echo.
goto end

:BuildUUID
cd %~dp0source\uuid
make
cd ..\..
echo.
goto end

:ImportLibraries32
cd %~dp0source\import
make
cd ..\..
echo.
goto end

:ImportLibraries64
cd %~dp0source\import\x64
make
cd ..\..\..
echo.

:end
