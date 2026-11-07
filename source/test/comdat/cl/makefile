bar:
	asmc -c -win64 -Gw -frame foo.asm
	cl -Gw bar.c -link -map foo.obj
	pause
clean:
	del *.obj
	del bar.exe
	del bar.map
