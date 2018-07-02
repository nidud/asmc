msvc = \vc12

cflags = /I$(msvc)\include /I\DirectX\Inc -O2 -Gv
lflags = /LIBPATH:$(msvc)\lib\amd64

test.exe:
    $(msvc)\bin\amd64\cl $(cflags) $*.cpp /link $(lflags) > NUL
    $@
    pause
    del $*.obj
    del $*.exe
    asmc -win64 $*.asm
    linkw op q sys con_64 file $*
    $@
    pause
    del $*.obj
    del $*.exe
