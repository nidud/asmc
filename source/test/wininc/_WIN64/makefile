#
# _WIN64 defined by Asmc if switch -win64 is used
#
test.exe:
    asmc -q -win64 $*.asm
    linkw system con_64 file $*
    $@ 1 2 3
    pause
    del $@
    del $*.obj

