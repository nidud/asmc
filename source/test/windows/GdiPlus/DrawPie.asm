include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"DrawPie">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)
   .new p:Pen(White)

    g.DrawPie(&p, 0.0, 0.0, 200.0, 100.0, 0.0, 45.0)
    g.DrawPie(&p, 0, 100, 200, 100, 0.0, 45.0)

    p.Release()
    g.Release()
    ret

OnPaint endp

include Graphics.inc

