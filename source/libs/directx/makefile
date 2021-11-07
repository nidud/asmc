!include srcpath

AFLAGS = -Cs -I$(inc_dir)

$(lib_dir)\x64\directxmath.lib:
    asmc64 $(AFLAGS) /r *.asm
    libw /q /b /n /c /fac $@ *.obj
    del *.obj

directx.x64:
    asmc -q -win64 -I$(inc_dir) $*.regress
    linkw sys con_64 f $*
    if not exist $*.exe exit
    $*.exe
    if errorlevel 1 exit
    cmd /C del $*.obj $*.exe
