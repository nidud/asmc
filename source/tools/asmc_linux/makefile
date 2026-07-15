# This converts the Asmc-source to GAS
# using a modified version of objconv

flags = -elf64 -fpic -Zp8 -Cs -I../../asmc/inc -I../../../include

asmc_linux: strip_s
	asmc -c -jtd $(flags) ../../asmc/src/*.asm
	md src
	for %%q in (*.o) do call :conv %%q
	del *.o
	exit
	:conv
	objconv -fgasm %1 src\%~n1.s
	strip_s src\%~n1.s

strip_s:
	asmc -win64 $*.asm
