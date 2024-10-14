static = 0
mslink = 0

CApplication.exe:
!if $(static)
    asmc64 -c -ws -frame -Zp8 $*.asm
!if $(mslink)
    link /libpath:%AsmcDir%\lib\x64 /machine:x64 $*.obj
!else
    linkw system gui_64W file $*.obj
!endif
!else
    asmc64 -ws -peg -Zp8 $*.asm
!endif
    $@

