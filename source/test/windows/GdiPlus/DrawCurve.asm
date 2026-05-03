include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"DrawCurve">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)

   ; Create pen.

   .new p:Pen(Red, 3.0)

   ; Create points that define curve.

   .new points[7]:Point = {
        {  50,  50 },
        { 100,  25 },
        { 200,   5 },
        { 250,  50 },
        { 300, 100 },
        { 350, 200 },
        { 250, 150 }
        }

    ; Draw lines between original points to screen.

    g.DrawLines(&p, &points, 7)

    ; Draw curve to screen.

    p.SetColor(Green)
    g.DrawCurve(&p, &points, 7)

    p.Release()
    g.Release()
    ret

OnPaint endp

include Graphics.inc

