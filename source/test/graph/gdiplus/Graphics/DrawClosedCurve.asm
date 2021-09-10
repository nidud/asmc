
CLASSNAME equ <"DrawClosedCurve">

OnPaint macro hdc

   .new g:Graphics(hdc)
   .new p:Pen(Red)
   .new i6:Point(250, 150)
   .new i5:Point(350, 200)
   .new i4:Point(300, 100)
   .new i3:Point(250,  50)
   .new i2:Point(200,   5)
   .new i1:Point(100,  25)
   .new ii:Point( 50,  50)

    g.DrawLines(&p, &ii, 7)
    p.New(Green)
    g.DrawClosedCurve(&p, &ii, 7, 1.0, FillModeAlternate)

    p.Release()
    g.Release()

    exitm<>
    endm

include Graphics.inc

