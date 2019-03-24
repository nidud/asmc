
test.exe:
    asmc64 *.asm
    linkw sys con_64 file $*, IConfig
    $@
    type $*.ini
    pause
    asmc64 -pe $*.asm
    $@
    type $*.ini
    pause
