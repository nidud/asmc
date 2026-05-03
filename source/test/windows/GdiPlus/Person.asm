;
; https://docs.microsoft.com/en-us/windows/win32/api/gdiplusgraphics/nf-gdiplusgraphics-graphics-drawstring(constwchar_int_constfont_constpointf__constbrush)
;
include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"Person">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

    .new g:Graphics(hdc)
    .new Person:GraphicsPath()
    .new p:Pen(Yellow)

    Person.AddEllipse(23, 1, 14, 14)
    Person.AddLine(18, 16, 42, 16)
    Person.AddLine(50, 40, 44, 42)
    Person.AddLine(38, 25, 37, 42)
    Person.AddLine(45, 75, 37, 75)
    Person.AddLine(30, 50, 23, 75)
    Person.AddLine(16, 75, 23, 42)
    Person.AddLine(22, 25, 16, 42)
    Person.AddLine(10, 40, 18, 16)
    g.DrawPath(&p, &Person)

    p.Release()
    Person.Release()
    g.Release()
    ret

OnPaint endp

include Graphics.inc

