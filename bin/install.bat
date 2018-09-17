REM
REM This builds the import libraries and LIBC
REM
cd ..\lib
..\bin\dz make.exe
cd amd64
..\..\bin\dz make.exe
cd ..\..\source\lib32
..\..\bin\dz make.exe
cd ..\lib64
..\..\bin\dz make.exe
cd ..\directx
..\..\bin\dz make.exe
cd ..\uuid
..\..\bin\dz make.exe
