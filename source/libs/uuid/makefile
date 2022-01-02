!include srcpath

AFLAGS = -I$(inc_dir)
UUID32 = $(lib_dir)\x86\uuid.lib
UUID64 = $(lib_dir)\x64\uuid.lib

all: list.exe $(UUID32) $(UUID64) clean

$(UUID32):
        asmc $(AFLAGS) -coff *.u
        libw -q -b -n -c -fac $@ *.obj
        del *.obj

$(UUID64):
        asmc $(AFLAGS) -win64 *.u
        libw -q -b -n -c -fac $@ *.obj
        del *.obj

list.exe:
        asmc $(AFLAGS) -q guid.asm > list.txt
        asmc $(AFLAGS) -pe $*.asm
        $@

clean:
        del *.u
        del list.txt
        del list.exe
