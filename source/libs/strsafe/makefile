!include srcpath

all: $(lib_dir)\x64\strsafe.lib $(lib_dir)\x86\strsafe.lib

$(lib_dir)\x86\strsafe.lib:
    asmc -coff -Cs -Zi -r x86\*.asm
    libw -q -b -n -c -fac $@ *.obj
    del *.obj

$(lib_dir)\x64\strsafe.lib:
    asmc64 -DSTRSAFE_LIB -Cs -r x64\*.asm
    libw -q -b -n -c -fac $@ *.obj
    del *.obj

