
# this creats a .RES file using asmc and link using LinkW /RES:

dpitutorial.exe: resource
	asmc64 -res resource.asm
	asmc64 -q -Fe$@	 -ws -Cs -Zp8 $*.asm -link -res:resource.res
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
	if not exist imgconv.exe (
	 asmc64 -q -pe -ws -frame imgconv.asm
	)

vs:
	project -p -w -u dpitutorial resource
