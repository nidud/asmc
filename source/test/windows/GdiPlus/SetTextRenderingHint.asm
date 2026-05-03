include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"SetSmoothingMode">

    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

   .new g:Graphics(hdc)

    ;; Set the text rendering hint to TextRenderingHintSingleBitPerPixel.

    g.SetTextRenderingHint(TextRenderingHintSingleBitPerPixel)

    ;; Draw text.

   .new f1:Font(L"Arial", 24.0)
   .new p1:PointF(0.0, 0.0)
   .new b1:SolidBrush(White)

    g.DrawString(L"Low quality rendering", 21, &f1, p1, NULL, &b1)

    ;; Get the text rendering hint.

   .new hint:TextRenderingHint
    mov hint,g.GetTextRenderingHint()

    ;; Set the text rendering hint to TextRenderingHintAntiAlias.

    g.SetTextRenderingHint(TextRenderingHintAntiAlias)

    ;; Draw more text to demonstrate the difference.

   .new f2:Font(L"Arial", 24.0)
   .new p2:PointF(0.0, 50.0)
   .new b2:SolidBrush(White)

    g.DrawString(L"High quality rendering", 22, &f1, p2, NULL, &b2)

    g.Release()
    ret

OnPaint endp

include Graphics.inc

