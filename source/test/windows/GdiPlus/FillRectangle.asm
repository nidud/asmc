include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"FillRectangle">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)
   .new b:SolidBrush(Blue)
   .new r:RectF(40.0, 40.0, 200.0, 200.0)

    g.FillRectangle(&b, r)

    b.Release()
    g.Release()
    ret

OnPaint endp

include Graphics.inc

