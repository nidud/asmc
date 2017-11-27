test.exe:
    asmc -q -pe -gui $*.asm
    $@
    del $@
    asmc -q -pe -gui -D_WIN64 $*.asm
    $@
    del $@

