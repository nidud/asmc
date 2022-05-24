msvcrt = 1

CC = asmc64 -Zp8 -Cs
!if $(msvcrt)
lib = msvcrt
CC += -nolib -D__PE__
!else
lib = libc
!endif

objs = \
  hello-world.obj \
  builder.obj \
  action-namespace.obj \
  sunny.obj \
  plugman.obj \
  drawing.obj \
  grid-packing.obj

.asm.obj:
    $(CC) $<
    linkw system gtk_$(lib) file $*.obj

hello-world.exe: $(objs)
    del *.obj

