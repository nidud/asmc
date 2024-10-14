all: catch.exe test32.exe test64.exe

test32.exe:
    asmc $*.asm
    $@
    pause
    del $@
    del $*.obj

test64.exe:
    asmc64 $*.asm
    $@
    pause
    del $@
    del $*.obj

catch.exe:
    asmc64 -pe -Zp8 -frame $*.asm
    $@ 1
