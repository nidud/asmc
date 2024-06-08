include srcpath

Tutorial.exe:
	asmc   -q -pe -gui -I$(inc_dir) -Fo$*0132.exe -ws $*01.asm
	asmc64 -q -pe -gui -I$(inc_dir) -Fo$*0164.exe -ws $*01.asm
	asmc   -q -pe -gui -I$(inc_dir) -Fo$*0232.exe $*02.asm
	asmc64 -q -pe -gui -I$(inc_dir) -Fo$*0264.exe $*02.asm
	asmc64 -q -pe -gui -I$(inc_dir) -Fo$*0364.exe $*03.asm
	asmc64 -q -pe -gui -I$(inc_dir) -Fo$*0464.exe $*04.asm
	asmc64 -q -pe -gui -I$(inc_dir) -Fo$*0564.exe $*05.asm
