msvcrt = 1

dlldef.exe:
!if $(msvcrt)
    asmc -pe -D__PE__ -D_WIN64 $*.asm
!else
    asmc -q -D_WIN64 -win64 $*.asm
    linkw system x64 file $*
!endif
    $@ kernel32.dll