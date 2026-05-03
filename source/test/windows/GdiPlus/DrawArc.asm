;
; https://docs.microsoft.com/en-us/dotnet/api/system.drawing.drawing2d.graphicspath.addarc?view=dotnet-plat-ext-3.1
;
include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"DrawArc">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)
   .new c:GraphicsPath()
   .new p:Pen(Red, 3.0)
   .new r:Rect(90, 45, 50, 100)

    c.StartFigure()
    c.AddArc(r, 0.0, 180.0)
    c.CloseFigure()
    g.DrawPath(&p, &c)

    p.SetColor(Green)
    p.SetWidth(2.0)
    g.DrawArc(&p, 20.0, 20.0, 100.0, 200.0, 45.0, 270.0)

    p.Release()
    c.Release()
    g.Release()
    ret

OnPaint endp

include Graphics.inc

