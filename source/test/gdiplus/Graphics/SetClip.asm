
CLASSNAME equ <"SetClip">

OnPaint macro hdc

    .new g:Graphics(hdc)
    .new b:SolidBrush(White)

    ; Create rectangle for clipping region.
    .new r:RectF(40.0, 20.0, 100.0, 100.0)

    ; Set clipping region of graphics to rectangle
    g.SetClip(&r, CombineModeReplace)

    ; Fill rectangle to demonstrate clip region
    g.FillRectangle(&b, 0, 0, 500, 300)

    b.Release()
    g.Release()

    exitm<>
    endm

include Graphics.inc

