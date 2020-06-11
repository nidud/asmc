;
; https://docs.microsoft.com/en-us/windows/win32/api/gdiplusgraphics/nf-gdiplusgraphics-graphics-gethalftonepalette
;
CLASSNAME equ <"GetHalftonePalette">

OnPaint macro _hdc

   .new hdc:HDC
    mov hdc,rax

   .new image:Image(L"..\\ImageAttributes\\Mosaic.png")
   .new g:Graphics(hdc)

    g.DrawImage(&image, 10, 10)
    g.Release()

   .new hPalette:HPALETTE
    mov hPalette,Graphics_GetHalftonePalette()

    SelectPalette(hdc, hPalette, FALSE)
    RealizePalette(hdc)

   .new g:Graphics(hdc)

    g.DrawImage(&image, 300, 10)
    g.Release()
    DeleteObject(hPalette)
    exitm<>
    endm

include Graphics.inc

