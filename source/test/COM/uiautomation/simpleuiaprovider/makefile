#
# https://github.com/microsoft/Windows-classic-samples/tree/master/Samples/UIAutomationSimpleProvider
#
mslink = 0

UIASimpleProvider.exe:
!if $(mslink)
    asmc64 -q -D__MSLINK__ -ws -Cs $*.asm Control.asm Provider.asm
    rc -r -I\watcom\h\win $*.rc
    link /libpath:%AsmcDir%\lib\x64 /entry:wWinStart /machine:x64 UIASimpleProvider.obj Control.obj Provider.obj UIASimpleProvider.res
!else
    asmc64 -q -ws -Cs $*.asm Control.asm Provider.asm
    wrc -q -r -I\watcom\h\win $*.rc
    linkw system gui_64W option RESource=$*.res file $*, Control, Provider
!endif
    del $*.res
#    del *.obj
