regress = 1

asmc.exe:
	if exist *.obj del *.obj
	set asmc=-nologo
	set include=-src\h;%include%
	asmc -q -Isrc\h -mz res\stub.asm
	asmc -q -Isrc\h -coff src\*.asm
	for %%q in (src\*.c) do wcc386 -q -Isrc\h -d2 -bt=nt -bc -ecd -3r -obmilrt -s %%q
	linkw @<<
name	$@
option	q
option	m
option	stub=stub.exe
file	{ ..\..\lib\C0.obj *.obj }
<<
	wrc -q res\$*.res $@
	del stub.exe
	del *.obj
!if $(regress)
	if not exist .\asmc.exe exit
	cd regress
	runtest ..\..\asmc.exe
!endif
