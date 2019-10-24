
build_pe = 1

test.exe:
!if $(build_pe)
    asmc64 -pe -D_WIN32REG $*.asm
!else
    asmc64 -D_WIN32REG $*.asm
    linkw system con_64 file $*.obj
!endif
