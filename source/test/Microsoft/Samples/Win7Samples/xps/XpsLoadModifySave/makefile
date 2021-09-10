#
# Note: needs Open Watcom
#
XpsLoadModifySave.exe:
    wrc -r $*.rc
    asmc64 -q -ws -Cs -Zp8 $*.asm
    linkw system con_64W file $* option RESource=$*.res
    del $*.res
    del $*.obj
