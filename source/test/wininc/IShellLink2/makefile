IShellLink.exe:
    asmc64 -ws $*.asm
    linkw sys con_64W file $*
    $@
    pause
    del $*.obj
    del $*.exe


