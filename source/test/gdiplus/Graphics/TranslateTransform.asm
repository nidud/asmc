
CLASSNAME equ <"TranslateTransform">

OnPaint macro hdc

   .new g:Graphics(hdc)
   .new pen:Pen(White)

    g.RotateTransform(30.0)
    g.TranslateTransform(100.0, 50.0, MatrixOrderAppend)
    g.DrawEllipse(&pen, 0, 0, 200, 80)
    g.Release()
    exitm<>
    endm

include Graphics.inc

