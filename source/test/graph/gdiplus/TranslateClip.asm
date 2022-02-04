include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"TranslateClip">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

    .new g:Graphics(hdc)
    .new b:SolidBrush(White)

    ; Create rectangle for clipping region.
    .new r:RectF(40.0, 20.0, 100.0, 100.0)

    ; Set clipping region of graphics to rectangle
    g.SetClip(r, CombineModeReplace)

    ; Translate clipping region
    g.TranslateClip(50, 50)

    ; Fill rectangle to demonstrate clip region
    g.FillRectangle(&b, 0, 0, 500, 300)

    b.Release()
    g.Release()
    ret

OnPaint endp

include Graphics.inc

