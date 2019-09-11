# Makefile for Asmc using LINKW
# Open Watcom's WRC used to add the ASMC.ICO file

asmc.exe:
    if exist *.obj del *.obj
    asmc -q -Isrc\h -mz res\stub.asm
    for %%q in (src\*.c) do wcc386 -D_LIBC -D_ASMC -q -Isrc\h -d2 -bt=nt -bc -ecc -3r -ox -s %%q
    asmc -q -Zp4 -Cs -Isrc\h -coff src\x86\*.asm
    linkw name $@ Op q, m, stub=stub.exe symt _cstart file { *.obj }
    wrc -q res\$*.res $@
    del stub.exe
    del *.obj
