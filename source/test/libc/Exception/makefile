all: test32.exe test64.exe

test32.exe:
    asmc $*.asm
    linkw sys con_32 file $*
    $@
    pause
    del $@
    del $*.obj

test64.exe:
    asmc64 $*.asm
    linkw sys con_64 file $*
    $@
    pause
    del $@
    del $*.obj
