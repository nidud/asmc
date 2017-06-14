msvcrt = 0

_getwch.exe:
!if $(msvcrt)
    asmc -pe -ws -D_UNICODE -D__PE__ -D_WIN64 $*.asm
!else
    asmc -q -ws -win64 -D_UNICODE -D_WIN64 $*.asm
    linkw system con_64W file $*
    del $*.obj
!endif
    $@
    pause
    del $@
