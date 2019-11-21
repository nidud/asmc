test.exe:
    asmc64 -nolib -gui $*.asm
    linkw op map system dgui_64 file $*
    $@
    del $*.obj
    dir | find ".ico"
    pause

