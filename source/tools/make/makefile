debug  = 0
asmc   = \asmc
watcom = \watcom
msvc   = \vc

all: make.res make.exe clean

make.exe:
    $(asmc)\bin\asmc -q -coff -Zi -Cs $(asmc)\source\tools\make\$*.asm
!if $(debug)
    $(msvc)\bin\link /debug /subsystem:console /libpath:$(asmc)\lib libc.lib $*.obj
!else
    $(asmc)\bin\linkw sys con_32 file $*
    $(watcom)\binnt\wrc.exe -q $*.res $@
!endif

make.res:
    $(watcom)\binnt\rc.exe -nologo -I$(watcom)\h\win $*.rc

clean:
    del make.obj
    del make.res
