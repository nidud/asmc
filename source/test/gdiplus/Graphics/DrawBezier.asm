;
; https://docs.microsoft.com/en-us/dotnet/api/system.drawing.graphics.drawbezier?view=dotnet-plat-ext-3.1
;
CLASSNAME equ <"DrawBezier">

OnPaint macro hdc

   .new g:Graphics(hdc)
   .new c:GraphicsPath()
   .new p:Pen(Yellow)

   .new s:Point(100, 100)
   .new a:Point(200, 10)
   .new b:Point(350, 50)
   .new e:Point(500, 100)

    c.StartFigure()
    c.AddBezier(&s, &a, &b, &e)
    c.CloseFigure()
    g.DrawPath(&p, &c)

    p.New(Green)
    mov a.Y,110
    mov b.Y,150
    mov s.Y,200
    mov e.Y,200
    g.DrawBezier(&p, &s, &a, &b, &e)

    p.Release()
    c.Release()
    g.Release()

    exitm<>
    endm

include Graphics.inc

