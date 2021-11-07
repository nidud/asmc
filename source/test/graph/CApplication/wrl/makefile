static = 0
mslink = 0
include = %AsmcDir%\include\winrt

CApplication.exe:
!if $(static)
    asmc64 -I$(include) -ws -frame $*.asm
!if $(mslink)
    link /libpath:%AsmcDir%\lib\x64 /machine:x64 $*.obj
!else
    linkw system gui_64W file $*.obj
!endif
!else
    asmc64 -I$(include) -ws -pe -gui $*.asm
!endif
    $@

