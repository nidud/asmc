all: Radio.exe clean

Radio.exe:
    asmc64 -ws -nologo $*.asm
    iddc -win64 Replace.idd
    linkw sys tcon_64W file $*, Replace
    $@

clean:
    del Radio.obj
    del Replace.obj
    del Radio.exe
