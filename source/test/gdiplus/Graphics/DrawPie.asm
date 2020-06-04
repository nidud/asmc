
CLASSNAME equ <"DrawPie">

OnPaint macro hdc

   .new g:Graphics(hdc)
   .new p:Pen(White)

    g.DrawPie(&p, 0.0, 0.0, 200.0, 100.0, 0.0, 45.0)
    g.DrawPie(&p, 0, 100, 200, 100, 0.0, 45.0)

    p.Release()
    g.Release()

    exitm<>
    endm

include Graphics.inc

