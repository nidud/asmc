
set PATH=D:\VS19\VC\Tools\MSVC\14.28.29333\bin\Hostx64\x64;%PATH%
set PATH=%ProgramFiles(x86)%\Windows Kits\10\Debuggers\x64;%PATH%

asmc64 -Zi8 main.asm
link /debug /subsystem:console main.obj
windbg main.exe
