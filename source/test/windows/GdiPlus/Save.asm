;
; https://docs.microsoft.com/en-us/dotnet/api/system.drawing.graphics.save?view=dotnet-plat-ext-3.1
;
include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"Save">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

    .new g:Graphics(hdc)
    .new s:GraphicsState
    .new r:SolidBrush(Red)
    .new b:SolidBrush(Blue)

    ;; Translate transformation matrix
    g.TranslateTransform(100.0, 0.0)

    ;; Save translated graphics state
    mov s,g.Save()

    ;; Reset transformation matrix to identity and fill rectangle.
    g.ResetTransform()
    g.FillRectangle(&r, 0, 0, 100, 100)

    ;; Restore graphics state to translated state and fill second

    ;; rectangle.
    g.Restore(s)
    g.FillRectangle(&b, 0, 0, 100, 100)

    r.Release()
    b.Release()
    g.Release()
    ret

OnPaint endp

include Graphics.inc

