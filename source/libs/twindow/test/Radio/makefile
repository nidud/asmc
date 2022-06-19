all: Radio.exe clean

Radio.exe:
    asmc64 -nologo $*.asm
    iddc -win64 Replace.idd
    linkw sys tcon_64 file $*, Replace
    $@

clean:
    del Radio.obj
    del Replace.obj
    del Radio.exe
