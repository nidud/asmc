;
; https://docs.microsoft.com/en-us/windows/win32/api/gdiplusgraphics/nf-gdiplusgraphics-graphics-gethalftonepalette
;
include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"GetHalftonePalette">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new image:Image(L"..\\res\\Mosaic.png")
   .new g:Graphics(hdc)

    g.DrawImage(&image, 10, 10)
    g.Release()

   .new hPalette:HPALETTE
    mov hPalette,g.GetHalftonePalette()

    SelectPalette(hdc, hPalette, FALSE)
    RealizePalette(hdc)

   .new g:Graphics(hdc)

    g.DrawImage(&image, 300, 10)
    g.Release()
    DeleteObject(hPalette)
    ret

OnPaint endp

include Graphics.inc

