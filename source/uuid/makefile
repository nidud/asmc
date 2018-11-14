..\..\lib\uuid.lib:
    asmc -q uuid.asm > list.txt
    asmc -pe src.asm
    src.exe
    asmc -coff -r src\*.asm
    libw -q -b -n -c -fac $@ *.obj
    del *.obj
    asmc64 -r src\*.asm
    libw -q -b -n -c -fac ..\..\lib\amd64\uuid.lib *.obj
    del *.obj
    del src.exe
    del list.txt
    dir /W src\*.*
    del src\*.asm
    pause

