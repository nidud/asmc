;
; https://docs.microsoft.com/en-us/windows/win32/api/gdiplusgraphics/nf-gdiplusgraphics-graphics-drawstring(constwchar_int_constfont_constpointf__constbrush)
;
CLASSNAME equ <"Gradient">

OnPaint macro hdc

       .new g:Graphics(hdc)
       .new x:Point(0, 0)
       .new y:Point(ps.rcPaint.right, ps.rcPaint.bottom)
       .new b:LinearGradientBrush(&x, &y, Red, Blue)

        g.FillRectangle(&b, 0, 0, ps.rcPaint.right, ps.rcPaint.bottom)
        b.Release()
        g.Release()

    exitm<>
    endm

include Graphics.inc

