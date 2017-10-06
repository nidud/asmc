test.exe:
    asmc /q /pe /D__PE__ $*.asm
    $@
    del $@
    asmc /q /pe /D__PE__ /D_WIN64 $*.asm
    $@
    del $@

