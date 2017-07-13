msvc  = 1
debug = 0

lcount.exe:
!if $(msvc)
    asmc /pe -D__PE__ $*.asm
!else
    asmc /coff /Zi $*.asm
!if $(debug)
    link /debug /subsystem:console libc.lib $*.obj
!else
    linkw system con_32 file $*
!endif
    del $*.obj
!endif
    $@ -r ..\*.asm
    pause

