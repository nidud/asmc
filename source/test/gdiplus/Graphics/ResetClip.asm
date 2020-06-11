
CLASSNAME equ <"ResetClip">

OnPaint macro hdc

   .new g:Graphics(hdc)

    ;; Set the clipping region, and draw its outline.

   .new r:Rect(100, 50, 200, 120)

    g.SetClip(&r)

   .new blackPen:Pen(White, 2.0)

    g.DrawRectangle(&blackPen, 100, 50, 200, 120);

    ;; Fill a clipped ellipse in red.

   .new c1:Color(255, 255, 0, 0)
   .new redBrush:SolidBrush(c1)

    g.FillEllipse(&redBrush, 80, 40, 100, 70)

    ;; Reset the clipping region.

    g.ResetClip()

    ;; Fill an unclipped ellipse with blue.

   .new c2:Color(255, 0, 0, 255)
   .new blueBrush:SolidBrush(c2)

    g.FillEllipse(&blueBrush, 160, 150, 100, 60)
    g.Release()
    exitm<>
    endm

include Graphics.inc

