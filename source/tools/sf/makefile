debug  = 0
msvcrt = 1

sf.exe:
!if $(debug)
    asmc /Zi /coff $*.asm
    link /debug /out:$@ /libpath:\asmc\lib /subsystem:console libc.lib $*.obj
!else
 !if $(msvcrt)
    asmc -pe -D__PE__ $*.asm
 !else
    asmc -q $*.asm
    linkw system con_32 file $*
 !endif
!endif
