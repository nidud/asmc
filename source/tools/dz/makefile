
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
source	= $(asmc)\source\tools\dz\src
include = -I$(asmc)\source\tools\dz\include -I$(asmc)\include

CC  = $(asmc)\bin\asmc /coff /Cs /Zi /D__DZ__ /D__BMP__ $(include)
RC  = $(asmc)\bin\iddc /coff
LIB = $(asmc)\bin\libw /b /n /c /fac

!if $(debug)
LINK = $(msvc)\bin\link /map /debug /subsystem:console /libpath:$(asmc)\lib
!else
LINK = $(asmc)\bin\linkw op stub=$(source)\res\dz.bin lib libc.lib file
ICON = $(watc)\binnt\wrc -q res\dz.res $@
!endif

all: libc.lib dz.obj dz.exe clean

dz.exe:
 $(LINK) dz.obj
 $(ICON)

libc.lib:
 $(CC) $(source)\shared\*.asm
 $(CC) $(source)\common\*.asm
 $(CC) $(source)\dzmain\*.asm
 $(RC) /r res\*.idd
 $(LIB) $@ *.obj
 @del *.obj

dz.obj:
 $(CC) $(source)\dz.asm

clean:
 @del libc.lib
 @del dz.obj

