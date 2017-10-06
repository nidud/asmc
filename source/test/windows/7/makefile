#
#  __PE__ auto defined if switch -pe used
#
test.exe:
    asmc /q /pe $*.asm
    $@
    del $@
    asmc /q /pe /D_WIN64 $*.asm
    $@
    del $@

