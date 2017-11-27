Timer.exe:
    asmc $*.asm
    iddc /r *.idd
    linkw system con_32 file $*, TMain, Help1, Help2, About
    del *.obj