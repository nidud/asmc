#
# Note: needs Open Watcom
#
watcom = 1

SendWM_COPYDATA.exe:
    asmc64 -q -ws -Cs -Zp8 $*.asm
!if $(watcom)
    wrc -r $*.rc
    linkw system gui_64W file $* option RESource=$*.res
!else
    rc /I\Win10SDK.0.18362.0\um /I\Win10SDK.0.18362.0\shared $*.rc
    link $*.obj $*.res
!endif
    del $*.res
    del $*.obj
