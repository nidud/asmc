include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"DrawRectangle">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)
   .new p:Pen(White)
   .new i:Rect(0, 0, 200, 200)
   .new f:RectF(30.0, 20.0, 150.0, 150.0)

    g.DrawRectangle(&p, f)
    g.DrawRectangle(&p, i)

    p.Release()
    g.Release()
    ret

OnPaint endp

include Graphics.inc

