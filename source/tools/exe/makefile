msvcrt = 1

exe.exe:
!if $(msvcrt)
    asmc64 -pe -ws $*.asm
!else
    asmc64 -ws $*.asm
    linkw system con_64W file $*
!endif
    $@ cmd.exe
    pause