!include srcpath

UUID32 = $(lib_dir)\uuid.lib
UUID64 = $(lib_dir)\x64\uuid.lib

all: list.exe $(UUID32) $(UUID64) clean

$(UUID32):
        asmc -coff *.u
        libw -q -b -n -c -fac $@ *.obj
        del *.obj

$(UUID64):
        asmc -win64 *.u
        libw -q -b -n -c -fac $@ *.obj
        del *.obj

list.exe:
        asmc -q guid.asm > list.txt
        asmc -pe $*.asm
        $@

clean:
        del *.u
        del list.txt
        del list.exe
