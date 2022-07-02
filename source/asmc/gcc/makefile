
pic-default = yes

ifeq (yes,$(pic-default))
lpic = -Wl,-pie,-z,now,-z,noexecstack
apic = -fpic
else
lpic = -Wl,-no-pie
endif

CC = ../../../bin/asmc64
flags = $(apic) -Zp8 -Cs -I../inc -I../../../include

all: asmc asmc64 clean

asmc:
	chmod u=rwx,go=r $(CC)
	$(CC) $(flags) ../../libc/fltintrn/*.asm ../src/*.asm
	gcc $(lpic) -s -o $@ *.o

asmc64:
	$(CC) -DASMC64 $(flags) ../../libc/fltintrn/*.asm ../src/*.asm
	gcc $(lpic) -s -o $@ *.o

clean:
	rm *.o

install:
	sudo install ./asmc /usr/local/bin
	sudo install ./asmc64 /usr/local/bin
