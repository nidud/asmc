!include srcpath

AFLAGS = -Cs -I$(inc_dir)

$(lib_dir)\amd64\libc.lib:
    asmc64 $(AFLAGS) /r *.asm
    libw /q /b /n /c /fac $@ *.obj
    del *.obj

