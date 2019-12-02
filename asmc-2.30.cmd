@echo off
cls
%~d0
cd %~dp0
set PATH=%~dp0bin;%PATH%
set INCLUDE=%~dp0include;%INCLUDE%

echo.
asmc -logo
echo.

if not exist %~dp0lib\user32.lib (
    choice /N /M "32-bit Import Libraries Missing: Build them now ? "
    if not errorlevel 2 call :ImportLibraries32
) else (
    echo 32-bit Import Libraries %~dp0lib
)

if not exist %~dp0lib\amd64\user32.lib (
    choice /N /M "64-bit Import Libraries Missing: Build them now ? "
    if not errorlevel 2 call :ImportLibraries64
) else (
    echo 64-bit Import Libraries %~dp0lib\amd64
)
echo.
if not exist %~dp0lib\libc.lib (
    choice /N /M "32-bit Runtime Library Missing: Build it now ? "
    if not errorlevel 2 call :BuildCRT32
) else (
    echo 32-bit Runtime Library: %~dp0lib\libc.lib
)

if not exist %~dp0lib\amd64\libc.lib (
    choice /N /M "64-bit Runtime Library Missing: Build it now ? "
    if not errorlevel 2 call :BuildCRT64
) else (
    echo 64-bit Runtime Library: %~dp0lib\amd64\libc.lib
)

echo.
echo Esc toggles panels
echo.

dz -cmd -nologo
goto end

rem Build libraries

:ImportLibraries32
cd %~dp0lib
make
cd ..
echo.
goto end

:ImportLibraries64
cd %~dp0lib\amd64
make
cd ..\..
echo.
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

:end
