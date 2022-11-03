timeit.exe:
    asmc64 -q -Cs -bin ?.asm
    asmc64 -q -pe $*.asm
    $@
    del *.bin
    del $@
