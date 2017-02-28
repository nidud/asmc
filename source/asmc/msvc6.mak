#
# Makefile for Asmc using MSVC Version 6
#
asmc.exe:
	asmc -q -Isrc\h -coff src\*.asm
	cl -c -Gz -nologo -Isrc\h src\*.c
	link @<<
/out:$@
/nodefaultlib
/subsystem:console
..\..\lib\kernel32.lib
..\..\lib\libc.lib
..\..\lib\crt.obj
*.obj
<<
	@del *.obj

