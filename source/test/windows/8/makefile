#
#  __PE__ auto defined if switch -pe used
#
test.exe:
    asmc /q /pe $*.asm
    echo 32-bit
    $@
    echo 64-bit
    del $@
    asmc /q /pe /D_WIN64 $*.asm
    $@
    del $@

