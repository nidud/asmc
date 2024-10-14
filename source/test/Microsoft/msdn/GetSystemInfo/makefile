test.exe:
    echo.
    echo 32-bit PE
    asmc -q -pe $*.asm
    $@
    pause
    echo.
    echo 64-bit PE
    asmc -q -pe -win64 $*.asm
    $@
    pause
    echo.
    echo 64-bit /LARGEADDRESSAWARE
    asmc -q -win64 $*.asm
    $@
    pause
    del *.obj
    del *.exe

