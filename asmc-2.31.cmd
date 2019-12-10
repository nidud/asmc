@echo off

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
    echo Imports: %~dp0lib
)
if not exist %~dp0lib\libc.lib (
    choice /N /M "32-bit Runtime Library Missing: Build it now ? "
    if not errorlevel 2 call :BuildCRT32
) else (
    echo Runtime: %~dp0lib\libc.lib
)
if exist %~dp0lib\uuid.lib (
    echo Library: %~dp0lib\uuid.lib
) else (
    echo Missing: %~dp0lib\uuid.lib
)
if exist %~dp0lib\quadmath.lib (
    echo Library: %~dp0lib\quadmath.lib
) else (
    echo Missing: %~dp0lib\quadmath.lib
)
if exist %~dp0lib\consxc.lib (
    echo Library: %~dp0lib\consxc.lib
) else (
    echo Missing: %~dp0lib\consxc.lib
)
echo.

if not exist %~dp0lib\amd64\user32.lib (
    choice /N /M "64-bit Import Libraries Missing: Build them now ? "
    if not errorlevel 2 call :ImportLibraries64
) else (
    echo Imports: %~dp0lib\amd64
)
if not exist %~dp0lib\amd64\libc.lib (
    choice /N /M "64-bit Runtime Library Missing: Build it now ? "
    if not errorlevel 2 call :BuildCRT64
) else (
    echo Runtime: %~dp0lib\amd64\libc.lib
)
if exist %~dp0lib\amd64\uuid.lib (
    echo Library: %~dp0lib\amd64\uuid.lib
) else (
    echo Missing: %~dp0lib\amd64\uuid.lib
)
if exist %~dp0lib\amd64\quadmath.lib (
    echo Library: %~dp0lib\amd64\quadmath.lib
) else (
    echo Missing: %~dp0lib\amd64\quadmath.lib
)
if exist %~dp0lib\amd64\directxmath.lib (
    echo Library: %~dp0lib\amd64\directxmath.lib
) else (
    echo Missing: %~dp0lib\amd64\directxmath.lib
)

echo.
echo Esc toggle panels
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
