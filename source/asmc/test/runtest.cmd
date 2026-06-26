@echo off

if not exist exp\NUL md exp

SET ASMX=%1
if (%1)==() SET ASMX=..\asmc.exe

for %%f in (src\x86-bin-*.asm)  do call :x86-bin %%f
for %%f in (src\x64-bin-*.asm)  do call :x64-bin %%f
for %%f in (src\x86-err-*.asm)  do call :x86-err %%f
for %%f in (src\x64-err-*.asm)  do call :x64-err %%f
for %%f in (src\x86-elf-*.asm)  do call :x86-elf %%f
for %%f in (src\x64-elf-*.asm)  do call :x64-elf %%f
for %%f in (src\x86-coff-*.asm) do call :x86-coff %%f
for %%f in (src\x64-coff-*.asm) do call :x64-coff %%f
for %%f in (src\x86-mz-*.asm)   do call :x86-mz %%f
for %%f in (src\x86-got-*.asm)  do call :x86-got %%f
for %%f in (src\x64-got-*.asm)  do call :x64-got %%f
for %%f in (src\x86-omf-*.asm)  do call :x86-omf %%f
for %%f in (src\x86-pe-*.asm)   do call :x86-pe %%f
for %%f in (src\x64-pe-*.asm)   do call :x64-pe %%f
for %%f in (src\x86-ep-*.asm)   do call :x86-ep %%f
for %%f in (src\x86-zg-*.asm)   do call :x86-zg %%f
for %%f in (src\x86-zd-*.asm)   do call :x86-zd %%f
for %%f in (src\x86-ext-*.asm)  do call :x86-ext %%f
for %%f in (src\x86-omf2-*.asm) do call :x86-omf2 %%f
for %%f in (src\x86-cu-*.asm)   do call :x86-cu %%f
for %%f in (src\x86-berr-*.asm) do call :x86-berr %%f
for %%f in (src\x86-cerr-*.asm) do call :x86-cerr %%f
for %%f in (src\x64-cerr-*.asm) do call :x64-cerr %%f
for %%f in (src\x86-perr-*.asm) do call :x86-perr %%f
for %%f in (src\x64-dwarf*.asm) do call :x64-dwarf %%f
for %%f in (src\x86-cv-*.asm)   do call :x86-cv %%f

exit

:x86-bin
if not exist exp\%~n1.bin %ASMX% -q -bin -DBIN -Fo exp\%~n1.bin %1
%ASMX% -q -bin %1
fcmp %~n1.bin exp\%~n1.bin
if errorlevel 1 goto end
del %~n1.bin
goto end

:x64-bin
if not exist exp\%~n1.bin %ASMX% -win64 -q -bin -DBIN -Fo exp\%~n1.bin %1
%ASMX% -win64 -q -bin %1
fcmp %~n1.bin exp\%~n1.bin
if errorlevel 1 goto end
del %~n1.bin
goto end

:x86-err
if not exist exp\%~n1.err %ASMX% -c -q -W3 -Fw exp\%~n1.err %1 >NUL
%ASMX% -c -q -W3 -omf %1 >NUL
fcmp %~n1.err exp\%~n1.err
if errorlevel 1 goto end
if exist %~n1.obj del %~n1.obj
del %~n1.err
goto end

:x64-err
if not exist exp\%~n1.err %ASMX% -c -q -W3 -win64 -Fw exp\%~n1.err %1 >NUL
%ASMX% -c -q -W3 -win64 %1 >NUL
fcmp %~n1.err exp\%~n1.err
if errorlevel 1 goto end
if exist %~n1.obj del %~n1.obj
del %~n1.err
goto end

:x86-elf
if not exist exp\%~n1.o %ASMX% -c -q -elf -Fo exp\%~n1.o %1
%ASMX% -c -q -elf %1
fcmp %~n1.o exp\%~n1.o
if errorlevel 1 goto end
del %~n1.o
goto end

