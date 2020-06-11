
CLASSNAME equ <"Restore">

OnPaint macro hdc

   .new g:Graphics(hdc)
   .new state1:GraphicsState
   .new state2:GraphicsState
   .new redPen:Pen(Red)
   .new greenPen:Pen(Green)
   .new bluePen:Pen(Blue)

    g.RotateTransform(30.0)
    mov state1,g.Save()
    g.TranslateTransform(100.0, 0.0, MatrixOrderAppend)
    mov state2,g.Save()
    g.ScaleTransform(1.0, 3.0, MatrixOrderAppend)

    ;; Draw an ellipse.
    ;; Three transformations apply: rotate, then translate, then scale.

    g.DrawEllipse(&redPen, 0, 0, 100, 20)

    ;; Restore to state2 and draw the ellipse again.
    ;; Two transformations apply: rotate then translate.

    g.Restore(state2)
    g.DrawEllipse(&greenPen, 0, 0, 100, 20)

    ;; Restore to state1 and draw the ellipse again.
    ;; Only the rotation transformation applies.

    g.Restore(state1)
    g.DrawEllipse(&bluePen, 0, 0, 100, 20)
    g.Release()
    exitm<>
    endm

include Graphics.inc

