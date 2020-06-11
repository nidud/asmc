
CLASSNAME equ <"ResetTransform">

OnPaint macro hdc

   .new g:Graphics(hdc)

    ;; Rotate the transformation and draw a rectangle.

    g.RotateTransform(45.0)

   .new blackPen:Pen(White)
   .new redPen:Pen(Red)

    g.DrawRectangle(&blackPen, 100, 0, 100, 50)

    ;; Reset the transformation to identity, and draw a second rectangle.

    g.ResetTransform()
    g.DrawRectangle(&redPen, 110, 0, 100, 50)
    g.Release()
    exitm<>
    endm

include Graphics.inc

