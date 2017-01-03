# MAKEFILE--
# Makefile for Doszip
#
!include ../srcpath

dz.exe: dz.dos
	asmc -mz -Fo dz.exe -q -I$(inc_dir) dz.asm
dz.dos:
	iddc -ml -r src\*.idd
	asmc -q -I$(inc_dir) -D__DZ__ src\*.asm
	linkw Name $@ System dos OP M, Q L dz F { $(STARTUP) *.obj }
	del *.obj