:x64-elf
if not exist exp\%~n1.o %ASMX% -c -q -elf64 -Fo exp\%~n1.o %1
%ASMX% -c -q -elf64 %1
fcmp %~n1.o exp\%~n1.o
if errorlevel 1 goto end
del %~n1.o
goto end

:x86-coff
if not exist exp\%~n1.obj %ASMX% -c -q -coff -Fo exp\%~n1.obj %1
%ASMX% -c -q -coff %1
fcmp -coff %~n1.obj exp\%~n1.obj
if errorlevel 1 goto end
del %~n1.obj
goto end

:x64-coff
if not exist exp\%~n1.obj %ASMX% -c -q -win64 -Fo exp\%~n1.obj %1
%ASMX% -c -q -win64 %1
fcmp -coff %~n1.obj exp\%~n1.obj
if errorlevel 1 goto end
del %~n1.obj
goto end

:x86-mz
if not exist exp\%~n1.exe %ASMX% -q -mz -Fo exp\%~n1.exe %1
%ASMX% -q -mz %1
fcmp %~n1.exe exp\%~n1.exe
if errorlevel 1 goto end
del %~n1.exe
goto end

:x86-got
if not exist exp\%~n1.o %ASMX% -c -q -elf -Fo exp\%~n1.o %1
%ASMX% -c -q -elf %1
fcmp %~n1.o exp\%~n1.o
if errorlevel 1 goto end
del %~n1.o
if not exist exp\%~n1pie.o %ASMX% -c -q -elf -fpic -Fo exp\%~n1pie.o %1
%ASMX% -q -c -elf -fpic -Fo %~n1pie %1
fcmp %~n1pie.o exp\%~n1pie.o
if errorlevel 1 goto end
del %~n1pie.o
if not exist exp\%~n1pic.o %ASMX% -c -q -elf -fPIC -Fo exp\%~n1pic.o %1
%ASMX% -q -c -elf -fPIC -Fo %~n1pic %1
fcmp %~n1pic.o exp\%~n1pic.o
if errorlevel 1 goto end
del %~n1pic.o
goto end

:x64-got
if not exist exp\%~n1.o %ASMX% -c -q -elf64 -Fo exp\%~n1.o %1
%ASMX% -c -q -elf64 %1
fcmp %~n1.o exp\%~n1.o
if errorlevel 1 goto end
del %~n1.o
if not exist exp\%~n1pie.o %ASMX% -c -q -elf64 -fpic -Fo exp\%~n1pie.o %1
%ASMX% -q -c -elf64 -fpic -Fo %~n1pie %1
fcmp %~n1pie.o exp\%~n1pie.o
if errorlevel 1 goto end
del %~n1pie.o
if not exist exp\%~n1pic.o %ASMX% -c -q -elf64 -fPIC -Fo exp\%~n1pic.o %1
%ASMX% -q -c -elf64 -fPIC -Fo %~n1pic %1
fcmp %~n1pic.o exp\%~n1pic.o
if errorlevel 1 goto end
del %~n1pic.o
goto end

:x86-omf
if not exist exp\%~n1.obj %ASMX% -c -q -omf -Fo exp\%~n1.obj %1
%ASMX% -c -q -omf %1
if errorlevel 1 goto end
fcmp %~n1.obj exp\%~n1.obj
if errorlevel 1 goto end
del %~n1.obj
goto end

:x86-omf2
if not exist exp\%~n1.obj %ASMX% -c -q -Fo exp\%~n1.obj %1
%ASMX% -c -q %1
if errorlevel 1 goto end
fcmp %~n1.obj exp\%~n1.obj
if errorlevel 1 goto end
del %~n1.obj
goto end

:x86-cu
if not exist exp\%~n1.obj %ASMX% -c -q -Cu -Fo exp\%~n1.obj %1
%ASMX% -c -q -Cu %1
if errorlevel 1 exit
fcmp %~n1.obj exp\%~n1.obj
if errorlevel 1 goto end
del %~n1.obj
goto end

