;
; https://docs.microsoft.com/en-us/windows/win32/api/gdiplusgraphics/nf-gdiplusgraphics-graphics-getcompositingmode
;
include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"GetCompositingMode">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)

    g.SetCompositingMode(CompositingModeSourceCopy)

   .new c1:Color(128, 255, 0, 0)
   .new alphaBrush:SolidBrush(c1)

    g.FillRectangle(&alphaBrush, 0, 0, 100, 100)

    ;; Get the compositing mode.

   .new compMode:CompositingMode
    mov compMode,g.GetCompositingMode()

    ;; Change the compositing mode if it is CompositingModeSourceCopy.

    .if (compMode == CompositingModeSourceCopy)

        g.SetCompositingMode(CompositingModeSourceOver)
    .endif

    g.FillRectangle(&alphaBrush, 0, 100, 100, 100)
    g.Release()
    ret

OnPaint endp

include Graphics.inc

