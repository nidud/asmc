
CLASSNAME equ <"DrawEllipse">

OnPaint macro hdc

   .new g:Graphics(hdc)
   .new c:GraphicsPath()
   .new p:Pen(White)
   .new i:Rect(0, 0, 200, 200)
   .new f:RectF(30.0, 20.0, 150.0, 150.0)

    g.DrawEllipse(&p, &f)
    g.DrawEllipse(&p, &i)

    p.Release()
    c.Release()
    g.Release()

    exitm<>
    endm

include Graphics.inc

