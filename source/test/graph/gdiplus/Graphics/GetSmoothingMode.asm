;
; https://docs.microsoft.com/en-us/windows/win32/api/gdiplusgraphics/nf-gdiplusgraphics-graphics-getsmoothingmode
;
include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"GetSmoothingMode">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)

    ;; Set the smoothing mode to SmoothingModeHighSpeed.
    g.SetSmoothingMode(SmoothingModeHighSpeed)

   .new p:Pen(Red, 3.0)
   .new r:Rect(10, 0, 200, 100)
   .new mode:SmoothingMode

    ;; Draw an ellipse.
    g.DrawEllipse(&p, r)

    ;; Get the smoothing mode.
    mov mode,g.GetSmoothingMode()

    ;; Test mode to see whether smoothing has been set for the Graphics object.

    .if (mode == SmoothingModeAntiAlias)
    ;.if (mode == SmoothingModeNone)

        g.SetSmoothingMode(SmoothingModeHighQuality)
    .endif

    ;; Draw an ellipse to demonstrate the difference.

    p.Release()

   .new p:Pen(Red, 3.0)
   .new r:Rect(220, 0, 200, 100)

    g.DrawEllipse(&p, r)

    g.Release()
    ret

OnPaint endp

include Graphics.inc

