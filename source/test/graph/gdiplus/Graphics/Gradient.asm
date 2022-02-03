;
; https://docs.microsoft.com/en-us/windows/win32/api/gdiplusgraphics/nf-gdiplusgraphics-graphics-drawstring(constwchar_int_constfont_constpointf__constbrush)
;
include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"Gradient">

    .code

    assume rbx:ptr PAINTSTRUCT

OnPaint proc uses rbx hdc:HDC, ps:ptr PAINTSTRUCT

    mov rbx,ps
   .new g:Graphics(hdc)
   .new x:Point(0, 0)
   .new y:Point([rbx].rcPaint.right, [rbx].rcPaint.bottom)
   .new b:LinearGradientBrush(x, y, Red, Blue)

    g.FillRectangle(&b, 0, 0, [rbx].rcPaint.right, [rbx].rcPaint.bottom)
    b.Release()
    g.Release()
    ret

OnPaint endp

include Graphics.inc

