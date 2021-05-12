@echo off

REM
REM BUILDEXPCV [<ASMC64>]
REM

SET MLBASE=%AsmcDir%\bin\asmc64.exe
if NOT (%1)==() SET MLBASE=%1

cd ..
if not exist tmp md tmp
cd tmp

for %%f in (..\src\bin64\*.asm) do call :cv8 %%f
for %%f in (..\src\win64\*.asm) do call :cv8 %%f
for %%f in (..\src\vec64\*.asm) do call :cv8Gv %%f

rem del *.*
exit

:cv8
%MLBASE% -q -Zi8 %1
copy %~n1.obj ..\expcv\%~n1.obj
goto end

:cv8Gv
%MLBASE% -q -Gv -Zi8 %1
copy %~n1.obj ..\expcv\%~n1.obj
goto end

:end
