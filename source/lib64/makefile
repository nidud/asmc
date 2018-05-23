!include srcpath

AFLAGS = -win64 -Cs -Zi -I$(inc_dir)

$(lib_dir)\amd64\libc.lib:
    asmc $(AFLAGS) $(src_dir)\quadmath\src\const\*.asm
    asmc $(AFLAGS) $(src_dir)\quadmath\src\x64\*.asm
    asmc $(AFLAGS) /r $(src_dir)\lib64\*.asm
    libw /q /b /n /c /fac $@ *.obj
    del *.obj

