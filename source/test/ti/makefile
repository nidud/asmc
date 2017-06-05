ti.exe:
    asmc -q $*.asm
    linkw op q symt _cstart file $*
    $@
    del *.obj
    pause
