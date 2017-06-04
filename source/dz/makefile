#
# Visual C version 6 used for debug
# Open Watcom used to add the DZ.ICO file
#
debug = 0

msvc = \vc
watc = \watcom
asmc = \asmc
#
# use full path of this directory (source level debug)
#
source	= $(asmc)\source\dz\src
include = -I$(source)\h -I$(asmc)\include

CC  = $(asmc)\bin\asmc /coff /Cs /Zi /D__DZ__ $(include)
RC  = $(asmc)\bin\iddc /coff
LIB = $(asmc)\bin\libw /b /n /c /fac

!if $(debug)
LINK = $(msvc)\bin\link /debug /subsystem:console /libpath:$(asmc)\lib
!else
LINK = $(asmc)\bin\linkw op stub=$(source)\res\dz.bin lib dz.lib file
ICON = $(watc)\binnt\wrc -q $(source)\res\dz.res $@
!endif

all: dz.lib dz.obj dz.exe clean

dz.exe:
 $(LINK) dz.obj
 $(ICON)

dz.lib:
 $(RC) /r $(source)\res\*.idd
 $(CC) /r $(source)\lib\*.asm
 $(LIB) $@ *.obj
 @del *.obj

dz.obj:
 $(CC) $(source)\dz.asm

clean:
 @del dz.lib
 @del dz.obj

