timeit.exe:
    asmc -q -bin ?.asm
    asmc -q -pe $*.asm
    $@
    del *.bin
    del $@
