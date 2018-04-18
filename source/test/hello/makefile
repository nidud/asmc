hello.exe:
    asmc -q -pe $*.asm
    echo PE-WIN32A:
    $@
    del $@
    pause
    asmc -q -pe -win64 $*.asm
    echo PE-WIN64A:
    $@
    pause
    del $@

