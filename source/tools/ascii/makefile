ascii.exe:
    asmc $*.asm
    iddc -mf -frc.obj Ascii.IDD
    linkw system con_32 file $*, rc
    del $*.obj
    del rc.obj