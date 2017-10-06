test.exe:
    asmc /q /pe /D__PE__ $*.asm
    echo 32-bit
    $@
    echo 64-bit
    del $@
    asmc /q /pe /D__PE__ /D_WIN64 $*.asm
    $@
    del $@

