include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"TranslateTransform">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)
   .new pen:Pen(White)

    g.RotateTransform(30.0)
    g.TranslateTransform(100.0, 50.0, MatrixOrderAppend)
    g.DrawEllipse(&pen, 0, 0, 200, 80)
    g.Release()
    ret

OnPaint endp

include Graphics.inc

