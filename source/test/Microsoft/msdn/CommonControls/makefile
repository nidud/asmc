
watcom = 1

CommonControls.exe:
    if not exist res\error.ico (
        md res
        asmc64 -ws -pe resource.asm
        resource.exe
        del resource.exe
    )
    asmc64 -c -q -ws -Cs -Zp8 $*.asm
!if $(watcom)
    wrc -q -r $*.rc
    linkw system gui_64W file $* option RESource=$*.res
!else
    rc /I\Win10SDK.0.18362.0\um /I\Win10SDK.0.18362.0\shared $*.rc
    link $*.obj $*.res
!endif
    del $*.res
    del $*.obj
