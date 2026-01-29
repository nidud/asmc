;
; https://docs.microsoft.com/en-us/dotnet/api/system.drawing.graphics.drawbezier?view=dotnet-plat-ext-3.1
;
include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"DrawBeziers">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)

   ; Create pen.

   .new p:Pen(White, 3.0)

   ; Create points that define curve.

   .new points[7]:Point = {
        {  10,  10 },
        {  40,  20 },
        {  50,  50 },
        {  50, 120 },
        { 600, 150 },
        { 650, 250 },
        { 400, 300 }
        }

   .new pointsF[7]:PointF = {
        { 500.0, 300.0 },
        { 650.0, 250.0 },
        { 600.0, 150.0 },
        { 500.0, 100.0 },
        { 350.0,  50.0 },
        { 200.0,  10.0 },
        { 100.0, 100.0 }
        }

    ; Draw REAL-curve to screen.

    g.DrawBeziers(&p, &pointsF, 7)

    ; Draw INT-curve to screen.

    p.SetColor(Red)
    g.DrawBeziers(&p, &points, 7)

    p.Release()
    g.Release()
    ret

OnPaint endp


include Graphics.inc

