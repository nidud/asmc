@echo off

SET ASMX=%1
if (%1)==() SET ASMX=..\asmc.exe

SET OWLINK=%AsmcDir%\bin\linkw.exe

REM MS LINK >= 8.0 is needed for testing SAFESEH.
SET MSLINK=%DZDRIVE%\tools\VC9\bin\link.exe

for %%f in (src\bin\*.asm) do call :cmpbin %%f
for %%f in (src\bin64\*.asm) do call :cmpbin %%f
for %%f in (src\mz\*.asm)  do call :cmpmz  %%f
for %%f in (src\err\*.asm) do call :cmperr %%f
for %%f in (src\zneerr\*.asm) do call :zneerr %%f
for %%f in (src\omf\*.asm) do call :lnkomf %%f
for %%f in (src\omf\*.asm) do call :cmpomf %%f
for %%f in (src\coff\*.asm) do call :coff %%f
for %%f in (src\cofferr\*.asm) do call :cofferr %%f
for %%f in (src\win64\*.asm) do call :win64 %%f
for %%f in (src\coffdbg\*.asm) do call :coffdbg %%f
for %%f in (src\pe\*.asm) do call :pe %%f
for %%f in (src\zg\*.asm) do call :zg %%f
for %%f in (src\zd\*.asm) do call :zd %%f
for %%f in (src\binerr\*.asm) do call :binerr %%f
for %%f in (src\ifdef\*.asm) do call :ifdef %%f
for %%f in (src\elf\*.asm) do call :elf %%f
for %%f in (src\omf2\*.asm) do call :omf2 %%f
for %%f in (src\omfcu\*.asm) do call :omfcu %%f
for %%f in (src\elf64\*.asm) do call :elf64 %%f
for %%f in (src\vec64\*.asm) do call :vec64 %%f
for %%f in (src\bin64\*.asm) do call :cv8bin %%f
for %%f in (src\vec64\*.asm) do call :cv8Gv %%f
for %%f in (src\win64\*.asm) do call :cv8 %%f
for %%f in (src\zne\*.asm) do call :zne %%f
for %%f in (src\zne64\*.asm) do call :zne %%f
for %%f in (src\zneomf\*.asm) do call :zneomf %%f

call :safeseh
call :dllimp

exit

:cmpbin
%ASMX% -q -bin %1
fcmp %~n1.bin exp\%~n1.bin
if errorlevel 1 goto end
del %~n1.bin
goto end

:cmpmz
%ASMX% -q -mz %1
fcmp %~n1.exe exp\%~n1.exe
if errorlevel 1 goto end
del %~n1.exe
goto end

:cmperr
%ASMX% -c -q -W3 -omf %1 >NUL
fcmp %~n1.err exp\%~n1.err
if errorlevel 1 goto end
del %~n1.err
if exist %~n1.obj del %~n1.obj
goto end

:zneerr
%ASMX% -c -q -Zne -W3 -omf %1 >NUL
fcmp %~n1.err exp\%~n1.err
if errorlevel 1 goto end
del %~n1.err
if exist %~n1.obj del %~n1.obj
goto end

:zneomf
%ASMX% -c -q -Zne -omf %1
if errorlevel 1 goto end
fcmp %~n1.obj exp\%~n1.obj
if errorlevel 1 goto end
del %~n1.obj
if (%OWLINK%) == () goto end
%ASMX% -c -q -Zne -omf %1
if errorlevel 1 goto end
%OWLINK% op q,nofar format dos LIBPath src\omf file %~n1.obj
fcmp %~n1.exe exp\%~n1.exe
if errorlevel 1 goto end
del %~n1.obj
del %~n1.exe
goto end

:cmpomf
%ASMX% -c -q -omf %1
if errorlevel 1 goto end
fcmp %~n1.obj exp\%~n1.obj
if errorlevel 1 goto end
del %~n1.obj
goto end

:lnkomf
if (%OWLINK%) == () goto end
%ASMX% -c -q -omf %1
if errorlevel 1 goto end
%OWLINK% op q,nofar format dos LIBPath src\omf file %~n1.obj
fcmp %~n1.exe exp\%~n1.exe
if errorlevel 1 goto end
del %~n1.obj
del %~n1.exe
goto end

:safeseh
if (%MSLINK%) == () goto end
%ASMX% -c -q -coff -safeseh src\safeseh\safeseh.asm
if errorlevel 1 exit
%MSLINK% /nologo /SAFESEH safeseh.obj src\safeseh\safeseh.lib
fcmp -p SAFESEH.EXE exp\SAFESEH.EXE
if errorlevel 1 goto end
del SAFESEH.EXE
del SAFESEH.OBJ
goto end

