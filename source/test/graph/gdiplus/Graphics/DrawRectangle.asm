
CLASSNAME equ <"DrawRectangle">

OnPaint macro hdc

   .new g:Graphics(hdc)
   .new p:Pen(White)
   .new i:Rect(0, 0, 200, 200)
   .new f:RectF(30.0, 20.0, 150.0, 150.0)

    g.DrawRectangle(&p, &f)
    g.DrawRectangle(&p, &i)

    p.Release()
    g.Release()

    exitm<>
    endm

include Graphics.inc

