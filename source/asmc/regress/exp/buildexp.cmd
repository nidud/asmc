@echo off

REM
REM BUILDEXP [<ASMC> [<MSLINK>]]
REM
REM Use a version that passed the test as base
REM

SET MLBASE=%AsmcDir%\bin\asmc.exe
if NOT (%1)==() SET MLBASE=%1

SET OWLINK=%AsmcDir%\bin\linkw.exe

REM MS LINK >= 8.0 is needed for testing SAFESEH
SET MSLINK=%DZDRIVE%\VC9\bin\link.exe
if NOT (%2)==() SET MSLINK=%2

cd ..

for %%f in (src\bin\*.asm) do call :cmpbin %%f
for %%f in (src\bin64\*.asm) do call :cmpbin %%f
for %%f in (src\mz\*.asm)  do call :cmpmz  %%f
for %%f in (src\err\*.asm) do call :cmperr %%f
for %%f in (src\omf\*.asm) do call :lnkomf %%f
for %%f in (src\omf\*.asm) do call :cmpomf %%f
for %%f in (src\coff\*.asm) do call :coff %%f
for %%f in (src\cofferr\*.asm) do call :cofferr %%f
for %%f in (src\win64\*.asm) do call :win64 %%f
for %%f in (src\coffdbg\*.asm) do call :coffdbg %%f
for %%f in (src\pe\*.asm) do call :pe %%f
for %%f in (src\zne\*.asm) do call :zne %%f
for %%f in (src\zg\*.asm) do call :zg %%f
for %%f in (src\zd\*.asm) do call :zd %%f
for %%f in (src\binerr\*.asm) do call :binerr %%f
for %%f in (src\ifdef\*.asm) do call :ifdef %%f
for %%f in (src\elf\*.asm) do call :elf %%f
for %%f in (src\omf2\*.asm) do call :omf2 %%f
for %%f in (src\omfcu\*.asm) do call :omfcu %%f
for %%f in (src\elf64\*.asm) do call :elf64 %%f
for %%f in (src\vec64\*.asm) do call :vec64 %%f

call :safeseh
call :dllimp

rem del *.*
exit

:cmpbin
%MLBASE% -c -q -bin -Fo exp\%~n1.bin %1
goto end

:cmpmz
%MLBASE% -c -q -mz -Fo exp\%~n1.exe %1
goto end

:cmperr
%MLBASE% -c -q -W3 -omf %1 > exp\%~n1.err
goto end

:cmpomf
%MLBASE% -c -q -omf -Fo exp\%~n1.obj %1
goto end

:lnkomf
if (%OWLINK%) == () goto end
%MLBASE% -c -q -omf %1
%OWLINK% n exp\%~n1.exe op q,nofar format dos LIBPath src\omf file %~n1.obj
goto end

:safeseh
if (%MSLINK%) == () goto end
%MLBASE% -c -q -coff -safeseh src\safeseh\safeseh.asm
%MSLINK% /out:exp\safeseh.exe /nologo /SAFESEH safeseh.obj src\safeseh\safeseh.lib
goto end

:coff
%MLBASE% -c -q -coff -Fo exp\%~n1.obj %1
goto end

:cofferr
%MLBASE% -c -q -coff -eq %1
copy %~n1.err exp\%~n1.err
goto end

:win64
%MLBASE% -c -q -win64 -Fo exp\%~n1.obj %1
goto end

:vec64
%MLBASE% -c -q -Gv -win64 -Fo exp\%~n1.obj %1
goto end

:coffdbg
%MLBASE% -c -q -coff -Zi -Fo exp\%~n1.obj %1
goto end

:dllimp
if (%OWLINK%) == () goto extern
%MLBASE% -c -q -coff -Fd src\dllimp\dllimp.asm
%OWLINK% name exp\dllimp.exe format win pe f dllimp.obj op q,noreloc
:extern
if (%MSLINK%) == () goto end
%MLBASE% -c -q -coff src\extern\extern4.asm
%MSLINK% /out:exp\extern4.exe /nologo /subsystem:console extern4.obj
goto end

:ifdef
%MLBASE% -c -q -zlc -zld -Fo exp\%~n1.obj %1
goto end

:elf
%MLBASE% -c -q -elf -Fo exp\%~n1.o %1
goto end

:elf64
%MLBASE% -c -q -elf64 -Fo exp\%~n1.o %1
goto end

:omfcu
%MLBASE% -c -q -Cu -Fo exp\%~n1.obj %1
goto end

:omf2
%MLBASE% -c -q -Fo exp\%~n1.obj %1
goto end

:pe
%MLBASE% -c -q -pe -Fo exp\%~n1.exe %1
goto end

:zne
%MLBASE% -c -q -eq -Zne %1
copy %~n1.err exp\%~n1.err
goto end

:zg
%MLBASE% -c -q -Zg -bin -Fo exp\%~n1.bin %1
goto end

:zd
%MLBASE% -c -q -Zd -omf -Fo exp\%~n1.obj %1
goto end

:binerr
%MLBASE% -c -q -eq -bin %1
copy %~n1.err exp\%~n1.err
goto end

:end
