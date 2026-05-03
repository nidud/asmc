include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"DrawImage">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)
   .new image:Image(L"..\\res\\Photograph.jpg")

    g.DrawImage(&image, 100.0, 100.0, 160.0, 150.0, 150.0, 48.0, UnitPixel)

    image.Release()
    g.Release()
    ret

OnPaint endp

include Graphics.inc

