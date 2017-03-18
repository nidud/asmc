@echo off

if not exist exp md exp
if not exist tmp md tmp

cd tmp

for %%f in (..\src\*.asm) do call :cmpbin %%f
cd ..
exit

:cmpbin
asmc -q -bin %1
fcmp %~n1.bin ..\exp\%~n1.bin
if errorlevel 1 goto end
del %~n1.bin
:end

