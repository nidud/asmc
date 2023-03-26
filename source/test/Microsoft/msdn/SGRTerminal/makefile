static = 0

all: EnablingVTerminal.exe SGRTerminal.exe AnniversaryUpdate.exe

EnablingVTerminal.exe:
!if $(static)
    asmc64 $*.asm
    linkw system con_64 file $*.obj
!else
    asmc64 -pe $*.asm
!endif

SGRTerminal.exe:
!if $(static)
    asmc64 $*.asm
    linkw system con_64 file $*.obj
!else
    asmc64 -pe $*.asm
!endif

AnniversaryUpdate.exe:
!if $(static)
    asmc64 $*.asm
    linkw system con_64 file $*.obj
!else
    asmc64 -pe $*.asm
!endif
