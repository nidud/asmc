;
; https://docs.microsoft.com/en-us/dotnet/api/system.drawing.graphics.drawbezier?view=dotnet-plat-ext-3.1
;
include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"DrawBezier">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)

   .new path:GraphicsPath()
   .new pen:Pen(Yellow)

   .new start:Point(100, 100)
   .new control1:Point(200, 10)
   .new control2:Point(350, 50)
   .new pend:Point(500, 100)

    path.StartFigure()
    path.AddBezier(start, control1, control2, pend)
    path.CloseFigure()
    g.DrawPath(&pen, &path)

    pen.SetColor(Green)
    mov control1.Y,110
    mov control2.Y,150
    mov start.Y,200
    mov pend.Y,200
    g.DrawBezier(&pen, start, control1, control2, pend)

    pen.Release()
    path.Release()
    g.Release()
    ret

OnPaint endp

include Graphics.inc

