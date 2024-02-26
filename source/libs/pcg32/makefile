#
# Makefile for [A]PCG32
#
ifdef YACC

apcg32.a:
	asmc64 -Cs x64/*.asm
	ar rcs $@ *.o
	rm *.o
	sudo cp apcg32.a /lib

else

include srcpath

$(lib_dir)/x64/pcg32.lib:
	asmc64 -Cs x64/*.asm
	libw -q -b -n -c -fac $@ *.obj
	del *.obj

endif
