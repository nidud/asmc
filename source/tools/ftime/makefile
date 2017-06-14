debug = 0

ftime.exe:
 asmc /coff /Zi $*.asm
!if $(debug)
 link /debug /subsystem:console libc.lib $*.obj
 $@ -cd01.02.02 -ct01:02:03 *.lst
 pause
!else
 linkw system con_32 file $*
!endif

