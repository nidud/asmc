
CLASSNAME equ <"SetCompositingMode">

OnPaint macro hdc

    .new g:Graphics(hdc)

    ;; Create a SolidBrush object with an alpha-blended color.

   .new c1:Color(180, 255, 0, 0)
   .new alphaBrush:SolidBrush(c1)

    ;; Set the compositing mode to CompositingModeSourceOver,
    ;; and fill a rectangle.

    g.SetCompositingMode(CompositingModeSourceOver)
    g.FillRectangle(&alphaBrush, 0, 0, 100, 100)

    ;; Set the compositing mode to CompositingModeSourceCopy,
    ;; and fill a rectangle.

    g.SetCompositingMode(CompositingModeSourceCopy)
    g.FillRectangle(&alphaBrush, 100, 0, 100, 100)

    g.Release()
    exitm<>
    endm

include Graphics.inc

