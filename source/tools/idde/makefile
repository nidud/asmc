
idde.exe:
	cl -c /TC /GS- idde.c
	asmc -c -idd -win64 res\*.idd
	Cvtres.exe /machine:x64 /OUT:idderc.obj res\idde.res
	link /out:$@ /merge:.CRT=.rdata /libpath:%AsmcDir%\lib\x64 /machine:x64 /subsystem:console *.obj libc.lib
	del *.s
	del *.obj

