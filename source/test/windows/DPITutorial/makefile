#
# Note: needs Open Watcom
#
ifndef RC
RC = WRC
endif
DPITutorial.exe: resource
	$(RC) -r $*.rc
	asmc64 -q -Fe$@	 -ws -Cs -Zp8 $*.asm -link -res:$*.res
	$@
	del *.res
	del *.obj

resource: imgconv
	if not exist res\scaled100.bmp (
	 imgconv res\scaled100.png res\scaled100.bmp
	 imgconv res\scaled125.png res\scaled125.bmp
	 imgconv res\scaled150.png res\scaled150.bmp
	 imgconv res\scaled200.png res\scaled200.bmp
	)

imgconv:
	if not exist %ASMCDIR%\bin\imgconv.exe (
	 asmc64 -q -pe -ws -frame -Fo %ASMCDIR%\bin\imgconv.exe %ASMCDIR%\source\tools\bitmap\imgconv\imgconv.asm
	)

vs:
	project -p -w -u DPITutorial
