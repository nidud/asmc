!include srcpath

$(lib_dir)\amd64\directxmath.lib:
    asmc -win64 -Cs -I$(inc_dir) src\const\*.asm
    asmc -win64 -Cs -I$(inc_dir) src\color\*.asm
    asmc -win64 -Cs -I$(inc_dir) src\x64\*.asm
    libw -q -b -n -c -fac $@ *.obj
    del *.obj
