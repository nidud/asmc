AddPackageSample.exe:
	asmc64 -I%AsmcDir%\include\winrt -ws -pe $*.asm
#	$@ "https://github.com/microsoft/Windows-classic-samples/blob/main/Samples/AppxPackingExtractAppx/cpp/Data/HelloWorld.appx?raw=true"

vs:
	project -p -u AddPackageSample
