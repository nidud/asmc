idde.exe:
	asmc -c -idd -win64 res\*.idd
	cl -c /I%AsmcDir%\include\h /TC /GS- idde.c
	rc idde.rc
	link /out:$@ /merge:.CRT=.rdata /libpath:%AsmcDir%\lib\x64 /subsystem:console *.obj idde.res libc.lib
	del *.s *.obj *.res
