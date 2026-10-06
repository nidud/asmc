#
# Makefile for Asmc
#

flags = -Cs -Iinc -I../../include

ifdef MASM
flags += -DMASMCOMPAT
endif

ifdef YACC
link = -o $@
ifdef debug
flags += -Zd -Zf
endif
ifdef MT
flags += -MT
else
ifndef static
flags += -fplt
endif
endif
else
link = -out:$@.exe -stack:0x300000,0x200000
endif

ifdef x86
acc = asmc
flags += -Zp4
ifdef YACC
flags += -elf
else
flags += -coff
endif
else
acc = asmc64
flags += -Zp8
ifndef YACC
flags += -frame
endif
endif

ifdef YACC
CC = ../../bin/$(acc)
else
CC = ..\..\bin\$(acc).exe
endif

all: asmc asmc64

asmc:
ifdef YACC
	chmod a+x $(CC)
endif
	$(CC) $(flags) src/*.asm -link $(link)
ifdef YACC
	rm -f *.o
endif

asmc64:
	$(CC) -DASMC64 $(flags) src/*.asm -link $(link)
ifdef YACC
	rm -f *.o
endif

asmcinc:
	$(CC) -DASMCINC $(flags) src/*.asm -link $(link)
ifdef YACC
	rm -f *.o
endif

clean:
ifdef YACC
	rm -f *.o
else
	del *.obj
endif

ifdef YACC
.PHONY: all asmc asmc64 asmcinc clean install install_asmc install_asmc64 uninstall debug32 debug64 debugmt32 debugmt64

install: all install_asmc install_asmc64
	sudo rm -f -R /usr/lib/asmc
	sudo mkdir /usr/lib/asmc
	sudo mkdir /usr/lib/asmc/x86
	sudo cp -R ../../include /usr/lib/asmc/include
	sudo cp ./asmc-profile.sh /etc/profile.d
	@echo ----------------------------------------------------
	@echo These changes may need a reboot: see asmc-profile.sh
	@echo ----------------------------------------------------

install_asmc:
	sudo install ./asmc /usr/bin

install_asmc64:
	sudo install ./asmc64 /usr/bin

uninstall:
	sudo rm -f /usr/bin/asmc
	sudo rm -f /usr/bin/asmc64
	sudo rm -f -R /usr/lib/asmc
	sudo rm -f /etc/profile.d/asmc-profile.sh

debug32:
	make x86=1 debug=1 asmc clean
	gdb -x ../test/dwarf/layout.gdb --args asmc -I../../include -Fe pltgot -elf -Zd -fPIC ../test/dwarf/pltgot/got.asm -fplt ../test/dwarf/pltgot/plt.asm
#	gdb -x ../test/dwarf/layout.gdb pltgot
	rm -f ./asmc
#	rm ./pltgot

debug64:
	make debug=1 asmc64 clean
	gdb -x ../test/dwarf/layout.gdb --args asmc64 -c -I../../include -Zd -fPIC ../test/dwarf/pltgot/got.asm
	rm -f ./asmc64

build_libc:
	make -C ../libc

# Note: This assumes install and build_libc is done

debugmt32:
	make x86=1 MT=1 debug=1 asmc clean
	gdb -x ../test/dwarf/layout.gdb --args asmc -c -elf -Zd -fPIC ../test/dwarf/pltgot/got.asm
	rm -f ./asmc

debugmt64:
	make MT=1 debug=1 asmc clean
	gdb -x ../test/dwarf/layout.gdb --args asmc -c -elf64 -Zd -fPIC ../test/dwarf/pltgot/got.asm
	rm -f ./asmc

else

# Build Asmc using LINKW

release:
	del *.obj
	make x86=1 asmc
	make asmc64
	del *.obj
	copy asmc.exe ..\..\bin
	copy asmc64.exe ..\..\bin

asmc32:
	make x86=1 asmc
	make x86=1 asmc64
	del *.obj

masm_compat:
	make MASM=1 asmc
	make MASM=1 asmc64
	del *.obj

linux32:
	md $@
	asmc -Iinc -elf -Zp4 -Cs src\*.asm -link -nor -st:0x300000 -d:libcmt.a -o:$@\asmc.
	asmc -DASMC64 -Iinc -elf -Zp4 -Cs src\*.asm -link -nor -st:0x300000 -d:libcmt.a -o:$@\asmc64.
	del *.o

linux64:
	md $@
	asmc -Iinc -elf64 -Zp8 -Cs src\*.asm -link -nor -st:0x300000 -d:libcmt.a -o:$@\asmc.
	asmc -DASMC64 -Iinc -elf64 -Zp8 -Cs src\*.asm -link -nor -st:0x300000 -d:libcmt.a -o:$@\asmc64.
	del *.o

owlinux:
	md $@
	asmc -Fe$@\asmc. -Iinc -elf -Zp4 -Cs src\*.asm -link -nor -st:0x300000 -d:\watcom\lib386\linux\clib3s.lib
	asmc -DASMC64 -Fe$@\asmc64. -Iinc -elf -Zp4 -Cs src\*.asm -link -nor -st:0x300000 -d:\watcom\lib386\linux\clib3s.lib
	del *.o

endif
