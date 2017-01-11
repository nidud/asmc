
hello.exe:
	asmc -pe -D__PE__ hello.asm
	asmc -pe -D__PE__ -D_WIN64 -Fo hello64.exe hello.asm
	asmc -pe -D__PE__ system.asm
	asmc -pe -D__PE__ -D_WIN64 -Fo system64.exe system.asm


