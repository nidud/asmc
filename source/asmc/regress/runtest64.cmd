@echo off

SET ASMX=%1
if (%1)==() SET ASMX=..\..\asmc64.exe

if not exist tmp md tmp
cd tmp

for %%f in (..\src\bin64\*.asm) do call :cmpbin %%f
for %%f in (..\src\win64\*.asm) do call :win64 %%f
for %%f in (..\src\elf64\*.asm) do call :elf64 %%f
for %%f in (..\src\vec64\*.asm) do call :vec64 %%f
for %%f in (..\src\err64\*.asm) do call :cmperr %%f
for %%f in (..\src\bin64\*.asm) do call :cv8 %%f
for %%f in (..\src\win64\*.asm) do call :cv8 %%f
for %%f in (..\src\vec64\*.asm) do call :cv8Gv %%f
cd ..
exit

:cmperr
%ASMX% -q -W3 %1 >NUL
fcmp %~n1.err ..\exp64\%~n1.err
if errorlevel 1 goto end
del %~n1.err
if exist %~n1.obj del %~n1.obj
goto end

:cmpbin
%ASMX% -q -bin %1
fcmp %~n1.bin ..\exp\%~n1.bin
if errorlevel 1 goto end
del %~n1.bin
goto end

:win64
%ASMX% -q %1
if errorlevel 1 goto end
fcmp -coff %~n1.OBJ ..\exp\%~n1.OBJ
if errorlevel 1 goto end
del %~n1.OBJ
goto end

:vec64
%ASMX% -q -Gv %1
if errorlevel 1 goto end
fcmp -coff %~n1.OBJ ..\exp\%~n1.OBJ
if errorlevel 1 goto end
del %~n1.OBJ
goto end

:elf64
%ASMX% -q -elf64 %1
if errorlevel 1 goto end
fcmp %~n1.OBJ ..\exp\%~n1.obj
if errorlevel 1 goto end
del %~n1.OBJ
goto end

:cv8
%ASMX% -q -Zi8 %1
fcmp -coff %~n1.obj ..\expcv\%~n1.obj
if errorlevel 1 goto end
del %~n1.obj
goto end

:cv8Gv
%ASMX% -q -Zi8 -Gv %1
fcmp -coff %~n1.obj ..\expcv\%~n1.obj
if errorlevel 1 goto end
del %~n1.obj
goto end

:end

