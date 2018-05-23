!include srcpath

$(lib_dir)\amd64\quadmath.lib: $(lib_dir)\quadmath.lib
    asmc -win64 -Cs -I$(inc_dir) src\const\*.asm
    asmc -win64 -Cs -I$(inc_dir) src\x64\*.asm
    libw /q /b /n /c /fac $@ *.obj
    del *.obj

$(lib_dir)\quadmath.lib:
    asmc -Cs -Zi -I$(inc_dir) $(src_dir)\quadmath\src\const\*.asm
    asmc -Cs -Zi -I$(inc_dir) $(src_dir)\quadmath\src\x86\*.asm
    libw /q /b /n /c /fac $@ *.obj
    del *.obj
