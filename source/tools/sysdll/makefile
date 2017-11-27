msvcrt = 0

sysdll.exe:
!if $(msvcrt)
    asmc -pe -D__PE__ -D_WIN64 $*.asm
!else
    asmc -q -win64 $*.asm
    linkw system con_64 file $*
!endif
    $@ /def msvcrt