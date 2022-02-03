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
   .new c:GraphicsPath()
   .new p:Pen(Yellow)

   .new s:Point(100, 100)
   .new a:Point(200, 10)
   .new b:Point(350, 50)
   .new e:Point(500, 100)

    c.StartFigure()
    c.AddBezier(s, a, b, e)
    c.CloseFigure()
    g.DrawPath(&p, &c)
    p.Release()

   .new p:Pen(Green)
    mov a.Y,110
    mov b.Y,150
    mov s.Y,200
    mov e.Y,200
    g.DrawBezier(&p, s, a, b, e)

    p.Release()
    c.Release()
    g.Release()
    ret

OnPaint endp

include Graphics.inc

