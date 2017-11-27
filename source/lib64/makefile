!include srcpath

$(lib_dir)\amd64\libc.lib:
    asmc /win64 /D_WIN64 /Cs /Zi /I$(inc_dir) /r $(src_dir)\lib64\*.asm
    libw /q /b /n /c /fac $@ *.obj
    del *.obj

