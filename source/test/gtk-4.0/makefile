#
# The Windows version use directory \gtk-4.0 (see linkw.lnk)
#
# libraries used (\gtk-4.0\lib):
#
#	gtk-4.lib
#	gio-2.0.lib
#	gobject-2.0.lib
#	glib-2.0.lib
#

ifdef YACC

.SUFFIXES: .asm

OBJS =	hello-world.o \
	builder.o \
	action-namespace.o \
	sunny.o \
	plugman.o \
	drawing.o \
	grid-packing.o \
	search-bar.o \
	window-default.o

.asm.o:
	asmc64 -q -Zp8 -Cs -fpic $<
	gcc -o $* $*.o `pkg-config --cflags --libs gtk4`

targets: $(OBJS)
	rm -f *.o

clean:
	rm -f hello-world
	rm -f builder
	rm -f action-namespace
	rm -f sunny
	rm -f plugman
	rm -f drawing
	rm -f grid-packing
	rm -f search-bar
	rm -f window-default

else

msvcrt = 1

flags = -Zp8 -Cs
!if $(msvcrt)
lib = msvcrt
flags += -nolib -D__PE__
!else
lib = libc
!endif

OBJS =	hello-world.obj \
	builder.obj \
	action-namespace.obj \
	sunny.obj \
	plugman.obj \
	drawing.obj \
	grid-packing.obj \
	search-bar.obj \
	window-default.obj

.asm.obj:
	asmc64 -nologo $(flags) $<
	linkw system gtk_$(lib) file $*.obj

targets: $(OBJS)
	del *.obj

clean:
	del *.exe
endif
