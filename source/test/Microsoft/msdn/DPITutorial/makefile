#
# Note: needs Open Watcom
#
DPITutorial.exe:
    wrc -r $*.rc
    asmc64 -c -q -ws -Cs -Zp8 $*.asm
    linkw name $* system gui_64W file $*.obj option RESource=$*.res
    del *.res
    del *.obj
