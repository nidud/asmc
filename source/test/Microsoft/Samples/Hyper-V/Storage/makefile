
win64 = 0

VirtualDisk.exe:
!if $(win64)
    asmc64 -c -frame -Zp8 -ws *.asm
    linkw name $@ system con_64W file { *.obj }
!else
    asmc -c -Zp8 -ws *.asm
    linkw name $@ system con_32W file { *.obj }
!endif
    del *.obj

