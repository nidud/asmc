# Makefile for Asmc using Open Watcom

# In order to use the regression test the expected output
# has to be build. See the regress\exp\buildexp.cmd file
# for more details.
Regress = 0
CC	= wcc386 -q -Isrc\h -d2 -bt=nt -bc -ecd -3r -ox -s

asmc.exe:
	if exist *.obj del *.obj
	asmc -q -Isrc\h -mz res\stub.asm
	asmc -q -Isrc\h -coff src\*.asm
	for %%q in (src\*.c) do $(CC) %%q
	linkw @<<
Name	$@
Option	Q
Option	Map
Option	Stub=stub.exe
Lib	libc
File	{ ..\..\lib\crt.obj *.obj }
<<
	wrc -q res\$*.res $@
	del stub.exe
	del *.obj
!IF $(Regress)
	if not exist .\asmc.exe exit
	cd regress
	runtest
!ENDIF
