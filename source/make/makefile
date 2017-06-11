debug  = 0
asmc   = \asmc
watcom = \watcom

all: make.res make.exe clean

make.exe:
 asmc -q -coff -Zi -Cs $*.asm
!if $(debug)
 link /debug /subsystem:console /libpath:$(asmc)\lib libc.lib $*.obj
!else
 linkw symt _cstart file $*
 wrc -q $*.res $@
!endif

make.res:
 $(watcom)\binnt\rc.exe -nologo -I$(watcom)\h\win $*.rc

clean:
 del make.obj
 del make.res
