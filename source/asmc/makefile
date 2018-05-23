# Makefile for Asmc using LINKW
# Open Watcom's WRC used to add the ASMC.ICO file

# In order to use the regression test the expected output
# has to be build. See the regress\exp\buildexp.cmd file
# for more details.
regress = 0

asmc.exe:
    if exist *.obj del *.obj
    asmc -q -Isrc\h -mz res\stub.asm
    for %%q in (src\*.c) do wcc386 -D_LIBC -D_ASMC -q -Isrc\h -d2 -bt=nt -bc -ecc -3r -ox -s %%q
    asmc -q -Isrc\h -coff src\x86\*.asm
    linkw name $@ Op q, m, stub=stub.exe symt _cstart file { *.obj }
    wrc -q res\$*.res $@
    del stub.exe
    del *.obj
!if $(regress)
    if not exist .\asmc.exe exit
    cd regress
    runtest ..\..\asmc.exe
!endif
