#
# Makefile for [A]STRSAFE
#
ifdef YACC

astrsafe.a:
	asmc64 -Cs src/*.asm
	ar rcs $@ *.o
	rm *.o
	sudo cp astrsafe.a /lib

else

include srcpath

all: $(lib_dir)/x64/strsafe.lib $(lib_dir)/x86/strsafe.lib

$(lib_dir)/x86/strsafe.lib:
	asmc -coff -Cs -Zi8 src/*.asm
	asmc -coff -Cs -Zi8 -ws -Fo *W src/*.asm
	libw -q -b -n -c -fac $@ *.obj
	del *.obj

$(lib_dir)/x64/strsafe.lib:
	asmc64 -Cs -Zi8 src/*.asm
	asmc64 -Cs -Zi8 -ws -Fo *W src/*.asm
	libw -q -b -n -c -fac $@ *.obj
	del *.obj

endif