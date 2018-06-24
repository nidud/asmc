!include srcpath

AFLAGS = -win64 -Cs -Zi -I$(inc_dir)

$(lib_dir)\amd64\libc.lib:
    asmc $(AFLAGS) /r $(src_dir)\lib64\*.asm
    libw /q /b /n /c /fac $@ *.obj
    del *.obj

