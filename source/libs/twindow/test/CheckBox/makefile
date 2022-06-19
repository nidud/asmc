all: CheckBox.exe clean

CheckBox.exe:
    asmc64 -nologo $*.asm
    iddc -win64 DZPanelOptions.IDD
    linkw sys tcon_64 file $*, DZPanelOptions
    $@

clean:
    del *.obj
    del *.exe
