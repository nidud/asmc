all: ..\..\lib\x64\strsafe.lib ..\..\lib\strsafe.lib

..\..\lib\strsafe.lib:
    asmc -coff -Cs -Zi -r x86\*.asm
    libw -q -b -n -c -fac $@ *.obj
    del *.obj

..\..\lib\amd64\strsafe.lib:
    asmc64 -Cs -r x64\*.asm
    libw -q -b -n -c -fac $@ *.obj
    del *.obj

