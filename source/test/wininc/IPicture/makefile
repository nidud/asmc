SaveIcon.exe:
    asmc64 $*.asm
    linkw sys gui_64 file $*
    $@
    del $*.obj
    dir | find ".ico"
    pause

