!include srcpath

AFLAGS = -Zi -Zp8 -D_CRTBLD -Cs -I$(inc_dir)

target_path = $(lib_dir)\x64

$(target_path)\libc.lib: $(target_path)
    asmc64 $(AFLAGS) /r $(src_dir)\libs\lib64\*.asm
    libw /q /b /n /c /fac $@ *.obj
    del *.obj

$(target_path):
    if not exist $(target_path) md $(target_path)
