asmc = \asmc

all: test.exe test_pe.exe test_c.exe clean

test.exe:
 asmc $*.asm
 linkw symt _cstart file $*

test_pe.exe:
 asmc -pe -D__PE__ $*.asm

test_c.exe:
 cl /I$(asmc)\include $*.c /link /libpath:$(asmc)\lib

clean:
 del *.obj