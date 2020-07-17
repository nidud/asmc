
test.exe:
    asmc -q -pe $*.asm
    $@
    pause
    del $@
    asmc64 -q -pe $*.asm
    $@
    pause
    del $@
