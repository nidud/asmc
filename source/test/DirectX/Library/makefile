
all: build clean

targets = \
    ConvertVectorFloatToInt.obj \
    ConvertVectorIntToFloat.obj \
    ScalarSinCos.obj \
    Sin.obj \
    Tan.obj

.asm.obj:
    asmc64 -nologo $*.asm
    linkw system con_64 file $@

build: $(targets)

clean:
    del *.obj
