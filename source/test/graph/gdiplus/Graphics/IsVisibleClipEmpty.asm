;
; https://docs.microsoft.com/en-us/windows/win32/api/gdiplusgraphics/nf-gdiplusgraphics-graphics-isvisibleclipempty
;
include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"IsVisibleClipEmpty">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)

    ;; If the clipping region is not empty, draw a rectangle.

    .if (!g.IsVisibleClipEmpty())

        .new p:Pen(White, 3.0)

        g.DrawRectangle(&p, 0, 0, 100, 100)
    .endif

    g.Release()
    ret

OnPaint endp

include Graphics.inc

