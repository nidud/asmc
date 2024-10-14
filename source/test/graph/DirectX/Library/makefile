!include srcpath

aflags = -q -I$(inc_dir)

all: build clean

targets = \
    ConvertVectorFloatToInt.obj \
    ConvertVectorIntToFloat.obj \
    ScalarSinCos.obj \
    Sin.obj \
    Tan.obj

.asm.obj:
    asmc64 $(aflags) $*.asm

build: $(targets)

clean:
    del *.obj
