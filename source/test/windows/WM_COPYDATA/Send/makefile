SendWM_COPYDATA.exe:
	rc $*.rc
	asmc64 -q -ws -Cs -Zp8 $*.asm -link -res:$*.res
	del $*.res
	del $*.obj
vs:
	project -p -w -u -rSendWM_COPYDATA SendWM_COPYDATA
