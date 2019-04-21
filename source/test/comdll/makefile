test.exe:
    asmc64 -nologo -pe -gui $*.asm
    asmc64 -nologo -pe -ws install.asm
    asmc64 -nologo -pe -ws uninstall.asm
    asmc64 -nologo -D__GUID__ IConfig.asm
    linkw option quiet system dll_64 file IConfig.obj
    $@
    pause



