
libdir = %ASMCDIR%\lib
SRCDIR = %ASMCDIR%\source\consx

CONSXS = %ASMCDIR%\lib\consxs.lib
CONSXC = %ASMCDIR%\lib\consxc.lib

all: $(CONSXC) $(CONSXS)

$(CONSXC):
    asmc /coff /Cs /Zi $(SRCDIR)\x86\*.asm
    libw /q /b /n /c /fac $@ *.obj
    del *.obj

$(CONSXS):
    asmc /coff /Cs /Gz /Zi $(SRCDIR)\x86\*.asm
    libw /q /b /n /c /fac $@ *.obj
    del *.obj
