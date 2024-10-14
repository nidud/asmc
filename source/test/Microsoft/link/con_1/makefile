
test:
    asmc -nolib -coff -Bl link $@.asm
    $@
    pause
    asmc64 -nolib -Bl link $@.asm
    $@
    pause
    del $@.obj
    del $@.exe


