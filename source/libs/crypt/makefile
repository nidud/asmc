!include srcpath

flags = -nologo -nolib
win32 = $(lib_dir)\crypt.lib
win64 = $(lib_dir)\x64\crypt.lib
elf32 = $(lib_dir)\elf\crypt.lib

base32 = $(src_dir)\libs\crypt\x86\*.asm
base64 = $(src_dir)\libs\crypt\x64\*.asm

all: $(win32) $(win64) $(elf32)

$(win32):
    asmc $(flags) -coff -safeseh -Zi $(base32)
    libw -q -b -n -c -fac $@ *.obj
    del *.obj

$(win64):
    asmc $(flags) -win64 $(base64)
    libw -q -b -n -c -fac $@ *.obj
    del *.obj

$(elf32):
    if not exist $(lib_dir)\elf md $(lib_dir)\elf
    asmc $(flags) -elf $(base32)
    libw -q -b -n -c -ie $@ *.obj
    del *.obj

