@echo off

REM
REM BUILDEXP64 [<ASMC>]
REM

SET MLBASE=%AsmcDir%\bin\asmc.exe
if NOT (%1)==() SET MLBASE=%1

cd ..
if not exist tmp md tmp
cd tmp

for %%f in (..\src\bin64\*.asm) do call :cv8bin %%f
for %%f in (..\src\vec64\*.asm) do call :cv8Gv %%f
for %%f in (..\src\win64\*.asm) do call :cv8 %%f

rem del *.*
exit

:cv8
%MLBASE% -q -win64 -Zi8 %1
copy %~n1.obj ..\exp64\%~n1.obj
goto end

:cv8bin
%MLBASE% -q -win64 -D__ASMC64__ -Zi8 %1
copy %~n1.obj ..\exp64\%~n1.obj
goto end

:cv8Gv
%MLBASE% -q -win64 -Gv -Zi8 %1
copy %~n1.obj ..\exp64\%~n1.obj
goto end

:end
