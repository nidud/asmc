static = 0 
 
ConsoleScreenBuffer.exe: 
!if $(static) 
    asmc64 $*.asm 
    linkw system con_64 file $*.obj 
!else 
    asmc64 -pe $*.asm 
!endif 
    $@ 
    pause 
 
