include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"DrawPolygon">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)

   ; Create pen.

   .new p:Pen(White, 3.0)

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

    ; Draw polygon curve to screen.

    g.DrawPolygon(&p, &points, 7)

    p.Release()
    g.Release()
    ret

OnPaint endp

include Graphics.inc

