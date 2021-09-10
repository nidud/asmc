;
; https://docs.microsoft.com/en-us/windows/win32/api/gdiplusgraphics/nf-gdiplusgraphics-graphics-drawstring(constwchar_int_constfont_constpointf__constbrush)
;
CLASSNAME equ <"DrawString">

OnPaint macro hdc

   .new g:Graphics(hdc)
   .new p:PointF(20.0, 20.0)
   .new b:SolidBrush(Green)
   .new f:Font(L"Arial", 16.0)

    g.DrawString(L"Sample Text", 11, &f, &p, NULL, &b)

    b.Release()
    f.Release()
    g.Release()

    exitm<>
    endm

include Graphics.inc

