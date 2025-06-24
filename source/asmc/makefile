#
# Makefile for Asmc
#

flags = -Cs -Iinc -I../../include

ifdef YACC
link = -o $@ -s
else
link = -out:$@.exe -stack:0x300000,0x200000
endif

ifdef x86
acc = asmc
flags += -Zp4
ifdef YACC
ifdef LIBC
link += -m32 -static -nostdlib -l:x86/libasmc.a -Wl,-no-pie,-z,now,-z,noexecstack
else
link += -m32 -static -Wl,-no-pie,-z,now,-z,noexecstack
endif
flags += -elf
else
flags += -coff
endif
else
acc = asmc64
flags += -Zp8
ifdef YACC
ifdef LIBC
link += -static -nostdlib -l:libasmc.a -Wl,-no-pie,-z,now,-z,noexecstack
else
link += -Wl,-pie,-z,now,-z,noexecstack
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

clean:
ifdef YACC
	rm *.o
else
	del *.obj
endif

install:
	sudo install ./asmc /usr/bin
	sudo install ./asmc64 /usr/bin
	sudo rm -f -R /usr/lib/asmc
	sudo mkdir /usr/lib/asmc
	sudo mkdir /usr/lib/asmc/x86
	sudo cp -R ../../include /usr/lib/asmc/include
	sudo rm -f /usr/lib/asmc/include/*.h
	sudo rm -f /usr/lib/asmc/include/*.rh
	sudo rm -f /usr/lib/asmc/include/sys/*.h
	sudo cp ./asmc-profile.sh /etc/profile.d
	rm ./asmc
	rm ./asmc64
	@echo -------------------------------------------
	@echo Note: These changes needs a reboot, or run:
	@echo export INCLUDE=/usr/lib/asmc/include
	@echo -------------------------------------------

uninstall:
	sudo rm -f /usr/bin/asmc
	sudo rm -f /usr/bin/asmc64
	sudo rm -f -R /usr/lib/asmc
	sudo rm -f /etc/profile.d/asmc-profile.sh

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

linux32:
	md $@
	asmc -c -6 -mscrt -MT -elf -Zp4 -Cs -r ..\libc\*.asm ..\libc\*.s
	libw -q -b -n -c asmc.a *.o
	del *.o
	asmc -c -Iinc -elf -Zp4 -Cs src\*.asm
	linkw N $@\asmc. FORM elf RU LIN L asmc.a OP NOR, ST=0x300000 F { *.o }
	asmc -DASMC64 -Iinc -elf -Zp4 -Cs src\*.asm
	linkw N $@\asmc64. FORM elf RU LIN L asmc.a OP NOR, ST=0x300000 F { *.o }
	del *.o
	del asmc.a

linux64:
	md $@
	asmc -c -mscrt -MT -elf64 -Zp8 -Cs -r ..\libc\*.asm ..\libc\*.s
	libw -q -b -n -c asmc.a *.o
	del *.o
	asmc -c -Iinc -elf64 -Zp8 -Cs src\*.asm
	linkw N $@\asmc. FORM elf RU LIN L asmc.a OP NOR, ST=0x300000 F { *.o }
	asmc -DASMC64 -Iinc -elf64 -Zp8 -Cs src\*.asm
	linkw N $@\asmc64. FORM elf RU LIN L asmc.a OP NOR, ST=0x300000 F { *.o }
	del *.o
	del asmc.a

owlinux:
	md $@
	asmc -c -Iinc -elf -Zp4 -Cs src\*.asm
	linkw N $@\asmc. FORM elf RU LIN L \watcom\lib386\linux\clib3s.lib OP NOR, ST=0x300000 F { *.o }
	asmc -c -DASMC64 -Iinc -elf -Zp4 -Cs src\*.asm
	linkw N $@\asmc64. FORM elf RU LIN L \watcom\lib386\linux\clib3s.lib OP NOR, ST=0x300000 F { *.o }
	del *.o
