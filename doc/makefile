ifdef YACC
asmc.chm:
	mdchm -clean asmc
else
asmc:	mdchm
	mdchm -clean $@
mdchm:
	if not exist ..\bin\mdchm.exe (
	   asmc64 -pe -frame -Fo..\bin\mdchm.exe ..\source\tools\mdchm\mdchm.asm
	)
endif