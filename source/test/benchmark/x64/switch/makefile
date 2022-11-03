timeit.exe:
    asmc64 -DCOUNT=100 -q -bin ?.asm
    asmc64 -q -pe $*.asm
    $@
    del *.bin
    del $@
