
CLASSNAME equ <"FillRectangle">

OnPaint macro hdc

   .new g:Graphics(hdc)
   .new b:SolidBrush(Blue)
   .new r:RectF(40.0, 40.0, 200.0, 200.0)

    g.FillRectangle(&b, &r)

    b.Release()
    g.Release()

    exitm<>
    endm

include Graphics.inc

