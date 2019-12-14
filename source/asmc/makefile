# Makefile for Asmc using LINKW

asmc.exe:
    for %%q in (src\*.c) do wcc386 -D_LIBC -D_ASMC -q -Isrc\h -d2 -bt=nt -bc -ecc -3r -ox -s %%q
    asmc -q -Zp4 -Cs -Isrc\h -coff src\x86\*.asm
    linkw name $@ symt _cstart file { *.obj }
    del *.obj
