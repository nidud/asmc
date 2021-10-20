#
# Note: needs Open Watcom
#
UiaSimpleProvider.exe:
    wrc -r -I\watcom\h\nt UiaSimpleProvider.rc
    asmc64 -q -ws -Cs -Zp8 *.asm
    linkw name $* system gui_64W file { *.obj } option RESource=UiaSimpleProvider.res
    del *.res
    del *.obj
