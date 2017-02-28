#
# Makefile for Asmc using MSVC Version 6
#
asmc.exe:
	asmc -q -coff -Zi -DDEBUG -Isrc\h src\*.asm
	cl -c -nologo -Gz -Od -Zi -DDEBUG -Isrc\h src\*.c
	link @<<
/debug
/map
/out:$@
/nodefaultlib
/subsystem:console
..\..\lib\kernel32.lib
..\..\lib\libcd.lib
..\..\lib\crtd.obj
*.obj
<<
	@del *.obj

