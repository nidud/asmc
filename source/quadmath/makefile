
libdir = ..\..\lib
lib_32 = $(libdir)\quadmath.lib
lib_64 = $(libdir)\amd64\quadmath.lib
flags  = -Cs -nolib

all: $(lib_64) $(lib_32)

$(lib_32):
    asmc $(flags) -coff -safeseh -Zi -r const\*.asm x86\*.asm
    libw -q -b -n -c -fac $@ *.obj
    del *.obj

$(lib_64):
    asmc $(flags) -win64 -r const\*.asm x64\*.asm
    libw -q -b -n -c -fac $@ *.obj
    del *.obj

quad.x86:
    asmc -q $*.regress
    linkw sys con_32 f $*
    if not exist $*.exe exit
    $*.exe
    if errorlevel 1 exit
    dir *.obj > nul
    cmd /C del $*.obj $*.exe

quad.x64:
    asmc -q -win64 $*.regress
    linkw sys con_64 f $*
    if not exist $*.exe exit
    $*.exe
    if errorlevel 1 exit
    dir *.obj > nul
    cmd /C del $*.obj $*.exe

