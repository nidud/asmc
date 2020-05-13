test.exe:
    asmc64 -q $*.asm
    linkw sys con_64 name $@ file $*
    $@
    pause
