DesktopDuplication.exe:
    asmc64 -Zp8 *.asm
    linkw name $@ system gui_64 file { *.obj }
    del *.obj
    $@
