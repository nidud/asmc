#
# Makefile for Asmc
#

flags = -Cs -Iinc -I../../include
ifdef SUBVERSION
flags += -DSUBVERSION=$(SUBVERSION)
endif
ifdef MASM
flags += -DMASMCOMPAT
endif

ifdef YACC
link = -o $@
ifdef debug
flags += -Zd -Zf
else
link += -s
endif
else
link = -out:$@.exe -stack:0x300000,0x200000
endif

ifdef x86
acc = asmc
flags += -Zp4
ifdef YACC
flags += -elf
ifdef LIBC
flags += -MT
endif
else
flags += -coff
endif
else
acc = asmc64
flags += -Zp8
ifdef YACC
ifdef LIBC
flags += -MT
else
flags += -fpic
endif
else
flags += -win64 -frame
endif
endif

ifdef YACC
CC = ../../bin/$(acc)
else
CC = ..\..\bin\$(acc).exe
endif

all: asmc asmc64 clean

asmc:
ifdef YACC
	chmod a+x $(CC)
endif
	$(CC) $(flags) src/*.asm -link $(link)

asmc64:
	$(CC) -DASMC64 $(flags) src/*.asm -link $(link)

asmcinc:
	$(CC) -DASMCINC $(flags) src/*.asm -link $(link)

clean:
ifdef YACC
	rm *.o
else
	del *.obj
endif

ifdef YACC

install: install_asmc
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
	sudo install ./asmc64 /usr/bin
	rm ./asmc
	rm ./asmc64

uninstall:
	sudo rm -f /usr/bin/asmc
	sudo rm -f /usr/bin/asmc64
	sudo rm -f -R /usr/lib/asmc
	sudo rm -f /etc/profile.d/asmc-profile.sh

build_libc:
	make -C ../libc

# Note: build LIBC before using these

debug32:
	make x86=1 LIBC=1 debug=1 asmc clean
	gdb -x ../test/dwarf/layout.gdb --args asmc -c -elf64 -Zd -fPIC ../test/dwarf/dynamic2/func2.asm
	rm ./asmc

debug64:
	make LIBC=1 debug=1 asmc64 clean
	gdb -x ../test/dwarf/layout.gdb --args asmc64 -c -Zd -fPIC ../test/dwarf/dynamic2/func2.asm
	rm ./asmc64

else

# Build Asmc using LINKW

release:
	del *.obj
	make SUBVERSION=64 x86=1 asmc
	make SUBVERSION=64 asmc64
	del *.obj
	copy asmc.exe ..\..\bin
	copy asmc64.exe ..\..\bin

asmc32:
	make x86=1 asmc
	make x86=1 asmc64
	make asmc64
	del *.obj

masm_compat:
	make MASM=1 asmc
	make MASM=1 asmc64
	del *.obj

linux32:
	md $@
	asmc -Iinc -elf -Zp4 -Cs src\*.asm -link -nor -st:0x300000 -d:libc.a -o:$@\asmc.
	asmc -DASMC64 -Iinc -elf -Zp4 -Cs src\*.asm -link -nor -st:0x300000 -d:libc.a -o:$@\asmc64.
	del *.o

linux64:
	md $@
	asmc -Iinc -elf64 -Zp8 -Cs src\*.asm -link -nor -st:0x300000 -d:libc.a -o:$@\asmc.
	asmc -DSUBVERSION=58 -DASMC64 -Iinc -elf64 -Zp8 -Cs src\*.asm -link -nor -st:0x300000 -d:libc.a -o:$@\asmc64.
	del *.o

owlinux:
	md $@
	asmc -Fe$@\asmc. -Iinc -elf -Zp4 -Cs src\*.asm -link -nor -st:0x300000 -d:\watcom\lib386\linux\clib3s.lib
	asmc -DASMC64 -Fe$@\asmc64. -Iinc -elf -Zp4 -Cs src\*.asm -link -nor -st:0x300000 -d:\watcom\lib386\linux\clib3s.lib
	del *.o

endif
