include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"SetSmoothingMode">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

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
    ret

OnPaint endp

include Graphics.inc

