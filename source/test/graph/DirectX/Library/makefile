!include srcpath

aflags = -nologo -I$(inc_dir)

all: build clean

targets = \
    ConvertVectorFloatToInt.obj \
    ConvertVectorIntToFloat.obj \
    ScalarSinCos.obj \
    Sin.obj \
    Tan.obj

.asm.obj:
    asmc64 $(aflags) $*.asm
    linkw system con_64 file $@

build: $(targets)

clean:
    del *.obj
