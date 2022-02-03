;
; https://docs.microsoft.com/en-us/windows/win32/api/gdiplusgraphics/nf-gdiplusgraphics-graphics-drawstring(constwchar_int_constfont_constpointf__constbrush)
;
include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"DrawString">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)
   .new p:PointF(20.0, 20.0)
   .new b:SolidBrush(Green)
   .new f:Font(L"Arial", 16.0)

    g.DrawString("Sample Text", 11, &f, p, NULL, &b)

    b.Release()
    f.Release()
    g.Release()
    ret

OnPaint endp

include Graphics.inc

