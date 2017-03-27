@echo off

if not exist tmp md tmp
cd tmp

for %%f in (..\src\*.asm) do call :cmp32 %%f
for %%f in (..\src\x64\*.asm) do call :cmp64 %%f
cd ..
exit

:cmp32
asmc -q -Zp4 -bin %1
fcmp %~n1.bin ..\exp\%~n1.bin
if errorlevel 1 goto end
del %~n1.bin
goto end

:cmp64
asmc /q -Zp8 /D__PE__ /D_WIN64 /win64 /bin %1
fcmp %~n1.bin ..\exp\%~n1.bin
if errorlevel 1 goto end
del %~n1.bin

:end

