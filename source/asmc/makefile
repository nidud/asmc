#
# Makefile for Asmc
#
ifdef YACC

acc = asmc236
pic-default = yes
ifeq (yes,$(pic-default))
lpic = -Wl,-pie,-z,now,-z,noexecstack
apic = -fpic
else
lpic = -Wl,-no-pie
endif
CC = ./$(acc)
flags = $(apic) -Zp8 -Cs -Iinc -I../../include
ifeq (asmc,$(acc))
flags += -elf64
endif
all: asmc236 asmc asmc64 clean

else

NAME = asmc
FLAG = -Zp8 -win64 -frame
LIBP = x64
ifdef x86
FLAG = -Zp4 -coff
LIBP = x86
endif
ifdef ASMC64
NAME = asmc64
FLAG += -DASMC64
endif
ifndef OUTP
OUTP = .
endif

$(OUTP)\$(NAME).exe:
	del *.obj
	..\..\bin\$(NAME) -c $(FLAG) -Cs -Iinc -I..\..\include src\*.asm
	..\..\bin\linkw @<<
libpath ..\..\lib\$(LIBP)
name	$@
option	stack=0x300000 com stack=0x200000
file	{ *.obj }
<<
	del *.obj
endif

asmc236:
	gcc -c src/gas/*.s && gcc -Wl,-pie -s -o $@ *.o

asmc:
	$(CC) -c $(flags) ../libc/fltintrn/*.asm src/*.asm
	gcc $(lpic) -s -o $@ *.o

asmc64:
	$(CC) -c -DASMC64 $(flags) ../libc/fltintrn/*.asm src/*.asm
	gcc $(lpic) -s -o $@ *.o
#	$(CC) -c -DASMC64 $(flags) src/*.asm
#	gcc -static -nostdlib -Wl,-no-pie -s -o $@ *.o -l:libasmc.a

clean:
	rm *.o
	rm ./asmc236

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

