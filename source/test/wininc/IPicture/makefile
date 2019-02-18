SaveIcon.exe:
    asmc $*.asm
    linkw sys gui_32 file $*
    $@
    del $*.obj
    dir | find ".ico"
    pause

