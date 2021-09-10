;
; https://docs.microsoft.com/en-us/dotnet/api/system.drawing.graphics.drawbezier?view=dotnet-plat-ext-3.1
;
CLASSNAME equ <"DrawBeziers">

OnPaint macro hdc

   .new g:Graphics(hdc)
   .new c:GraphicsPath()
   .new p:Pen(White)

   .new i6:Point(400, 300)
   .new i5:Point(650, 250)
   .new i4:Point(600, 150)
   .new i3:Point( 50, 120)
   .new i2:Point( 50,  50)
   .new i1:Point( 40,  20)
   .new ii:Point( 10,  10)

   .new e2:PointF(500.0, 300.0)
   .new c4:PointF(650.0, 250.0)
   .new c3:PointF(600.0, 150.0)
   .new e1:PointF(500.0, 100.0)
   .new c2:PointF(350.0,  50.0)
   .new c1:PointF(200.0,  10.0)
   .new ff:PointF(100.0, 100.0)

    g.DrawBeziers(&p, &ff, 7)
    p.New(Red)
    g.DrawBeziers(&p, &ii, 7)

    p.Release()
    c.Release()
    g.Release()

    exitm<>
    endm

include Graphics.inc

