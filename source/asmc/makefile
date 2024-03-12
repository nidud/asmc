#
# Makefile for Asmc
#
ifdef YACC

acc = asmc64
pic-default = yes
ifeq (yes,$(pic-default))
lpic = -Wl,-pie,-z,now,-z,noexecstack
apic = -fpic
else
lpic = -Wl,-no-pie
endif
CC = ../../bin/$(acc)
flags = $(apic) -Zp8 -Cs -Iinc -I../../include
ifeq (asmc,$(acc))
flags += -elf64
endif
all: asmc asmc64 clean

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
	..\..\bin\$(NAME) $(FLAG) -Cs -Iinc -I..\..\include src\*.asm
	..\..\bin\linkw @<<
libpath ..\..\lib\$(LIBP)
name	$@
symt	_cstart
option	stack=0x300000 com stack=0x200000
file	{ *.obj }
<<
	del *.obj
endif

asmc:
	chmod a+x $(CC)
	$(CC) $(flags) ../libc/fltintrn/*.asm src/*.asm
	gcc $(lpic) -s -o $@ *.o

asmc64:
	$(CC) -DASMC64 $(flags) ../libc/fltintrn/*.asm src/*.asm
	gcc $(lpic) -s -o $@ *.o

clean:
	rm *.o

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

clean_old:
	sudo rm -f /usr/local/bin/asmc
	sudo rm -f /usr/local/bin/asmc64
	sudo rm -f -R /usr/lib/asmc-2.34
	sudo rm -f -R /usr/include/asmc-2.34
	sudo rm -f /etc/profile.d/include-path.sh
