!include srcpath

all: $(lib_dir)\x64\strsafe.lib $(lib_dir)\strsafe.lib

$(lib_dir)\strsafe.lib:
    asmc -coff -Cs -Zi -r x86\*.asm
    libw -q -b -n -c -fac $@ *.obj
    del *.obj

$(lib_dir)\amd64\strsafe.lib:
    asmc64 -Cs -r x64\*.asm
    libw -q -b -n -c -fac $@ *.obj
    del *.obj

