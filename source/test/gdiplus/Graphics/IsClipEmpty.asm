;
; https://docs.microsoft.com/en-us/windows/win32/api/gdiplusgraphics/nf-gdiplusgraphics-graphics-isclipempty
;
CLASSNAME equ <"IsClipEmpty">

OnPaint macro hdc

   .new g:Graphics(hdc)

    ;; If the clipping region is not empty, draw a rectangle.

    .if (!g.IsClipEmpty())

        .new p:Pen(White, 3.0)

        g.DrawRectangle(&p, 0, 0, 100, 100)
    .endif

    g.Release()
    exitm<>
    endm

include Graphics.inc

