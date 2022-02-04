;
; https://docs.microsoft.com/en-us/windows/win32/api/gdiplusgraphics/nf-gdiplusgraphics-graphics-drawstring(constwchar_int_constfont_constpointf__constbrush)
;
include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"MeasureString">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

    .new g:Graphics(hdc)
    .new p:Pen(Red)
    .new w:Pen(White)
    .new b:SolidBrush(Green)
    .new f:Font(L"Arial", 16.0)
    .new s:StringFormat()
    .new r:RectF(100.0, 60.0, 200.0, 100.0)
    .new z:RectF

    s.SetAlignment(StringAlignmentCenter)

    ;; Measure string.
    g.MeasureString(L"Measure String", 14, &f, r, &s, &z)

    ;; Draw rectangle representing the layout Rect.
    g.DrawRectangle(&w, r)

    ;; Draw rectangle representing size of string.
    g.DrawRectangle(&p, z)

    ;; Draw string to screen.
    g.DrawString(L"Measure String", -1, &f, r, &s, &b)

    s.Release()
    w.Release()
    p.Release()
    b.Release()
    f.Release()
    g.Release()
    ret

OnPaint endp

include Graphics.inc

