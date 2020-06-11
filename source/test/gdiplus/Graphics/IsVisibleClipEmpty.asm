;
; https://docs.microsoft.com/en-us/windows/win32/api/gdiplusgraphics/nf-gdiplusgraphics-graphics-isvisibleclipempty
;
CLASSNAME equ <"IsVisibleClipEmpty">

OnPaint macro hdc

   .new g:Graphics(hdc)

    ;; If the clipping region is not empty, draw a rectangle.

    .if (!g.IsVisibleClipEmpty())

        .new p:Pen(White, 3.0)

        g.DrawRectangle(&p, 0, 0, 100, 100)
    .endif

    g.Release()
    exitm<>
    endm

include Graphics.inc

