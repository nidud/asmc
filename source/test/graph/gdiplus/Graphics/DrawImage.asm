include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"DrawImage">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)
   .new i:Image(L"..\\bitmap\\image.png")

    g.DrawImage(&i, 100.0, 100.0, 60.0, 50.0, 150.0, 48.0, UnitPixel)

    i.Release()
    g.Release()
    ret

OnPaint endp

include Graphics.inc

