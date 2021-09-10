
CLASSNAME equ <"SetSmoothingMode">

OnPaint macro hdc

   .new g:Graphics(hdc)
   .new b1:SolidBrush(Green)
   .new b2:SolidBrush(Green)

    ;; Set the smoothing mode to SmoothingModeHighSpeed, and fill an ellipse.

    g.SetSmoothingMode(SmoothingModeHighSpeed)
    g.FillEllipse(&b1, 0, 0, 200, 100)

    ;; Set the smoothing mode to SmoothingModeHighQuality, and fill an ellipse.

    g.SetSmoothingMode(SmoothingModeHighQuality)
    g.FillEllipse(&b2, 200, 0, 200, 100)

    g.Release()
    exitm<>
    endm

include Graphics.inc

