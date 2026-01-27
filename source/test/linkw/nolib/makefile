ifndef LC
LC = LINKW
endif
ifndef MC
MC = x64
endif
ifeq x64 $(MC)
CC = ASMC64
else
CC = ASMC -coff
endif

all: nolib nolib0 clean

nolib:
	$(CC) -q -nolib $@.asm -link -defaultlib:msvcrt.lib -map
	$@
nolib0:
	$(CC) -q -nolib $@.asm -link -defaultlib:msvcrt.lib -map
	$@
clean:
	pause
	del *.obj
	del *.exe
x86:
	make MC=x86
mslink:
	make LC=LINK

