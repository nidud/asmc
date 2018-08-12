test.exe:
    asmc -pe -gui $*.asm
    $@

test64.exe:
    asmc64 $*.asm
    linkw sys gui_64 file $*
    $@

