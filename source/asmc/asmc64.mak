# Makefile for Asmc64 using LINKW
# Open Watcom's WRC used to add the ASMC.ICO file

asmc64.exe:
    if exist *.obj del *.obj
    asmc -q -Isrc\h -mz res\stub.asm
    for %%q in (src\*.c) do wcc386 -D__ASMC64__ -D_LIBC -D_ASMC -q -Isrc\h -d2 -bt=nt -bc -ecc -3r -ox -s %%q
    asmc -q -Zp4 -Cs -D__ASMC64__ -Isrc\h -coff src\x86\*.asm
    linkw name $@ Op q, stub=stub.exe symt _cstart file { *.obj }
    wrc -q res\asmc.res $@
    del stub.exe
    del *.obj
