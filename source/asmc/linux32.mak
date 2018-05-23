# Makefile for Asmc Linux using Open Watcom

watcom	= \watcom

cflags = -q -Isrc\h -I$(watcom)\lh -3s -ox -s -zc -bc -bt=linux

asmc:
 set include=$(watcom)\lh
 for %%q in (src\*.c) do wcc386 $(cflags) %%q
 wcc386 $(cflags) src\quadmath\atoquad.c
 wlink @<<
name	asmc.
format	elf runtime linux
libpath $(watcom)/lib386
libpath $(watcom)/lib386/linux
lib	clib3s.lib
option	norelocs, quiet, stack=0x20000
file { *.obj }
<<
 del *.obj
