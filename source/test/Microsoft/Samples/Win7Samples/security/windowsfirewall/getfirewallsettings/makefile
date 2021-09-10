static = 0
mslink = 0

GetFirewallSettings.exe:
!if $(static)
    asmc64 -frame $*.asm
!if $(mslink)
    link /libpath:%AsmcDir%\lib\x64 /machine:x64 $*.obj
!else
    linkw system con_64 file $*.obj
!endif
!else
    asmc64 -pe $*.asm
!endif
    $@
    pause