:x86-pe %%f
if not exist exp\%~n1.exe %ASMX% -q -pe -Fo exp\%~n1.exe %1
%ASMX% -q -pe %1
fcmp -pe %~n1.exe exp\%~n1.exe
if errorlevel 1 goto end
del %~n1.exe
goto end

:x64-pe %%f
if not exist exp\%~n1.exe %ASMX% -q -win64 -pe -Fo exp\%~n1.exe %1
%ASMX% -q -win64 -pe %1
fcmp -pe %~n1.exe exp\%~n1.exe
if errorlevel 1 goto end
del %~n1.exe
goto end

:x86-ep
if not exist exp\%~n1.ep %ASMX% -q -EP %1 > exp\%~n1.ep
%ASMX% -q -EP %1 > %~n1.ep
fcmp %~n1.ep exp\%~n1.ep
if errorlevel 1 goto end
del %~n1.ep
del %~n1.obj
goto end

:x86-zg
if not exist exp\%~n1.bin %ASMX% -q -Zg -bin -Fo exp\%~n1.bin %1
%ASMX% -q -Zg -bin %1
fcmp %~n1.bin exp\%~n1.bin
if errorlevel 1 goto end
del %~n1.bin
goto end

:x86-zd
if not exist exp\%~n1.obj %ASMX% -q -Zd -omf -Fo exp\%~n1.obj %1
%ASMX% -c -q -Zd -omf %1
fcmp %~n1.obj exp\%~n1.obj
if errorlevel 1 goto end
del %~n1.obj
goto end

:x86-berr
if not exist exp\%~n1.err %ASMX% -c -q -eq -bin -Fw exp\%~n1.err %1 >NUL
%ASMX% -c -q -eq -bin %1
fcmp %~n1.err exp\%~n1.err
if errorlevel 1 goto end
del %~n1.err
goto end

:x86-cerr
if not exist exp\%~n1.err %ASMX% -c -q -coff -eq -Fw exp\%~n1.err %1 >NUL
%ASMX% -c -q -coff -eq %1
fcmp %~n1.err exp\%~n1.err
if errorlevel 1 goto end
del %~n1.err
goto end

:x64-cerr
if not exist exp\%~n1.err %ASMX% -c -q -win64 -eq -Fw exp\%~n1.err %1 >NUL
%ASMX% -c -q -win64 -eq %1
fcmp %~n1.err exp\%~n1.err
if errorlevel 1 goto end
del %~n1.err
goto end

:x86-perr
if not exist exp\%~n1.err %ASMX% -c -q -pe -eq -Fw exp\%~n1.err %1 >NUL
%ASMX% -q -pe -eq %1
fcmp %~n1.err exp\%~n1.err
if errorlevel 1 goto end
del %~n1.err
if exist %~n1.exe del %~n1.exe
goto end

:x86-ext
if not exist exp\%~n1.exe %ASMX% -q -coff -Fe exp\%~n1.exe %1
%ASMX% -q -coff %1
if errorlevel 1 exit
fcmp -pe %~n1.exe exp\%~n1.exe
if errorlevel 1 goto end
del %~n1.exe
del %~n1.obj
goto end

:x86-cv
if not exist exp\%~n1.obj %ASMX% -c -q -coff -Zi4 -Fo exp\%~n1.obj %1
%ASMX% -c -q -coff -Zi4 %1
if errorlevel 1 exit
fcmp -coff %~n1.obj exp\%~n1.obj
if errorlevel 1 goto end
del %~n1.obj
goto end

:x64-dwarf
if not exist exp\%~n1.o %ASMX% -c -q -elf64 -Zd -Fo exp\%~n1.o %1
%ASMX% -q -c -elf64 -Zd %1
fcmp %~n1.o exp\%~n1.o
if errorlevel 1 goto end
del %~n1.o
goto end

:end
