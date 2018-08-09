
test.exe:
    asmc -win64 *.asm
    linkw sys con_64 file $*, IConfig
    $@
    type $*.ini
    pause
    asmc -pe -win64 $*.asm
    $@
    type $*.ini
    pause
