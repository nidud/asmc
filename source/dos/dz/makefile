# MAKEFILE--
# Makefile for Doszip
#
dz.exe:
    asmc -mz -Fo dz.exe -q -I..\include dz.asm
    iddc -ml -r src\*.idd
    asmc -I..\include -D__DZ__ src\*.asm
    linkw system dos name dz.dos file ..\lib\c0l, *.obj
    del *.obj
