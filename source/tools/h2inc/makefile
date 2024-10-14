#
# Makefile for H2INC
#
aflags = -c -q -Cs

ifdef YACC

ifdef static
lflags = -nostdlib -Wl,-no-pie -l:libasmc.a
else
aflags += -fpic
lflags = -Wl,-pie,-z,now,-z,noexecstack
endif

h2inc:
	asmc64 $(aflags) $@.asm
	gcc -s -o $@ $@.o $(lflags)

else

ifdef static
aflags += -frame
else
aflags += -pe -frame -Fo \asmc\bin\h2inc.exe
endif
h2inc.exe:
	asmc64 $(aflags) $*.asm
ifdef static
	linkw system con_64 file $*
endif
endif

clean:
ifdef YACC
	rm -f *.o
	rm -f ./h2inc
else
ifdef static
	del h2inc.obj
endif
	del h2inc.exe
endif
