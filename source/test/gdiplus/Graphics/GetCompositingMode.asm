;
; https://docs.microsoft.com/en-us/windows/win32/api/gdiplusgraphics/nf-gdiplusgraphics-graphics-getcompositingmode
;
CLASSNAME equ <"GetCompositingMode">

OnPaint macro hdc

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
    exitm<>
    endm

include Graphics.inc

