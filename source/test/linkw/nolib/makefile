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

FL = /NOLOGO /MAP /MACHINE:$(MC) /SUBSYSTEM:CONSOLE /LIBPATH:%ASMCDIR%\lib\$(MC)

all: nolib nolib0 clean

nolib:
	$(CC) -q -nolib $@.asm
	$(LC) $(FL) $@.obj msvcrt.lib msvcrt0.lib
	$@
nolib0:
	$(CC) -q -nolib $@.asm
	$(LC) $(FL) $@.obj msvcrt.lib msvcrt0.lib
	$@
clean:
	pause
	del *.obj
	del *.exe
x86:
	make MC=x86
mslink:
	make LC=LINK

