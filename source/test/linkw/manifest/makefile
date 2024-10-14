ifndef LC
LC = LINKW
endif
CC = ASMC64
FL = /MACHINE:x64 /SUBSYSTEM:CONSOLE /LIBPATH:%ASMCDIR%\lib\x64 /MERGE:.CRT=.rdata

all: manifest clean

manifest:
	$(CC) -c $@.asm
	$(LC) /$@ $(FL) $@.obj
	$(CC) -c -Fo my$@ $@.asm
	$(LC) /$@ /$@FILE:my.$@ $(FL) $@.obj
	$(CC) -c $@dependency.asm
	$(LC) $(FL) $@dependency.obj

clean:
	del *.obj
	del *.exe

mslink:
	make LC=LINK
