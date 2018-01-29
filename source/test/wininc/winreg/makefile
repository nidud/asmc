
build_pe = 1

test.exe:
!if $(build_pe)
    asmc -pe -gui -D_WIN32REG $*.asm
!else
    asmc -D_WIN32REG $*.asm
    linkw format windows nt runtime windows file $*.obj
!endif