:coff
%ASMX% -c -q -coff %1
if errorlevel 1 goto end
fcmp -coff %~n1.OBJ exp\%~n1.OBJ
if errorlevel 1 goto end
del %~n1.OBJ
goto end

:cofferr
%ASMX% -c -q -coff -eq %1
fcmp %~n1.err exp\%~n1.err
if errorlevel 1 goto end
del %~n1.err
goto end

:win64
%ASMX% -c -q -win64 %1
if errorlevel 1 exit
fcmp -coff %~n1.OBJ exp\%~n1.OBJ
if errorlevel 1 goto end
del %~n1.OBJ
goto end

:vec64
%ASMX% -c -q -win64 -Gv %1
if errorlevel 1 exit
fcmp -coff %~n1.OBJ exp\%~n1.OBJ
if errorlevel 1 goto end
del %~n1.OBJ
goto end

:coffdbg
%ASMX% -c -q -coff -Zi %1
if errorlevel 1 exit
fcmp -coff %~n1.OBJ exp\%~n1.OBJ
if errorlevel 1 goto end
del %~n1.OBJ
goto end

:dllimp
if (%OWLINK%) == () goto extern
%ASMX% -c -q -coff -Fd src\dllimp\dllimp.asm
if errorlevel 1 exit
%OWLINK% format win pe f dllimp.obj op q,noreloc
fcmp -pe DLLIMP.EXE exp\DLLIMP.EXE
if errorlevel 1 goto end
del DLLIMP.EXE
del DLLIMP.OBJ
:extern
if (%MSLINK%) == () goto end
%ASMX% -c -q -coff src\extern\extern4.asm
if errorlevel 1 exit
%MSLINK% /nologo /subsystem:console extern4.obj
fcmp -pe EXTERN4.EXE exp\EXTERN4.EXE
if errorlevel 1 goto end
del EXTERN4.EXE
del EXTERN4.OBJ
goto end

:ifdef
%ASMX% -c -q -zlc -zld %1
if errorlevel 1 exit
fcmp %~n1.OBJ exp\%~n1.obj
if errorlevel 1 goto end
del %~n1.OBJ
goto end

:elf
%ASMX% -c -q -elf %1
if errorlevel 1 exit
fcmp %~n1.o exp\%~n1.o
if errorlevel 1 goto end
del %~n1.o
goto end

:elf64
%ASMX% -c -q -elf64 %1
if errorlevel 1 exit
fcmp %~n1.o exp\%~n1.o
if errorlevel 1 goto end
del %~n1.o
goto end

:omfcu
%ASMX% -c -q -Cu %1
if errorlevel 1 exit
fcmp %~n1.OBJ exp\%~n1.obj
if errorlevel 1 goto end
del %~n1.OBJ
goto end

:omf2
%ASMX% -c -q %1
if errorlevel 1 exit
fcmp %~n1.OBJ exp\%~n1.obj
if errorlevel 1 goto end
del %~n1.OBJ
goto end

:pe
%ASMX% -q -pe %1
fcmp -pe %~n1.EXE exp\%~n1.EXE
if errorlevel 1 goto end
del %~n1.EXE
goto end

:zg
%ASMX% -q -Zg -bin %1
fcmp %~n1.BIN exp\%~n1.bin
if errorlevel 1 goto end
del %~n1.BIN
goto end

:zd
%ASMX% -c -q -Zd -omf %1
fcmp %~n1.OBJ exp\%~n1.obj
if errorlevel 1 goto end
del %~n1.OBJ
goto end

:binerr
%ASMX% -c -q -eq -bin %1
fcmp %~n1.ERR exp\%~n1.err
if errorlevel 1 goto end
del %~n1.ERR
goto end

:cv8
%ASMX% -c -q -win64 -Zi8 %1
fcmp -coff %~n1.obj exp64\%~n1.obj
if errorlevel 1 goto end
del %~n1.obj
goto end

:cv8bin
%ASMX% -c -q -win64 -D__ASMC64__ -Zi8 %1
fcmp -coff %~n1.obj exp64\%~n1.obj
if errorlevel 1 goto end
del %~n1.obj
goto end

:cv8Gv
%ASMX% -c -q -win64 -Zi8 -Gv %1
fcmp -coff %~n1.obj exp64\%~n1.obj
if errorlevel 1 goto end
del %~n1.obj
goto end

:zne
%ASMX% -q -Zne -bin %1
fcmp %~n1.bin exp\%~n1.bin
if errorlevel 1 goto end
del %~n1.bin
goto end

:end

