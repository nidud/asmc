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

FL = /MACHINE:$(MC) /SUBSYSTEM:WINDOWS /LIBPATH:%ASMCDIR%\lib\$(MC) /MERGE:.CRT=.rdata

all: clean mydll myapp

mydll:
	$(CC) -c $@.asm
	$(LC) $(FL) /DLL /DEF:$@.def $@.obj
myapp:
	$(CC) -c $@.asm
	$(LC) $(FL) $@.obj
clean:
	del *.obj
	del *.exe
	del *.dll
	del *.lib
pe:
	asmc -peg myapp.asm -ped mydll.asm
pe64:
	asmc64 -peg myapp.asm -ped mydll.asm
x86:
	make MC=x86
mslink:
	make LC=LINK

