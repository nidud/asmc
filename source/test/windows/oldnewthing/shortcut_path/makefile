test.exe:
    if not exist Contoso.lnk (
        asmc64 -q -pe -ws Contosolnk.asm
        Contosolnk.exe
    )
    asmc -q -pe -ws -Fo $*132.exe $*1.asm
    asmc64 -q -pe -ws -Fo $*164.exe $*1.asm
    $*164 Contoso.lnk
    $*132 Contoso.lnk
    asmc -q -pe -ws -Fo $*232.exe $*2.asm
    asmc64 -q -pe -ws -Fo $*264.exe $*2.asm
    $*264 Contoso.lnk
    $*232 Contoso.lnk
    pause
