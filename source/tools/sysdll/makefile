msvcrt = 1

sysdll.exe:
!if $(msvcrt)
    asmc64 -pe $*.asm
!else
    asmc64 $*.asm
    linkw sys con_64 file $*
!endif
    $@ /lib msvcrt
