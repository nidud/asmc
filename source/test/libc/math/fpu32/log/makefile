test.exe:
    asmc -q -coff -Zi $*.asm
#    linkw system con_32 file $*.obj
    link /debug /libpath:\asmc\lib /subsystem:console libc.lib $*.obj
    $@
    pause
    asmc -q -pe -D__PE__ $*.asm
    $@
    pause
