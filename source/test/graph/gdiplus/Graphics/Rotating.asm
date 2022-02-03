;
; https://docs.microsoft.com/en-us/windows/win32/api/gdiplusgraphics/nf-gdiplusgraphics-graphics-drawstring(constwchar_int_constfont_constpointf__constbrush)
;
include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"Rotating">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

    .new g:Graphics(hdc)
    .new c:GraphicsPath()
    .new p:Pen(White)

    c.AddEllipse(23, 1, 14, 14)
    c.AddLine(18, 16, 42, 16)
    c.AddLine(50, 40, 44, 42)
    c.AddLine(38, 25, 37, 42)
    c.AddLine(45, 75, 37, 75)
    c.AddLine(30, 50, 23, 75)
    c.AddLine(16, 75, 23, 42)
    c.AddLine(22, 25, 16, 42)
    c.AddLine(10, 40, 18, 16)

    g.TranslateTransform(100.0, 50.0)
    g.RotateTransform(35.0)
    g.DrawPath(&p, &c)
    g.ResetTransform()

    p.Release()
    c.Release()
    g.Release()
    ret

OnPaint endp

include Graphics.inc

