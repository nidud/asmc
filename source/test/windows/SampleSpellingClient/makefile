SampleSpellingClient.exe:
	asmc64 -q -ws -frame $*.asm
	$@ en-US
	pause
	del $@
	del $*.obj

vs:
	project -p -u SampleSpellingClient
