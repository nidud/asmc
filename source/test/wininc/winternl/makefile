#
#  __PE__ auto defined if switch -pe used
#
test.exe:
    asmc -pe -D_WIN64 $*.asm
    $@
    pause
    del $@
