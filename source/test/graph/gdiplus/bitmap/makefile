png_to_bmp.exe:
    asmc64 -pe -Zp8 png_to_bmp.asm
    asmc64 -pe -Zp8 bmp_to_png.asm
    asmc64 -ws -pe -Zp8 jpeg_compression.asm
    asmc64 -ws -pe -Zp8 -gui gui.asm
    if exist gui.exe gui

